/*
 *  saveResult.cpp
 *  save the face retrival results
 *  Ethan
 *  2015-06-29
 */

#include "saveResult.h"

#include <fstream>
#include <io.h>

using namespace std;

void save_result(IplImage* result_face, IplImage* query_face)
{
	//获取当前文件夹序号
	string index = getIndex();
	string savePath = "../results/" + index +"/";
	
	//新建文件夹
	_mkdir(savePath.c_str());

	//更改文件夹序号
	setIndex();

	string resultFaceName = "result.jpg";
	string queryFaceName = "query.jpg";

	string resultFacePath = savePath + resultFaceName;
	string queryFacePath = savePath + queryFaceName;

	//保存图像
	cvSaveImage(resultFacePath.c_str(), result_face);
	cvSaveImage(queryFacePath.c_str(), query_face);

	return;

}

string getIndex()
{
	string configfile = "../results/index.txt";
	string index;

	ifstream fp;
	fp.open(configfile.c_str(), ios::in);
	fp >> index;
	fp.close();

	//cout << index << endl;
	return index;
}

void setIndex()
{
	int index;
	string configfile = "../results/index.txt";

	ifstream fp;
	fp.open(configfile.c_str(), ios::in);
	fp >> index;
	fp.close();

	index++;

	ofstream fp1;
	fp1.open(configfile.c_str(), ios::out);
	fp1 << index;
	fp1.close();

	return;
}