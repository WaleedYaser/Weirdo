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
	static int x = 0;
	static int y = 0;

	if (msg->input.key_d.is_down)
		x++;
	if (msg->input.key_a.is_down)
		x--;
	if (msg->input.key_w.is_down)
		y++;
	if (msg->input.key_s.is_down)
		y--;

	zero_os_bitmap_fill(bitmap, c_black);
	zero_color_t color = c_white;
	color.a = 200.0f;
	zero_os_bitmap_fill_rect(bitmap, 0, 0, bitmap->width, 100, c_teal);
	zero_os_bitmap_fill_circle(bitmap, x + 50, y + 50, 50, color);

	kuro_rect_raster(
		kuro_rect_t{
			vec2_t{50, 50}, vec2_t{200, 20}, vec2_t{500, 100}, vec2_t{10, 200},
			c_lime, c_lime, c_lime, c_lime},
		bitmap);

	kuro_line_raster(
		kuro_line_t{vec2_t{200, 200}, vec2_t{600, 600}, 20, c_red, c_blue},
		bitmap);

}
