#include <graphics.h>				// 引用EasyX图形库
#include <conio.h>
#include <stdio.h>
#include <io.h>

#pragma comment( lib, "MSIMG32.LIB")	// 引用该库才能使用 AlphaBlend 函数
int recognitionPicture(char path[], char nameSuffix[]);	//识别图片格式函数
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
// 透明输出图片函数

int main()
{	
	IMAGE img, img2;// img2为展示如何正确输出png背景透明
	//1.定义 IMAGE 对象

	// 2.检查资源是否存在，详细说明参见7.2和7.3节内容，相对路径法表示文件名
	if (_waccess(_T("res\\062-demo.jpg"), 0) < 0)
	{
		printf("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名\n");
		_getch();
		return 0; // 资源不存在时，退出程序，不继续往下
	}
	if (_waccess(_T("res\\065-demo2.png"), 0) < 0)	
	{
		printf("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名\n");
		_getch();
		return 0; // 资源不存在时，退出程序，不继续往下
	}

	initgraph(812, 453);			// 创建一个宽812 x高453像素的窗口	

	// 识别图片格式，封装成一个函数，相对路径法表示文件名,本函数暂时不支持_T("*")
	// 本块在实际运用时，可删除
	if(recognitionPicture("res\\062-demo.jpg", "JPG")<0) 
	{
		_getch();closegraph();
		return 0; // 图片格式不标准时，退出程序，不继续往下
	}
	if(recognitionPicture("res\\065-demo2.png", "PNG")<0) 
	{
		_getch();closegraph();	
		return 0; // 图片格式不标准时，退出程序，不继续往下
	}

	loadimage(&img, _T("res\\062-demo.jpg"),0,0);
	// 3.读取图片到img对象中，图片可以是png格式，也可以是jpg格式
	// 相对路径法表示文件名,可以修改为自定义的图片路径,
	// 第3、4个参数为设置图片长、宽;若想加载原图大小,可设为0，也可用loadimage(&img, _T("res\\062-demo.jpg"));

	loadimage(&img2, _T("res\\065-demo2.png"),200,200);

	putimage(0, 0, &img);
	// 4.显示 IMAGE 对象到需要的位置 在坐标 (0, 0) 位置显示 IMAGE 对象（图片）

	//putimage(450, 50, &img2);				// 非透明输出
	transparentimage(NULL, 450, 50, &img2);	// 透明输出
	// 4.显示 IMAGE 对象到需要的位置 在坐标 (450, 50) 位置显示 IMAGE 对象（图片）

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}

/*函数功能：检查path[]指向的图片是否存在，判断path[]指向的图片与nameSuffix[]指向的后缀名是否一致，显示path[]指向的图片本质类别
* 参数：path：图片路径，包含图片名称，绝对路径相对路径皆可以
*       nameSuffix：path文件的后缀名，大小。如：demo.jpg要写成JPG。目前仅支持检查：JPG、PNG、GIF三种类型
* 返回值：0一切正常，-1有异常，程序内部进行提示是何种异常。*/
int recognitionPicture(char path[], char nameSuffix[])
{
	char buf[11];
	FILE *fp;
	fopen_s(&fp,path,"rb");
	setbkmode(TRANSPARENT);	
	settextcolor(RGB(255,0,0)); 
	settextstyle(20, 0, _T("楷体"));
	if (NULL == fp) 
	{
		outtextxy(0,0,_T("文件打开失败，可能原因：1.文件不存在；2.路径错误；3.路径名含有无法识别字符"));
		getchar();
		return -1;
	}
	fread(buf, sizeof(buf), 1 , fp); //		读取文件
	if(strncmp("JFIF", buf + 6, strlen("JEIF")) == 0)
		// 如果是JPEG文件，其文件偏移第六个字节处为JEIF
	{
		if(strncmp("JPG", nameSuffix, strlen("JPG")) == 0)
		{
			// outtextxy(0,0,_T("这是 JEPG，与后缀名类型一致。"));
			// 检查通过就不显示内容
			fclose(fp);
			return 0;
		}
		else
			outtextxy(0,0,_T("这是 JEPG，与后缀名类型不一致。"));
	}
	else if(strncmp("GIF89a", buf + 0, strlen("GIF89a")) == 0)
		// 如果是GIF文件，其文件偏移第0个字节处为GIF89a
	{
		if(strncmp("GIF", nameSuffix, strlen("GIF")) == 0)
		{
			// outtextxy(0,0,_T("这是 GIF，与后缀名类型一致。"));
			// 检查通过就不显示内容
			fclose(fp);
			return 0;
		}
		else
			outtextxy(0,0,_T("这是 GIF，与后缀名类型不一致。"));
	}
	else if(strncmp("PNG", buf + 1, strlen("PNG")) == 0)	
		// 如果是PNG文件，其文件偏移第1个字节处为PNG
	{
		if(strncmp("PNG", nameSuffix, strlen("PNG")) == 0)
		{
			// outtextxy(0,0,_T("这是 PNG，与后缀名类型一致。"));
			// 检查通过就不显示内容
			fclose(fp);
			return 0;
		}
		else
			outtextxy(0,0,_T("这是 PNG，与后缀名类型不一致。"));
	}
	else
		outtextxy(0,0,_T("该图片无法识别！"));
	fclose(fp);
	return -1; // 与后缀名类型不一致。
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