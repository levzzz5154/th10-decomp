// 0x0041FD90: if a record is flagged, raise the running bit of three
// sub-records, clear a global bit, publish a global mode and clear the flag.
// Both the early exit and the tail return 1, so MSVC merges them into one.
// The record arrives in EDX (dead leading __fastcall slot).  The global and the
// record flag are cleared through pointers to their fields so MSVC emits the
// read-modify-write `and [mem],imm` retail has instead of a load/and/store.
struct Sub2 { unsigned char pad_000[4]; unsigned int flags_004; };
struct Owner2 {
    unsigned char pad_000[0x0C];
    Sub2* a_00c;                 // +0x00C
    Sub2* b_010;                 // +0x010
    unsigned char pad_014[0x89a8 - 0x14];
    Sub2* c_89a8;                // +0x89A8
};
struct Flagged4 { unsigned int flags_000; };
extern "C" Owner2* g_ascii_manager;
extern "C" unsigned int g_app_flags;
extern "C" unsigned int g_main_state;
extern "C" __declspec(noinline) int __fastcall Update2(void* unused, Flagged4* record);
#pragma code_seg(".text$01flag")
int __fastcall Update2(void* unused, Flagged4* record) {
    (void)unused;
    if (!(record->flags_000 & 2u))
        return 1;
    Owner2* owner = g_ascii_manager;
    owner->a_00c->flags_004 |= 2u;
    owner->b_010->flags_004 |= 2u;
    owner->c_89a8->flags_004 |= 2u;
    unsigned int* global = &g_app_flags;
    *global &= 0xFFFFEFFFu;
    unsigned int* mode = &g_main_state;
    *mode = 4u;
    unsigned int* flags = &record->flags_000;
    *flags &= ~2u;
    return 1;
}
#pragma code_seg()
