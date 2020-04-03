#pragma once

#include "kuro/export.h"

#include <zero/window_msg.h>
#include <zero/os/bitmap.h>

KURO_API void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *input);

typedef void (*kuro_frame_proc_t)(zero_os_bitmap_t *, zero_window_msg_t *input);
kuro_frame_proc_t ex_kuro_frame;
