/************************************************************************
���������ճ̹���ϵͳ
�汾�ţ�2.0
����С�飺�����п��飨�����֡�Ƚ�󡢵��ĺ���
�����ܣ�1�����ѧ���˿ںͽ�ʦ�˿ڣ�ѧ����ѧ�����ҹ�����ʦ�˽�ʦ�ල����
		  2��ע�ᡢ��¼�˺ţ��޸�����
		  3����ӡ��޸ġ�ɾ������ʾ�ճ�
		  4���ļ��Զ�����
		  5) �������棬�����Ѻã�������ǿ
		  6��ϵͳ������Զ�����
		  7����¼���˳���Ҫ���µ�¼
************************************************************************/

/*�Կ⺯���Ķ���*/
#include <graphics.h>      // ����ͼ�ο�ͷ�ļ�
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>

/*�궨��*/
#define NUMBER 100//��������ɣ�ѧ��/��ʦ�����û����� 
#define MANAGELENGTH 30//�����¼����ȣ�����ʱ�䣩 
#define STRLENGTH 30//�����û�������
#define NUMLENGTH 12//�������볤�� 

/*����ͼƬ*/
IMAGE welcome;//��ӭ����
IMAGE welcome_button;//ENTER��ť
IMAGE startup;//��ʼ����
IMAGE stu1;//ѧ���˳�ʼ
IMAGE stu1_return;
IMAGE stu1_exit;
IMAGE stu_register;//ѧ����:�����˻�
IMAGE stu_logon;//ѧ����:ѧ����¼
IMAGE stu_resetpassword;//ѧ���ˣ��޸�����
IMAGE stu_schedulemanagement1;//ѧ���ˣ��ճ̹������1
IMAGE stu_schedulemanagement2;//ѧ���ˣ��ճ̹������2
IMAGE stu_schedulemanagement2_return;
IMAGE stu_schedulemanagement2_exit;
IMAGE teacher1;//��ʦ�˳�ʼ
IMAGE teacher1_return;
IMAGE teacher1_exit;
IMAGE teacher_register;//��ʦ�ˣ������˻�
IMAGE teacher_logon;//��ʦ�ˣ���ʦ��¼
IMAGE teacher_resetpassword;//��ʦ��:�޸�����
IMAGE teacher_schedulemanagement1;//��ʦ�ˣ��ճ̹������1
IMAGE teacher_schedulemanagement2;//��ʦ�ˣ��ճ̹������2
IMAGE teacher_schedulemanagement2_return;
IMAGE teacher_schedulemanagement2_exit;
IMAGE createschedule;//ѧ���ˣ������ճ�
IMAGE resetschedule;//ѧ���ˣ��޸��ճ�
IMAGE finishedcondition;//ѧ���ˣ����״̬
IMAGE setstuschedule;//��ʦ�ˣ��趨ѧ���ճ�
IMAGE resetstuschedule;//��ʦ�ˣ��޸�ѧ���ճ�
IMAGE checkfinishedcondition;//��ʦ�ˣ��鿴���״̬
IMAGE end;//��������

/*ȫ�ֱ���*/
int nStudentNum = 0;//ע���ѧ����ţ���0��ʼ����ͬʱҲ������ע�������� 
int nTeacherNum = 0;//ע��Ľ�ʦ��� ����һ��ע����û����Ϊ0�� 
int nStuFlag = 0;//�����ж�ѧ���Ƿ��¼�ı�־����
int nTeacherFlag = 0;//�����жϽ�ʦ�Ƿ��¼�ı�־���� 
int studentnum;//�����¼��ѧ�����
int teachernum;//�����¼�Ľ�ʦ���

/*����ѧ���ṹ������*/
struct student
{
	wchar_t szName[STRLENGTH];//����ѧ���û���
	wchar_t password1[NUMLENGTH];//����ѧ���˻�����
	wchar_t password2[NUMLENGTH];//����ѧ��������������
	int nSerialNum;//����ѧ�����(��1��ʼ) 
	int nManagement = 0;//����ѧ�����ճ��¼���  
	wchar_t Management1[10][MANAGELENGTH];//����洢��ѧ���趨�ĳ�ʼʱ���ַ�����      �趨һ��ѧ������趨10���¼� 
	wchar_t Management2[10][MANAGELENGTH];//����洢��ѧ���趨�Ľ�ֹʱ���ַ�����
	wchar_t Management3[10][MANAGELENGTH];//����洢��ѧ���趨���ճ������ַ�����
	wchar_t FinishStatus[10][MANAGELENGTH];//����ÿ��ѧ���趨���ճ̵����״̬ 
}stu[NUMBER];

/*�����ʦ�Ľṹ������*/
struct  teacher
{
	wchar_t szName[STRLENGTH];//�����ʦ�û���
	wchar_t password1[NUMLENGTH];//�����ʦ�˻�����
	wchar_t password2[NUMLENGTH];//�����ʦ������������ 
	int nSerialNum;//������ʦ���(��1��ʼ) 
}teacher[NUMBER];

/*��������***********************************************/

/*��ӭ���溯��*/
void Welcome(FILE *fp);

/*�ļ����溯��*/
void SaveFile(FILE *fp);

/*һ�����˵�����*/
void Select_MainMenu(FILE *fp);

/*�����˵�����*/

//�����˵�ѧ����Ŀ¼��ʾ
void OutputStu_SecondMenu(FILE *fp);
//�����˵���ʦ��Ŀ¼��ʾ
void OutputTeacher_SecondMenu(FILE *fp);
//�����˵���ѧ�������˻� 
void Stu_Register(FILE *fp);
// �����˵���ѧ����¼
void Stu_Logon();
//�����˵���ѧ���޸�����
void Stu_ResetPassword(FILE *fp);
//�����˵���ѧ���ճ̹���
void Stu_ScheduleManagement(FILE *fp);
//�����˵�����ʦ�����˻�
void Teacher_Register(FILE *fp);
//�����˵�����ʦ��¼
void Teacher_Logon();
//�����˵�����ʦ�޸�����
void Teacher_ResetPassword(FILE *fp);
//�����˵�����ʦ��ѧ���ճ̹���
void Teacher_ScheduleManagement(FILE *fp);

/*�����˵�����*/

/*�����˵�*/

//�����˵����½��ճ� 
void CreateSchedule(FILE *fp);
//�����˵����޸��ճ�
void ResetSchedule(FILE *fp);
//�����˵������״̬
void FinishedCondition(FILE *fp);
//�����˵����趨ѧ���ճ�
void SetStuSchedule(FILE *fp);
//�����˵����޸�ѧ���ճ�
void ResetStuSchedule(FILE *fp);
//�����˵����鿴ѧ�����״̬
void CheckFinishedCondition();

/*�����˵�����*/

/*������������********************************************/

