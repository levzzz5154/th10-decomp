// 0x00429B30..0x00429B53 (36 bytes): reseed a record's timer and store the
// caller's value into the record it points at.
//
// The record's +0x18 pointer leads to a timing block; its +0x0C word is handed
// to the CRT's _time32 at 0x00452B71, and the new value -- the caller's
// argument plus seven when it is non-zero, the global at 0x00474C7C otherwise --
// is stored into the pointed-at record's +0x5C word. The function always
// returns zero.
//
// The record arrives in EDI and the value in ESI, receivers no C++ declaration
// names, so the body is compiled in the native-LTCG cluster
// build_support/layout/ltcg/reseed.json whose synthetic caller establishes that
// convention. _time32 is an ordinary __cdecl leaf the declaration names.

struct TimerBlock {
    unsigned char unknown_0000[0x5C];
    int field_5C;                       // +0x5C
};

struct TimerRecord {
    unsigned char unknown_0000[0x18];
    TimerBlock* block;         // +0x18
};

extern "C" int __cdecl asm_FID_conflict___time32_00452b71(int* timer);
extern "C" int g_globals_stage;

__declspec(noinline) int Reseed(TimerRecord* record, int value);

#pragma code_seg(".text$01reseed")
int Reseed(TimerRecord* record, int value) {
    asm_FID_conflict___time32_00452b71((int*)((char*)record->block + 0x0C));
    record->block->field_5C = (value != 0) ? value + 7 : g_globals_stage;
    return 0;
}
#pragma code_seg()
