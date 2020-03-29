#pragma once

#include "engine/Exports.h"

#include <windows.h>
#include <stdint.h>

namespace engine::os
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

	ENGINE_EXPORT Bitmap
	bitmap_new(int width, int height);

	ENGINE_EXPORT void
	bitmap_free(Bitmap &self, int width, int height);

	ENGINE_EXPORT void
	bitmap_resize(Bitmap &self, int width, int height);

	ENGINE_EXPORT void
	bitmap_fill(Bitmap &self, const Color &color);

	ENGINE_EXPORT void
	bitmap_set(Bitmap &self, int x, int y, const Color &color);
}
