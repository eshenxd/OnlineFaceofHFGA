/*
 *  代码功能：提取图片的cnn特征
 *  代码作者：Ethan
 *  编写时间：2015/04/09
*/

#include "get_cnn_feature.h"


using namespace std;
using namespace cv;


int get_cnn_feature(Mat imgSrc ,double* feature)
{
	
	Mat imgresize(60,60,CV_64FC3);

	if(imgSrc.empty()) //判断图片调入是否成功
		return -1; //调入图片失败则退出
	Size sz=Size(60,60);
	resize(imgSrc,imgresize,sz);

	double x[10800];

	int h=imgresize.rows;
	int w=imgresize.cols;
	int c=imgresize.channels();
	int k=0;
	double l;
	for (int ch = 0; ch < c; ch++)  
	{  
		for (int j = 0; j < w; j++)  
		{  
			for (int i = 0; i < h; i++)  
			{
				l=(double)imgresize.row(i).col(j).data[c - 1- ch];
				x[k] =l/255;  
				k++;
			}  
		}  
	}
	emxArray_real_T *fv=emxCreate_real_T(1,256);
	gen_feature(x,fv);
	
	double *y=new double[256];
	y=fv->data;

	copy(y,y+256,feature);

	delete[] y;

	return 0;
}
