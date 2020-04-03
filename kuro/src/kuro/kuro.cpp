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

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg)
{
	static vec2 player_pos = {0};
	vec2 player_vel = {0};

	if (msg->input.key_d)
	{
		player_vel.x += 10.0f;
	}
	if (msg->input.key_a)
	{
		player_vel.x -= 10.0f;
	}
	if (msg->input.key_w)
	{
		player_vel.y += 10.0f;
	}
	if (msg->input.key_s)
	{
		player_vel.y -= 10.0f;
	}

	player_pos.x += player_vel.x;
	player_pos.y += player_vel.y;

	zero_os_bitmap_fill(bitmap, zero_os_color_t{30, 30, 30});

	triangle_t t = {
		vec2{   0.0f,  100.0f}, // p1
		vec2{-100.0f, -100.0f}, // p2
		vec2{ 100.0f, -100.0f}, // p3
		vec3{255.0f, 255.0f, 255.0f},  // c1
		vec3{  0.0f, 255.0f, 255.0f},  // c2
		vec3{255.0f,   0.0f, 255.0f}}; // c3

	// mouse to frame
	vec2 mouse_pos = vec2{(float)msg->input.mouse_x, (float)msg->input.mouse_y};
	if (mouse_pos.x < 0.0f) mouse_pos.x = 0.0f;
	if (mouse_pos.y < 0.0f) mouse_pos.y = 0.0f;
	if (mouse_pos.x + 1 > msg->window_width) mouse_pos.x = (float)msg->window_width - 1.0f;
	if (mouse_pos.y + 1 > msg->window_height) mouse_pos.y = (float)msg->window_height - 1.0f;

	mouse_pos.x = mouse_pos.x - bitmap->width / 2.0f;
	mouse_pos.y = bitmap->height / 2.0f - mouse_pos.y;

	circle_t c = {
		mouse_pos,	// center
		20.0f,	   // radius
		vec3{200.0f, 100.0f, 50.0f}}; // color

	_kuro_raster_triangle(bitmap, t);
	_kuro_raster_circle(bitmap, c);

	circle_t p = {
		player_pos,	// center
		20.0f,	   // radius
		vec3{100.0f, 200.0f, 50.0f}}; // color
	_kuro_raster_circle(bitmap, p);
}
