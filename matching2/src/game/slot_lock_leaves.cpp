#include "th10/game/slot_lock_leaves.hpp"

// 0x00421C50 - Leave one slot lock. Retail carries the table base in
// EDI and the slot index in ESI; the critical sections are 0x18-byte
// records in an array at table+0x64C and each slot has a one-byte
// nesting depth counter in the parallel array at table+0x6F4. The
// readable form reifies both registers and injects the Win32
// LeaveCriticalSection edge.
void SlotLockTable_Leave(unsigned char* table, int slot,
                         void (*leave)(void*)) {
    if (leave != 0) {
        leave(table + 0x64c + slot * 0x18);
    }
    table[0x6f4 + slot] = (unsigned char)(table[0x6f4 + slot] - 1);
}

// 0x00421D20 - Release the COM object cached in the holder slot (retail
// ESI+0xC): call vtable slot 2 (Release) and clear the cache so the
// object is not released twice.
void CachedComSlot_Release(CachedComObject** slot) {
    CachedComObject* object = *slot;
    if (object != 0) {
        object->vtbl->release(object);
        *slot = 0;
    }
}
