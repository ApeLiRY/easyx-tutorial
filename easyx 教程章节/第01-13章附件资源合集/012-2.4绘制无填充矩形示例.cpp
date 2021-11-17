#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口

	setlinecolor(RGB(255,0,0));
	// 1.设置当前画线颜色为 红色

	setlinestyle(PS_DASH,5);
	// 2.设置当前画线样式为 ----,宽度为5

	rectangle(10,20,100,120);
	// 3.绘制矩形边框 左上角坐标(10,20)，右下角坐标(100,120)

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}