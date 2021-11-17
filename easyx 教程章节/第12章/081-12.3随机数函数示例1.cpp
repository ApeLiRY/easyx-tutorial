#include <stdio.h>
#include <stdlib.h>					// 包含rand()函数

int main()
{
	int r;
	for(int i=0; i<10; i++)
	{
		r = rand();
		printf("%d\n", r);
	}

	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}