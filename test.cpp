#include <highgui.h>
#include <cv.h>  
#include <cvaux.h>
#include <time.h>
#include "commonfile.h"
#include "horizontal_priority.h"
#include "oblique_priority.h"
#include "encoding.h"

using namespace std;

int flag[M][N]={0};
char Q[60000] = {0};

int main(int argc,char** argv)//分别输入1.原图 2.EPSILON 3.划分方式
{
	IplImage* img;
	if( argc==4 && (img=cvLoadImage( argv[1], 0))!=0 )   //将源彩色图像img转化成目标灰色图像读入
	{
		cout << "图片已被正确读取，参数数量也正确！" << endl;
	
		int k=0;//分割块的数量
		unsigned int time1,time2;
		const char* original_img = argv[1];
		double Threshold = atof(argv[2]);
		//////////////////////////////////////////显示原始图像
		IplImage* colorimg = cvLoadImage(original_img);
		cvNamedWindow("原图",CV_WINDOW_AUTOSIZE);
		cvShowImage("原图",colorimg);
		//////////////////////////////////////////显示灰度图像
		IplImage* grayimg = cvCreateImage(cvGetSize(colorimg), IPL_DEPTH_8U, 1);
		cvCvtColor(colorimg,grayimg,CV_BGR2GRAY);

		//IplImage* Binaryimg = cvCreateImage(cvGetSize(grayimg), IPL_DEPTH_8U, 1);
		//cvThreshold(grayimg, Binaryimg, 100, 255, CV_THRESH_BINARY);//二值化

		cvNamedWindow("灰度图",CV_WINDOW_AUTOSIZE);
		cvShowImage("灰度图",grayimg);

		IplImage* segmented_img = cvCreateImage(cvGetSize(grayimg), IPL_DEPTH_8U, 1);
		time1 = clock();

		switch (atoi(argv[3]))
		{
		case 1 :
			k = find_horizontal( grayimg, segmented_img, Threshold);//调用图像水平优先分割函数
			printf("阈值：%f\n水平优先分割\n",Threshold);
			break;
		case 2 :
			k = find_oblique( grayimg, segmented_img, Threshold);//调用图像斜向优先分割函数
			printf("阈值：%f\n斜向优先分割\n",Threshold);
			break;
		default:
			break;
		}

		time2 = clock();

		//OutputMatrixToTextfile(flag);		//输出标志矩阵到txt文件中
		//FlagMatrixEncoding(flag);			//将标志矩阵编码
		//OutputEncodedFlagToTextfile(Q);
		//OutputGreyValueRecordToTextfile();

		printf("Elapsed time: %u ms\n",time2-time1);//显示分割过程花费的时间
		printf("%d\n",k);							//显示分割块数
		cvNamedWindow("segmented_img",CV_WINDOW_AUTOSIZE);
		cvShowImage("segmented_img",segmented_img);	
		/*for(k=0;k<100;k++)
			printf("%d,%d,%d,%d\n",P[k].topleft,P[k].topright,P[k].bottomleft,P[k].bottomright);*/
		cvWaitKey(0);
		cvReleaseImage(&grayimg);
		cvReleaseImage(&segmented_img);
		cvDestroyAllWindows();

		return 0;
	}
	else
	{
		cout << "图片不存在或参数不正确！"<< endl;
		return -1;
	}
}
