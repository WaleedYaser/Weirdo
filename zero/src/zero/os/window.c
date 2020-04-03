#include "zero/os/window.h"

// TODO(Waleed): implement assert
#include <assert.h>
#include <stdint.h>

LRESULT CALLBACK
_zero_os_main_window_procedure(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
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
_zero_os_window_class(void)
{
	static WNDCLASSEX wcx;

	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.style  = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = _zero_os_main_window_procedure;
	wcx.hInstance = GetModuleHandle(NULL);
	wcx.lpszClassName = "zero_os_window_class";

	ATOM res = RegisterClassEx(&wcx);
	assert(res && "RegisterClassEX failed");

	return wcx;
}

// API

zero_os_window_t
zero_os_window_create(void)
{
	WNDCLASSEX wcx = _zero_os_window_class();
	HWND hwnd = CreateWindowEx(
		0,
		wcx.lpszClassName,
		"zero",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		0,
		0,
		wcx.hInstance,
		0);

	assert(hwnd && "CreateWindowEx failed");
	return (zero_os_window_t) {.hwnd = hwnd};
}

void
zero_os_window_destroy(zero_os_window_t self)
{
	BOOL res = DestroyWindow(self.hwnd);
	assert(res && "DestroyWindow failed");
}

void
zero_os_window_message(zero_os_window_t self, zero_window_msg_t *window_msg)
{
	MSG msg;
	while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);

		switch (msg.message)
		{
			case WM_QUIT:
				window_msg->quit = true;
				break;
			case WM_SYSKEYUP:
			case WM_KEYUP:
			{
				switch (msg.wParam)
				{
					case 'W':
						window_msg->input.key_w = false;
						break;
					case 'S':
						window_msg->input.key_s = false;
						break;
					case 'A':
						window_msg->input.key_a = false;
						break;
					case 'D':
						window_msg->input.key_d = false;
						break;
					case VK_SPACE:
						window_msg->input.key_space = false;
						break;
					case VK_ESCAPE:
						window_msg->input.key_escape = false;
						break;
				}
			} break;

			case WM_SYSKEYDOWN:
			case WM_KEYDOWN:
			{
				switch (msg.wParam)
				{
					case 'W':
						window_msg->input.key_w = true;
						break;
					case 'S':
						window_msg->input.key_s = true;
						break;
					case 'A':
						window_msg->input.key_a = true;
						break;
					case 'D':
						window_msg->input.key_d = true;
						break;
					case VK_SPACE:
						window_msg->input.key_space = true;
						break;
					case VK_ESCAPE:
						window_msg->input.key_escape = true;
						break;
				}
			} break;
		}

		DispatchMessage(&msg);
	}

	// get window width and height
	RECT rcClient;
	GetClientRect(self.hwnd, &rcClient);
	window_msg->window_width  = rcClient.right - rcClient.left;
	window_msg->window_height = rcClient.bottom - rcClient.top;

	// get mouse postition
	POINT point;
	BOOL err = GetCursorPos(&point);
	assert(err && "GetCursorPosition failed");
	err = ScreenToClient(self.hwnd, &point);
	assert(err && "ScreenToClient failed");
	window_msg->input.mouse_x = point.x;
	window_msg->input.mouse_y = point.y;
}

void
zero_os_window_fill(zero_os_window_t self, const zero_os_bitmap_t *bitmap)
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
