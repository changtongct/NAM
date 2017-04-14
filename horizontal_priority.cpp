#include"horizontal_priority.h"

int find_horizontal(IplImage* grayimg, IplImage* segmented_img, double Threshold)
{
	int x1, x2, y1, y2;
	int x2_h, y2_h, x2_v, y2_v;
	int f1 = 0;
	int k = 0;
	long int area_h = 0, area_v = 0;

	for(y1=0;y1<grayimg->height;y1++)
		for(x1=0;x1<grayimg->width;x1++)
		{
			if(flag[y1][x1]==0)						//已找到符合要求的下一个(x1,y1)
			{
////////////////////////////////////////////////////////////////////////////////////////////////////////////行优先遍历，并计算所得块的面积
				x2_h = x1;
				y2_h = y1;
				while( (x2_h<grayimg->width) && (flag[y1][x2_h]==0) )
				{
					if(judgement( x1, x2_h, y1, y2_h, grayimg, Threshold)==1)
					{
						break;
					}
					x2_h++;
				}
				x2_h--;

				while( y2_h<grayimg->height )
				{
					if(judgement( x1, x2_h, y1, y2_h, grayimg, Threshold)==1)
					{
						break;
					}
					y2_h++;
				}
				y2_h--;

				/*f1=0;
				for(y2_h=y1;y2_h<grayimg->height;y2_h++)
				{
					if(f1==0)
					{
						for(x2_h=x1;x2_h<grayimg->width;x2_h++)
						{
							if(judgement(x1,x2_h,y1,y2_h,grayimg)==1)
							{
								f1=1;
								x2_h--;
								break;
							}
							if(((x2_h+1)==grayimg->width)||(flag[y2_h][x2_h+1]!=0))
							{
								f1=1;
								break;
							}
						}
					}
					else
					{
						if(judgement(x1,x2_h,y1,y2_h,grayimg)==1)
						{
							y2_h--;
							break;
						}
						if((y2_h+1)==grayimg->height)
						{
							break;
						}
					}
				}*/
				area_h = (y2_h-y1+1)*(x2_h-x1+1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////列优先遍历，并计算所得块的面积
				x2_v = x1;
				y2_v = y1;

				while( y2_v<grayimg->height )
				{
					if(judgement( x1, x2_v, y1, y2_v, grayimg, Threshold)==1)
					{
						break;
					}
					y2_v++;
				}
				y2_v--;

				while( (x2_v<grayimg->width) && (flag[y1][x2_v]==0) )
				{
					if(judgement( x1, x2_v, y1, y2_v, grayimg, Threshold)==1)
					{
						break;
					}
					x2_v++;
				}
				x2_v--;

				/*f1=0;
				for(x2_v=x1;x2_v<grayimg->width;x2_v++)
				{
					if(f1==0)
					{
						for(y2_v=y1;y2_v<grayimg->height;y2_v++)
						{
							if(judgement(x1,x2_v,y1,y2_v,grayimg)==1)
							{
								f1=1;
								y2_v--;
								break;
							}
							if((y2_v+1)==grayimg->height)
							{
								f1=1;
								break;
							}
						}
					}
					else
					{
						if(flag[y1][x2_v]==0)
						{
							if(judgement(x1,x2_v,y1,y2_v,grayimg)==1)
							{
								y2_v--;
								break;
							}
						}
						if(((x2_v+1)==grayimg->width)||(flag[y1][x2_v+1]!=0))
						{
							break;
						}
					}
				}*/
				area_v = (y2_v-y1+1)*(x2_v-x1+1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
				/*if(Num<100)
				{
					printf("(%d,%d),(%d,%d)\n",x1,y1,x2,y2);
					Num++;
				}*/
				GreyValueRecord( x1, x2, y1, y2, grayimg);
				flag[y1][x1]=1;
				flag[y2][x2]=2;
				matrixprocess(x1, x2, y1, y2, flag);
				segmentdisplay(x1, x2, y1, y2, segmented_img);
				k++;
				x1=x2;
			}
		}
	return k;
}