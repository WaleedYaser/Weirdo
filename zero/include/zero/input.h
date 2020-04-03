#ifndef ZERO_INPUT_H
#define ZERO_INPUT_H

#include <stdbool.h>

typedef struct _zero_input
{
	int mouse_x;
	int mouse_y;

	bool key_w;
	bool key_s;
	bool key_a;
	bool key_d;
	bool key_space;
	bool key_escape;
} zero_input_t;

#endif
