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
	
	//����ע��ͼ��
	cvSaveImage(ImagePath_tmp.c_str(),people.image);

	//����ע������
	ofstream fpOut(InfoFilePath_tmp.c_str(),ios::out);
	for(int i=0;i<MAX_FEATURE_SIZE;++i)
	{
		fpOut<<people.feature[i]<<endl;
	}
	fpOut.close();

	//����ע�����֤��
	//ofstream fpOut1(CardNumPath_tmp.c_str(),ios::out);
	fpOut.open(CardNumPath_tmp,ios::out);
	fpOut<<people.cardNum<<endl;
	fpOut.close();

	//�������֤����Ƭ
	cvSaveImage(CardPicPath_tmp.c_str(),people.card_pic);
	
}



//��ע���ļ�
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
		cout<<"ע���ļ������𻵣�������ע�ᣡ\n";
		return false;
	}

	for(unsigned int ix=0;ix<FeatureFilePath.size();++ix)
	{
		char* fname=new char[20];
		_splitpath(FeatureFilePath[ix].c_str(),NULL,NULL,fname,NULL);

		//����
		tmp.name=(string)fname;

		//����
		ifstream fpIn;
		fpIn.open(FeatureFilePath[ix].c_str(),ios::in);

		for(int j=0;j<MAX_FEATURE_SIZE;++j)
		{
			fpIn>>tmp.feature_c[j];
		}
		fpIn.close();

		//���֤��
		//fpIn.open(CardNumFilePath[ix].c_str(),ios::in);
		//fpIn>>tmp.cardNum;
		//fpIn.close();

		//��ƵͼƬ
		tmp.image=cvLoadImage(ImgFilePath[ix].c_str(),1);
		//tmp.card_pic=cvLoadImage(CardPicFilePath[ix].c_str(),1);

		people.push_back(tmp);
	}

	return true;
}