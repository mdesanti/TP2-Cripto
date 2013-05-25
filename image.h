//
//  image.h
//  TP2-Cripto
//
//  Created by Matias De Santi on 25/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#ifndef TP2_Cripto_image_h
#define TP2_Cripto_image_h

#pragma pack(push,1)
/* Windows 3.x bitmap file header */
typedef struct {
    char         filetype[2];   /* magic - always 'B' 'M' */
    unsigned int filesize;
    short        reserved1;
    short        reserved2;
    unsigned int dataoffset;    /* offset in bytes to actual bitmap data */
} file_header;

/* Windows 3.x bitmap full header, including file header */
typedef struct {
    file_header  fileheader;
    unsigned int headersize;
    int          width;
    int          height;
    short        planes;
    short        bitsperpixel;  /* we only support the value 24 here */
    unsigned int compression;   /* we do not support compression */
    unsigned int bitmapsize;
    int          horizontalres;
    int          verticalres;
    unsigned int numcolors;
    unsigned int importantcolors;
} bitmap_header;
#pragma pack(pop)

typedef struct {
    bitmap_header* header;
    char * data;
} image;

#endif
