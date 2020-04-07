#include "kuro/kuro.h"
#include "kuro/raster.h"

#define PI 3.14159265359f

static vec3 c_black = vec3{33.0f, 33.0f, 33.0f};
static vec3 c_teal  = vec3{43.0f, 151.0f, 136.0f};
static vec3 c_brown = vec3{119.0f, 84.0f, 73.0f};
static vec3 c_lime  = vec3{205.0f, 220.0f, 71.0f};
static vec3 c_cyan  = vec3{58.0f, 190.0f, 213.0f};

inline static zero_os_color_t
_os_color_from_vec3(vec3 color)
{
	return zero_os_color_t{(uint8_t) color.r, (uint8_t) color.g, (uint8_t) color.b};
}

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	// source: http://buildnewgames.com/gamephysics/
	static float x = 0.0f;
	static float y = 200.0f;

	static float vy = 0.0f; // y velocity
	static float ay = 0.0f; // y acceleration

	static float m = 0.1f;	// mass in kg
	static float r = 20.0f;	// radius in cm

	static float e = -0.5f;		// coef of bouncing
	static float rho = 1.2f;	// density of air
	static float c_d = 0.47f;	// coef of drag
	static float A = PI * r * r * 10000.0f;	// frontal area of the ball

	static float ground_y = 30.0f - (float)bitmap->height / 2.0f;

	float fy = 0.0f;	// force

	if (msg->input.key_w.down && ((y - r) == ground_y))
	{
		fy = 20.0f;
	}

	if (msg->input.key_d.is_down)
	{
		x += dt * 150.0f;
	}

	if (msg->input.key_a.is_down)
	{
		x -= dt * 150.0f;
	}

	// gravity
	fy -= m * 9.81f;
	// air resistance force
	// fy += 1.0f * 0.5f * rho * c_d * A * vy * vy;

	float dy = vy * dt + (0.5f * ay * dt * dt);
	y += dy * 100.0f;

	float new_ay = fy / m;
	float avg_ay = 0.5f * (new_ay + ay);
	vy += avg_ay * dt;

	if (((y - r) < ground_y) && vy < 0.0f)
	{
		// vy *= e;
		y = ground_y + r;
		vy = 0.0f;
		ay = 0.0f;
	}

	zero_os_bitmap_fill(bitmap, _os_color_from_vec3(c_cyan));

	vec2 tl = vec2{-bitmap->width / 2.0f, ground_y};
	vec2 tr = vec2{bitmap->width / 2.0f, ground_y};
	vec2 bl = vec2{-bitmap->width / 2.0f, -bitmap->height / 2.0f};
	vec2 br = vec2{bitmap->width / 2.0f, -bitmap->height / 2.0f};

	kuro_raster_rect(bitmap, kuro_rect_t{
		tl, tr, br, bl, c_teal, c_teal, c_teal, c_teal});

	kuro_raster_rect(bitmap, kuro_rect_t{
		vec2{x - r, y - r}, vec2{x + r, y - r}, vec2{x + r, y + r}, vec2{x - r, y + r},
		c_lime, c_lime, c_lime, c_lime});
}
