/*
 * ���빦�ܣ���ȡ�Ϸʹ�����������ȡ����Ƭ�����������֤����
 * �������ߣ�Ethan
 * ��дʱ�䣺2014/04/09
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

	std::string get_card_name()const; //��ȡ��Ƭ������
	std::string get_card_number()const; //��ȡ��Ƭ�����֤����
	IplImage* get_card_pic();//��ȡ���֤��Ƭ

	void detectAddFile();
private:

	std::string FoldPath;//FoldPathΪ���֤������������Ƭ��λ�ã��ڶ��������ϵͳ�趨������
	std::string ImagePath;
	std::string imageName;
	std::string name;
	std::string card_number;

	IplImage* card_pic;

};



#endif