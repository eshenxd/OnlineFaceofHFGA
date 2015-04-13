#include "getCardInfo.h"

using namespace std;

void Card_Info::detectAddFile()
{
	vector<string>files;
	files.clear();

	getFiles(FoldPath,files);

	if(files.size()==1)
		{
			ImagePath=files[0];
			card_pic=cvLoadImage(files[0].c_str(),1);
			flag=true;
			remove(files[0].c_str());
	    }

	else if(files.size()>1)
	{
		for(unsigned int ix=0;ix<files.size();ix++)
			remove(files[ix].c_str());
	}

	char fname[50];
	_splitpath(ImagePath.c_str(),NULL,NULL,fname,NULL);

	imageName=(string)fname;
	int pos=imageName.find('(',0);
	name=imageName.substr(0,pos);
	card_number=imageName.substr(pos+1,18);
}


Card_Info::Card_Info(string path)
{
	flag=false;
	FoldPath=path;	
}

Card_Info::~Card_Info()
{

}

string Card_Info::get_card_name()const
{
	return name;
}

string Card_Info::get_card_number()const
{
	return card_number;
}

IplImage* Card_Info::get_card_pic()
{
	return card_pic;
}