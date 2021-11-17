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

	setfillstyle(BS_HATCHED,HS_FDIAGONAL);
	// 4.设置当前填充样式为 斜线。

	setfillcolor(RGB(0,255,0));
	// 5.设置当前填充颜色为 绿色

	fillpolygon(pts, 3);
	// 6.绘制有外框的填充多边形(以三边形为例),参数为各顶点坐标，顶点数

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}