//��ӭ���溯��
void Welcome(FILE *fp)
{
	loadimage(&welcome, L"welcome.jpg");//���뻶ӭ���棨�ر�ע�⣺˫�������治���пո�Ҫ��ͼƬ������ȫһ�£�
	putimage(0, 0, &welcome);//��ʾ��ӭ����
	/*���������꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 232 && msg.x < 498 && msg.y > 478 && msg.y < 543)//������ض����򣬼�ENTER��ť��������
				{
					loadimage(&welcome_button, L"welcome_button.jpg");//�����ɫ��ťͼƬ
					putimage(0, 0, &welcome_button);//��ʾ��ɫ��ťͼƬ
					Sleep(100);//��ʱ������CPUռ���ʣ������������Ч��
					Select_MainMenu(fp);//����һ�����˵�ѡ���
				}
			}
		}
	}
}

//�ļ����溯��
void SaveFile(FILE *fp)
{
	fopen_s(&fp, "alldate.dat", "wb");
	//���ļ����ȫ�ֱ���
	fwrite(&nStudentNum, 4, 1, fp);
	fwrite(&nTeacherNum, 4, 1, fp);
	fwrite(&nStuFlag, 4, 1, fp);
	fwrite(&nTeacherFlag, 4, 1, fp);
	fwrite(&studentnum, 4, 1, fp);
	fwrite(&teachernum, 4, 1, fp);
	//���ѧ���ṹ������
	for (int i = 0; i < nStudentNum; i++)
		fwrite(&stu[i], sizeof(struct student), 1, fp);
	//�����ʦ�ṹ������ 
	for (int i = 0; i < nTeacherNum; i++)
		fwrite(&teacher[i], sizeof(struct teacher), 1, fp);
	fclose(fp);
}

//һ�����˵�ѡ��(ѧ���ˡ���ʦ��)����
void Select_MainMenu(FILE *fp)
{
	loadimage(&startup, L"startup.jpg");//�����ʼ����
	putimage(0, 0, &startup);//��ʾ��ʼ����
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//������ض����򣬼���ѧ���ˡ���ť��������
					OutputStu_SecondMenu(fp);//����ѧ���˺���
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//������ض����򣬼�����ʦ�ˡ���ť��������
					OutputTeacher_SecondMenu(fp);//���ý�ʦ�˺���
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)
				{
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
				}
			}
		}
	}
}

//�����˵�ѧ����Ŀ¼��ʾ
void OutputStu_SecondMenu(FILE *fp)
{
	loadimage(&stu1, L"stu1.jpg");//����ѧ���˽���
	putimage(0, 0, &stu1);//��ʾѧ���˽���
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������ʦ�ˡ���ť��������
					OutputTeacher_SecondMenu(fp);//���ý�ʦ�˺���
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//������ض����򣬼���STUDENT����ť��������
					Select_MainMenu(fp);//����һ�����˵�ѡ���
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//������ض����򣬼��������˻�����ť��������
					Stu_Register(fp);//����ѧ�������˻�����
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//������ض����򣬼���ѧ����¼����ť��������
					Stu_Logon();//����ѧ����¼����
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//������ض����򣬼����޸����롱��ť��������
					Stu_ResetPassword(fp);//����ѧ���޸����뺯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//������ض����򣬼����ճ̹�����ť��������
					if(nStuFlag == 1)//�ѵ�¼
						Stu_ScheduleManagement(fp);//����ѧ���ճ̹�����
					else 
						MessageBox(NULL, _T("����δ��¼"), _T("�ճ̹���"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{

					loadimage(&stu1_return, L"stu1_return.jpg");
					putimage(0, 0, &stu1_return);
					Sleep(100);
					Welcome(fp);
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					/*�˳���¼��ʹ���´ν���ϵͳ�����µ�¼��*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//�����ļ����溯��
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
				}
			}
		}
	}
}

//�����˵�����ʦ��Ŀ¼��ʾ
void OutputTeacher_SecondMenu(FILE *fp)
{
	loadimage(&teacher1, L"teacher1.jpg");//�����ʦ�˽���
	putimage(0, 0, &teacher1);//��ʾ��ʦ�˽���
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//������ض����򣬼���ѧ���ˡ���ť��������
					OutputStu_SecondMenu(fp);//����ѧ���˺���
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//������ض����򣬼���STUDENT����ť��������
					Select_MainMenu(fp);//����һ�����˵�����
				if (msg.x > 81 && msg.x < 365 && msg.y > 69 && msg.y < 135)//������ض����򣬼��������˻�����ť��������
					Teacher_Register(fp);//���ý�ʦ�����˻�����
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 227)//������ض����򣬼�����ʦ��¼����ť��������
					Teacher_Logon();//���ý�ʦ��¼����
				if (msg.x > 81 && msg.x < 365 && msg.y > 254 && msg.y < 320)//������ض����򣬼����޸����롱��ť��������
					Teacher_ResetPassword(fp);//���ý�ʦ�޸����뺯��
				if (msg.x > 81 && msg.x < 365 && msg.y > 347 && msg.y < 410)//������ض����򣬼���ѧ���ճ̹�����ť��������
					if(nTeacherFlag == 1)//�ѵ�¼
						Teacher_ScheduleManagement(fp);//���ý�ʦ��ѧ���ճ̹�����
					else 
						MessageBox(NULL, _T("����δ��¼"), _T("ѧ���ճ̹���"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{

					loadimage(&teacher1_return, L"teacher1_return.jpg");
					putimage(0, 0, &teacher1_return);
					Sleep(100);
					Welcome(fp);
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					/*�˳���¼��ʹ���´ν���ϵͳ�����µ�¼��*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//�����ļ����溯��
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
				}
			}
		}
	}
}

//�����˵���ѧ�������˻�
void Stu_Register(FILE *fp)
{
	loadimage(&stu_register, L"stu_register.jpg");//����ѧ���˴����˻�����
	putimage(0, 0, &stu_register);

	/*�����û���*/
	int i;
	do{
		InputBox(stu[nStudentNum].szName, 10, _T("�������û���"));//��ʾ�û������û���
		//�����������û���Ϣ���е����ݣ��Ƚ���������û����Ƿ���ڣ�������ڣ�ϵͳ������ʾ
		for (i = 0; i < nStudentNum; i++)
		{
			if (wcscmp(stu[i].szName, stu[nStudentNum].szName) == 0)
			{
				MessageBox(NULL, _T("���û��Ѿ����ڣ�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND);//�����ʾ�������û�
				break;//����forѭ��
					  //�޸���1.0�汾�û�ע��ʱ���ֵ�bug
			}
				
		}
		if (i >= nStudentNum)//˵��û���ҵ��ظ����û��� 
			break;
	  } while (1);//����û����ظ���һֱѭ����ֱ�����ظ�ʱ����ѭ�� 
				 //�����û����������� 

	/*���������û�����*/
	 do{
		  InputBox(stu[nStudentNum].password1, 10, _T("������6λ������"));//��ʾ�û���������
		  InputBox(stu[nStudentNum].password2, 10, _T("��ȷ������"));//��ʾ�û�ȷ������
		  if (wcscmp(stu[nStudentNum].password1, stu[nStudentNum].password2) != 0)//�����������벻��� 
			  MessageBox(NULL, _T("�������벻һ�£�����������"), _T("�����˻�"), MB_ICONSTOP|MB_SETFOREGROUND);
		  else
		  {
			  MessageBox(NULL, _T("ע��ɹ���"), _T("�����˻�"), MB_SETFOREGROUND);
			  //�����ֱ�Ϊ����Ϣ��ӵ�еĴ��ڡ���Ϣ������ݡ���Ϣ��ı��⡢��־��(�����־��"��"(|)��������)
			 //���Ĳ�����ʾ������Ϣ��Ϊǰ������
			  nStudentNum++;//������һ����Ҫע���ѧ���û��ı��
			  stu[nStudentNum - 1].nSerialNum = nStudentNum;//��һ 
			  SaveFile(fp);//�����ļ����溯��
			  break;
		  }
		} while (1);
}

//�����˵���ѧ����¼
void Stu_Logon()
{
	loadimage(&stu_logon, L"stu_logon.jpg");//����ѧ����ѧ����¼����
	putimage(0, 0, &stu_logon);

	/*�����û���*/
	int i;
	wchar_t username[STRLENGTH];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[NUMLENGTH];//����һ����ʱ�洢������ַ����� 
	do{
		InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
		for (i = 0; i < nStudentNum; i++)
			if (wcscmp(username, stu[i].szName) == 0)//�ҵ��� 
			{
				studentnum = i; 
				break;//����forѭ��
			}//��¼�����û�������Ӧ��ѧ����ţ�����¼���û�����Ӧ�ı�� 

		if (i >= nStudentNum)//˵��û���ҵ���Ӧ�û��� 
			MessageBox(NULL, _T("���û�������"), _T("ѧ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�ҵ��˴��û������˳������û�����ѭ����������������ģ�� 
	  }while (1);

	/*��������ģ��*/
	do {
		InputBox(password, 10, _T("����������"));//��ʾ�û��������룬�������ʱ�洢������ַ�����
		if (wcscmp(password, stu[studentnum].password1) == 0)//������� 
		{
			MessageBox(NULL, _T("��¼�ɹ���"), _T("ѧ����¼"), MB_SETFOREGROUND);
			nStuFlag = 1;//��־���Ѿ��ɹ���¼ 
			break;
		}//������������ģ�� 
		else
			MessageBox(NULL, _T("�������"), _T("ѧ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵���ѧ���޸�����
void Stu_ResetPassword(FILE *fp)
{
	loadimage(&stu_resetpassword, L"stu_resetpassword.jpg");//����ѧ�����޸��������
	putimage(0, 0, &stu_resetpassword);

	//studentnum ��¼�޸������ѧ���û��ı��(����¼��ѧ���û��ı�ţ� 
	int i;
	wchar_t username[STRLENGTH];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[NUMLENGTH];//����һ����ʱ�洢������ַ����� 
	wchar_t resetpassword[NUMLENGTH];//����һ����ʱ�洢�޸ĺ�������ַ����� 
	do {
		InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
		for (i = 0; i < nStudentNum; i++)
			if (wcscmp(username, stu[i].szName) == 0)//�ҵ��� 
			{
				studentnum = i; 
				break;
			}//��¼�����û�������Ӧ��ѧ����ţ�����¼���û�����Ӧ�ı�� 

		if (i >= nStudentNum)//˵��û���ҵ���Ӧ�û��� 
			MessageBox(NULL, _T("���û�������"), _T("�޸�����"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�ҵ��˴��û������˳������û�����ѭ���������޸�����ģ�� 
	} while (1);

	do {
		InputBox(password, 10, _T("������ԭʼ����"));
		if (wcscmp(password, stu[studentnum].password1) == 0)//�������
		{
			InputBox(resetpassword, 10, _T("������ȷ��������6λ���޸�����"));
			wcscpy_s(stu[studentnum].password1, resetpassword);//��ԭ�����Ϊ�޸ĺ������(wcscpy�൱��strcopy)
			MessageBox(NULL, _T("�޸�����ɹ���"), _T("�޸�����"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;//�˳��޸�����ģ�� 
		}
		else
			MessageBox(NULL, _T("�������"), _T("�޸�����"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵���ѧ���ճ̹���
void Stu_ScheduleManagement(FILE *fp)
{
	loadimage(&stu_schedulemanagement1, L"stu_schedulemanagement1.jpg");//����ѧ�����ճ̹������1
	putimage(0, 0, &stu_schedulemanagement1);
	Sleep(100);//��ʱ����ʾ���Ч��
	loadimage(&stu_schedulemanagement2, L"stu_schedulemanagement2.jpg");//����ѧ�����ճ̹������2
	putimage(0, 0, &stu_schedulemanagement2);
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 80 && msg.x < 365 && msg.y > 92 && msg.y < 159)//������ض����򣬼����½��ճ̡���ť��������
					CreateSchedule(fp);//�����½��ճ̺���
				if (msg.x > 80 && msg.x < 365 && msg.y > 219 && msg.y < 287)//������ض����򣬼����޸��ճ̡���ť��������
					ResetSchedule(fp);//�����޸��ճ̺���
				if (msg.x > 80 && msg.x < 365 && msg.y > 344 && msg.y < 408)//������ض����򣬼������״̬����ť��������
					FinishedCondition(fp);//�������״̬����
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//�������ʦ�ˡ���ť��������
					OutputTeacher_SecondMenu(fp);//���ý�ʦ�˺���
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//������ض����򣬼���STUDENT����ť��������
					Select_MainMenu(fp);//����һ�����˵�ѡ���
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{

					loadimage(&stu_schedulemanagement2_return, L"stu_schedulemanagement2_return.jpg");
					putimage(0, 0, &stu_schedulemanagement2_return);
					Sleep(100);
					OutputStu_SecondMenu(fp);//���ö����˵�ѧ����
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					/*�˳���¼��ʹ���´ν���ϵͳ�����µ�¼��*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//�����ļ����溯��
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
				}
			}
		}
	}
}

//�����˵����½��ճ�
void CreateSchedule(FILE *fp)
{
	loadimage(&createschedule, L"createschedule.jpg");//�����½��ճ̽���
	putimage(0, 0, &createschedule);
	wchar_t FinishStatus1[MANAGELENGTH];//����һ��"���"�ַ�����
	wcscpy_s(FinishStatus1, L"���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	wchar_t FinishStatus2[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus2, L"δ���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	stu[studentnum].nManagement++;//���ճ��¼�����1
	InputBox(stu[studentnum].Management1[stu[studentnum].nManagement], 11, _T("��ʼʱ�䣨����2018.09.08��"));//��ʼʱ��
	InputBox(stu[studentnum].Management2[stu[studentnum].nManagement], 11, _T("����ʱ�䣨����2018.09.23��"));//��ֹʱ��
	InputBox(stu[studentnum].Management3[stu[studentnum].nManagement], 11, _T("�ճ����ݣ�����2018.09.08��"));//�ճ�����
	do {
		InputBox(stu[studentnum].FinishStatus[stu[studentnum].nManagement], 11, _T("����״̬�����/δ��ɣ�"));//����״̬
		if (wcscmp(stu[studentnum].FinishStatus[stu[studentnum].nManagement], FinishStatus1) == 0)
		{
			MessageBox(NULL, _T("�½��ɹ���"), _T("�½��ճ�"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else if (wcscmp(stu[studentnum].FinishStatus[stu[studentnum].nManagement], FinishStatus2) == 0)
		{
			MessageBox(NULL, _T("�½��ɹ���"), _T("�½��ճ�"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else
			MessageBox(NULL, _T("�������"), _T("�½��ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵�;�޸��ճ�
void ResetSchedule(FILE *fp)
{
	loadimage(&resetschedule, L"resetschedule.jpg");//�����޸��ճ̽���
	putimage(0, 0, &resetschedule);
	wchar_t FinishStatus1[MANAGELENGTH];//����һ��"���"�ַ�����
	wcscpy_s(FinishStatus1, L"���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	wchar_t FinishStatus2[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus2, L"δ���");
	wchar_t sequencenum[100];//����洢��ŵ��ַ�����
	wchar_t tem_sequencenum[100];//������ʱ�洢��ŵ��ַ�����
	int sequence;//������ʱ�洢ѡ����ŵı��� 
	//wchar_t resetschedule[MANAGELENGTH];//������ʱ�洢�޸ĺ��ճ̵�����
	//wchar_t finishstatus[MANAGELENGTH];//������ʱ�洢�޸ĺ����״̬������ 
	//��ʾ�ճ�
	int position_x = 476;//����š�������
	int position_y = 92;//����š�������
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	settextcolor(COLORREF(RGB(0,0,0)));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������С20����ʽ����
	outtextxy(position_x, position_y, _T("���    ��ʼʱ��    ��ֹʱ��    �ճ�����    ״̬"));//��ʾ����һ�б�ͷ
	for (int i = 1; i <= stu[studentnum].nManagement; i++)//��ʾ����ѧ���û����е��ճ�
	{
		/*������ת��Ϊ�ַ����ĺ���*/
		//����outtextxy���ʱ�޷�ֱ�����int�����������Ҫ��int��ת��Ϊ�ַ���
		//�˺�����ȡ���취ö�٣�ö��1-10��
		if (i == 0)
			wcscpy_s(sequencenum, L"0");
		if (i == 1)
			wcscpy_s(sequencenum, L"1");
		if (i == 2)
			wcscpy_s(sequencenum, L"2");
		if (i == 3)
			wcscpy_s(sequencenum, L"3");
		if (i == 4)
			wcscpy_s(sequencenum, L"4");
		if (i == 5)
			wcscpy_s(sequencenum, L"5");
		if (i == 6)
			wcscpy_s(sequencenum, L"6");
		if (i == 7)
			wcscpy_s(sequencenum, L"7");
		if (i == 8)
			wcscpy_s(sequencenum, L"8");
		if (i == 9)
			wcscpy_s(sequencenum, L"9");
		if (i == 10)
			wcscpy_s(sequencenum, L"10");
		position_y+= 20;//������һ��
		outtextxy(494, position_y, sequencenum);//��ʾ���
		outtextxy(556, position_y, stu[studentnum].Management1[i]);//��ʼʱ��
		outtextxy(676, position_y, stu[studentnum].Management2[i]);//����ʱ��
		outtextxy(800, position_y, stu[studentnum].Management3[i]);//�ճ�����
		outtextxy(916, position_y, stu[studentnum].FinishStatus[i]);//���״̬
	}
	//ѡ���¼�
	int i;
	do {
		InputBox(tem_sequencenum, 10, _T("��ѡ����Ҫ�޸ĵ��ճ����"));
		//��������ַ��������ֵ�ת��
		if (wcscmp(tem_sequencenum, L"0") == 0)
			sequence = 0;
		if (wcscmp(tem_sequencenum, L"1") == 0)
			sequence = 1;
		if (wcscmp(tem_sequencenum, L"2") == 0)
			sequence = 2;
		if (wcscmp(tem_sequencenum, L"3") == 0)
			sequence = 3;
		if (wcscmp(tem_sequencenum, L"4") == 0)
			sequence = 4;
		if (wcscmp(tem_sequencenum, L"5") == 0)
			sequence = 5;
		if (wcscmp(tem_sequencenum, L"6") == 0)
			sequence = 6;
		if (wcscmp(tem_sequencenum, L"7") == 0)
			sequence = 7;
		if (wcscmp(tem_sequencenum, L"8") == 0)
			sequence = 8;
		if (wcscmp(tem_sequencenum, L"9") == 0)
			sequence = 9;
		if (wcscmp(tem_sequencenum, L"10") == 0)
			sequence = 10;
		for (i = 1; i <= stu[studentnum].nManagement; i++)
			if (sequence == i)
				break;

		if (i > stu[studentnum].nManagement)//˵�����������û���������ճ���ŵķ�Χ�� 
			MessageBox(NULL, _T("����������"), _T("�޸��ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�˳�ѡ���ճ���ŵ�ѭ�� 
	} while (1);

	//�޸��ճ�  
	InputBox(stu[studentnum].Management1[sequence], 11, _T("�����¹滮��ʼʱ�䣨����2018.09.08��"));//��ʼʱ��
	InputBox(stu[studentnum].Management2[sequence], 11, _T("�����¹滮����ʱ�䣨����2018.09.23��"));//��ֹʱ��
	InputBox(stu[studentnum].Management3[sequence], 11, _T("�����¹滮�ճ����ݣ�����2018.09.08��"));//�ճ�����

	do {//�޸�״̬ 
		InputBox(stu[studentnum].FinishStatus[sequence], 11, _T("�����¹滮���״��:(���/δ���)"));
		if (wcscmp(stu[studentnum].FinishStatus[sequence], FinishStatus1) == 0)
		{
			MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸��ճ�"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else if (wcscmp(stu[studentnum].FinishStatus[sequence], FinishStatus2) == 0)
		{
			MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸��ճ�"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else
			MessageBox(NULL, _T("�������"), _T("�޸��ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵������״̬(��ʾ�õ�¼�û��������ճ̲����¹滮���״̬)
void FinishedCondition(FILE *fp)
{
	loadimage(&finishedcondition, L"finishedcondition.jpg");//�������״̬����
	putimage(0, 0, &finishedcondition);
	//��ʾ�ճ�
	wchar_t sequencenum[100];//����洢��ŵ��ַ�����
	int position_x = 476;//����š�������
	int position_y = 92;//����š�������
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������С20����ʽ����
	outtextxy(position_x, position_y, _T("���    ��ʼʱ��    ��ֹʱ��    �ճ�����    ״̬"));//��ʾ����һ�б�ͷ
	for (int i = 1; i <= stu[studentnum].nManagement; i++)//��ʾ����ѧ���û����е��ճ�
	{
		/*������ת��Ϊ�ַ����ĺ���*/
		//����outtextxy���ʱ�޷�ֱ�����int�����������Ҫ��int��ת��Ϊ�ַ���
		//�˺�����ȡ���취ö�٣�ö��1-10��
		if (i == 0)
			wcscpy_s(sequencenum, L"0");
		if (i == 1)
			wcscpy_s(sequencenum, L"1");
		if (i == 2)
			wcscpy_s(sequencenum, L"2");
		if (i == 3)
			wcscpy_s(sequencenum, L"3");
		if (i == 4)
			wcscpy_s(sequencenum, L"4");
		if (i == 5)
			wcscpy_s(sequencenum, L"5");
		if (i == 6)
			wcscpy_s(sequencenum, L"6");
		if (i == 7)
			wcscpy_s(sequencenum, L"7");
		if (i == 8)
			wcscpy_s(sequencenum, L"8");
		if (i == 9)
			wcscpy_s(sequencenum, L"9");
		if (i == 10)
			wcscpy_s(sequencenum, L"10");
		position_y += 20;//������һ��
		outtextxy(494, position_y, sequencenum);//��ʾ���
		outtextxy(556, position_y, stu[studentnum].Management1[i]);//��ʼʱ��
		outtextxy(676, position_y, stu[studentnum].Management2[i]);//����ʱ��
		outtextxy(800, position_y, stu[studentnum].Management3[i]);//�ճ�����
		outtextxy(916, position_y, stu[studentnum].FinishStatus[i]);//���״̬
	}
	//ѡ���¼�
	int i;
	int sequence;//������Ҫ�޸ĵ��ճ����
	wchar_t sequence1[100];//������ʱ�洢ѡ����ճ���ŵ��ַ�����
	wchar_t FinishStatus[MANAGELENGTH];//����һ����ʱ�洢���״̬���ַ�����
	wchar_t FinishStatus1[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus1, L"���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	wchar_t FinishStatus2[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus2, L"δ���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	do {
		InputBox(sequence1, 10, _T("��ѡ����Ҫ�޸ĵ��ճ����"));
		//��������ַ��������ֵ�ת��
		if (wcscmp(sequence1, L"0") == 0)
			sequence = 0;
		if (wcscmp(sequence1, L"1") == 0)
			sequence = 1;
		if (wcscmp(sequence1, L"2") == 0)
			sequence = 2;
		if (wcscmp(sequence1, L"3") == 0)
			sequence = 3;
		if (wcscmp(sequence1, L"4") == 0)
			sequence = 4;
		if (wcscmp(sequence1, L"5") == 0)
			sequence = 5;
		if (wcscmp(sequence1, L"6") == 0)
			sequence = 6;
		if (wcscmp(sequence1, L"7") == 0)
			sequence = 7;
		if (wcscmp(sequence1, L"8") == 0)
			sequence = 8;
		if (wcscmp(sequence1, L"9") == 0)
			sequence = 9;
		if (wcscmp(sequence1, L"10") == 0)
			sequence = 10;
		for (i = 1; i <= stu[studentnum].nManagement; i++)
			if (sequence == i)
				break;

		if (i > stu[studentnum].nManagement)//˵�����������û���������ճ���ŵķ�Χ�� 
			MessageBox(NULL, _T("����������"), _T("���״̬"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�˳�ѡ���ճ���ŵ�ѭ�� 
	} while (1);
	//��ѡ״̬ 
	do {
		InputBox(FinishStatus, 10, _T("�����¹滮���״��:(���/δ���)"));
		if (wcscmp(FinishStatus, FinishStatus1) == 0)
		{
			wcscpy_s(stu[studentnum].FinishStatus[sequence], FinishStatus1);//���
			MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸�״̬"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else if (wcscmp(FinishStatus, FinishStatus2) == 0)
		{
			wcscpy_s(stu[studentnum].FinishStatus[sequence], FinishStatus2);//δ���
			MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸�״̬"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else
			MessageBox(NULL, _T("�������"), _T("�޸�״̬"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);

}

//�����˵�����ʦ�����˻�
void Teacher_Register(FILE *fp)
{
	loadimage(&teacher_register, L"teacher_register.jpg");//�����ʦ�˴����˻�����
	putimage(0, 0, &teacher_register);

	/*�����û���*/
	int i;
	do {
		InputBox(teacher[nTeacherNum].szName, 10, _T("�������û���"));//��ʾ�û������û���
		//�����������û���Ϣ���е����ݣ��Ƚ���������û����Ƿ���ڣ�������ڣ�ϵͳ������ʾ
		for (i = 0; i < nTeacherNum; i++)
		{
			if (wcscmp(teacher[i].szName, teacher[nTeacherNum].szName) == 0)
			{
				MessageBox(NULL, _T("���û��Ѿ����ڣ�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND);//�����ʾ�������û�
				break;//����forѭ��
			}
		}
		if (i >= nTeacherNum)//˵��û���ҵ�����ע���û��ظ����û��� 
			break;
	} while (1);//����û����ظ���һֱѭ����ֱ�����ظ�ʱ����ѭ�� 
			  //�����û����������� 
  /*���������û�����*/
	do {
		InputBox(teacher[nTeacherNum].password1, 10, _T("������6λ������"));//��ʾ�û���������
		InputBox(teacher[nTeacherNum].password2, 10, _T("��ȷ������"));//��ʾ�û�ȷ������
		if (wcscmp(teacher[nTeacherNum].password1, teacher[nTeacherNum].password2) != 0)//�����������벻��� 
			MessageBox(NULL, _T("�������벻һ�£�����������"), _T("�����˻�"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("ע��ɹ���"), _T("�����˻�"), MB_SETFOREGROUND);
			nTeacherNum++;//��ʾ��һ�ν�Ҫע��Ľ�ʦ�û��ı�� 
			SaveFile(fp);//�����ļ����溯��
			break;
		}
	} while (1);
}

//�����˵�:��ʦ��¼
void Teacher_Logon()
{
	loadimage(&teacher_logon, L"teacher_logon.jpg");//�����ʦ�˽�ʦ��¼����
	putimage(0, 0, &teacher_logon);

	/*�����û���*/
	int i;
	wchar_t username[STRLENGTH];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[NUMLENGTH];//����һ����ʱ�洢������ַ����� 
	do {
		InputBox(username, 10, _T("�������û���"));//��ʾ�û������û������������ʱ�洢�û������ַ�����
		for (i = 0; i < nTeacherNum; i++)
			if (wcscmp(username, teacher[i].szName) == 0)//�ҵ��� 
			{
				teachernum = i;
				break;
			}//��¼�����û�������Ӧ�Ľ�ʦ��ţ�����¼���û�����Ӧ�ı�� 

		if (i >= nTeacherNum)//˵��û���ҵ���Ӧ�û��� 
			MessageBox(NULL, _T("���û�������"), _T("��ʦ��¼"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�ҵ��˴��û������˳������û�����ѭ����������������ģ�� 
	} while (1);
	
	/*��������ģ��*/
	do {
		InputBox(password, 10, _T("����������"));//��ʾ�û��������룬�������ʱ�洢������ַ�����
		if (wcscmp(password, teacher[teachernum].password1) == 0)//������� 
		{
			MessageBox(NULL, _T("��¼�ɹ���"), _T("��ʦ��¼"), MB_SETFOREGROUND);
			nTeacherFlag = 1;//��־��ʦ�û���¼�ɹ� 
			break;
		}//������������ģ�� 
		else
			MessageBox(NULL, _T("�������"), _T("ѧ����¼"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵�����ʦ�޸�����
void Teacher_ResetPassword(FILE *fp)
{
	loadimage(&teacher_resetpassword, L"teacher_resetpassword.jpg");//�����ʦ���޸��������
	putimage(0, 0, &teacher_resetpassword);

	//teachernum ��¼�޸�������û��ı��(����¼�Ľ�ʦ�û��ı��) 
	int i;
	wchar_t username[STRLENGTH];//����һ����ʱ�洢�û������ַ����� 
	wchar_t password[NUMLENGTH];//����һ����ʱ�洢������ַ����� 
	wchar_t resetpassword[NUMLENGTH];//����һ����ʱ�洢�޸ĺ�������ַ����� 
	do {
		InputBox(username, 10, _T("�������û���"));
		for (i = 0; i < nTeacherNum; i++)
			if (wcscmp(username, teacher[i].szName) == 0)//�ҵ��� 
			{
				teachernum = i; 
				break;
			}//��¼�����û�������Ӧ��ѧ����ţ�����¼���û�����Ӧ�ı�� 

		if (i >= nTeacherNum)//˵��û���ҵ���Ӧ�û��� 
			MessageBox(NULL, _T("���û�������"), _T("�޸�����"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�ҵ��˴��û������˳������û�����ѭ���������޸�����ģ�� 
	} while (1);

	do {
		InputBox(password, 10, _T("������ԭʼ����"));
		if (wcscmp(password, teacher[teachernum].password1) == 0)//�������
		{
			InputBox(resetpassword, 10, _T("������ȷ��������6λ���޸�����"));
			wcscpy_s(teacher[teachernum].password1, resetpassword);//��ԭ�����Ϊ�޸ĺ������
			MessageBox(NULL, _T("�޸�����ɹ���"), _T("�޸�����"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;//�˳��޸�����ģ�� 
		}
		else
			MessageBox(NULL, _T("�������"), _T("�޸�����"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵�����ʦ��ѧ���ճ̹���
void Teacher_ScheduleManagement(FILE *fp)
{
	loadimage(&teacher_schedulemanagement1, L"teacher_schedulemanagement1.jpg");//�����ʦ���ճ̹������1
	putimage(0, 0, &teacher_schedulemanagement1);
	Sleep(100);
	loadimage(&teacher_schedulemanagement2, L"teacher_schedulemanagement2.jpg");//�����ʦ���ճ̹������2
	putimage(0, 0, &teacher_schedulemanagement2);
	/*�����Ƕ����ť����꽻��*/
	MOUSEMSG msg;//������������������Ϣ
	FlushMouseMsgBuffer();// ��������Ϣ��������������Ч�����Ϣ���뵽��ʽ�ж���
	while (true) // ��ѭ��,ѭ�����������Ϣ
	{
		while (MouseHit())	//���������Ϣ;���������Ϣ��ʱ��ִ��,�ɼ�������������Ϣ
		{
			msg = GetMouseMsg();//��ȡ�����Ϣ
			if (WM_LBUTTONDOWN == msg.uMsg)//�ж������Ϣ;����������
			{
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//������ض����򣬼���STUDENT����ť��������
					Select_MainMenu(fp);//����һ�����˵�ѡ���
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//������ض����򣬼���ѧ���ˡ���ť��������
					OutputStu_SecondMenu(fp);//����ѧ���˺���
				if (msg.x > 81 && msg.x < 365 && msg.y > 95 && msg.y < 158)//������ض����򣬼����½�ѧ���ճ̡���ť��������
					SetStuSchedule(fp);//�����趨ѧ���ճ̺���
				if (msg.x > 81 && msg.x < 365 && msg.y > 218 && msg.y < 284)//������ض����򣬼����޸�ѧ���ճ̡���ť��������
					ResetStuSchedule(fp);//���ý�ʦ�޸�ѧ���ճ̺���
				if (msg.x > 81 && msg.x < 365 && msg.y > 342 && msg.y < 410)//������ض����򣬼����鿴���״̬����ť��������
					CheckFinishedCondition();//���ý�ʦ�鿴ѧ�����״̬����
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//��������ذ�ť
				{

					loadimage(&teacher_schedulemanagement2_return, L"teacher_schedulemanagement2_return.jpg");
					putimage(0, 0, &teacher_schedulemanagement2_return);
					Sleep(100);
					OutputTeacher_SecondMenu(fp);//���ö����˵���ʦ��
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//�����exit��ť
				{
					/*�˳���¼��ʹ���´ν���ϵͳ�����µ�¼��*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//�����ļ����溯��
					loadimage(&stu1_exit, L"stu1_exit.jpg");
					putimage(0, 0, &stu1_exit);
					Sleep(100);
					loadimage(&end, L"end.jpg");
					putimage(0, 0, &end);
				}
			}
		}
	}	
}

//�����˵����趨ѧ���ճ�

void SetStuSchedule(FILE *fp)
{
	loadimage(&setstuschedule, L"setstuschedule.jpg");//�����趨ѧ���ճ̽���
	putimage(0, 0, &setstuschedule);

	int position_x = 476;//����š�������
	int position_y = 92;//����š�������
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������С20����ʽ����
	wchar_t FinishStatus2[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus2, L"δ���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	int sequence;//������ʱ�洢ѡ��ѧ����ŵı���
	wchar_t sequence1[100];//������ʱ�洢ѡ��ѧ����ŵı���ת����洢���ַ�����
	wchar_t sequencenum[100];//����洢ѧ����ŵ��ַ����飬������ת��Ϊ�ַ�
	wchar_t sch_sequencenum[100];//����洢�ճ���ŵ��ַ����飬������ת��Ϊ�ַ�
	//��ʾ����ѧ���������ճ�
	outtextxy(position_x, position_y, _T("���    ��ʼʱ��    ��ֹʱ��    �ճ�����    ״̬"));//��ʾ����һ�б�ͷ
	for (int i = 0; i < nStudentNum; i++)
	{
		/*������ת��Ϊ�ַ����ĺ���*/
		//����outtextxy���ʱ�޷�ֱ�����int�����������Ҫ��int��ת��Ϊ�ַ���
		//�˺�����ȡ���취ö�٣�ö��1-10��
		if (stu[i].nSerialNum == 0)
			wcscpy_s(sequencenum, L"0");
		if (stu[i].nSerialNum == 1)
			wcscpy_s(sequencenum, L"1");
		if (stu[i].nSerialNum == 2)
			wcscpy_s(sequencenum, L"2");
		if (stu[i].nSerialNum == 3)
			wcscpy_s(sequencenum, L"3");
		if (stu[i].nSerialNum == 4)
			wcscpy_s(sequencenum, L"4");
		if (stu[i].nSerialNum == 5)
			wcscpy_s(sequencenum, L"5");
		if (stu[i].nSerialNum == 6)
			wcscpy_s(sequencenum, L"6");
		if (stu[i].nSerialNum == 7)
			wcscpy_s(sequencenum, L"7");
		if (stu[i].nSerialNum == 8)
			wcscpy_s(sequencenum, L"8");
		if (stu[i].nSerialNum == 9)
			wcscpy_s(sequencenum, L"9");
		if (stu[i].nSerialNum == 10)
			wcscpy_s(sequencenum, L"10");
		position_y += 20;//������һ��
		outtextxy(position_x, position_y, sequencenum);//��ʾ��Ӧѧ����ţ���ʾ�ڡ���š����·���
		outtextxy(position_x+20, position_y, stu[i].szName);//��ʾ��Ӧѧ���û���
		//��ʾ����ѧ�����ճ�
		for (int j = 1; j <= stu[i].nManagement; j++)//��ʾ����ѧ���û����е��ճ�
		{
			if (j == 0)
				wcscpy_s(sch_sequencenum, L"0");
			if (j == 1)
				wcscpy_s(sch_sequencenum, L"1");
			if (j == 2)
				wcscpy_s(sch_sequencenum, L"2");
			if (j == 3)
				wcscpy_s(sch_sequencenum, L"3");
			if (j == 4)
				wcscpy_s(sch_sequencenum, L"4");
			if (j == 5)
				wcscpy_s(sch_sequencenum, L"5");
			if (j == 6)
				wcscpy_s(sch_sequencenum, L"6");
			if (j == 7)
				wcscpy_s(sch_sequencenum, L"7");
			if (j == 8)
				wcscpy_s(sch_sequencenum, L"8");
			if (j == 9)
				wcscpy_s(sch_sequencenum, L"9");
			if (j == 10)
				wcscpy_s(sch_sequencenum, L"10");
			position_y += 20;//������һ��
			outtextxy(494, position_y, sch_sequencenum);//��ʾ���
			outtextxy(556, position_y, stu[i].Management1[j]);//��ʼʱ��
			outtextxy(676, position_y, stu[i].Management2[j]);//����ʱ��
			outtextxy(800, position_y, stu[i].Management3[j]);//�ճ�����
			outtextxy(916, position_y, stu[i].FinishStatus[j]);//���״̬
		}
	}
	//ѡ��ѧ�� 
	int i;
	do {
		InputBox(sequence1, 10, _T("��ѡ����Ҫ�趨��ѧ�������"));
		//��������ַ��������ֵ�ת��
		if (wcscmp(sequence1, L"0") == 0)
			sequence = 0;
		if (wcscmp(sequence1, L"1") == 0)
			sequence = 1;
		if (wcscmp(sequence1, L"2") == 0)
			sequence = 2;
		if (wcscmp(sequence1, L"3") == 0)
			sequence = 3;
		if (wcscmp(sequence1, L"4") == 0)
			sequence = 4;
		if (wcscmp(sequence1, L"5") == 0)
			sequence = 5;
		if (wcscmp(sequence1, L"6") == 0)
			sequence = 6;
		if (wcscmp(sequence1, L"7") == 0)
			sequence = 7;
		if (wcscmp(sequence1, L"8") == 0)
			sequence = 8;
		if (wcscmp(sequence1, L"9") == 0)
			sequence = 9;
		if (wcscmp(sequence1, L"10") == 0)
			sequence = 10;
		for (i = 0; i < nStudentNum; i++)
			if (sequence == stu[i].nSerialNum)
				break;
		if (i >= nStudentNum)//˵��û�ж�Ӧ��ѧ�����
			MessageBox(NULL, _T("�����������������"), _T("�趨ѧ���ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//����ѡ����ŵ�do whileѭ�� 
	} while (1);
	//����ѧ���趨�ճ�
	stu[sequence - 1].nManagement++;//���ճ��¼�����1
	InputBox(stu[sequence - 1].Management1[stu[sequence - 1].nManagement], 11, _T("���趨��ʼʱ��"));//��ʼʱ�� 
	InputBox(stu[sequence - 1].Management2[stu[sequence - 1].nManagement], 11, _T("��ѡ����Ҫ�趨��ѧ�������"));//��ֹʱ�� 
	InputBox(stu[sequence - 1].Management3[stu[sequence - 1].nManagement], 11, _T("��ѡ����Ҫ�趨��ѧ�������"));//�ճ�����
	wcscpy_s(stu[sequence - 1].FinishStatus[stu[sequence - 1].nManagement], FinishStatus2);//Ĭ������Ϊ"δ���" 
	MessageBox(NULL, _T("�趨�ɹ���"), _T("�趨ѧ���ճ�"), MB_SETFOREGROUND);
	SaveFile(fp);//�����ļ����溯��
}

//�����˵����޸�ѧ���ճ�
void ResetStuSchedule(FILE *fp)
{
	loadimage(&resetstuschedule, L"resetstuschedule.jpg");//�����ʦ�˽�ʦ��¼����
	putimage(0, 0, &resetstuschedule);

	int position_x = 476;//����š�������
	int position_y = 92;//����š�������
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������С20����ʽ����
	wchar_t FinishStatus1[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus1, L"���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	wchar_t FinishStatus2[MANAGELENGTH];//����һ��"δ���"�ַ����� 
	wcscpy_s(FinishStatus2, L"δ���");//����ֱ�ӳ�ʼ����Ҫ�ȶ����ٸ�ֵ
	int schedulesequence;//������ʱ�洢ѡ��ѧ���ճ̵���� 
	wchar_t schedulesequence1[100];//������ʱ�洢ѡ��ѧ���ճ����ת��������ַ�����
	int sequence;//������ʱ�洢ѡ��ѧ����ŵı���
	wchar_t sequence1[100];//������ʱ�洢ѡ��ѧ����ŵı���ת����洢���ַ�����
	wchar_t sequencenum[100];//����洢ѧ����ŵ��ַ����飬������ת��Ϊ�ַ�
	wchar_t sch_sequencenum[100];//����洢�ճ���ŵ��ַ����飬������ת��Ϊ�ַ�
	//��ʾ����ѧ���������ճ�
	outtextxy(position_x, position_y, _T("���    ��ʼʱ��    ��ֹʱ��    �ճ�����    ״̬"));//��ʾ����һ�б�ͷ
	for (int i = 0; i < nStudentNum; i++)
	{
		/*������ת��Ϊ�ַ����ĺ���*/
		//����outtextxy���ʱ�޷�ֱ�����int�����������Ҫ��int��ת��Ϊ�ַ���
		//�˺�����ȡ���취ö�٣�ö��1-10��
		if (stu[i].nSerialNum == 0)
			wcscpy_s(sequencenum, L"0");
		if (stu[i].nSerialNum == 1)
			wcscpy_s(sequencenum, L"1");
		if (stu[i].nSerialNum == 2)
			wcscpy_s(sequencenum, L"2");
		if (stu[i].nSerialNum == 3)
			wcscpy_s(sequencenum, L"3");
		if (stu[i].nSerialNum == 4)
			wcscpy_s(sequencenum, L"4");
		if (stu[i].nSerialNum == 5)
			wcscpy_s(sequencenum, L"5");
		if (stu[i].nSerialNum == 6)
			wcscpy_s(sequencenum, L"6");
		if (stu[i].nSerialNum == 7)
			wcscpy_s(sequencenum, L"7");
		if (stu[i].nSerialNum == 8)
			wcscpy_s(sequencenum, L"8");
		if (stu[i].nSerialNum == 9)
			wcscpy_s(sequencenum, L"9");
		if (stu[i].nSerialNum == 10)
			wcscpy_s(sequencenum, L"10");
		position_y += 20;//������һ��
		outtextxy(position_x, position_y, sequencenum);//��ʾ��Ӧѧ����ţ���ʾ�ڡ���š����·���
		outtextxy(position_x + 20, position_y, stu[i].szName);//��ʾ��Ӧѧ���û���
		//��ʾ����ѧ�����ճ�
		for (int j = 1; j <= stu[i].nManagement; j++)//��ʾ����ѧ���û����е��ճ�
		{
			if (j == 0)
				wcscpy_s(sch_sequencenum, L"0");
			if (j == 1)
				wcscpy_s(sch_sequencenum, L"1");
			if (j == 2)
				wcscpy_s(sch_sequencenum, L"2");
			if (j == 3)
				wcscpy_s(sch_sequencenum, L"3");
			if (j == 4)
				wcscpy_s(sch_sequencenum, L"4");
			if (j == 5)
				wcscpy_s(sch_sequencenum, L"5");
			if (j == 6)
				wcscpy_s(sch_sequencenum, L"6");
			if (j == 7)
				wcscpy_s(sch_sequencenum, L"7");
			if (j == 8)
				wcscpy_s(sch_sequencenum, L"8");
			if (j == 9)
				wcscpy_s(sch_sequencenum, L"9");
			if (j == 10)
				wcscpy_s(sch_sequencenum, L"10");
			position_y += 20;//������һ��
			outtextxy(494, position_y, sch_sequencenum);//��ʾ���
			outtextxy(556, position_y, stu[i].Management1[j]);//��ʼʱ��
			outtextxy(676, position_y, stu[i].Management2[j]);//����ʱ��
			outtextxy(800, position_y, stu[i].Management3[j]);//�ճ�����
			outtextxy(916, position_y, stu[i].FinishStatus[j]);//���״̬
		}
	}
	//ѡ��ѧ�� 
	int i;
	do {
		InputBox(sequence1, 10, _T("��ѡ����Ҫ�޸ĵ�ѧ�������"));
		//��������ַ��������ֵ�ת��
		if (wcscmp(sequence1, L"0") == 0)
			sequence = 0;
		if (wcscmp(sequence1, L"1") == 0)
			sequence = 1;
		if (wcscmp(sequence1, L"2") == 0)
			sequence = 2;
		if (wcscmp(sequence1, L"3") == 0)
			sequence = 3;
		if (wcscmp(sequence1, L"4") == 0)
			sequence = 4;
		if (wcscmp(sequence1, L"5") == 0)
			sequence = 5;
		if (wcscmp(sequence1, L"6") == 0)
			sequence = 6;
		if (wcscmp(sequence1, L"7") == 0)
			sequence = 7;
		if (wcscmp(sequence1, L"8") == 0)
			sequence = 8;
		if (wcscmp(sequence1, L"9") == 0)
			sequence = 9;
		if (wcscmp(sequence1, L"10") == 0)
			sequence = 10;
		for (i = 0; i < nStudentNum; i++)
			if (sequence == stu[i].nSerialNum)
				break;
		if (i >= nStudentNum)//˵��û�ж�Ӧ��ѧ�����
			MessageBox(NULL, _T("�����������������"), _T("�޸�ѧ���ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//����ѡ����ŵ�do whileѭ�� 
	} while (1);
	//ѡ���¼�
	int k;
	do {
		InputBox(schedulesequence1, 10, _T("��ѡ����Ҫ�޸ĵ��ճ����"));
		//��������ַ��������ֵ�ת��
		if (wcscmp(schedulesequence1, L"0") == 0)
			schedulesequence = 0;
		if (wcscmp(schedulesequence1, L"1") == 0)
			schedulesequence = 1;
		if (wcscmp(schedulesequence1, L"2") == 0)
			schedulesequence = 2;
		if (wcscmp(schedulesequence1, L"3") == 0)
			schedulesequence = 3;
		if (wcscmp(schedulesequence1, L"4") == 0)
			schedulesequence = 4;
		if (wcscmp(schedulesequence1, L"5") == 0)
			schedulesequence = 5;
		if (wcscmp(schedulesequence1, L"6") == 0)
			schedulesequence = 6;
		if (wcscmp(schedulesequence1, L"7") == 0)
			schedulesequence = 7;
		if (wcscmp(schedulesequence1, L"8") == 0)
			schedulesequence = 8;
		if (wcscmp(schedulesequence1, L"9") == 0)
			schedulesequence = 9;
		if (wcscmp(sequence1, L"10") == 0)
			schedulesequence = 10;
		for (k = 1; k <= stu[sequence - 1].nManagement; k++)
			if (k == schedulesequence)
				break;
		if (k > stu[sequence - 1].nManagement)//˵�����������û���������ճ���ŵķ�Χ�� 
			MessageBox(NULL, _T("����������"), _T("�޸�ѧ���ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//�˳�ѡ���ճ���ŵ�ѭ�� 
	} while (1);

	//�޸��ճ�  
	InputBox(stu[sequence - 1].Management1[schedulesequence], 11, _T("�����¹滮��ʼʱ��"));//��ʼʱ�� 
	InputBox(stu[sequence - 1].Management2[schedulesequence], 11, _T("�����¹滮��ֹʱ��"));//��ֹʱ�� 
	InputBox(stu[sequence - 1].Management3[schedulesequence], 11, _T("�����¹滮�ճ�����"));//�ճ�����
	MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸�ѧ���ճ�"), MB_SETFOREGROUND);
	do {//�޸�״̬ 
		InputBox(stu[sequence - 1].FinishStatus[schedulesequence], 11, _T("�����¹滮���״̬�����/δ��ɣ�"));
		if (wcscmp(stu[sequence - 1].FinishStatus[schedulesequence], FinishStatus1) == 0)
		{
			MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸�ѧ���ճ�"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else if (wcscmp(stu[studentnum].FinishStatus[sequence - 1], FinishStatus2) == 0)
		{
			MessageBox(NULL, _T("�޸ĳɹ���"), _T("�޸�ѧ���ճ�"), MB_SETFOREGROUND);
			SaveFile(fp);//�����ļ����溯��
			break;
		}
		else
			MessageBox(NULL, _T("�������"), _T("�޸�ѧ���ճ�"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//�����˵����鿴ѧ�����״̬
void CheckFinishedCondition()
{
	loadimage(&checkfinishedcondition, L"checkfinishedcondition.jpg");//�����ʦ�˽�ʦ��¼����
	putimage(0, 0, &checkfinishedcondition);

	int position_x = 476;//����š�������
	int position_y = 92;//����š�������
	setbkmode(TRANSPARENT);//�������屳��Ϊ͸��
	settextcolor(COLORREF(RGB(0, 0, 0)));//����������ɫΪ��ɫ
	settextstyle(20, 0, _T("����"));//���������С20����ʽ����
	wchar_t sequencenum[100];//����洢ѧ����ŵ��ַ����飬������ת��Ϊ�ַ�
	wchar_t sch_sequencenum[100];//����洢�ճ���ŵ��ַ����飬������ת��Ϊ�ַ�
	//��ʾ����ѧ���������ճ�
	outtextxy(position_x, position_y, _T("���    ��ʼʱ��    ��ֹʱ��    �ճ�����    ״̬"));//��ʾ����һ�б�ͷ
	for (int i = 0; i < nStudentNum; i++)
	{
		/*������ת��Ϊ�ַ����ĺ���*/
		//����outtextxy���ʱ�޷�ֱ�����int�����������Ҫ��int��ת��Ϊ�ַ���
		//�˺�����ȡ���취ö�٣�ö��1-10��
		if (stu[i].nSerialNum == 0)
			wcscpy_s(sequencenum, L"0");
		if (stu[i].nSerialNum == 1)
			wcscpy_s(sequencenum, L"1");
		if (stu[i].nSerialNum == 2)
			wcscpy_s(sequencenum, L"2");
		if (stu[i].nSerialNum == 3)
			wcscpy_s(sequencenum, L"3");
		if (stu[i].nSerialNum == 4)
			wcscpy_s(sequencenum, L"4");
		if (stu[i].nSerialNum == 5)
			wcscpy_s(sequencenum, L"5");
		if (stu[i].nSerialNum == 6)
			wcscpy_s(sequencenum, L"6");
		if (stu[i].nSerialNum == 7)
			wcscpy_s(sequencenum, L"7");
		if (stu[i].nSerialNum == 8)
			wcscpy_s(sequencenum, L"8");
		if (stu[i].nSerialNum == 9)
			wcscpy_s(sequencenum, L"9");
		if (stu[i].nSerialNum == 10)
			wcscpy_s(sequencenum, L"10");
		position_y += 20;//������һ��
		outtextxy(position_x, position_y, sequencenum);//��ʾ��Ӧѧ����ţ���ʾ�ڡ���š����·���
		outtextxy(position_x + 20, position_y, stu[i].szName);//��ʾ��Ӧѧ���û���
		//��ʾ����ѧ�����ճ�
		for (int j = 1; j <= stu[i].nManagement; j++)//��ʾ����ѧ���û����е��ճ�
		{
			if (j == 0)
				wcscpy_s(sch_sequencenum, L"0");
			if (j == 1)
				wcscpy_s(sch_sequencenum, L"1");
			if (j == 2)
				wcscpy_s(sch_sequencenum, L"2");
			if (j == 3)
				wcscpy_s(sch_sequencenum, L"3");
			if (j == 4)
				wcscpy_s(sch_sequencenum, L"4");
			if (j == 5)
				wcscpy_s(sch_sequencenum, L"5");
			if (j == 6)
				wcscpy_s(sch_sequencenum, L"6");
			if (j == 7)
				wcscpy_s(sch_sequencenum, L"7");
			if (j == 8)
				wcscpy_s(sch_sequencenum, L"8");
			if (j == 9)
				wcscpy_s(sch_sequencenum, L"9");
			if (j == 10)
				wcscpy_s(sch_sequencenum, L"10");
			position_y += 20;//������һ��
			outtextxy(494, position_y, sch_sequencenum);//��ʾ���
			outtextxy(556, position_y, stu[i].Management1[j]);//��ʼʱ��
			outtextxy(676, position_y, stu[i].Management2[j]);//����ʱ��
			outtextxy(800, position_y, stu[i].Management3[j]);//�ճ�����
			outtextxy(916, position_y, stu[i].FinishStatus[j]);//���״̬
		}
	}
}

/*������*/
int main()
{
	FILE *fp;
	fopen_s(&fp,"alldate.dat", "rb");
	/*���ļ��ж���ȫ�ֱ���*/
	fread(&nStudentNum, 4, 1, fp);
	fread(&nTeacherNum, 4, 1, fp);
	fread(&nStuFlag, 4, 1, fp);
	fread(&nTeacherFlag, 4, 1, fp);
	fread(&studentnum, 4, 1, fp);
	fread(&teachernum, 4, 1, fp);
	//����ѧ���ṹ������
	for (int i = 0; i < nStudentNum; i++)
		fread(&stu[i], sizeof(struct student), 1, fp);
	//�����ʦ�ṹ������ 
	for (int i = 0; i < nTeacherNum; i++)
		fread(&teacher[i], sizeof(struct teacher), 1, fp);
	fclose(fp);
	/*�������*/

	initgraph(1366, 700);//���崰�ڴ�С
	Welcome(fp);//����Welcome
	
	return 0;
}
