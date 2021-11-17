#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640,480);			// 创建一个宽640 x高480像素的窗口	

	HWND hwnd;
	// 1.设置窗口句柄变量保存窗口信息

	hwnd = GetHWnd();
	// 2.获取窗口句柄

	SetWindowText(hwnd, _T("Hello World!"));
	// 3.设置窗口标题为 Hello World!

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}