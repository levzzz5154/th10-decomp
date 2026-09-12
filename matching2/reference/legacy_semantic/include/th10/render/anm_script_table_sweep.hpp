#pragma once

// ANM script table sweep releasing dead sprite slots (retail 0x00403990).
#include "th10/util/scalars.hpp"

// One entry of the packed sprite-slot list that begins at record+0x1C in
// retail. A negative id terminates the list; `step` is the byte offset from
// this slot to the next one.
struct AnmSpriteSlot {
	short id;
	short step;
	short reserved;
	short vm_index; // ANM VM pool slot (retail stride 0x3AC)
};

struct AnmSweepRecord {
	Byte flags;              // retail byte at +0x03; bit 0: active
	const AnmSpriteSlot* slots; // retail: packed slot list at +0x1C
};

struct AnmSweepEnv {
	const short* count;           // retail *(manager+0x10)
	AnmSweepRecord** records; // retail *(manager+0x14)
	void* vm_pool;                // retail manager+0x17C
	// Runs the ANM interpreter (retail 0x0043EE30) on pool slot `vm_index`
	// and reports whether that VM is still live afterwards (retail: the
	// instruction cursor at vm+0x390 is nonzero).
	int (*run_script)(void* vm_pool, int vm_index);
};

int AnmScriptTable_Sweep(AnmSweepEnv* env);
