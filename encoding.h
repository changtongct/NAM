#include <highgui.h>
#include <cv.h>  
#include <cvaux.h>
#include <math.h>
#include "commonfile.h"

#ifndef M
#define M 280
#define N 280
#endif

extern char Q[60000];

void FlagMatrixEncoding(int flag[M][N]);