#include <graphics.h>					// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);				
	// 1.创建一个宽640 x高480像素的窗口

	//initgraph(640, 480, SHOWCONSOLE);	
	// 2.创建一个宽640 x高480像素的窗口,同时显示控制台窗口

	//initgraph(640, 480, SHOWCONSOLE | NOCLOSE);	
	// 3.创建一个宽640 x高480像素的窗口,同时显示控制台窗口,并禁用关闭按钮：

	outtextxy(0,10,_T("Hello World!"));	// 在坐标(0,10)处输出Hello World!

	getchar();							// 暂停程序运行，查看输出结果
	closegraph();						// 关闭图形界面
	return 0;
}