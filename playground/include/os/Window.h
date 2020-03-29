#pragma once

#include "os\Bitmap.h"

#include <windows.h>

namespace os
{
	struct Message
	{
		bool quit;
		int  window_width;
		int  window_height;
	};

	struct Window
	{
		HWND hwnd;
	};

	Window
	window_create();

	void
	window_destroy(Window &self);

	Message
	window_message(Window &self);

	void
	window_fill(Window &self, const Bitmap &bitmap);
}
