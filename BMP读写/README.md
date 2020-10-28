#include "bmp.h"  

const char* fileName_get = "1.bmp";
const char* fileName_out = "1 - 副本.bmp";

int main()  
{  
	ClImage* img = clLoadImage(fileName_get);  
	bool flag = clSaveImage(fileName_out, img);  
	if(flag)  
	{
		printf("save ok...\n");  
	}
	else
	{
		printf("save failure...\n");
	}
	system("pause");
	return 0;  
}  
