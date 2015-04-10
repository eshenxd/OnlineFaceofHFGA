#ifndef _GET_CNN_FEATURE_H_
#define _GET_CNN_FEATURE_H_

#include "gen_feature.h"
#include "gen_feature_types.h"
#include "gen_feature_emxAPI.h"

#include "../opencv/include/opencv/cv.h"
#include "../opencv/include/opencv/highgui.h"


#include <iostream>

#pragma comment(lib,"gen_feature.lib")

#pragma comment(lib,"opencv_highgui2410d.lib")
#pragma comment(lib,"opencv_core2410d.lib")
#pragma comment(lib,"opencv_imgproc2410d.lib")


int get_cnn_feature(cv::Mat imgSrc ,double feature[]);// imgSrc为输入图像，feature为输出特征

#endif