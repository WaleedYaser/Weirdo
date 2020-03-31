#include "zero/os/window.h"
#include "zero/os/timer.h"

#include <stdio.h>

inline static void
_render_triangle(zero_os_bitmap_t *bitmap)
{
	float t1[2] = { 0.0f,  0.5f}; float c1[3] = {255.0f, 0.0f, 0.0f};
	float t2[2] = {-0.5f, -0.5f}; float c2[3] = {0.0f, 255.0f, 0.0f};
	float t3[2] = { 0.5f, -0.5f}; float c3[3] = {0.0f, 0.0f, 255.0f};

	int width = bitmap->width;
	int height = bitmap->height;

	float e1[2] = {t2[0] - t1[0], t2[1] - t1[1]};
	float e2[2] = {t3[0] - t2[0], t3[1] - t2[1]};
	float a = e1[0] * e2[1] - e1[1] * e2[0];

	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			float x = float(2 * i - width) / float(width);
			float y = float(2 * j - height) / float(height);

			float v1[2] = {t1[0] - x, t1[1] - y};
			float v2[2] = {t2[0] - x, t2[1] - y};
			float v3[2] = {t3[0] - x, t3[1] - y};

			float a1 = (v2[0] * v3[1] - v2[1] * v3[0]) / a;
			float a2 = (v3[0] * v1[1] - v3[1] * v1[0]) / a;
			float a3 = (v1[0] * v2[1] - v1[1] * v2[0]) / a;

			zero_os_color_t color;
			if ((a1 >= 0.0f) && (a2 >= 0.0f) && (a3 >= 0.0f))
			{
				uint8_t r = uint8_t(a1 * c1[0] + a2 * c2[0] + a3 * c3[0]);
				uint8_t g = uint8_t(a1 * c1[1] + a2 * c2[1] + a3 * c3[1]);
				uint8_t b = uint8_t(a1 * c1[2] + a2 * c2[2] + a3 * c3[2]);
				color = zero_os_color_t{r, g, b};
				bitmap->data[i + j * bitmap->width] = (color.r << 16) | (color.g << 8) | (color.b << 0);
			}
		}
	}
}

int
main()
{
	uint8_t target_fps = 30;
	float target_frame_ms = 1000.0f / float(target_fps);

	zero_os_window_t window = zero_os_window_create();
	zero_os_bitmap_t bitmap = zero_os_bitmap_new(1280, 720);

	zero_os_timer_period(1);
	zero_os_timer_t timer = zero_os_timer_start();
	while (true)
	{
		zero_os_window_message_t msg = zero_os_window_message(window);
		if (msg.quit)
			break;

		if (msg.window_width != bitmap.width || msg.window_height != bitmap.height)
			zero_os_bitmap_resize(&bitmap, msg.window_width, msg.window_height);

		zero_os_bitmap_fill(&bitmap, zero_os_color_t{});
		_render_triangle(&bitmap);
		zero_os_window_fill(window, &bitmap);

		zero_os_microseconds_t frame_time = zero_os_timer_end(timer);
		float busy_frame_ms = float(frame_time.ms) / 1000.0f;
		if (busy_frame_ms < target_frame_ms)
		{
			zero_os_timer_sleep(uint32_t(target_frame_ms - busy_frame_ms));
		}

		float frame_ms = zero_os_timer_end(timer).ms / 1000.0f;
		printf("busy frame ms: %0.4f ms, frame ms: %0.4f ms\n", busy_frame_ms, frame_ms);

		timer = zero_os_timer_start();
	}
	return 0;
}
