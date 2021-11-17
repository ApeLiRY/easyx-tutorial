#include <graphics.h>				// 引用EasyX图形库
#include <conio.h>
#include <stdio.h>
#include <io.h>

#pragma comment(lib, "Winmm.lib")    // 引用 Windows Multimedia API

int main()
{	
	initgraph(812, 453);			// 创建一个宽812 x高453像素的窗口	

	// 产生临时文件的文件路径及文件名
	TCHAR tmpmp3[_MAX_PATH];
	GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat_s(tmpmp3, _T("056-7.3周杰伦 - 青花瓷.mp3")); // 所加载的音频名称

	// 6.{ 提取资源中的音频存储到临时文件夹中
	// 创建空文件
	HANDLE hFile = CreateFile(tmpmp3, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return 0;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC    hRes    = FindResource(NULL, _T("MYMP3"), _T("MP3"));  // 资源ID、类型名称	
	HGLOBAL    hMem    = LoadResource(NULL, hRes);
	DWORD    dwSize    = SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0; // 返回写入字节
	WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	CloseHandle(hFile);
	// } 已将所加载音频文件读取到内存中了，路径名存于 tmpmp3 中

	// 以下内容与第7章类似

	// 7.检查资源是否存在，详细说明参见7.2和7.3节内容，相对路径法表示文件名
	if (_waccess(tmpmp3, 0) < 0)
	{
		printf("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名\n");
		_getch();
		return 0; // 资源不存在时，退出程序，不继续往下
	}

	// 8.打开音乐 open ***
	TCHAR mcicmd[300];
	MCIERROR mciError;				// 存储播放音乐过程中的异常情况代码
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);
	mciError=mciSendString(mcicmd, NULL, 0, NULL);
	if(mciError)					// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0;					// 播放失败时，退出程序，不继续往下
	}
	// 第一个参数是多媒体命令字符串，不区分大小写。程序中，先要通过 open 命令打开 *.*，并用 alias 指定别名为“***”，这样在之后的代码中就可以方便的通过“***”这个别名访问该音乐了。当然，并不是必须要指定别名，每次通过文件名访问也是可以的。
	// open 后面的音乐用绝对路径或相对路径都可以，如果文件名没有空格或特殊符号，文件名不必加双引号（注意转义\"表示引号"），建议最好加上双引号。
	// 注意各单词和参数之间的空格

	// 输出提示信息
	//	outtextxy(0, 0, _T("按任意键开始播放"));_getch();

	// 9.播放音乐  play ***
	mciError=mciSendString(_T("play mymusic"), NULL, 0, NULL);
	// 其他播放命令,可将上一行语句注释掉，打开下列两行中的任一行，进行体验
	// mciError=mciSendString(_T("play mymusic from 0"), NULL, 0, NULL); // 从头播放 from 0 ***
	// mciError=mciSendString(_T("play mymusic repeat"), NULL, 0, NULL); // 循环播放repeat  ***
	if(mciError)				// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	// 输出提示信息
	outtextxy(0, 0, _T("按任意键停止播放"));
	_getch();

	// 10.停止播放音乐  stop ***
	mciError=mciSendString(_T("stop mymusic"), NULL, 0, NULL); 	
	if(mciError)				// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	// 11.关闭音乐   close ***
	mciError=mciSendString(_T("close mymusic"), NULL, 0, NULL);
	if(mciError)				// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	// 12.删除临时文件，避免在电脑中留下垃圾文件
	DeleteFile(tmpmp3);

	// 输出提示信息
	outtextxy(0, 0, _T("按任意键退出程序"));
	_getch();

	// 播放失败时，故障码和对应说明表存于附件中-MultimediaMCI错误返回码详解
	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	closegraph();					// 关闭图形界面
	return 0;
}