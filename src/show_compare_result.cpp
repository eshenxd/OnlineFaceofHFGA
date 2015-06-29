#include "show_compare_result.h"


using namespace std;


ShowResult::ShowResult(People people)
{
	img_result_show=cvCreateImage(cvSize(SHOW_WIDTH,SHOW_HEGHT),people.image->depth,people.image->nChannels);

	show_image=cvCreateImage(cvGetSize(people.image),people.image->depth,people.image->nChannels);

	//cardPic=cvCreateImage(cvSize(204,252),people.card_pic->depth,people.card_pic->nChannels);
	//cvResize(people.card_pic,cardPic);

	cvCopy(people.image,show_image);

	show_message.name=people.name;
	show_message.cardNum=people.cardNum;

}


ShowResult::~ShowResult()
{
	if(img_result_show!=NULL)
		cvReleaseImage(&img_result_show);
	if(show_image!=NULL)
		cvReleaseImage(&show_image);
	
}


void ShowResult::show_result()
{
	cvResize(show_image,img_result_show);

	cvShowImage("RESULTS",img_result_show);
	//cvShowImage("CARD",cardPic);
	cvWaitKey(2);

	cout<<"\n";
	cout<<"识别结果:"<<endl;
	cout<<"/*"<<endl;
	cout<<"         姓名："+show_message.name<<endl;
	//cout<<"         身份证编号："+show_message.cardNum<<endl;
	cout<<"*/"<<endl;
}

bool ShowResult::show_judge()
{
	cout<<"是否签到人？（Y/N）\n";
	string judge;
	cin>>judge;

	if(judge=="Y"||judge=="y")return true;

	else
		return false;
}

