#include "version_info_show.h"


void version_info_show(std::string name ,std::string function ,std::string author ,std::string time )
{
	std::cout<<"\n";
	std::cout<<"\n";

	std::cout<<"***************************************************************************\n";
	std::cout<<"\n";
	std::cout<<"                               欢迎使用          \n";
	std::cout<<"                         "+name;
	std::cout<<"\n";
	std::cout<<"信息：\n";
	std::cout<<"     功    能："+function<<std::endl;
	std::cout<<"     开发单位："+author<<std::endl;
	std::cout<<"     开发时间："+time<<std::endl;
	std::cout<<"\n";
	std::cout<<"***************************************************************************\n";
}