#include "kuro/kuro.h"

#include <assert.h>

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

	// clipping
	float width = (float) bitmap->width;
	float height = (float) bitmap->height;

	float width_over_2 = width / 2.0f;
	float height_over_2 = height / 2.0f;

	if (min.x < -width_over_2) min.x = -width_over_2;
	if (min.y < -height_over_2) min.y = -height_over_2;
	if (max.x < -width_over_2) max.x = -width_over_2;
	if (max.y < -height_over_2) max.y = -height_over_2;

	if (min.x > width_over_2) min.x = width_over_2;
	if (min.y > height_over_2) min.y = height_over_2;
	if (max.x > width_over_2) max.x = width_over_2;
	if (max.y > height_over_2) max.y = height_over_2;

	vec2 e1 = vec2{t.p2.x - t.p1.x, t.p2.y - t.p1.y};
	vec2 e2 = vec2{t.p3.x - t.p2.x, t.p3.y - t.p2.y};
	float a = _cross(e1, e2);

	for (int j = (int)min.y; j < (int)max.y; ++j)
	{
		for (int i = (int)min.x; i < (int)max.x; ++i)
		{
			vec2 v1 = vec2{t.p1.x - i, t.p1.y - j};
			vec2 v2 = vec2{t.p2.x - i, t.p2.y - j};
			vec2 v3 = vec2{t.p3.x - i, t.p3.y - j};

			float a1 = _cross(v2, v3) / a;
			float a2 = _cross(v3, v1) / a;
			float a3 = _cross(v1, v2) / a;

			if ((a1 >= 0.0f) && (a2 >= 0.0f) && (a3 >= 0.0f))
			{
				uint8_t r = (uint8_t)(a1 * t.c1.r + a2 * t.c2.r + a3 * t.c3.r);
				uint8_t g = (uint8_t)(a1 * t.c1.g + a2 * t.c2.g + a3 * t.c3.g);
				uint8_t b = (uint8_t)(a1 * t.c1.b + a2 * t.c2.b + a3 * t.c3.b);

				int x = i + (int)(width / 2.0f);
				int y = j + (int)(height / 2.0f);
				assert(x >= 0 && x < bitmap->width && y >= 0 && y <= bitmap->height &&
					"bitmap out of range");
				bitmap->data[x + y * bitmap->width] = (r << 16) | (g << 8) | (b << 0);
			}
		}
	}
}

inline static void
_kuro_raster_circle(zero_os_bitmap_t *bitmap, circle_t c)
{
	vec2 min = vec2{c.center.x - c.radius, c.center.y - c.radius};
	vec2 max = vec2{c.center.x + c.radius, c.center.y + c.radius};

	// clipping
	float width = (float) bitmap->width;
	float height = (float) bitmap->height;

	float width_over_2 = width / 2.0f;
	float height_over_2 = height / 2.0f;

	if (min.x < -width_over_2) min.x = -width_over_2;
	if (min.y < -height_over_2) min.y = -height_over_2;
	if (max.x < -width_over_2) max.x = -width_over_2;
	if (max.y < -height_over_2) max.y = -height_over_2;

	if (min.x > width_over_2) min.x = width_over_2;
	if (min.y > height_over_2) min.y = height_over_2;
	if (max.x > width_over_2) max.x = width_over_2;
	if (max.y > height_over_2) max.y = height_over_2;

	float r_squared = c.radius * c.radius;

	for (int j = (int)min.y; j < (int)max.y; ++j)
	{
		for (int i = (int)min.x; i < (int)max.x; ++i)
		{
			vec2 v = vec2{c.center.x - i, c.center.y - j};

			float d_squared = v.x * v.x + v.y * v.y;

			if (d_squared <= r_squared)
			{
				uint8_t r = (uint8_t)(c.color.r);
				uint8_t g = (uint8_t)(c.color.g);
				uint8_t b = (uint8_t)(c.color.b);

				int x = i + (int)(width / 2.0f);
				int y = j + (int)(height / 2.0f);
				assert(x >= 0 && x < bitmap->width && y >= 0 && y <= bitmap->height &&
					"bitmap out of range");
				bitmap->data[x + y * bitmap->width] = (r << 16) | (g << 8) | (b << 0);
			}
		}
	}
}

#define PI 3.14159265359f

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg)
{
	// source: http://buildnewgames.com/gamephysics/
	static float x = 0.0f;
	static float y = 200.0f;
	static float vy = 0.0f;
	static float ay = 0.0f;
	static float m = 0.1f;
	static float r = 20.0f;
	static float dt = 1.0f / 30.0f;
	static float e = -0.5f;
	static float rho = 1.2f;
	static float c_d = 0.47f;
	static float A = PI * r * r / 10000.0f;
	static float ground_y = -50.0f;

	float fy = 0.0f;

	fy -= m * 9.81f;
	fy += -1.0f * 0.5f * rho * c_d * A * vy * vy;

	float dy = vy * dt + (0.5f * ay * dt * dt);
	y += dy * 100.0f;

	float new_ay = fy / m;
	float avg_ay = 0.5f * (new_ay + ay);
	vy += avg_ay * dt;

	if (y - r < ground_y && vy < 0.0f)
	{
		vy *= e;
		y = ground_y + r;
	}

	zero_os_bitmap_fill(bitmap, zero_os_color_t{30, 30, 30});

	vec2 tl = vec2{-bitmap->width / 2.0f, -50.0f};
	vec2 tr = vec2{bitmap->width / 2.0f, -50.0f};
	vec2 bl = vec2{-bitmap->width / 2.0f, -bitmap->height / 2.0f};
	vec2 br = vec2{bitmap->width / 2.0f, -bitmap->height / 2.0f};


	vec3 ct = {0.0f, 200.0f, 100.0f};
	vec3 cb = {0.0f, 200.0f, 100.0f};

	_kuro_raster_triangle(bitmap, triangle_t{
		tl, tr, br,
		ct, ct, cb});

	_kuro_raster_triangle(bitmap, triangle_t{
		tl, br, bl,
		ct, cb, cb});

	_kuro_raster_circle(bitmap, circle_t{
		vec2{x, y}, r, vec3{200.0f, 50.0f, 100.0f}});


}
