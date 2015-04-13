#ifndef _SHOW_COMPARE_RESULT_H_
#define _SHOW_COMPARE_RESULT_H_

#include "header.h"
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

#define SHOW_WIDTH 200
#define SHOW_HEGHT 200



class ShowResult
{
public:
	ShowResult(People people);
	~ShowResult();

	void show_result();
	bool show_judge();
	void save_result(IplImage* src_img);

private:
	IplImage* img_result_show;//��һ��Ϊ��ʾͼƬ��С��200x200��
	IplImage* show_image;//  ע��ͼƬ
	IplImage* cardPic;//���֤��Ƭ

	People show_message;//ע����Ϣ

};

#endif /*_SHOW_COMPARE_RESULT_H_*/