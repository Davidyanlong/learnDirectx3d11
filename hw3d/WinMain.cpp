
#include "Window.h"

// ��Ϊ�������ǵ��ļ�����winMain ���� ֱ��һ��main ������Ϊ��ں����ᱨ��
int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR				IpCmdLine,
	int						nCmdShow
)
{
	Window wnd(800, 300, "Donkey fart box");

	// 4. message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		// TranslateMessage will post auxilliary WM_CHAR messages from key msgs
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// check if GetMessage call itself borked
	if (gResult == -1) {
		return -1;
	}
	// wParam here is the value passed to PostQuitMessage
	return msg.wParam;

}