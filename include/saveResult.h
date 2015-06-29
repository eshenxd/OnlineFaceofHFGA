#ifndef _SAVE_RESULT_H_
#define _SAVE_RESULT_H_

#include "header.h"
#include <direct.h>//use function _mkdir()

void save_result(IplImage* result_face, IplImage* query_face);

std::string getIndex();

void setIndex();

#endif