#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{	
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	IMAGE img;
	// 1.定义 IMAGE 对象

	setcolor(RGB(255,0,0));
	line(10, 50, 100, 50);
	line(50, 10, 50, 100);
	// 绘制十字

	getimage(&img, 0, 0, 100, 100);
	// 2.保存区域至 img 对象

	putimage(0, 120, &img);
	// 3.将 img 对象显示在屏幕的某个位置

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}