#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

unsigned short BMP=0x4D42;
/*
位图头结构
*/
#pragma pack(1)
typedef struct 
{
    unsigned char bfType[2];//文件格式
    unsigned long bfSize;//文件大小
    unsigned short bfReserved1;//保留
    unsigned short bfReserved2;
    unsigned long bfOffBits; //DIB数据在文件中的偏移量
}fileHeader;
#pragma pack()
/*
位图数据信息结构
*/
#pragma pack(1)
typedef struct 
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
#pragma pack()


void menu_dis();     //菜单
void load_image();   //载入图像
void Is_Gary();      //灰度图判断
void Pix_Num();      //图像宽高
void Image_Size();   //图像所占字节
int GetDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b);   //获取X,Y点的rgb值
void Save_Data();    //保存数据

FILE * fpBMP;
fileHeader * fh;
fileInfo * fi;

long LineByteWidth; 
BYTE *Buffer = NULL;   //像素存放数组
int main()
{
	int n;
	load_image();  //载入图像
	while(1)
	{
		menu_dis();
		printf("请输入选项: ");
		scanf("%d",&n);
		switch (n)
		{
		case 1:
			Is_Gary();
			break;
		case 2:
			Pix_Num();
			break;
		case 3:
			Image_Size();
			break;
		case 4:
			Save_Data();
			break;
		case 5:
			printf("程序完成，请按任意键退出!\n");
			free(fh);
			free(fi);
			getchar();getchar();
			exit(0);
			break;
		default:
			printf("Input error,press any key to iuput again!\n");
			getchar();getchar();
			continue;
		}
	}
    return 0;
}

void menu_dis()
{
		system("cls");   //clear the screen
		printf("\n\n\t*******************************************\n");
		printf("\n\t            ※图像文件的属性※           \n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t*                                         *\n");
		printf("\t*          [1]   查询图像颜色             *\n");
		printf("\t*          [2]   查询图像长宽             *\n");
		printf("\t*          [3]   查询图像字节             *\n");
		printf("\t*          [4]   指定区域写入             *\n");
		printf("\t*          [5]   退出                     *\n");
		printf("\t*                                         *\n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n\n");
}

void load_image()
{
	if((fpBMP=fopen("1.bmp","rb"))==NULL)
    {
        printf("打开文件失败");
        exit(0);
    }
	fh=(fileHeader *)malloc(sizeof(fileHeader));
    fi=(fileInfo *)malloc(sizeof(fileInfo));
    //读取位图头结构和信息头
    fread(fh,sizeof(fileHeader),1,fpBMP);
    fread(fi,sizeof(fileInfo),1,fpBMP);
	if(fh->bfType[0] == 'B' && fh->bfType[1] == 'M')
	{
		long dpixeladd = fi->biBitCount / 8;  
		LineByteWidth = fi->biWidth * (dpixeladd);  
		if ((LineByteWidth % 4) != 0)  
		LineByteWidth += 4 - (LineByteWidth % 4);  
		if ((Buffer = (BYTE*)malloc(sizeof(BYTE)* LineByteWidth * fi->biHeight)) != NULL)  
		{  
			fread(Buffer, LineByteWidth * fi->biHeight, 1, fpBMP);  
			fclose(fpBMP);  
		}  
        printf("此图是BMP格式图片\n请按任意键继续操作");
		getchar();
	}
	else
	{
		printf("图像不是bmp格式，请更改文件夹内图片格式\n");
		getchar();
		exit(0);
	}
}

void Is_Gary()
{
	if(fi->biBitCount == 8)
		printf("\n图像为单通道灰度图\n请按任意键继续操作");
	else
		printf("\n图像为三通道彩色图\n请按任意键继续操作");
	getchar();getchar();
}

void Pix_Num()
{
	printf("\n图像宽高像素分别为： %d*%d\n请按任意键继续操作",fi->biWidth,fi->biHeight);
	getchar();getchar();
}

void Image_Size()
{
	printf("\n图像所占字节数为： %d\n请按任意键继续操作",fh->bfOffBits+fi->biSizeImage);
	getchar();getchar();
}

int GetDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b)  
{  
    int dpixeladd;  
    BYTE *ptr;  
    if (X < 0 || X >= fi->biWidth || Y < 0 || Y >= fi->biHeight)  
    {  
        return 0;  
    }  
    dpixeladd = fi->biBitCount / 8;  
    ptr = Buffer + X * dpixeladd + (fi->biHeight - 1 - Y) * LineByteWidth;  
    *b = *ptr;  
    *g = *(ptr + 1);  
    *r = *(ptr + 2);  
    return 1;  
}

void Save_Data()
{
	int left_x,left_y,right_x,right_y;
	printf("请输入矩形左上角和右下角坐标，坐标范围不能超出图像范围:%d*%d\n\n",fi->biWidth,fi->biHeight);
	printf("请输入矩形左上角X坐标:");
	scanf("%d",&left_x);
	printf("请输入矩形左上角Y坐标:");
	scanf("%d",&left_y);
	printf("请输入矩形右上角X坐标:");
	scanf("%d",&right_x);
	printf("请输入矩形右上角X坐标:");
	scanf("%d",&right_y);
	if(left_x>=right_x || left_y>=right_y)
	{
		printf("输入坐标有误，请重新输入\n");
		getchar();getchar();
		return;
	}
	else
	{
		FILE *Save_fp=NULL;
		BYTE r,g,b;
		Save_fp = fopen("data.txt", "wb");
		for(int i=left_x;i<=right_x;i++)
		{
			for(int j=left_y;j<=right_y;j++)
			{
				if(GetDIBColor(i,j,&r,&g,&b)==1)
					fprintf(Save_fp,"(%d, %d): r:%d, g:%d, b:%d\n\n", i, j, (int)r, (int)g, (int)b);
			}
		}	
		printf("文件写入成功！\n请按任意键继续操作");
		getchar();getchar();
	}
}
