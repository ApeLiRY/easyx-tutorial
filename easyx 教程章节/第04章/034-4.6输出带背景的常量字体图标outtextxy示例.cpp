#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	setbkmode(OPAQUE);	
	// 1.设置文字背景模式为 OPAQUE 实现输出文字背景用当前背景色填充（默认）

	setbkcolor(RGB(0,255,0)); 
	// 2.设置文字背景颜色为 绿色

	settextcolor(RGB(255,0,0)); 
	// 3.设置文字颜色为 红色

	settextstyle(50, 0, _T("Wingdings"));
	// 4.设置文字大小和字体，参数依次为：高、宽、字体。若宽度为0表示自适应,
	// 字体_T(“*”)中*可自行替换，建议使用常见的字体，如：宋体、楷体、隶书等

	outtextxy(20, 30, 0x28);
	//5.输出字体图标,在坐标(20,30)处输出电话机,0x28是电话机在Wingdings字体中的编码

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}