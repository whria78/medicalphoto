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
  File:      minoltamn.cpp
  Version:   $Rev: 1473 $
  Author(s): Gilles Caulier (cgilles) <caulier dot gilles at gmail dot com>
             Andreas Huggel (ahu) <ahuggel@gmx.net>
  History:   06-May-06, gc: submitted
  Credits:   See header file.
 */

// *****************************************************************************
#include "rcsid.hpp"
EXIV2_RCSID("@(#) $Id: minoltamn.cpp 1473 2008-06-03 02:15:04Z ahuggel $")

// *****************************************************************************
// included header files
#include "types.hpp"
#include "minoltamn.hpp"
#include "makernote.hpp"
#include "value.hpp"
#include "tags.hpp"
#include "i18n.h"                // NLS support.

#include <string>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstring>

// *****************************************************************************
// class member definitions
namespace Exiv2 {

    // -- Standard Minolta Makernotes tags ---------------------------------------------------------------

    //! Lookup table to translate Minolta color mode values to readable labels
    extern const TagDetails minoltaColorMode[] = {
        { 0,  N_("Natural Color")  },
        { 1,  N_("Black & White")  },
        { 2,  N_("Vivid Color")    },
        { 3,  N_("Solarization")   },
        { 4,  N_("AdobeRGB")       },
        { 5,  N_("Sepia")          },
        { 9,  N_("Natural")        },
        { 12, N_("Portrait")       },
        { 13, N_("Natural sRGB")   },
        { 14, N_("Natural+ sRGB")  },
        { 15, N_("Landscape")      },
        { 16, N_("Evening")        },	
        { 17, N_("Night Scene")    },
        { 18, N_("Night Portrait") }
    };

    //! Lookup table to translate Minolta image quality values to readable labels
    extern const TagDetails minoltaImageQuality[] = {
        { 0, N_("Raw")        },
        { 1, N_("Super Fine") },
        { 2, N_("Fine")       },
        { 3, N_("Standard")   },
        { 4, N_("Economy")    },
        { 5, N_("Extra Fine") }
    };

    //! Lookup table to translate Minolta zone matching values
    extern const TagDetails minoltaZoneMatching[] = {
        { 0, N_("ISO Setting Used") },
        { 1, N_("High Key")         },
        { 2, N_("Low Key")          }
    };

    //! Lookup table to translate Minolta image stabilization values
    extern const TagDetails minoltaImageStabilization[] = {
        { 1, N_("Off") },
        { 5, N_("On")  }
    };

    //! Lookup table to translate Minolta Lens id values to readable labels
    /* NOTE:
       - duplicate tags value are:
       0/25520, 4/25920, 13/25610, 19/25910, 22/26050/26070,
       25500/25501/26130, 25540/25541/25850, 25580/25581, 2564025641,
       25720/25721, 25790/25791, 25960/25961, 25980/25981, 26150/26151
       - No need to i18n these string.
    */
    extern const TagDetails minoltaLensID[] = {
        { 0,     "AF28-85mm F3.5-4.5"                                                         },
        { 1,     "AF80-200mm F2.8G"                                                           },
        { 2,     "AF28-70mm F2.8G"                                                            },
        { 3,     "AF28-80mm F4-5.6"                                                           },
        { 4,     "AF85mm F1.4G"                                                               },
        { 5,     "AF35-70mm F3.5-4.5"                                                         },
        { 6,     "AF24-85mm F3.5-4.5"                                                         },
        { 7,     "AF100-300mm F4.5-5.6(D) APO | AF100-400mm F4.5-6.7(D)"                      },
        { 8,     "AF70-210mm F4.5-5.6"                                                        },
        { 9,     "AF50mm F3.5 Macro"                                                          },
        { 10,    "AF28-105mm F3.5-4.5"                                                        },
        { 11,    "AF300mm F4G APO"                                                            },
        { 12,    "AF100mm F2.8 Soft Focus"                                                    },
        { 13,    "AF75-300mm F4.5-5.6"                                                        },
        { 14,    "AF100-400mm F4.5-6.7 APO"                                                   },
        { 15,    "AF400mm F4.5G APO"                                                          },
        { 16,    "AF17-35mm F3.5G"                                                            },
        { 17,    "AF20-35mm F3.5-4.5"                                                         },
        { 18,    "AF28-80mm F3.5-5.6"                                                         },
        { 19,    "AF35mm F1.4G"                                                               },
        { 20,    "STF135mm F2.8[T4.5]"                                                        },
        { 22,    "AF35-80mm F4-5.6"                                                           },
        { 23,    "AF200mm F4G APO Macro"                                                      },
        { 24,    "AF24-105mm F3.5-4.5(D) | SIGMA 18-50mm F2.8 | Sigma DC 18-125mm F4-5,6 D"   },
        { 25,    "AF100-300mm F4.5-5.6 APO(D) | SIGMA 30mm F1.4"                              },
        { 27,    "AF85mm F1.4G(D)"                                                            },
        { 28,    "AF100mm F2.8 Macro(D)"                                                      },
        { 29,    "AF75-300mm F4.5-5.6(D)"                                                     },
        { 30,    "AF28-80mm F3.5-5.6(D)"                                                      },
        { 31,    "AF50mm F2.8 Macro(D) | AF50mm F3.5 Macro"                                   },
        { 32,    "AF100-400mm F4.5-6.7(D) x1.5 | AF300mm F2.8G APO(D) SSM"                    },
        { 33,    "AF70-200mm F2.8G APO(D) SSM"                                                },
        { 35,    "AF85mm F1.4G(D) Limited"                                                    },
        { 36,    "AF28-100mm F3.5-5.6(D)"                                                     },
        { 38,    "AF17-35mm F2.8-4(D)"                                                        },
        { 39,    "AF28-75mm F2.8(D)"                                                          },
        { 40,    "AFDT18-70mm F3.5-5.6(D)"                                                    },
        { 41,    "AFDT11-18mm F4.5-5.6(D)"                                                    },
        { 42,    "AFDT18-200mm F3.5-6.3(D)"                                                   },
        { 45,    "CZ Planar T* AF85mm F1.4"                                                   },
        { 46,    "CZ Vario-Sonnar T* AFDT16-80mm F3.5-4.5"                                    },
        { 47,    "CZ Sonnar T* 135mm F1.8"                                                    },
        { 128,   "TAMRON 18-200, 28-300 | 80-300mm F3.5-6.3"                                  },
        { 193,   "AF 1.4x APO II"                                                             },
        { 25500, "AF50mm F1.7"                                                                },
        { 25501, "AF50mm F1.7"                                                                },
        { 25510, "AF35-70mm F1.4"                                                             },
        { 25511, "AF35-70mm F4"                                                               },
        { 25520, "AF28-85mm F3.5-4.5"                                                         },
        { 25521, "TOKINA 19-35mm F3.5-4.5 | TOKINA 28-70mm F2.8 AT-X"                         },
        { 25530, "AF28-135mm F4-4.5"                                                          },
        { 25531, "AF28-135mm F4-4.5"                                                          },
        { 25540, "AF35-105mm F3.5-4.5"                                                        },
        { 25541, "AF35-105mm F3.5-4.5"                                                        },
        { 25550, "AF70-210mm F4"                                                              },
        { 25551, "AF70-210mm F4 Macro | SIGMA 70-210mm F4-5.6 APO"                            },
        { 25560, "AF135mm F2.8"                                                               },
        { 25561, "AF135mm F2.8"                                                               },
        { 25570, "AF28mm F2.8"                                                                },
        { 25571, "AF28mm F2.8"                                                                },
        { 25580, "AF24-50mm F4"                                                               },
        { 25581, "AF24-50mm F4"                                                               },
        { 25600, "AF100-200mm F4.5"                                                           },
        { 25601, "AF100-200mm F4.5"                                                           },
        { 25610, "AF75-300mm F4.5-5.6"                                                        },
        { 25611, "SIGMA 70-300mm F4-5.6 | SIGMA 300mm F4 APO Macro"                           },
        { 25620, "AF50mm F1.4"                                                                },
        { 25621, "AF50mm F1.4 NEW"                                                            },
        { 25630, "AF300mm F2.8G APO"                                                          },
        { 25631, "AF300mm F2.8G"                                                              },
        { 25640, "AF50mm F2.8 Macro"                                                          },
        { 25641, "AF50mm F2.8 Macro"                                                          },
        { 25650, "AF600mm F4 APO"                                                             },
        { 25660, "AF24mm F2.8"                                                                },
        { 25661, "AF24mm F2.8 | SIGMA 17-35mm F2.8-4.0 EX-D"                                  },
        { 25720, "AF500mm F8 Reflex"                                                          },
        { 25721, "AF500mm F8 Reflex"                                                          },
        { 25780, "AF16mm F2.8 Fisheye"                                                        },
        { 25781, "AF16mm F2.8 Fisheye | SIGMA 8mm F4 Fisheye"                                 },
        { 25790, "AF20mm F2.8"                                                                },
        { 25791, "AF20mm F2.8"                                                                },
        { 25810, "AF100mm F2.8 Macro"                                                         },
        { 25811, "AF100mm F2.8 Macro(D) | TAMRON 90mm F2.8 Macro | SIGMA 180mm F5.6 Macro"    },
        { 25850, "AF35-105mm F3.5-4.5"                                                        },
        { 25858, "TAMRON 24-135mm F3.5-5.6"                                                   },
        { 25880, "AF70-210mm F3.5-4.5"                                                        },
        { 25890, "AF80-200mm F2.8 APO"                                                        },
        { 25891, "TOKINA 80-200mm F2.8"                                                       },
        { 25910, "AF35mm F1.4G"                                                               },
        { 25911, "AF35mm F1.4G"                                                               },
        { 25920, "AF85mm F1.4G"                                                               },
        { 25921, "AF85mm F1.4G(D)"                                                            },
        { 25930, "AF200mm F2.8 APO"                                                           },
        { 25931, "AF200mm F2.8G"                                                              },
        { 25940, "AF 3X-1X F1.7-2.8 Macro"                                                    },
        { 25960, "AF28mm F2"                                                                  },
        { 25961, "AF28mm F2"                                                                  },
        { 25970, "AF35mm F2"                                                                  },
        { 25971, "AF35mm F2"                                                                  },
        { 25980, "AF100mm F2"                                                                 },
        { 25981, "AF100mm F2"                                                                 },
        { 26040, "AF80-200mm F4.5-5.6"                                                        },
        { 26050, "AF35-80mm F4-5.6"                                                           },
        { 26060, "AF100-300mm F4.5-5.6"                                                       },
        { 26061, "AF100-300mm F4.5-5.6(D) | SIGMA 105mm F2.8 Macro EX-DG"                     },
        { 26070, "AF35-80mm F4-5.6"                                                           },
        { 26071, "AF35-80mm F4-5.6"                                                           },
        { 26080, "AF300mm F2.8G APO High Speed"                                               },
        { 26081, "AF300mm F2.8G"                                                              },
        { 26090, "AF600mm F4G APO High Speed"                                                 },
        { 26120, "AF200mm F2.8G APO High Speed"                                               },
        { 26121, "AF200mm F2.8G(D)"                                                           },
        { 26130, "AF50mm F1.7"                                                                },
        { 26131, "AF50mm F1.7"                                                                },
        { 26150, "AF28-105mm F3.5-4.5 Xi"                                                     },
        { 26151, "AF28-105mm F3.5-4.5 Xi"                                                     },
        { 26160, "AF35-200mm F4.5-5.6 Xi"                                                     },
        { 26161, "AF35-200mm F4.5-5.6 Xi"                                                     },
        { 26180, "AF28-80mm F4-5.6 Xi"                                                        },
        { 26190, "AF80-200mm F4.5-5.6 Xi"                                                     },
        { 26210, "AF100-300mm F4.5-5.6 Xi"                                                    },
        { 26240, "AF35-80mm F4-5.6 Power"                                                     },
        { 26241, "AF35-80mm F4-5.6"                                                           },
        { 45741, "AF200mm F2.8G x2 | TOKINA 300mm F2.8 x2"                                    }
    };

