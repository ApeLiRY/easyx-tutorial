#include <graphics.h>				// 引用EasyX图形库
#include <conio.h>
#include <stdio.h>
#include <io.h>

int main()
{	
	IMAGE img[2];					
	// 1.定义 IMAGE 对象
	int i;
	wchar_t res[2][100]={_T("res\\062-demo.jpg"),_T("res\\063-demo2.jpg")}; 
	// 相对路径法表示文件名,可以修改为自定义的图片路径,

	// 2.检查资源是否存在，详细说明参见7.2和7.3节内容，相对路径法表示文件名
	for(i=0; i<2; i++)
	{
		if (_waccess(res[i], 0) < 0) // 文件名
		{
			printf("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名\n");
			_getch();
			return 0; // 资源不存在时，退出程序，不继续往下
		}
	}

	initgraph(812, 534);			// 创建一个宽812 x高534像素的窗口	

	for(i=0; i<2; i++)
	{
		loadimage(&img[i], res[i],0,0);
		// 3.读取图片到img对象中，图片可以是png格式，也可以是jpg格式
		// 第3、4个参数为设置图片长、宽;若想加载原图大小,可设为0，也可用loadimage(&img, _T("res\\062-demo.jpg"));
	}

	for(i=0; i<2; i++)
	{
		putimage(0, 0, &img[i]);
		// 4.显示 IMAGE 对象到需要的位置 在坐标 (0, 0) 位置显示 IMAGE 对象（图片）
		_getch();
	}

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}