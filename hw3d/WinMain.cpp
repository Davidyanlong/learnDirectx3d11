#include <Windows.h>
#include "WindowsMessageMap.h"
#include <string>
#include <sstream>

const wchar_t* GetWC(const char* c);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 因为这里我们的文件名是winMain 所以 直接一个main 方法作为入口函数会报错
int CALLBACK WinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPSTR				IpCmdLine,
	int						nCmdShow
)
{
	const auto pClassName = L"hw3dbutts";
	// 1. register window class
	//  https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/ns-winuser-wndclassexw
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = (wchar_t*)pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	// 2. create window instance
	// https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-createwindowexa
	HWND  hWnd = CreateWindowEx(
		0, pClassName,
		L"Happy Hard Window",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, 640, 480,
		nullptr, nullptr, hInstance, nullptr
	);

	// 3.show the damn window 
	// https://learn.microsoft.com/zh-cn/windows/win32/api/winuser/nf-winuser-showwindow
	ShowWindow(hWnd, SW_SHOW);

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

// char*  转换为 wchar_t*
const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
#pragma warning(disable:4996)
	mbstowcs(wc, c, cSize);

	return wc;
}

// 添加自定义的的消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	const wchar_t* msgW = GetWC(mm(msg, lParam, wParam).c_str());
	OutputDebugString(msgW);
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);	   // 点击关闭结束进程
		break;
	case WM_KEYDOWN:
	 // https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
		if (wParam == 'F')
		{
			SetWindowText(hWnd, L"Respects");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, L"Dangerfield");
		}
		break;
	case WM_CHAR:  // 输入文件就会触发
		{
			static std::wstring title;
			title.push_back((char)wParam);
			SetWindowText(hWnd, title.c_str());
		}
		break;
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		std::ostringstream oss;
		oss << "(" << pt.x << "," << pt.y << ")";
		SetWindowText(hWnd, GetWC(oss.str().c_str()));

	}
		break;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
