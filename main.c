//
//  test.c
//  TP2-Cripto
//
//  Created by Matias De Santi on 23/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "imageAdmin.h"
#include "in.h"
#include "generalDefines.h"
#include "embed.h"

#define BUFFER_SIZE 10*1024

int parseInForEmbed(int argc, char * argv[]);
char * getInFile(char* in);
char * encryptFile(char* in, char* crypt_alg, char* method, char* pass);
char * getSequence(char * in);
const char *get_filename_ext(const char *filename);

int main(int argc, const char * argv[]) {
    int code = 0;
    
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
    encryptedFile = encryptFile(in, crypt_alg, method, password);
    image * carrierImg = loadImage(carrier);
    embedLSB1(original, encryptedFile, carrierImg);
    
    return 0;
}


char * encryptFile(char* in, char* crypt_alg, char* method, char* pass) {
    char * buffer = (char*)malloc(BUFFER_SIZE);
    char * sequence = getSequence(in);
    snprintf(buffer, BUFFER_SIZE, "openssl enc -%s-%s -in %s -out /tmp/cripto.enc -pass pass:%s\n", crypt_alg, method, in, pass);
    printf("%s\n", buffer);
    if(system(buffer) == -1) {
        printf("Error\n");
    }
    return getInFile("/tmp/cripto.enc");
}

char * getSequence(char * in) {
    char *buffer = NULL;
    char *result = NULL;
    char * extension = get_filename_ext(in);
    FILE *fh = fopen(in, "rb");
//    FILE *out = NULL;
    int n = 0;
    if (fh != NULL) {
        fseek(fh, 0L, SEEK_END);
        long s = ftell(fh);
        rewind(fh);
        buffer = malloc(s);
        if ( buffer != NULL ) {
            fread(buffer, s, 1, fh);
            printf("%s\n", buffer);
            fclose(fh); fh = NULL;
        }
//        result = malloc(s+2000); //cuanto le ponemos aca?
//        snprintf(result,(s+2000), "%lu%s%s%c", s, buffer, extension,'\0');
//        out = fopen("/tmp/aux.txt", "w");
//        n=fwrite(result,sizeof(char),sizeof(result),out);
//        fclose(out);
    }
    return result;

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

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename)
        return "";
    return dot;
}

