#ifndef TH10_ENEMY_SCRIPT_BIND_0040D830_HPP
#define TH10_ENEMY_SCRIPT_BIND_0040D830_HPP
struct BindScriptEntry_0040d830 {
    const char* name;
    unsigned int value;
};

struct BindScriptVm_0040d830;
struct BindScriptTable_0040d830 {
    unsigned int reserved_00;
    unsigned int reserved_04;
    int count;
    unsigned int reserved_0C[0x20];
    const BindScriptEntry_0040d830* entries;

    __declspec(noinline) int Resolve(const char* name);
};

// 0x0040CC70..0x0040CD00: Entity_ClearAnims
// Drop every animation slot's "active" flag and blank the eight 0x210-byte
// slot records, then clear the two trailing flags. The object arrives in EDX
// (__fastcall), its caller's ECX is unused, and the object is returned.
#include <string.h>

// One animation slot: a 0x210-byte record whose +0x204 word is the slot's own
// flag word (retail writes -1 there after blanking the record).
struct BindAnimationSlot_0040d830 {
    unsigned char unknown_000[0x204];
    int field_204;                                   // +0x204
    unsigned char unknown_208[0x8];
};

// The owner block is huge, so only the touched offsets are described. The flag
// words cleared up front sit at 0x12C, 0x17C, 0x1C8, 0x204, 0x240, 0x27C and
// 0x2B8; the slot table starts at 0x2C4.
struct BindAnimationOwner_0040d830 {
    unsigned char unknown_000[0x12C];
    unsigned flag_12C;                               // +0x12C
    unsigned char unknown_130[0x4C];
    unsigned flag_17C;                               // +0x17C
    unsigned char unknown_180[0x48];
    unsigned flag_1C8;                               // +0x1C8
    unsigned char unknown_1CC[0x38];
    unsigned flag_204;                               // +0x204
    unsigned char unknown_208[0x38];
    unsigned flag_240;                               // +0x240
    unsigned char unknown_244[0x38];
    unsigned flag_27C;                               // +0x27C
    unsigned char unknown_280[0x38];
    unsigned flag_2B8;                               // +0x2B8
    unsigned char unknown_2BC[0x8];
    BindAnimationSlot_0040d830 slots[8];                               // +0x2C4
    unsigned char unknown_1344[0xE8];
    unsigned flag_142C;                              // +0x142C
    unsigned char unknown_1430[0x10];
    unsigned flag_1440;                              // +0x1440
};


__declspec(noinline) BindAnimationOwner_0040d830* __fastcall ClearBoundAnimations_0040d830(int unused, BindAnimationOwner_0040d830* owner);
#endif
