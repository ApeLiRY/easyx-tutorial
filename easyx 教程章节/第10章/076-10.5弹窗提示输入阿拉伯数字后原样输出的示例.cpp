#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{	
	// 定义字符串缓冲区，并接收用户输入
	wchar_t s[10];

	InputBox(s, 10, _T("请输入数字"));
	// 参数依次为：
	// 接收用户输入字符串的指针、限制用户输入内容的长度、
	// 显示在窗体中的提示信息。其余参数为默认值。
	// 完整参数参见节内容。

	MessageBox(NULL, s, _T("test"), MB_OK | MB_ICONHAND);
	// 输出接收到的字符串

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}