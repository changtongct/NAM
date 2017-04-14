#include "oblique_priority.h"

int find_oblique(IplImage* grayimg, IplImage* segmented_img, double Threshold)
{
	int x1, y1, x2, y2;
	int x2_h, y2_h, x2_v, y2_v;
	int k = 0;
	long int area_h =0, area_v = 0;

	for(y1=0; y1< grayimg->height; y1++)
		for(x1=0; x1< grayimg->width; x1++)
		{
			if(flag[y1][x1]==0)
			{
				x2 = x1;
				y2 = y1;
				while((x2 < grayimg->width ) && (y2 < grayimg->height) && (flag[y1][x2]==0))
				{
					if(judgement( x1, x2, y1, y2, grayimg, Threshold)==1)
					{
						break;
					}
					x2++;
					y2++;
				}
				x2--;
				y2--;

/////////////////////////////////////////////////////////////////////////////////////////////
				x2_h = x2;
				y2_h = y2;
				while((x2_h < grayimg->width) && (flag[y1][x2_h]==0))
				{
					if(judgement( x1, x2_h, y1, y2_h, grayimg, Threshold)==1)
					{
						break;
					}
					x2_h++;
				}
				x2_h--;
				area_h = (y2_h-y1+1)*(x2_h-x1+1);
/////////////////////////////////////////////////////////////////////////////////////////////
				x2_v = x2;
				y2_v = y2;
				while(y2_v < grayimg->height)
				{
					if(judgement( x1, x2_v, y1, y2_v, grayimg, Threshold)==1)
					{
						break;
					}
					y2_v++;
				}
				y2_v--;
				area_v = (y2_v-y1+1)*(x2_v-x1+1);
/////////////////////////////////////////////////////////////////////////////////////////////
				if(area_h >= area_v)
				{	
					x2=x2_h;
					y2=y2_h;
				}
				else
				{
					x2=x2_v;
					y2=y2_v;
				}
				GreyValueRecord( x1, x2, y1, y2, grayimg);
				flag[y1][x1] = 1;
				flag[y2][x2] = 2;
				matrixprocess(x1, x2, y1, y2, flag);
				segmentdisplay(x1, x2, y1, y2, segmented_img);
				k++;

				x1 = x2;
			}
		}

	return k;
}