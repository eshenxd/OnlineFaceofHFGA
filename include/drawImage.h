#ifndef _DRAW_IMAGE_H_
#define _DRAW_IMAGE_H_

#include "header.h"

void draw_image(CvRect area, IplImage* img);//画矩形

void draw_image(CvRect area, std::string showMsg, IplImage* img, CvScalar color=CV_RGB(0, 0, 255));//输出文字信息&画矩形

void draw_image(int* pos,IplImage* img);//已知两个对角点画矩形

void draw_image(int* pos,std::string showMsg,IplImage* img,CvScalar color);//已知两个对角点画矩形&输出文字信息

#endif