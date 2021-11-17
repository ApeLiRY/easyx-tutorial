#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{	
	// 定义字符串缓冲区，并接收用户输入
	wchar_t s[10];
	int i;

	i = InputBox(s, 10, _T("请输入数字"), _T("test"), NULL, 0, 0, false);
	// 参数依次为：
	// 接收用户输入字符串的指针、限制用户输入内容的长度、
	// 显示在窗体中的提示信息、标题栏内容、输入区的默认值、
	// InputBox 的宽度、InputBox 的高度、是否允许用户取消输入
	// 完整参数解释参见10.4节内容。
	// 返回值：如果用户按“确定”，返回 true；如果用户按“取消”，返回 false。
	
	if(true==i)
		MessageBox(NULL, s, _T("test"), MB_OK | MB_ICONHAND);
	else
		MessageBox(NULL, _T("点击了取消按键"), _T("test"), MB_OK | MB_ICONHAND);
	// 输出接收到的字符串

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}