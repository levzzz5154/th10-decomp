#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F800..0x0041F81D: ?SetPolar@Vector2@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_SetPolar_Vector2_0041f800() {
    __asm {
    L_0041f800:
        push ecx
    L_0041f801:
        mov dword ptr [esp],ecx
    L_0041f804:
        mov eax,dword ptr [esp]
    L_0041f807:
        fld dword ptr [esp+8]
    L_0041f80b:
        fsincos
    L_0041f80d:
        fmul dword ptr [esp+0Ch]
    L_0041f811:
        fstp dword ptr [eax]
    L_0041f813:
        fmul dword ptr [esp+0Ch]
    L_0041f817:
        fstp dword ptr [eax+4]
    L_0041f81a:
        pop ecx
    L_0041f81b:
        ret 8
    }
}

// 0x004458B0..0x004458CD: Vector2_SetPolar
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Vector2_SetPolar_004458b0() {
    __asm {
    L_004458b0:
        push ecx
    L_004458b1:
        mov dword ptr [esp],ecx
    L_004458b4:
        mov eax,dword ptr [esp]
    L_004458b7:
        fld dword ptr [esp+8]
    L_004458bb:
        fsincos
    L_004458bd:
        fmul dword ptr [esp+0Ch]
    L_004458c1:
        fstp dword ptr [eax]
    L_004458c3:
        fmul dword ptr [esp+0Ch]
    L_004458c7:
        fstp dword ptr [eax+4]
    L_004458ca:
        pop ecx
    L_004458cb:
        ret 8
    }
}
