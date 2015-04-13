#pragma once
#ifndef _FACE_COMPARE_H_
#define _FACE_COMPARE_H_

#include "header.h"

double face_compare(Main& job,People& people);/* 将与采集到的人脸距离最小的注册人脸
															   * 信息保存在people中，并将最小距离保
															   * 存在distance中
															   */

#endif