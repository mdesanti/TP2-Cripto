//
//  imageLoader.c
//  TP2-Cripto
//
//  Created by Matias De Santi on 25/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#include <stdio.h>
#include "image.h"
#include "imageAdmin.h"


image* loadImage(char* input) {
    
    //variable dec:
    FILE *fp;
    bitmap_header* hp;
    int n;
    char * data;
    image* img;
    int error = 0;
    
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
