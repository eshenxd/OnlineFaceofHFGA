#include "face_compare.h"


using namespace std;

#define FEATURE_DIM 256

double cala_Similarity(double* array1 ,double* array2 );

double cala_distance(double* array1 ,double* array2 ,int m)
{
	double sum_tmp=0;
	double dis_tmp=0;

	for(int ix=0;ix<m;ix++)
	{
		sum_tmp=sum_tmp+(array1[ix]-array2[ix])*(array1[ix]-array2[ix]);
	}

	dis_tmp=sqrt(sum_tmp);

	return dis_tmp;
}
double face_compare(Main& job,People& people)
{
	vector<People>data=job.Data; 
	double* feature=job.feature;

	double Max_sim=cala_Similarity(feature,data[0].feature_c);
	people.name=data[0].name;
	people.image=data[0].image;
	people.cardNum=data[0].cardNum;
	people.card_pic=data[0].card_pic;

	int index_i;

	for(unsigned int ix=1;ix<data.size();ix++)
	{
		double sim=cala_Similarity(feature,data[ix].feature_c);

		if(sim>Max_sim)
		{
			Max_sim=sim;
			index_i=ix;

			people.name=data[ix].name;
			people.image=data[ix].image;
			people.cardNum=data[ix].cardNum;
			people.card_pic=data[ix].card_pic;
		}
	}

	return Max_sim;
}


double cala_Similarity(double* array1 ,double* array2 )
{
	double similarity=0;

	cv::FileStorage fs("bys.yaml",cv::FileStorage::READ);

	if (!fs.isOpened()) {
		return false;
	}

	cv::Mat A;
	cv::Mat G;

	fs["A"]>>A;
	fs["G"]>>G;

	cv::Mat A1;
	cv::Mat G1;

	A.convertTo(A1,CV_64FC1);
	G.convertTo(G1,CV_64FC1);

	double x=A1.at<double>(0,0);

	cv::Mat feature1(256,1,CV_64FC1,array1);
	cv::Mat feature2(256,1,CV_64FC1,array2);

	//double x=feature1.at<double>(0,0);

	/* cv::Mat a=feature1.t()*A;

	double b=a.dot(feature1);*/

	cv::Mat a=feature1.t()*A1*feature1+feature2.t()*A1*feature2-2*(feature1.t()*G1*feature2);

	double c=a.at<double>(0,0);

	return c;
}

