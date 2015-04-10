#include "header.h"
#include "version_info_show.h"

using namespace std;
using namespace cv;




int main()
{
	version_info_show("中国科大在线人脸检索系统v1.0","人脸注册与检索","网络传播与控制安徽省重点实验室","2015年4月10日");

	cvNamedWindow("VIDEO", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("SHOW",CV_WINDOW_AUTOSIZE);

	//选择软件模式

	cout<<"请选择软件功能：[1/2]\n";
	cout<<"               1.Register 注册\n";
	cout<<"               2.Recognition 识别\n";

	int function_num;
	cin>>function_num;

	if(function_num==1)
	{
		register_mode();
	}
	
}