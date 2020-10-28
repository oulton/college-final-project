#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

unsigned short BMP=0x4D42;
/*
λͼͷ�ṹ
*/
#pragma pack(1)
typedef struct 
{
    unsigned char bfType[2];//�ļ���ʽ
    unsigned long bfSize;//�ļ���С
    unsigned short bfReserved1;//����
    unsigned short bfReserved2;
    unsigned long bfOffBits; //DIB�������ļ��е�ƫ����
}fileHeader;
#pragma pack()
/*
λͼ������Ϣ�ṹ
*/
#pragma pack(1)
typedef struct 
{
    unsigned long biSize;//�ýṹ�Ĵ�С
    long biWidth;//�ļ����
    long biHeight;//�ļ��߶�
    unsigned short biPlanes;//ƽ����
    unsigned short biBitCount;//��ɫλ��
    unsigned long biCompression;//ѹ������
    unsigned long biSizeImage;//DIB��������С
    long biXPixPerMeter;
    long biYPixPerMeter;
    unsigned long biClrUsed;//������ɫ������
    unsigned long biClrImporant;//������Ҫ��ɫ
}fileInfo;
#pragma pack()


void menu_dis();     //�˵�
void load_image();   //����ͼ��
void Is_Gary();      //�Ҷ�ͼ�ж�
void Pix_Num();      //ͼ����
void Image_Size();   //ͼ����ռ�ֽ�
int GetDIBColor(int X, int Y, BYTE *r, BYTE *g, BYTE *b);   //��ȡX,Y���rgbֵ
void Save_Data();    //��������

FILE * fpBMP;
fileHeader * fh;
fileInfo * fi;

long LineByteWidth; 
BYTE *Buffer = NULL;   //���ش������
int main()
{
	int n;
	load_image();  //����ͼ��
	while(1)
	{
		menu_dis();
		printf("������ѡ��: ");
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
			printf("������ɣ��밴������˳�!\n");
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
		printf("\n\t            ��ͼ���ļ������ԡ�           \n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t*                                         *\n");
		printf("\t*          [1]   ��ѯͼ����ɫ             *\n");
		printf("\t*          [2]   ��ѯͼ�񳤿�             *\n");
		printf("\t*          [3]   ��ѯͼ���ֽ�             *\n");
		printf("\t*          [4]   ָ������д��             *\n");
		printf("\t*          [5]   �˳�                     *\n");
		printf("\t*                                         *\n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n\n");
}

void load_image()
{
	if((fpBMP=fopen("1.bmp","rb"))==NULL)
    {
        printf("���ļ�ʧ��");
        exit(0);
    }
	fh=(fileHeader *)malloc(sizeof(fileHeader));
    fi=(fileInfo *)malloc(sizeof(fileInfo));
    //��ȡλͼͷ�ṹ����Ϣͷ
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
        printf("��ͼ��BMP��ʽͼƬ\n�밴�������������");
		getchar();
	}
	else
	{
		printf("ͼ����bmp��ʽ��������ļ�����ͼƬ��ʽ\n");
		getchar();
		exit(0);
	}
}

void Is_Gary()
{
	if(fi->biBitCount == 8)
		printf("\nͼ��Ϊ��ͨ���Ҷ�ͼ\n�밴�������������");
	else
		printf("\nͼ��Ϊ��ͨ����ɫͼ\n�밴�������������");
	getchar();getchar();
}

void Pix_Num()
{
	printf("\nͼ�������طֱ�Ϊ�� %d*%d\n�밴�������������",fi->biWidth,fi->biHeight);
	getchar();getchar();
}

void Image_Size()
{
	printf("\nͼ����ռ�ֽ���Ϊ�� %d\n�밴�������������",fh->bfOffBits+fi->biSizeImage);
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
	printf("������������ϽǺ����½����꣬���귶Χ���ܳ���ͼ��Χ:%d*%d\n\n",fi->biWidth,fi->biHeight);
	printf("������������Ͻ�X����:");
	scanf("%d",&left_x);
	printf("������������Ͻ�Y����:");
	scanf("%d",&left_y);
	printf("������������Ͻ�X����:");
	scanf("%d",&right_x);
	printf("������������Ͻ�X����:");
	scanf("%d",&right_y);
	if(left_x>=right_x || left_y>=right_y)
	{
		printf("����������������������\n");
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
		printf("�ļ�д��ɹ���\n�밴�������������");
		getchar();getchar();
	}
}
