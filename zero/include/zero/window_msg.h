#pragma once

#include "zero/input.h"

#include <stdbool.h>

struct zero_window_msg_t
{
	bool quit;
	int window_width;
	int window_height;
	zero_input_t input;
};
