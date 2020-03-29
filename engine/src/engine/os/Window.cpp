// TODO(Waleed): implement assert

#include "engine/os/Window.h"

#include <assert.h>
#include <stdint.h>

namespace engine::os
{
	LRESULT CALLBACK
	_main_window_procedure(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch(umsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}

	inline static WNDCLASSEX
	_window_class()
	{
		static WNDCLASSEX wcx = {};

		wcx.cbSize = sizeof(WNDCLASSEX);
		wcx.style  = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
		wcx.lpfnWndProc = _main_window_procedure;
		wcx.hInstance = GetModuleHandle(NULL);
		wcx.lpszClassName = "MyClass";

		ATOM res = RegisterClassEx(&wcx);
		assert(res && "RegisterClassEX failed");

		return wcx;
	}

	// API

	Window
	window_create()
	{
		WNDCLASSEX wcx = _window_class();
		HWND hwnd = CreateWindowEx(
			0,
			wcx.lpszClassName,
			"Title",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			0,
			0,
			wcx.hInstance,
			0);

		assert(hwnd && "CreateWindowEx failed");
		return Window{hwnd};
	}

	void
	window_destroy(Window &self)
	{
		BOOL res = DestroyWindow(self.hwnd);
		assert(res && "DestroyWindow failed");
	}

	Message
	window_message(Window &self)
	{
		Message res{};

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
	window_fill(Window &self, const Bitmap &bitmap)
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
			0, 0, bitmap.width, bitmap.height,
			bitmap.data,
			&bitmap.bmi,
			DIB_RGB_COLORS,
			SRCCOPY);
	}
};
