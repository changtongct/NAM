#include <highgui.h>
#include <cv.h>  
#include <cvaux.h>
#include "commonfile.h"

extern int flag[M][N];
extern int Num;

int find_horizontal(IplImage* grayimg, IplImage* segmented_img, double Threshold);