/*λͼͷ�ṹ*/
#pragma pack(2) //�����ֽڶ���
typedef struct TagBITMAPFILEHEADER
{
	unsigned char bfType[2];//�ļ���ʽ
	unsigned long bfSize;//�ļ���С
	unsigned short bfReserved1;//����
	unsigned short bfReserved2;
	unsigned long bfOffBits; //DIB�������ļ��е�ƫ����
}fileHeader;

/*λͼ������Ϣ�ṹ*/

typedef struct TagBITMAPINFOHEADER
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

/*��ɫ��ṹ*/

typedef struct TagRGBQUAD
{
	unsigned char rgbBlue; //��ɫ��������
	unsigned char rgbGreen;//��ɫ��������
	unsigned char rgbRed;//��ɫ��������
	unsigned char rgbReserved;
}rgbQuad;