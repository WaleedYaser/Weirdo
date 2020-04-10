#pragma once

#include "kuro/vec2.h"
#include "kuro/triangle.h"

#include <zero/os/bitmap.h>

struct kuro_rect_t
{
	vec2_t bl, br, tr, tl;
	zero_color_t c1, c2, c3, c4;
};

void
kuro_rect_raster(const kuro_rect_t &self, zero_os_bitmap_t *bitmap)
{
	kuro_triangle_t t1 = kuro_triangle_t {self.bl, self.br, self.tr, self.c1, self.c2, self.c3};
	kuro_triangle_t t2 = kuro_triangle_t {self.bl, self.tr, self.tl, self.c1, self.c3, self.c4};
	kuro_triangle_raster(t1, bitmap);
	kuro_triangle_raster(t2, bitmap);
}

