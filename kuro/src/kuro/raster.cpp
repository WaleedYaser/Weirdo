#include "kuro/raster.h"

#include <assert.h>

struct aa_box_t
{
	vec2 min;
	vec2 max;
};

inline static vec2
_vec2_min(vec2 a, vec2 b)
{
	vec2 min;
	min.x = a.x < b.x ? a.x : b.x;
	min.y = a.y < b.y ? a.y : b.y;
	return min;
}

inline static vec2
_vec2_max(vec2 a, vec2 b)
{
	vec2 max;
	max.x = a.x > b.x ? a.x : b.x;
	max.y = a.y > b.y ? a.y : b.y;
	return max;
}

inline static aa_box_t
_kuro_triangle_aa_box(kuro_triangle_t t)
{
	return aa_box_t{
		_vec2_min(_vec2_min(t.p1, t.p2), t.p3),
		_vec2_max(_vec2_max(t.p1, t.p2), t.p3)};
}

inline static aa_box_t
_kuro_aa_box_clip(aa_box_t box, aa_box_t clip_box)
{
	if (box.min.x < clip_box.min.x) box.min.x = clip_box.min.x;
	if (box.min.y < clip_box.min.y) box.min.y = clip_box.min.y;
	if (box.max.x > clip_box.max.x) box.max.x = clip_box.min.x;
	if (box.max.y > clip_box.max.y) box.max.y = clip_box.min.y;
	return box;
}

inline static aa_box_t
_kuro_bitmap_aa_box(float width, float height)
{
	return aa_box_t{
		vec2{-width / 2.0f, -height / 2.0f},
		vec2{width / 2.0f, height / 2.0f}};
}

inline static float
_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

inline static void
_kuro_bitmap_color_set(zero_os_bitmap_t *bitmap, vec2 index, vec3 color)
{
	int x = (int)(index.x + (bitmap->width / 2.0f));
	int y = (int)(index.y + (bitmap->height / 2.0f));

	assert(x >= 0 && x < bitmap->width && y >= 0 && y <= bitmap->height &&
		"bitmap out of range");

	bitmap->data[x + y * bitmap->width] =
		((uint8_t)color.r << 16) |
		((uint8_t)color.g <<  8) |
		((uint8_t)color.b <<  0);
}

void
kuro_raster_triangle(zero_os_bitmap_t *bitmap, kuro_triangle_t t)
{
	aa_box_t triangle_box = _kuro_triangle_aa_box(t);
	aa_box_t bitmap_box   = _kuro_bitmap_aa_box((float)bitmap->width, (float)bitmap->height);
	aa_box_t clip_box     = _kuro_aa_box_clip(triangle_box, bitmap_box);

	vec2 e1 = vec2{t.p2.x - t.p1.x, t.p2.y - t.p1.y};
	vec2 e2 = vec2{t.p3.x - t.p2.x, t.p3.y - t.p2.y};
	float a = _cross(e1, e2);

	for (float y = clip_box.min.y; y < clip_box.max.y; ++y)
	{
		for (float x = clip_box.min.x; x < clip_box.max.x; ++x)
		{
			vec2 v1 = vec2{t.p1.x - x, t.p1.y - y};
			vec2 v2 = vec2{t.p2.x - x, t.p2.y - y};
			vec2 v3 = vec2{t.p3.x - x, t.p3.y - y};

			float a1 = _cross(v2, v3) / a;
			float a2 = _cross(v3, v1) / a;
			float a3 = _cross(v1, v2) / a;

			if ((a1 >= 0.0f) && (a2 >= 0.0f) && (a3 >= 0.0f))
			{
				vec3 color;
				color.r = a1 * t.c1.r + a2 * t.c2.r + a3 * t.c3.r;
				color.g = a1 * t.c1.g + a2 * t.c2.g + a3 * t.c3.g;
				color.b = a1 * t.c1.b + a2 * t.c2.b + a3 * t.c3.b;
				_kuro_bitmap_color_set(bitmap, vec2{x, y}, color);
			}
		}
	}
}

void
kuro_raster_rect(zero_os_bitmap_t *bitmap, kuro_rect_t rect)
{
	kuro_raster_triangle(bitmap, kuro_triangle_t{
		rect.p1, rect.p2, rect.p3, rect.c1, rect.c2, rect.c3});
	kuro_raster_triangle(bitmap, kuro_triangle_t{
		rect.p1, rect.p3, rect.p4, rect.c1, rect.c3, rect.c4});
}

void
kuro_raster_circle(zero_os_bitmap_t *bitmap, kuro_circle_t circle)
{
	aa_box_t circle_box = aa_box_t{
		vec2{circle.center.x - circle.radius, circle.center.y - circle.radius},
		vec2{circle.center.x + circle.radius, circle.center.y + circle.radius}};

	aa_box_t bitmap_box = _kuro_bitmap_aa_box((float)bitmap->width, (float)bitmap->height);
	aa_box_t clip_box   = _kuro_aa_box_clip(circle_box, bitmap_box);

	float r_squared = circle.radius * circle.radius;

	for (float y = clip_box.min.y; y < clip_box.max.y; ++y)
	{
		for (float x = clip_box.min.x; x < clip_box.max.x; ++x)
		{
			vec2 v = vec2{circle.center.x - x, circle.center.y - y};
			float d_squared = v.x * v.x + v.y * v.y;

			if (d_squared <= r_squared)
			{
				_kuro_bitmap_color_set(bitmap, vec2{x, y}, circle.color);
			}
		}
	}
}
