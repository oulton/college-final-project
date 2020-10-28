#include <highgui.h>
#include <cv.h>
#include <stdio.h>
#include <math.h>
#define PI 3.1415926
//the simple turnGraying
IplImage* turn_Graying(IplImage* img)
{
    int col,row; 
    for( row= 0; row < img->height; row++ )
    {
        for ( col = 0; col < img->width; col++ )
        { 
            img->imageData[img->widthStep * row + col * 3]=
                img->imageData[img->widthStep * row + col * 3 + 1]=
                img->imageData[img->widthStep * row + col * 3 + 2]=
                0.212671*img->imageData[img->widthStep * row + col * 3]+
                0.715160*img->imageData[img->widthStep * row + col * 3 + 1]+
                0.072169*img->imageData[img->widthStep * row + col * 3 + 2];
            //0.072169B+ 0.715160G+ 0.212671R
        }
    }
    return img;
}

//nChannels==1,Horizontal_mirror
IplImage* Gray_Horizontal_mg(IplImage* img)
{
    IplImage *img1=cvCloneImage(img);

    int col,row;
    for(row=0;row<img->height;row++)
    {
        for(col=0;col<img->width;col++)
        {
            img1->imageData[img1->widthStep*row+col]=img->imageData[img->widthStep*row+ (img->width-col-1)];
            img1->imageData[img1->widthStep*row+col+1]=img->imageData[img->widthStep*row+ (img->width-col-1)+1];
            img1->imageData[img1->widthStep*row+col+2]=img->imageData[img->widthStep*row+ (img->width-col-1)+2];
        }
    }
    return img1;
}

//nChannels==3,Horizontal_mirror
IplImage* Colour_Horizontal_mg(IplImage* img)
{
    IplImage *img1=cvCloneImage(img);

    int col,row;
    for(row=0;row<img->height;row++)
    {
        for(col=0;col<img->width;col++)
        {
            img1->imageData[img1->widthStep*row+col*3]=img->imageData[img->widthStep*row+ (img->width-col-1)*3];
            img1->imageData[img1->widthStep*row+col*3+1]=img->imageData[img->widthStep*row+ (img->width-col-1)*3+1];
            img1->imageData[img1->widthStep*row+col*3+2]=img->imageData[img->widthStep*row+ (img->width-col-1)*3+2];
        }
    }
    return img1;
}

//nChannels==1,Vertical_mirror
IplImage* Gray_Vertical_mg(IplImage* img)
{
	IplImage *img1=cvCloneImage(img);
	int col,row; 
	for(row=0;row<img->height;row++) 
	{ 
		for(col=0;col<img->width;col++) 
		{
			img1->imageData[img1->widthStep*row+col]=img->imageData[img->widthStep*(img->height-row-1)+ col];
			img1->imageData[img1->widthStep*row+col+1]=img->imageData[img->widthStep*(img->height-row-1)+ col+1];
			img1->imageData[img1->widthStep*row+col+2]=img->imageData[img->widthStep*(img->height-row-1)+ col+2];
		}   
	} 
	return img1;
}

//nChannels==3,Vertical_mirror
IplImage* Colour_Vertical_mg(IplImage* img)
{
	IplImage *img1=cvCloneImage(img);
	int col,row; 
	for(row=0;row<img->height;row++) 
	{ 
		for(col=0;col<img->width;col++) 
		{
			img1->imageData[img1->widthStep*row+col*3]=img->imageData[img->widthStep*(img->height-row-1)+ col*3];
			img1->imageData[img1->widthStep*row+col*3+1]=img->imageData[img->widthStep*(img->height-row-1)+ col*3+1];
			img1->imageData[img1->widthStep*row+col*3+2]=img->imageData[img->widthStep*(img->height-row-1)+ col*3+2];
		}   
	} 
	return img1;
}

