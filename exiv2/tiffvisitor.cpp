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
  File:      tiffvisitor.cpp
  Version:   $Rev: 1366 $
  Author(s): Andreas Huggel (ahu) <ahuggel@gmx.net>
  History:   11-Apr-06, ahu: created
 */
// *****************************************************************************
#include "rcsid.hpp"
EXIV2_RCSID("@(#) $Id: tiffvisitor.cpp 1366 2008-01-09 16:44:09Z ahuggel $")

// *****************************************************************************
// included header files
#ifdef _MSC_VER
# include "exv_msvc.h"
#else
# include "exv_conf.h"
#endif

#include "tiffcomposite.hpp"  // Do not change the order of these 2 includes,
#include "tiffvisitor.hpp"    // see bug #487
#include "tiffparser.hpp"
#include "makernote2.hpp"
#include "exif.hpp"
#include "iptc.hpp"
#include "value.hpp"
#include "image.hpp"
#include "jpgimage.hpp"
#include "i18n.h"             // NLS support.

// + standard includes
#include <string>
#include <iostream>
#include <iomanip>
#include <cassert>

// *****************************************************************************
// class member definitions
namespace Exiv2 {

    void TiffFinder::init(uint16_t tag, uint16_t group)
    {
        tag_ = tag;
        group_ = group;
        tiffComponent_ = 0;
    }

    void TiffFinder::findObject(TiffComponent* object)
    {
        if (object->tag() == tag_ && object->group() == group_) {
            tiffComponent_ = object;
            setGo(false);
        }
    }

    void TiffFinder::visitEntry(TiffEntry* object)
    {
        findObject(object);
    }

    void TiffFinder::visitDataEntry(TiffDataEntry* object)
    {
        findObject(object);
    }

    void TiffFinder::visitSizeEntry(TiffSizeEntry* object)
    {
        findObject(object);
    }

    void TiffFinder::visitDirectory(TiffDirectory* object)
    {
        findObject(object);
    }

    void TiffFinder::visitSubIfd(TiffSubIfd* object)
    {
        findObject(object);
    }

    void TiffFinder::visitMnEntry(TiffMnEntry* object)
    {
        findObject(object);
    }

    void TiffFinder::visitIfdMakernote(TiffIfdMakernote* object)
    {
        findObject(object);
    }

    void TiffFinder::visitArrayEntry(TiffArrayEntry* object)
    {
        findObject(object);
    }

    void TiffFinder::visitArrayElement(TiffArrayElement* object)
    {
        findObject(object);
    }

    TiffMetadataDecoder::TiffMetadataDecoder(Image* pImage,
                                             TiffComponent* const pRoot,
                                             FindDecoderFct findDecoderFct,
                                             uint32_t threshold)
        : pImage_(pImage),
          pRoot_(pRoot),
          findDecoderFct_(findDecoderFct),
          threshold_(threshold),
          decodedIptc_(false)
    {
        // Find camera make
        TiffFinder finder(0x010f, Group::ifd0);
        pRoot_->accept(finder);
        TiffEntryBase* te = dynamic_cast<TiffEntryBase*>(finder.result());
        if (te && te->pValue()) {
            make_ = te->pValue()->toString();
        }
    }

    void TiffMetadataDecoder::visitEntry(TiffEntry* object)
    {
        decodeTiffEntry(object);
    }

    void TiffMetadataDecoder::visitDataEntry(TiffDataEntry* object)
    {
        decodeTiffEntry(object);
    }

    void TiffMetadataDecoder::visitSizeEntry(TiffSizeEntry* object)
    {
        decodeTiffEntry(object);
    }

    void TiffMetadataDecoder::visitDirectory(TiffDirectory* /*object*/)
    {
        // Nothing to do
    }

    void TiffMetadataDecoder::visitSubIfd(TiffSubIfd* object)
    {
        decodeTiffEntry(object);
    }

    void TiffMetadataDecoder::visitMnEntry(TiffMnEntry* object)
    {
        if (!object->mn_) decodeTiffEntry(object);
    }

    void TiffMetadataDecoder::visitIfdMakernote(TiffIfdMakernote* /*object*/)
    {
        // Nothing to do
    }

