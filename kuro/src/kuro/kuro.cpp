#include "kuro/kuro.h"
#include "kuro/triangle.h"
#include "kuro/rect.h"
#include "kuro/line.h"

static zero_color_t c_black = zero_color_t{33, 33, 33, 255};
static zero_color_t c_teal  = zero_color_t{43, 151, 136, 200};
static zero_color_t c_brown = zero_color_t{119, 84, 73, 255};
static zero_color_t c_lime  = zero_color_t{205, 220, 71, 100};
static zero_color_t c_cyan  = zero_color_t{58, 190, 213, 255};
static zero_color_t c_red   = zero_color_t{255, 0, 0, 100};
static zero_color_t c_green = zero_color_t{0, 255, 0, 100};
static zero_color_t c_blue  = zero_color_t{0, 0, 255, 100};
static zero_color_t c_white = zero_color_t{255, 255, 255, 255};

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	// update
	static uint8_t grid[9][17] = {
		{1, 1, 1, 1,   1, 1, 1, 1,   0,   1, 1, 1, 1,   1, 1, 1, 1},
		{1, 0, 0, 1,   1, 1, 1, 1,   0,   0, 0, 0, 0,   0, 0, 0, 1},
		{1, 0, 0, 1,   0, 0, 0, 0,   0,   0, 0, 0, 0,   1, 1, 0, 1},
		{1, 0, 1, 1,   0, 0, 0, 0,   0,   0, 0, 0, 0,   1, 1, 0, 1},

		{0, 0, 0, 0,   0, 0, 0, 1,   0,   1, 1, 1, 1,   1, 1, 0, 0},

		{1, 1, 0, 1,   0, 0, 0, 1,   0,   0, 0, 0, 0,   1, 1, 0, 1},
		{1, 0, 0, 1,   0, 0, 0, 1,   0,   0, 0, 0, 0,   1, 0, 0, 1},
		{1, 0, 0, 1,   0, 0, 0, 1,   0,   0, 0, 0, 0,   1, 0, 0, 1},
		{1, 1, 1, 1,   1, 1, 1, 1,   0,   1, 1, 1, 1,   1, 1, 1, 1}};

	static vec2_t grid_start = {4, 3};
	int tile_size = 55;

	static vec2_t player_pos = {0};
	vec2_t player_dir = {0};
	float player_vel = (float)tile_size;

	if (msg->input.key_d.is_down)
		player_dir.x += 1.0f;
	if (msg->input.key_a.is_down)
		player_dir.x -= 1.0f;
	if (msg->input.key_w.is_down)
		player_dir.y += 1.0f;
	if (msg->input.key_s.is_down)
		player_dir.y -= 1.0f;

	player_pos += dt * player_vel * player_dir;

	// render
	zero_os_bitmap_fill(bitmap, c_black);

	for (int j = 0; j < 9; ++j)
	{
		for (int i = 0; i < 17; ++i)
		{
			zero_color_t tile_color = (grid[j][i] == 1 ? c_teal : c_brown);
			zero_os_bitmap_fill_rect(
				bitmap,
				(int)grid_start.x + i * tile_size,
				(int)grid_start.y + j * tile_size,
				tile_size,
				tile_size,
				tile_color);
		}
	}

	zero_os_bitmap_fill_rect(bitmap, (int)player_pos.x, (int)player_pos.y, tile_size, tile_size, c_lime);
}
