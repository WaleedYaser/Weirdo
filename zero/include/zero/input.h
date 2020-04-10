#pragma once

#include <stdbool.h>
#include <stdint.h>

struct zero_input_key_t
{
	bool up;
	bool down;
	bool is_down;
	uint8_t count;
};

struct zero_input_t
{
	int mouse_x;
	int mouse_y;

	union
	{
		// TODO(Waleed): don't use magic numbers
		zero_input_key_t keys[6];
		struct
		{
			zero_input_key_t key_w;
			zero_input_key_t key_s;
			zero_input_key_t key_a;
			zero_input_key_t key_d;
			zero_input_key_t key_space;
			zero_input_key_t key_escape;
		};
	};
};
