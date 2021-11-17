#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	wchar_t temp[100];				// unicode编码存储字符用的
	int i=666;						// 需要输出的整型变量

	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	setbkmode(OPAQUE);	
	// 1.设置文字背景模式为 OPAQUE 实现输出文字背景用当前背景色填充（默认）

	setbkcolor(RGB(0,255,0)); 
	// 2.设置文字背景颜色为 绿色

	settextcolor(RGB(255,0,0)); 
	// 3.设置文字颜色为 红色

	settextstyle(25, 0, _T("楷体"));
	// 4.设置文字大小和字体，参数依次为：高、宽、字体。若宽为0则表示自适应,
	// 字体_T(“*”)中*可自行替换，建议使用常见的字体，如：宋体、楷体、隶书等

	_stprintf_s(temp,_T("hello %d"),i);
	//_stprintf_s(temp,_T("hello %.2f"),1.23f);
	//_stprintf_s(temp,_T("hello %c"), 'a');
	//_stprintf_s(temp,_T("hello %ws"), _T("abc"));
	// 将变量内容格式化写入到中间变量temp中
	// 上述注释的语句展示了一些格式控制符的使用示例，自行将上述注释仅打开一条查看

	outtextxy(20, 30, temp);
	// 5.输出带背景的文字,在指定的坐标(20,30)处输出Hello 666展示输出字符变量内容

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}