#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	
	
	HMODULE hmod = GetModuleHandle(NULL);			 // 获取当前进程的句柄	
	HCURSOR hcur = LoadCursor(hmod, _T("MYCURSOR")); // 加载资源中的鼠标样式图片
	// 6.加载鼠标样式图片

	HWND hwnd = GetHWnd();	
	// 7.定义并获取窗口句柄；

	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
	// 8. 设置窗口中的鼠标样式
	//     红色参数依次为：7中的窗口句柄，6中的鼠标样式

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}