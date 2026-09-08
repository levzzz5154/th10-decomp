#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E8E1..0x0045E97E: __umatherr
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_umatherr_0045e8e1() {
    __asm {
    L_0045e8e1:
        push ebp
    L_0045e8e2:
        mov ebp,esp
    L_0045e8e4:
        sub esp,20h
    L_0045e8e7:
        xor eax,eax
    L_0045e8e9:
        mov ecx,dword ptr [eax*8+473C98h]
    L_0045e8f0:
        cmp ecx,dword ptr [ebp+0Ch]
    L_0045e8f3:
        je short L_0045e959
    L_0045e8f5:
        inc eax
    L_0045e8f6:
        cmp eax,1Dh
    L_0045e8f9:
        jl short L_0045e8e9
    L_0045e8fb:
        xor eax,eax
    L_0045e8fd:
        test eax,eax
    L_0045e8ff:
        mov dword ptr [ebp-1Ch],eax
    L_0045e902:
        je short L_0045e962
    L_0045e904:
        mov eax,dword ptr [ebp+10h]
    L_0045e907:
        mov dword ptr [ebp-18h],eax
    L_0045e90a:
        mov eax,dword ptr [ebp+14h]
    L_0045e90d:
        mov dword ptr [ebp-14h],eax
    L_0045e910:
        mov eax,dword ptr [ebp+18h]
    L_0045e913:
        mov dword ptr [ebp-10h],eax
    L_0045e916:
        mov eax,dword ptr [ebp+1Ch]
    L_0045e919:
        push esi
    L_0045e91a:
        mov esi,dword ptr [ebp+8]
    L_0045e91d:
        mov dword ptr [ebp-0Ch],eax
    L_0045e920:
        mov eax,dword ptr [ebp+20h]
    L_0045e923:
        mov dword ptr [ebp-8],eax
    L_0045e926:
        mov eax,dword ptr [ebp+24h]
    L_0045e929:
        push 0FFFFh
    L_0045e92e:
        push dword ptr [ebp+28h]
    L_0045e931:
        mov dword ptr [ebp-20h],esi
    L_0045e934:
        mov dword ptr [ebp-4],eax
    L_0045e937:
        call asm_ctrlfp_0045ed87
    L_0045e93c:
        lea eax,[ebp-20h]
    L_0045e93f:
        push eax
    L_0045e940:
        call asm_FUN_0045e3a0_0045e3a0
    L_0045e945:
        add esp,0Ch
    L_0045e948:
        test eax,eax
    L_0045e94a:
        jne short L_0045e953
    L_0045e94c:
        push esi
    L_0045e94d:
        call asm_FID_conflict___set_errno_from_matherr_0045e86c
    L_0045e952:
        pop ecx
    L_0045e953:
        fld qword ptr [ebp-8]
    L_0045e956:
        pop esi
    L_0045e957:
        leave
    L_0045e958:
        ret
    L_0045e959:
        mov eax,dword ptr [eax*8+473C9Ch]
    L_0045e960:
        jmp short L_0045e8fd
    L_0045e962:
        push 0FFFFh
    L_0045e967:
        push dword ptr [ebp+28h]
    L_0045e96a:
        call asm_ctrlfp_0045ed87
    L_0045e96f:
        push dword ptr [ebp+8]
    L_0045e972:
        call asm_FID_conflict___set_errno_from_matherr_0045e86c
    L_0045e977:
        fld qword ptr [ebp+20h]
    L_0045e97a:
        add esp,0Ch
    L_0045e97d:
        leave
    L_0045e97e:
        ret
    }
}
