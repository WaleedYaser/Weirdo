#pragma once

#include "kuro/export.h"

#include <zero/window_msg.h>
#include <zero/os/bitmap.h>

#ifdef __cplusplus
extern "C" {
#endif

KURO_API void
kuro_frame(zero_os_bitmap_t *bitmap, zero_window_msg_t *input, float delta_time);

typedef void (*kuro_frame_proc_t)(zero_os_bitmap_t *, zero_window_msg_t *, float);
kuro_frame_proc_t ex_kuro_frame;

#ifdef __cplusplus
}
#endif
