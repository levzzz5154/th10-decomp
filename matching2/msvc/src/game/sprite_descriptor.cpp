// BLOCKED (D3202): closest_byte_count=162/162; first_diff=none (retail
// assembly baseline only; no readable candidate retained).
// residual_class=hidden ESI descriptor live-in, private AnimationManager
// lookup ABI, four ordered __ftol2/x87 conversions, and descriptor field
// layout/return cleanup. Live Ghidra topology: callers 0x00422B5D,
// 0x004232A1, 0x00423441; callees 0x004491C0 and 0x00463B2C.
// variants_tested=Ghidra complete decompilation, xrefs/callers/callees,
// disassembly, variable/storage audit, legacy descriptor model, and all three
// caller clusters; no compiler-readable candidate was byte-measured or
// retained.
// next_lever=schema2 native-LTCG cluster containing the three real callers,
// FUN_004491C0, and __ftol2 at 0x00463B2C, with ESI descriptor ownership,
// x87 conversion order, and the 0x2C-byte output layout fixed before cutover.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424480..0x00424521: FUN_00424480
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424480_00424480() {
    __asm {
    L_00424480:
        push ecx
    L_00424481:
        mov eax,dword ptr [esp+8]
    L_00424485:
        mov edx,dword ptr [data_00491c10]
    L_0042448b:
        push ebx
    L_0042448c:
        push ebp
    L_0042448d:
        push edi
    L_0042448e:
        push eax
    L_0042448f:
        call asm_AnimationManager_Find_004491c0
    L_00424494:
        mov ebx,eax
    L_00424496:
        mov edi,dword ptr [ebx+394h]
    L_0042449c:
        fld dword ptr [edi+30h]
    L_0042449f:
        call asm_FUN_00463b2c_00463b2c
    L_004244a4:
        fld dword ptr [edi+34h]
    L_004244a7:
        mov ebp,eax
    L_004244a9:
        call asm_FUN_00463b2c_00463b2c
    L_004244ae:
        fld dword ptr [edi+0Ch]
    L_004244b1:
        mov dword ptr [esp+0Ch],eax
    L_004244b5:
        call asm_FUN_00463b2c_00463b2c
    L_004244ba:
        fld dword ptr [edi+8]
    L_004244bd:
        mov dword ptr [esp+14h],eax
    L_004244c1:
        call asm_FUN_00463b2c_00463b2c
    L_004244c6:
        mov ecx,dword ptr [esi+4]
    L_004244c9:
        test ecx,ecx
    L_004244cb:
        jl short L_004244d7
    L_004244cd:
        pop edi
    L_004244ce:
        pop ebp
    L_004244cf:
        or eax,0FFFFFFFFh
    L_004244d2:
        pop ebx
    L_004244d3:
        pop ecx
    L_004244d4:
        ret 14h
    L_004244d7:
        mov ecx,dword ptr [ebx+308h]
    L_004244dd:
        mov edx,dword ptr [ecx]
    L_004244df:
        mov ecx,dword ptr [esp+18h]
    L_004244e3:
        mov dword ptr [esi+4],edx
    L_004244e6:
        mov edx,dword ptr [esp+1Ch]
    L_004244ea:
        mov dword ptr [esi+8],ecx
    L_004244ed:
        mov ecx,dword ptr [esp+20h]
    L_004244f1:
        mov dword ptr [esi+18h],eax
    L_004244f4:
        mov eax,dword ptr [esp+14h]
    L_004244f8:
        pop edi
    L_004244f9:
        mov dword ptr [esi+0Ch],edx
    L_004244fc:
        mov edx,dword ptr [esp+20h]
    L_00424500:
        mov dword ptr [esi+10h],ecx
    L_00424503:
        mov ecx,dword ptr [esp+8]
    L_00424507:
        mov dword ptr [esi+24h],ebp
    L_0042450a:
        pop ebp
    L_0042450b:
        mov dword ptr [esi+1Ch],eax
    L_0042450e:
        mov dword ptr [esi+14h],edx
    L_00424511:
        mov dword ptr [esi+20h],ecx
    L_00424514:
        mov dword ptr [esi+28h],0
    L_0042451b:
        xor eax,eax
    L_0042451d:
        pop ebx
    L_0042451e:
        pop ecx
    L_0042451f:
        ret 14h
    }
}
