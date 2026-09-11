// 0x0040AC90. Publish the requested input mode on a state object, unless the
// object's +0x3CC flag word has bit 0x1000 set, in which case the mode is
// forced to 2. Retail passes the object in EAX and the mode on the stack, and
// the callee pops it:
//
//   L_0040ac90: mov  ecx,[eax+3CCh]        ; 8b 88 cc 03 00 00
//               test ch,10h                ; f6 c5 10
//               jne  L_0040aca8            ; 75 0d
//               mov  ecx,[esp+4]           ; 8b 4c 24 04
//               mov  [eax+390h],ecx        ; 89 88 90 03 00 00
//               ret  4                     ; c2 04 00
//   L_0040aca8: mov  dword ptr [eax+390h],2
//               ret  4
//
// Every retail caller loads the object from a fixed global (0x00491C28) into
// EAX and pushes a literal mode, which is the shape the synthetic caller in
// layout/ltcg/set_input_mode.json reproduces. The body was carved out of
// src/game/score.cpp, where the same offsets are used by other state code.

struct InputState {
    unsigned char unknown_0000[0x390];
    int           mode_390;              // +0x390, selected input mode
    unsigned char unknown_0394[0x3CC - 0x394];
    unsigned int  flags_3CC;             // +0x3CC, bit 0x1000 forces mode 2
};

__declspec(noinline) void SetInputMode(InputState* state, int mode);

#pragma code_seg(".text$01setmode")
void SetInputMode(InputState* state, int mode) {
    if ((state->flags_3CC & 0x1000) == 0) {
        state->mode_390 = mode;
    } else {
        state->mode_390 = 2;
    }
}
#pragma code_seg()
