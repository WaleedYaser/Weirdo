#ifndef ZERO_INPUT_H
#define ZERO_INPUT_H

#include <stdbool.h>
#include <stdint.h>

typedef struct _zero_input_key
{
	bool up;
	bool down;
	bool is_down;
	uint8_t count;
} zero_input_key_t;

typedef struct _zero_input
{
	int mouse_x;
	int mouse_y;

	zero_input_key_t key_w;
	zero_input_key_t key_s;
	zero_input_key_t key_a;
	zero_input_key_t key_d;
	zero_input_key_t key_space;
	zero_input_key_t key_escape;
} zero_input_t;

#endif
