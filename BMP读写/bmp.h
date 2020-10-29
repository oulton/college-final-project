

#ifndef BMP_H  
#define BMP_H  

#include <stdio.h>  
#include <stdlib.h>  

typedef struct  
{  
	//unsigned short    bfType;   //文件格式
	unsigned long    bfSize;      //文件大小
	unsigned short    bfReserved1;  
	unsigned short    bfReserved2;  
	unsigned long    bfOffBits;   //DIB数据在文件中的偏移量
} ClBitMapFileHeader;  

typedef struct  
{  
	unsigned long  biSize;    //该结构的大小
	long   biWidth;           //文件宽度
	long   biHeight;          //文件高度
	unsigned short   biPlanes;   
	unsigned short   biBitCount;   //颜色位数
	unsigned long  biCompression;  //压缩类型 
	unsigned long  biSizeImage;    //DIB数据区大小
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
