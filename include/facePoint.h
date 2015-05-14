#ifndef _FACE_POINT_H
#define _FACE_POINT_H

#include "header.h"

#include "../include/asmfitting.h"
#include "../include/asmbuilding.h"
#include "../include/asmlibrary.h"

#pragma comment(lib,"../lib/asmlibrary.lib")

#define MAX_FACE_NUM_POINT_P_USTC  1 //一帧中最多的人脸数
#define  NUMUSTC_P_USTC 30
#define SMALL_LEN_P_USTC 320

//扩展使用
#define PointWidth_P_USTC 300
#define PointHeight_P_USTC 300


struct new_Rect
{

	int left;
	int top;
	int right;
	int bottom;
};//人脸位置

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
};//关键点位置

class FacePoints
{
public:
	void load_model();//读ASM模板

	void facePoint_init(IplImage* );//初始化特征点定位器，这里需要传入灰度图像

	int runFacePoints(int, int* rect);//定位特征点，rect为人脸在整副图像中的位置，int为图像中人脸的个数

	/*
	参数是一个10维数组，表示5个点的坐标
	顺序依次是两眼，鼻尖，两个嘴角
	*/
	void getFacePoints(int* );

	void facePoint_release();//释放特征点定位器

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