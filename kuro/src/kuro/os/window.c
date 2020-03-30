
#include "kuro/os/window.h"

// TODO(Waleed): implement assert
#include <assert.h>
#include <stdint.h>

LRESULT CALLBACK
_kuro_os_main_window_procedure(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch(umsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

static WNDCLASSEX
_kuro_os_window_class(void)
{
	static WNDCLASSEX wcx;

	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style  = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = _kuro_os_main_window_procedure;
	wcx.hInstance = GetModuleHandle(NULL);
	wcx.lpszClassName = "kuro_os_window_class";

	ATOM res = RegisterClassEx(&wcx);
	assert(res && "RegisterClassEX failed");

	return wcx;
}

// API

kuro_os_window_t
kuro_os_window_create(void)
{
	WNDCLASSEX wcx = _kuro_os_window_class();
	HWND hwnd = CreateWindowEx(
		0,
		wcx.lpszClassName,
		"kuro",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0,
		0,
		wcx.hInstance,
		0);

	assert(hwnd && "CreateWindowEx failed");
	return (kuro_os_window_t) {.hwnd = hwnd};
}

void
kuro_os_window_destroy(kuro_os_window_t self)
{
	BOOL res = DestroyWindow(self.hwnd);
	assert(res && "DestroyWindow failed");
}

kuro_os_window_message_t
kuro_os_window_message(kuro_os_window_t self)
{
	kuro_os_window_message_t res = {0};

	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			res.quit = true;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Get window width and height
	RECT rcClient;
	GetClientRect(self.hwnd, &rcClient);
	res.window_width  = rcClient.right - rcClient.left;
	res.window_height = rcClient.bottom - rcClient.top;

	return res;
}

void
kuro_os_window_fill(kuro_os_window_t self, const kuro_os_bitmap_t *bitmap)
{
	HDC hdc = GetDC(self.hwnd);

	// Get window width and height
	RECT rcClient;
	GetClientRect(self.hwnd, &rcClient);
	int window_width  = rcClient.right - rcClient.left;
	int window_height = rcClient.bottom - rcClient.top;

	StretchDIBits(
		hdc,
		0, 0, window_width, window_height,
		0, 0, bitmap->width, bitmap->height,
		bitmap->data,
		&(bitmap->bmi),
		DIB_RGB_COLORS,
		SRCCOPY);
}
