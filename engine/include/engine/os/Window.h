#pragma once

#include "engine/Exports.h"
#include "engine/os/Bitmap.h"

#include <windows.h>

namespace engine::os
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

	ENGINE_EXPORT Window
	window_create();

	ENGINE_EXPORT void
	window_destroy(Window &self);

	ENGINE_EXPORT Message
	window_message(Window &self);

	ENGINE_EXPORT void
	window_fill(Window &self, const Bitmap &bitmap);
}
