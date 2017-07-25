/*
 * File:	exif.cpp
 * Purpose:	cpp EXIF reader
 * 16/Mar/2003 <ing.davide.pizzolato@libero.it>
 * based on jhead-1.8 by Matthias Wandel <mwandel(at)rim(dot)net>
 */
#include "stdafx.h"
#include "exif.h"

////////////////////////////////////////////////////////////////////////////////
Cexif::Cexif(EXIFINFO* info)
{
	if (info) {
		m_exifinfo = info;
		freeinfo = false;
	} else {
		m_exifinfo = new EXIFINFO;
		memset(m_exifinfo,0,sizeof(EXIFINFO));
		freeinfo = true;
	}

	m_szLastError[0]='\0';
	ExifImageWidth = MotorolaOrder = 0;
	SectionsRead=0;
	memset(&Sections, 0, MAX_SECTIONS * sizeof(Section_t));
}
////////////////////////////////////////////////////////////////////////////////
Cexif::~Cexif()
{
	for(int i=0;i<MAX_SECTIONS;i++) if(Sections[i].Data) free(Sections[i].Data);
	if (freeinfo) delete m_exifinfo;
}
////////////////////////////////////////////////////////////////////////////////
bool Cexif::DecodeExif(FILE * hFile)
{
    int a;
    int HaveCom = 0;

    a = fgetc(hFile);

    if (a != 0xff || fgetc(hFile) != M_SOI){
        return 0;
    }

    for(;;){
        int itemlen;
        int marker = 0;
        int ll,lh, got;
        unsigned char * Data;

        if (SectionsRead >= MAX_SECTIONS){
			strcpy(m_szLastError,"Too many sections in jpg file");
			return 0;
        }

        for (a=0;a<7;a++){
            marker = fgetc(hFile);
            if (marker != 0xff) break;

            if (a >= 6){
                printf("too many padding unsigned chars\n");
                return 0;
            }
        }

        if (marker == 0xff){
            // 0xff is legal padding, but if we get that many, something's wrong.
            strcpy(m_szLastError,"too many padding unsigned chars!");
			return 0;
        }

        Sections[SectionsRead].Type = marker;

        // Read the length of the section.
        lh = fgetc(hFile);
        ll = fgetc(hFile);

        itemlen = (lh << 8) | ll;

        if (itemlen < 2){
            strcpy(m_szLastError,"invalid marker");
			return 0;
        }

        Sections[SectionsRead].Size = itemlen;

        Data = (unsigned char *)malloc(itemlen);
        if (Data == NULL){
            strcpy(m_szLastError,"Could not allocate memory");
			return 0;
        }
        Sections[SectionsRead].Data = Data;

        // Store first two pre-read unsigned chars.
        Data[0] = (unsigned char)lh;
        Data[1] = (unsigned char)ll;

        got = fread(Data+2, 1, itemlen-2,hFile); // Read the whole section.
        if (got != itemlen-2){
            strcpy(m_szLastError,"Premature end of file?");
			return 0;
        }
        SectionsRead += 1;

        switch(marker){

            case M_SOS:   // stop before hitting compressed data 
                // If reading entire image is requested, read the rest of the data.
                /*if (ReadMode & READ_IMAGE){
                    int cp, ep, size;
                    // Determine how much file is left.
                    cp = ftell(infile);
                    fseek(infile, 0, SEEK_END);
                    ep = ftell(infile);
                    fseek(infile, cp, SEEK_SET);

                    size = ep-cp;
                    Data = (uchar *)malloc(size);
                    if (Data == NULL){
                        strcpy(m_szLastError,"could not allocate data for entire image");
						return 0;
                    }

                    got = fread(Data, 1, size, infile);
                    if (got != size){
                        strcpy(m_szLastError,"could not read the rest of the image");
						return 0;
                    }

                    Sections[SectionsRead].Data = Data;
                    Sections[SectionsRead].Size = size;
                    Sections[SectionsRead].Type = PSEUDO_IMAGE_MARKER;
                    SectionsRead ++;
                    HaveAll = 1;
                }*/
                return 1;

            case M_EOI:   // in case it's a tables-only JPEG stream
                printf("No image in jpeg!\n");
                return 0;

            case M_COM: // Comment section
                if (HaveCom){
                    // Discard this section.
                    free(Sections[--SectionsRead].Data);
					Sections[SectionsRead].Data=0;
                }else{
                    process_COM(Data, itemlen);
                    HaveCom = 1;
                }
                break;

            case M_JFIF:
                // Regular jpegs always have this tag, exif images have the exif
                // marker instead, althogh ACDsee will write images with both markers.
                // this program will re-create this marker on absence of exif marker.
                // hence no need to keep the copy from the file.
                free(Sections[--SectionsRead].Data);
				Sections[SectionsRead].Data=0;
                break;

            case M_EXIF:
                // Seen files from some 'U-lead' software with Vivitar scanner
                // that uses marker 31 for non exif stuff.  Thus make sure 
                // it says 'Exif' in the section before treating it as exif.
                if (memcmp(Data+2, "Exif", 4) == 0){
                    m_exifinfo->IsExif = process_EXIF((unsigned char *)Data+2, itemlen);
                }else{
                    // Discard this section.
                    free(Sections[--SectionsRead].Data);
					Sections[SectionsRead].Data=0;
                }
                break;

            case M_SOF0: 
            case M_SOF1: 
            case M_SOF2: 
            case M_SOF3: 
            case M_SOF5: 
            case M_SOF6: 
            case M_SOF7: 
            case M_SOF9: 
            case M_SOF10:
            case M_SOF11:
            case M_SOF13:
            case M_SOF14:
            case M_SOF15:
                process_SOFn(Data, marker);
                break;
            default:
                // Skip any other sections.
                //if (ShowTags) printf("Jpeg section marker 0x%02x size %d\n",marker, itemlen);
                break;
        }
    }
	return 1;
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Process a EXIF marker
   Describes all the drivel that most digital cameras include...
--------------------------------------------------------------------------*/
bool Cexif::process_EXIF(unsigned char * CharBuf, unsigned int length)
{
    m_exifinfo->FlashUsed = 0; 
    /* If it's from a digicam, and it used flash, it says so. */
    m_exifinfo->Comments[0] = '\0';  /* Initial value - null string */

    ExifImageWidth = 0;

    {   /* Check the EXIF header component */
        static const unsigned char ExifHeader[] = "Exif\0\0";
        if (memcmp(CharBuf+0, ExifHeader,6)){
			strcpy(m_szLastError,"Incorrect Exif header");
			return 0;
		}
    }

    if (memcmp(CharBuf+6,"II",2) == 0){
        MotorolaOrder = 0;
    }else{
        if (memcmp(CharBuf+6,"MM",2) == 0){
            MotorolaOrder = 1;
        }else{
            strcpy(m_szLastError,"Invalid Exif alignment marker.");
			return 0;
        }
    }

    /* Check the next two values for correctness. */
    if (Get16u(CharBuf+8) != 0x2a){
        strcpy(m_szLastError,"Invalid Exif start (1)");
		return 0;
    }

	int FirstOffset = Get32u(CharBuf+10);
    if (FirstOffset < 8 || FirstOffset > 16){
        // I used to ensure this was set to 8 (website I used indicated its 8)
        // but PENTAX Optio 230 has it set differently, and uses it as offset. (Sept 11 2002)
        strcpy(m_szLastError,"Suspicious offset of first IFD value");
		return 0;
    }

    unsigned char * LastExifRefd = CharBuf;

    /* First directory starts 16 unsigned chars in.  Offsets start at 8 unsigned chars in. */
    if (!ProcessExifDir(CharBuf+14, CharBuf+6, length-6, m_exifinfo, &LastExifRefd))
		return 0;

    /* This is how far the interesting (non thumbnail) part of the exif went. */
    // int ExifSettingsLength = LastExifRefd - CharBuf;

    /* Compute the CCD width, in milimeters. */
    if (m_exifinfo->FocalplaneXRes != 0){
        m_exifinfo->CCDWidth = (float)(ExifImageWidth * m_exifinfo->FocalplaneUnits / m_exifinfo->FocalplaneXRes);
    }

	return 1;
}
//--------------------------------------------------------------------------
// Get 16 bits motorola order (always) for jpeg header stuff.
//--------------------------------------------------------------------------
int Cexif::Get16m(void * Short)
{
    return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 16 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
int Cexif::Get16u(void * Short)
{
    if (MotorolaOrder){
        return (((unsigned char *)Short)[0] << 8) | ((unsigned char *)Short)[1];
    }else{
        return (((unsigned char *)Short)[1] << 8) | ((unsigned char *)Short)[0];
    }
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 32 bit signed value from file's native unsigned char order
--------------------------------------------------------------------------*/
long Cexif::Get32s(void * Long)
{
    if (MotorolaOrder){
        return  ((( char *)Long)[0] << 24) | (((unsigned char *)Long)[1] << 16)
              | (((unsigned char *)Long)[2] << 8 ) | (((unsigned char *)Long)[3] << 0 );
    }else{
        return  ((( char *)Long)[3] << 24) | (((unsigned char *)Long)[2] << 16)
              | (((unsigned char *)Long)[1] << 8 ) | (((unsigned char *)Long)[0] << 0 );
    }
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Convert a 32 bit unsigned value from file's native unsigned char order
--------------------------------------------------------------------------*/
unsigned long Cexif::Get32u(void * Long)
{
    return (unsigned long)Get32s(Long) & 0xffffffff;
}
////////////////////////////////////////////////////////////////////////////////

/* Describes format descriptor */
static const int BytesPerFormat[] = {0,1,1,2,4,8,1,1,2,4,8,4,8};
#define NUM_FORMATS 12

#define FMT_BYTE       1 
#define FMT_STRING     2
#define FMT_USHORT     3
#define FMT_ULONG      4
#define FMT_URATIONAL  5
#define FMT_SBYTE      6
#define FMT_UNDEFINED  7
#define FMT_SSHORT     8
#define FMT_SLONG      9
#define FMT_SRATIONAL 10
#define FMT_SINGLE    11
#define FMT_DOUBLE    12

/* Describes tag values */

#define TAG_EXIF_VERSION      0x9000
#define TAG_EXIF_OFFSET       0x8769
#define TAG_INTEROP_OFFSET    0xa005

#define TAG_MAKE              0x010F
#define TAG_MODEL             0x0110

#define TAG_ORIENTATION       0x0112
#define TAG_XRESOLUTION       0x011A
#define TAG_YRESOLUTION       0x011B
#define TAG_RESOLUTIONUNIT    0x0128

#define TAG_EXPOSURETIME      0x829A
#define TAG_FNUMBER           0x829D

#define TAG_SHUTTERSPEED      0x9201
#define TAG_APERTURE          0x9202
#define TAG_BRIGHTNESS        0x9203
#define TAG_MAXAPERTURE       0x9205
#define TAG_FOCALLENGTH       0x920A

#define TAG_DATETIME_ORIGINAL 0x9003
#define TAG_USERCOMMENT       0x9286

#define TAG_SUBJECT_DISTANCE  0x9206
#define TAG_FLASH             0x9209

#define TAG_FOCALPLANEXRES    0xa20E
#define TAG_FOCALPLANEYRES    0xa20F
#define TAG_FOCALPLANEUNITS   0xa210
#define TAG_EXIF_IMAGEWIDTH   0xA002
#define TAG_EXIF_IMAGELENGTH  0xA003

/* the following is added 05-jan-2001 vcs */
#define TAG_EXPOSURE_BIAS     0x9204
#define TAG_WHITEBALANCE      0x9208
#define TAG_METERING_MODE     0x9207
#define TAG_EXPOSURE_PROGRAM  0x8822
#define TAG_ISO_EQUIVALENT    0x8827
#define TAG_COMPRESSION_LEVEL 0x9102

#define TAG_THUMBNAIL_OFFSET  0x0201
#define TAG_THUMBNAIL_LENGTH  0x0202


/*--------------------------------------------------------------------------
   Process one of the nested EXIF directories.
--------------------------------------------------------------------------*/
bool Cexif::ProcessExifDir(unsigned char * DirStart, unsigned char * OffsetBase, unsigned ExifLength,
                           EXIFINFO * const m_exifinfo, unsigned char ** const LastExifRefdP )
{
    int de;
    int NumDirEntries;
    unsigned ThumbnailOffset = 0;
    unsigned ThumbnailSize = 0;

    NumDirEntries = Get16u(DirStart);

    if ((DirStart+2+NumDirEntries*12) > (OffsetBase+ExifLength)){
        strcpy(m_szLastError,"Illegally sized directory");
		return 0;
    }

    for (de=0;de<NumDirEntries;de++){
        int Tag, Format, Components;
        unsigned char * ValuePtr;
            /* This actually can point to a variety of things; it must be
               cast to other types when used.  But we use it as a unsigned char-by-unsigned char
               cursor, so we declare it as a pointer to a generic unsigned char here.
            */
        int BytesCount;
        unsigned char * DirEntry;
        DirEntry = DirStart+2+12*de;

        Tag = Get16u(DirEntry);
        Format = Get16u(DirEntry+2);
        Components = Get32u(DirEntry+4);

        if ((Format-1) >= NUM_FORMATS) {
            /* (-1) catches illegal zero case as unsigned underflows to positive large */
            strcpy(m_szLastError,"Illegal format code in EXIF dir");
			return 0;
		}

        BytesCount = Components * BytesPerFormat[Format];

        if (BytesCount > 4){
            unsigned OffsetVal;
            OffsetVal = Get32u(DirEntry+8);
            /* If its bigger than 4 unsigned chars, the dir entry contains an offset.*/
            if (OffsetVal+BytesCount > ExifLength){
                /* Bogus pointer offset and / or unsigned charcount value */
                strcpy(m_szLastError,"Illegal pointer offset value in EXIF.");
				return 0;
            }
            ValuePtr = OffsetBase+OffsetVal;
        }else{
            /* 4 unsigned chars or less and value is in the dir entry itself */
            ValuePtr = DirEntry+8;
        }

        if (*LastExifRefdP < ValuePtr+BytesCount){
            /* Keep track of last unsigned char in the exif header that was
               actually referenced.  That way, we know where the
               discardable thumbnail data begins.
            */
            *LastExifRefdP = ValuePtr+BytesCount;
        }

        /* Extract useful components of tag */
        switch(Tag){
            case TAG_DATETIME_ORIGINAL:
                strncpy(m_exifinfo->DateTime, (char*)ValuePtr, 19);
                break;

        }

        if (Tag == TAG_EXIF_OFFSET || Tag == TAG_INTEROP_OFFSET){
            unsigned char * SubdirStart;
            SubdirStart = OffsetBase + Get32u(ValuePtr);
            if (SubdirStart < OffsetBase || 
                SubdirStart > OffsetBase+ExifLength){
                strcpy(m_szLastError,"Illegal subdirectory link");
				return 0;
            }
            ProcessExifDir(SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
            continue;
        }
    }


    {
        /* In addition to linking to subdirectories via exif tags,
           there's also a potential link to another directory at the end
           of each directory.  This has got to be the result of a
           committee!  
        */
        unsigned char * SubdirStart;
        unsigned Offset;
        Offset = Get16u(DirStart+2+12*NumDirEntries);
        if (Offset){
            SubdirStart = OffsetBase + Offset;
            if (SubdirStart < OffsetBase 
                || SubdirStart > OffsetBase+ExifLength){
                strcpy(m_szLastError,"Illegal subdirectory link");
				return 0;
            }
            ProcessExifDir(SubdirStart, OffsetBase, ExifLength, m_exifinfo, LastExifRefdP);
        }
    }


    if (ThumbnailSize && ThumbnailOffset){
        if (ThumbnailSize + ThumbnailOffset <= ExifLength){
            /* The thumbnail pointer appears to be valid.  Store it. */
            m_exifinfo->ThumbnailPointer = OffsetBase + ThumbnailOffset;
            m_exifinfo->ThumbnailSize = ThumbnailSize;
        }
    }

	return 1;
}
////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------------------------------------
   Evaluate number, be it int, rational, or float from directory.
--------------------------------------------------------------------------*/
double Cexif::ConvertAnyFormat(void * ValuePtr, int Format)
{
    double Value;
    Value = 0;

    switch(Format){
        case FMT_SBYTE:     Value = *(signed char *)ValuePtr;  break;
        case FMT_BYTE:      Value = *(unsigned char *)ValuePtr;        break;

        case FMT_USHORT:    Value = Get16u(ValuePtr);          break;
        case FMT_ULONG:     Value = Get32u(ValuePtr);          break;

        case FMT_URATIONAL:
        case FMT_SRATIONAL: 
            {
                int Num,Den;
                Num = Get32s(ValuePtr);
                Den = Get32s(4+(char *)ValuePtr);
                if (Den == 0){
                    Value = 0;
                }else{
                    Value = (double)Num/Den;
                }
                break;
            }

        case FMT_SSHORT:    Value = (signed short)Get16u(ValuePtr);  break;
        case FMT_SLONG:     Value = Get32s(ValuePtr);                break;

        /* Not sure if this is correct (never seen float used in Exif format)
         */
        case FMT_SINGLE:    Value = (double)*(float *)ValuePtr;      break;
        case FMT_DOUBLE:    Value = *(double *)ValuePtr;             break;
    }
    return Value;
}
////////////////////////////////////////////////////////////////////////////////
void Cexif::process_COM (const unsigned char * Data, int length)
{
    int ch;
    char Comment[MAX_COMMENT+1];
    int nch;
    int a;

    nch = 0;

    if (length > MAX_COMMENT) length = MAX_COMMENT; // Truncate if it won't fit in our structure.

    for (a=2;a<length;a++){
        ch = Data[a];

        if (ch == '\r' && Data[a+1] == '\n') continue; // Remove cr followed by lf.

        if ((ch>=0x20) || ch == '\n' || ch == '\t'){
            Comment[nch++] = (char)ch;
        }else{
            Comment[nch++] = '?';
        }
    }

    Comment[nch] = '\0'; // Null terminate

    //if (ShowTags) printf("COM marker comment: %s\n",Comment);

    strcpy(m_exifinfo->Comments,Comment);
}
////////////////////////////////////////////////////////////////////////////////
void Cexif::process_SOFn (const unsigned char * Data, int marker)
{
    int data_precision, num_components;

    data_precision = Data[2];
    m_exifinfo->Height = Get16m((void*)(Data+3));
    m_exifinfo->Width = Get16m((void*)(Data+5));
    num_components = Data[7];

    if (num_components == 3){
        m_exifinfo->IsColor = 1;
    }else{
        m_exifinfo->IsColor = 0;
    }

    m_exifinfo->Process = marker;

    //if (ShowTags) printf("JPEG image is %uw * %uh, %d color components, %d bits per sample\n",
    //               ImageInfo.Width, ImageInfo.Height, num_components, data_precision);
}
////////////////////////////////////////////////////////////////////////////////

