#include "create_new_thread.h"
#include "get_cnn_feature.h"

using namespace std;


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
		cout<<"begin new thread!\n";
		
		get_cnn_feature(job->image_Face,job->feature);
	}

}