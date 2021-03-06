//
//  main.c
//  TP2-Cripto
//
//  Created by Matias De Santi on 21/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EMBED "-embed"
#define IN "-in"
#define P "-p"
#define OUT "-out"
#define STEG "-steg"

typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t LONG;

#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;  //specifies the file type
    DWORD bfSize;  //specifies the size in bytes of the bitmap file
    WORD bfReserved1;  //reserved; must be 0
    WORD bfReserved2;  //reserved; must be 0
    DWORD bOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //species height in pixels
    WORD biPlanes; //specifies the number of color planes, must be 1
    WORD biBitCount; //specifies the number of bit per pixel
    DWORD biCompression;//spcifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable
    
    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;
    
    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);
          
    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42) {
 	   fclose(filePtr);
       return NULL;
    }
          
    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr);
          
    //move file point to the begging of bitmap data
	fseek(filePtr, bitmapFileHeader.bOffBits, SEEK_SET);
          
    //allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
          
    //verify memory allocation
    if (!bitmapImage) {
	    free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }
          
    //read in the bitmap image data
    fread(bitmapImage,bitmapInfoHeader->biSizeImage,1,filePtr);
          
    //make sure bitmap image data was read
    if (bitmapImage == NULL) {
	    fclose(filePtr);
        return NULL;
    }
          
    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3) {
    	tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
	}
          
    //close file and return bitmap iamge data
    fclose(filePtr);
	return bitmapImage;
}

/* int main(int argc, const char * argv[]) {
//    FILE * image =  fopen("/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/degradeColor255.bmp", "r");
    
    BITMAPINFOHEADER bitmapInfoHeader;
    unsigned char *bitmapData;
    
    bitmapData = LoadBitmapFile("/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/degradeColor255.bmp",&bitmapInfoHeader);
    //now do what you want with it, later on i will show you how to display it in a normal window
    printf("finished\n");
}
*/

