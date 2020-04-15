#pragma once

#include "kuro/vec2.h"
#include "kuro/cam2d.h"

#include <zero/os/bitmap.h>

struct kuro_aa_rect_t
{
	vec2_t min;
	vec2_t max;
	zero_color_t color;
};

inline static float
lerp(float a0, float a1, float w)
{
	return (1.0f - w) * a0 + w * a1;
}

static float noise[540][960];
static bool init = false;

inline static void
kuro_aa_rect_raster(
	const kuro_aa_rect_t &self,
	const kuro_cam2d_t &cam,
	zero_os_bitmap_t *bitmap,
	int seed)
{

	if (init == false)
	{
		for (int j = 0; j < 540; ++j)
		{
			for (int i = 0; i < 960; ++i)
			{
				noise[j][i] = ((float)rand() / RAND_MAX) * 0.3f + 0.7f;
			}
		}
		init = true;
	}

	vec2_t pixel_min = kuro_cam2d_to_pixel(cam, self.min, bitmap->width, bitmap->height);
	vec2_t pixel_max = kuro_cam2d_to_pixel(cam, self.max, bitmap->width, bitmap->height);

	// because image is top down our min y bcome max y and vice verse
	float tmp = pixel_max.y;
	pixel_max.y = pixel_min.y;
	pixel_min.y = tmp;

	// clip
	pixel_min = vec2_max(pixel_min, vec2_t{});
	pixel_max = vec2_min(pixel_max, vec2_t{(float)bitmap->width, (float)bitmap->height});

	// TODO(Waleed): use float index instead
	for (int j = (int)pixel_min.y, cy = 0; j < pixel_max.y; ++j, ++cy)
	{
		for (int i = (int)pixel_min.x, cx = 0; i < pixel_max.x; ++i, ++cx)
		{
			float n = noise[seed % 540][(int)(((float)i / bitmap->width * 960) + 2 * j) % 960];

			zero_color_t color = self.color;
			if (n > 0.9f)
			{
				color = color * n;
			}
			else
			{
				color = color;
			}
			n = noise[(int)((float)j / bitmap->height * 540)][(int)((float)i / bitmap->width * 960)];
			color = color + color * (1 - n) * 0.5f;
			zero_os_bitmap_pixel_set(bitmap, i, j, color);
		}
	}
}
