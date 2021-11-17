#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>
#include <conio.h>					// 包含按键检测、接收等函数

int main()
{
	char c;
	// 1.定义变量，保存键盘消息

	char a = 0xE0, b=0;
	// 定义变量用于与getch()返回值进行比较，以确认是否按下了功能键；由于_getch()返回值是char型，故此处变量也是char型，这也是为什么要用变量而不是直接用0xE0了。直接用0xE0，其类型不是char，一般是int，而char型的0xE0不等于int型的0xE0。

	printf("程序运行开始\n");

	Sleep(5000);			
	// 延时5s,在此期间多按键盘

	//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); 
	// 调用控制台 API，清空之前缓冲区内的所有按键信息
	// 不使用这个的函数时候可以不调用EasyX库
	// 运行两次，一次注释掉本函数，一次不注释，查看输出，体会本函数的作用

	while(true)
	// 主循环,循环监听键盘信息
	{
		while (_kbhit())
		// 2.监听键盘信息;当有键盘按下的时候执行,可检测连续的键盘信息
		{
			c = _getch();

			if (c == a || c == b)	// 获取功能性按键，如：上下左右箭头
			//与普通按键不同,当按下功能按键时当getch()会返回0或0xE0,这时候需要再调用一次_getch(),第二次_getch()返回值表示功能键,如:72表示上;80表示下;75表示左;77表示右
			{	
				printf("功能按键\n"); // 突出显示是否进入到本区域
				c = _getch();	
			}

			// 3.获取键盘信息
			if(c!='1')
				// 4.判断键盘信息,按键不是1则输出按键字符
				printf("%c", c);
			// 5.响应键盘点击的对应的操作，输出按键字符。
		}
		
		Sleep(200);		// 延时是故意放大的，为了展示连续按下键盘时的情况
		printf("未检测到键盘信息\n");
		// 快速按下多个按键和正常按下多个键查看结果，体会while (_kbhit())循环的作用
	}

	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}