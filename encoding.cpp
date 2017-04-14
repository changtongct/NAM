#include "encoding.h"

void FlagMatrixEncoding(int flag[M][N])
{
	int i, j;//遍历矩阵行和列
	char TempArray[10];//编码时每一位生成的临时字符串
	int Num_Of_Bits_First, Num_Of_Bits_Rest;//每行第一个和剩下的码位数
	int Last_Not_Zero_Place;//上一个非零的码的位置，最后得到-1的话表示全为零
	int Num = 0;

	Num_Of_Bits_First = NumberOfBits(N);
	//Num = 0;						//二进制转十进制例
	//char a[] = "11111110";		
	//Num=BinaryToDecimal(a, 8);
	//printf("%d\n",Num);
	//int a = 678;					//十进制转二进制例
	//char b[10]={0};
	//DecimalToTenBinary(a,b);
	//for(int c=0;c<10;c++)
	//{
	//	printf("%c",b[c]);
	//}
	//printf("\n");
	int a = 0;
	for(i=0;i<M;i++)
	{
		Last_Not_Zero_Place = -1;
		for(j=0;j<N;j++)
		{
			if(flag[i][j]!=3)
			{		
				if(Last_Not_Zero_Place == -1)
				{
					DecimalToTenBinary( j, TempArray);//j转为2进制;
					for(int k=0 ; k<Num_Of_Bits_First ; k++)
					{
						Q[Num] = TempArray[k+10-Num_Of_Bits_First];
						Num++;
					}
					if(flag[i][j]==1)
					{
						Q[++Num] = '1';
						Q[++Num] = '1';
					}
					else if(flag[i][j]==2)
					{
						Q[++Num] = '1';
						Q[++Num] = '0';
						Q[++Num] = '1';
					}
					else if(flag[i][j]==-1)
					{
						Q[++Num] = '1';
						Q[++Num] = '0';
						Q[++Num] = '0';
					}
					else
					{
						printf("Error!");
					}
					Last_Not_Zero_Place = j;
				}
				else
				{
					Num_Of_Bits_Rest = NumberOfBits(N-Last_Not_Zero_Place);
					//printf("%d\n",Last_Not_Zero_Place);
					DecimalToTenBinary( (j-Last_Not_Zero_Place), TempArray);//j转为2进制;
					for(int k=0 ; k<Num_Of_Bits_Rest ; k++)
					{
						Q[Num] = TempArray[k+10-Num_Of_Bits_Rest];
						Num++;
					}
					//printf("%d\n",Num_Of_Bits_Rest);
					//cvWaitKey(0);
					if(flag[i][j]==1)
					{
						Q[++Num] = '1';
						Q[++Num] = '1';
					}
					else if(flag[i][j]==2)
					{
						Q[++Num] = '1';
						Q[++Num] = '0';
						Q[++Num] = '1';
					}
					else if(flag[i][j]==-1)
					{
						Q[++Num] = '1';
						Q[++Num] = '0';
						Q[++Num] = '0';
					}
					else
					{
						printf("Error!");
					}
					Last_Not_Zero_Place = j;
				}
			}
		}
		if(Last_Not_Zero_Place!=(N-1))
		{
			Q[++Num] = '0';
		}
		//printf("%d\n",++a);
		//printf("%d\n",Num);
		//cvWaitKey(0);
	}
}