#pragma once

#include "kuro/export.h"

#include <zero/os/bitmap.h>

KURO_API void
kuro_render(zero_os_bitmap_t *bitmap);

typedef void (*kuro_render_proc_t)(zero_os_bitmap_t *);
kuro_render_proc_t kuro_render_from_dll;
