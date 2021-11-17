/************************************************************************
程序名：日程管理系统
版本号：2.0
开发小组：天码行空组（符泽林、冉弩、邓文豪）
程序功能：1）设计学生端口和教师端口，学生端学生自我管理，教师端教师监督管理
		  2）注册、登录账号，修改密码
		  3）添加、修改、删除、显示日程
		  4）文件自动保存
		  5) 精美界面，界面友好，交互性强
		  6）系统会进行自动保存
		  7）登录后退出需要重新登录
************************************************************************/

/*对库函数的定义*/
#include <graphics.h>      // 引用图形库头文件
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <conio.h>
#include<tchar.h>

/*宏定义*/
#define NUMBER 100//定义可容纳（学生/教师）的用户数量 
#define MANAGELENGTH 30//定义事件长度（包含时间） 
#define STRLENGTH 30//定义用户名长度
#define NUMLENGTH 12//定义密码长度 

/*定义图片*/
IMAGE welcome;//欢迎界面
IMAGE welcome_button;//ENTER按钮
IMAGE startup;//初始界面
IMAGE stu1;//学生端初始
IMAGE stu1_return;
IMAGE stu1_exit;
IMAGE stu_register;//学生端:创建账户
IMAGE stu_logon;//学生端:学生登录
IMAGE stu_resetpassword;//学生端：修改密码
IMAGE stu_schedulemanagement1;//学生端：日程管理界面1
IMAGE stu_schedulemanagement2;//学生端：日程管理界面2
IMAGE stu_schedulemanagement2_return;
IMAGE stu_schedulemanagement2_exit;
IMAGE teacher1;//教师端初始
IMAGE teacher1_return;
IMAGE teacher1_exit;
IMAGE teacher_register;//教师端：创建账户
IMAGE teacher_logon;//教师端：教师登录
IMAGE teacher_resetpassword;//教师端:修改密码
IMAGE teacher_schedulemanagement1;//教师端：日程管理界面1
IMAGE teacher_schedulemanagement2;//教师端：日程管理界面2
IMAGE teacher_schedulemanagement2_return;
IMAGE teacher_schedulemanagement2_exit;
IMAGE createschedule;//学生端：创建日程
IMAGE resetschedule;//学生端：修改日程
IMAGE finishedcondition;//学生端：完成状态
IMAGE setstuschedule;//教师端：设定学生日程
IMAGE resetstuschedule;//教师端：修改学生日程
IMAGE checkfinishedcondition;//教师端：查看完成状态
IMAGE end;//结束界面

/*全局变量*/
int nStudentNum = 0;//注册的学生编号（从0开始）（同时也代表着注册人数） 
int nTeacherNum = 0;//注册的教师编号 （第一个注册的用户编号为0） 
int nStuFlag = 0;//定义判断学生是否登录的标志变量
int nTeacherFlag = 0;//定义判断教师是否登录的标志变量 
int studentnum;//定义登录的学生编号
int teachernum;//定义登录的教师编号

/*定义学生结构体数组*/
struct student
{
	wchar_t szName[STRLENGTH];//定义学生用户名
	wchar_t password1[NUMLENGTH];//定义学生账户密码
	wchar_t password2[NUMLENGTH];//定义学生二次输入密码
	int nSerialNum;//定义学生序号(从1开始) 
	int nManagement = 0;//定义学生的日程事件数  
	wchar_t Management1[10][MANAGELENGTH];//定义存储该学生设定的初始时间字符数组      设定一个学生最多设定10个事件 
	wchar_t Management2[10][MANAGELENGTH];//定义存储该学生设定的截止时间字符数组
	wchar_t Management3[10][MANAGELENGTH];//定义存储该学生设定的日程内容字符数组
	wchar_t FinishStatus[10][MANAGELENGTH];//定义每个学生设定的日程的完成状态 
}stu[NUMBER];

/*定义教师的结构体数组*/
struct  teacher
{
	wchar_t szName[STRLENGTH];//定义教师用户名
	wchar_t password1[NUMLENGTH];//定义教师账户密码
	wchar_t password2[NUMLENGTH];//定义教师二次输入密码 
	int nSerialNum;//定义老师序号(从1开始) 
}teacher[NUMBER];

/*函数声明***********************************************/

/*欢迎界面函数*/
void Welcome(FILE *fp);

/*文件保存函数*/
void SaveFile(FILE *fp);

/*一级主菜单函数*/
void Select_MainMenu(FILE *fp);

/*二级菜单函数*/

//二级菜单学生端目录显示
void OutputStu_SecondMenu(FILE *fp);
//二级菜单教师端目录显示
void OutputTeacher_SecondMenu(FILE *fp);
//二级菜单：学生创建账户 
void Stu_Register(FILE *fp);
// 二级菜单：学生登录
void Stu_Logon();
//二级菜单：学生修改密码
void Stu_ResetPassword(FILE *fp);
//二级菜单：学生日程管理
void Stu_ScheduleManagement(FILE *fp);
//二级菜单：教师创建账户
void Teacher_Register(FILE *fp);
//二级菜单：教师登录
void Teacher_Logon();
//二级菜单：教师修改密码
void Teacher_ResetPassword(FILE *fp);
//二级菜单：教师对学生日程管理
void Teacher_ScheduleManagement(FILE *fp);

/*二级菜单结束*/

/*三级菜单*/

//三级菜单：新建日程 
void CreateSchedule(FILE *fp);
//三级菜单：修改日程
void ResetSchedule(FILE *fp);
//三级菜单：完成状态
void FinishedCondition(FILE *fp);
//三级菜单：设定学生日程
void SetStuSchedule(FILE *fp);
//三级菜单：修改学生日程
void ResetStuSchedule(FILE *fp);
//三级菜单：查看学生完成状态
void CheckFinishedCondition();

