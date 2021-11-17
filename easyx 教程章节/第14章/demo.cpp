//////////////////////////////////////////////////////
// 程序名称：连连看
// 编译环境：Visual C++ 2010 EasyX_20190415(beta) 
// 作　　者：席锦
// 最后修改：2019-6-16
///////////////////////////////////////////////
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <time.h> 

#pragma comment (lib,"winmm.lib")		//  包含播放声音组件的头文件
#pragma comment( lib, "MSIMG32.LIB")	// 引用该库才能使用 AlphaBlend 函数

//------函数声明
int initializationConstant();			// 初始化全局变量的常量模块
int audioModule(int mode);				// 音频模块
void setTheTitleModule();				//设置标题模块
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
// 透明输出图片函数

const int N=4;  // 苹果数

typedef struct  // 苹果结构体
{ 
	int num;	// 苹果编号
	int a;		// 第一个数
	int b;		// 第二个数
	int sum;	// a (+-*/) b 的值
	wchar_t str[20];	// 显示字符
}APPLES;

typedef struct	// 卡车结构体
{ 
	int num;	// 卡车编号
	int sum;	// 卡车上的值
	int result;	// 连线成功与否；0失败，1成功
}CARS;

const int mp3Num=5;  // 音频个数,不能为0

//------全局变量,当做全局常量使用
typedef struct							// 程序中的一些常量标记
{	
	wchar_t	resMp3[mp3Num][100];		//  用于存储mp3路径名
	wchar_t Title[100];					// 程序标题
	wchar_t Imgapple[100],Imgcar[100];	// 存储苹果和卡车的图片
	wchar_t again[100],about[100];		// 重新开始、信息图片文件夹
}myFlagConstant;
myFlagConstant myAllFlagConstant;

//------全局变量,当做全局变量使用
typedef struct							// 程序中的一些变量标记
{
	HWND hwnd;							// 窗口句柄
	APPLES apple[N];					// 苹果结构体
	CARS car[N];						// 卡车结构体
}myFlagVariate;
myFlagVariate myAllFlagVariate;


