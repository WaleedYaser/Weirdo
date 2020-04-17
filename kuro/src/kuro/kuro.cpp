#include "kuro/kuro.h"
#include "kuro/cam2d.h"
#include "kuro/aa_rect.h"
#include "kuro/tile_map.h"

static zero_color_t c_teal = zero_color_t{43, 151, 136, 255};
static zero_color_t c_lime = zero_color_t{205, 220, 71, 255};

static bool init = false;

static float noise[540][960];
static float edge[540][960];
static float noise_offset = 0.0f;

static vec2_t player_pos = vec2_t{0, 4};
static float vy = 0.0f;

inline static void
kuro_post_edge(zero_os_bitmap_t *bitmap)
{
	for (int j = 1; j + 1 < bitmap->height; ++j)
	{
		for (int i = 1; i + 1 < bitmap->width; ++i)
		{
			uint32_t c_tl = bitmap->data[i - 1 + (j - 1) * bitmap->width];
			uint32_t c_t = bitmap->data[i + (j - 1) * bitmap->width];
			uint32_t c_tr = bitmap->data[i + 1 + (j - 1) * bitmap->width];

			uint32_t c_cl = bitmap->data[i - 1 + j * bitmap->width];
			uint32_t c_c = bitmap->data[i + j * bitmap->width];
			uint32_t c_cr = bitmap->data[i + 1 + j * bitmap->width];

			uint32_t c_bl = bitmap->data[i - 1 + (j + 1) * bitmap->width];
			uint32_t c_b = bitmap->data[i + (j + 1) * bitmap->width];
			uint32_t c_br = bitmap->data[i + 1 + (j + 1) * bitmap->width];

			float e = 0.0f;
			if (c_tl == c_t && c_t == c_tr && c_tr == c_cl &&
				c_cl == c_c && c_c == c_cr && c_cr == c_bl &&
				c_bl == c_b && c_b == c_br)
			{
			}
			else
			{
				e = 1.0f;
			}
			int x_edge = (int)((float) i / bitmap->width * 960);
			int y_edge = (int)((float) j / bitmap->height * 540);
			edge[y_edge][x_edge] = e;
		}
	}

	for (int j = 0; j < bitmap->height; ++j)
	{
		for (int i = 0; i < bitmap->width; ++i)
		{
			int x_edge = (int)((float) i / bitmap->width * 960);
			int y_edge = (int)((float) j / bitmap->height * 540);
			float e = edge[y_edge][x_edge];

			uint32_t color = (uint32_t)(bitmap->data[i + j * bitmap->width] * e);
			bitmap->data[i + j * bitmap->width] = color;
		}
	}
}

inline static void
kuro_post_proc(zero_os_bitmap_t *bitmap)
{
	for (int j = 0; j < bitmap->height; ++j)
	{
		for (int i = 0; i < bitmap->width; ++i)
		{
			int x_noise = (int)((float) i / bitmap->width * 960);
			int y_noise = (int)((float) j / bitmap->height * 540);

			int x_offset = 2 * j;
			int y_offset = (int)(noise_offset + 0.5f) % 540;

			zero_color_t color = zero_os_bitmap_pixel_get(bitmap, i, j);

			float n = 0.5f * (1.0f - noise[y_noise][x_noise]);
			float n_diagonal = noise[y_offset][(x_noise + x_offset) % 960];
			if (n_diagonal > 0.9f)
				color = n_diagonal * color;

			color = color + n * color;
			zero_os_bitmap_pixel_set(bitmap, i, j, color);
		}
	}
}

inline static void
kuro_init()
{
	if (init)
		return;

	for (int j = 0; j < 540; ++j)
	{
		for (int i = 0; i < 960; ++i)
		{
			noise[j][i] = ((float)rand() / RAND_MAX) * 0.3f + 0.7f;
		}
	}
	init = true;
}

void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *msg, float dt)
{
	kuro_init();

	zero_os_bitmap_fill(bitmap, c_black);

	kuro_cam2d_t cam = kuro_cam2d_new(32, 16);
	kuro_cam2d_fit(cam, bitmap->width, bitmap->height);

	float fy = 0.0f;

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


	for (int j = 0; j < tile_map_count_y; ++j)
	{
		for (int i = 0; i < tile_map_count_x; ++i)
		{
			kuro_aa_rect_t tile_rect = kuro_tile_map_rect(i, j);
			kuro_aa_rect_raster(tile_rect, cam, bitmap);
		}
	}

	kuro_aa_rect_raster(player_rect, cam, bitmap);
	zero_os_bitmap_fill_circle(bitmap, 200, 200, 100, c_teal);
	kuro_post_edge(bitmap);
	// kuro_post_proc(bitmap);

	noise_offset += dt * 5;
}
