#include <zero/os/window.h>
#include <zero/os/timer.h>

#include <kuro/kuro.h>

#include <assert.h>
#include <stdio.h>

HMODULE kuro_dll;
FILETIME last_time;

inline static void
_set_current_dir_to_proc_dir()
{
	char filename[100] = {0};
	GetModuleFileName(0, filename, sizeof(filename));

	char *last_slash = filename;
	char* iter = filename;
	while (*iter++)
		if (*iter == '\\')
			last_slash = ++iter;
	*last_slash = '\0';
	bool res = SetCurrentDirectory(filename);
	assert(res && "SetCurrentDirectory failed");
}

inline static void
_load_kuro_dll()
{
	HANDLE hfile = CreateFile("kuro.dll", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
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

	ex_kuro_frame = (kuro_frame_proc_t) GetProcAddress(kuro_dll, "kuro_frame");
	assert(ex_kuro_frame && "failed to load kuro_render_from_dll function");

	last_time = ftwrite;
}


int
main()
{
	uint32_t width = 960;
	uint32_t height = 540;
	uint32_t target_fps = 30;

	_set_current_dir_to_proc_dir();

	zero_os_window_t window = zero_os_window_create(width, height);
	float target_frame_ms = 1000.0f / (float)target_fps;

	zero_os_bitmap_t bitmap = zero_os_bitmap_new(width, height);

	zero_os_timer_period(1);
	zero_os_timer_t timer = zero_os_timer_start();
	float delta_time = 0.0f;

	zero_window_msg_t msg = {0};
	while (true)
	{
		_load_kuro_dll();

		zero_os_window_message(window, &msg);
		if (msg.quit)
			break;

		if (msg.window_width != bitmap.width || msg.window_height != bitmap.height)
		{
			zero_os_bitmap_free(&bitmap);
			bitmap = zero_os_bitmap_new(msg.window_width, msg.window_height);
		}

		ex_kuro_frame(&bitmap, &msg, delta_time);
		zero_os_window_fill(window, &bitmap);

		// TODO(Waleed): not accurate yet
		zero_os_microseconds_t frame_time = zero_os_timer_end(timer);
		float busy_frame_ms = (float)frame_time.ms / 1000.0f;
		if (busy_frame_ms < target_frame_ms)
		{
			zero_os_timer_sleep(uint32_t(target_frame_ms - busy_frame_ms));
		}

		float frame_ms = zero_os_timer_end(timer).ms / 1000.0f;
		timer = zero_os_timer_start();

		delta_time = frame_ms / 1000.0f;
		printf("busy frame ms: %0.4f ms, frame ms: %0.4f ms\n", busy_frame_ms, frame_ms);
	}

	zero_os_bitmap_free(&bitmap);
	return 0;
}
