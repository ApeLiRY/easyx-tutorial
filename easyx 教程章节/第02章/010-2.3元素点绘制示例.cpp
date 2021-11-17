#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口

	putpixel(10,20,RGB(0,255,0));
	// 绘制点，在坐标(10,20)处输出颜色为绿色的点

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}