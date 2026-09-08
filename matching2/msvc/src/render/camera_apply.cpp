#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004215A0..0x004216E9: FUN_004215a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004215a0_004215a0() {
    __asm {
    L_004215a0:
        sub esp,28h
    L_004215a3:
        push ebx
    L_004215a4:
        push ebp
    L_004215a5:
        push esi
    L_004215a6:
        mov esi,dword ptr [data_00491c10]
    L_004215ac:
        test esi,esi
    L_004215ae:
        je short L_004215b5
    L_004215b0:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004215b5:
        fld dword ptr [edi+0Ch]
    L_004215b8:
        lea esi,[edi+18h]
    L_004215bb:
        fadd dword ptr [edi]
    L_004215bd:
        push esi
    L_004215be:
        lea eax,[esp+20h]
    L_004215c2:
        push eax
    L_004215c3:
        fstp dword ptr [esp+24h]
    L_004215c7:
        lea ecx,[esp+30h]
    L_004215cb:
        fld dword ptr [edi+10h]
    L_004215ce:
        push ecx
    L_004215cf:
        fadd dword ptr [edi+4]
    L_004215d2:
        lea ebx,[edi+4Ch]
    L_004215d5:
        push ebx
    L_004215d6:
        fstp dword ptr [esp+30h]
    L_004215da:
        fld dword ptr [edi+14h]
    L_004215dd:
        fadd dword ptr [edi+8]
    L_004215e0:
        fstp dword ptr [esp+34h]
    L_004215e4:
        fld dword ptr [edi+3Ch]
    L_004215e7:
        fadd dword ptr [edi]
    L_004215e9:
        fstp dword ptr [esp+38h]
    L_004215ed:
        fld dword ptr [edi+40h]
    L_004215f0:
        fadd dword ptr [edi+4]
    L_004215f3:
        fstp dword ptr [esp+3Ch]
    L_004215f7:
        fld dword ptr [edi+44h]
    L_004215fa:
        fadd dword ptr [edi+8]
    L_004215fd:
        fstp dword ptr [esp+40h]
    L_00421601:
        call asm_D3DXMatrixLookAtLH_00452194
    L_00421606:
        mov edx,dword ptr [edi+0D4h]
    L_0042160c:
        fild dword ptr [edi+0D4h]
    L_00421612:
        test edx,edx
    L_00421614:
        push 44E10000h
    L_00421619:
        lea ebp,[edi+8Ch]
    L_0042161f:
        push 41F00000h
    L_00421624:
        jge short L_0042162c
    L_00421626:
        fadd dword ptr [data_00470b98]
    L_0042162c:
        mov eax,dword ptr [edi+0D8h]
    L_00421632:
        fild dword ptr [edi+0D8h]
    L_00421638:
        test eax,eax
    L_0042163a:
        jge short L_00421642
    L_0042163c:
        fadd dword ptr [data_00470b98]
    L_00421642:
        fdivp st(1),st
    L_00421644:
        push ecx
    L_00421645:
        mov ecx,dword ptr [edi+48h]
    L_00421648:
        fstp dword ptr [esp]
    L_0042164b:
        push ecx
    L_0042164c:
        push ebp
    L_0042164d:
        call asm_D3DXMatrixPerspectiveFovLH_0045219a
    L_00421652:
        mov eax,dword ptr [data_00491c30]
    L_00421657:
        mov edx,dword ptr [eax]
    L_00421659:
        push ebx
    L_0042165a:
        push 2
    L_0042165c:
        push eax
    L_0042165d:
        call dword ptr [edx+0B0h]
    L_00421663:
        mov eax,dword ptr [data_00491c30]
    L_00421668:
        mov ecx,dword ptr [eax]
    L_0042166a:
        push ebp
    L_0042166b:
        push 3
    L_0042166d:
        push eax
    L_0042166e:
        call dword ptr [ecx+0B0h]
    L_00421674:
        fld dword ptr [esi+8]
    L_00421677:
        fmul dword ptr [edi+10h]
    L_0042167a:
        lea eax,[edi+30h]
    L_0042167d:
        fld dword ptr [esi+4]
    L_00421680:
        mov edx,eax
    L_00421682:
        fmul dword ptr [edi+14h]
    L_00421685:
        push eax
    L_00421686:
        push eax
    L_00421687:
        fsubp st(1),st
    L_00421689:
        fstp dword ptr [esp+18h]
    L_0042168d:
        mov ecx,dword ptr [esp+18h]
    L_00421691:
        fld dword ptr [esi]
    L_00421693:
        fmul dword ptr [edi+14h]
    L_00421696:
        fld dword ptr [esi+8]
    L_00421699:
        fmul dword ptr [edi+0Ch]
    L_0042169c:
        fsubp st(1),st
    L_0042169e:
        fstp dword ptr [esp+1Ch]
    L_004216a2:
        fld dword ptr [esi+4]
    L_004216a5:
        fmul dword ptr [edi+0Ch]
    L_004216a8:
        fld dword ptr [esi]
    L_004216aa:
        fmul dword ptr [edi+10h]
    L_004216ad:
        mov dword ptr [edx],ecx
    L_004216af:
        mov ecx,dword ptr [esp+1Ch]
    L_004216b3:
        mov dword ptr [edx+4],ecx
    L_004216b6:
        fsubp st(1),st
    L_004216b8:
        fstp dword ptr [esp+20h]
    L_004216bc:
        mov ecx,dword ptr [esp+20h]
    L_004216c0:
        mov dword ptr [edx+8],ecx
    L_004216c3:
        call asm_D3DXVec3Normalize_0045217c
    L_004216c8:
        mov eax,dword ptr [data_00491c10]
    L_004216cd:
        test eax,eax
    L_004216cf:
        pop esi
    L_004216d0:
        pop ebp
    L_004216d1:
        pop ebx
    L_004216d2:
        je short L_004216e6
    L_004216d4:
        mov edx,dword ptr [edi+0E8h]
    L_004216da:
        mov dword ptr [eax+5Ch],edx
    L_004216dd:
        mov ecx,dword ptr [edi+0ECh]
    L_004216e3:
        mov dword ptr [eax+60h],ecx
    L_004216e6:
        add esp,28h
    L_004216e9:
        ret
    }
}
