#pragma once

#include <windows.h>
#include <stdint.h>

namespace os
{
	struct Color
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	struct Bitmap
	{
		BITMAPINFO bmi;
		uint32_t *data;
		int width;
		int height;
	};

	Bitmap
	bitmap_new(int width, int height);

	void
	bitmap_free(Bitmap &self, int width, int height);

	void
	bitmap_resize(Bitmap &self, int width, int height);

	void
	bitmap_fill(Bitmap &self, const Color &color);

	void
	bitmap_set(Bitmap &self, int x, int y, const Color &color);
}