//nChannels==1,Gray_Rotate_image
IplImage* Gray_Rotate_image(IplImage* img,double a)
{
	IplImage *img1=cvCloneImage(img);
   
	int col,row,m,n,R,G,B; 
	float x,y,p,q;
	double cosa=cos(a*PI/180.0);
	double sina=sin(a*PI/180.0);
	int width=img->width;
	int height=img->height;
	for(row=-height/2;row<height/2;row++) 
	{ 
		for (col=-width/2;col<width/2;col++) 
		{ 	//get the rotate origin
			x=(float)(col*cosa-row*sina);
			y=(float)(col*sina+row*cosa);
			//get the max int x,y
			if(y>0) m=(int)y;
			else m=(int)(y-1);
			if(x>0) n=(int)x;
			else n=(int)(x-1);
			//get the d-value
			p=x-n;
			q=y-m;
			if(q==1)
			{
				q=0;
				m=m+1;
			}
			if(p==1)
			{
				p=0;
				n=n+1;
			}
			if((m>=-height/2)&&(m<height/2)&&(n>=-width/2)&&(n<width/2))//take the origin as the center 
			{
				R=(int)((1.0-q)*((1.0-p)*img->imageData[img->widthStep*(m+height/2)+(n+width/2)]
					+p*img->imageData[img->widthStep*(m+height/2)+(n+width/2+1)])
					+q*((1.0-p)*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2)]
					+p*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2+1)]));
				G=(int)((1.0-q)*((1.0-p)*img->imageData[img->widthStep*(m+height/2)+(n+width/2)+1]
					+p*img->imageData[img->widthStep*(m+height/2)+(n+width/2+1)+1])
					+q*((1.0-p)*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2)+1]
					+p*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2+1)+1]));
				B=(int)((1.0-q)*((1.0-p)*img->imageData[img->widthStep*(m+height/2)+(n+width/2)+2]
					+p*img->imageData[img->widthStep*(m+height/2)+(n+width/2+1)+2])
					+q*((1.0-p)*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2)+2]
					+p*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2+1)+2]));
			}
			else R=G=B=0; //rotate out of the size
			//if(R<0||G<0||B<0) R=G=B=0;
			if(R>255||G>255||B>255) R=G=B=255; //out of the RGB,turn white
			img1->imageData[img1->widthStep*(row+height/2)+(col+width/2)]=R;
			img1->imageData[img1->widthStep*(row+height/2)+(col+width/2)+1]=G;
			img1->imageData[img1->widthStep*(row+height/2)+(col+width/2)+2]=B;
		}
	} 
	return img1;
}

//nChannels==3,Gray_Rotate_image
IplImage* Colour_Rotate_image(IplImage* img,double a)
{
	IplImage *img1=cvCloneImage(img);
   
	int col,row,m,n,R,G,B; 
	float x,y,p,q;
	double cosa=cos(a*PI/180.0);
	double sina=sin(a*PI/180.0);
	int width=img->width;
	int height=img->height;

	for(row=-height/2;row<height/2;row++) 
	{ 
		for (col=-width/2;col<width/2;col++) 
		{ 
			x=(float)(col*cosa-row*sina);
			y=(float)(col*sina+row*cosa);
			if(y>0) m=(int)y;
			else m=(int)(y-1);
			if(x>0) n=(int)x;
			else n=(int)(x-1);
			p=x-n;
			q=y-m;
			if(q==1)
			{
				q=0;
				m=m+1;
			}
			if(p==1)
			{
				p=0;
				n=n+1;
			}
			if((m>=-height/2)&&(m<height/2)&&(n>=-width/2)&&(n<width/2))
			{
				R=(int)((1.0-q)*((1.0-p)*img->imageData[img->widthStep*(m+height/2)+(n+width/2)*3]
					+p*img->imageData[img->widthStep*(m+height/2)+(n+width/2+1)*3])
					+q*((1.0-p)*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2)*3]
					+p*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2+1)*3]));
				G=(int)((1.0-q)*((1.0-p)*img->imageData[img->widthStep*(m+height/2)+(n+width/2)*3+1]
					+p*img->imageData[img->widthStep*(m+height/2)+(n+width/2+1)*3+1])
					+q*((1.0-p)*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2)*3+1]
					+p*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2+1)*3+1]));
				B=(int)((1.0-q)*((1.0-p)*img->imageData[img->widthStep*(m+height/2)+(n+width/2)*3+2]
					+p*img->imageData[img->widthStep*(m+height/2)+(n+width/2+1)*3+2])
					+q*((1.0-p)*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2)*3+2]
					+p*img->imageData[img->widthStep*(m+height/2+1)+(n+width/2+1)*3+2]));
			}
			else R=G=B=0;
			//if(R<0||G<0||B<0) R=G=B=0;
			if(R>255||G>255||B>255) R=G=B=255;
			img1->imageData[img1->widthStep*(row+height/2)+(col+width/2)*3]=R;
			img1->imageData[img1->widthStep*(row+height/2)+(col+width/2)*3+1]=G;
			img1->imageData[img1->widthStep*(row+height/2)+(col+width/2)*3+2]=B;
		}
	}
	return img1;
}
