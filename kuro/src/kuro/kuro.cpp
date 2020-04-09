#include "kuro/kuro.h"
#include "kuro/raster.h"
#include "kuro/rect.h"

#define PI 3.14159265359f

static vec3 c_black = vec3{33.0f, 33.0f, 33.0f};
static vec3 c_teal  = vec3{43.0f, 151.0f, 136.0f};
static vec3 c_brown = vec3{119.0f, 84.0f, 73.0f};
static vec3 c_lime  = vec3{205.0f, 220.0f, 71.0f};
static vec3 c_cyan  = vec3{58.0f, 190.0f, 213.0f};
static vec3 c_red   = vec3{255.0f, 0.0f, 0.0f};
static vec3 c_green = vec3{0.0f, 255.0f, 0.0f};
static vec3 c_blue  = vec3{0.0f, 0.0f, 255.0f};
static vec3 c_white = vec3{255.0f, 255.0f, 255.0f};

static bool _init = true;

inline static zero_os_color_t
_os_color_from_vec3(vec3 color)
{
	return zero_os_color_t{(uint8_t) color.r, (uint8_t) color.g, (uint8_t) color.b};
}


void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	// initializtation code
	static rect_t rect   = rect_new(vec2_t{200.0f, 0.0f}, 100.0f, 50.0f);
	static vec2_t spring = vec2_t{0};
	static float stiffness = 0.5f;
	static float angular_b = -7.0f;
	static float b = -1.0f;

	if (_init)
	{
		rect.v = vec2_t{0.0f, 2.0f};
		_init = false;
	}

	// loop
	vec2_t f = vec2_t{0};
	float torque = 0.0f;

	// verlet
	vec2_t dr = rect.v * dt + rect.a * 0.5f * dt * dt;
	rect_move(rect, dr * 100.0f);

	// add gravity
	f -= vec2_t{0.0f, rect.m * 9.81f};

	// add damping
	f += rect.v * b;

	// add spring
	vec2_t spring_force = (rect.tl - spring) * -stiffness;
	vec2_t _r = rect_center(rect) - rect.tl;

	// the cross product informs us of the box's tendency to rotate
	float rxf = cross(_r, spring_force);

	torque -= rxf;
	f += spring_force;

	// finish velocity verlet
	vec2_t new_a = f * rect.m;
	vec2_t dv = (rect.a + new_a) * 0.5 * dt;
	rect.v += dv;

	// do rotation
	torque += rect.omega * angular_b; // angular damping
	rect.alpha = torque / rect.j;
	rect.omega += rect.alpha * dt;
	float delta_theta = rect.omega * dt;
	rect_rotate(rect, delta_theta);

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

	float ground_y = 50.0f - (float)bitmap->height / 2.0f;

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

	kuro_raster_rect(bitmap, kuro_rect_t{
		vec2{rect.tl.x, rect.tl.y},
		vec2{rect.tr.x, rect.tr.y},
		vec2{rect.br.x, rect.br.y},
		vec2{rect.bl.x, rect.bl.y},
		c_brown, c_brown, c_brown, c_brown});

	kuro_raster_line(bitmap, kuro_line_t{
		vec2{spring.x, spring.y}, vec2{rect.tl.x, rect.tl.y}, 2.0f, c_black});

	kuro_raster_circle(bitmap, kuro_circle_t{
		vec2{spring.x, spring.y}, 5.0f, c_black});

	kuro_raster_circle(bitmap, kuro_circle_t{
		vec2{rect.tl.x, rect.tl.y}, 5.0f, c_black});

	// rect_rotate(debug_rect, dt);
}
