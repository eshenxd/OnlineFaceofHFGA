#include "create_new_thread.h"
#include "get_cnn_feature.h"
#include "register.h"

using namespace std;

void register_operate(Main* job);

void create_new_thread(Main* job)
{
	_beginthread(feature_operate,NULL,(void*)job);
}

void __cdecl feature_operate(void* pThis)
{
	Main* job=(Main*)pThis;


	while(true)
	{
		WaitForSingleObject(job->g_event,INFINITE);
		
		cout<<"\n";
		cout<<"注册人信息：\n";
		cout<<"/*"<<endl;
		cout<<"姓      名："+job->people.name<<endl;
		cout<<"身份证编号："+job->people.cardNum<<endl;
		cout<<"*/"<<endl;

		get_cnn_feature(job->image_Face,job->feature);

		register_operate(job);
	}

}

void register_operate(Main* job)
{
	Register reg;
	reg.register_init();
	
	People people;

	people.cardNum=job->people.cardNum;
	people.feature=job->feature;
	people.image=job->image_face_tmp;
	people.name=job->people.name;
	people.card_pic=job->people.card_pic;

	reg.save_register_info(people);

	job->Compare_OK=true;
}

void recognition_operate(Main& job)
{

}