int main()
{
	IMAGE Imgapple,Imgcar;				// 存储苹果和卡车的图片
	IMAGE again,about;					// 重新开始、信息
	MOUSEMSG mou;						//定义鼠标变量

	if (initializationConstant()<0)		//	给全局变量当常量的变量赋值
	{
		return 0;
	}

	// 一次只运行一个程序实例，如果已运行则退出,避免同时运行多个本程序，造成资源冲突；
	// 如:本程序会对外部文件进行写操作的话，若运行多个程序可能会写失败，也可能会导致数据污染
	if(FindWindow(NULL,myAllFlagConstant.Title))
	{
		MessageBox(NULL,_T("一个系统只能运行一个本程序，\n本系统已有一个本程序在运行，本次启动失败。\n重启程序前请先关闭已运行的本程序。\n"),_T("程序启动失败"),MB_OK|MB_ICONEXCLAMATION);
		return 0;						// 结束程序
	}

	initgraph(920,500);					// 创建窗口
	setbkcolor(0xffffff);				//设置背景色为白色	
	cleardevice();						//调用清屏cleardevice用背景色刷新背景

	setTheTitleModule();				//设置标题模块

	myAllFlagVariate.hwnd = GetHWnd();	// 获取窗口句柄

	if(audioModule(2*mp3Num)<0)			// 加载所有音频，并重命名
	{
		closegraph();
		return 0;
	}

	loadimage(&Imgapple,myAllFlagConstant.Imgapple);	//加载图片
	loadimage(&Imgcar,myAllFlagConstant.Imgcar);
	loadimage(&again,myAllFlagConstant.again);
	loadimage(&about,myAllFlagConstant.about);

	// 以上内容仅定义或加载一次
	// 以下内容每次重新运行皆需重新定义或加载

a:	int i,j;
	int flag=1;						// 随机布局时所采用的中间变量
	wchar_t temp[100];				// 显示转换用的中间变量
	int mouflag=-1;					// 鼠标点击的标记
	int overflag=0;					// 游戏结束的标记

	if(audioModule(0)<0)			//	循环播放背景音乐
	{
		closegraph();
		return 0;
	}

	putimage(50,50,&Imgapple);		 // 绘制苹果
	putimage(250,50,&Imgapple);
	putimage(450,50,&Imgapple);
	putimage(650,50,&Imgapple);

	putimage(50,350,&Imgcar);		// 绘制卡车
	putimage(250,350,&Imgcar);
	putimage(450,350,&Imgcar);
	putimage(650,350,&Imgcar);

	transparentimage(NULL, 680, 450, &again);	// 透明输出重新开始按钮图片
	transparentimage(NULL, 830, 420, &about);	// 透明输出关于按钮图片

	// 产生随机苹果值   开始
	srand((unsigned) time(NULL));				//用时间做种，每次产生随机数不一样
	// 设置苹果和车上的字体信息
	setbkmode(TRANSPARENT);						// 字体背景透明
	settextcolor(0xffffff);
	settextstyle(40,0,_T("楷体"));				// 设置字体大小(40)和类型_T("楷体"))
	for (i=0; i<N;)
	{
		myAllFlagVariate.apple[i].num=i;
		myAllFlagVariate.apple[i].a=rand()%11;	// 0-10之间的值
		switch(rand()%2)  // 0、1，表示+或-
		{
		case 0:
			_stprintf_s(temp, _T("%c"), '+');
			myAllFlagVariate.apple[i].b=rand()%11;		// 0-10之间的值
			myAllFlagVariate.apple[i].sum=myAllFlagVariate.apple[i].a+myAllFlagVariate.apple[i].b;
			break;
		case 1:
			_stprintf_s(temp, _T("%c"), '-');
			myAllFlagVariate.apple[i].b=rand()%11;		// 0-10之间的值
			myAllFlagVariate.apple[i].sum=myAllFlagVariate.apple[i].a-myAllFlagVariate.apple[i].b;
			break;	
		}
		_stprintf_s(myAllFlagVariate.apple[i].str, _T("%d%s%d"), myAllFlagVariate.apple[i].a,temp,myAllFlagVariate.apple[i].b);

		if (myAllFlagVariate.apple[i].sum<0)			// 新产生的式子值结果为负数需要重新生成
		{
			continue;
		}

		flag=0;
		for (j=0;j<i;j++)
		{
			if((myAllFlagVariate.apple[i].sum!=myAllFlagVariate.apple[j].sum))	// 新产生的式子值与之前产生的不相等
			{
				flag++;	
			}

		}
		if (flag==i)	// 新产生的式子合法(不与已存在的值冲突,且结果不为负数)
		{
			outtextxy(90+200*i,120,myAllFlagVariate.apple[i].str);
			i++;
		}

	}
	// 产生随机苹果值   结束

	// 将苹果值随机赋给卡车值   开始
	for (i=0;i<N;)
	{
		myAllFlagVariate.car[i].num=i;
		myAllFlagVariate.car[i].sum=myAllFlagVariate.apple[rand()%4].sum;	//	随机生成0-3，表示苹果的下标，将其结果赋值给car
		flag=1;
		for (j=0;j<i;j++)
		{
			if(myAllFlagVariate.car[i].sum==myAllFlagVariate.car[j].sum)	// 新产生的值与之前产生的相等,则标记式子相等，需要重新产生随机值
			{
				flag=0;
				break;
			}

		}
		if (flag)	// 新产生的值合法(不与已存在的值冲突)
		{
			myAllFlagVariate.car[i].result=0;  // 未连线
			_stprintf_s(temp, _T("%d"), myAllFlagVariate.car[i].sum);
			outtextxy(135+200*i,370,temp);
			i++;
		}
	}
	// 将苹果值随机赋给卡车值   结束

	// 设置鼠标选择情况的字体信息
	settextstyle(20,0,_T("楷体"));	// 设置字体大小(20)和类型_T("楷体"))
	settextcolor(0x0000ff);			// 设置字体颜色 
	_stprintf_s(temp,_T("当前状态: 未选中任何苹果"));
	outtextxy(300,10,temp);
	outtextxy(100,280,_T("1号                  2号                  3号                  4号")); 

	// 响应鼠标 开始
	while (1)   // 主要界面
	{
		if (MouseHit())   // 获取一个鼠标信息
		{
			mou = GetMouseMsg();  //获得一个鼠标消息
			if (WM_LBUTTONDOWN == mou.uMsg)//鼠标左键按下(1)
			{
				//  检测鼠标信息是否在设置里
				if (mou.x > 50 && mou.x<205 && mou.y>50 && mou.y < 216)	// 响应 点击苹果，从左到右依次为0123
				{
					if(audioModule(1)<0)	//	播放选中的声音
					{
						closegraph();
						return 0;
					}

					mouflag=0;
					settextcolor(0xffffff);			// 设置字体颜色白色  
					outtextxy(300,10,temp);			// 显示字符，清除上次的残留字迹
					settextcolor(0x0000ff);			// 设置字体颜色
					_stprintf_s(temp,_T("当前状态: 选中1号苹果"));// 刷新新的字迹
					outtextxy(300,10,temp);         // 显示新字符  		
				}
				else if (mou.x > 250 && mou.x<405 && mou.y>50 && mou.y < 216)
				{
					if(audioModule(1)<0)
					{
						closegraph();
						return 0;
					}

					mouflag=1;
					settextcolor(0xffffff);
					outtextxy(300,10,temp);
					settextcolor(0x0000ff);
					_stprintf_s(temp,_T("当前状态: 选中2号苹果"));
					outtextxy(300,10,temp);		
				}
				else if (mou.x > 450 && mou.x<605 && mou.y>50 && mou.y < 216)
				{
					if(audioModule(1)<0)
					{
						closegraph();
						return 0;
					}

					mouflag=2;
					settextcolor(0xffffff); 
					outtextxy(300,10,temp);
					settextcolor(0x0000ff);
					_stprintf_s(temp,_T("当前状态: 选中3号苹果"));
					outtextxy(300,10,temp);	
				}
				else if (mou.x > 650 && mou.x<805 && mou.y>50 && mou.y < 216)
				{
					if(audioModule(1)<0)	//	播放选中声音
					{
						closegraph();
						return 0;
					}
					mouflag=3;
					settextcolor(0xffffff); 
					outtextxy(300,10,temp);
					settextcolor(0x0000ff);
					_stprintf_s(temp,_T("当前状态: 选中4号苹果"));
					outtextxy(300,10,temp);	
				}
				else if (mou.x > 50 && mou.x<200 && mou.y>350 && mou.y < 442)	// 响应 点击卡车，从左到右依次为0123
				{
					if (mouflag>-1 && mouflag<4)  // 点击了苹果才能响应点击卡车
					{	
						if (myAllFlagVariate.apple[mouflag].sum==myAllFlagVariate.car[0].sum)
						{
							if(audioModule(3)<0)	//	播放连线成功
							{
								closegraph();
								return 0;
							}
							myAllFlagVariate.car[0].result=1;  // 连线
							// 绘制连线
							setcolor(0x0000ff);
							line(120+200*mouflag,150,125,370); 
							mciSendString(_T("play res\\xiaochu.mp3"), NULL, 0,NULL); // 播放声音		
						}
						else
						{
							if(audioModule(4)<0)	//	播放连线失败
							{
								closegraph();
								return 0;
							}
						}						mouflag=-1;
						settextcolor(0xffffff);             // 设置字体颜色(大写颜色英文)   
						outtextxy(300,10,temp);         // 显示字符
						settextcolor(0x0000ff);             // 设置字体颜色(大写颜色英文)   
						_stprintf_s(temp,_T("当前状态: 未选中任何苹果"));
						outtextxy(300,10,temp);         // 显示字符
					}
				}
				else if (mou.x > 250 && mou.x<400 && mou.y>350 && mou.y < 442)
				{
					if (mouflag>-1 && mouflag<4)  // 点击了苹果才能响应点击卡车
					{	
						if (myAllFlagVariate.apple[mouflag].sum==myAllFlagVariate.car[1].sum)
						{
							if(audioModule(3)<0)	//	播放连线成功
							{
								closegraph();
								return 0;
							}
							myAllFlagVariate.car[1].result=1;  // 连线
							// 绘制连线
							setcolor(0x0000ff);
							line(120+200*mouflag,150,125+200*1,370); 
						}
						else
						{
							if(audioModule(4)<0)	//	播放连线失败
							{
								closegraph();
								return 0;
							}
						}						mouflag=-1;
						settextcolor(0xffffff);             // 设置字体颜色(大写颜色英文)   
						outtextxy(300,10,temp);         // 显示字符
						settextcolor(0x0000ff);             // 设置字体颜色(大写颜色英文)   
						_stprintf_s(temp,_T("当前状态: 未选中任何苹果"));
						outtextxy(300,10,temp);         // 显示字符
					}
				}
				else if (mou.x >450 && mou.x<600 && mou.y>350 && mou.y < 442)
				{
					if (mouflag>-1 && mouflag<4)  // 点击了苹果才能响应点击卡车
					{	
						if (myAllFlagVariate.apple[mouflag].sum==myAllFlagVariate.car[2].sum)
						{
							if(audioModule(3)<0)	//	播放连线成功
							{
								closegraph();
								return 0;
							}
							myAllFlagVariate.car[2].result=1;  // 连线
							// 绘制连线
							setcolor(0x0000ff);
							line(120+200*mouflag,150,125+200*2,370); 
						}
						else
						{
							if(audioModule(4)<0)	//	播放连线失败
							{
								closegraph();
								return 0;
							}
						}						mouflag=-1;
						settextcolor(0xffffff);             // 设置字体颜色(大写颜色英文)   
						outtextxy(300,10,temp);         // 显示字符
						settextcolor(0x0000ff);             // 设置字体颜色(大写颜色英文)   
						_stprintf_s(temp,_T("当前状态: 未选中任何苹果"));
						outtextxy(300,10,temp);         // 显示字符
					}
				}
				else if (mou.x > 650 && mou.x<800 && mou.y>350 && mou.y < 442)
				{
					if (mouflag>-1 && mouflag<4)  // 点击了苹果才能响应点击卡车
					{	
						if (myAllFlagVariate.apple[mouflag].sum==myAllFlagVariate.car[3].sum)
						{
							if(audioModule(3)<0)	//	播放连线失败
							{
								closegraph();
								return 0;
							}
							myAllFlagVariate.car[3].result=1;  // 连线
							// 绘制连线
							setcolor(0x0000ff);
							line(120+200*mouflag,150,125+200*3,370); 
						}
						else
						{
							if(audioModule(4)<0)	//	播放连线失败
							{
								closegraph();
								return 0;
							}
						}
						mouflag=-1;
						settextcolor(0xffffff);             // 设置字体颜色(大写颜色英文)   
						outtextxy(300,10,temp);         // 显示字符
						settextcolor(0x0000ff);             // 设置字体颜色(大写颜色英文)   
						_stprintf_s(temp,_T("当前状态: 未选中任何苹果"));
						outtextxy(300,10,temp);         // 显示字符	
					}
				}
				else if (mou.x > 680 && mou.x<680+132 && mou.y>450 && mou.y < 450+52)	// 响应重新开始按钮
				{
					if(audioModule(mp3Num+0)<0)	//	关闭背景音响
					{
						closegraph();
						return 0;
					}
					cleardevice(); //调用清屏cleardevice用背景色刷新背景
					goto a; // 重新开始
				}
				else if (mou.x > 830 && mou.x<830+78 && mou.y>420 && mou.y < 420+78)	// 响应关于按钮
				{
					MessageBox(myAllFlagVariate.hwnd,_T("前言：\n调皮的苹果偷偷地从卡车上溜出来了，聪明的你，能将苹果送回到属于它的卡车上么？\n目标：\n用线将苹果与对应的卡车连接起来。\n操作说明：\n1.先用鼠标点击苹果，点击的苹果数字将变色；\n2.再点击卡车，若配对成功则会显示出连线，否则苹果撤销选中；\n3.直到出现四条线，则游戏结束，选择是否重新开始。\n版本信息：连连看 V1.1\n作    者：席锦\n联系邮件：no1xijin@126.com\n制作日期：2019年6月16日"),_T("关于"),MB_OK|MB_ICONASTERISK);
				}
			}
		}
		// 检查是否结束
		flag=1;  // 游戏结束
		for (i=0;i<4;i++)
		{
			if (myAllFlagVariate.car[i].result!=1)  // 游戏未结束
			{
				flag=0; 	
				break;  // 继续
			}
		}
		if (flag)
		{
			if(audioModule(mp3Num+0)<0)	//	关闭背景音响
			{
				closegraph();
				return 0;
			}
			if(audioModule(2)<0)		//	播放通过音响
			{
				closegraph();
				return 0;
			}
			settextcolor(0xffffff);		// 设置字体颜色(大写颜色英文)   
			outtextxy(300,10,temp);		// 显示字符
			settextcolor(0x0000ff);		// 设置字体颜色(大写颜色英文)   
			_stprintf_s(temp,_T("当前状态: 游戏结束!!"));
			outtextxy(300,10,temp);		// 显示字符
			if(MessageBox(myAllFlagVariate.hwnd,_T("游戏结束,是否继续？\n"),_T("游戏结束"),MB_YESNO|MB_DEFBUTTON1|MB_ICONQUESTION)==IDYES) //最后的数字表示第几个按钮为默认
			{
				cleardevice();			//调用清屏cleardevice用背景色刷新背景
				goto a;					// 重新开始
			}
			else
				break;					// 退出
		}
		Sleep(10);						// 延时10ms

	}

	closegraph();
	return 0;
}

