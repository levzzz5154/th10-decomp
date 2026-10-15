#pragma once
// Member construction retires each embedded record before the final player wipe.
#include <string.h>
#include <stddef.h>
#define PlayerReset_ClearFlag(address) do { unsigned int* flag = (address); *flag &= ~1u; } while (0)
struct PlayerResetSlot {
    char pad_000[0x6C];
    unsigned field_06C;
    char pad_070[0x40];
    unsigned field_0B0;
    char pad_0B4[0x48];
    unsigned field_0FC;
    char pad_100[0x28];
    unsigned field_128;
    char pad_12C[0x48];
    unsigned field_174;
    char pad_178[0x38];
    unsigned field_1B0;
    char pad_1B4[0x48];
    unsigned field_1FC;
    char pad_200[0x28];
    unsigned field_228;
    char pad_22C[0x14C];
    unsigned field_378;
    char pad_37C[8];
    unsigned short field_384;
    char pad_386[0x26];
    PlayerResetSlot() {
        PlayerReset_ClearFlag(&field_06C);
        PlayerReset_ClearFlag(&field_0B0);
        PlayerReset_ClearFlag(&field_0FC);
        PlayerReset_ClearFlag(&field_128);
        PlayerReset_ClearFlag(&field_174);
        PlayerReset_ClearFlag(&field_1B0);
        PlayerReset_ClearFlag(&field_1FC);
        PlayerReset_ClearFlag(&field_228);
        PlayerReset_ClearFlag(&field_378);
        memset(this,0,sizeof(*this));
        field_384=0xffff;
    }
};


// These bases and strides are also used by the complete pickup sweep.
struct PlayerTimerRecord14 {
    int previous, current;
    float elapsed;
    const float* speed;
    unsigned int flags;
    PlayerTimerRecord14() { PlayerReset_ClearFlag(&flags); }
};
struct PlayerPickupRecord5c {
    PlayerTimerRecord14 timer;
    unsigned char reserved_14[0x48];
};
struct PlayerAnimationRecord98 {
    unsigned char reserved_00[0x80];
    unsigned int flags;
    unsigned char reserved_84[0x14];
    PlayerAnimationRecord98() { PlayerReset_ClearFlag(&flags); }
};
struct PlayerIndicatorRecord6c {
    unsigned char reserved_00[0x44];
    PlayerTimerRecord14 timer;
    unsigned char reserved_58[0x14];
};
struct PlayerResetBlock {
    unsigned char reserved_000[0x14];
    PlayerResetSlot slot;
    unsigned char reserved_3c0[0x460-0x3c0];
    PlayerTimerRecord14 timer_460;
    PlayerTimerRecord14 timer_474;
    PlayerTimerRecord14 timer_488;
    PlayerPickupRecord5c pickups[128];
    unsigned char reserved_329c[4];
    PlayerAnimationRecord98 animations[4];
    unsigned char reserved_3500[0xC];
    PlayerIndicatorRecord6c indicators[33];
    unsigned char reserved_42f8[0x14];
    PlayerTimerRecord14 final_timer;
    unsigned char reserved_4320[0x4478-0x4320];
    __declspec(noinline) PlayerResetBlock();
    __declspec(noinline) int Initialize();
    unsigned int& Word(unsigned int offset) { return *(unsigned int*)((unsigned char*)this+offset); }
    float& Float(unsigned int offset) { return *(float*)((unsigned char*)this+offset); }
};
typedef char PlayerResetLayout[(
    sizeof(PlayerResetBlock)==0x4478 &&
    offsetof(PlayerResetBlock,slot)==0x14 &&
    offsetof(PlayerResetBlock,timer_460)==0x460 &&
    offsetof(PlayerResetBlock,timer_474)==0x474 &&
    offsetof(PlayerResetBlock,timer_488)==0x488 &&
    offsetof(PlayerResetBlock,pickups)==0x49c &&
    offsetof(PlayerResetBlock,animations)==0x32a0 &&
    offsetof(PlayerResetBlock,indicators)==0x350c &&
    offsetof(PlayerResetBlock,final_timer)==0x430c &&
    offsetof(PlayerTimerRecord14,flags)==0x10 &&
    sizeof(PlayerPickupRecord5c)==0x5c &&
    sizeof(PlayerAnimationRecord98)==0x98 &&
    sizeof(PlayerIndicatorRecord6c)==0x6c)?1:-1];
extern "C" PlayerResetBlock* g_player;
