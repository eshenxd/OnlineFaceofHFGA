#include "register.h"


using namespace std;

#define MAX_FEATURE_SIZE 256

void  Register::register_init()
{
	SavePath="../Register/";

	ImagePath=SavePath+"image/";

	InfoFilePath=SavePath+"file/";

	CardNumPath=SavePath+"cardnum/";
}

void Register::save_register_info(People people)
{
	string ImagePath_tmp=ImagePath+people.name+".jpg";
	string InfoFilePath_tmp=InfoFilePath+people.name+".dat";
	string CardNumPath_tmp=CardNumPath+people.name+".dat";
	string CardPicPath_tmp=ImagePath+"card.jpg";
	
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
void Register::load_register_info(vector<People>&people)
{
	vector<string>ImgFilePath;
	vector<string>FeatureFilePath;
	vector<string>CardNumFilePath;

	People tmp;

	tmp.feature=new double[MAX_FEATURE_SIZE];

	getFiles(ImagePath,ImgFilePath);
	getFiles(InfoFilePath,FeatureFilePath);
	getFiles(CardNumPath,CardNumFilePath);

	for(unsigned int ix=0;ix<FeatureFilePath.size();++ix)
	{
		char* fname=new char[20];
		_splitpath(FeatureFilePath[ix].c_str(),NULL,NULL,fname,NULL);

		tmp.name=(string)fname;

		ifstream fpIn;
		fpIn.open(FeatureFilePath[ix].c_str(),ios::in);

		for(int j=0;j<MAX_FEATURE_SIZE;++j)
		{
			fpIn>>tmp.feature[j];
		}
		fpIn.close();

		fpIn.open(CardNumFilePath[ix].c_str(),ios::in);
		fpIn>>tmp.cardNum;
		fpIn.close();


		people.push_back(tmp);
	}

}

