#include <string.h>

// 0x004220E0: initialise a freshly allocated recovery state in place.
//
// The factory at 0x00422360 calls this with the object in EDX and keeps the
// result from EAX, so the object pointer is the second __fastcall parameter.
extern "C" void* g_pause_menu;

struct RecoveryState {
    unsigned flags;              // +0x000
    char pad_004[0x1C];
    unsigned field_20;           // +0x020
    int field_24;                // +0x024
    char pad_028[0x04];
    int field_2C;                // +0x02C
    char pad_030[0x80];
    int field_B0;                // +0x0B0
    char pad_0B4[0x40];
    int field_F4;                // +0x0F4
    int field_F8;                // +0x0F8
    int field_FC;                // +0x0FC
    char pad_100[0x04];
    int field_104;               // +0x104
    char pad_108[0x80];
    int field_188;               // +0x188
    char pad_18C[0x40];
    int field_1CC;               // +0x1CC
    int field_1D0;               // +0x1D0
    char pad_1D4[0xF4];
};

void* __fastcall RecoveryState_Initialize(int unused, RecoveryState* state) {
    state->field_20 &= ~1u;
    state->field_B0 = 0;
    state->field_24 = 0;
    state->field_F8 = 0;
    state->field_F4 = 1;
    // The two maxima are written through a raw pointer: retail materialises the
    // constant beside the stores and only schedules it there for an indirect
    // store, while a member store lets the optimiser sink it past the callee
    // save.
    unsigned* maximum = (unsigned*)((char*)state + 0x2C);
    *maximum = 999;
    maximum = (unsigned*)((char*)state + 0x104);
    *maximum = 999;
    state->field_188 = 0;
    state->field_FC = 0;
    state->field_1D0 = 0;
    state->field_1CC = 1;
    memset(state, 0, sizeof(*state));
    state->flags |= 2u;
    g_pause_menu = state;
    return state;
}