    void TiffMetadataDecoder::decodeOlympThumb(const TiffEntryBase* object)
    {
        const DataValue* v = dynamic_cast<const DataValue*>(object->pValue());
        if (v != 0) {
            ExifData& exifData = pImage_->exifData();
            exifData["Exif.Thumbnail.Compression"] = uint16_t(6);
            DataBuf buf(v->size());
            v->copy(buf.pData_);
            Exifdatum& ed = exifData["Exif.Thumbnail.JPEGInterchangeFormat"];
            ed = uint32_t(0);
            ed.setDataArea(buf.pData_, buf.size_);
            exifData["Exif.Thumbnail.JPEGInterchangeFormatLength"] = uint32_t(buf.size_);
        }
    }

    void TiffMetadataDecoder::getObjData(byte const*& pData,
                                         long& size,
                                         uint16_t tag,
                                         uint16_t group,
                                         const TiffEntryBase* object)
    {
        if (object && object->tag() == tag && object->group() == group) {
            pData = object->pData();
            size = object->size();
            return;
        }
        TiffFinder finder(tag, group);
        pRoot_->accept(finder);
        TiffEntryBase const* te = dynamic_cast<TiffEntryBase*>(finder.result());
        if (te) {
            pData = te->pData();
            size = te->size();
            return;
        }
    }

    void TiffMetadataDecoder::decodeXmp(const TiffEntryBase* object)
    {
        // add Exif tag anyway
        decodeStdTiffEntry(object);

        byte const* pData = 0;
        long size = 0;
        getObjData(pData, size, 0x02bc, Group::ifd0, object);
        if (pData) {
            std::string& xmpPacket = pImage_->xmpPacket();
            xmpPacket.assign(reinterpret_cast<const char*>(pData), size);
            std::string::size_type idx = xmpPacket.find_first_of('<');
            if (idx != std::string::npos && idx > 0) {
#ifndef SUPPRESS_WARNINGS
                std::cerr << "Warning: Removing " << static_cast<unsigned long>(idx)
						  << " characters from the beginning of the XMP packet\n";
#endif
                xmpPacket = xmpPacket.substr(idx);
            }
            if (XmpParser::decode(pImage_->xmpData(), xmpPacket)) {
#ifndef SUPPRESS_WARNINGS
                std::cerr << "Warning: Failed to decode XMP metadata.\n";
#endif
            }
        }
    } // TiffMetadataDecoder::decodeXmp

    void TiffMetadataDecoder::decodeIptc(const TiffEntryBase* object)
    {
        // add Exif tag anyway
        decodeStdTiffEntry(object);

        // All tags are read at this point, so the first time we come here,
        // find the relevant IPTC tag and decode IPTC if found
        if (decodedIptc_) {
            return;
        }
        decodedIptc_ = true;
        // 1st choice: IPTCNAA
        byte const* pData = 0;
        long size = 0;
        getObjData(pData, size, 0x83bb, Group::ifd0, object);
        if (pData) {
            if (0 == pImage_->iptcData().load(pData, size)) {
                return;
            }
#ifndef SUPPRESS_WARNINGS
            else {
                std::cerr << "Warning: Failed to decode IPTC block found in "
                          << "Directory Image, entry 0x83bb\n";
            }
#endif
        }

        // 2nd choice if no IPTCNAA record found or failed to decode it:
        // ImageResources
        pData = 0;
        size = 0;
        getObjData(pData, size, 0x8649, Group::ifd0, object);
        if (pData) {
            byte const* record = 0;
            uint32_t sizeHdr = 0;
            uint32_t sizeData = 0;
            if (0 != Photoshop::locateIptcIrb(pData, size,
                                              &record, &sizeHdr, &sizeData)) {
                return;
            }
            if (0 == pImage_->iptcData().load(record + sizeHdr, sizeData)) {
                return;
            }
#ifndef SUPPRESS_WARNINGS
            else {
                std::cerr << "Warning: Failed to decode IPTC block found in "
                          << "Directory Image, entry 0x8649\n";
            }
#endif
        }
    } // TiffMetadataDecoder::decodeIptc

