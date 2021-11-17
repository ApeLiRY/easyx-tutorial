#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

#pragma comment( lib, "MSIMG32.LIB")	
// 引用该库才能使用 AlphaBlend 函数，实现png透明显示
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
// 实现png透明显示

int main()
{
	IMAGE img1, img2;
	// 定义 IMAGE 对象
		
	initgraph(812, 453);						// 创建一个宽812 x高453像素的窗口	

	// 展示嵌入 jpg 图片    1
	loadimage(&img1, _T("JPG"), _T("MYJPG"));
	putimage(0, 0, &img1);

	// 展示嵌入 png 图片
	loadimage(&img2, _T("PNG"), _T("MYPNG"),200,200);
	putimage(450, 20, &img2);					// 不透明显示  2

	transparentimage(NULL, 450, 250, &img2);	// 透明显示  3
	// 在坐标 (450, 50) 位置显示 IMAGE 对象（图片）

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}

/* 半透明贴图函数
* 参数：
*            dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
*            x, y:  目标贴图位置
*            srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体*/
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
