#pragma once

// Default viewport application on device reset (retail 0x0043C1A0).

struct ViewportEnv {
	void (*flush_draw_queue)(void);
	int* viewport_slot; // global {x, y, width, height} rectangle
	void* device;
	void (*set_viewport)(void* device, const int* viewport);
	void (*reset_text_state)(void);
};

int Renderer_ApplyDefaultViewport(ViewportEnv* env);
