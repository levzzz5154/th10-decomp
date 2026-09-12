#pragma once

// Cached COM-style object with the standard three-slot vtable prologue
// (QueryInterface / AddRef / Release); only Release (index 2) is used by
// the recovered leaves.
struct CachedComObject;
struct CachedComVtbl {
    void* query_interface;
    void* add_ref;
    void(__stdcall* release)(CachedComObject*);
};
struct CachedComObject {
    const CachedComVtbl* vtbl;
};

// 0x00421C50 - Leave one slot lock in the 0x18-byte critical-section
// array at table+0x64C and decrement the paired per-slot depth byte at
// table+0x6F4. The Win32 LeaveCriticalSection edge is injected.
void SlotLockTable_Leave(unsigned char* table, int slot,
                         void (*leave)(void*));

// 0x00421D20 - Release the COM object cached in a holder slot (retail
// holder+0xC) through vtable slot 2 and clear the slot.
void CachedComSlot_Release(CachedComObject** slot);
