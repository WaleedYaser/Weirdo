#include "kuro/kuro.h"
#include "kuro/cam2d.h"
#include "kuro/aa_rect.h"
#include "kuro/tile_map.h"

static zero_color_t c_teal  = zero_color_t{43, 151, 136, 255};
static zero_color_t c_lime  	= zero_color_t{205, 220, 71, 255};

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	zero_os_bitmap_fill(bitmap, c_black);

	kuro_cam2d_t cam = kuro_cam2d_new(32, 16);
	kuro_cam2d_fit(cam, bitmap->width, bitmap->height);

	static float vy = 0.0f;
	float fy = 0.0f;

	static vec2_t player_pos = vec2_t{0, 4};
	vec2_t player_dir = {0};
	float player_vel = 5.0f;

	if (msg->input.key_d.is_down)
		player_dir.x += 1.0f;
	if (msg->input.key_a.is_down)
		player_dir.x -= 1.0f;
	if (msg->input.key_w.down)
		fy = 20000.0f;

	fy -= 80.0f * 9.81f;
	float dy = vy * dt;
	float ay = fy / 50.0f;
	vy += ay * dt;

	vec2_t new_pos;
	new_pos.x = player_pos.x + dt * player_vel * player_dir.x;
	new_pos.y = player_pos.y + dy;

	if (kuro_tile_map_point_valid(vec2_t{new_pos.x - 0.5f, player_pos.y + 0.1f}) &&
		kuro_tile_map_point_valid(vec2_t{new_pos.x + 0.5f, player_pos.y + 0.1f}) &&
		kuro_tile_map_point_valid(vec2_t{new_pos.x - 0.5f, player_pos.y + 1.3f}) &&
		kuro_tile_map_point_valid(vec2_t{new_pos.x + 0.5f, player_pos.y + 1.3f}))
	{
		player_pos.x = new_pos.x;
	}

	if (kuro_tile_map_point_valid(vec2_t{player_pos.x - 0.5f, new_pos.y}) &&
		kuro_tile_map_point_valid(vec2_t{player_pos.x - 0.5f, new_pos.y + 1.4f}) &&
		kuro_tile_map_point_valid(vec2_t{player_pos.x + 0.5f, new_pos.y}) &&
		kuro_tile_map_point_valid(vec2_t{player_pos.x + 0.5f, new_pos.y + 1.4f}))
	{
		player_pos.y = new_pos.y;	
	}
	else
	{
		vy = 0.0f;
	}

	kuro_aa_rect_t player_rect = kuro_aa_rect_t{
		player_pos - vec2_t{0.5f, 0.0f},
		player_pos + vec2_t{0.5f, 1.4f},
		c_lime};

	static float seed = 0.0f;

	for (int j = 0; j < tile_map_count_y; ++j)
	{
		for (int i = 0; i < tile_map_count_x; ++i)
		{
			kuro_aa_rect_t tile_rect = kuro_tile_map_rect(i, j);
			kuro_aa_rect_raster(tile_rect, cam, bitmap, (uint32_t)seed);
		}
	}

	kuro_aa_rect_raster(player_rect, cam, bitmap, (uint32_t)(seed + 1));

	seed += dt * 5;
}
