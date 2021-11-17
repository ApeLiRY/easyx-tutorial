#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640,480);			// 创建一个宽640 x高480像素的窗口	
	
	wchar_t s[50];
	int i=666;

	HWND hwnd;
	// 1.设置窗口句柄变量保存窗口信息

	hwnd = GetHWnd();
	// 2.获取窗口句柄

	_stprintf_s(s,_T("hello %d"),i);
	//_stprintf_s(s,_T("hello %.2f"),1.23f);
	//_stprintf_s(s,_T("hello %c"), 'a');
	//_stprintf_s(s,_T("hello %ws"), _T("abc"));
	// 将变量内容格式化写入到中间变量s中
	// 上述注释的语句展示了一些格式控制符的使用示例，自行将上述注释仅打开一条查看

	SetWindowText(hwnd, s);
	// 3.设置窗口标题为 Hello 666

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}