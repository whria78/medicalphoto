// ***************************************************************** -*- C++ -*-
/*
 * Copyright (C) 2004-2008 Andreas Huggel <ahuggel@gmx.net>
 *
 * This program is part of the Exiv2 distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, 5th Floor, Boston, MA 02110-1301 USA.
 */
/*
  File:      image.cpp
  Version:   $Rev: 1404 $
  Author(s): Andreas Huggel (ahu) <ahuggel@gmx.net>
             Brad Schick (brad) <brad@robotbattle.com>
  History:   26-Jan-04, ahu: created
             11-Feb-04, ahu: isolated as a component
             19-Jul-04, brad: revamped to be more flexible and support Iptc
             15-Jan-05, brad: inside-out design changes
 */
// *****************************************************************************
#include "rcsid.hpp"
EXIV2_RCSID("@(#) $Id: image.cpp 1404 2008-04-15 03:46:01Z ahuggel $")

// *****************************************************************************
// included header files
#ifdef _MSC_VER
# include "exv_msvc.h"
#else
# include "exv_conf.h"
#endif

#include "image.hpp"
#include "error.hpp"
#include "futils.hpp"

#include "cr2image.hpp"
#include "crwimage.hpp"
#include "jpgimage.hpp"
#include "mrwimage.hpp"
#ifdef EXV_HAVE_LIBZ
# include "pngimage.hpp"
#endif // EXV_HAVE_LIBZ
#include "rafimage.hpp"
#include "tiffimage.hpp"
#include "orfimage.hpp"
#include "gifimage.hpp"
#include "psdimage.hpp"
#include "tgaimage.hpp"
#include "bmpimage.hpp"
#include "jp2image.hpp"
#include "xmpsidecar.hpp"

// + standard includes
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _MSC_VER
# define S_ISREG(m)      (((m) & S_IFMT) == S_IFREG)
#endif
#ifdef EXV_HAVE_UNISTD_H
# include <unistd.h>                            // stat
#endif

// *****************************************************************************
// class member definitions
namespace Exiv2 {

    const ImageFactory::Registry ImageFactory::registry_[] = {
        //image type       creation fct     type check  Exif mode    IPTC mode    XMP mode     Comment mode
        //---------------  ---------------  ----------  -----------  -----------  -----------  ------------
        { ImageType::jpeg, newJpegInstance, isJpegType, amReadWrite, amReadWrite, amReadWrite, amReadWrite },
        { ImageType::exv,  newExvInstance,  isExvType,  amReadWrite, amReadWrite, amReadWrite, amReadWrite },
        { ImageType::cr2,  newCr2Instance,  isCr2Type,  amRead,      amRead,      amRead,      amNone      },
        { ImageType::crw,  newCrwInstance,  isCrwType,  amReadWrite, amNone,      amNone,      amReadWrite },
        { ImageType::mrw,  newMrwInstance,  isMrwType,  amRead,      amRead,      amRead,      amNone      },
        { ImageType::tiff, newTiffInstance, isTiffType, amRead,      amRead,      amRead,      amNone      },
        { ImageType::orf,  newOrfInstance,  isOrfType,  amRead,      amRead,      amRead,      amNone      },
  #ifdef EXV_HAVE_LIBZ
        { ImageType::png,  newPngInstance,  isPngType,  amRead,      amRead,      amRead,      amNone      },
  #endif // EXV_HAVE_LIBZ
        { ImageType::raf,  newRafInstance,  isRafType,  amRead,      amRead,      amRead,      amNone      },
        { ImageType::xmp,  newXmpInstance,  isXmpType,  amNone,      amNone,      amReadWrite, amNone      },
        { ImageType::gif,  newGifInstance,  isGifType,  amNone,      amNone,      amNone,      amNone      },
        { ImageType::psd,  newPsdInstance,  isPsdType,  amRead,      amRead,      amRead,      amNone      },
        { ImageType::tga,  newTgaInstance,  isTgaType,  amNone,      amNone,      amNone,      amNone      },
        { ImageType::bmp,  newBmpInstance,  isBmpType,  amNone,      amNone,      amNone,      amNone      },
        { ImageType::jp2,  newJp2Instance,  isJp2Type,  amRead,      amRead,      amRead,      amNone      },
        // End of list marker
        { ImageType::none, 0,               0,          amNone,      amNone,      amNone,      amNone      }
    };

