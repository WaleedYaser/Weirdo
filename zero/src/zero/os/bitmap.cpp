#include "zero/os/bitmap.h"

zero_os_bitmap_t
zero_os_bitmap_new(int width, int height)
{
	zero_os_bitmap_t self = {0};

	self.data = (DWORD *)VirtualAlloc(
		0,
		sizeof(DWORD) * width * height,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE);

	self.bmi.bmiHeader.biSize		 = sizeof(BITMAPINFOHEADER);
	self.bmi.bmiHeader.biWidth		 = width;
	self.bmi.bmiHeader.biHeight		 = -height; // the sign is negative to create top-down image
	self.bmi.bmiHeader.biPlanes		 = 1;
	self.bmi.bmiHeader.biBitCount	 = 32;
	self.bmi.bmiHeader.biCompression = BI_RGB;

	self.width  = width;
	self.height = height;

	return self;
}

void
zero_os_bitmap_free(zero_os_bitmap_t *self)
{
	VirtualFree(self->data, 0, MEM_RELEASE);
}

void
zero_os_bitmap_fill(zero_os_bitmap_t *self, zero_color_t color)
{
	DWORD raw = 
		((uint8_t)color.a) << 24 |
		((uint8_t)color.r) << 16 |
		((uint8_t)color.g) <<  8 |
		((uint8_t)color.b) <<  0 ;

	for (int i = 0; i < self->width * self->height; ++i)
	{
		self->data[i] = raw;
	}
}
