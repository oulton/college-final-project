#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"cv.h"
#include"highgui.h"

/*位图头结构*/
#pragma pack(2) //按两字节对齐
typedef struct TagBITMAPFILEHEADER
{
    unsigned char bfType[2];//文件格式
    unsigned long bfSize;//文件大小
    unsigned short bfReserved1;//保留
    unsigned short bfReserved2;
    unsigned long bfOffBits; //DIB数据在文件中的偏移量
}fileHeader;

/*位图数据信息结构*/
typedef struct TagBITMAPINFOHEADER
{
    unsigned long biSize;//该结构的大小
    long biWidth;//文件宽度
    long biHeight;//文件高度
    unsigned short biPlanes;//平面数
    unsigned short biBitCount;//颜色位数
    unsigned long biCompression;//压缩类型
    unsigned long biSizeImage;//DIB数据区大小
    long biXPixPerMeter;
    long biYPixPerMeter;
    unsigned long biClrUsed;//多少颜色索引表
    unsigned long biClrImporant;//多少重要颜色
}fileInfo;

/*调色板结构*/
typedef struct TagRGBQUAD
{
    unsigned char rgbBlue; //蓝色分量亮度
    unsigned char rgbGreen;//绿色分量亮度
    unsigned char rgbRed;//红色分量亮度
    unsigned char rgbReserved;
}rgbQuad;

void save_bitmap(IplImage *image)
{
    int height=image->height;
    int width=image->width;
    int imagesize=(((image->width+3)/4)*4*image->height)*3;
    
    fileHeader fHeader={0};
    fileInfo fInfo={0};

    static int k=0;
	char str[20]={'o','u','t','c','o','l','o','u','r'};
	char num[2]={'1'};
	FILE *fp;
	//for the fail is a variable
	num[0]=num[0]+k;
	k++;
	strcat(str,num);

	fp=fopen(str,"wb");
    if(!fp)
    {
        printf("cannot creat a new file!\n ");
        exit(0);
    }

    //Create Bitmap File Header
    fHeader.bfType[0]='B';
    fHeader.bfType[1]='M';
    fHeader.bfReserved1=0;
    fHeader.bfReserved2=0;
    fHeader.bfSize=sizeof(fileHeader)+sizeof(fileInfo)+imagesize;
    fHeader.bfOffBits=sizeof(fileHeader)+sizeof(fileInfo);

    //Create Bitmap Info Header
    fInfo.biSize=sizeof(fileInfo);
    fInfo.biHeight=-height;
    fInfo.biWidth=width;
    fInfo.biPlanes=1;
    fInfo.biBitCount=24;  //3通道  彩图
    fInfo.biSizeImage=imagesize;
    fInfo.biCompression=0;
    fInfo.biXPixPerMeter=0;
    fInfo.biYPixPerMeter=0;
    fInfo.biClrUsed=0;
    fInfo.biClrImporant=0;

    //write into file
    fwrite(&fHeader,sizeof(fileHeader),1,fp);
    fwrite(&fInfo,sizeof(fileInfo),1,fp);
    fwrite(image->imageData,(size_t) imagesize,1,fp);
    fclose(fp);
}
void save_graying(IplImage *image)
{
    fileHeader fHeader={0};
    fileInfo fInfo={0};
    rgbQuad colors[256];
    int i;
    int w,h;
    static int k=0;
	char str[20]={'o','u','t','g','r','a','y'};
	char num[2]={'1'};
	FILE *fp;

	num[0]=num[0]+k;
	k++;
	strcat(str,num);
	fp=fopen(str,"wb");
    if(!fp)
        printf("failed\n");
    w=image->width;
    h=image->height;

    //Create Bitmap File Header
    fHeader.bfType[0]='B';
    fHeader.bfType[1]='M';
    fHeader.bfReserved1=0;
    fHeader.bfReserved2=0;
    fHeader.bfSize=(((w+3)/4)*4*h)+1078;
    fHeader.bfOffBits=1078;

    //Create Bitmap Info Header 
    fInfo.biSize=sizeof(fileInfo);
    fInfo.biHeight=-h;
    fInfo.biWidth=w;
    fInfo.biPlanes=1;
    fInfo.biBitCount=8;  //1通道  非彩图
    fInfo.biSizeImage=(((w+3)/4)*4*h);
    fInfo.biCompression=0;
    fInfo.biXPixPerMeter=0;
    fInfo.biYPixPerMeter=0;
    fInfo.biClrUsed=0;
    fInfo.biClrImporant=0;

    //Create bitmap RGBQuad
    for(i=0;i<256;i++)
    {
        colors[i].rgbBlue=i;
        colors[i].rgbGreen=i;
        colors[i].rgbRed=i;
    }

    //write into file
    fwrite(&fHeader,sizeof(fileHeader),1,fp);
    fwrite(&fInfo,sizeof(fileInfo),1,fp);
    fwrite(colors,sizeof(rgbQuad),256,fp);
    fwrite(image->imageData,(size_t)(((w+3)/4)*4*h),1,fp);
    fclose(fp);
}