    void TiffMetadataDecoder::decodeSubIfd(const TiffEntryBase* object)
    {
        assert(object);

        // Only applicable if ifd0 NewSubfileType is Thumbnail/Preview image
        GroupType::const_iterator i = groupType_.find(Group::ifd0);
        if (i == groupType_.end() || (i->second & 1) == 0) return;

        // Only applicable if subIFD NewSubfileType is Primary image
        i = groupType_.find(object->group());
        if (i == groupType_.end() || (i->second & 1) == 1) return;

        // Todo: ExifKey should have an appropriate c'tor, it should not be
        //       necessary to use groupName here
        ExifKey key(object->tag(), tiffGroupName(Group::ifd0));
        setExifTag(key, object->pValue());

    }

    void TiffMetadataDecoder::decodeTiffEntry(const TiffEntryBase* object)
    {
        assert(object != 0);

        // Remember NewSubfileType
        if (object->tag() == 0x00fe && object->pValue()) {
            groupType_[object->group()] = object->pValue()->toLong();
        }

        const DecoderFct decoderFct = findDecoderFct_(make_,
                                                      object->tag(),
                                                      object->group());
        // skip decoding if decoderFct == 0
        if (decoderFct) {
            EXV_CALL_MEMBER_FN(*this, decoderFct)(object);
        }
    } // TiffMetadataDecoder::decodeTiffEntry

    void TiffMetadataDecoder::decodeStdTiffEntry(const TiffEntryBase* object)
    {
        assert(object !=0);
        assert(pImage_ != 0);
        // "Normal" tag has low priority: only decode if it doesn't exist yet.
        // Todo: ExifKey should have an appropriate c'tor, it should not be
        //       necessary to use groupName here
        ExifKey key(object->tag(), object->groupName());
        // Todo: Too much searching here, optimize when threshold goes.
        if (pImage_->exifData().findKey(key) == pImage_->exifData().end()) {
            setExifTag(key, object->pValue());
        }
    } // TiffMetadataDecoder::decodeTiffEntry

    void TiffMetadataDecoder::setExifTag(const ExifKey& key, const Value* pValue)
    {
        if (   threshold_ > 0
            && pValue != 0
            && static_cast<uint32_t>(pValue->size()) > threshold_
            && key.tagName().substr(0, 2) == "0x") {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Warning: "
                      << "Size " << pValue->size() << " of " << key.key()
                      << " exceeds " << threshold_
                      << " bytes limit. Not decoded.\n";
#endif
            return;
        }
        assert(pImage_ != 0);
        ExifData::iterator pos = pImage_->exifData().findKey(key);
        if (pos != pImage_->exifData().end()) pImage_->exifData().erase(pos);
        pImage_->exifData().add(key, pValue);

    } // TiffMetadataDecoder::addExifTag

    void TiffMetadataDecoder::visitArrayEntry(TiffArrayEntry* /*object*/)
    {
        // Nothing to do
    }

    void TiffMetadataDecoder::visitArrayElement(TiffArrayElement* object)
    {
        decodeTiffEntry(object);
    }

    const std::string TiffPrinter::indent_("   ");

    void TiffPrinter::incIndent()
    {
        prefix_ += indent_;
    } // TiffPrinter::incIndent

    void TiffPrinter::decIndent()
    {
        if (prefix_.length() >= indent_.length()) {
            prefix_.erase(prefix_.length() - indent_.length(), indent_.length());
        }
    } // TiffPrinter::decIndent

    void TiffPrinter::visitEntry(TiffEntry* object)
    {
        printTiffEntry(object, prefix());
    } // TiffPrinter::visitEntry

    void TiffPrinter::visitDataEntry(TiffDataEntry* object)
    {
        printTiffEntry(object, prefix());
        if (object->pValue()) {
            os_ << prefix() << _("Data area") << " "
                << object->pValue()->sizeDataArea()
                << " " << _("bytes.\n");
        }
    } // TiffPrinter::visitEntry

    void TiffPrinter::visitSizeEntry(TiffSizeEntry* object)
    {
        printTiffEntry(object, prefix());
    }

    void TiffPrinter::visitDirectory(TiffDirectory* object)
    {
        assert(object != 0);

        os_ << prefix() << object->groupName() << " " << _("directory with") << " "
        // cast to make MSVC happy
           << std::dec << static_cast<unsigned int>(object->components_.size());
        if (object->components_.size() == 1) os_ << " " << _("entry:\n");
        else os_ << " " << _("entries:\n");
        incIndent();

    } // TiffPrinter::visitDirectory

