#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00429A70..0x00429B25: FUN_00429a70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00429a70_00429a70() {
    __asm {
    L_00429a70:
        mov eax,dword ptr [data_00477810]
    L_00429a75:
        sub esp,10h
    L_00429a78:
        test eax,eax
    L_00429a7a:
        je asm_target_00429b1d
    L_00429a80:
        mov eax,dword ptr [edx+10h]
    L_00429a83:
        test eax,eax
    L_00429a85:
        je asm_target_00429b1d
    L_00429a8b:
        cmp eax,1
    L_00429a8e:
        jne asm_target_00429b1d
    L_00429a94:
        movzx eax,byte ptr [edx+1C4h]
    L_00429a9b:
        mov dword ptr [esp],eax
    L_00429a9e:
        mov dword ptr [esp+4],43BF8000h
    L_00429aa6:
        mov dword ptr [esp+8],43E10000h
    L_00429aae:
        fild dword ptr [esp]
    L_00429ab1:
        mov dword ptr [esp+0Ch],0
    L_00429ab9:
        fcom dword ptr [data_00470c30]
    L_00429abf:
        fnstsw ax
    L_00429ac1:
        test ah,5
    L_00429ac4:
        jp short L_00429acf
    L_00429ac6:
        fstp st(0)
    L_00429ac8:
        mov ecx,0FF5050FFh
    L_00429acd:
        jmp short L_00429ae6
    L_00429acf:
        fcomp dword ptr [data_00470c2c]
    L_00429ad5:
        fnstsw ax
    L_00429ad7:
        test ah,5
    L_00429ada:
        jp short L_00429ae3
    L_00429adc:
        mov ecx,0FFA0A0FFh
    L_00429ae1:
        jmp short L_00429ae6
    L_00429ae3:
        or ecx,0FFFFFFFFh
    L_00429ae6:
        mov eax,dword ptr [data_004776e0]
    L_00429aeb:
        mov dword ptr [eax+8974h],ecx
    L_00429af1:
        movzx ecx,byte ptr [edx+1C4h]
    L_00429af8:
        push ebx
    L_00429af9:
        push ecx
    L_00429afa:
        push 46E658h
    L_00429aff:
        push eax
    L_00429b00:
        lea ebx,[esp+14h]
    L_00429b04:
        call asm_GameThread_AppendFormatted_00401630
    L_00429b09:
        mov edx,dword ptr [data_004776e0]
    L_00429b0f:
        add esp,0Ch
    L_00429b12:
        mov dword ptr [edx+8974h],0FFFFFFFFh
    L_00429b1c:
        pop ebx
    L_00429b1d:
        mov eax,1
    L_00429b22:
        add esp,10h
    L_00429b25:
        ret
    }
}
