#include "kuro/kuro.h"
#include "kuro/cam2d.h"
#include "kuro/aa_rect.h"
#include "kuro/tile_map.h"

static zero_color_t c_black = zero_color_t{33, 33, 33, 255};
static zero_color_t c_teal  = zero_color_t{43, 151, 136, 255};

static zero_color_t c_lime  	= zero_color_t{205, 220, 71, 255};
static zero_color_t c_dark_blue = zero_color_t{40, 43, 77, 255};

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	zero_os_bitmap_fill(bitmap, c_dark_blue);

	kuro_cam2d_t cam = kuro_cam2d_new(32, 16);
	kuro_cam2d_fit(cam, bitmap->width, bitmap->height);

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

	kuro_aa_rect_t player_rect = kuro_aa_rect_t{
		player_pos - vec2_t{0.5f, 0.0f},
		player_pos + vec2_t{0.5f, 1.0f},
		c_lime};

	for (int j = 0; j < tile_map_count_y; ++j)
	{
		for (int i = 0; i < tile_map_count_x; ++i)
		{
			kuro_aa_rect_t tile_rect = kuro_tile_map_rect(i, j);
			kuro_aa_rect_raster(tile_rect, cam, bitmap);
		}
	}

	kuro_aa_rect_raster(player_rect, cam, bitmap);
}
