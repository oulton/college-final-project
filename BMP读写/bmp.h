

#ifndef BMP_H  
#define BMP_H  

#include <stdio.h>  
#include <stdlib.h>  

typedef struct  
{  
	//unsigned short    bfType;  
	unsigned long    bfSize;  
	unsigned short    bfReserved1;  
	unsigned short    bfReserved2;  
	unsigned long    bfOffBits;  
} ClBitMapFileHeader;  

typedef struct  
{  
	unsigned long  biSize;   
	long   biWidth;   
	long   biHeight;   
	unsigned short   biPlanes;   
	unsigned short   biBitCount;  
	unsigned long  biCompression;   
	unsigned long  biSizeImage;   
	long   biXPelsPerMeter;   
	long   biYPelsPerMeter;   
	unsigned long   biClrUsed;   
	unsigned long   biClrImportant;   
} ClBitMapInfoHeader;  

typedef struct   
{  
	unsigned char rgbBlue; //该颜色的蓝色分量 
	unsigned char rgbGreen; //该颜色的绿色分量 
	unsigned char rgbRed; //该颜色的红色分量 
	unsigned char rgbReserved; //保留值 
} ClRgbQuad;  

typedef struct  
{  
	int width;  
	int height;  
	int channels;  
	unsigned char* imageData;  
}ClImage;  

ClImage* clLoadImage(const char* path);  
bool clSaveImage(const char* path, ClImage* bmpImg);  

#endif
