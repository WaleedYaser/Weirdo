#include "zero/os/window.h"
#include "zero/os/timer.h"

#include <stdio.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */

inline static void
_render_gradient(zero_os_bitmap_t *bitmap, int x_offset, int y_offset)
{
	float t1[2] = {float(bitmap->width) / 2.0f, 0.0f};
	float t2[2] = {0.0f, float(bitmap->height)};
	float t3[2] = {float(bitmap->width), float(bitmap->height)};

	for (int x = 0; x < bitmap->width; ++x)
	{
		for (int y = 0; y < bitmap->height; ++y)
		{
			float v1[2] = {t1[0] - x, t1[1] - y};
			float v2[2] = {t2[1] - x, t2[1] - y};
			float v3[2] = {t3[2] - x, t3[1] - y};

			bool b1 = ((v1[0] * v2[1] - v1[1] * v2[0]) >= 0.0f);
			bool b2 = ((v2[0] * v3[1] - v2[1] * v3[0]) >= 0.0f);
			bool b3 = ((v3[0] * v1[1] - v3[1] * v1[0]) >= 0.0f);

			zero_os_color_t color;
			if (b1 && b2 && b3)
				color = zero_os_color_t{255, 0, 0};
			else
				color = zero_os_color_t{};

			bitmap->data[x + y * bitmap->width] = (color.r << 16) | (color.g << 8) | (color.b << 0);
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

	zero_os_timer_t timer = zero_os_timer_start();
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

		zero_os_microseconds_t frame_time = zero_os_timer_end(timer);
		if (frame_time.ms / 1000 < 30)
			zero_os_timer_sleep(uint32_t(30.0f - frame_time.ms / 1000.0f));

		// TODO(Waleed): doesn't work correctly
		frame_time = zero_os_timer_end(timer);
		printf("ms: %.2fms/f\n", frame_time.ms / 1000.0f);
	//	char buffer[256];
	// 	sprintf_s(buffer, sizeof(buffer), "ms: %.2fms/f\n", frame_time.ms / 1000.0f);
	//	OutputDebugString(buffer);

		timer = zero_os_timer_start();
	}
	return 0;
}
