#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	int i;

	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	setbkmode(TRANSPARENT);	
	// 1.设置文字背景模式为 TRANSPARENT 实现输出文字无背景色

	settextcolor(RGB(255,0,0)); 
	// 2.设置文字颜色为红色

	settextstyle(60, 0, _T("Wingdings"));
	// 3.设置文字大小和字体，参数依次为：高、宽、字体。若宽度为0表示自适应,
	// 字体_T(“*”)中*可自行替换，建议使用常见的字体，如：宋体、楷体、隶书等

	setlinecolor(RGB(255,0,0));
	setlinestyle(PS_SOLID,5);
	rectangle(10,40,180,80);
	// 绘制出显示文字的边框区域,为了显示区域位置设计的，此块代码可以删除

	i= 0x28;

	RECT A1 = {10,40,180,80}; 
	// 4.设置文字输出区域，四个参数依次为左上坐标(10,40)和右下坐标(180,80)，drawtext函数必须进行设置该参数
	
	drawtext(i, &A1, DT_WORDBREAK); 
	// 5.输出字体图标,在坐标(20,30)处输出电话机,0x28是电话机在Wingdings字体中的编码
	// DT_WORDBREAK自动换行。当文字超过右边界时自动换行(不拆开单词)。\n同样可以换行。
	// 关于参数DT_WORDBREAK的更多内容参见帮助文档中drawtext函数内容

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}