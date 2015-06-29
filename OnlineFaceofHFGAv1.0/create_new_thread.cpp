#include "create_new_thread.h"
#include "get_cnn_feature.h"
#include "register.h"
#include "face_compare.h"
#include "show_compare_result.h"
#include "saveResult.h"

using namespace std;

void register_operate(Main* job);
void recognition_operate(Main* job);

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


		get_cnn_feature(job->image_Face,job->feature);
		if(job->mode_index==1)
			register_operate(job);

		else
			recognition_operate(job);	
	}

}

void register_operate(Main* job)
{	
	Register reg;
	reg.register_init();

	
	
	cout<<"\n";
	cout<<"������ע������Ϣ��\n";
	cout<<"/*"<<endl;
	
	cin>>job->people.name;
	cout<<"*/"<<endl;
	People people;

	

	people.cardNum=job->people.cardNum;
	people.feature=job->feature;
	people.image=job->image_face_tmp;
	people.name=job->people.name;

	
	//people.card_pic=job->image_align;

	reg.save_register_info(people);

	job->register_OK=true;
}

void recognition_operate(Main* job)
{
	Register reg;
	reg.register_init();//�����ʼ����ע���������ʱ����Ҫ����ѭ��֮�⣬ֻ���ļ�һ�Σ����ṩ�ٶ�

	People people;//��űȶԽ��

	/*cvShowImage("test",job->image_align);
	cvWaitKey(0);*/

	bool flag=reg.load_register_info(job->Data);//fasle
	if(flag==false)return;

	double mindistance=face_compare(*job,people);

	ShowResult show(people);
	show.show_result();

	save_result(people.image,job->image_face_tmp);
	

	job->Compare_OK=true;
}