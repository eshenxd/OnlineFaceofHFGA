#ifndef _FACE_POINT_H
#define _FACE_POINT_H

#include "header.h"

#include "../include/asmfitting.h"
#include "../include/asmbuilding.h"
#include "../include/asmlibrary.h"

#pragma comment(lib,"../lib/asmlibrary.lib")

#define MAX_FACE_NUM_POINT_P_USTC  1 //һ֡������������
#define  NUMUSTC_P_USTC 30
#define SMALL_LEN_P_USTC 320

//��չʹ��
#define PointWidth_P_USTC 300
#define PointHeight_P_USTC 300


struct new_Rect
{

	int left;
	int top;
	int right;
	int bottom;
};//����λ��

struct _Rect_Point
{

	int left_eye_x;
	int left_eye_y;

	int right_eye_x;
	int right_eye_y;

	int nose_x;
	int nose_y;

	int left_mouth_x;
	int left_mouth_y;

	int right_mouth_x;
	int right_mouth_y;
};//�ؼ���λ��

class FacePoints
{
public:
	void load_model();//��ASMģ��

	void facePoint_init(IplImage* );//��ʼ�������㶨λ����������Ҫ����Ҷ�ͼ��

	int runFacePoints(int, int* rect);//��λ�����㣬rectΪ����������ͼ���е�λ�ã�intΪͼ���������ĸ���

	/*
	������һ��10ά���飬��ʾ5���������
	˳�����������ۣ��Ǽ⣬�������
	*/
	void getFacePoints(int* );

	void facePoint_release();//�ͷ������㶨λ��

protected:
private:
	asm_shape *shapes, *detshapes;

	asmfitting fit_asm;

	_Rect_Point* facePoint;
	new_Rect* facepos;

	int width, height;

	IplImage* gray_img;

	int* pos;

	bool init_asm();

	void free_shape_memeory(asm_shape** shapes);
};

#endif