int initializationConstant()	// 初始化全局变量的常量模块
{
	// 设置音频路径，相对路径表示法
	_stprintf_s(myAllFlagConstant.resMp3[0],_T("res\\bk.mp3"));
	_stprintf_s(myAllFlagConstant.resMp3[1],_T("res\\doorbell.mp3"));
	_stprintf_s(myAllFlagConstant.resMp3[2],_T("res\\pass.mp3"));
	_stprintf_s(myAllFlagConstant.resMp3[3],_T("res\\takeAway.mp3"));
	_stprintf_s(myAllFlagConstant.resMp3[4],_T("res\\cancel.mp3"));
	// 以上全局变量当常量用于int audioModule(int mode);// 音频模块

	// 程序标题内容
	_stprintf_s(myAllFlagConstant.Title,_T("连连看 V1.1"));
	// 以上全局变量当常量用于void setTheTitleModule();//设置标题模块

	// 加载图片
	_stprintf_s(myAllFlagConstant.Imgapple,_T("res\\apple.jpg"));	
	// 检查图片资源是否存在
	if (_waccess(myAllFlagConstant.Imgapple, 0) < 0)
	{	
		MessageBox(myAllFlagVariate.hwnd, _T("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名"), _T("图片文件缺失"), MB_OK | MB_ICONHAND);			
		return -1;							// 资源不存在时，退出程序，不继续往下
	}
	_stprintf_s(myAllFlagConstant.Imgcar,_T("res\\car.jpg"));
	if (_waccess(myAllFlagConstant.Imgcar, 0) < 0)
	{	
		MessageBox(myAllFlagVariate.hwnd, _T("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名"), _T("图片文件缺失"), MB_OK | MB_ICONHAND);			
		return -1;
	}

	_stprintf_s(myAllFlagConstant.again,_T("res\\again.png"));
	if (_waccess(myAllFlagConstant.again, 0) < 0)
	{	
		MessageBox(myAllFlagVariate.hwnd, _T("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名"), _T("图片文件缺失"), MB_OK | MB_ICONHAND);			
		return -1;
	}
	_stprintf_s(myAllFlagConstant.about,_T("res\\about.png"));
	if (_waccess(myAllFlagConstant.about, 0) < 0)
	{	
		MessageBox(myAllFlagVariate.hwnd, _T("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名"), _T("图片文件缺失"), MB_OK | MB_ICONHAND);			
		return -1;
	}

	return 0;
}