    void TiffPrinter::visitDirectoryNext(TiffDirectory* object)
    {
        decIndent();
        if (object->hasNext()) {
            if (object->pNext_) os_ << prefix() << _("Next directory:\n");
            else os_ << prefix() << _("No next directory\n");
        }
    } // TiffPrinter::visitDirectoryNext

    void TiffPrinter::visitDirectoryEnd(TiffDirectory* /*object*/)
    {
        // Nothing to do
    } // TiffPrinter::visitDirectoryEnd

    void TiffPrinter::visitSubIfd(TiffSubIfd* object)
    {
        os_ << prefix() << _("Sub-IFD") << " ";
        printTiffEntry(object);
    } // TiffPrinter::visitSubIfd

    void TiffPrinter::visitMnEntry(TiffMnEntry* object)
    {
        if (!object->mn_) printTiffEntry(object, prefix());
        else os_ << prefix() << _("Makernote") << " ";
    } // TiffPrinter::visitMnEntry

    void TiffPrinter::visitIfdMakernote(TiffIfdMakernote* /*object*/)
    {
        // Nothing to do
    } // TiffPrinter::visitIfdMakernote

    void TiffPrinter::printTiffEntry(TiffEntryBase* object,
                                     const std::string& px) const
    {
        assert(object != 0);

        os_ << px << object->groupName()
            << " " << _("tag") << " 0x" << std::setw(4) << std::setfill('0')
            << std::hex << std::right << object->tag()
            << ", " << _("type") << " " << TypeInfo::typeName(object->typeId())
            << ", " << std::dec << object->count() << " "<< _("component");
        if (object->count() > 1) os_ << "s";
        os_ << " in " << object->size() << " " << _("bytes");
        if (object->size() > 4) os_ << ", " << _("offset") << " " << object->offset();
        os_ << "\n";
        const Value* vp = object->pValue();
        if (vp && vp->count() < 100) os_ << prefix() << *vp;
        else os_ << prefix() << "...";
        os_ << "\n";

    } // TiffPrinter::printTiffEntry

    void TiffPrinter::visitArrayEntry(TiffArrayEntry* object)
    {
        // Array entry degenerates to a normal entry if type is not unsignedShort
        if (object->typeId() != unsignedShort) {
            printTiffEntry(object, prefix());
        }
        else {
            os_ << prefix() << _("Array Entry") << " " << object->groupName()
                << " " << _("tag") << " 0x" << std::setw(4) << std::setfill('0')
                << std::hex << std::right << object->tag() << "\n";
        }
    } // TiffPrinter::visitArrayEntry

    void TiffPrinter::visitArrayElement(TiffArrayElement* object)
    {
        printTiffEntry(object, prefix());
    } // TiffPrinter::visitArrayElement

    TiffReader::TiffReader(const byte*    pData,
                           uint32_t       size,
                           TiffComponent* pRoot,
                           TiffRwState::AutoPtr state)
        : pData_(pData),
          size_(size),
          pLast_(pData + size),
          pRoot_(pRoot),
          pState_(state.release()),
          pOrigState_(pState_)
    {
        assert(pData_);
        assert(size_ > 0);

    } // TiffReader::TiffReader

    TiffReader::~TiffReader()
    {
        if (pOrigState_ != pState_) delete pOrigState_;
        delete pState_;
    }

    void TiffReader::resetState() {
        if (pOrigState_ != pState_) delete pState_;
        pState_ = pOrigState_;
    }

    void TiffReader::changeState(TiffRwState::AutoPtr state)
    {
        if (state.get() != 0) {
            if (pOrigState_ != pState_) delete pState_;
            // 0 for create function indicates 'no change'
            if (state->createFct_ == 0) state->createFct_ = pState_->createFct_;
            // invalidByteOrder indicates 'no change'
            if (state->byteOrder_ == invalidByteOrder) state->byteOrder_ = pState_->byteOrder_;
            pState_ = state.release();
        }
    }

    ByteOrder TiffReader::byteOrder() const
    {
        assert(pState_);
        return pState_->byteOrder_;
    }

    uint32_t TiffReader::baseOffset() const
    {
        assert(pState_);
        return pState_->baseOffset_;
    }

    TiffComponent::AutoPtr TiffReader::create(uint32_t extendedTag,
                                              uint16_t group) const
    {
        assert(pState_);
        assert(pState_->createFct_);
        return pState_->createFct_(extendedTag, group);
    }

