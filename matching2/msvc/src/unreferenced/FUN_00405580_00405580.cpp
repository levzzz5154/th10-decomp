// 0x00405580. Read the dword at +0x3788 of the game-state object handed in EAX.
//
//   L_00405580: mov eax,dword ptr [eax+3788h]   ; 8b 80 88 37 00 00
//               ret                             ; c3
//
// The object is the one reachable through the global pointer at 0x004776F4:
// src/game/player.cpp reads the same +0x3788 dword (compared with 0x5D, 0x60
// and 0x6D) next to the byte flags at +0x378C, which is where the accessor's
// caller loads it from. The body is compiled in the native LTCG cluster of
// layout/ltcg/game_state_field3788_getter.json, whose synthetic caller reads
// the singleton pointer from that global so MSVC keeps it in EAX.

struct GameState {
    unsigned char unknown_0000[0x3788];
    int field_3788;   // +0x3788
};

__declspec(noinline) int GameState_GetField3788(GameState* state);

#pragma code_seg(".text$01get")
int GameState_GetField3788(GameState* state) {
    return state->field_3788;
}
#pragma code_seg()
