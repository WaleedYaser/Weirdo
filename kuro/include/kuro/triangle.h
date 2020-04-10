#pragma once

#include "kuro/vec2.h"

#include "zero/os/bitmap.h"

struct kuro_triangle_t
{
	vec2_t p1, p2, p3;
	zero_color_t c1, c2, c3;
};

inline static void
kuro_triangle_raster(const kuro_triangle_t &self, zero_os_bitmap_t *bitmap)
{
	vec2_t t_min = vec2_min(vec2_min(self.p1, self.p2), self.p3);
	vec2_t t_max = vec2_max(vec2_max(self.p1, self.p2), self.p3);

	t_min = vec2_max(t_min, vec2_t{0, 0});
	t_max = vec2_min(t_max, vec2_t{bitmap->width - 1.0f, bitmap->height - 1.0f});

	float a = cross(self.p2 - self.p1, self.p3 - self.p2);

	for (int j = (int)t_min.y; j < (int)t_max.y; ++j)
	{
		for (int i = (int)t_min.x; i < (int)t_max.x; ++i)
		{
			vec2_t v1 = self.p1 - vec2_t{i + 0.5f, j + 0.5f};
			vec2_t v2 = self.p2 - vec2_t{i + 0.5f, j + 0.5f};
			vec2_t v3 = self.p3 - vec2_t{i + 0.5f, j + 0.5f};

			float t1 = cross(v2, v3) / a;
			float t2 = cross(v3, v1) / a;
			float t3 = cross(v1, v2) / a;

			if (t1 >= 0 && t2 >= 0 && t3 >= 0)
			{
				zero_os_bitmap_pixel_blend(bitmap, i, j, t1 * self.c1 + t2 * self.c2 + t3 * self.c3);
			}
		}
	}
}

