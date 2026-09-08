#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004588A7..0x00458B1D: FUN_004588a7
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004588a7_004588a7() {
    __asm {
    L_004588a7:
        push ebp
    L_004588a8:
        mov ebp,esp
    L_004588aa:
        sub esp,24h
    L_004588ad:
        mov eax,dword ptr [data_00473660]
    L_004588b2:
        mov ecx,dword ptr [ebp+0Ch]
    L_004588b5:
        push esi
    L_004588b6:
        mov esi,dword ptr [ebp+10h]
    L_004588b9:
        xor eax,ebp
    L_004588bb:
        push edi
    L_004588bc:
        mov edi,dword ptr [ebp+14h]
    L_004588bf:
        mov edx,0A1h
    L_004588c4:
        cmp edi,edx
    L_004588c6:
        mov dword ptr [ebp-4],eax
    L_004588c9:
        mov eax,dword ptr [ebp+8]
    L_004588cc:
        jg asm_target_004589d7
    L_004588d2:
        je asm_target_004589cb
    L_004588d8:
        cmp edi,18h
    L_004588db:
        jg asm_target_00458969
    L_004588e1:
        je short L_00458956
    L_004588e3:
        push 2
    L_004588e5:
        pop edx
    L_004588e6:
        sub edi,edx
    L_004588e8:
        je short L_00458947
    L_004588ea:
        dec edi
    L_004588eb:
        je short L_0045893b
    L_004588ed:
        sub edi,5
    L_004588f0:
        je short L_0045892c
    L_004588f2:
        dec edi
    L_004588f3:
        je short L_00458920
    L_004588f5:
        sub edi,5
    L_004588f8:
        je short L_0045890d
    L_004588fa:
        dec edi
    L_004588fb:
        jne asm_target_00458b10
    L_00458901:
        mov dword ptr [ebp-20h],46AC04h
    L_00458908:
        jmp asm_target_004589a5
    L_0045890d:
        mov dword ptr [ebp-24h],3
    L_00458914:
        mov dword ptr [ebp-20h],46AC04h
    L_0045891b:
        jmp asm_target_00458a60
    L_00458920:
        mov dword ptr [ebp-20h],46ABFCh
    L_00458927:
        jmp asm_target_00458adb
    L_0045892c:
        mov dword ptr [ebp-24h],edx
    L_0045892f:
        mov dword ptr [ebp-20h],46ABFCh
    L_00458936:
        jmp asm_target_00458a60
    L_0045893b:
        mov dword ptr [ebp-20h],46F7C8h
    L_00458942:
        jmp asm_target_00458adb
    L_00458947:
        mov dword ptr [ebp-24h],edx
    L_0045894a:
        mov dword ptr [ebp-20h],46F7C8h
    L_00458951:
        jmp asm_target_00458a60
    L_00458956:
        mov dword ptr [ebp-24h],3
    L_0045895d:
        mov dword ptr [ebp-20h],46ABF8h
    L_00458964:
        jmp asm_target_00458a60
    L_00458969:
        sub edi,19h
    L_0045896c:
        je short L_0045899e
    L_0045896e:
        dec edi
    L_0045896f:
        je short L_00458997
    L_00458971:
        dec edi
    L_00458972:
        je short L_0045898e
    L_00458974:
        dec edi
    L_00458975:
        je asm_target_00458ab5
    L_0045897b:
        dec edi
    L_0045897c:
        jne asm_target_00458b10
    L_00458982:
        mov dword ptr [ebp-20h],46ABF8h
    L_00458989:
        jmp asm_target_00458ad7
    L_0045898e:
        mov dword ptr [ebp-24h],2
    L_00458995:
        jmp short L_0045895d
    L_00458997:
        fld1
    L_00458999:
        jmp asm_target_00458b0e
    L_0045899e:
        mov dword ptr [ebp-20h],46ABF8h
    L_004589a5:
        fld qword ptr [eax]
    L_004589a7:
        lea eax,[ebp-24h]
    L_004589aa:
        fstp qword ptr [ebp-1Ch]
    L_004589ad:
        push eax
    L_004589ae:
        fld qword ptr [ecx]
    L_004589b0:
        mov dword ptr [ebp-24h],4
    L_004589b7:
        fstp qword ptr [ebp-14h]
    L_004589ba:
        fld qword ptr [esi]
    L_004589bc:
        fstp qword ptr [ebp-0Ch]
    L_004589bf:
        call dword ptr [data_00473658]
    L_004589c5:
        pop ecx
    L_004589c6:
        jmp asm_target_00458b0b
    L_004589cb:
        mov dword ptr [ebp-24h],3
    L_004589d2:
        jmp asm_target_00458a59
    L_004589d7:
        mov edx,3EAh
    L_004589dc:
        cmp edi,edx
    L_004589de:
        jg asm_target_00458a98
    L_004589e4:
        je asm_target_00458a8f
    L_004589ea:
        sub edi,0A2h
    L_004589f0:
        je short L_00458a52
    L_004589f2:
        sub edi,4
    L_004589f5:
        je short L_00458a42
    L_004589f7:
        sub edi,4
    L_004589fa:
        je short L_00458a32
    L_004589fc:
        dec edi
    L_004589fd:
        je short L_00458a26
    L_004589ff:
        sub edi,33Dh
    L_00458a05:
        je short L_00458a1a
    L_00458a07:
        dec edi
    L_00458a08:
        jne asm_target_00458b10
    L_00458a0e:
        mov dword ptr [ebp-20h],46ABFCh
    L_00458a15:
        jmp asm_target_00458ad7
    L_00458a1a:
        mov dword ptr [ebp-20h],46F7C8h
    L_00458a21:
        jmp asm_target_00458ad7
    L_00458a26:
        mov dword ptr [ebp-20h],46ABF0h
    L_00458a2d:
        jmp asm_target_00458adb
    L_00458a32:
        mov dword ptr [ebp-24h],2
    L_00458a39:
        mov dword ptr [ebp-20h],46ABF0h
    L_00458a40:
        jmp short L_00458a60
    L_00458a42:
        mov dword ptr [ebp-24h],3
    L_00458a49:
        mov dword ptr [ebp-20h],46ABE8h
    L_00458a50:
        jmp short L_00458a60
    L_00458a52:
        mov dword ptr [ebp-24h],4
    L_00458a59:
        mov dword ptr [ebp-20h],46ABE0h
    L_00458a60:
        fld qword ptr [eax]
    L_00458a62:
        lea eax,[ebp-24h]
    L_00458a65:
        fstp qword ptr [ebp-1Ch]
    L_00458a68:
        push eax
    L_00458a69:
        fld qword ptr [ecx]
    L_00458a6b:
        fstp qword ptr [ebp-14h]
    L_00458a6e:
        fld qword ptr [esi]
    L_00458a70:
        fstp qword ptr [ebp-0Ch]
    L_00458a73:
        call dword ptr [data_00473658]
    L_00458a79:
        test eax,eax
    L_00458a7b:
        pop ecx
    L_00458a7c:
        jne asm_target_00458b0b
    L_00458a82:
        call asm_FUN_00456af2_00456af2
    L_00458a87:
        mov dword ptr [eax],22h
    L_00458a8d:
        jmp short L_00458b0b
    L_00458a8f:
        mov dword ptr [ebp-20h],46AC04h
    L_00458a96:
        jmp short L_00458ad7
    L_00458a98:
        sub edi,3EBh
    L_00458a9e:
        je short L_00458ad0
    L_00458aa0:
        dec edi
    L_00458aa1:
        je short L_00458ac7
    L_00458aa3:
        dec edi
    L_00458aa4:
        je short L_00458abe
    L_00458aa6:
        dec edi
    L_00458aa7:
        je short L_00458ab5
    L_00458aa9:
        dec edi
    L_00458aaa:
        jne short L_00458b10
    L_00458aac:
        mov dword ptr [ebp-20h],46ABD8h
    L_00458ab3:
        jmp short L_00458ad7
    L_00458ab5:
        mov dword ptr [ebp-20h],46ABF8h
    L_00458abc:
        jmp short L_00458adb
    L_00458abe:
        mov dword ptr [ebp-20h],46ABD0h
    L_00458ac5:
        jmp short L_00458ad7
    L_00458ac7:
        mov dword ptr [ebp-20h],46ABC8h
    L_00458ace:
        jmp short L_00458ad7
    L_00458ad0:
        mov dword ptr [ebp-20h],46ABC0h
    L_00458ad7:
        fld qword ptr [eax]
    L_00458ad9:
        fstp qword ptr [esi]
    L_00458adb:
        fld qword ptr [eax]
    L_00458add:
        lea eax,[ebp-24h]
    L_00458ae0:
        fstp qword ptr [ebp-1Ch]
    L_00458ae3:
        push eax
    L_00458ae4:
        fld qword ptr [ecx]
    L_00458ae6:
        mov dword ptr [ebp-24h],1
    L_00458aed:
        fstp qword ptr [ebp-14h]
    L_00458af0:
        fld qword ptr [esi]
    L_00458af2:
        fstp qword ptr [ebp-0Ch]
    L_00458af5:
        call dword ptr [data_00473658]
    L_00458afb:
        test eax,eax
    L_00458afd:
        pop ecx
    L_00458afe:
        jne short L_00458b0b
    L_00458b00:
        call asm_FUN_00456af2_00456af2
    L_00458b05:
        mov dword ptr [eax],21h
    L_00458b0b:
        fld qword ptr [ebp-0Ch]
    L_00458b0e:
        fstp qword ptr [esi]
    L_00458b10:
        mov ecx,dword ptr [ebp-4]
    L_00458b13:
        pop edi
    L_00458b14:
        xor ecx,ebp
    L_00458b16:
        pop esi
    L_00458b17:
        call asm_security_check_cookie_00458ea5
    L_00458b1c:
        leave
    L_00458b1d:
        ret
    }
}