    // Minolta Tag Info
    const TagInfo MinoltaMakerNote::tagInfo_[] = {
        TagInfo(0x0000, "Version", N_("Makernote Version"),
                N_("String 'MLT0' (not null terminated)"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0001, "CameraSettingsStdOld", N_("Camera Settings (Std Old)"),
                N_("Standard Camera settings (Old Camera models like D5, D7, S304, and S404)"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0003, "CameraSettingsStdNew", N_("Camera Settings (Std New)"),
                N_("Standard Camera settings (New Camera Models like D7u, D7i, and D7hi)"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0004, "CameraSettings7D", N_("Camera Settings (7D)"),
                N_("Camera Settings (for Dynax 7D model)"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0018, "ImageStabilizationData", N_("Image Stabilization Data"),
                N_("Image stabilization data"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0040, "CompressedImageSize", N_("Compressed Image Size"),
                N_("Compressed image size"),
                minoltaIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0081, "Thumbnail", N_("Thumbnail"),
                N_("Jpeg thumbnail 640x480 pixels"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0088, "ThumbnailOffset", N_("Thumbnail Offset"),
                N_("Offset of the thumbnail"),
                minoltaIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0089, "ThumbnailLength", N_("Thumbnail Length"),
                N_("Size of the thumbnail"),
                minoltaIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0101, "ColorMode", N_("Color Mode"),
                N_("Color mode"),
                minoltaIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaColorMode)),
        TagInfo(0x0102, "Quality", N_("Image Quality"),
                N_("Image quality"),
                minoltaIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaImageQuality)),

        // TODO: Tag 0x0103 : quality or image size (see ExifTool doc).

        TagInfo(0x0107, "ImageStabilization", N_("Image Stabilization"),
                N_("Image stabilization"),
                minoltaIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaImageStabilization)),
        TagInfo(0x010a, "ZoneMatching", N_("Zone Matching"),
                N_("Zone matching"),
                minoltaIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaZoneMatching)),
        TagInfo(0x010b, "ColorTemperature", N_("Color Temperature"),
                N_("Color temperature"),
                minoltaIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x010c, "LensID", N_("Lens ID"),
                N_("Lens identifier"),
                minoltaIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaLensID)),
        TagInfo(0x0114, "CameraSettings5D", N_("Camera Settings (5D)"),
                N_("Camera Settings (for Dynax 5D model)"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0e00, "PrintIM", N_("Print IM"),
                N_("PrintIM information"),
                minoltaIfdId, makerTags, undefined, printValue),
        TagInfo(0x0f00, "CameraSettingsZ1", N_("Camera Settings (Z1)"),
                N_("Camera Settings (for Z1, DImage X, and F100 models)"),
                minoltaIfdId, makerTags, undefined, printValue),
        // End of list marker

        TagInfo(0xffff, "(UnknownMinoltaMakerNoteTag)", "(UnknownMinoltaMakerNoteTag)",
                N_("Unknown Minolta MakerNote tag"),
                minoltaIfdId, makerTags, invalidTypeId, printValue)
    };

    const TagInfo* MinoltaMakerNote::tagList()
    {
        return tagInfo_;
    }

    // -- Standard Minolta camera settings ---------------------------------------------------------------

    //! Lookup table to translate Minolta Std camera settings exposure mode values to readable labels
    extern const TagDetails minoltaExposureModeStd[] = {
        { 0, N_("Program")           },
        { 1, N_("Aperture priority") },
        { 2, N_("Shutter priority")  },
        { 3, N_("Manual")            }
    };

    //! Lookup table to translate Minolta Std camera settings exposure mode values to readable labels
    extern const TagDetails minoltaFlashModeStd[] = {
        { 0, N_("Fill flash")        },
        { 1, N_("Red-eye reduction") },
        { 2, N_("Rear flash sync")   },
        { 3, N_("Wireless")          }
    };

    //! Lookup table to translate Minolta Std camera settings white balance values to readable labels
    extern const TagDetails minoltaWhiteBalanceStd[] = {
        { 0,  N_("Auto")          },
        { 1,  N_("Daylight")      },
        { 2,  N_("Cloudy")        },
        { 3,  N_("Tungsten")      },
        { 5,  N_("Custom")        },
        { 7,  N_("Fluorescent")   },
        { 8,  N_("Fluorescent 2") },
        { 11, N_("Custom 2")      },
        { 12, N_("Custom 3")      }
    };

    //! Lookup table to translate Minolta Std camera settings image size values to readable labels
    extern const TagDetails minoltaImageSizeStd[] = {
        { 0, N_("Full size") },
        { 1, "1600x1200"     },
        { 2, "1280x960"      },
        { 3, "640x480"       },
        { 6, "2080x1560"     },
        { 7, "2560x1920"     },
        { 8, "3264x2176"     }
    };

    //! Lookup table to translate Minolta Std camera settings image quality values to readable labels
    extern const TagDetails minoltaImageQualityStd[] = {
        { 0, N_("Raw")        },
        { 1, N_("Super fine") },
        { 2, N_("Fine")       },
        { 3, N_("Standard")   },
        { 4, N_("Economy")    },
        { 5, N_("Extra fine") }
    };

    //! Lookup table to translate Minolta Std camera settings drive mode values to readable labels
    extern const TagDetails minoltaDriveModeStd[] = {
        { 0, N_("Single")         },
        { 1, N_("Continuous")     },
        { 2, N_("Self-timer")     },
        { 4, N_("Bracketing")     },
        { 5, N_("Interval")       },
        { 6, N_("UHS continuous") },
        { 7, N_("HS continuous")  }
    };

    //! Lookup table to translate Minolta Std camera settings metering mode values to readable labels
    extern const TagDetails minoltaMeteringModeStd[] = {
        { 0, N_("Multi-segment")   },
        { 1, N_("Center weighted") },
        { 2, N_("Spot")            }
    };

    //! Lookup table to translate Minolta Std camera settings macro mode values to readable labels
    extern const TagDetails minoltaMacroModeStd[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Lookup table to translate Minolta Std camera settings digital zoom values to readable labels
    extern const TagDetails minoltaDigitalZoomStd[] = {
        { 0, N_("Off")                      },
        { 1, N_("Electronic magnification") },
        { 2, "2x"                           }
    };

    //! Lookup table to translate Minolta Std camera bracket step mode values to readable labels
    extern const TagDetails minoltaBracketStepStd[] = {
        { 0, "1/3 EV" },
        { 1, "2/3 EV" },
        { 2, "1 EV"   }
    };

    //! Lookup table to translate Minolta Std camera settings AF points values to readable labels
    extern const TagDetails minoltaAFPointsStd[] = {
        { 0, N_("Center")       },
        { 1, N_("Top")          },
        { 2, N_("Top-right")    },
        { 3, N_("Right")        },
        { 4, N_("Bottom-right") },
        { 5, N_("Bottom")       },
        { 6, N_("Bottom-left")  },
        { 7, N_("Left")         },
        { 8, N_("Top-left")     }
    };

    //! Lookup table to translate Minolta Std camera settings white balance values to readable labels
    extern const TagDetails minoltaFlashStd[] = {
        { 0, N_("Did not fire") },
        { 1, N_("Fired")        }
    };

    //! Lookup table to translate Minolta Std camera settings file number memory values to readable labels
    extern const TagDetails minoltaFileNumberMemoryStd[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Lookup table to translate Minolta Std camera settings sharpness values to readable labels
    extern const TagDetails minoltaSharpnessStd[] = {
        { 0, N_("Hard")   },
        { 1, N_("Normal") },
        { 2, N_("Soft")   }
    };

    //! Lookup table to translate Minolta Std camera settings subject program values to readable labels
    extern const TagDetails minoltaSubjectProgramStd[] = {
        { 0, N_("None")           },
        { 1, N_("Portrait")       },
        { 2, N_("Text")           },
        { 3, N_("Night portrait") },
        { 4, N_("Sunset")         },
        { 5, N_("Sports action")  }
    };

    //! Lookup table to translate Minolta Std camera settings ISO settings values to readable labels
    extern const TagDetails minoltaISOSettingStd[] = {
        { 0, "100"      },
        { 1, "200"      },
        { 2, "400"      },
        { 3, "800"      },
        { 4, N_("Auto") },
        { 5, "64"       }
    };

    //! Lookup table to translate Minolta Std camera settings model values to readable labels
    extern const TagDetails minoltaModelStd[] = {
        { 0, "DiMAGE 7 | X1 | X21 | X31" },
        { 1, "DiMAGE 5"                  },
        { 2, "DiMAGE S304"               },
        { 3, "DiMAGE S404"               },
        { 4, "DiMAGE 7i"                 },
        { 5, "DiMAGE 7Hi"                },
        { 6, "DiMAGE A1"                 },
        { 7, "DiMAGE A2 | S414"          }
    };

    //! Lookup table to translate Minolta Std camera settings interval mode values to readable labels
    extern const TagDetails minoltaIntervalModeStd[] = {
        { 0, N_("Still image")      },
        { 1, N_("Time-lapse movie") }
    };

    //! Lookup table to translate Minolta Std camera settings folder name values to readable labels
    extern const TagDetails minoltaFolderNameStd[] = {
        { 0, N_("Standard form") },
        { 1, N_("Data form")     }
    };

    //! Lookup table to translate Minolta Std camera settings color mode values to readable labels
    extern const TagDetails minoltaColorModeStd[] = {
        { 0, N_("Natural color")   },
        { 1, N_("Black and white") },
        { 2, N_("Vivid color")     },
        { 3, N_("Solarization")    },
        { 4, N_("Adobe RGB")       }
    };

    //! Lookup table to translate Minolta Std camera settings internal flash values to readable labels
    extern const TagDetails minoltaInternalFlashStd[] = {
        { 0, N_("Did not fire") },
        { 1, N_("Fired")        }
    };

    //! Lookup table to translate Minolta Std camera settings wide focus zone values to readable labels
    extern const TagDetails minoltaWideFocusZoneStd[] = {
        { 0, N_("No zone")                              },
        { 1, N_("Center zone (horizontal orientation)") },
        { 1, N_("Center zone (vertical orientation)")   },
        { 1, N_("Left zone")                            },
        { 4, N_("Right zone")                           }
    };

    //! Lookup table to translate Minolta Std camera settings focus mode values to readable labels
    extern const TagDetails minoltaFocusModeStd[] = {
        { 0, N_("Auto focus")   },
        { 1, N_("Manual focus") }
    };

    //! Lookup table to translate Minolta Std camera settings focus area values to readable labels
    extern const TagDetails minoltaFocusAreaStd[] = {
        { 0, N_("Wide focus (normal)") },
        { 1, N_("Spot focus")          }
    };

    //! Lookup table to translate Minolta Std camera settings DEC switch position values to readable labels
    extern const TagDetails minoltaDECPositionStd[] = {
        { 0, N_("Exposure")   },
        { 1, N_("Contrast")   },
        { 2, N_("Saturation") },
        { 3, N_("Filter")     }
    };

    //! Lookup table to translate Minolta Std camera settings color profile values to readable labels
    extern const TagDetails minoltaColorProfileStd[] = {
        { 0, N_("Not embedded") },
        { 1, N_("Embedded")     }
    };

    //! Lookup table to translate Minolta Std camera settings data Imprint values to readable labels
    extern const TagDetails minoltaDataImprintStd[] = {
        { 0, N_("None")       },
        { 1, "YYYY/MM/DD"     },
        { 2, "MM/DD/HH:MM"    },
        { 3, N_("Text")       },
        { 4, N_("Text + ID#") }
    };

    //! Lookup table to translate Minolta Std camera settings flash metering values to readable labels
    extern const TagDetails minoltaFlashMeteringStd[] = {
        { 0, N_("ADI (Advanced Distance Integration)") },
        { 1, N_("Pre-flash TTl")                       },
        { 2, N_("Manual flash control")                }
    };

    std::ostream& MinoltaMakerNote::printMinoltaExposureSpeedStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << (value.toLong()/8)-1;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaExposureTimeStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << (value.toLong()/8)-6;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaFNumberStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << (value.toLong()/8)-1;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaExposureCompensationStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << value.toLong()/256;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaFocalLengthStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << (value.toLong()/3)-2;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaDateStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << value.toLong() / 65536 << ":" << std::right << std::setw(2) << std::setfill('0')
           << (value.toLong() - value.toLong() / 65536 * 65536) / 256 << ":"
           << std::right << std::setw(2) << std::setfill('0') << value.toLong() % 256;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaTimeStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << std::right << std::setw(2) << std::setfill('0') << value.toLong() / 65536
           << ":" << std::right << std::setw(2) << std::setfill('0')
           << (value.toLong() - value.toLong() / 65536 * 65536) / 256 << ":"
           << std::right << std::setw(2) << std::setfill('0') << value.toLong() % 256;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaFlashExposureCompStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << (value.toLong()-6)/3;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaWhiteBalanceStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << value.toLong()/256;
        return os;
    }

    std::ostream& MinoltaMakerNote::printMinoltaBrightnessStd(std::ostream& os, const Value& value)
    {
        // From the PHP JPEG Metadata Toolkit
        os << (value.toLong()/8)-6;
        return os;
    }

    // Minolta Standard Camera Settings Tag Info (Old and New)
    const TagInfo MinoltaMakerNote::tagInfoCsStd_[] = {
        TagInfo(0x0001, "ExposureMode", N_("Exposure Mode"),
                N_("Exposure mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaExposureModeStd)),
        TagInfo(0x0002, "FlashMode", N_("Flash Mode"),
                N_("Flash mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFlashModeStd)),
        TagInfo(0x0003, "WhiteBalance", N_("White Balance"),
                N_("White balance"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaWhiteBalanceStd)),
        TagInfo(0x0004, "ImageSize", N_("Image Size"),
                N_("Image size"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaImageSizeStd)),
        TagInfo(0x0005, "Quality", N_("Image Quality"),
                N_("Image quality"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaImageQualityStd)),
        TagInfo(0x0006, "DriveMode", N_("Drive Mode"),
                N_("Drive mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaDriveModeStd)),
        TagInfo(0x0007, "MeteringMode", N_("Metering Mode"),
                N_("Metering mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaMeteringModeStd)),
        TagInfo(0x0008, "ExposureSpeed", N_("Exposure Speed"),
                N_("Exposure speed"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaExposureSpeedStd),
        TagInfo(0x0009, "ExposureTime", N_("Exposure Time"),
                N_("Exposure time"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaExposureTimeStd),
        TagInfo(0x000A, "FNumber", N_("FNumber"),
                N_("The F-Number"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaFNumberStd),
        TagInfo(0x000B, "MacroMode", N_("Macro Mode"),
                N_("Macro mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaMacroModeStd)),
        TagInfo(0x000C, "DigitalZoom", N_("Digital Zoom"),
                N_("Digital zoom"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaDigitalZoomStd)),
        TagInfo(0x000D, "ExposureCompensation", N_("Exposure Compensation"),
                N_("Exposure compensation"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaExposureCompensationStd),
        TagInfo(0x000E, "BracketStep", N_("Bracket Step"),
                N_("Bracket step"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaBracketStepStd)),
        TagInfo(0x0010, "IntervalLength", N_("Interval Length"),
                N_("Interval length"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0011, "IntervalNumber", N_("Interval Number"),
                N_("Interval number"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0012, "FocalLength", N_("Focal Length"),
                N_("Focal length"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaFocalLengthStd),
        TagInfo(0x0013, "FocusDistance", N_("Focus Distance"),
                N_("Focus distance"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0014, "Flash", N_("Flash"),
                N_("Flash mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFlashStd)),
        TagInfo(0x0015, "MinoltaDate", N_("Minolta Date"),
                N_("Minolta date"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaDateStd),
        TagInfo(0x0016, "MinoltaTime", N_("Minolta Time"),
                N_("Minolta time"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaTimeStd),
        TagInfo(0x0017, "MaxAperture", N_("Max Aperture"),
                N_("Max aperture"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x001A, "FileNumberMemory", N_("File Number Memory"),
                N_("File number memory"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFileNumberMemoryStd)),
        TagInfo(0x001B, "ImageNumber", N_("Image Number"),
                N_("Image number"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x001C, "ColorBalanceRed", N_("Color Balance Red"),
                N_("Color balance red"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaWhiteBalanceStd),
        TagInfo(0x001D, "ColorBalanceGreen", N_("Color Balance Green"),
                N_("Color balance green"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaWhiteBalanceStd),
        TagInfo(0x001E, "ColorBalanceBlue", N_("Color Balance Blue"),
                N_("Color balance blue"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaWhiteBalanceStd),
        TagInfo(0x001F, "Saturation", N_("Saturation"),
                N_("Saturation"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0020, "Contrast", N_("Contrast"),
                N_("Contrast"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x0021, "Sharpness", N_("Sharpness"),
                N_("Sharpness"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaSharpnessStd)),
        TagInfo(0x0022, "SubjectProgram", N_("Subject Program"),
                N_("Subject program"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaSubjectProgramStd)),
        TagInfo(0x0023, "FlashExposureComp", N_("Flash Exposure Compensation"),
                N_("Flash exposure compensation in EV"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaFlashExposureCompStd),
        TagInfo(0x0024, "ISOSpeed", N_("ISO Speed Mode"),
                N_("ISO speed setting"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaISOSettingStd)),
        TagInfo(0x0025, "MinoltaModel", N_("Minolta Model"),
                N_("Minolta model"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaModelStd)),
        TagInfo(0x0026, "IntervalMode", N_("Interval Mode"),
                N_("Interval mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaIntervalModeStd)),
        TagInfo(0x0027, "FolderName", N_("Folder Name"),
                N_("Folder name"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFolderNameStd)),
        TagInfo(0x0028, "ColorMode", N_("ColorMode"),
                N_("ColorMode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaColorModeStd)),
        TagInfo(0x0029, "ColorFilter", N_("Color Filter"),
                N_("Color filter"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x002A, "BWFilter", N_("Black and White Filter"),
                N_("Black and white filter"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x002B, "InternalFlash", N_("Internal Flash"),
                N_("Internal flash"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaInternalFlashStd)),
        TagInfo(0x002C, "Brightness", N_("Brightness"),
                N_("Brightness"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printMinoltaBrightnessStd),
        TagInfo(0x002D, "SpotFocusPointX", N_("Spot Focus Point X"),
                N_("Spot focus point X"),
        minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x002E, "SpotFocusPointY", N_("Spot Focus Point Y"),
                N_("Spot focus point Y"),
                minoltaCsNewIfdId, makerTags, unsignedLong, printValue),
        TagInfo(0x002F, "WideFocusZone", N_("Wide Focus Zone"),
                N_("Wide focus zone"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaWideFocusZoneStd)),
        TagInfo(0x0030, "FocusMode", N_("Focus Mode"),
                N_("Focus mode"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFocusModeStd)),
        TagInfo(0x0031, "FocusArea", N_("Focus area"),
                N_("Focus area"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFocusAreaStd)),
        TagInfo(0x0032, "DECPosition", N_("DEC Switch Position"),
                N_("DEC switch position"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaDECPositionStd)),
        TagInfo(0x0033, "ColorProfile", N_("Color Profile"),
                N_("Color profile"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaColorProfileStd)),
        TagInfo(0x0034, "DataImprint", N_("Data Imprint"),
                N_("Data Imprint"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaDataImprintStd)),
        TagInfo(0x003F, "FlashMetering", N_("Flash Metering"),
                N_("Flash metering"),
                minoltaCsNewIfdId, makerTags, unsignedLong, EXV_PRINT_TAG(minoltaFlashMeteringStd)),

        // End of list marker
        TagInfo(0xffff, "(UnknownMinoltaCsStdTag)", "(UnknownMinoltaCsStdTag)",
                N_("Unknown Minolta Camera Settings tag"),
                minoltaCsNewIfdId, makerTags, invalidTypeId, printValue)
    };

    const TagInfo* MinoltaMakerNote::tagListCsStd()
    {
        return tagInfoCsStd_;
    }

    // -- Minolta Dynax 7D camera settings ---------------------------------------------------------------

    //! Lookup table to translate Minolta Dynax 7D camera settings exposure mode values to readable labels
    extern const TagDetails minoltaExposureMode7D[] = {
        { 0, N_("Program")           },
        { 1, N_("Aperture priority") },
        { 2, N_("Shutter priority")  },
        { 3, N_("Manual")            },
        { 4, N_("Auto")              },
        { 5, N_("Program-shift A")   },
        { 6, N_("Program-shift S")   }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings image size values to readable labels
    extern const TagDetails minoltaImageSize7D[] = {
        { 0, N_("Large")  },
        { 1, N_("Medium") },
        { 2, N_("Small")  }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings image quality values to readable labels
    extern const TagDetails minoltaImageQuality7D[] = {
        { 0,  N_("Raw")      },
        { 16, N_("Fine")     },
        { 32, N_("Normal")   },
        { 34, N_("Raw+Jpeg") },
        { 48, N_("Economy")  }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings white balance values to readable labels
    extern const TagDetails minoltaWhiteBalance7D[] = {
        { 0,   N_("Auto")        },
        { 1,   N_("Daylight")    },
        { 2,   N_("Shade")       },
        { 3,   N_("Cloudy")      },
        { 4,   N_("Tungsten")    },
        { 5,   N_("Fluorescent") },
        { 256, N_("Kelvin")      },
        { 512, N_("Manual")      }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings focus mode values to readable labels
    extern const TagDetails minoltaFocusMode7D[] = {
        { 0, N_("Single-shot AF") },
        { 1, N_("Continuous AF")  },
        { 3, N_("Automatic AF")   },
        { 4, N_("Manual")         }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings AF points values to readable labels
    extern const TagDetails minoltaAFPoints7D[] = {
        { 1,   N_("Center")       },
        { 2,   N_("Top")          },
        { 4,   N_("Top-right")    },
        { 8,   N_("Right")        },
        { 16,  N_("Bottom-right") },
        { 32,  N_("Bottom")       },
        { 64,  N_("Bottom-left")  },
        { 128, N_("Left")         },
        { 256, N_("Top-left")     }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings white balance values to readable labels
    extern const TagDetails minoltaFlash7D[] = {
        { 0, N_("Did not fire") },
        { 1, N_("Fired")        }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings ISO settings values to readable labels
    extern const TagDetails minoltaISOSetting7D[] = {
        { 0, N_("Auto") },
        { 1, "100"      },
        { 3, "200"      },
        { 4, "400"      },
        { 5, "800"      },
        { 6, "1600"     },
        { 7, "3200"     }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings color space values to readable labels
    extern const TagDetails minoltaColorSpace7D[] = {
        { 0, N_("sRGB (Natural)")  },
        { 1, N_("sRGB (Natural+)") },
        { 4, N_("Adobe RGB")       }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings rotation values to readable labels
    extern const TagDetails minoltaRotation7D[] = {
        { 72, N_("Horizontal (normal)") },
        { 76, N_("Rotate 90 CW")        },
        { 82, N_("Rotate 270 CW")       }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings noise reduction values to readable labels
    extern const TagDetails minoltaNoiseReduction7D[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings image stabilization values to readable labels
    extern const TagDetails minoltaImageStabilization7D[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Lookup table to translate Minolta Dynax 7D camera settings zone matching on values to readable labels
    extern const TagDetails minoltaZoneMatchingOn7D[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    // Minolta Dynax 7D Camera Settings Tag Info
    const TagInfo MinoltaMakerNote::tagInfoCs7D_[] = {
        TagInfo(0x0000, "ExposureMode", N_("Exposure Mode"),
                N_("Exposure mode"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaExposureMode7D)),
        TagInfo(0x0002, "ImageSize", N_("Image Size"),
                N_("Image size"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaImageSize7D)),
        TagInfo(0x0003, "Quality", N_("Image Quality"),
                N_("Image quality"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaImageQuality7D)),
        TagInfo(0x0004, "WhiteBalance", N_("White Balance"),
                N_("White balance"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaWhiteBalance7D)),
        TagInfo(0x000E, "FocusMode", N_("Focus Mode"),
                N_("Focus mode"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaFocusMode7D)),
        TagInfo(0x0010, "AFPoints", N_("AF Points"),
                N_("AF points"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaAFPoints7D)),
        TagInfo(0x0015, "Flash", N_("Flash"),
                N_("Flash"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaFlash7D)),
        TagInfo(0x0016, "FlashMode", N_("Flash Mode"),
                N_("Flash mode"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x001C, "ISOSpeed", N_("ISO Speed Mode"),
                N_("ISO speed setting"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaISOSetting7D)),
        TagInfo(0x001E, "ExposureCompensation", N_("Exposure Compensation"),
                N_("Exposure compensation"),
                minoltaCs7DIfdId, makerTags, signedShort, printValue),
        TagInfo(0x0025, "ColorSpace", N_("Color Space"),
                N_("Color space"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaColorSpace7D)),
        TagInfo(0x0026, "Sharpness", N_("Sharpness"),
                N_("Sharpness"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0027, "Contrast", N_("Contrast"),
                N_("Contrast"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0028, "Saturation", N_("Saturation"),
                N_("Saturation"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x002D, "FreeMemoryCardImages", N_("Free Memory Card Images"),
                N_("Free memory card images"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x003F, "ColorTemperature", N_("Color Temperature"),
                N_("Color temperature"),
                minoltaCs7DIfdId, makerTags, signedShort, printValue),
        TagInfo(0x0040, "Hue", N_("Hue"), N_("Hue"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0046, "Rotation", N_("Rotation"),
                N_("Rotation"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaRotation7D)),
        TagInfo(0x0047, "FNumber", N_("FNumber"),
                N_("The F-Number"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0048, "ExposureTime", N_("Exposure Time"),
                N_("Exposure time"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        // 0x004A is a dupplicate than 0x002D.
        TagInfo(0x004A, "FreeMemoryCardImages", N_("Free Memory Card Images"),
                N_("Free memory card images"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x005E, "ImageNumber", N_("Image Number"),
                N_("Image number"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0060, "NoiseReduction", N_("Noise Reduction"),
                N_("Noise reduction"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaNoiseReduction7D)),
        // 0x0062 is a dupplicate than 0x005E.
        TagInfo(0x0062, "ImageNumber", N_("Image Number"),
                N_("Image number"),
                minoltaCs7DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0071, "ImageStabilization", N_("Image Stabilization"),
                N_("Image stabilization"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaImageStabilization7D)),
        TagInfo(0x0075, "ZoneMatchingOn", N_("Zone Matching On"),
                N_("Zone matching on"),
                minoltaCs7DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaZoneMatchingOn7D)),

        // End of list marker
        TagInfo(0xffff, "(UnknownMinoltaCs7DTag)", "(UnknownMinoltaCs7DTag)",
                N_("Unknown Minolta Camera Settings 7D tag"),
                minoltaCs7DIfdId, makerTags, invalidTypeId, printValue)
    };

    const TagInfo* MinoltaMakerNote::tagListCs7D()
    {
        return tagInfoCs7D_;
    }

    // -- Minolta Dynax 5D camera settings ---------------------------------------------------------------

    //! Lookup table to translate Minolta Dynax 5D camera settings exposure mode values to readable labels
    extern const TagDetails minoltaExposureMode5D[] = {
        { 0,    N_("Program")           },
        { 1,    N_("Aperture priority") },
        { 2,    N_("Shutter priority")  },
        { 3,    N_("Manual")            },
        { 4,    N_("Auto")              },
        { 4131, N_("Connected copying") }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings image size values to readable labels
    extern const TagDetails minoltaImageSize5D[] = {
        { 0, N_("Large")  },
        { 1, N_("Medium") },
        { 2, N_("Small")  }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings image quality values to readable labels
    extern const TagDetails minoltaImageQuality5D[] = {
        { 0,  N_("Raw")      },
        { 16, N_("Fine")     },
        { 32, N_("Normal")   },
        { 34, N_("Raw+Jpeg") },
        { 48, N_("Economy")  }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings white balance values to readable labels
    extern const TagDetails minoltaWhiteBalance5D[] = {
        { 0,   N_("Auto")        },
        { 1,   N_("Daylight")    },
        { 2,   N_("Cloudy")      },
        { 3,   N_("Shade")       },
        { 4,   N_("Tungsten")    },
        { 5,   N_("Fluorescent") },
        { 6,   N_("Flash")       },
        { 256, N_("Kelvin")      },
        { 512, N_("Manual")      }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings flash labels
    extern const TagDetails minoltaFlash5D[] = {
        { 0, N_("Did not fire") },
        { 1, N_("Fired")        }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings metering mode values to readable labels
    extern const TagDetails minoltaMeteringMode5D[] = {
        { 0, N_("Multi-segment")   },
        { 1, N_("Center weighted") },
        { 2, N_("Spot")            }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings ISO settings values to readable labels
    extern const TagDetails minoltaISOSetting5D[] = {
        { 0,  N_("Auto")                     },
        { 1,  "100"                          },
        { 3,  "200"                          },
        { 4,  "400"                          },
        { 5,  "800"                          },
        { 6,  "1600"                         },
        { 7,  "3200"                         },
        { 8,  N_("200 (Zone Matching High)") },
        { 10, N_("80 (Zone Matching Low)")   }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings rotation values to readable labels
    extern const TagDetails minoltaRotation5D[] = {
        { 72, N_("Horizontal (normal)") },
        { 76, N_("Rotate 90 CW")        },
        { 82, N_("Rotate 270 CW")       }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings noise reduction values to readable labels
    extern const TagDetails minoltaNoiseReduction5D[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings image stabilization values to readable labels
    extern const TagDetails minoltaImageStabilization5D[] = {
        { 0, N_("Off") },
        { 1, N_("On")  }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings focus position values to readable labels
    extern const TagDetails minoltaFocusPosition5D[] = {
        { 0, N_("Wide")       },
        { 1, N_("Central")    },
        { 2, N_("Up")         },
        { 3, N_("Up right")   },
        { 4, N_("Right")      },
        { 5, N_("Down right") },
        { 6, N_("Down")       },
        { 7, N_("Down left")  },
        { 8, N_("Left")       },
        { 9, N_("Up left")    }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings focus area values to readable labels
    extern const TagDetails minoltaFocusArea5D[] = {
        { 0, N_("Wide")      },
        { 1, N_("Selection") },
        { 2, N_("Spot")      }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings focus mode values to readable labels
    extern const TagDetails minoltaAFMode5D[] = {
        { 0, "AF-A" },
        { 1, "AF-S" },
        { 2, "AF-D" },
        { 3, "DMF"  }
    };

    //! Lookup table to translate Minolta Dynax 5D camera settings focus mode values to readable labels
    extern const TagDetails minoltaFocusMode5D[] = {
        { 0, "AF" },
        { 1, "MF" }
    };

    //! Method to convert Minolta Dynax 5D exposure manual bias values.
    std::ostream& MinoltaMakerNote::printMinoltaExposureManualBias5D(std::ostream& os, const Value& value)
    {
        // From Xavier Raynaud: the value is converted from 0:256 to -5.33:5.33

        std::ostringstream oss;
        oss.copyfmt(os);
        os << std::fixed << std::setprecision(2)
           << (float (value.toLong()-128)/24);
        os.copyfmt(oss);
        return os;
    }

    //! Method to convert Minolta Dynax 5D exposure compensation values.
    std::ostream& MinoltaMakerNote::printMinoltaExposureCompensation5D(std::ostream& os, const Value& value)
    {
        std::ostringstream oss;
        oss.copyfmt(os);
        os << std::fixed << std::setprecision(2)
           << (float (value.toLong()-300)/100);
        os.copyfmt(oss);
        return os;
    }

    // Minolta Dynax 5D Camera Settings Tag Info
    const TagInfo MinoltaMakerNote::tagInfoCs5D_[] = {
        TagInfo(0x000A, "ExposureMode", N_("Exposure Mode"),
                N_("Exposure mode"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaExposureMode5D)),
        TagInfo(0x000C, "ImageSize", N_("Image Size"),
                N_("Image size"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaImageSize5D)),
        TagInfo(0x000D, "Quality", N_("Image Quality"),
                N_("Image quality"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaImageQuality5D)),
        TagInfo(0x000E, "WhiteBalance", N_("White Balance"),
                N_("White balance"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaWhiteBalance5D)),
        TagInfo(0x001a, "FocusPosition", N_("Focus Position"),
                N_("Focus position"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaFocusPosition5D)),
        TagInfo(0x001b, "FocusArea", N_("Focus Area"),
                N_("Focus area"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaFocusArea5D)),
        TagInfo(0x001F, "Flash", N_("Flash"),
                N_("Flash"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaFlash5D)),
        TagInfo(0x0025, "MeteringMode", N_("Metering Mode"),
                N_("Metering mode"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaMeteringMode5D)),
        TagInfo(0x0026, "ISOSpeed", N_("ISO Speed Mode"),
                N_("ISO speed setting"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaISOSetting5D)),
        TagInfo(0x0030, "Sharpness", N_("Sharpness"),
                N_("Sharpness"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0031, "Contrast", N_("Contrast"),
                N_("Contrast"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0032, "Saturation", N_("Saturation"),
                N_("Saturation"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0035, "ExposureTime", N_("Exposure Time"),
                N_("Exposure time"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0036, "FNumber", N_("FNumber"),
                N_("The F-Number"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0037, "FreeMemoryCardImages", N_("Free Memory Card Images"),
                N_("Free memory card images"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0038, "ExposureRevision", N_("Exposure Revision"),
                N_("Exposure revision"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0048, "FocusMode", N_("Focus Mode"),
                N_("Focus mode"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaFocusMode5D)),
        TagInfo(0x0049, "ColorTemperature", N_("Color Temperature"),
                N_("Color temperature"),
                minoltaCs5DIfdId, makerTags, signedShort, printValue),
        TagInfo(0x0050, "Rotation", N_("Rotation"),
                N_("Rotation"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaRotation5D)),
        TagInfo(0x0053, "ExposureCompensation", N_("Exposure Compensation"),
                N_("Exposure compensation"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printMinoltaExposureCompensation5D),
        TagInfo(0x0054, "FreeMemoryCardImages", N_("Free Memory Card Images"),
                N_("Free memory card images"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x0091, "ExposureManualBias", N_("Exposure Manual Bias"),
                N_("Exposure manual bias"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printMinoltaExposureManualBias5D),
        TagInfo(0x009e, "AFMode", N_("AF Mode"),
                N_("AF mode"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaAFMode5D)),
        TagInfo(0x00AE, "ImageNumber", N_("Image Number"),
                N_("Image number"),
                minoltaCs5DIfdId, makerTags, unsignedShort, printValue),
        TagInfo(0x00B0, "NoiseReduction", N_("Noise Reduction"),
                N_("Noise reduction"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaNoiseReduction5D)),
        TagInfo(0x00BD, "ImageStabilization", N_("Image Stabilization"),
                N_("Image stabilization"),
                minoltaCs5DIfdId, makerTags, unsignedShort, EXV_PRINT_TAG(minoltaImageStabilization5D)),

        // From Xavier Raynaud: some notes on missing tags.
        // 0x0051 seems to be identical to FNumber (0x0036). An approx. relation between Tag value
        // and Fstop is exp(-0.335+value*0.043)
        // 0x0052 seems to be identical to ExposureTime (0x0035). An approx. relation between Tag
        // value and Exposure time is exp(-4+value*0.085)

        // End of list marker
        TagInfo(0xffff, "(UnknownMinoltaCs5DTag)", "(UnknownMinoltaCs5DTag)",
                N_("Unknown Minolta Camera Settings 5D tag"),
                minoltaCs5DIfdId, makerTags, invalidTypeId, printValue)
    };

    const TagInfo* MinoltaMakerNote::tagListCs5D()
    {
        return tagInfoCs5D_;
    }

    // TODO : Add camera settings tags info "New2"...

    //! @cond IGNORE
    MinoltaMakerNote::RegisterMn::RegisterMn()
    {
        MakerNoteFactory::registerMakerNote("KONICA MINOLTA*", "*", createMinoltaMakerNote);
        MakerNoteFactory::registerMakerNote("Minolta*", "*", createMinoltaMakerNote);

        MakerNoteFactory::registerMakerNote(minoltaIfdId,      MakerNote::AutoPtr(new MinoltaMakerNote));
        MakerNoteFactory::registerMakerNote(minoltaCs5DIfdId,  MakerNote::AutoPtr(new MinoltaMakerNote));
        MakerNoteFactory::registerMakerNote(minoltaCs7DIfdId,  MakerNote::AutoPtr(new MinoltaMakerNote));
        MakerNoteFactory::registerMakerNote(minoltaCsOldIfdId, MakerNote::AutoPtr(new MinoltaMakerNote));
        MakerNoteFactory::registerMakerNote(minoltaCsNewIfdId, MakerNote::AutoPtr(new MinoltaMakerNote));
    }
    //! @endcond

    int MinoltaMakerNote::read(const byte* buf, long len, long start, ByteOrder byteOrder, long shift)
    {
        int rc = IfdMakerNote::read(buf, len, start, byteOrder, shift);
        if (rc) return rc;

        // Decode Dynax 5D camera settings and add settings as additional entries
        Entries::iterator cs5D = ifd_.findTag(0x0114);

        if (cs5D != ifd_.end() && cs5D->type() == undefined) {
            for (uint16_t c = 0; cs5D->count()/2 > c; ++c)  {
                addCsEntry(minoltaCs5DIfdId, c, cs5D->offset() + c*2, cs5D->data() + c*2, 1);
            }
            // Discard the original entry
            ifd_.erase(cs5D);
        }

        // Decode Dynax 7D camera settings and add settings as additional entries
        Entries::iterator cs7D = ifd_.findTag(0x0004);

        if (cs7D != ifd_.end() && cs7D->type() == undefined) {
            for (uint16_t c = 0; cs7D->count()/2 > c; ++c)  {
                addCsEntry(minoltaCs7DIfdId, c, cs7D->offset() + c*2, cs7D->data() + c*2, 1);
            }
            // Discard the original entry
            ifd_.erase(cs7D);
        }

        // Decode Old Std camera settings and add settings as additional entries
        Entries::iterator csOldStd = ifd_.findTag(0x0001);

        if (csOldStd != ifd_.end() && csOldStd->type() == undefined) {
            for (uint16_t c = 0; csOldStd->count()/4 > c; ++c)  {
                addCsStdEntry(minoltaCsOldIfdId, c, csOldStd->offset() + c*4, csOldStd->data() + c*4, 1);
            }
            // Discard the original entry
            ifd_.erase(csOldStd);
        }

        // Decode New Std camera settings and add settings as additional entries
        Entries::iterator csNewStd = ifd_.findTag(0x0003);

        if (csNewStd != ifd_.end() && csNewStd->type() == undefined) {
            for (uint16_t c = 0; csNewStd->count()/4 > c; ++c)  {
                addCsStdEntry(minoltaCsNewIfdId, c, csNewStd->offset() + c*4, csNewStd->data() + c*4, 1);
            }
            // Discard the original entry
            ifd_.erase(csNewStd);
        }

        // Copy remaining ifd entries
        entries_.insert(entries_.begin(), ifd_.begin(), ifd_.end());

        // Set idx
        int idx = 0;
        Entries::iterator e = entries_.end();
        for (Entries::iterator i = entries_.begin(); i != e; ++i) {
            i->setIdx(++idx);
        }

        return 0;
    }

    void MinoltaMakerNote::addCsEntry(IfdId ifdId, uint16_t tag, long offset, const byte* data, int count)
    {
        Entry e(false);
        e.setIfdId(ifdId);
        e.setTag(tag);
        e.setOffset(offset);
        e.setValue(unsignedShort, count, data, 2*count, bigEndian);
        add(e);
    }

    void MinoltaMakerNote::addCsStdEntry(IfdId ifdId, uint32_t tag, long offset, const byte* data, int count)
    {
        Entry e(false);
        e.setIfdId(ifdId);
        e.setTag(tag);
        e.setOffset(offset);
        e.setValue(unsignedLong, count, data, 4*count, bigEndian);
        add(e);
    }

    void MinoltaMakerNote::add(const Entry& entry)
    {
        assert(alloc_ == entry.alloc());
        assert(   entry.ifdId() == minoltaIfdId
               || entry.ifdId() == minoltaCs5DIfdId
               || entry.ifdId() == minoltaCs7DIfdId
               || entry.ifdId() == minoltaCsOldIfdId
               || entry.ifdId() == minoltaCsNewIfdId);
        // allow duplicates
        entries_.push_back(entry);
    }

    long MinoltaMakerNote::copy(byte* buf, ByteOrder byteOrder, long offset)
    {
        if (byteOrder_ == invalidByteOrder) byteOrder_ = byteOrder;

        assert(ifd_.alloc());
        ifd_.clear();

        // Add all standard Minolta entries to the IFD
        Entries::const_iterator end = entries_.end();
        for (Entries::const_iterator i = entries_.begin(); i != end; ++i) {
            if (i->ifdId() == minoltaIfdId) {
                ifd_.add(*i);
            }
        }

        // Collect Dynax 5D camera settings entries and add the original Minolta tag
        Entry cs5D;
        if (assemble(cs5D, minoltaCs5DIfdId, 0x0114, bigEndian)) {
            ifd_.erase(0x0114);
            ifd_.add(cs5D);
        }

        // Collect Dynax 7D camera settings entries and add the original Minolta tag
        Entry cs7D;
        if (assemble(cs7D, minoltaCs7DIfdId, 0x0004, bigEndian)) {
            ifd_.erase(0x0004);
            ifd_.add(cs7D);
        }

        // Collect Old Std camera settings entries and add the original Minolta tag
        Entry csOldStd;
        if (assembleStd(csOldStd, minoltaCsOldIfdId, 0x0001, bigEndian)) {
            ifd_.erase(0x0001);
            ifd_.add(csOldStd);
        }

        // Collect New Std camera settings entries and add the original Minolta tag
        Entry csNewStd;
        if (assembleStd(csNewStd, minoltaCsNewIfdId, 0x0003, bigEndian)) {
            ifd_.erase(0x0003);
            ifd_.add(csNewStd);
        }

        return IfdMakerNote::copy(buf, byteOrder_, offset);
    } // MinoltaMakerNote::copy

    void MinoltaMakerNote::updateBase(byte* pNewBase)
    {
        byte* pBase = ifd_.updateBase(pNewBase);
        if (absShift_ && !alloc_) {
            Entries::iterator end = entries_.end();
            for (Entries::iterator pos = entries_.begin(); pos != end; ++pos) {
                pos->updateBase(pBase, pNewBase);
            }
        }
    } // MinoltaMakerNote::updateBase

    long MinoltaMakerNote::size() const
    {
        Ifd ifd(minoltaIfdId, 0, alloc_); // offset doesn't matter

        // Add all standard Minolta entries to the IFD
        Entries::const_iterator end = entries_.end();
        for (Entries::const_iterator i = entries_.begin(); i != end; ++i) {
            if (i->ifdId() == minoltaIfdId) {
                ifd.add(*i);
            }
        }
        // Collect Dynax 5D camera settings entries and add the original Minolta tag
        Entry cs5D(alloc_);
        if (assemble(cs5D, minoltaCs5DIfdId, 0x0114, bigEndian)) {
            ifd.erase(0x0114);
            ifd.add(cs5D);
        }

        // Collect Dynax 7D camera settings entries and add the original Minolta tag
        Entry cs7D(alloc_);
        if (assemble(cs7D, minoltaCs7DIfdId, 0x0004, bigEndian)) {
            ifd.erase(0x0004);
            ifd.add(cs7D);
        }

        // Collect Old Std camera settings entries and add the original Minolta tag
        Entry csOldStd(alloc_);
        if (assembleStd(csOldStd, minoltaCsOldIfdId, 0x0001, bigEndian)) {
            ifd.erase(0x0001);
            ifd.add(csOldStd);
        }

        // Collect New Std camera settings entries and add the original Minolta tag
        Entry csNewStd(alloc_);
        if (assembleStd(csNewStd, minoltaCsNewIfdId, 0x0003, bigEndian)) {
            ifd.erase(0x0003);
            ifd.add(csNewStd);
        }

        return headerSize() + ifd.size() + ifd.dataSize();
    } // MinoltaMakerNote::size

    long MinoltaMakerNote::assemble(Entry& e, IfdId ifdId, uint16_t tag, ByteOrder /*byteOrder*/) const
    {
        DataBuf buf(1024);
        std::memset(buf.pData_, 0x0, 1024);
        uint16_t len = 0;
        Entries::const_iterator end = entries_.end();
        for (Entries::const_iterator i = entries_.begin(); i != end; ++i) {
            if (i->ifdId() == ifdId) {
                uint16_t pos = i->tag() * 2;
                uint16_t size = pos + static_cast<uint16_t>(i->size());
                assert(size <= 1024);
                std::memcpy(buf.pData_ + pos, i->data(), i->size());
                if (len < size) len = size;
            }
        }
        if (len > 0) {
            e.setIfdId(minoltaIfdId);
            e.setIdx(0); // don't care
            e.setTag(tag);
            e.setOffset(0); // will be calculated when the IFD is written
            e.setValue(undefined, len, buf.pData_, len * 2);
        }
        return len;
    } // MinoltaMakerNote::assemble

    long MinoltaMakerNote::assembleStd(Entry& e, IfdId ifdId, uint32_t tag, ByteOrder /*byteOrder*/) const
    {
        DataBuf buf(1024);
        std::memset(buf.pData_, 0x0, 1024);
        uint32_t len = 0;
        Entries::const_iterator end = entries_.end();
        for (Entries::const_iterator i = entries_.begin(); i != end; ++i) {
            if (i->ifdId() == ifdId) {
                uint32_t pos = i->tag() * 4;
                uint32_t size = pos + static_cast<uint32_t>(i->size());
                assert(size <= 1024);
                std::memcpy(buf.pData_ + pos, i->data(), i->size());
                if (len < size) len = size;
            }
        }
        if (len > 0) {
            e.setIfdId(minoltaIfdId);
            e.setIdx(0); // don't care
            e.setTag(tag);
            e.setOffset(0); // will be calculated when the IFD is written
            e.setValue(undefined, len, buf.pData_, len * 4);
        }
        return len;
    } // MinoltaMakerNote::assembleStd

    Entries::const_iterator MinoltaMakerNote::findIdx(int idx) const
    {
        return std::find_if(entries_.begin(), entries_.end(), FindEntryByIdx(idx));
    }

    MinoltaMakerNote::MinoltaMakerNote(bool alloc)
        : IfdMakerNote(minoltaIfdId, alloc)
    {
    }

    MinoltaMakerNote::MinoltaMakerNote(const MinoltaMakerNote& rhs)
        : IfdMakerNote(rhs)
    {
        entries_ = rhs.entries_;
    }

    MinoltaMakerNote::AutoPtr MinoltaMakerNote::create(bool alloc) const
    {
        return AutoPtr(create_(alloc));
    }

    MinoltaMakerNote* MinoltaMakerNote::create_(bool alloc) const
    {
        return new MinoltaMakerNote(alloc);
    }

    MinoltaMakerNote::AutoPtr MinoltaMakerNote::clone() const
    {
        return AutoPtr(clone_());
    }

    MinoltaMakerNote* MinoltaMakerNote::clone_() const
    {
        return new MinoltaMakerNote(*this);
    }

// *****************************************************************************
// free functions

    MakerNote::AutoPtr createMinoltaMakerNote(bool alloc, const byte* /*buf*/, long /*len*/,
                                              ByteOrder /*byteOrder*/, long /*offset*/)
    {
        return MakerNote::AutoPtr(new MinoltaMakerNote(alloc));
    }

}                                       // namespace Exiv2
