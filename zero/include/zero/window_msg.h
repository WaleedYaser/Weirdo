#ifndef ZERO_WINDOW_MSG
#define ZERO_WINDOW_MSG

#include "zero/input.h"

#include <stdbool.h>

typedef struct _zero_window_msg
{
	bool quit;
	int window_width;
	int window_height;
	zero_input_t input;
} zero_window_msg_t;

#endif
