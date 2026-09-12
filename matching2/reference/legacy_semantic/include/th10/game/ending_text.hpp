#pragma once

// Ending-text controller construction with five text VMs (retail 0x0040BA90).
// streamer segment refill, and the 32-segment ripple ring update.

// ---------------------------------------------------------------------------
// 0x0040BA90 - ending-text controller (0xEC bytes, allocated by 0x0040B560
// right after the selected eNN.msg script is loaded)
// ---------------------------------------------------------------------------

struct EndingTimer {
	int previous;       // +0x00
	int current;        // +0x04
	float elapsed;      // +0x08
	const float* speed; // +0x0C (&DAT_00476F78 frame-speed global in the exe)
	unsigned int flags; // +0x10 (bit0 = initialized)
};

struct EndingText {
	int handle;                         // +0x00
	EndingTimer timer_a;               // +0x04
	EndingTimer timer_b;               // +0x18
	EndingTimer timer_c;               // +0x2C
	int vm_handles[5];                  // +0x40 (text VMs, scripts 0x42..0x46)
	const unsigned char* script_cursor; // +0x54 (first MSG script entry)
	unsigned int fields_58[7];          // +0x58..0x70 (zeroed here)
	unsigned int flags;                 // +0x74 (bit0 set on construction)
	unsigned int field_78;              // +0x78 (zeroed here)
	unsigned int color;                 // +0x7C (0x00FFFFFF)
	unsigned int fields_80[20];         // +0x80..0xCC (zeroed here)
	const void* on_deck_vtable;         // +0xD0 (PTR_FUN_004703E4 in the exe)
	unsigned int on_deck_fields[4];     // +0xD4..0xE0 (zeroed here)
	unsigned int fields_e4[2];          // +0xE4..0xE8 (zeroed here)
};

// The slice of the animation VM that batch 22 touches. Handles come back
// from the register hook and resolve through the find hook the same way
// AnimationManager_Find walks the two live lists.
struct EndingAnimationVm {
	int handle;               // +0x000 (list key compared by the find walk)
	int layer;                // +0x020 (set to 15 for ending text lines)
	unsigned int anim_flags;  // +0x35C (|= 0x40000000)
	unsigned int state_flags; // +0x360 (|= 2)
	unsigned char marker_a;   // +0x3A0 (= 0x10)
	unsigned char marker_b;   // +0x3A1 (= 0x10)
};

struct EndingTextEnv {
	void* manager; // g_pGameStateManager in the exe
	EndingAnimationVm* (*allocate_vm)(void* manager);         // hook 0x00449950
	void (*init_script)(EndingAnimationVm* vm, int script);   // hook 0x00449870
	int (*register_vm)(EndingAnimationVm* vm, void* manager); // hook 0x004489D0
	EndingAnimationVm* (*find_vm)(void* manager, int handle); // hook 0x004491C0
	const float* frame_speed;                                  // &DAT_00476F78
	const void* on_deck_vtable;                                // PTR_FUN_004703E4
};

EndingText* EndingText_Construct(EndingText* text,
                                        const unsigned char* script_cursor,
                                        const EndingTextEnv* env);
