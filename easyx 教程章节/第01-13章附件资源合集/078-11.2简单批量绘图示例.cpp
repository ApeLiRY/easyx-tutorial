#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640,480);			// 创建一个宽640 x高480像素的窗口	

	setlinecolor(WHITE);
	setfillcolor(RED);

	// BeginBatchDraw();
	// 1.开启批量绘图模式

	for(int i=50; i<600; i++)
	{
		circle(i, 100, 40);
		floodfill(i, 100, WHITE);
		// 2.绘制 

		// FlushBatchDraw();	
		// 3.显示绘制

		Sleep(10);
		cleardevice();	//	擦除已经绘制的内容
	}

	// EndBatchDraw();
	// 4.关闭批量绘图模式

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}