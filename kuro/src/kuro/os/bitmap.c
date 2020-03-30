#include "kuro/os/bitmap.h"

kuro_os_bitmap_t
kuro_os_bitmap_new(int width, int height)
{
	kuro_os_bitmap_t self = {0};

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
kuro_os_bitmap_free(kuro_os_bitmap_t *self)
{
	VirtualFree(self->data, 0, MEM_RELEASE);
}

void
kuro_os_bitmap_resize(kuro_os_bitmap_t *self, int width, int height)
{
	VirtualFree(self->data, 0, MEM_RELEASE);
	self->data = (uint32_t *)VirtualAlloc(
		0,
		4 * width * height,
		MEM_RESERVE | MEM_COMMIT,
		PAGE_READWRITE);

	self->bmi.bmiHeader.biWidth  = width;
	self->bmi.bmiHeader.biHeight = height;

	self->width  = width;
	self->height = height;
}

void
kuro_os_bitmap_fill(kuro_os_bitmap_t *self, kuro_os_color_t color)
{
	for (int i = 0; i < self->width * self->height; ++i)
	{
		self->data[i] = (color.r << 16) | (color.g << 8) | (color.b << 0);
	}
}

void
kuro_os_bitmap_set(kuro_os_bitmap_t *self, int x, int y, kuro_os_color_t color)
{
	self->data[x + y * self->width] = (color.r << 16) | (color.g << 8) | (color.b << 0);
}
