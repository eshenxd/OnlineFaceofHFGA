#include "header.h"
#include "video_camera.h"
#include "detect_face.h"
#include "drawImage.h"
#include "create_new_thread.h"
#include "getCardInfo.h"

using namespace std;
using namespace cv;


void register_mode()
{
	cout<<"��ѡ����ע��ģʽ��\n";
	cout<<"��ʼע�����..\n";

	Main job;
	People people;//������Ƶ�г��ֵ�������Ϣ
	Card_Info info("D:/photo");

	//�½��߳�
	create_new_thread(&job);

	job.face_frame_num=0;

	//������ͷ
	Camera cam;

	while(cam.suc_flag)
	{//3
		
		//��ȡͼ��
		job.image_In=cam.read_from_camera();
		job.image_Show=cvCreateImage(cvGetSize(job.image_In),job.image_In->depth,job.image_In->nChannels);
		cvCopy(job.image_In,job.image_Show);


		//��ȡˢ���֤����Ϣ
		info.detectAddFile();

		if (info.flag==true)
		{
			//����ˢ���֤
			people.name=info.get_card_name();
			people.cardNum=info.get_card_number();

			job.people=people;

			/* face_detect */
			FaceDetector fd(job.image_In);
			fd.runFaceDetector();

			if (fd.getDetectFaceCount()==1)
			{
				job.face_frame_num++;

				fd.getDetectFacePos(0,job.pos);

				/* �������λ�� */
				draw_image(job.pos,job.image_Show);

				
				if(job.face_frame_num<10)
				{
					draw_image(job.pos,"Register Prepare...",job.image_Show,cvScalar(255,255,0));

				}

				else if(job.face_frame_num==10)
				{
					/* ��ȡ����ͼƬ */
					CvRect rect = cvRect(job.pos[0], job.pos[1], job.pos[2] - job.pos[0], job.pos[3] - job.pos[1]);
					job.image_face_tmp = cvCreateImage(cvSize(job.pos[2] - job.pos[0], job.pos[3] - job.pos[1]),
						job.image_In->depth, job.image_In->nChannels);
					cvSetImageROI(job.image_In,rect);
					cvCopy(job.image_In,job.image_face_tmp);
					cvResetImageROI(job.image_In);

					Mat matmtx(job.image_face_tmp,true);
					job.image_Face=matmtx;

					job.g_event.SetEvent();
					
				}

				else if(job.face_frame_num>10)
				{
					draw_image(job.pos,"Register ...",job.image_Show,cvScalar(255,0,255));
				}		

	    }
			else
			{
				job.face_frame_num=0;
				info.flag=false;
			}
		}

		cvShowImage("VIDEO",job.image_Show);
		cvWaitKey(2);

		cvReleaseImage(&job.image_Show);
	}
}