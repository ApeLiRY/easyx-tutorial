#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{	
	HWND hwnd;
	wchar_t s[50];
	int i;

	i=666;
	
	hwnd=GetHWnd();	 // 获取当前窗口句柄
	
	_stprintf_s(s,_T("hello \n%d"), i);
	//_stprintf_s(s,_T("hello %.2f"),1.23f);
	//_stprintf_s(s,_T("hello %c"), 'a');
	//_stprintf_s(s,_T("hello %ws"), _T("abc"));
	// 将变量内容格式化写入到中间变量s中
	// 上述注释的语句展示了一些格式控制符的使用示例，自行将上述注释仅打开一条查看

	MessageBox(hwnd, s, _T("test"), MB_OK | MB_ICONHAND);
	// 参数依次为：
	// 消息框拥有的窗口、消息框的内容、消息框的标题、标志集(多个标志用"与"(|)符号连接)
	// 标志集参数可有多个，具体值参见10.1节

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}