//
//  test.c
//  TP2-Cripto
//
//  Created by Matias De Santi on 23/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "image.h"
#include "imageAdmin.h"
#include "in.h"
#include "generalDefines.h"
#include "embed.h"

#define BUFFER_SIZE 10*1024

#define AES_128 MCRYPT_RIJNDAEL_128
#define DES MCRYPT_3DES

int parseInForEmbed(int argc, char * argv[]);
char * getInFile(char* in);
char * encryptFile(char* in, char* crypt_alg, char* method, char* pass);
char * getSequence(char * in);
char *get_filename_ext(const char *filename);

int main(int argc, char * argv[]) {
    int code = 0;
    
    printf("hola\n");
    
    if(strcmp(argv[1], HIDE_INFO) == 0) {
        int code = parseInForEmbed(argc, argv);
        
    } else if(strcmp(argv[1], EXTRACT_INFO) == 0) {
        printf("EXTRACT!\n");
    }
    
    if(code == UNRECOGNIZED_PARAM) {
        printf("Incorrect parameters");
    }
    
    
//	image* img = loadImage("/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/image.bmp");
//    saveImage( "/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/image2.bmp", img);

}

int parseInForEmbed(int argc, char * argv[]) {
    char * in;
    char * carrier;
    char * outputPath;
    char * steg_alg;
    char * crypt_alg;
    char * method;
    char * password;
    int i = 2;
    for (i = 2; i < argc; i+=2) {
        if(strcmp(argv[i], IN_PARAM) == 0) {
//            printf("IN -> %s\n", argv[i]);
            in = argv[i+1];
        } else if(strcmp(argv[i], CARRIER_FILE_PARAM) == 0) {
//            printf("CARRIER -> %s\n", argv[i]);
            carrier = argv[i+1];
        } else if(strcmp(argv[i], OUTPUT_PATH_PARAM) == 0) {
//            printf("OUT -> %s\n", argv[i]);
            outputPath = argv[i+1];
        } else if(strcmp(argv[i], STEG_ALG_PARAM) == 0) {
//            printf("STEG -> %s\n", argv[i]);
            steg_alg = argv[i+1];
        } else if(strcmp(argv[i], CRYPT_PARAM) == 0) {
//            printf("CRYPT_PARAM -> %s\n", argv[i]);
            crypt_alg = argv[i+1];
        } else if(strcmp(argv[i], METHOD_PARAM) == 0) {
//            printf("METHOD_PARAM -> %s\n", argv[i]);
            method = argv[i+1];
        } else if(strcmp(argv[i], PASSWORD_PARAM) == 0) {
//            printf("PASSWORD -> %s\n", argv[i]);
            password = argv[i+1];
        } else {
            return UNRECOGNIZED_PARAM;
        }
    }
    
    char * encryptedFile = NULL;
    image* original = loadImage(carrier);
    char * array = toCharArray(original);
    char * sequence = getSequence(in, array);
    encryptedFile = encryptFile(in, crypt_alg, method, password);
    image * carrierImg = loadImage(carrier);
    embedLSB1(original, encryptedFile, carrierImg);
    
    return 0;
}


char * encryptFile(char* in, char* crypt_alg, char* method, char* pass) {
    char * IV = "BBBBBBBBCCCCCCCC";
    char *key = "0123456789abcdef";
    int keysize = 16; /* 128 bits */
    char * sequence = getSequence(in);
    int size = *((int*)sequence); //size of the sequence
    
    if(*pass){
		char* buffer;
	    int buffer_len = ceil(size/16.0)*16;
	    buffer = calloc(1, buffer_len);
	    memcpy(buffer, msg, buffer_len);

		encrypt(buffer, buffer_len, IV, key, keysize, DES, "cbc"); 
		char* encrypted = preappend_size(buffer);
		printf("Encrypted:%d %s\n",*((int*)encrypted),encrypted+4);
		msg = encrypted;
	}
}

char * getSequence(char * in) {
	FILE* in = fopen(in,"r");
	char* extension = get_filename_ext(in);
	int size = file_size(in);
	int length = 4 + size + strlen(extension) + 1;
	char* sequence = malloc(length);
	char read, *pointer=sequence;
	
	p+=4; //move 4 forward to insert size
	
	memcpy(msg, &length, 4);
	
	while((read=fgetc(in))!=-1){
		*pointer = read;
		pointer++;
	}
	fclose(in);
	strcpy(pointer,extension);
	return sequence;
}

char * getInFile(char* in) {
    char *buffer = NULL;
    FILE *fh = fopen(in, "rb");
    if (fh != NULL) {
        fseek(fh, 0L, SEEK_END);
        long s = ftell(fh);
        rewind(fh);
        buffer = malloc(s);
        if ( buffer != NULL ) {
            fread(buffer, s, 1, fh);
            fclose(fh); fh = NULL;
        }
    }
    return buffer;
}

int getFileSize(char * path) {
	FILE *fh = fopen(in, "r");
	int size = 0;
    if (fh != NULL) {
        fseek(fh, 0L, SEEK_END);
        s = ftell(fh);
        fclose(fh);
    }
    return size;
}

char *get_filename_ext(const char *filename) {
    char *dot = strchr(filename, '.');
    if(!dot || dot == filename)
        return "";
    return dot;
}