    void TiffReader::visitEntry(TiffEntry* object)
    {
        readTiffEntry(object);
    }

    void TiffReader::visitDataEntry(TiffDataEntry* object)
    {
        assert(object != 0);

        readTiffEntry(object);
        TiffFinder finder(object->szTag(), object->szGroup());
        pRoot_->accept(finder);
        TiffEntryBase* te = dynamic_cast<TiffEntryBase*>(finder.result());
        if (te && te->pValue()) {
            setDataArea(object, te->pValue());
        }
    }

    void TiffReader::visitSizeEntry(TiffSizeEntry* object)
    {
        assert(object != 0);

        readTiffEntry(object);
        TiffFinder finder(object->dtTag(), object->dtGroup());
        pRoot_->accept(finder);
        TiffEntryBase* te = dynamic_cast<TiffEntryBase*>(finder.result());
        if (te && te->pValue()) {
            setDataArea(te, object->pValue());
        }
    }

    void TiffReader::setDataArea(TiffEntryBase* pOffsetEntry, const Value* pSize)
    {
        assert(pOffsetEntry);
        assert(pSize);

        Value* pOffset = pOffsetEntry->pValue_;
        assert(pOffset);

        long size = 0;
        for (long i = 0; i < pSize->count(); ++i) {
            size += pSize->toLong(i);
        }
        long offset = pOffset->toLong(0);
        // Todo: Remove limitation of Jpeg writer: strips must be contiguous
        // Until then we check: last offset + last size - first offset == size?
        if (  pOffset->toLong(pOffset->count()-1)
            + pSize->toLong(pSize->count()-1)
            - offset != size) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Warning: "
                      << "Directory " << pOffsetEntry->groupName()
                      << ", entry 0x" << std::setw(4)
                      << std::setfill('0') << std::hex << pOffsetEntry->tag()
                      << " Data area is not contiguous, ignoring it.\n";
#endif
            return;
        }
        if (baseOffset() + offset + size > size_) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Warning: "
                      << "Directory " << pOffsetEntry->groupName()
                      << ", entry 0x" << std::setw(4)
                      << std::setfill('0') << std::hex << pOffsetEntry->tag()
                      << " Data area exceeds data buffer, ignoring it.\n";
#endif
            return;
        }
        pOffset->setDataArea(pData_ + baseOffset() + offset, size);
    }

    void TiffReader::visitDirectory(TiffDirectory* object)
    {
        assert(object != 0);

        const byte* p = object->start();
        assert(p >= pData_);

        if (p + 2 > pLast_) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Error: "
                      << "Directory " << object->groupName()
                      << ": IFD exceeds data buffer, cannot read entry count.\n";
#endif
            return;
        }
        const uint16_t n = getUShort(p, byteOrder());
        p += 2;
        // Sanity check with an "unreasonably" large number
        if (n > 256) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Error: "
                      << "Directory " << object->groupName() << " with "
                      << n << " entries considered invalid; not read.\n";
