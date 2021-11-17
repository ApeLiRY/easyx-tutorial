#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(812, 453);			// 创建一个宽812 x高453像素的窗口	

	// 展示嵌入 jpg 图片
	loadimage(NULL, _T("JPG"), _T("MYJPG"));

	// 展示嵌入 png 图片，会透明显示
	loadimage(NULL, _T("PNG"), _T("MYPNG"));

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}