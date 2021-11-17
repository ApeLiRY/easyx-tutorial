#include <stdio.h>

int main()
{
	int i;
	_asm int 3
	i=2;
	// 当i等于1时，正确输出为:Hello World!-1;错误输出还是:Hello World!-1;
	// 				此时给人的错觉就是程序运行正常
	// 当i不等于1时，正确输出为:Hello World!-2;错误输出是:Hello World!-1;

	if (i=1)							// 正确形式为：(i==1)
		printf("Hello World!-1\n");		// 输出Hello World!-1
	else
		printf("Hello World!-2\n");		// 输出Hello World!-2

	getchar();							// 暂停程序运行，查看输出结果
	return 0;
}