    bool ImageFactory::Registry::operator==(const int& imageType) const
    {
        return imageType == imageType_;
    }

    Image::Image(int              imageType, 
                 uint16_t         supportedMetadata,
                 BasicIo::AutoPtr io)
        : io_(io),
          pixelWidth_(0),
          pixelHeight_(0),
          imageType_(imageType),
          supportedMetadata_(supportedMetadata),
#ifdef EXV_HAVE_XMP_TOOLKIT
          writeXmpFromPacket_(false)
#else 
          writeXmpFromPacket_(true)
#endif
    {
    }

    void Image::clearMetadata()
    {
        clearExifData();
        clearIptcData();
        clearXmpPacket();
        clearXmpData();
        clearComment();
    }

    void Image::setMetadata(const Image& image)
    {
        setExifData(image.exifData());
        setIptcData(image.iptcData());
        setXmpPacket(image.xmpPacket());
        setXmpData(image.xmpData());
        setComment(image.comment());
    }

    void Image::clearExifData()
    {
        exifData_.clear();
    }

    void Image::setExifData(const ExifData& exifData)
    {
        exifData_ = exifData;
    }

    void Image::clearIptcData()
    {
        iptcData_.clear();
    }

    void Image::setIptcData(const IptcData& iptcData)
    {
        iptcData_ = iptcData;
    }

    void Image::clearXmpPacket()
    {
        xmpPacket_.clear();
        writeXmpFromPacket(true);
    }

    void Image::setXmpPacket(const std::string& xmpPacket)
    {
        xmpPacket_ = xmpPacket;
        writeXmpFromPacket(true);
    }

    void Image::clearXmpData()
    {
        xmpData_.clear();
        writeXmpFromPacket(false);
    }

    void Image::setXmpData(const XmpData& xmpData)
    {
        xmpData_ = xmpData;
        writeXmpFromPacket(false);
    }

    void Image::writeXmpFromPacket(bool flag)
    {
#ifdef EXV_HAVE_XMP_TOOLKIT
        writeXmpFromPacket_ = flag; 
#endif
    }

    void Image::clearComment()
    {
        comment_.erase();
    }

    void Image::setComment(const std::string& comment)
    {
        comment_ = comment;
    }

    bool Image::good() const
    {
        if (io_->open() != 0) return false;
        IoCloser closer(*io_);
        return ImageFactory::checkType(imageType_, *io_, false);
    }

    bool Image::supportsMetadata(MetadataId metadataId) const
    {
        return (supportedMetadata_ & metadataId) != 0;
    }

    AccessMode Image::checkMode(MetadataId metadataId) const
    {
        return ImageFactory::checkMode(imageType_, metadataId);
    }

    AccessMode ImageFactory::checkMode(int type, MetadataId metadataId)
    {
        const Registry* r = find(registry_, type);
        if (!r) throw Error(13, type);
        AccessMode am = amNone;
        switch (metadataId) {
        case mdNone:
            break;
        case mdExif:
            am = r->exifSupport_;
            break;
        case mdIptc:
            am = r->iptcSupport_;
            break;
        case mdXmp:
            am = r->xmpSupport_;
            break;
        case mdComment:
            am = r->commentSupport_;
            break;
        // no default: let the compiler complain
        }
        return am;
    }

    bool ImageFactory::checkType(int type, BasicIo& io, bool advance)
    {
        const Registry* r = find(registry_, type);
        if (0 != r) {
            return r->isThisType_(io, advance);
        }
        return false;
    } // ImageFactory::checkType

    int ImageFactory::getType(const std::string& path)
    {
        FileIo fileIo(path);
        return getType(fileIo);
    }

    int ImageFactory::getType(const byte* data, long size)
    {
        MemIo memIo(data, size);
        return getType(memIo);
    }

