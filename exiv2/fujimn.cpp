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
  File:      fujimn.cpp
  Version:   $Rev: 1473 $
  Author(s): Andreas Huggel (ahu) <ahuggel@gmx.net>
             Gilles Caulier (gc) <caulier.gilles@kdemail.net>
  History:   18-Feb-04, ahu: created
             07-Mar-04, ahu: isolated as a separate component
  Credits:   See header file.
 */
// *****************************************************************************
#include "rcsid.hpp"
EXIV2_RCSID("@(#) $Id: fujimn.cpp 1473 2008-06-03 02:15:04Z ahuggel $")

// *****************************************************************************
// included header files
#include "types.hpp"
#include "fujimn.hpp"
#include "makernote.hpp"
#include "value.hpp"
#include "i18n.h"                // NLS support.

// + standard includes
#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstring>

// *****************************************************************************
// class member definitions
namespace Exiv2 {

    //! @cond IGNORE
    FujiMakerNote::RegisterMn::RegisterMn()
    {
        MakerNoteFactory::registerMakerNote("FUJIFILM", "*", createFujiMakerNote);
        MakerNoteFactory::registerMakerNote(
            fujiIfdId, MakerNote::AutoPtr(new FujiMakerNote));
    }
    //! @endcond

    //! OffOn, multiple tags
    extern const TagDetails fujiOffOn[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Sharpness, tag 0x1001
    extern const TagDetails fujiSharpness[] = {
        { 1, N_("Soft mode 1") },
        { 2, N_("Soft mode 2") },
        { 3, N_("Normal")      },
        { 4, N_("Hard mode 1") },
        { 5, N_("Hard mode 2") }
    };

    //! WhiteBalance, tag 0x1002
    extern const TagDetails fujiWhiteBalance[] = {
        {    0, N_("Auto")                     },
        {  256, N_("Daylight")                 },
        {  512, N_("Cloudy")                   },
        {  768, N_("Fluorescent (daylight)")   },
        {  769, N_("Fluorescent (warm white)") },
        {  770, N_("Fluorescent (cool white)") },
        { 1024, N_("Incandescent")             },
        { 3480, N_("Custom")                   }
    };

    //! Color, tag 0x1003
    extern const TagDetails fujiColor[] = {
        {   0, N_("Normal")               },
        { 256, N_("High")                 },
        { 512, N_("Low")                  },
        { 768, N_("None (black & white)") }
    };

    //! Tone, tag 0x1004
    extern const TagDetails fujiTone[] = {
        {   0, N_("Normal") },
        { 256, N_("High")   },
        { 512, N_("Low")    }
    };

    //! FlashMode, tag 0x1010
    extern const TagDetails fujiFlashMode[] = {
        { 0, N_("Auto")              },
        { 1, N_("On")                },
        { 2, N_("Off")               },
        { 3, N_("Red-eye reduction") }
    };

    //! FocusMode, tag 0x1021
    extern const TagDetails fujiFocusMode[] = {
        { 0, N_("Auto")   },
        { 1, N_("Manual") }
    };

    //! PictureMode, tag 0x1031
    extern const TagDetails fujiPictureMode[] = {
        {   0, N_("Auto")                      },
        {   1, N_("Portrait")                  },
        {   2, N_("Landscape")                 },
        {   4, N_("Sports")                    },
        {   5, N_("Night scene")               },
        {   6, N_("Program AE")                },
        {   7, N_("Natural light")             },
        {   8, N_("Anti-blur")                 },
        {  10, N_("Sunset")                    },
        {  11, N_("Museum")                    },
        {  12, N_("Party")                     },
        {  13, N_("Flower")                    },
        {  14, N_("Text")                      },
        {  15, N_("Natural light & flash")     },
        {  16, N_("Beach")                     },
        {  17, N_("Snow")                      },
        {  18, N_("Fireworks")                 },
        {  19, N_("Underwater")                },
        { 256, N_("Aperture-priority AE")      },
        { 512, N_("Shutter speed priority AE") },
        { 768, N_("Manual")                    }
    };

    //! Continuous, tag 0x1100
    extern const TagDetails fujiContinuous[] = {
        { 0, N_("Off")              },
        { 1, N_("On")               },
        { 2, N_("No flash & flash") }
    };

    //! FinePixColor, tag 0x1210
    extern const TagDetails fujiFinePixColor[] = {
        { 0,  N_("Standard")      },
        { 16, N_("Chrome")        },
        { 48, N_("Black & white") }
    };

    //! DynamicRange, tag 0x1400
    extern const TagDetails fujiDynamicRange[] = {
        { 1, N_("Standard") },
        { 3, N_("Wide")     }
    };

    //! FilmMode, tag 0x1401
    extern const TagDetails fujiFilmMode[] = {
        {    0, N_("F0/Standard")           },
        {  256, N_("F1/Studio portrait")    },
        {  512, N_("F2/Fujichrome")         },
        {  768, N_("F3/Studio portrait Ex") },
        { 1024, N_("F4/Velvia")             }
    };

    //! DynamicRange, tag 0x1402
    extern const TagDetails fujiDynamicRangeSetting[] = {
        {     0, N_("Auto (100-400%)")      },
        {     1, N_("Raw")                  },
        {   256, N_("Standard (100%)")      },
        {   512, N_("Wide mode 1 (230%)")   },
        {   513, N_("Wide mode 2 (400%)")   },
        { 32768, N_("Film simulation mode") }
    };

    // Fujifilm MakerNote Tag Info
    const TagInfo FujiMakerNote::tagInfo_[] = {
        TagInfo(0x0000, "Version", N_("Version"),
                N_("Fujifilm Makernote version"),
                fujiIfdId, makerTags, undefined, printValue),
        TagInfo(0x0010, "SerialNumber", N_("Serial Number"),
                N_("This number is unique, and contains the date of manufacture, "
                   "but is not the same as the number printed on the camera body."),
                fujiIfdId, makerTags, asciiString, printValue),
        TagInfo(0x1000, "Quality", N_("Quality"),
                N_("Image quality setting"),
                fujiIfdId, makerTags, asciiString, printValue),
        TagInfo(0x1001, N_("Sharpness"), N_("Sharpness"),
                N_("Sharpness setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiSharpness)),
        TagInfo(0x1002, "WhiteBalance", N_("White Balance"),
                N_("White balance setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiWhiteBalance)),
        TagInfo(0x1003, "Color", N_("Color"),
                N_("Chroma saturation setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiColor)),
        TagInfo(0x1004, "Tone", N_("Tone"),
                N_("Contrast setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiTone)),
        TagInfo(0x1010, "FlashMode", N_("Flash Mode"),
                N_("Flash firing mode setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiFlashMode)),
        TagInfo(0x1011, "FlashStrength", N_("Flash Strength"),
                N_("Flash firing strength compensation setting"),
                fujiIfdId, makerTags, signedRational, printValue),
        TagInfo(0x1020, "Macro", N_("Macro"),
                N_("Macro mode setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiOffOn)),
        TagInfo(0x1021, "FocusMode", N_("Focus Mode"),
                N_("Focusing mode setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiFocusMode)),
        TagInfo(0x1022, "0x1022", "0x1022",
                N_("Unknown"),
                fujiIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x1030, "SlowSync", N_("Slow Sync"),
                N_("Slow synchro mode setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiOffOn)),
        TagInfo(0x1031, "PictureMode", N_("Picture Mode"),
                N_("Picture mode setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiPictureMode)),
        TagInfo(0x1032, "0x1032", "0x1032",
                N_("Unknown"),
                fujiIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x1100, "Continuous", N_("Continuous"),
                N_("Continuous shooting or auto bracketing setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiContinuous)),
        TagInfo(0x1101, "SequenceNumber", N_("Sequence Number"),
                N_("Sequence number"),
                fujiIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x1200, "0x1200", "0x1200",
                N_("Unknown"),
                fujiIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x1210, "FinePixColor", N_("FinePix Color"),
                N_("Fuji FinePix color setting"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiFinePixColor)),
        TagInfo(0x1300, "BlurWarning", N_("Blur Warning"),
                N_("Blur warning status"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiOffOn)),
        TagInfo(0x1301, "FocusWarning", N_("Focus Warning"),
                N_("Auto Focus warning status"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiOffOn)),
        TagInfo(0x1302, "ExposureWarning", N_("Exposure Warning"),
                N_("Auto exposure warning status"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiOffOn)),
        TagInfo(0x1400, "DynamicRange", N_("Dynamic Range"),
                N_("Dynamic range"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiDynamicRange)),
        TagInfo(0x1401, "FilmMode", N_("Film Mode"),
                N_("Film mode"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiFilmMode)),
        TagInfo(0x1402, "DynamicRangeSetting", N_("Dynamic Range Setting"),
                N_("Dynamic range settings"),
                fujiIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(fujiDynamicRangeSetting)),
        TagInfo(0x1403, "DevelopmentDynamicRange", N_("Development Dynamic Range"),
                N_("Development dynamic range"),
                fujiIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x1404, "MinFocalLength", N_("Minimum Focal Length"),
                N_("Minimum focal length"),
                fujiIfdId, makerTags, unsignedRational, printValue),
        TagInfo(0x1405, "MaxFocalLength", N_("Maximum Focal Length"),
                N_("Maximum focal length"),
                fujiIfdId, makerTags, unsignedRational, printValue),
        TagInfo(0x1406, "MaxApertureAtMinFocal", N_("Maximum Aperture at Mininimum Focal"),
                N_("Maximum aperture at mininimum focal"),
                fujiIfdId, makerTags, unsignedRational, printValue),
        TagInfo(0x1407, "MaxApertureAtMaxFocal", N_("Maximum Aperture at Maxinimum Focal"),
                N_("Maximum aperture at maxinimum focal"),
                fujiIfdId, makerTags, unsignedRational, printValue),
        TagInfo(0x8000, "FileSource", N_("File Source"),
                N_("File source"),
                fujiIfdId, makerTags, asciiString, printValue),
        TagInfo(0x8002, "OrderNumber", N_("Order Number"),
                N_("Order number"),
                fujiIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x8003, "FrameNumber", N_("Frame Number"),
                N_("Frame number"),
                fujiIfdId, makerTags, unsignedShort, printValue),

        // End of list marker
        TagInfo(0xffff, "(UnknownFujiMakerNoteTag)", "(UnknownFujiMakerNoteTag)",
                N_("Unknown FujiMakerNote tag"),
                fujiIfdId, makerTags, invalidTypeId, printValue)
    };

    const TagInfo* FujiMakerNote::tagList()
    {
        return tagInfo_;
    }

    FujiMakerNote::FujiMakerNote(bool alloc)
        : IfdMakerNote(fujiIfdId, alloc)
    {
        byteOrder_ = littleEndian;
        absShift_ = false;
        byte buf[] = {
            'F', 'U', 'J', 'I', 'F', 'I', 'L', 'M', 0x0c, 0x00, 0x00, 0x00
        };
        readHeader(buf, 12, byteOrder_);
    }

    FujiMakerNote::FujiMakerNote(const FujiMakerNote& rhs)
        : IfdMakerNote(rhs)
    {
    }

    int FujiMakerNote::readHeader(const byte* buf,
                                  long len,
                                  ByteOrder /*byteOrder*/)
    {
        if (len < 12) return 1;

        header_.alloc(12);
        std::memcpy(header_.pData_, buf, header_.size_);
        // Read offset to the IFD relative to the start of the makernote
        // from the header. Note that we ignore the byteOrder paramter
        start_ = getUShort(header_.pData_ + 8, byteOrder_);
        return 0;
    }

    int FujiMakerNote::checkHeader() const
    {
        int rc = 0;
        // Check the FUJIFILM prefix
        if (   header_.size_ < 12
            || std::string(reinterpret_cast<char*>(header_.pData_), 8)
                    != std::string("FUJIFILM", 8)) {
            rc = 2;
        }
        return rc;
    }

    FujiMakerNote::AutoPtr FujiMakerNote::create(bool alloc) const
    {
        return AutoPtr(create_(alloc));
    }

    FujiMakerNote* FujiMakerNote::create_(bool alloc) const
    {
        AutoPtr makerNote(new FujiMakerNote(alloc));
        assert(makerNote.get() != 0);
        makerNote->readHeader(header_.pData_, header_.size_, byteOrder_);
        return makerNote.release();
    }

    FujiMakerNote::AutoPtr FujiMakerNote::clone() const
    {
        return AutoPtr(clone_());
    }

    FujiMakerNote* FujiMakerNote::clone_() const
    {
        return new FujiMakerNote(*this);
    }

// *****************************************************************************
// free functions

    MakerNote::AutoPtr createFujiMakerNote(bool        alloc,
                                           const byte* /*buf*/,
                                           long        /*len*/,
                                           ByteOrder   /*byteOrder*/,
                                           long        /*offset*/)
    {
        return MakerNote::AutoPtr(new FujiMakerNote(alloc));
    }

}                                       // namespace Exiv2
