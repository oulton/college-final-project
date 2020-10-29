
const char* fileName_get = "1.bmp";
const char* fileName_out = "1 - 副本.bmp";


ClImage* img = clLoadImage(fileName_get);  
bool flag = clSaveImage(fileName_out, img);  