    int ImageFactory::getType(BasicIo& io)
    {
        if (io.open() != 0) return ImageType::none;
        IoCloser closer(io);
        for (unsigned int i = 0; registry_[i].imageType_ != ImageType::none; ++i) {
            if (registry_[i].isThisType_(io, false)) {
                return registry_[i].imageType_;
            }
        }
        return ImageType::none;
    } // ImageFactory::getType

    Image::AutoPtr ImageFactory::open(const std::string& path)
    {
        BasicIo::AutoPtr io(new FileIo(path));
        Image::AutoPtr image = open(io); // may throw
        if (image.get() == 0) throw Error(11, path);
        return image;
    }

    Image::AutoPtr ImageFactory::open(const byte* data, long size)
    {
        BasicIo::AutoPtr io(new MemIo(data, size));
        Image::AutoPtr image = open(io); // may throw
        if (image.get() == 0) throw Error(12);
        return image;
    }

    Image::AutoPtr ImageFactory::open(BasicIo::AutoPtr io)
    {
        if (io->open() != 0) {
            throw Error(9, io->path(), strError());
        }
        for (unsigned int i = 0; registry_[i].imageType_ != ImageType::none; ++i) {
            if (registry_[i].isThisType_(*io, false)) {
                return registry_[i].newInstance_(io, false);
            }
        }
        return Image::AutoPtr();
    } // ImageFactory::open

    Image::AutoPtr ImageFactory::create(int type,
                                        const std::string& path)
    {
        std::auto_ptr<FileIo> fileIo(new FileIo(path));
        // Create or overwrite the file, then close it
        if (fileIo->open("w+b") != 0) {
            throw Error(10, path, "w+b", strError());
        }
        fileIo->close();
        BasicIo::AutoPtr io(fileIo);
        Image::AutoPtr image = create(type, io);
        if (image.get() == 0) throw Error(13, type);
        return image;
    }

    Image::AutoPtr ImageFactory::create(int type)
    {
        BasicIo::AutoPtr io(new MemIo);
        Image::AutoPtr image = create(type, io);
        if (image.get() == 0) throw Error(13, type);
        return image;
    }

    Image::AutoPtr ImageFactory::create(int type,
                                        BasicIo::AutoPtr io)
    {
        // BasicIo instance does not need to be open
        const Registry* r = find(registry_, type);
        if (0 != r) {
            return r->newInstance_(io, true);
        }
        return Image::AutoPtr();
    } // ImageFactory::create

    TiffHeader::TiffHeader(ByteOrder byteOrder)
        : byteOrder_(byteOrder), tag_(0x002a), offset_(0x00000008)
    {
    }

    int TiffHeader::read(const byte* buf)
    {
        if (buf[0] == 0x49 && buf[1] == 0x49) {
            byteOrder_ = littleEndian;
        }
        else if (buf[0] == 0x4d && buf[1] == 0x4d) {
            byteOrder_ = bigEndian;
        }
        else {
            return 1;
        }
        tag_ = getUShort(buf+2, byteOrder_);
        offset_ = getULong(buf+4, byteOrder_);
        return 0;
    }

    long TiffHeader::copy(byte* buf) const
    {
        switch (byteOrder_) {
        case littleEndian:
            buf[0] = 0x49;
            buf[1] = 0x49;
            break;
        case bigEndian:
            buf[0] = 0x4d;
            buf[1] = 0x4d;
            break;
        case invalidByteOrder:
            // do nothing
            break;
        }
        us2Data(buf+2, 0x002a, byteOrder_);
        ul2Data(buf+4, 0x00000008, byteOrder_);
        return size();
    } // TiffHeader::copy

// *****************************************************************************
// template, inline and free functions

    void append(Blob& blob, const byte* buf, uint32_t len)
    {
        if (len != 0) {
            assert(buf != 0);
            Blob::size_type size = blob.size();
            if (blob.capacity() - size < len) {
                blob.reserve(size + 65536);
            }
            blob.resize(size + len);
            std::memcpy(&blob[size], buf, len);
        }
    } // append

}                                       // namespace Exiv2
