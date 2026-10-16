// 0x00421C90..0x00421CFD: the seven flag/mode accessors of one UI state
// record.
//
// Each entry reads the record out of EAX and returns either one bit of the
// flag dword at +0x150 or the mode byte at +0x13D, so seven separate regions
// share one object and one convention:
//
//   0x00421C90  (flags >> 6) & 1        0x00421CA0  (flags >> 5) & 1
//   0x00421CB0  (flags >> 3) & 1        0x00421CC0  (flags >> 1) & 1
//   0x00421CD0  mode (zero-extended)    0x00421CE0  flags & 1
//   0x00421CF0  (flags >> 2) & 1
//
// Bits 1..6 of the flag dword are the ones the front-end layout builder
// (0x00420870, src/app/fun_00420870.cpp) tests one at a time while it
// composes the screen, and the byte at +0x13D is the mode it stores with them,
// so the record is the screen state the option screen publishes.
//
// No C++ declaration names EAX, so the seven leaves are compiled in the
// native-LTCG cluster build_support/layout/ltcg/ui_state_accessors.json, whose
// array-walking synthetic caller makes the register allocator hand each
// accessor its record in EAX.  The bodies themselves are ordinary C++.

struct UiState {
    unsigned char unknown_000[0x13D];
    unsigned char mode;                     // +0x13D
    unsigned char unknown_13e[0x12];
    unsigned int flags;                     // +0x150
};

__declspec(noinline) int UiState_00421c90_Flag6(UiState* state);
__declspec(noinline) int UiState_00421c90_Flag5(UiState* state);
__declspec(noinline) int UiState_00421c90_Flag3(UiState* state);
__declspec(noinline) int UiState_00421c90_Flag1(UiState* state);
__declspec(noinline) unsigned int UiState_00421c90_Mode(UiState* state);
__declspec(noinline) int UiState_00421c90_Flag0(UiState* state);
__declspec(noinline) int UiState_00421c90_Flag2(UiState* state);

#pragma code_seg(".text$01f6")
int UiState_00421c90_Flag6(UiState* state) {
    return (state->flags >> 6) & 1;
}
#pragma code_seg()

#pragma code_seg(".text$03f5")
int UiState_00421c90_Flag5(UiState* state) {
    return (state->flags >> 5) & 1;
}
#pragma code_seg()

#pragma code_seg(".text$05f3")
int UiState_00421c90_Flag3(UiState* state) {
    return (state->flags >> 3) & 1;
}
#pragma code_seg()

#pragma code_seg(".text$07f1")
int UiState_00421c90_Flag1(UiState* state) {
    return (state->flags >> 1) & 1;
}
#pragma code_seg()

#pragma code_seg(".text$09m0")
unsigned int UiState_00421c90_Mode(UiState* state) {
    return state->mode;
}
#pragma code_seg()

#pragma code_seg(".text$11f0")
int UiState_00421c90_Flag0(UiState* state) {
    return state->flags & 1;
}
#pragma code_seg()

#pragma code_seg(".text$13f2")
int UiState_00421c90_Flag2(UiState* state) {
    return (state->flags >> 2) & 1;
}
#pragma code_seg()
