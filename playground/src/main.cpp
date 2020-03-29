#include "os\Window.h"

inline static void
_render_gradient(os::Bitmap &bitmap, int x_offset, int y_offset)
{
	for (int y = 0; y < bitmap.height; ++y)
	{
		for (int x = 0; x < bitmap.width; ++x)
		{
			os::Color c = os::Color{
				uint8_t(x + x_offset),
				uint8_t(y + y_offset),
				uint8_t(y + y_offset)};
			os::bitmap_set(bitmap, x, y, c);
		}
	}
}

int
main()
{
	os::Window window = os::window_create();

	os::Bitmap bitmap = os::bitmap_new(1280, 720);

	int x_offset = 0;
	int y_offset = 0;
	while (true)
	{
		os::Message msg = window_message(window);
		if (msg.quit)
			break;

		if (msg.window_width != bitmap.width || msg.window_height != bitmap.height)
			os::bitmap_resize(bitmap, msg.window_width, msg.window_height);

		_render_gradient(bitmap, x_offset, y_offset);
		os::window_fill(window, bitmap);

		x_offset += 10;
		y_offset += 10;

		Sleep(5);
	}
	return 0;
}
