#include <stddef.h>

// 0x00421C70..0x00421C88: acquire the indexed slot lock and increment its
// nesting byte.  Native LTCG assigns the table to EDI and the slot to ESI;
// those private registers are why this is kept in a small cluster context.
struct SlotLockTable {
    unsigned char reserved_000[0x64C];
};

extern "C" void (__stdcall *imp_EnterCriticalSection)(void*);

#pragma code_seg(".text$01slot")
extern "C" __declspec(noinline) void SlotLockTable_EnterRetail(
        int slot, SlotLockTable* table) {
    imp_EnterCriticalSection((unsigned char*)table + 0x64C + slot * 0x18);
    ++*((unsigned char*)table + 0x6F4 + slot);
}
#pragma code_seg()
