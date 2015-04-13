#pragma once
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "header.h"
#include "getFiles.h"
#include <fstream>
#include <iostream>

class Register
{
public:
	void register_init();
	void save_register_info(People people);
	bool load_register_info(std::vector<People>& people);

private:
	std::string SavePath;
	std::string InfoFilePath;
	std::string ImagePath;
	std::string CardNumPath;
	std::string CardPicPath;
	

};

#endif




