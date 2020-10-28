#include<stdio.h>
#include<ctype.h>
#include <highgui.h>
#include <cv.h>
IplImage* turn_Graying(IplImage* );			 //the simple turnGraying
IplImage* Gray_Horizontal_mg(IplImage* );    //nChannels==1,Horizontal_mirror
IplImage* Colour_Horizontal_mg(IplImage* );  //nChannels==3,Horizontal_mirror
IplImage* Gray_Vertical_mg(IplImage* );      //nChannels==1,Vertical_mirror
IplImage* Colour_Vertical_mg(IplImage* );    //nChannels==3,Vertical_mirror
IplImage* Gray_Rotate_image(IplImage* ,double);		//nChannels==1,Gray_Rotate
IplImage* Colour_Rotate_image(IplImage* ,double);	//nChannels==3,Gray_Rotate
void save_graying(IplImage *);				 //nChannels==1,save the graying bitmap
void save_bitmap(IplImage *);				 //nChannels==3,save the colourful bitmap
void menu_dis();    //the menu_display

int main()
{
	int choice;
	double angle;
	char s,ss;
	IplImage* img;
	IplImage* img1;
	while(1)
	{
		menu_dis();
		printf("Please input your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				img=cvLoadImage("./001.bmp",1);
				img1=turn_Graying(img);
				cvNamedWindow("turn_Graying imshow",CV_WINDOW_AUTOSIZE);
				cvShowImage("turn_Graying imshow", img1);
				cvWaitKey(1000);
				cvDestroyWindow("turn_Graying imshow");
				printf("turn_Graying succeed!\n");
				while(1)
				{
					printf("Would you like to save it?:(Y/N)");
					getchar();
					scanf("%c",&s);
					if(toupper(s)=='Y')
					{
						img1=cvLoadImage("./001.bmp",0);
						save_graying(img1);
						cvReleaseImage(&img1);
						printf("turn_Graying file has saved!\n");
						printf("press any key to continue,and it will clear the screen...\n");
						getchar();getchar();
						break;
					}
					else if(toupper(s)=='N')
					{
						cvReleaseImage(&img1);
						printf("press any key to continue,and it will clear the screen\n");
						getchar();getchar();
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
					}
				}
				break;
			case 2:
				printf("Input an angle:");
				scanf("%lf",&angle);
				img=cvLoadImage("./001.bmp",0);
				img1=Gray_Rotate_image(img,angle);
				cvNamedWindow("Gray_Rotate_image imshow",CV_WINDOW_AUTOSIZE);
				cvShowImage("Gray_Rotate_image imshow", img1);
				cvWaitKey(1000);
				cvDestroyWindow("Gray_Rotate_image imshow");
				printf("Gray_Rotate_image succeed!\n");
				while(1)
				{
					printf("Would you like to save it?:(Y/N)");
					getchar();
					scanf("%c",&s);
					if(toupper(s)=='Y')
					{
						save_graying(img1);
						cvReleaseImage(&img1);
						printf("Gray_Rotate_image file has saved!\n");
						printf("press any key to continue,and it will clear the screen...\n");
						getchar();getchar();
						break;
					}
					else if(toupper(s)=='N')
					{
						cvReleaseImage(&img1);
						printf("press any key to continue,and it will clear the screen\n");
						getchar();getchar();
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
					}
				}
				break;
			case 3:
				printf("Input an angle:");
				scanf("%lf",&angle);
				img=cvLoadImage("./001.bmp",1);
				img1=Colour_Rotate_image(img,angle);
				cvNamedWindow("Colour_Rotate_image imshow",CV_WINDOW_AUTOSIZE);
				cvShowImage("Colour_Rotate_image imshow", img1);
				cvWaitKey(1000);
				cvDestroyWindow("Colour_Rotate_image imshow");
				printf("Colour_Rotate_image succeed!\n");
				while(1)
				{
					printf("Would you like to save it?:(Y/N)");
					getchar();
					scanf("%c",&s);
					if(toupper(s)=='Y')
					{
						save_bitmap(img1);
						cvReleaseImage(&img1);
						printf("Colour_Rotate_image file has saved!\n");
						printf("press any key to continue,and it will clear the screen...\n");
						getchar();getchar();
						break;
					}
					else if(toupper(s)=='N')
					{
						cvReleaseImage(&img1);
						printf("press any key to continue,and it will clear the screen\n");
						getchar();getchar();
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
					}
				}
				break;
			case 4:
				printf("»Ò¶È¾µÏñ»¹ÊÇ²ÊÉ«¾µÏñ£¬ÇëÑ¡Ôñ:\n");
				printf("Graying_mirror or Colourful_mirror?:(G/C)");
				while(1)
				{
					getchar();ss=getchar();
					if(toupper(ss)=='G')
					{
						img=cvLoadImage("./001.bmp",0);
						img1=Gray_Horizontal_mg(img);
						break;
					}
					else if(toupper(ss)=='C')
					{
						img=cvLoadImage("./001.bmp",1);
						img1=Colour_Horizontal_mg(img);
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
						continue;
					}
				}
				cvNamedWindow("Horizontal_mg imshow",CV_WINDOW_AUTOSIZE );
				cvShowImage("Horizontal_mg imshow", img1);
				cvWaitKey(1000);
				cvDestroyWindow("Horizontal_mg imshow");
				printf("Horizontal_mg succeed!\n");
				while(1)
				{
					printf("Would you like to save it?:(Y/N)");
					getchar();
					scanf("%c",&s);
					if(toupper(s)=='Y')
					{
						if(toupper(ss)=='G')
							save_graying(img1);
						else
							save_bitmap(img1);
						cvReleaseImage(&img1);
						printf("Horizontal_mg file has saved!\n");
						printf("press any key to continue,and it will clear the screen...\n");
						getchar();getchar();
						break;
					}
					else if(toupper(s)=='N')
					{
						cvReleaseImage(&img1);
						printf("press any key to continue,and it will clear the screen\n");
						getchar();getchar();
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
						continue;
					}
				}
				break;
			case 5:
				printf("»Ò¶È¾µÏñ»¹ÊÇ²ÊÉ«¾µÏñ£¬ÇëÑ¡Ôñ:\n");
				printf("Graying_mirror or Colourful_mirror?:(G/C)");
				while(1)
				{
					getchar();ss=getchar();
					if(toupper(ss)=='G')
					{
						img=cvLoadImage("./001.bmp",0);
						img1=Gray_Vertical_mg(img);
						break;
					}
					else if(toupper(ss)=='C')
					{
						img=cvLoadImage("./001.bmp",1);
						img1=Colour_Vertical_mg(img);
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
						continue;
					}
				}
				cvNamedWindow("Vertical_mg imshow",CV_WINDOW_AUTOSIZE );
				cvShowImage("Vertical_mg imshow", img1);
				cvWaitKey(1000);
				cvDestroyWindow("Vertical_mg imshow");
				printf("Vertical_mg succeed!\n");
				while(1)
				{
					printf("Would you like to save it?:(Y/N)");
					getchar();
					scanf("%c",&s);
					if(toupper(s)=='Y')
					{
						if(toupper(ss)=='G')
							save_graying(img1);
						else
							save_bitmap(img1);
						cvReleaseImage(&img1);
						printf("Vertical_mg file has saved!\n");
						printf("press any key to continue,and it will clear the screen...\n");
						getchar();getchar();
						break;
					}
					else if(toupper(s)=='N')
					{
						cvReleaseImage(&img1);
						printf("press any key to continue,and it will clear the screen\n");
						getchar();getchar();
						break;
					}
					else
					{
						printf("Input error,please input again:\n");
						continue;
					}
				}
				break; 
			case 0:
				printf("Run this .exe succeed!\n");
				exit(0);
			default:
				printf("Input error,press any key to iuput again!\n");
				getchar();getchar();
				continue;
		}
	}
	return 0;
}