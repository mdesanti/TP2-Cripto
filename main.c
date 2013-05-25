//
//  test.c
//  TP2-Cripto
//
//  Created by Matias De Santi on 23/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>


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

image * loadImage(char* input);
void saveImage(char* outputFilem, image * img);

int main(int argc, const char * argv[]) {
	image* img = loadImage("/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/image.bmp");
    saveImage( "/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/image2.bmp", img);
    printf("%d\n", 1);
}

image* loadImage(char* input) {
    
    //variable dec:
    FILE *fp;
    bitmap_header* hp;
    int n;
    char * data;
    image* img;
    
    //Open input file:
    fp = fopen(input, "rb");
    if(fp==NULL){
        //cleanup
    }
    
    //Read the input file headers:
    hp=(bitmap_header*)malloc(sizeof(bitmap_header));
    if(hp==NULL)
        return 3;
    
    n=fread(hp, sizeof(bitmap_header), 1, fp);
    if(n<1){
        //cleanup
    }
    
    //Read the data of the image:
    data = (char*)malloc(sizeof(char)*hp->bitmapsize);
    if(data==NULL){
        //cleanup
    }
    
    fseek(fp,sizeof(char)*hp->fileheader.dataoffset,SEEK_SET);
    n=fread(data,sizeof(char),hp->bitmapsize, fp);
    if(n<1){
        //cleanup
    }
    
    img = (image*)malloc(sizeof(image));
    img->data = data;
    img->header = hp;
    
    fclose(fp);
    return img;
}


void saveImage(char * outputFile, image * img) {
    
    FILE* out;
    int n;
    
    //Open output file:
    out = fopen(outputFile, "w");
    if(out==NULL){
        //cleanup
    }
    
    n=fwrite(img->header,sizeof(char),sizeof(bitmap_header),out);
    if(n<1){
        //cleanup
    }
    fseek(out,sizeof(char)*img->header->fileheader.dataoffset,SEEK_SET);
    n=fwrite(img->data,sizeof(char),img->header->bitmapsize,out);
    if(n<1){
        //cleanup
    }
    
    fclose(out);
}