/*三级菜单结束*/

/*函数声明结束********************************************/

//欢迎界面函数
void Welcome(FILE *fp)
{
	loadimage(&welcome, L"welcome.jpg");//导入欢迎界面（特别注意：双引号里面不能有空格，要跟图片命名完全一致）
	putimage(0, 0, &welcome);//显示欢迎界面
	/*下面进行鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 232 && msg.x < 498 && msg.y > 478 && msg.y < 543)//鼠标点击特定区域，即ENTER按钮所在区域
				{
					loadimage(&welcome_button, L"welcome_button.jpg");//导入橙色按钮图片
					putimage(0, 0, &welcome_button);//显示橙色按钮图片
					Sleep(100);//延时，降低CPU占用率，并且做到点击效果
					Select_MainMenu(fp);//调用一级主菜单选项函数
				}
			}
		}
	}
}

//文件保存函数
void SaveFile(FILE *fp)
{
	fopen_s(&fp, "alldate.dat", "wb");
	//向文件输出全局变量
	fwrite(&nStudentNum, 4, 1, fp);
	fwrite(&nTeacherNum, 4, 1, fp);
	fwrite(&nStuFlag, 4, 1, fp);
	fwrite(&nTeacherFlag, 4, 1, fp);
	fwrite(&studentnum, 4, 1, fp);
	fwrite(&teachernum, 4, 1, fp);
	//输出学生结构体数据
	for (int i = 0; i < nStudentNum; i++)
		fwrite(&stu[i], sizeof(struct student), 1, fp);
	//输出教师结构体数组 
	for (int i = 0; i < nTeacherNum; i++)
		fwrite(&teacher[i], sizeof(struct teacher), 1, fp);
	fclose(fp);
}

//一级主菜单选项(学生端、教师端)函数
void Select_MainMenu(FILE *fp)
{
	loadimage(&startup, L"startup.jpg");//导入初始界面
	putimage(0, 0, &startup);//显示初始界面
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true)
	{
		while (MouseHit())
		{
			msg = GetMouseMsg();
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//鼠标点击特定区域，即“学生端”按钮所在区域
					OutputStu_SecondMenu(fp);//调用学生端函数
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//鼠标点击特定区域，即“教师端”按钮所在区域
					OutputTeacher_SecondMenu(fp);//调用教师端函数
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

//二级菜单学生端目录显示
void OutputStu_SecondMenu(FILE *fp)
{
	loadimage(&stu1, L"stu1.jpg");//导入学生端界面
	putimage(0, 0, &stu1);//显示学生端界面
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“教师端”按钮所在区域
					OutputTeacher_SecondMenu(fp);//调用教师端函数
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击特定区域，即“STUDENT”按钮所在区域
					Select_MainMenu(fp);//调用一级主菜单选项函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 71 && msg.y < 134)//鼠标点击特定区域，即“创建账户”按钮所在区域
					Stu_Register(fp);//调用学生创建账户函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 228)//鼠标点击特定区域，即“学生登录”按钮所在区域
					Stu_Logon();//调用学生登录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 252 && msg.y < 318)//鼠标点击特定区域，即“修改密码”按钮所在区域
					Stu_ResetPassword(fp);//调用学生修改密码函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 344 && msg.y < 413)//鼠标点击特定区域，即“日程管理”按钮所在区域
					if(nStuFlag == 1)//已登录
						Stu_ScheduleManagement(fp);//调用学生日程管理函数
					else 
						MessageBox(NULL, _T("您还未登录"), _T("日程管理"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{

					loadimage(&stu1_return, L"stu1_return.jpg");
					putimage(0, 0, &stu1_return);
					Sleep(100);
					Welcome(fp);
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					/*退出登录（使得下次进入系统后重新登录）*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//调用文件保存函数
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

//二级菜单：教师端目录显示
void OutputTeacher_SecondMenu(FILE *fp)
{
	loadimage(&teacher1, L"teacher1.jpg");//导入教师端界面
	putimage(0, 0, &teacher1);//显示教师端界面
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//鼠标点击特定区域，即“学生端”按钮所在区域
					OutputStu_SecondMenu(fp);//调用学生端函数
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击特定区域，即“STUDENT”按钮所在区域
					Select_MainMenu(fp);//调用一级主菜单函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 69 && msg.y < 135)//鼠标点击特定区域，即“创建账户”按钮所在区域
					Teacher_Register(fp);//调用教师创建账户函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 162 && msg.y < 227)//鼠标点击特定区域，即“教师登录”按钮所在区域
					Teacher_Logon();//调用教师登录函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 254 && msg.y < 320)//鼠标点击特定区域，即“修改密码”按钮所在区域
					Teacher_ResetPassword(fp);//调用教师修改密码函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 347 && msg.y < 410)//鼠标点击特定区域，即“学生日程管理”按钮所在区域
					if(nTeacherFlag == 1)//已登录
						Teacher_ScheduleManagement(fp);//调用教师对学生日程管理函数
					else 
						MessageBox(NULL, _T("您还未登录"), _T("学生日程管理"), MB_ICONEXCLAMATION | MB_SETFOREGROUND);
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{

					loadimage(&teacher1_return, L"teacher1_return.jpg");
					putimage(0, 0, &teacher1_return);
					Sleep(100);
					Welcome(fp);
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					/*退出登录（使得下次进入系统后重新登录）*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//调用文件保存函数
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

//二级菜单：学生创建账户
void Stu_Register(FILE *fp)
{
	loadimage(&stu_register, L"stu_register.jpg");//进入学生端创建账户界面
	putimage(0, 0, &stu_register);

	/*输入用户名*/
	int i;
	do{
		InputBox(stu[nStudentNum].szName, 10, _T("请输入用户名"));//提示用户输入用户名
		//接下来查找用户信息表中的内容，比较新输入的用户名是否存在，如果存在，系统给出提示
		for (i = 0; i < nStudentNum; i++)
		{
			if (wcscmp(stu[i].szName, stu[nStudentNum].szName) == 0)
			{
				MessageBox(NULL, _T("该用户已经存在，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);//输出提示，提醒用户
				break;//跳出for循环
					  //修复了1.0版本用户注册时出现的bug
			}
				
		}
		if (i >= nStudentNum)//说明没有找到重复的用户名 
			break;
	  } while (1);//如果用户名重复则一直循环，直到不重复时跳出循环 
				 //输入用户名函数结束 

	/*下面设置用户密码*/
	 do{
		  InputBox(stu[nStudentNum].password1, 10, _T("请设置6位数密码"));//提示用户输入密码
		  InputBox(stu[nStudentNum].password2, 10, _T("请确认密码"));//提示用户确认密码
		  if (wcscmp(stu[nStudentNum].password1, stu[nStudentNum].password2) != 0)//两次输入密码不相等 
			  MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("创建账户"), MB_ICONSTOP|MB_SETFOREGROUND);
		  else
		  {
			  MessageBox(NULL, _T("注册成功！"), _T("创建账户"), MB_SETFOREGROUND);
			  //参数分别为：消息框拥有的窗口、消息框的内容、消息框的标题、标志集(多个标志用"与"(|)符号连接)
			 //最后的参数表示设置消息框为前景窗口
			  nStudentNum++;//代表下一个将要注册的学生用户的编号
			  stu[nStudentNum - 1].nSerialNum = nStudentNum;//加一 
			  SaveFile(fp);//调用文件保存函数
			  break;
		  }
		} while (1);
}

//二级菜单：学生登录
void Stu_Logon()
{
	loadimage(&stu_logon, L"stu_logon.jpg");//进入学生端学生登录界面
	putimage(0, 0, &stu_logon);

	/*输入用户名*/
	int i;
	wchar_t username[STRLENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[NUMLENGTH];//定义一个临时存储密码的字符数组 
	do{
		InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
		for (i = 0; i < nStudentNum; i++)
			if (wcscmp(username, stu[i].szName) == 0)//找到了 
			{
				studentnum = i; 
				break;//跳出for循环
			}//记录输入用户名所对应的学生编号，即登录的用户所对应的编号 

		if (i >= nStudentNum)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//找到了此用户名，退出输入用户名的循环，进入输入密码模块 
	  }while (1);

	/*输入密码模块*/
	do {
		InputBox(password, 10, _T("请输入密码"));//提示用户输入密码，输入给临时存储密码的字符数组
		if (wcscmp(password, stu[studentnum].password1) == 0)//密码符合 
		{
			MessageBox(NULL, _T("登录成功！"), _T("学生登录"), MB_SETFOREGROUND);
			nStuFlag = 1;//标志着已经成功登录 
			break;
		}//结束密码输入模块 
		else
			MessageBox(NULL, _T("密码错误"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//二级菜单：学生修改密码
void Stu_ResetPassword(FILE *fp)
{
	loadimage(&stu_resetpassword, L"stu_resetpassword.jpg");//进入学生端修改密码界面
	putimage(0, 0, &stu_resetpassword);

	//studentnum 记录修改密码的学生用户的编号(即登录的学生用户的编号） 
	int i;
	wchar_t username[STRLENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[NUMLENGTH];//定义一个临时存储密码的字符数组 
	wchar_t resetpassword[NUMLENGTH];//定义一个临时存储修改后密码的字符数组 
	do {
		InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
		for (i = 0; i < nStudentNum; i++)
			if (wcscmp(username, stu[i].szName) == 0)//找到了 
			{
				studentnum = i; 
				break;
			}//记录输入用户名所对应的学生编号，即登录的用户所对应的编号 

		if (i >= nStudentNum)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//找到了此用户名，退出输入用户名的循环，进入修改密码模块 
	} while (1);

	do {
		InputBox(password, 10, _T("请输入原始密码"));
		if (wcscmp(password, stu[studentnum].password1) == 0)//密码符合
		{
			InputBox(resetpassword, 10, _T("密码正确，请输入6位数修改密码"));
			wcscpy_s(stu[studentnum].password1, resetpassword);//将原密码改为修改后的密码(wcscpy相当于strcopy)
			MessageBox(NULL, _T("修改密码成功！"), _T("修改密码"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;//退出修改密码模块 
		}
		else
			MessageBox(NULL, _T("密码错误"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//二级菜单：学生日程管理
void Stu_ScheduleManagement(FILE *fp)
{
	loadimage(&stu_schedulemanagement1, L"stu_schedulemanagement1.jpg");//进入学生端日程管理界面1
	putimage(0, 0, &stu_schedulemanagement1);
	Sleep(100);//延时，显示点击效果
	loadimage(&stu_schedulemanagement2, L"stu_schedulemanagement2.jpg");//进入学生端日程管理界面2
	putimage(0, 0, &stu_schedulemanagement2);
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 80 && msg.x < 365 && msg.y > 92 && msg.y < 159)//鼠标点击特定区域，即“新建日程”按钮所在区域
					CreateSchedule(fp);//调用新建日程函数
				if (msg.x > 80 && msg.x < 365 && msg.y > 219 && msg.y < 287)//鼠标点击特定区域，即“修改日程”按钮所在区域
					ResetSchedule(fp);//调用修改日程函数
				if (msg.x > 80 && msg.x < 365 && msg.y > 344 && msg.y < 408)//鼠标点击特定区域，即“完成状态”按钮所在区域
					FinishedCondition(fp);//调用完成状态函数
				if (msg.x > 980 && msg.x < 1046 && msg.y > 554 && msg.y < 619)//点击“教师端”按钮所在区域
					OutputTeacher_SecondMenu(fp);//调用教师端函数
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击特定区域，即“STUDENT”按钮所在区域
					Select_MainMenu(fp);//调用一级主菜单选项函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{

					loadimage(&stu_schedulemanagement2_return, L"stu_schedulemanagement2_return.jpg");
					putimage(0, 0, &stu_schedulemanagement2_return);
					Sleep(100);
					OutputStu_SecondMenu(fp);//调用二级菜单学生端
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					/*退出登录（使得下次进入系统后重新登录）*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//调用文件保存函数
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

//三级菜单：新建日程
void CreateSchedule(FILE *fp)
{
	loadimage(&createschedule, L"createschedule.jpg");//进入新建日程界面
	putimage(0, 0, &createschedule);
	wchar_t FinishStatus1[MANAGELENGTH];//定义一个"完成"字符数组
	wcscpy_s(FinishStatus1, L"完成");//不能直接初始化，要先定义再赋值
	wchar_t FinishStatus2[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus2, L"未完成");//不能直接初始化，要先定义再赋值
	stu[studentnum].nManagement++;//让日程事件数加1
	InputBox(stu[studentnum].Management1[stu[studentnum].nManagement], 11, _T("初始时间（例：2018.09.08）"));//初始时间
	InputBox(stu[studentnum].Management2[stu[studentnum].nManagement], 11, _T("截至时间（例：2018.09.23）"));//截止时间
	InputBox(stu[studentnum].Management3[stu[studentnum].nManagement], 11, _T("日程内容（例：2018.09.08）"));//日程内容
	do {
		InputBox(stu[studentnum].FinishStatus[stu[studentnum].nManagement], 11, _T("设置状态（完成/未完成）"));//设置状态
		if (wcscmp(stu[studentnum].FinishStatus[stu[studentnum].nManagement], FinishStatus1) == 0)
		{
			MessageBox(NULL, _T("新建成功！"), _T("新建日程"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else if (wcscmp(stu[studentnum].FinishStatus[stu[studentnum].nManagement], FinishStatus2) == 0)
		{
			MessageBox(NULL, _T("新建成功！"), _T("新建日程"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else
			MessageBox(NULL, _T("输入错误"), _T("新建日程"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//三级菜单;修改日程
void ResetSchedule(FILE *fp)
{
	loadimage(&resetschedule, L"resetschedule.jpg");//进入修改日程界面
	putimage(0, 0, &resetschedule);
	wchar_t FinishStatus1[MANAGELENGTH];//定义一个"完成"字符数组
	wcscpy_s(FinishStatus1, L"完成");//不能直接初始化，要先定义再赋值
	wchar_t FinishStatus2[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus2, L"未完成");
	wchar_t sequencenum[100];//定义存储序号的字符数组
	wchar_t tem_sequencenum[100];//定义临时存储序号的字符数组
	int sequence;//定义临时存储选定序号的变量 
	//wchar_t resetschedule[MANAGELENGTH];//定义临时存储修改后日程的数组
	//wchar_t finishstatus[MANAGELENGTH];//定义临时存储修改后完成状态的数组 
	//显示日程
	int position_x = 476;//“序号”横坐标
	int position_y = 92;//“序号”纵坐标
	setbkmode(TRANSPARENT);//设置字体背景为透明
	settextcolor(COLORREF(RGB(0,0,0)));//设置字体颜色为黑色
	settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
	outtextxy(position_x, position_y, _T("序号    初始时间    截止时间    日程内容    状态"));//显示表格第一行表头
	for (int i = 1; i <= stu[studentnum].nManagement; i++)//显示出该学生用户所有的日程
	{
		/*将数字转化为字符串的函数*/
		//由于outtextxy输出时无法直接输出int型量，因此需要将int型转化为字符串
		//此函数采取笨办法枚举（枚举1-10）
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
		position_y+= 20;//向下推一行
		outtextxy(494, position_y, sequencenum);//显示序号
		outtextxy(556, position_y, stu[studentnum].Management1[i]);//初始时间
		outtextxy(676, position_y, stu[studentnum].Management2[i]);//截至时间
		outtextxy(800, position_y, stu[studentnum].Management3[i]);//日程内容
		outtextxy(916, position_y, stu[studentnum].FinishStatus[i]);//完成状态
	}
	//选择事件
	int i;
	do {
		InputBox(tem_sequencenum, 10, _T("请选择需要修改的日程序号"));
		//下面进行字符串与数字的转化
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

		if (i > stu[studentnum].nManagement)//说明输入的数字没有在所有日程序号的范围内 
			MessageBox(NULL, _T("请重新输入"), _T("修改日程"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//退出选择日程序号的循环 
	} while (1);

	//修改日程  
	InputBox(stu[studentnum].Management1[sequence], 11, _T("请重新规划初始时间（例：2018.09.08）"));//初始时间
	InputBox(stu[studentnum].Management2[sequence], 11, _T("请重新规划截至时间（例：2018.09.23）"));//截止时间
	InputBox(stu[studentnum].Management3[sequence], 11, _T("请重新规划日程内容（例：2018.09.08）"));//日程内容

	do {//修改状态 
		InputBox(stu[studentnum].FinishStatus[sequence], 11, _T("请重新规划完成状况:(完成/未完成)"));
		if (wcscmp(stu[studentnum].FinishStatus[sequence], FinishStatus1) == 0)
		{
			MessageBox(NULL, _T("修改成功！"), _T("修改日程"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else if (wcscmp(stu[studentnum].FinishStatus[sequence], FinishStatus2) == 0)
		{
			MessageBox(NULL, _T("修改成功！"), _T("修改日程"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else
			MessageBox(NULL, _T("输入错误"), _T("修改日程"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//三级菜单：完成状态(显示该登录用户的所有日程并重新规划完成状态)
void FinishedCondition(FILE *fp)
{
	loadimage(&finishedcondition, L"finishedcondition.jpg");//进入完成状态界面
	putimage(0, 0, &finishedcondition);
	//显示日程
	wchar_t sequencenum[100];//定义存储序号的字符数组
	int position_x = 476;//“序号”横坐标
	int position_y = 92;//“序号”纵坐标
	setbkmode(TRANSPARENT);//设置字体背景为透明
	settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
	settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式宋体
	outtextxy(position_x, position_y, _T("序号    初始时间    截止时间    日程内容    状态"));//显示表格第一行表头
	for (int i = 1; i <= stu[studentnum].nManagement; i++)//显示出该学生用户所有的日程
	{
		/*将数字转化为字符串的函数*/
		//由于outtextxy输出时无法直接输出int型量，因此需要将int型转化为字符串
		//此函数采取笨办法枚举（枚举1-10）
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
		position_y += 20;//向下推一行
		outtextxy(494, position_y, sequencenum);//显示序号
		outtextxy(556, position_y, stu[studentnum].Management1[i]);//初始时间
		outtextxy(676, position_y, stu[studentnum].Management2[i]);//截至时间
		outtextxy(800, position_y, stu[studentnum].Management3[i]);//日程内容
		outtextxy(916, position_y, stu[studentnum].FinishStatus[i]);//完成状态
	}
	//选择事件
	int i;
	int sequence;//定义需要修改的日程序号
	wchar_t sequence1[100];//定义临时存储选择的日程序号的字符数组
	wchar_t FinishStatus[MANAGELENGTH];//定义一个临时存储完成状态的字符数组
	wchar_t FinishStatus1[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus1, L"完成");//不能直接初始化，要先定义再赋值
	wchar_t FinishStatus2[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus2, L"未完成");//不能直接初始化，要先定义再赋值
	do {
		InputBox(sequence1, 10, _T("请选择需要修改的日程序号"));
		//下面进行字符串与数字的转化
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

		if (i > stu[studentnum].nManagement)//说明输入的数字没有在所有日程序号的范围内 
			MessageBox(NULL, _T("请重新输入"), _T("完成状态"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//退出选择日程序号的循环 
	} while (1);
	//勾选状态 
	do {
		InputBox(FinishStatus, 10, _T("请重新规划完成状况:(完成/未完成)"));
		if (wcscmp(FinishStatus, FinishStatus1) == 0)
		{
			wcscpy_s(stu[studentnum].FinishStatus[sequence], FinishStatus1);//完成
			MessageBox(NULL, _T("修改成功！"), _T("修改状态"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else if (wcscmp(FinishStatus, FinishStatus2) == 0)
		{
			wcscpy_s(stu[studentnum].FinishStatus[sequence], FinishStatus2);//未完成
			MessageBox(NULL, _T("修改成功！"), _T("修改状态"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else
			MessageBox(NULL, _T("输入错误"), _T("修改状态"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);

}

//二级菜单：教师创建账户
void Teacher_Register(FILE *fp)
{
	loadimage(&teacher_register, L"teacher_register.jpg");//进入教师端创建账户界面
	putimage(0, 0, &teacher_register);

	/*输入用户名*/
	int i;
	do {
		InputBox(teacher[nTeacherNum].szName, 10, _T("请输入用户名"));//提示用户输入用户名
		//接下来查找用户信息表中的内容，比较新输入的用户名是否存在，如果存在，系统给出提示
		for (i = 0; i < nTeacherNum; i++)
		{
			if (wcscmp(teacher[i].szName, teacher[nTeacherNum].szName) == 0)
			{
				MessageBox(NULL, _T("该用户已经存在，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);//输出提示，提醒用户
				break;//跳出for循环
			}
		}
		if (i >= nTeacherNum)//说明没有找到与已注册用户重复的用户名 
			break;
	} while (1);//如果用户名重复则一直循环，直到不重复时跳出循环 
			  //输入用户名函数结束 
  /*下面设置用户密码*/
	do {
		InputBox(teacher[nTeacherNum].password1, 10, _T("请设置6位数密码"));//提示用户输入密码
		InputBox(teacher[nTeacherNum].password2, 10, _T("请确认密码"));//提示用户确认密码
		if (wcscmp(teacher[nTeacherNum].password1, teacher[nTeacherNum].password2) != 0)//两次输入密码不相等 
			MessageBox(NULL, _T("两次输入不一致，请重新输入"), _T("创建账户"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
		{
			MessageBox(NULL, _T("注册成功！"), _T("创建账户"), MB_SETFOREGROUND);
			nTeacherNum++;//表示下一次将要注册的教师用户的编号 
			SaveFile(fp);//调用文件保存函数
			break;
		}
	} while (1);
}

//二级菜单:教师登录
void Teacher_Logon()
{
	loadimage(&teacher_logon, L"teacher_logon.jpg");//进入教师端教师登录界面
	putimage(0, 0, &teacher_logon);

	/*输入用户名*/
	int i;
	wchar_t username[STRLENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[NUMLENGTH];//定义一个临时存储密码的字符数组 
	do {
		InputBox(username, 10, _T("请输入用户名"));//提示用户输入用户名，输入给临时存储用户名的字符数组
		for (i = 0; i < nTeacherNum; i++)
			if (wcscmp(username, teacher[i].szName) == 0)//找到了 
			{
				teachernum = i;
				break;
			}//记录输入用户名所对应的教师编号，即登录的用户所对应的编号 

		if (i >= nTeacherNum)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("教师登录"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//找到了此用户名，退出输入用户名的循环，进入输入密码模块 
	} while (1);
	
	/*输入密码模块*/
	do {
		InputBox(password, 10, _T("请输入密码"));//提示用户输入密码，输入给临时存储密码的字符数组
		if (wcscmp(password, teacher[teachernum].password1) == 0)//密码符合 
		{
			MessageBox(NULL, _T("登录成功！"), _T("教师登录"), MB_SETFOREGROUND);
			nTeacherFlag = 1;//标志教师用户登录成功 
			break;
		}//结束密码输入模块 
		else
			MessageBox(NULL, _T("密码错误"), _T("学生登录"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//二级菜单：教师修改密码
void Teacher_ResetPassword(FILE *fp)
{
	loadimage(&teacher_resetpassword, L"teacher_resetpassword.jpg");//进入教师端修改密码界面
	putimage(0, 0, &teacher_resetpassword);

	//teachernum 记录修改密码的用户的编号(即登录的教师用户的编号) 
	int i;
	wchar_t username[STRLENGTH];//定义一个临时存储用户名的字符数组 
	wchar_t password[NUMLENGTH];//定义一个临时存储密码的字符数组 
	wchar_t resetpassword[NUMLENGTH];//定义一个临时存储修改后密码的字符数组 
	do {
		InputBox(username, 10, _T("请输入用户名"));
		for (i = 0; i < nTeacherNum; i++)
			if (wcscmp(username, teacher[i].szName) == 0)//找到了 
			{
				teachernum = i; 
				break;
			}//记录输入用户名所对应的学生编号，即登录的用户所对应的编号 

		if (i >= nTeacherNum)//说明没有找到对应用户名 
			MessageBox(NULL, _T("该用户不存在"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//找到了此用户名，退出输入用户名的循环，进入修改密码模块 
	} while (1);

	do {
		InputBox(password, 10, _T("请输入原始密码"));
		if (wcscmp(password, teacher[teachernum].password1) == 0)//密码符合
		{
			InputBox(resetpassword, 10, _T("密码正确，请输入6位数修改密码"));
			wcscpy_s(teacher[teachernum].password1, resetpassword);//将原密码改为修改后的密码
			MessageBox(NULL, _T("修改密码成功！"), _T("修改密码"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;//退出修改密码模块 
		}
		else
			MessageBox(NULL, _T("密码错误"), _T("修改密码"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//二级菜单：教师对学生日程管理
void Teacher_ScheduleManagement(FILE *fp)
{
	loadimage(&teacher_schedulemanagement1, L"teacher_schedulemanagement1.jpg");//进入教师端日程管理界面1
	putimage(0, 0, &teacher_schedulemanagement1);
	Sleep(100);
	loadimage(&teacher_schedulemanagement2, L"teacher_schedulemanagement2.jpg");//进入教师端日程管理界面2
	putimage(0, 0, &teacher_schedulemanagement2);
	/*下面是多个按钮的鼠标交互*/
	MOUSEMSG msg;//定义变量，保存鼠标消息
	FlushMouseMsgBuffer();// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	while (true) // 主循环,循环监听鼠标信息
	{
		while (MouseHit())	//监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();//获取鼠标消息
			if (WM_LBUTTONDOWN == msg.uMsg)//判断鼠标信息;鼠标左键按下
			{
				if (msg.x > 683 && msg.x < 759 && msg.y > 563 && msg.y < 621)//鼠标点击特定区域，即“STUDENT”按钮所在区域
					Select_MainMenu(fp);//调用一级主菜单选项函数
				if (msg.x > 408 && msg.x < 554 && msg.y > 474 && msg.y < 619)//鼠标点击特定区域，即“学生端”按钮所在区域
					OutputStu_SecondMenu(fp);//调用学生端函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 95 && msg.y < 158)//鼠标点击特定区域，即“新建学生日程”按钮所在区域
					SetStuSchedule(fp);//调用设定学生日程函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 218 && msg.y < 284)//鼠标点击特定区域，即“修改学生日程”按钮所在区域
					ResetStuSchedule(fp);//调用教师修改学生日程函数
				if (msg.x > 81 && msg.x < 365 && msg.y > 342 && msg.y < 410)//鼠标点击特定区域，即“查看完成状态”按钮所在区域
					CheckFinishedCondition();//调用教师查看学生完成状态函数
				if (msg.x > 21 && msg.x < 103 && msg.y > 613 && msg.y < 688)//鼠标点击返回按钮
				{

					loadimage(&teacher_schedulemanagement2_return, L"teacher_schedulemanagement2_return.jpg");
					putimage(0, 0, &teacher_schedulemanagement2_return);
					Sleep(100);
					OutputTeacher_SecondMenu(fp);//调用二级菜单教师端
				}
				if (msg.x > 1239 && msg.x < 1334 && msg.y > 20 && msg.y < 62)//鼠标点击exit按钮
				{
					/*退出登录（使得下次进入系统后重新登录）*/
					nStuFlag = 0;
					nTeacherFlag = 0;
					SaveFile(fp);//调用文件保存函数
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

//三级菜单：设定学生日程

void SetStuSchedule(FILE *fp)
{
	loadimage(&setstuschedule, L"setstuschedule.jpg");//进入设定学生日程界面
	putimage(0, 0, &setstuschedule);

	int position_x = 476;//“序号”横坐标
	int position_y = 92;//“序号”纵坐标
	setbkmode(TRANSPARENT);//设置字体背景为透明
	settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
	settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
	wchar_t FinishStatus2[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus2, L"未完成");//不能直接初始化，要先定义再赋值
	int sequence;//定义临时存储选定学生序号的变量
	wchar_t sequence1[100];//定义临时存储选定学生序号的变量转换后存储的字符数组
	wchar_t sequencenum[100];//定义存储学生序号的字符数组，将数字转换为字符
	wchar_t sch_sequencenum[100];//定义存储日程序号的字符数组，将数字转换为字符
	//显示所有学生的所有日程
	outtextxy(position_x, position_y, _T("序号    初始时间    截止时间    日程内容    状态"));//显示表格第一行表头
	for (int i = 0; i < nStudentNum; i++)
	{
		/*将数字转化为字符串的函数*/
		//由于outtextxy输出时无法直接输出int型量，因此需要将int型转化为字符串
		//此函数采取笨办法枚举（枚举1-10）
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
		position_y += 20;//向下推一行
		outtextxy(position_x, position_y, sequencenum);//显示对应学生序号（显示在“序号”正下方）
		outtextxy(position_x+20, position_y, stu[i].szName);//显示对应学生用户名
		//显示单个学生的日程
		for (int j = 1; j <= stu[i].nManagement; j++)//显示出该学生用户所有的日程
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
			position_y += 20;//向下推一行
			outtextxy(494, position_y, sch_sequencenum);//显示序号
			outtextxy(556, position_y, stu[i].Management1[j]);//初始时间
			outtextxy(676, position_y, stu[i].Management2[j]);//截至时间
			outtextxy(800, position_y, stu[i].Management3[j]);//日程内容
			outtextxy(916, position_y, stu[i].FinishStatus[j]);//完成状态
		}
	}
	//选择学生 
	int i;
	do {
		InputBox(sequence1, 10, _T("请选择需要设定的学生的序号"));
		//下面进行字符串与数字的转化
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
		if (i >= nStudentNum)//说明没有对应的学生序号
			MessageBox(NULL, _T("输入错误，请重新输入"), _T("设定学生日程"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//结束选择序号的do while循环 
	} while (1);
	//给该学生设定日程
	stu[sequence - 1].nManagement++;//让日程事件数加1
	InputBox(stu[sequence - 1].Management1[stu[sequence - 1].nManagement], 11, _T("请设定初始时间"));//初始时间 
	InputBox(stu[sequence - 1].Management2[stu[sequence - 1].nManagement], 11, _T("请选择需要设定的学生的序号"));//截止时间 
	InputBox(stu[sequence - 1].Management3[stu[sequence - 1].nManagement], 11, _T("请选择需要设定的学生的序号"));//日程内容
	wcscpy_s(stu[sequence - 1].FinishStatus[stu[sequence - 1].nManagement], FinishStatus2);//默认设置为"未完成" 
	MessageBox(NULL, _T("设定成功！"), _T("设定学生日程"), MB_SETFOREGROUND);
	SaveFile(fp);//调用文件保存函数
}

//三级菜单：修改学生日程
void ResetStuSchedule(FILE *fp)
{
	loadimage(&resetstuschedule, L"resetstuschedule.jpg");//进入教师端教师登录界面
	putimage(0, 0, &resetstuschedule);

	int position_x = 476;//“序号”横坐标
	int position_y = 92;//“序号”纵坐标
	setbkmode(TRANSPARENT);//设置字体背景为透明
	settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
	settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
	wchar_t FinishStatus1[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus1, L"完成");//不能直接初始化，要先定义再赋值
	wchar_t FinishStatus2[MANAGELENGTH];//定义一个"未完成"字符数组 
	wcscpy_s(FinishStatus2, L"未完成");//不能直接初始化，要先定义再赋值
	int schedulesequence;//定义临时存储选定学生日程的序号 
	wchar_t schedulesequence1[100];//定义临时存储选定学生日程序号转换存入的字符数组
	int sequence;//定义临时存储选定学生序号的变量
	wchar_t sequence1[100];//定义临时存储选定学生序号的变量转换后存储的字符数组
	wchar_t sequencenum[100];//定义存储学生序号的字符数组，将数字转换为字符
	wchar_t sch_sequencenum[100];//定义存储日程序号的字符数组，将数字转换为字符
	//显示所有学生的所有日程
	outtextxy(position_x, position_y, _T("序号    初始时间    截止时间    日程内容    状态"));//显示表格第一行表头
	for (int i = 0; i < nStudentNum; i++)
	{
		/*将数字转化为字符串的函数*/
		//由于outtextxy输出时无法直接输出int型量，因此需要将int型转化为字符串
		//此函数采取笨办法枚举（枚举1-10）
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
		position_y += 20;//向下推一行
		outtextxy(position_x, position_y, sequencenum);//显示对应学生序号（显示在“序号”正下方）
		outtextxy(position_x + 20, position_y, stu[i].szName);//显示对应学生用户名
		//显示单个学生的日程
		for (int j = 1; j <= stu[i].nManagement; j++)//显示出该学生用户所有的日程
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
			position_y += 20;//向下推一行
			outtextxy(494, position_y, sch_sequencenum);//显示序号
			outtextxy(556, position_y, stu[i].Management1[j]);//初始时间
			outtextxy(676, position_y, stu[i].Management2[j]);//截至时间
			outtextxy(800, position_y, stu[i].Management3[j]);//日程内容
			outtextxy(916, position_y, stu[i].FinishStatus[j]);//完成状态
		}
	}
	//选择学生 
	int i;
	do {
		InputBox(sequence1, 10, _T("请选择需要修改的学生的序号"));
		//下面进行字符串与数字的转化
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
		if (i >= nStudentNum)//说明没有对应的学生序号
			MessageBox(NULL, _T("输入错误，请重新输入"), _T("修改学生日程"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//结束选择序号的do while循环 
	} while (1);
	//选择事件
	int k;
	do {
		InputBox(schedulesequence1, 10, _T("请选择需要修改的日程序号"));
		//下面进行字符串与数字的转化
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
		if (k > stu[sequence - 1].nManagement)//说明输入的数字没有在所有日程序号的范围内 
			MessageBox(NULL, _T("请重新输入"), _T("修改学生日程"), MB_ICONSTOP | MB_SETFOREGROUND);
		else
			break;//退出选择日程序号的循环 
	} while (1);

	//修改日程  
	InputBox(stu[sequence - 1].Management1[schedulesequence], 11, _T("请重新规划初始时间"));//初始时间 
	InputBox(stu[sequence - 1].Management2[schedulesequence], 11, _T("请重新规划截止时间"));//截止时间 
	InputBox(stu[sequence - 1].Management3[schedulesequence], 11, _T("请重新规划日程内容"));//日程内容
	MessageBox(NULL, _T("修改成功！"), _T("修改学生日程"), MB_SETFOREGROUND);
	do {//修改状态 
		InputBox(stu[sequence - 1].FinishStatus[schedulesequence], 11, _T("请重新规划完成状态（完成/未完成）"));
		if (wcscmp(stu[sequence - 1].FinishStatus[schedulesequence], FinishStatus1) == 0)
		{
			MessageBox(NULL, _T("修改成功！"), _T("修改学生日程"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else if (wcscmp(stu[studentnum].FinishStatus[sequence - 1], FinishStatus2) == 0)
		{
			MessageBox(NULL, _T("修改成功！"), _T("修改学生日程"), MB_SETFOREGROUND);
			SaveFile(fp);//调用文件保存函数
			break;
		}
		else
			MessageBox(NULL, _T("输入错误"), _T("修改学生日程"), MB_ICONSTOP | MB_SETFOREGROUND);
	} while (1);
}

//三级菜单：查看学生完成状态
void CheckFinishedCondition()
{
	loadimage(&checkfinishedcondition, L"checkfinishedcondition.jpg");//进入教师端教师登录界面
	putimage(0, 0, &checkfinishedcondition);

	int position_x = 476;//“序号”横坐标
	int position_y = 92;//“序号”纵坐标
	setbkmode(TRANSPARENT);//设置字体背景为透明
	settextcolor(COLORREF(RGB(0, 0, 0)));//设置字体颜色为黑色
	settextstyle(20, 0, _T("楷体"));//设置字体大小20，格式楷体
	wchar_t sequencenum[100];//定义存储学生序号的字符数组，将数字转换为字符
	wchar_t sch_sequencenum[100];//定义存储日程序号的字符数组，将数字转换为字符
	//显示所有学生的所有日程
	outtextxy(position_x, position_y, _T("序号    初始时间    截止时间    日程内容    状态"));//显示表格第一行表头
	for (int i = 0; i < nStudentNum; i++)
	{
		/*将数字转化为字符串的函数*/
		//由于outtextxy输出时无法直接输出int型量，因此需要将int型转化为字符串
		//此函数采取笨办法枚举（枚举1-10）
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
		position_y += 20;//向下推一行
		outtextxy(position_x, position_y, sequencenum);//显示对应学生序号（显示在“序号”正下方）
		outtextxy(position_x + 20, position_y, stu[i].szName);//显示对应学生用户名
		//显示单个学生的日程
		for (int j = 1; j <= stu[i].nManagement; j++)//显示出该学生用户所有的日程
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
			position_y += 20;//向下推一行
			outtextxy(494, position_y, sch_sequencenum);//显示序号
			outtextxy(556, position_y, stu[i].Management1[j]);//初始时间
			outtextxy(676, position_y, stu[i].Management2[j]);//截至时间
			outtextxy(800, position_y, stu[i].Management3[j]);//日程内容
			outtextxy(916, position_y, stu[i].FinishStatus[j]);//完成状态
		}
	}
}

/*主函数*/
int main()
{
	FILE *fp;
	fopen_s(&fp,"alldate.dat", "rb");
	/*从文件中读入全局变量*/
	fread(&nStudentNum, 4, 1, fp);
	fread(&nTeacherNum, 4, 1, fp);
	fread(&nStuFlag, 4, 1, fp);
	fread(&nTeacherFlag, 4, 1, fp);
	fread(&studentnum, 4, 1, fp);
	fread(&teachernum, 4, 1, fp);
	//读入学生结构体数据
	for (int i = 0; i < nStudentNum; i++)
		fread(&stu[i], sizeof(struct student), 1, fp);
	//读入教师结构体数组 
	for (int i = 0; i < nTeacherNum; i++)
		fread(&teacher[i], sizeof(struct teacher), 1, fp);
	fclose(fp);
	/*读入结束*/

	initgraph(1366, 700);//定义窗口大小
	Welcome(fp);//调用Welcome
	
	return 0;
}
