#include <graphics.h>					// 引用EasyX图形库
#include <stdio.h>

int main()
{
	char str[] = "EasyX图形库";			// char
	wchar_t wstr[] = _T("EasyX图形库");	// wchar_t

	printf("strlen(str)=%d, wcslen(wstr)=%d\n", strlen(str), wcslen(wstr));
	// 同样文字，存于不同类型中占用位置大小不一样，但函数使用方式差不多

	getchar();							// 暂停程序运行，查看输出结果
	return 0;
}