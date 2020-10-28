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
		printf("选择1-3选项: ");
		scanf("%d",&n);
		switch (n)
		{
		case 1:
			Set_Color();
			break;
		case 2: 
			if(clSaveImage(fileName_out, img))  
			{
				printf("文件保存成功...\n请按任意键继续\n");  
			}
			else
			{
				printf("文件未保存成功...\n请按任意键继续\n");
			}
			getchar();getchar();
			break;
		case 3:
			printf("请按任意键退出!\n");
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
		printf("\n\t                  点运算                 \n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n");
		printf("\t*                                         *\n");
		printf("\t*          [1]   指定区域上色             *\n");
		printf("\t*          [2]   保存为BMP文件            *\n");
		printf("\t*          [3]   退出                     *\n");
		printf("\t*                                         *\n");
		printf("\t* * * * * * * * * * * * * * * * * * * * * *\n\n");
}

void Set_Color()
{
	int left_x,left_y,right_x,right_y;
	int R,G,B,Pixel;
	printf("请输入矩形左上角和右下角坐标，坐标范围不能超出图像范围:%d*%d\n\n",img->width,img->height);
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
		printf("输入坐标有误\n");
		getchar();getchar();
		return;
	}
	else
	{
		int step = img->channels*img->width;
		if(img->channels == 3)        //彩色图
		{
			printf("请输入要在此区域上的颜色：R G B值均为0-255之间\n");
			printf("请输入R： ");
			scanf("%d",&R);
			printf("请输入G： ");
			scanf("%d",&G);
			printf("请输入B： ");
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
		else if(img->channels == 1)  //灰度图
		{
			printf("请输入要在此区域上的颜色：灰度值在0-255之间\n");
			printf("请输入Pixel： ");
			scanf("%d",&Pixel);
			for(int i=left_x;i<=right_x;i++)
			{
				for(int j=left_y;j<=right_y;j++)
				{
					img->imageData[i*step+j] = Pixel; 
				}
			}
		}
		printf("上色完成\n");
		getchar();getchar();
	}
}
