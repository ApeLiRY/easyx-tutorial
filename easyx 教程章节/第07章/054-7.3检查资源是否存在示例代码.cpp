#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>
#include <io.h>

int main()
{	
	if (_waccess(_T("res"), 0) < 0) // 文件夹名
		printf("文件夹不存在\n");
	else
		printf("文件夹存在\n");
	if (_waccess(_T("res\\055-7.3周杰伦 - 听妈妈的话.wav"), 0) < 0)//文件名
		printf("文件不存在\n");
	else
		printf("文件存在\n");

	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}