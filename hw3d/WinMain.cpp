
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
		TranslateMessage(&msg );
		DispatchMessage(&msg);
	}

	if (gResult == -1) {
		return -1;
	}
	else
	{
		return msg.wParam;
	}
}