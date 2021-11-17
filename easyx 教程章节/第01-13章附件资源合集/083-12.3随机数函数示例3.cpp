#include <stdio.h>
#include <stdlib.h>					// 包含rand()函数
#include <time.h>

int main()
{
	int r;
	srand( (unsigned)time( NULL ) );
	for(int i=0; i<10; i++)
	{
		r = rand()%(9-0+1)+0;
		printf("%d\n", r);
	}

	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}