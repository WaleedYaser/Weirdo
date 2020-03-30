#include "zero/os/window.h"

inline static void
_render_gradient(zero_os_bitmap_t *bitmap, int x_offset, int y_offset)
{
	for (int y = 0; y < bitmap->height; ++y)
	{
		for (int x = 0; x < bitmap->width; ++x)
		{
			zero_os_color_t c = zero_os_color_t{
				uint8_t(x + x_offset),
				uint8_t(y + y_offset),
				uint8_t(y + y_offset)};
			zero_os_bitmap_set(bitmap, x, y, c);
		}
	}
}

int
main()
{
	zero_os_window_t window = zero_os_window_create();
	zero_os_bitmap_t bitmap = zero_os_bitmap_new(1280, 720);

	int x_offset = 0;
	int y_offset = 0;
	while (true)
	{
		zero_os_window_message_t msg = zero_os_window_message(window);
		if (msg.quit)
			break;

		if (msg.window_width != bitmap.width || msg.window_height != bitmap.height)
			zero_os_bitmap_resize(&bitmap, msg.window_width, msg.window_height);

		_render_gradient(&bitmap, x_offset, y_offset);
		zero_os_window_fill(window, &bitmap);

		x_offset += 10;
		y_offset += 10;

		Sleep(5);
	}
	return 0;
}
