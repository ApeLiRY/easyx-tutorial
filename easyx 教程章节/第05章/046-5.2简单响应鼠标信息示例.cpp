#include <graphics.h>				// 引用EasyX图形库
#include <stdio.h>

int main()
{
	initgraph(640, 480);			// 创建一个宽640 x高480像素的窗口	

	MOUSEMSG msg;
	// 1.定义变量，保存鼠标消息

	FlushMouseMsgBuffer();
	// 清空鼠标消息缓冲区，避免无效鼠标信息带入到正式判断中
	
	while(true)						// 主循环,循环监听鼠标信息
	{	
		while (MouseHit())	
		// 2.监听鼠标信息;当有鼠标消息的时候执行,可检测连续的鼠标信息
		{
			msg = GetMouseMsg();	
			// 3.获取鼠标消息

			if (WM_LBUTTONDOWN == msg.uMsg)
			// 4.判断鼠标信息;鼠标左键按下
			{
				closegraph();
				return 0;
				// 5.响应鼠标点击的对应的操作 退出程序
			}
		}
		Sleep(10);					// 延时，降低 CPU 占用率
	}

	getchar();						// 暂停程序运行，查看输出结果
	closegraph();					// 关闭图形界面
	return 0;
}