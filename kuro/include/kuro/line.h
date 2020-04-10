#pragma once

#include "kuro/vec2.h"
#include "kuro/rect.h"

#include <zero/os/bitmap.h>

#include <math.h>

struct kuro_line_t
{
	vec2_t p1, p2;
	float width;
	zero_color_t c1, c2;
};

void
kuro_line_raster(const kuro_line_t &self, zero_os_bitmap_t *bitmap)
{
	vec2_t p = perpendicular(normalize(self.p2 - self.p1));

	float width_2 = self.width / 2.0f;

	vec2_t p1 = self.p1 + width_2 * p;
	vec2_t p2 = self.p1 - width_2 * p;
	vec2_t p3 = self.p2 - width_2 * p;
	vec2_t p4 = self.p2 + width_2 * p;

	kuro_rect_raster(kuro_rect_t{p1, p2, p3, p4, self.c1, self.c1, self.c2, self.c2}, bitmap);
}

