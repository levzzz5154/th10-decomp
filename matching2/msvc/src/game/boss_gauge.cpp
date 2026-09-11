#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428C20..0x00428C9C: FUN_00428c20
// The manager (ECX) owns the 0x98-byte score slots based at +0x3244 and the
// state (EDX) names, through +0x58, the record that selects the live slot. Each
// update rebuilds the gauge position from the slot's two counters scaled to
// playfield units, publishes it as a vector, then folds the running
// displacement back in and reports success.
struct Vector3 {
    float x;
    float y;
    float z;
};

struct BossGaugeSource {          // state->source, at state + 0x58
    char pad_000[4];
    float value;                  // +0x04
    float maximum;                // +0x08
    char pad_00c[0x1C - 0x0C];
    signed char slot;             // +0x1C
};

struct BossGaugeState {
    char pad_000[0x14];
    Vector3 position;             // +0x14
    float offset_x;               // +0x20
    float offset_y;               // +0x24
    char pad_028[0x58 - 0x28];
    BossGaugeSource* source;      // +0x58
};

int __fastcall BossGauge_UpdateRetail(int* manager, BossGaugeState* state) {
    Vector3 position;
    BossGaugeSource* source = state->source;
    int* entry = (int*)((char*)manager + 152 * source->slot + 0x3244);
    Vector3* dst = &state->position;

    position.x = (float)entry[0] * 0.01f;
    position.y = (float)entry[1] * 0.01f;
    position.z = 0.0f;
    *dst = position;
    state->position.x = source->value - state->offset_x + state->position.x;
    state->position.y = state->source->maximum - state->offset_y + state->position.y;
    return 0;
}

// 0x00428E10..0x00428E62: FUN_00428e10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428e10_00428e10() {
    __asm {
    L_00428e10:
        mov edx,dword ptr [ecx]
    L_00428e12:
        mov dword ptr [eax+3CCh],edx
    L_00428e18:
        mov ecx,dword ptr [ecx+4]
    L_00428e1b:
        mov dword ptr [eax+3D0h],ecx
    L_00428e21:
        fild dword ptr [eax+3CCh]
    L_00428e27:
        mov ecx,1
    L_00428e2c:
        fmul dword ptr [data_00470b00]
    L_00428e32:
        fstp dword ptr [eax+3C0h]
    L_00428e38:
        fild dword ptr [eax+3D0h]
    L_00428e3e:
        fmul dword ptr [data_00470b00]
    L_00428e44:
        fstp dword ptr [eax+3C4h]
    L_00428e4a:
        mov dword ptr [eax+332Ch],ecx
    L_00428e50:
        mov dword ptr [eax+33C4h],ecx
    L_00428e56:
        mov dword ptr [eax+345Ch],ecx
    L_00428e5c:
        mov dword ptr [eax+34F4h],ecx
    L_00428e62:
        ret
    }
}
