//
//  imageAdmin.h
//  TP2-Cripto
//
//  Created by Matias De Santi on 25/05/13.
//  Copyright (c) 2013 Matias De Santi. All rights reserved.
//

#ifndef TP2_Cripto_imageAdmin_h
#define TP2_Cripto_imageAdmin_h

image * loadImage(char* input);
void saveImage(char* outputFilem, image * img);
image* copyImg(image * img);
char * toCharArray(image * img);

#endif
