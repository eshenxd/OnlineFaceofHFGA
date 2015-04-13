/*
 * 代码功能：获取合肥公安读卡器获取的照片的姓名和身份证号码
 * 代码作者：Ethan
 * 编写时间：2014/04/09
 */

#ifndef _GET_CARD_INFO_H_
#define _GET_CARD_INFO_H_

#include "getFiles.h"

#include <iostream>
#include "header.h"

#include <string>
#include <vector>

class Card_Info
{
public:
	Card_Info(std::string );
	~Card_Info();

	bool flag;

	std::string get_card_name()const; //获取照片的姓名
	std::string get_card_number()const; //获取照片的身份证号码
	IplImage* get_card_pic();//获取身份证照片

	void detectAddFile();
private:

	std::string FoldPath;//FoldPath为身份证读卡机保存照片的位置，在读卡机软件系统设定中设置
	std::string ImagePath;
	std::string imageName;
	std::string name;
	std::string card_number;

	IplImage* card_pic;

};



#endif