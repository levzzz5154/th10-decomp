#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

extern "C" void* __cdecl memset(void* destination, int value,
                                  unsigned int size);

struct EffectPoolState {
    int unknown_00[4];
    int vtable;
    int field_14;
    int field_18;
    int field_1C;
    int field_20;
    unsigned char pad_024[0x18];
    int field_3C;
    unsigned char pad_040[4];
    int field_44;
    unsigned char pad_048[0x80];
    int field_0C8;
    unsigned char pad_0CC[0x40];
    int field_10C;
    int field_110;
    int field_114;
    unsigned char pad_118[4];
    int field_11C;
    unsigned char pad_120[0x80];
    int field_1A0;
    unsigned char pad_1A4[0x40];
    int field_1E4;
    int field_1E8;
    int field_1EC;
    unsigned char pad_1F0[4];
    int field_1F4;
    unsigned char pad_1F8[0x80];
    int field_278;
    unsigned char pad_27C[0x40];
    int field_2BC;
    int field_2C0;
    unsigned char tail_2C4[0x20];
};

typedef char EffectPoolState_size_must_be_2E4[
    sizeof(EffectPoolState) == 0x2E4 ? 1 : -1];

// 0x0042BB30..0x0042BBC0: FUN_0042bb30
extern "C" EffectPoolState* __fastcall FUN_0042bb30(
    int unused, EffectPoolState* state) {
    (void)unused;
    state->field_14 = 0;
    state->field_18 = 0;
    state->field_1C = 0;
    state->field_20 = 0;
    int* vtable = &state->vtable;
    *vtable = 0x4703E4;
    state->field_0C8 = 0;
    state->field_3C = 0;
    state->field_110 = 0;
    state->field_10C = 1;
    int* maximum = &state->field_44;
    *maximum = 999;
    state->field_1A0 = 0;
    state->field_114 = 0;
    state->field_1E8 = 0;
    maximum = &state->field_11C;
    *maximum = 999;
    state->field_1E4 = 1;
    maximum = &state->field_1F4;
    *maximum = 999;
    state->field_278 = 0;
    state->field_1EC = 0;
    state->field_2C0 = 0;
    state->field_2BC = 1;
    memset(state, 0, sizeof(*state));
    state->unknown_00[0] |= 2;
    *(int*)&data_00477844 = (int)state;
    return state;
}
