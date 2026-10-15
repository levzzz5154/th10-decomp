#include "th10/game/spt_test_state.hpp"
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" unsigned char data_00477844;

#pragma code_seg(".text$00binit")
// 0x0042BB30..0x0042BBC0: construct the script tester (SptTest; its embedded script object has vtable 0x004703E4). Nothing calls it: the debug tool is unreachable in retail.
extern "C" __declspec(noinline) SptTestState* __fastcall SptTest_Construct(
    int unused, SptTestState* state) {
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

#pragma code_seg()
