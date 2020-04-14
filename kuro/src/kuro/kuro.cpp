#include "kuro/kuro.h"
#include "kuro/triangle.h"
#include "kuro/rect.h"
#include "kuro/line.h"

static zero_color_t c_black = zero_color_t{33, 33, 33, 255};
static zero_color_t c_teal  = zero_color_t{43, 151, 136, 255};
static zero_color_t c_brown = zero_color_t{119, 84, 73, 255};

static zero_color_t c_lime  	= zero_color_t{205, 220, 71, 255};
static zero_color_t c_green 	= zero_color_t{35, 136, 34, 255};
static zero_color_t c_dark_blue = zero_color_t{40, 43, 77, 255};


static constexpr int map_count_x = 32;
static constexpr int map_count_y = 16;
static constexpr int tile_size   = 1;

static uint8_t map[map_count_y][map_count_x] = {
	{1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1},
	{1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},

	{1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 0, 0, 0, 0, /**/ 1, 1, 1, 1},
	{1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 0, 0, 0, 0, /**/ 1, 1, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},

	{1, 1, 1, 1, /**/ 1, 1, 0, 0, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1},
	{1, 1, 1, 1, /**/ 1, 1, 0, 0, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},

	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 1, 1, 1, 1, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},
	{1, 1, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**//**/ 1, 1, 1, 1, /**/ 0, 0, 0, 0, /**/ 0, 0, 0, 0, /**/ 0, 0, 1, 1},
	{1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1},
	{1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**//**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1, /**/ 1, 1, 1, 1}};

inline static vec2_t
cam_to_pixel(vec2_t p_cam, float bottom, float left, float top, float right, uint32_t bitmap_width, uint32_t bitmap_heihgt)
{
	vec2_t p_ndc = vec2_t{
		(p_cam.x + right) / (right - left),
		(p_cam.y + top) / (top - bottom)};

	vec2_t p_raster = vec2_t{p_ndc.x * bitmap_width, p_ndc.y * bitmap_heihgt};

	return p_raster;
}

static constexpr float width  = 32.0f;
static constexpr float height = 16.0f;

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	float cam_right = width / 2.0f;
	float cam_top   = height / 2.0f;

	float x_scale = 1.0f;
	float y_scale = 1.0f;

	float cam_aspect_ratio = width / height;
	float bitmap_aspect_ratio = (float) bitmap->width / (float) bitmap->height;

	if (cam_aspect_ratio > bitmap_aspect_ratio)
		y_scale = cam_aspect_ratio / bitmap_aspect_ratio;
	else
		x_scale = bitmap_aspect_ratio / cam_aspect_ratio;

	cam_right *= x_scale;
	cam_top   *= y_scale;

	float cam_bottom = -cam_top;
	float cam_left   = -cam_right;

	static vec2_t player_pos = vec2_t{0, 0};
	vec2_t player_dir = {0};
	float player_vel = 5.0f;

	if (msg->input.key_d.is_down)
		player_dir.x += 1.0f;
	if (msg->input.key_a.is_down)
		player_dir.x -= 1.0f;
	if (msg->input.key_w.is_down)
		player_dir.y += 1.0f;
	if (msg->input.key_s.is_down)
		player_dir.y -= 1.0f;

	player_pos += dt * player_vel * player_dir;

	zero_os_bitmap_fill(bitmap, c_dark_blue);
	for (int j = 0; j < map_count_y; ++j)
	{
		for (int i = 0; i < map_count_x; ++i)
		{
			float x = (i - map_count_x / 2.0f);
			float y = (map_count_y / 2.0f - j - 1);

			vec2_t bl = vec2_t{x, y};
			vec2_t tr = vec2_t{x + 1.0f, y + 1.0f};

			vec2_t bl_raster = cam_to_pixel(
				bl,
				cam_bottom, cam_left, cam_top, cam_right,
				bitmap->width, bitmap->height);
			vec2_t tr_raster = cam_to_pixel(
				tr,
				cam_bottom, cam_left, cam_top, cam_right,
				bitmap->width, bitmap->height);

			if (map[j][i] != 0)
			{
				zero_os_bitmap_fill_rect(
					bitmap,
					(int)bl_raster.x,
					(int)bl_raster.y,
					(int)(tr_raster.x - bl_raster.x),
					(int)(tr_raster.y - bl_raster.y),
					c_green);
			}
		}
	}

	vec2_t bl = vec2_t{player_pos.x, player_pos.y};
	vec2_t tr = vec2_t{player_pos.x + 1.0f, player_pos.y + 1.0f};
	vec2_t bl_raster = cam_to_pixel(
		bl,
		cam_bottom, cam_left, cam_top, cam_right,
		bitmap->width, bitmap->height);
	vec2_t tr_raster = cam_to_pixel(
		tr,
		cam_bottom, cam_left, cam_top, cam_right,
		bitmap->width, bitmap->height);

	zero_os_bitmap_fill_rect(
		bitmap,
		(int)bl_raster.x,
		(int)bl_raster.y,
		(int)(tr_raster.x - bl_raster.x),
		(int)(tr_raster.y - bl_raster.y),
		c_lime);
}
