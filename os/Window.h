#pragma once

#include <windows.h>

namespace os
{
	struct Window
	{
		HWND hwnd;
	};

	Window
	window_new();

	void
	window_free(Window self);

	Event
	window_event(Window self);
}
