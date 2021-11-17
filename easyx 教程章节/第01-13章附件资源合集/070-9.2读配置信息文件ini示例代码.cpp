#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>
#include <io.h>

int main()
{	
	int i;
	wchar_t s[50];

	// 检查资源是否存在，详细说明参见7.2和7.3节内容，相对路径法表示文件名
	if (_waccess(_T("res\\073-demo.ini"), 0) < 0) // 文件名
	{
		printf("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名\n");
		getchar();
		return 0; // 资源不存在时，退出程序，不继续往下
	}

	i = GetPrivateProfileInt(_T("test"), _T("x"), 320, _T("res\\073-demo.ini"));
	// 读入整形的配置值

	GetPrivateProfileString(_T("test"), _T("s"), _T("error"), s, sizeof(s), _T("res\\073-demo.ini"));
	// 读入字符串的配置值
	// 若.exe与.ini在同一目录则最后一个参数_【T("res\\073-demo.ini"))】应写成：【_T(".\\073-demo.ini")】

	printf("i=%d\ns=%ws\n",i,s);

	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	getchar();						// 暂停程序运行，查看输出结果
	return 0;
}