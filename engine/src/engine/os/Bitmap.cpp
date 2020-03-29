#include "engine/os/Bitmap.h"

namespace engine::os
{
	Bitmap
	bitmap_new(int width, int height)
	{
		Bitmap self{};

		self.data = (uint32_t *)VirtualAlloc(
			0,
			4 * width * height,
			MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE);

		self.bmi.bmiHeader.biSize		 = sizeof(BITMAPINFOHEADER);
		self.bmi.bmiHeader.biWidth		 = width;
		self.bmi.bmiHeader.biHeight		 = height;
		self.bmi.bmiHeader.biPlanes		 = 1;
		self.bmi.bmiHeader.biBitCount	 = 32;
		self.bmi.bmiHeader.biCompression = BI_RGB;

		self.width  = width;
		self.height = height;

		return self;
	}

	void
	bitmap_free(Bitmap &self)
	{
		VirtualFree(self.data, 0, MEM_RELEASE);
	}

	void
	bitmap_resize(Bitmap &self, int width, int height)
	{
		VirtualFree(self.data, 0, MEM_RELEASE);
		self.data = (uint32_t *)VirtualAlloc(
			0,
			4 * width * height,
			MEM_RESERVE | MEM_COMMIT,
			PAGE_READWRITE);

		self.bmi.bmiHeader.biWidth		 = width;
		self.bmi.bmiHeader.biHeight		 = height;

		self.width  = width;
		self.height = height;
	}

	void
	bitmap_fill(Bitmap &self, const Color &color)
	{
		for (int i = 0; i < self.width * self.height; ++i)
		{
			self.data[i] = (color.r << 16) | (color.g << 8) | (color.b << 0);
		}
	}

	void
	bitmap_set(Bitmap &self, int x, int y, const Color &color)
	{
		self.data[x + y * self.width] = (color.r << 16) | (color.g << 8) | (color.b << 0);
	}
}
