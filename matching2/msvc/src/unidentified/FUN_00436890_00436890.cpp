#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436890..0x004368F2: FUN_00436890
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3901): closest_byte_count=0/99; first_diff=0x00436890;
// residual_class=compiler-generated SEH registration/handler frame, placement
// pointer ABI, and LegacyString allocator-cookie layout. variants_tested=
// exact retail assembly probe (99/99), corrected raw-layout readable candidate
// (64-byte extent), and reduced raw-layout candidate (63-byte extent); all
// nonexact output was restored. next_lever=derive the original constructor/
// exception model and caller-visible third stack argument before retrying the
// plain readable path.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436890_00436890() {
    __asm {
    L_00436890:
        mov eax,dword ptr fs:[0]
    L_00436896:
        push 0FFFFFFFFh
    L_00436898:
        push 46558Bh
    L_0043689d:
        push eax
    L_0043689e:
        mov dword ptr fs:[0],esp
    L_004368a5:
        push esi
    L_004368a6:
        mov esi,dword ptr [esp+14h]
    L_004368aa:
        lea ecx,[esi+0Ch]
    L_004368ad:
        xor eax,eax
    L_004368af:
        mov dword ptr [ecx+18h],0Fh
    L_004368b6:
        mov dword ptr [ecx+14h],eax
    L_004368b9:
        mov byte ptr [ecx+4],al
    L_004368bc:
        mov dword ptr [esp+0Ch],eax
    L_004368c0:
        push 0Dh
    L_004368c2:
        push 46F36Ch
    L_004368c7:
        mov dword ptr [esi],eax
    L_004368c9:
        mov dword ptr [esi+28h],258h
    L_004368d0:
        mov dword ptr [esi+8],10h
    L_004368d7:
        mov dword ptr [esi+4],eax
    L_004368da:
        call asm_AssignRange_LegacyString_00438420
    L_004368df:
        mov ecx,dword ptr [esp+4]
    L_004368e3:
        mov eax,esi
    L_004368e5:
        mov dword ptr fs:[0],ecx
    L_004368ec:
        pop esi
    L_004368ed:
        add esp,0Ch
    L_004368f0:
        ret 4
    }
}
