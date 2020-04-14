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

inline static void
kuro_aa_rect_raster(
	const kuro_aa_rect_t &self,
	const kuro_cam2d_t &cam,
	zero_os_bitmap_t *bitmap)
{
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
	for (int j = (int)pixel_min.y; j < pixel_max.y; ++j)
	{
		for (int i = (int)pixel_min.x; i < pixel_max.x; ++i)
		{
			zero_os_bitmap_pixel_set(bitmap, i, j, self.color);
		}
	}
}
