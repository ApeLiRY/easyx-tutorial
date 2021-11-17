#include <stdio.h>

#include <windows.h>  // 包含 DWORD start1,end1;
/*
GetTickCount() 
WIN32API 
头文件：windows.h 
函数原型：DWORD WINAPI GetTickCount(void); 
功能：返回自设备启动后的毫秒数（不含系统暂停时间）。 
总结：精确到毫秒。对于一般的实时控制，使用GetTickCount()函数就可以满足精度要求。
*/

#include <time.h>  // 包含 clock_t start2,end2; time_t start3,stop3
/*
2. clock() 
头文件：time.h 
函数原型：clock_t clock(void); 
功能：该函数返回值是硬件滴答数(毫秒)，要换算成秒，需要除以CLK_TCK或者 CLK_TCKCLOCKS_PER_SEC。 比如，在VC++下，这两个量的值都是1000。 
总结：可以精确到毫秒，适合一般场合的使用。 
*/

/*
time()
头文件：time.h 
函数原型：time_t time(time_t *seconds) 
功能：获取当前的系统时间，返回的结果是一个time_t类型，其实就是一个大整数，
其值表示从CUT(Coordinated Universal Time)时间1970年1月1日00:00:00(称为UNIX系统的Epoch时间)到当前时刻的秒数.   
*/
int main()
{
	int i,j;
	DWORD start1,end1; 
	clock_t start2,end2;
	time_t start3,stop3;

	printf("计时开始\n");
	start1= GetTickCount();
	start2= clock(); 
	start3 = time(NULL);

	i=2000;
	while(i--)  // 增加时间消耗，以便于观察
	{
		j=1000000;
		while(j--)
			;
	}

	end1= GetTickCount(); 
	end2= clock();
	stop3 = time(NULL);
	printf("计时结束\n");
	printf("总时间1：%d ms\n",end1-start1);
	printf("总时间2：%f s\n",((double)end2-start2)/CLK_TCK);
	printf("总时间3：%ld s\n",(stop3-start3));

	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}