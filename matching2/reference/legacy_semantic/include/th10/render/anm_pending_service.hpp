#pragma once

// ANM archive pending-slot service pass (retail 0x00447700).

// --- 0x00447700 --------------------------------------------------------------
struct AnmPendingEntry {
	int script;   // retail +0x124
	int pending;  // retail +0x128
};

int AnmArchive_ServicePending(void* context, AnmPendingEntry** slots,
                              int slot_count,
                              int (*advance)(void* context,
                                             AnmPendingEntry* entry),
                              void (*discard)(AnmPendingEntry* entry),
                              void (*free_memory)(void* memory));
