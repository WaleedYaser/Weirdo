#include "engine/os/Window.h"

inline static void
_render_gradient(engine::os::Bitmap &bitmap, int x_offset, int y_offset)
{
	for (int y = 0; y < bitmap.height; ++y)
	{
		for (int x = 0; x < bitmap.width; ++x)
		{
			engine::os::Color c = engine::os::Color{
				uint8_t(x + x_offset),
				uint8_t(y + y_offset),
				uint8_t(y + y_offset)};
			engine::os::bitmap_set(bitmap, x, y, c);
		}
	}
}

int
main()
{
	engine::os::Window window = engine::os::window_create();

	engine::os::Bitmap bitmap = engine::os::bitmap_new(1280, 720);

	int x_offset = 0;
	int y_offset = 0;
	while (true)
	{
		engine::os::Message msg = engine::os::window_message(window);
		if (msg.quit)
			break;

		if (msg.window_width != bitmap.width || msg.window_height != bitmap.height)
			engine::os::bitmap_resize(bitmap, msg.window_width, msg.window_height);

		_render_gradient(bitmap, x_offset, y_offset);
		engine::os::window_fill(window, bitmap);

		x_offset += 10;
		y_offset += 10;

		Sleep(5);
	}
	return 0;
}
