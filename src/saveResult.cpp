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
	//��ȡ��ǰ�ļ������
	string index = getIndex();
	string savePath = "../results/" + index +"/";
	
	//�½��ļ���
	_mkdir(savePath.c_str());

	//�����ļ������
	setIndex();

	string resultFaceName = "result.jpg";
	string queryFaceName = "query.jpg";

	string resultFacePath = savePath + resultFaceName;
	string queryFacePath = savePath + queryFaceName;

	//����ͼ��
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