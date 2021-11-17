#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	//方法1 加载系统预置的鼠标样式 十字
	//HCURSOR hcur = LoadCursor(NULL, IDC_CROSS);	

	//方法2 加载自定义图片 \\050-鼠标样式cur.cur 作为鼠标样式：
	HCURSOR hcur = (HCURSOR) LoadImage(NULL, _T("res\\050-鼠标样式cur.cur"), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);	// 相对路径法
	//				                                                                       鼠标：宽，高；设置为0,0,表示原图大小																		

	// 1.加载鼠标样式，并获取其句柄(HCURSOR)；上述两种方法任意任选一种即可。

	HWND hwnd = GetHWnd();	
	// 2.定义并获取窗口句柄；

	SetClassLong(hwnd, GCL_HCURSOR, (long)hcur);
	// 3. 设置窗口中的鼠标样式为1中加载的样式。
	//     红色参数依次为：2中的窗口句柄，1中的鼠标样式

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}