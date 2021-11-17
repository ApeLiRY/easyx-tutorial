#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	setfillstyle(BS_HATCHED,HS_FDIAGONAL);
	// 1.设置当前填充样式为 斜线。

	setfillcolor(RGB(0,255,0));
	// 2.设置当前填充颜色为 绿色

	solidcircle(100,120,50);
	// 3.绘制无外框的填充圆, 圆心坐标（100,120），半径50

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}