#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	setlinecolor(RGB(255,0,0));
	// 1.设置当前画线颜色为 红色

	setlinestyle(PS_SOLID, 5);
	// 2.设置当前画线样式为 实线，宽度为5

	ellipse(10,20,200,120);
	// 3.绘制空心椭圆,椭圆外切矩形左上（10,20）,椭圆外切矩形右下（100,120）

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}