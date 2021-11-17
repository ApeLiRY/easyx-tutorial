#include <graphics.h>				// 引用EasyX图形库
#include <conio.h>
#include <stdio.h>
#include <io.h>
#pragma comment(lib,"Winmm.lib")	// 引用 Windows Multimedia API,用于播放音乐

int main()
{	
	MCIERROR mciError;				// 存储播放音乐过程中的异常情况代码

	// 1.检查资源是否存在，详细说明参见7.2和7.3节内容，相对路径法表示文件名
	if (_waccess(_T("res\\056-7.3周杰伦 - 青花瓷.mp3"), 0) < 0)
	{
		printf("文件不存在，原因可能是:1.资源不存在；2.路径错误；3.无法识别文件(夹)名\n");
		_getch();
		return 0; // 资源不存在时，退出程序，不继续往下
	}

	// 2.打开音乐 open ***
	mciError=mciSendString(_T("open \"res\\056-7.3周杰伦 - 青花瓷.mp3\" alias mymusic"), NULL, 0, NULL);
	if(mciError)					// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0;					// 播放失败时，退出程序，不继续往下
	}
	// 第一个参数是多媒体命令字符串，不区分大小写。程序中，先要通过 open 命令打开 *.*，并用 alias 指定别名为“***”，这样在之后的代码中就可以方便的通过“***”这个别名访问该音乐了。当然，并不是必须要指定别名，每次通过文件名访问也是可以的。
	// open 后面的音乐用绝对路径或相对路径都可以，如果文件名没有空格或特殊符号，文件名不必加双引号（注意转义\"表示引号"），建议最好加上双引号。
	// 注意各单词和参数之间的空格

	printf("按任意键开始播放-1       \r");_getch();	// 暂停程序

	// 3.播放音乐  play ***
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

	printf("按任意键停止播放        \r");_getch();	// 暂停程序

	// 4.停止播放音乐  stop ***
	mciError=mciSendString(_T("stop mymusic"), NULL, 0, NULL); 	
	if(mciError)				// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	printf("按任意键开始播放-2      \r");_getch();	// 暂停程序

	mciError=mciSendString(_T("play mymusic"), NULL, 0, NULL);  // 循环播放 repeat  ***
	if(mciError)				// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	printf("按任意键停止播放        \r");_getch();	// 暂停程序

	mciError=mciSendString(_T("stop mymusic"), NULL, 0, NULL); // 停止播放音乐  stop ***
	if(mciError)	// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	// 5.关闭音乐   close ***
	mciError=mciSendString(_T("close mymusic"), NULL, 0, NULL);
	if(mciError)				// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	printf("按任意键开始播放-3        \r");_getch();	// 暂停程序

	mciError=mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);// 循环播放repeat ***
	if(mciError)	// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	printf("按任意键停止播放        \r");_getch();	// 暂停程序

	mciError=mciSendString(_T("stop mymusic"), NULL, 0, NULL); // 停止播放音乐  stop ***
	if(mciError)	// 上述命令执行成功返回0，否则返回非0的故障码
	{
		printf("MCI 错误代码为：%d", mciError);// 查表，看错误代码对应的说明
		_getch();
		return 0; // 播放失败时，退出程序，不继续往下
	}

	// 播放失败时，故障码和对应说明表存于附件中-MultimediaMCI错误返回码详解
	// _T(“*”)是将*转换为unicode编码的一种常见方式,unicode编码内容参见1.2节
	return 0;
}