#define g_sprt_ctrl stage_input_g_sprt_ctrl
#define g_front stage_input_g_front
#define data_00474c40 stage_input_data_00474c40
#define g_ascii_manager stage_input_data_004776e0
#define g_enemy_ctrl stage_input_g_enemy_ctrl
#define g_player stage_input_data_00477834
#define data_00477838 stage_input_data_00477838
#define data_0047783c stage_input_data_0047783c
#define data_00476f78 stage_input_data_00476f78
#define data_00491fc4 stage_input_data_00491fc4
#define data_00491fb8 stage_input_data_00491fb8
#define data_00492590 stage_input_data_00492590
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
// build_support/layout/ltcg/set_input_mode.json reproduces. The body was carved out of
// src/game/eclview/score.cpp, where the same offsets are used by other state code.

struct InputState {
    unsigned char unknown_0000[0x390];
    int           mode_390;              // +0x390, selected input mode
    unsigned char unknown_0394[0x3CC - 0x394];
    unsigned int  flags_3CC;             // +0x3CC, bit 0x1000 forces mode 2
};

__declspec(noinline) void SetInputMode(InputState* state, int mode);

#pragma code_seg(".text$0040ac90_fn")
void SetInputMode(InputState* state, int mode) {
    if ((state->flags_3CC & 0x1000) == 0) {
        state->mode_390 = mode;
    } else {
        state->mode_390 = 2;
    }
}
#pragma code_seg()
#undef g_sprt_ctrl
#undef g_front
#undef data_00474c40
#undef g_ascii_manager
#undef g_enemy_ctrl
#undef g_player
#undef data_00477838
#undef data_0047783c
#undef data_00476f78
#undef data_00491fc4
#undef data_00491fb8
#undef data_00492590
