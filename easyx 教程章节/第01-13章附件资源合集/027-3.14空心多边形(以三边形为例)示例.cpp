#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	POINT pts[]={{50,200},{200,200},{200,50}};
	// 1.设置各点坐标分别为：{50,200},{200,200},{200,50}

	setlinecolor(RGB(255,0,0));
	// 2.设置当前画线颜色为 红色

	setlinestyle(PS_SOLID, 5);
	// 3.设置当前画线样式为 实线，宽度为5

	polygon(pts, 3);
	// 4.绘制空心多边形(以三边形为例) 参数为各顶点坐标，顶点数

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}