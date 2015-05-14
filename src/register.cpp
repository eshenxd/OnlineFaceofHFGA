#include "register.h"


using namespace std;

#define MAX_FEATURE_SIZE 256

void  Register::register_init()
{
	SavePath="../Register/";

	ImagePath=SavePath+"image/";

	InfoFilePath=SavePath+"file/";

	CardNumPath=SavePath+"cardnum/";

	CardPicPath=SavePath+"cardpic/";
}

void Register::save_register_info(People people)
{
	string ImagePath_tmp=ImagePath+people.name+".jpg";
	string InfoFilePath_tmp=InfoFilePath+people.name+".dat";
	string CardNumPath_tmp=CardNumPath+people.name+".dat";
	string CardPicPath_tmp=CardPicPath+people.name+".jpg";
	
	//保存注册图像
	cvSaveImage(ImagePath_tmp.c_str(),people.image);

	//保存注册特征
	ofstream fpOut(InfoFilePath_tmp.c_str(),ios::out);
	for(int i=0;i<MAX_FEATURE_SIZE;++i)
	{
		fpOut<<people.feature[i]<<endl;
	}
	fpOut.close();

	//保存注册身份证号
	//ofstream fpOut1(CardNumPath_tmp.c_str(),ios::out);
	fpOut.open(CardNumPath_tmp,ios::out);
	fpOut<<people.cardNum<<endl;
	fpOut.close();

	//保存身份证的照片
	cvSaveImage(CardPicPath_tmp.c_str(),people.card_pic);
	
}



//读注册文件
bool Register::load_register_info(vector<People>&people)
{
	vector<string>ImgFilePath;
	vector<string>FeatureFilePath;
	vector<string>CardNumFilePath;
	vector<string>CardPicFilePath;
	people.clear();

	People tmp;

	//tmp.feature=new double[MAX_FEATURE_SIZE];

	getFiles(ImagePath,ImgFilePath);
	getFiles(InfoFilePath,FeatureFilePath);
	//getFiles(CardNumPath,CardNumFilePath);
	//getFiles(CardPicPath,CardPicFilePath);

	if(ImgFilePath.size()!=FeatureFilePath.size())
	{
		cout<<"注册文件库已损坏，请重新注册！\n";
		return false;
	}

	for(unsigned int ix=0;ix<FeatureFilePath.size();++ix)
	{
		char* fname=new char[20];
		_splitpath(FeatureFilePath[ix].c_str(),NULL,NULL,fname,NULL);

		//姓名
		tmp.name=(string)fname;

		//特征
		ifstream fpIn;
		fpIn.open(FeatureFilePath[ix].c_str(),ios::in);

		for(int j=0;j<MAX_FEATURE_SIZE;++j)
		{
			fpIn>>tmp.feature_c[j];
		}
		fpIn.close();

		//身份证号
		//fpIn.open(CardNumFilePath[ix].c_str(),ios::in);
		//fpIn>>tmp.cardNum;
		//fpIn.close();

		//视频图片
		tmp.image=cvLoadImage(ImgFilePath[ix].c_str(),1);
		//tmp.card_pic=cvLoadImage(CardPicFilePath[ix].c_str(),1);

		people.push_back(tmp);
	}

	return true;
}