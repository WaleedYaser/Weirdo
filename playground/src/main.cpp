#include <zero/os/window.h>
#include <zero/os/timer.h>

#include <kuro/kuro.h>

#include <assert.h>
#include <stdio.h>

HMODULE kuro_dll;
FILETIME last_time;

inline static void
_load_kuro_dll()
{
	HANDLE hfile = CreateFile("kuro.dll", GENERIC_READ, FILE_SHARE_READ, NULL,
        OPEN_EXISTING, 0, NULL);
	assert(hfile && "can't open kuro.dll");

	FILETIME ftwrite;
	bool res = GetFileTime(hfile, nullptr, nullptr, &ftwrite);

	CloseHandle(hfile);
	if (res == false)
		return;

	if (CompareFileTime(&last_time, &ftwrite) == 0)
		return;

	if (kuro_dll)
	{
		res = FreeLibrary(kuro_dll);
		assert(res && "failed to unload kuro.dll");
	}

	res = CopyFile("kuro.dll", "kuro_tmp.dll", false);
	if (res == false)
		return;

	kuro_dll = LoadLibrary("kuro_tmp.dll");
	assert(kuro_dll && "failed to load kuro.dll");

	kuro_render_from_dll = (kuro_render_proc_t) GetProcAddress(kuro_dll, "kuro_render");
	assert(kuro_render_from_dll && "failed to load kuro_render_from_dll function");

	last_time = ftwrite;
}


int
main()
{
	uint8_t target_fps = 30;
	float target_frame_ms = 1000.0f / float(target_fps);

	zero_os_window_t window = zero_os_window_create();
	zero_os_bitmap_t bitmap = zero_os_bitmap_new(1280, 720);

	zero_os_timer_period(1);
	zero_os_timer_t timer = zero_os_timer_start();
	while (true)
	{
		_load_kuro_dll();

		zero_os_window_message_t msg = zero_os_window_message(window);
		if (msg.quit)
			break;

		if (msg.window_width != bitmap.width || msg.window_height != bitmap.height)
			zero_os_bitmap_resize(&bitmap, msg.window_width, msg.window_height);

		kuro_render_from_dll(&bitmap);
		zero_os_window_fill(window, &bitmap);

		zero_os_microseconds_t frame_time = zero_os_timer_end(timer);
		float busy_frame_ms = float(frame_time.ms) / 1000.0f;
		if (busy_frame_ms < target_frame_ms)
		{
			zero_os_timer_sleep(uint32_t(target_frame_ms - busy_frame_ms));
		}

		float frame_ms = zero_os_timer_end(timer).ms / 1000.0f;
		printf("busy frame ms: %0.4f ms, frame ms: %0.4f ms\n", busy_frame_ms, frame_ms);

		timer = zero_os_timer_start();
	}
	return 0;
}