#endif
            return;
        }
        for (uint16_t i = 0; i < n; ++i) {
            if (p + 12 > pLast_) {
#ifndef SUPPRESS_WARNINGS
                std::cerr << "Error: "
                          << "Directory " << object->groupName()
                          << ": IFD entry " << i
                          << " lies outside of the data buffer.\n";
#endif
                return;
            }
            uint16_t tag = getUShort(p, byteOrder());
            TiffComponent::AutoPtr tc = create(tag, object->group());
            assert(tc.get());
            tc->setStart(p);
            object->addChild(tc);
            p += 12;
        }

        if (p + 4 > pLast_) {
#ifndef SUPPRESS_WARNINGS
                std::cerr << "Error: "
                          << "Directory " << object->groupName()
                          << ": IFD exceeds data buffer, cannot read next pointer.\n";
#endif
                return;
        }
        if (object->hasNext()) {
            TiffComponent::AutoPtr tc(0);
            uint32_t next = getLong(p, byteOrder());
            if (next) {
                tc = create(Tag::next, object->group());
#ifndef SUPPRESS_WARNINGS
                if (tc.get() == 0) {
                    std::cerr << "Warning: "
                              << "Directory " << object->groupName()
                              << " has an unhandled next pointer.\n";
                }
#endif
            }
            if (tc.get()) {
                if (baseOffset() + next > size_) {
#ifndef SUPPRESS_WARNINGS
                    std::cerr << "Error: "
                              << "Directory " << object->groupName()
                              << ": Next pointer is out of bounds.\n";
#endif
                    return;
                }
                tc->setStart(pData_ + baseOffset() + next);
                object->addNext(tc);
            }
        } // object->hasNext()

    } // TiffReader::visitDirectory

    void TiffReader::visitSubIfd(TiffSubIfd* object)
    {
        assert(object != 0);

        readTiffEntry(object);
        if (object->typeId() == unsignedLong && object->count() >= 1) {
            for (uint32_t i = 0; i < object->count(); ++i) {
                uint32_t offset = getULong(object->pData() + 4*i, byteOrder());
                if (baseOffset() + offset > size_) {
#ifndef SUPPRESS_WARNINGS
                    std::cerr << "Error: "
                              << "Directory " << object->groupName()
                              << ", entry 0x" << std::setw(4)
                              << std::setfill('0') << std::hex << object->tag()
                              << " Sub-IFD pointer " << i
                              << " is out of bounds; ignoring it.\n";
#endif
                    return;
                }
                // If there are multiple dirs, group is incremented for each
                TiffComponent::AutoPtr td(new TiffDirectory(object->tag(),
                                                            object->newGroup_ + i));
                td->setStart(pData_ + baseOffset() + offset);
                object->addChild(td);
            }
        }
#ifndef SUPPRESS_WARNINGS
        else {
            std::cerr << "Warning: "
                      << "Directory " << object->groupName()
                      << ", entry 0x" << std::setw(4)
                      << std::setfill('0') << std::hex << object->tag()
                      << " doesn't look like a sub-IFD.";
        }
#endif

    } // TiffReader::visitSubIfd

    void TiffReader::visitMnEntry(TiffMnEntry* object)
    {
        assert(object != 0);

        readTiffEntry(object);
        // Find camera make
        TiffFinder finder(0x010f, Group::ifd0);
        pRoot_->accept(finder);
        TiffEntryBase* te = dynamic_cast<TiffEntryBase*>(finder.result());
        std::string make;
        if (te && te->pValue()) {
            make = te->pValue()->toString();
            // create concrete makernote, based on make and makernote contents
            object->mn_ = TiffMnCreator::create(object->tag(),
                                                object->mnGroup_,
                                                make,
                                                object->pData(),
                                                object->size(),
                                                byteOrder());
        }
        if (object->mn_) object->mn_->setStart(object->pData());

    } // TiffReader::visitMnEntry

    void TiffReader::visitIfdMakernote(TiffIfdMakernote* object)
    {
        assert(object != 0);

        if (!object->readHeader(object->start(),
                                static_cast<uint32_t>(pLast_ - object->start()),
                                byteOrder())) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Error: Failed to read "
                      << object->ifd_.groupName()
                      << " IFD Makernote header.\n";
#ifdef DEBUG
            if (static_cast<uint32_t>(pLast_ - object->start()) >= 16) {
                hexdump(std::cerr, object->start(), 16);
            }
#endif // DEBUG
#endif // SUPPRESS_WARNINGS
            setGo(false);
            return;
        }
        // Modify reader for Makernote peculiarities, byte order and offset
        TiffRwState::AutoPtr state(
            new TiffRwState(object->byteOrder(),
                            object->baseOffset(static_cast<uint32_t>(object->start() - pData_))));
        changeState(state);
        object->ifd_.setStart(object->start() + object->ifdOffset());

    } // TiffReader::visitIfdMakernote

    void TiffReader::visitIfdMakernoteEnd(TiffIfdMakernote* /*object*/)
    {
        // Reset state (byte order, create function, offset) back to that
        // for the image
        resetState();
    } // TiffReader::visitIfdMakernoteEnd

    void TiffReader::readTiffEntry(TiffEntryBase* object)
    {
        assert(object != 0);

        const byte* p = object->start();
        assert(p >= pData_);

        if (p + 12 > pLast_) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Error: Entry in directory " << object->groupName()
                      << "requests access to memory beyond the data buffer. "
                      << "Skipping entry.\n";
#endif
            return;
        }
        // Component already has tag
        p += 2;
        object->type_ = getUShort(p, byteOrder());
        long typeSize = TypeInfo::typeSize(object->typeId());
        if (0 == typeSize) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Error: Directory " << object->groupName()
                      << ", entry 0x" << std::setw(4)
                      << std::setfill('0') << std::hex << object->tag()
                      << " has an invalid type:\n"
                      << "Type = " << std::dec << object->type_
                      << "; skipping entry.\n";
