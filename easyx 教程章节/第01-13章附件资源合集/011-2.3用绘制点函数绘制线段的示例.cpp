#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	int i;
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口

	for (i=10;i<100;i++)	// 绘制—
	{
		putpixel(i,10-2,RGB(255,0,0));
		putpixel(i,10-1,RGB(255,0,0));
		putpixel(i,10,RGB(255,0,0));
		putpixel(i,10+1,RGB(255,0,0));
		putpixel(i,10+2,RGB(255,0,0));
	}

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}