#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3507): closest_byte_count=0/341; first_diff=extent (readable typed Win32 candidate emitted 308 bytes vs retail 341);
// residual_class=private-EBX HINSTANCE ABI and Win32 import/call scheduling; GameMain passes the instance in EBX and the retail body uses that register directly;
// variants_tested=retail naked baseline (341/341 exact), readable WNDCLASSA/Win32 cdecl candidate (308-byte extent), live Ghidra FUN_00439730 decompile, and GameMain caller inspection;
// next_lever=native-LTCG cluster with GameMain as the real EBX caller, preserving the hidden instance register and exact Win32 import declarations.

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.

// 0x00439730..0x00439884: FUN_00439730
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00439730_00439730() {
    __asm {
    L_00439730:
        sub esp,28h
    L_00439733:
        xor eax,eax
    L_00439735:
        mov dword ptr [esp],eax
    L_00439738:
        mov dword ptr [esp+4],eax
    L_0043973c:
        mov dword ptr [esp+8],eax
    L_00439740:
        mov dword ptr [esp+0Ch],eax
    L_00439744:
        mov dword ptr [esp+10h],eax
    L_00439748:
        mov dword ptr [esp+14h],eax
    L_0043974c:
        mov dword ptr [esp+18h],eax
    L_00439750:
        mov dword ptr [esp+1Ch],eax
    L_00439754:
        push esi
    L_00439755:
        mov dword ptr [esp+24h],eax
    L_00439759:
        push 4
    L_0043975b:
        mov dword ptr [esp+2Ch],eax
    L_0043975f:
        call dword ptr [data_00466010]
    L_00439765:
        push 7F00h
    L_0043976a:
        push 0
    L_0043976c:
        mov dword ptr [esp+28h],eax
    L_00439770:
        call dword ptr [data_00466260]
    L_00439776:
        lea ecx,[esp+4]
    L_0043977a:
        push ecx
    L_0043977b:
        mov dword ptr [esp+20h],eax
    L_0043977f:
        mov dword ptr [esp+18h],ebx
    L_00439783:
        mov dword ptr [esp+0Ch],4390E0h
    L_0043978b:
        mov dword ptr [data_004924fc],1
    L_00439795:
        mov dword ptr [data_00492500],0
    L_0043979f:
        mov dword ptr [esp+2Ch],46F698h
    L_004397a7:
        call dword ptr [data_004661f8]
    L_004397ad:
        mov al,byte ptr [data_00491d65]
    L_004397b2:
        test al,al
    L_004397b4:
        jne short L_004397e4
    L_004397b6:
        push 0
    L_004397b8:
        push ebx
    L_004397b9:
        push 0
    L_004397bb:
        push 0
    L_004397bd:
        push 1E0h
    L_004397c2:
        push 280h
    L_004397c7:
        push 0
    L_004397c9:
        push 0
    L_004397cb:
        push 0CF0000h
    L_004397d0:
        push 46F66Ch
    L_004397d5:
        push 46F698h
    L_004397da:
        push 0
    L_004397dc:
        call dword ptr [data_00466238]
    L_004397e2:
        jmp short L_00439834
    L_004397e4:
        mov esi,dword ptr [data_0046625c]
    L_004397ea:
        push ebp
    L_004397eb:
        push edi
    L_004397ec:
        push 7
    L_004397ee:
        call esi
    L_004397f0:
        push 8
    L_004397f2:
        lea edi,[eax+eax+280h]
    L_004397f9:
        call esi
    L_004397fb:
        push 4
    L_004397fd:
        mov ebp,eax
    L_004397ff:
        call esi
    L_00439801:
        push 0
    L_00439803:
        push ebx
    L_00439804:
        push 0
    L_00439806:
        push 0
    L_00439808:
        lea eax,[eax+ebp*2+1E0h]
    L_0043980f:
        push eax
    L_00439810:
        push edi
    L_00439811:
        push 80000000h
    L_00439816:
        push 80000000h
    L_0043981b:
        push 100A0000h
    L_00439820:
        push 46F66Ch
    L_00439825:
        push 46F698h
    L_0043982a:
        push 0
    L_0043982c:
        call dword ptr [data_00466238]
    L_00439832:
        pop edi
    L_00439833:
        pop ebp
    L_00439834:
        test eax,eax
    L_00439836:
        mov dword ptr [data_004924f0],eax
    L_0043983b:
        mov dword ptr [data_00491c70],eax
    L_00439840:
        jne short L_0043984c
    L_00439842:
        mov eax,1
    L_00439847:
        pop esi
    L_00439848:
        add esp,28h
    L_0043984b:
        ret
    L_0043984c:
        mov esi,dword ptr [data_00466228]
    L_00439852:
        push 0
    L_00439854:
        push 0F020h
    L_00439859:
        push 112h
    L_0043985e:
        push eax
    L_0043985f:
        call esi
    L_00439861:
        push 10h
    L_00439863:
        call dword ptr [data_004660ac]
    L_00439869:
        mov edx,dword ptr [data_004924f0]
    L_0043986f:
        push 0
    L_00439871:
        push 0F120h
    L_00439876:
        push 112h
    L_0043987b:
        push edx
    L_0043987c:
        call esi
    L_0043987e:
        xor eax,eax
    L_00439880:
        pop esi
    L_00439881:
        add esp,28h
    L_00439884:
        ret
    }
}
