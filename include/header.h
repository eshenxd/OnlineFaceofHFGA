#ifndef  HEADER_H

#define HEADER_H

//#include "minmax.h"
#include <vector>
//#include <list>
//#include <iterator>
#include <algorithm>
//#include <atlimage.h>
//#include <time.h>
#include <math.h>
#include <string>
#include <sstream>
#include "io.h"
#include <iostream>
#include <fstream>
#include <afxmt.h>
#include <process.h>


#include "../opencv/include/opencv/cv.h" 
#include "../opencv/include/opencv/highgui.h"
#include "../opencv/include/opencv/cxcore.h"

class People
{
public:
	std::string name;
	std::string cardNum;
	IplImage* image;
	IplImage* card_pic;
	double* feature;
};

class Main
{
public:
	IplImage* image_In;   /** <Input image*/
	IplImage* image_Show; /* <show image*/

	double feature[256];     /** <cnn feature save*/
	double Hash[48];      /*< hash code save */
	int pos[4];

	People people;        /*< save register information */

	cv::Mat image_Face;    /**  face image for cnn feature extract */
	IplImage* image_face_tmp;

	bool operate_flag;
	bool register_OK;//注册完成
	bool Compare_OK;//比对完成
	CEvent g_event;

	int face_frame_num;
};

void register_mode();
void recognition_mode();


#ifdef DEBUG

#pragma comment(lib, "../opencv/lib/opencv_core2410d.lib")
#pragma comment(lib, "../opencv/lib/opencv_objdetect2410d.lib")
#pragma comment(lib, "../opencv/lib/opencv_highgui2410d.lib")
#pragma comment(lib, "../opencv/lib/opencv_imgproc2410d.lib")

#endif

#ifndef DEBUG

#pragma comment(lib, "../opencv/lib/opencv_core2410.lib")
#pragma comment(lib, "../opencv/lib/opencv_objdetect2410.lib")
#pragma comment(lib, "../opencv/lib/opencv_highgui2410.lib")
#pragma comment(lib, "../opencv/lib/opencv_imgproc2410.lib")

#endif

#endif