#include "kuro/kuro.h"

struct vec2
{
	float x, y;
};

union vec3
{
	struct
	{
		float x, y, z;
	};

	struct
	{
		float r, g, b;
	};
};

struct triangle_t
{
	vec2 p1, p2, p3;
	vec3 c1, c2, c3;
};

struct circle_t
{
	vec2 center;
	float radius;
	vec3 color;
};

inline static float
_cross(vec2 a, vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

inline static vec2
_kuro_to_screen(vec2 p, vec2 screen_dim)
{
	return vec2 {
		((p.x + 1.0f) * screen_dim.x) / 2.0f,
		((p.y + 1.0f) * screen_dim.y) / 2.0f};
}

inline static void
_kuro_raster_triangle(zero_os_bitmap_t *bitmap, triangle_t t)
{
	vec2 min = t.p1;
	vec2 max = t.p1;

	if (t.p2.x < min.x)
		min.x = t.p2.x;
	if (t.p3.x < min.x)
		min.x = t.p3.x;

	if (t.p2.y < min.y)
		min.y = t.p2.y;
	if (t.p3.y < min.y)
		min.y = t.p3.y;

	if (t.p2.x > max.x)
		max.x = t.p2.x;
	if (t.p3.x > max.x)
		max.x = t.p3.x;

	if (t.p2.y > max.y)
		max.y = t.p2.y;
	if (t.p3.y > max.y)
		max.y = t.p3.y;

	float width = (float) bitmap->width;
	float height = (float) bitmap->height;

	min = _kuro_to_screen(min, vec2{width, height});
	max = _kuro_to_screen(max, vec2{width, height});

	vec2 e1 = vec2{t.p2.x - t.p1.x, t.p2.y - t.p1.y};
	vec2 e2 = vec2{t.p3.x - t.p2.x, t.p3.y - t.p2.y};
	float a = _cross(e1, e2);

	for (int j = (int)min.y; j < (int)max.y; ++j)
	{
		for (int i = (int)min.x; i < (int)max.x; ++i)
		{
			float x = float(2 * (i + 0.5f) - width) / width;
			float y = float(2 * (j + 0.5f) - height) / height;

			vec2 v1 = vec2{t.p1.x - x, t.p1.y - y};
			vec2 v2 = vec2{t.p2.x - x, t.p2.y - y};
			vec2 v3 = vec2{t.p3.x - x, t.p3.y - y};

			float a1 = _cross(v2, v3) / a;
			float a2 = _cross(v3, v1) / a;
			float a3 = _cross(v1, v2) / a;

			if ((a1 >= 0.0f) && (a2 >= 0.0f) && (a3 >= 0.0f))
			{
				uint8_t r = (uint8_t)(a1 * t.c1.r + a2 * t.c2.r + a3 * t.c3.r);
				uint8_t g = (uint8_t)(a1 * t.c1.g + a2 * t.c2.g + a3 * t.c3.g);
				uint8_t b = (uint8_t)(a1 * t.c1.b + a2 * t.c2.b + a3 * t.c3.b);
				bitmap->data[i + j * bitmap->width] = (r << 16) | (g << 8) | (b << 0);
			}
		}
	}
}

void
_kuro_raster_circle(zero_os_bitmap_t *bitmap, circle_t c)
{
	vec2 min = vec2{c.center.x - c.radius, c.center.y - c.radius};
	vec2 max = vec2{c.center.x + c.radius, c.center.y + c.radius};

	float width = (float) bitmap->width;
	float height = (float) bitmap->height;

	min = _kuro_to_screen(min, vec2{width, height});
	max = _kuro_to_screen(max, vec2{width, height});

	float r_squared = c.radius * c.radius;

	for (int j = (int)min.y; j < (int)max.y; ++j)
	{
		for (int i = (int)min.x; i < (int)max.x; ++i)
		{
			float x = float(2 * (i + 0.5f) - width) / width;
			float y = float(2 * (j + 0.5f) - height) / height;

			vec2 v = vec2{c.center.x - x, c.center.y - y};

			float d_squared = v.x * v.x + v.y * v.y;

			if (d_squared <= r_squared)
			{
				uint8_t r = (uint8_t)(c.color.r);
				uint8_t g = (uint8_t)(c.color.g);
				uint8_t b = (uint8_t)(c.color.b);
				bitmap->data[i + j * bitmap->width] = (r << 16) | (g << 8) | (b << 0);
			}
		}
	}
}

void
kuro_render(zero_os_bitmap_t *bitmap)
{
	zero_os_bitmap_fill(bitmap, zero_os_color_t{30, 30, 30});

	triangle_t t = {
		vec2{ 0.0f,  0.5f}, // p1
		vec2{-0.5f, -0.5f}, // p2
		vec2{ 0.5f, -0.5f}, // p3
		vec3{255.0f, 255.0f, 255.0f},  // c1
		vec3{  0.0f, 255.0f, 255.0f},  // c2
		vec3{255.0f,   0.0f, 255.0f}}; // c3

	circle_t c = {
		vec2{0.5f, 0.5f}, // center
		0.3f,			  // radius
		vec3{200.0f, 100.0f, 50.0f}}; // color

	_kuro_raster_triangle(bitmap, t);
	_kuro_raster_circle(bitmap, c);
}
