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

int main(int argc,char** argv)//�ֱ�����1.ԭͼ 2.EPSILON 3.���ַ�ʽ
{
	IplImage* img;
	if( argc==4 && (img=cvLoadImage( argv[1], 0))!=0 )   //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
	{
		cout << "ͼƬ�ѱ���ȷ��ȡ����������Ҳ��ȷ��" << endl;
	
		int k=0;//�ָ�������
		unsigned int time1,time2;
		const char* original_img = argv[1];
		double Threshold = atof(argv[2]);
		//////////////////////////////////////////��ʾԭʼͼ��
		IplImage* colorimg = cvLoadImage(original_img);
		cvNamedWindow("ԭͼ",CV_WINDOW_AUTOSIZE);
		cvShowImage("ԭͼ",colorimg);
		//////////////////////////////////////////��ʾ�Ҷ�ͼ��
		IplImage* grayimg = cvCreateImage(cvGetSize(colorimg), IPL_DEPTH_8U, 1);
		cvCvtColor(colorimg,grayimg,CV_BGR2GRAY);

		//IplImage* Binaryimg = cvCreateImage(cvGetSize(grayimg), IPL_DEPTH_8U, 1);
		//cvThreshold(grayimg, Binaryimg, 100, 255, CV_THRESH_BINARY);//��ֵ��

		cvNamedWindow("�Ҷ�ͼ",CV_WINDOW_AUTOSIZE);
		cvShowImage("�Ҷ�ͼ",grayimg);

		IplImage* segmented_img = cvCreateImage(cvGetSize(grayimg), IPL_DEPTH_8U, 1);
		time1 = clock();

		switch (atoi(argv[3]))
		{
		case 1 :
			k = find_horizontal( grayimg, segmented_img, Threshold);//����ͼ��ˮƽ���ȷָ��
			printf("��ֵ��%f\nˮƽ���ȷָ�\n",Threshold);
			break;
		case 2 :
			k = find_oblique( grayimg, segmented_img, Threshold);//����ͼ��б�����ȷָ��
			printf("��ֵ��%f\nб�����ȷָ�\n",Threshold);
			break;
		default:
			break;
		}

		time2 = clock();

		//OutputMatrixToTextfile(flag);		//�����־����txt�ļ���
		//FlagMatrixEncoding(flag);			//����־�������
		//OutputEncodedFlagToTextfile(Q);
		//OutputGreyValueRecordToTextfile();

		printf("Elapsed time: %u ms\n",time2-time1);//��ʾ�ָ���̻��ѵ�ʱ��
		printf("%d\n",k);							//��ʾ�ָ����
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
		cout << "ͼƬ�����ڻ��������ȷ��"<< endl;
		return -1;
	}
}
