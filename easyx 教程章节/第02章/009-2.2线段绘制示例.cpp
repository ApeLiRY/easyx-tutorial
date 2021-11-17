#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口

	// 以下三个函数参数不同但作用效果相同,此处如此写是为了展示2.1节中的内容
	// 实际使用过程中，以下三种方式任意选择一种即可
	setlinecolor(RGB(255,0,0));		// 方式1
	//setlinecolor(0x0000FF);		// 方式2
	//setlinecolor(BGR(0xFF0000));	// 方式3
	// 1.设置当前画线颜色为 红色

	setlinestyle(PS_DASH,5);
	// 2.设置当前画线样式为 ----,宽度为5

	line(10,20,100,20);
	// 3.绘制线段 起点坐标(10,20)，终点坐标(100,20)

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}