/*
*函数名：	int audioModule(int mode)
*函数功能：	根据输入参数实现音效操作
*参数：		范围0--2*mp3Num+1
*返回值：	0正常，-1异常
*参数对应的操作：
*				0，播放 bk.mp3
*				1，播放 doorbell.mp3
*				2，播放 pass.mp3
*				3，播放 takeAway.mp3
*				4，播放 cancel.mp3
*		mp3Num+0，停止 bk.mp3
*		mp3Num+1，停止 doorbell.mp3
*		mp3Num+2，停止 pass.mp3
*		mp3Num+3，停止 takeAway.mp3
*		mp3Num+4，停止 cancel.mp3
*	2*mp3Num+0，打开所有需要加载的音效
*	2*mp3Num+1，停止并释放所有音频
*/
int audioModule(int mode)
{
	MCIERROR	mciError;							// 存储播放音乐过程中的异常情况代码
	wchar_t		temp[100];
	int			i;

	if((2*mp3Num)==mode)
	{
		for(i=0; i<mp3Num; i++)
		{
			// 检查音频资源是否存在
			if (_waccess(myAllFlagConstant.resMp3[i], 0) < 0)
			{	
				MessageBox(myAllFlagVariate.hwnd, _T("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名"), _T("音频文件缺失"), MB_OK | MB_ICONHAND);			
				return -1;							// 资源不存在时，退出程序，不继续往下
			}
			_stprintf_s(temp,_T("open \"%s\" alias mymusic%d"),myAllFlagConstant.resMp3[i], i);
			mciError=mciSendString(temp, NULL, 0, NULL);
			if(mciError)							// 上述命令执行成功返回0，否则返回非0的故障码
			{
				_stprintf_s(temp,_T("%s - MCI 错误代码为：%d"), myAllFlagConstant.resMp3[i], mciError);	// 4.2节内容	
				MessageBox(myAllFlagVariate.hwnd, temp, _T("音频打开失败"), MB_OK | MB_ICONHAND);			
				return -1;
			}
		}
	}
	else if((2*mp3Num+1)==mode)
	{
		for(i=0; i<mp3Num; i++)
		{
			_stprintf_s(temp,_T("stop mymusic%d"), i);
			mciError=mciSendString(temp, NULL, 0, NULL); 	
			if(mciError)
			{
				_stprintf_s(temp,_T("%s - MCI 错误代码为：%d"), myAllFlagConstant.resMp3[i], mciError);
				MessageBox(myAllFlagVariate.hwnd, temp, _T("音频停止失败"), MB_OK | MB_ICONHAND);			
				return -1;
			}
			_stprintf_s(temp,_T("close mymusic%d"), i);
			mciError=mciSendString(temp, NULL, 0, NULL); 	
			if(mciError)
			{
				_stprintf_s(temp,_T("%s - MCI 错误代码为：%d"), myAllFlagConstant.resMp3[i], mciError);
				MessageBox(myAllFlagVariate.hwnd, temp, _T("音频关闭失败"), MB_OK | MB_ICONHAND);		
				return -1;
			}
		}
	}
	else if(0==mode)
	{
		_stprintf_s(temp,_T("play mymusic%d repeat"), mode);
		mciError=mciSendString(temp, NULL, 0, NULL);
		if(mciError)
		{
			_stprintf_s(temp,_T("%s - MCI 错误代码为：%d"), myAllFlagConstant.resMp3[mode], mciError);
			MessageBox(myAllFlagVariate.hwnd, temp, _T("音频播放失败"), MB_OK | MB_ICONHAND);		
		}
	}
	else if((mode>0) && (mode<mp3Num))
	{
		_stprintf_s(temp,_T("play mymusic%d from 0"), mode);
		mciError=mciSendString(temp, NULL, 0, NULL);
		if(mciError)
		{
			_stprintf_s(temp,_T("%s - MCI 错误代码为：%d"), myAllFlagConstant.resMp3[mode], mciError);
			MessageBox(myAllFlagVariate.hwnd, temp, _T("音频播放失败"), MB_OK | MB_ICONHAND);		
		}
	}
	else if((mode>=mp3Num) && (mode<2*mp3Num))
	{
		_stprintf_s(temp,_T("stop mymusic%d"), mode-mp3Num);
		mciError=mciSendString(temp, NULL, 0, NULL);
		if(mciError)
		{
			_stprintf_s(temp,_T("%s - MCI 错误代码为：%d"), myAllFlagConstant.resMp3[mode-mp3Num], mciError);	// 4.2节内容
			MessageBox(myAllFlagVariate.hwnd, temp, _T("音频播放失败"), MB_OK | MB_ICONHAND);		
		}
	}
	else
	{
		_stprintf_s(temp,_T("音频操作参数仅支持0-%d"), 2*mp3Num+1);
		MessageBox(myAllFlagVariate.hwnd,  temp, _T("音频操作失败"), MB_OK | MB_ICONHAND);
		return -1;
	}

	// 播放失败时，故障码和对应说明表存于附件中-MultimediaMCI错误返回码详解
	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	return 0;
}

/*
*函数名：	void setTheTitleModule();//设置标题模块
*函数功能：	将全局变量当常量中的标题常量设置为程序标题
*参数：		无
*返回值：	无
*/
void setTheTitleModule()
{

	myAllFlagVariate.hwnd = GetHWnd();
	// 获取窗口句柄

	SetWindowText(myAllFlagVariate.hwnd, myAllFlagConstant.Title);
	// 设置窗口标题

}

/* 半透明贴图函数
* 参数：
*            dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
*            x, y:  目标贴图位置
*            srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体*/
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}