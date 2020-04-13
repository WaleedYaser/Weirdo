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
static constexpr int tile_size   = 30;

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

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	static vec2_t player_pos = vec2_t{3 * tile_size, 12 * tile_size};
	vec2_t player_dir = {0};
	float player_vel = 5.0f * tile_size;

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

			if (map[j][i] != 0)
			{
				zero_os_bitmap_fill_rect(
					bitmap,
					i * tile_size,
					(map_count_y - j - 1) * tile_size,
					tile_size,
					tile_size,
					c_green);
			}
		}
	}
	zero_os_bitmap_fill_rect(bitmap, (int)player_pos.x, (int)player_pos.y, tile_size, tile_size, c_lime);
}
