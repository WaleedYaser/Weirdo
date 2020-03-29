#include <os\Window.h>

namespace os
{
	inline static WNDCLASSEX
	_window_class()
	{
		static WNDCLASSEX wcx = {};
		if (wcx.size != 0)
		{
			wcx.size = sizeof(WNDCLASSEX);
			wcx.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
			wcx.lpfnWndProc = _main_window_proc;
			wcx.hInstance = 0;
			wcx.lpszClassName = "";

			auto res = RegisterClassEx(&wcx);
			assert(res == true && "RegisterClassEx failed");
		}
		return wcx;
	}

	Window
	window_new()
	{
		HWND hwnd = CreateWindowEx(
			0,
			wcx
		return Window{};
	}

	Window_Msg
	window_message(Window self)
	{
		Msg msg;
		PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
		/*
		 */
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
