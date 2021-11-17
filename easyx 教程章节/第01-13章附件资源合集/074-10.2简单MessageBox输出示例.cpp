#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{	

	MessageBox(NULL, _T("Hello World！"), _T("test"), MB_OK);
	// 参数依次为：
	// 消息框拥有的窗口、消息框的内容、消息框的标题、标志集(多个标志用"与"(|)符号连接)
	// 标志集参数可有多个，具体值参见10.1节

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}