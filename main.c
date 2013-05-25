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

int main(int argc, const char * argv[]) {
	image* img = loadImage("/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/image.bmp");
    saveImage( "/Users/mdesanti90/Matias/ITBA/4to-2doCuatrimestre/Cripto/TPE2/image2.bmp", img);
    printf("%d\n", 1);
}