#include "bmp.h"  

const char* fileName_get = "1.bmp";
const char* fileName_out = "output.bmp";

void menu_dis();
void Set_Color();

ClImage* img;
int main()  
{  
	int n;
	img = clLoadImage(fileName_get); 
	while(1)
	{
		menu_dis();
		printf("ѡ��1-3ѡ��: ");
		scanf("%d",&n);
		switch (n)
		{
		case 1:
			Set_Color();
			break;
		case 2: 
			if(clSaveImage(fileName_out, img))  
			{
				printf("�ļ�����ɹ�...\n�밴���������\n");  
			}
			else
			{
				printf("�ļ�δ����ɹ�...\n�밴���������\n");
			}
			getchar();getchar();
			break;
		case 3:
			printf("�밴������˳�!\n");
			getchar();getchar();
			exit(0);
			break;
		default:
			printf("Input error,press any key to iuput again!\n");
			getchar();getchar();
			continue;
		}
	}
	system("pause");
	return 0;  
}  

void menu_dis()
{
		system("cls");   //clear the screen
		printf("\n\n\t*******************************************\n");
		printf("\n\t                  ������                 \n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t*                                         *\n");
		printf("\t*          [1]   ָ��������ɫ             *\n");
		printf("\t*          [2]   ����ΪBMP�ļ�            *\n");
		printf("\t*          [3]   �˳�                     *\n");
		printf("\t*                                         *\n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n\n");
}

void Set_Color()
{
	int left_x,left_y,right_x,right_y;
	int R,G,B,Pixel;
	printf("������������ϽǺ����½����꣬���귶Χ���ܳ���ͼ��Χ:%d*%d\n\n",img->width,img->height);
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
		printf("������������\n");
		getchar();getchar();
		return;
	}
	else
	{
		int step = img->channels*img->width;
		if(img->channels == 3)        //��ɫͼ
		{
			printf("������Ҫ�ڴ������ϵ���ɫ��R G Bֵ��Ϊ0-255֮��\n");
			printf("������R�� ");
			scanf("%d",&R);
			printf("������G�� ");
			scanf("%d",&G);
			printf("������B�� ");
			scanf("%d",&B);
			for(int i=left_x;i<=right_x;i++)
			{
				for(int j=left_y;j<=right_y;j++)
				{
					img->imageData[i*step+j*3] = B;
					img->imageData[i*step+j*3+1] = G;
					img->imageData[i*step+j*3+2] = R;
				}
			}
		}
		else if(img->channels == 1)  //�Ҷ�ͼ
		{
			printf("������Ҫ�ڴ������ϵ���ɫ���Ҷ�ֵ��0-255֮��\n");
			printf("������Pixel�� ");
			scanf("%d",&Pixel);
			for(int i=left_x;i<=right_x;i++)
			{
				for(int j=left_y;j<=right_y;j++)
				{
					img->imageData[i*step+j] = Pixel; 
				}
			}
		}
		printf("��ɫ���\n");
		getchar();getchar();
	}
}