#endif
            return;
        }
        p += 2;
        object->count_ = getULong(p, byteOrder());
        p += 4;
        object->size_ = typeSize * object->count();
        object->offset_ = getULong(p, byteOrder());
        object->pData_ = p;
        if (object->size() > 4) {
            if (baseOffset() + object->offset() >= size_) {
#ifndef SUPPRESS_WARNINGS
                std::cerr << "Error: Offset of "
                          << "directory " << object->groupName()
                          << ", entry 0x" << std::setw(4)
                          << std::setfill('0') << std::hex << object->tag()
                          << " is out of bounds:\n"
                          << "Offset = 0x" << std::setw(8)
                          << std::setfill('0') << std::hex << object->offset()
                          << "; truncating the entry\n";
#endif
                object->size_ = 0;
                object->count_ = 0;
                object->offset_ = 0;
                return;
            }
            object->pData_ = pData_ + baseOffset() + object->offset();
            if (object->size() > static_cast<uint32_t>(pLast_ - object->pData())) {
#ifndef SUPPRESS_WARNINGS
                std::cerr << "Warning: Upper boundary of data for "
                          << "directory " << object->groupName()
                          << ", entry 0x" << std::setw(4)
                          << std::setfill('0') << std::hex << object->tag()
                          << " is out of bounds:\n"
                          << "Offset = 0x" << std::setw(8)
                          << std::setfill('0') << std::hex << object->offset()
                          << ", size = " << std::dec << object->size()
                          << ", exceeds buffer size by "
                          // cast to make MSVC happy
                          << static_cast<uint32_t>(object->pData() + object->size() - pLast_)
                          << " Bytes; adjusting the size\n";
#endif
                object->size_ = static_cast<uint32_t>(pLast_ - object->pData() + 1);
                // todo: adjust count_, make size_ a multiple of typeSize
            }
        }
        // On the fly type conversion for Exif.Photo.UserComment
        // Todo: This should be somewhere else, maybe in a Value factory
        // which takes a Key and Type
        TypeId t = TypeId(object->typeId());
        if (   object->tag()    == 0x9286
            && object->group()  == Group::exif
            && object->typeId() == undefined) {
            t = comment;
        }
        Value::AutoPtr v = Value::create(t);
        if (v.get()) {
            v->read(object->pData(), object->size(), byteOrder());
            object->pValue_ = v.release();
        }

    } // TiffReader::readTiffEntry

    void TiffReader::visitArrayEntry(TiffArrayEntry* object)
    {
        assert(object != 0);

        readTiffEntry(object);
        uint16_t s = static_cast<uint16_t>(object->size() / object->elSize());
        for (uint16_t i = 0; i < s; ++i) {
            uint16_t tag = i;
            TiffComponent::AutoPtr tc = create(tag, object->elGroup());
            assert(tc.get());
            tc->setStart(object->pData() + i * object->elSize());
            object->addChild(tc);
        }

    } // TiffReader::visitArrayEntry

    void TiffReader::visitArrayElement(TiffArrayElement* object)
    {
        assert(object != 0);

        const byte* p = object->start();
        assert(p >= pData_);

        if (p + 2 > pLast_) {
#ifndef SUPPRESS_WARNINGS
            std::cerr << "Error: Array element in group " << object->groupName()
                      << "requests access to memory beyond the data buffer. "
                      << "Skipping element.\n";
#endif
            return;
        }
        object->type_ = object->elTypeId();
        object->count_ = 1;
        object->size_ = TypeInfo::typeSize(object->typeId()) * object->count();
        object->offset_ = 0;
        object->pData_ = p;
        Value::AutoPtr v = Value::create(object->typeId());
        if (v.get()) {
            ByteOrder b =
                object->elByteOrder() == invalidByteOrder ?
                byteOrder() : object->elByteOrder();
            v->read(object->pData(), object->size(), b);
            object->pValue_ = v.release();
        }

    } // TiffReader::visitArrayElement

}                                       // namespace Exiv2
