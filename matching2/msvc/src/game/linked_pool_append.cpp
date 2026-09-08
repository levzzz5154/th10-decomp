#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AA50..0x0042AADA: LinkedPool_AllocateAndAppendRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LinkedPool_AllocateAndAppendRetail_0042aa50() {
    __asm {
    L_0042aa50:
        push 6284h
    L_0042aa55:
        call asm_operator_new_00452493
    L_0042aa5a:
        mov edx,eax
    L_0042aa5c:
        add esp,4
    L_0042aa5f:
        test edx,edx
    L_0042aa61:
        je short L_0042aa9e
    L_0042aa63:
        push edi
    L_0042aa64:
        xor eax,eax
    L_0042aa66:
        mov ecx,18A1h
    L_0042aa6b:
        mov edi,edx
    L_0042aa6d:
        rep stosd
    L_0042aa6f:
        mov dword ptr [edx+5460h],edx
    L_0042aa75:
        lea eax,[edx+5464h]
    L_0042aa7b:
        mov dword ptr [edx+6274h],eax
    L_0042aa81:
        mov dword ptr [edx+6278h],edx
    L_0042aa87:
        mov dword ptr [edx+627Ch],0
    L_0042aa91:
        mov dword ptr [edx+6280h],0
    L_0042aa9b:
        pop edi
    L_0042aa9c:
        jmp short L_0042aaa0
    L_0042aa9e:
        xor edx,edx
    L_0042aaa0:
        lea eax,[edx+6278h]
    L_0042aaa6:
        mov edx,dword ptr [esp+4]
    L_0042aaaa:
        lea ecx,[esi+esi*2+0Fh]
    L_0042aaae:
        lea ecx,[edx+ecx*4]
    L_0042aab1:
        mov edx,dword ptr [ecx+4]
    L_0042aab4:
        test edx,edx
    L_0042aab6:
        je short L_0042aac2
    L_0042aab8:
        mov ecx,dword ptr [ecx+4]
    L_0042aabb:
        mov edx,dword ptr [ecx+4]
    L_0042aabe:
        test edx,edx
    L_0042aac0:
        jne short L_0042aab8
    L_0042aac2:
        mov edx,dword ptr [ecx+4]
    L_0042aac5:
        test edx,edx
    L_0042aac7:
        je short L_0042aad2
    L_0042aac9:
        mov dword ptr [eax+4],edx
    L_0042aacc:
        mov edx,dword ptr [ecx+4]
    L_0042aacf:
        mov dword ptr [edx+8],eax
    L_0042aad2:
        mov dword ptr [ecx+4],eax
    L_0042aad5:
        mov dword ptr [eax+8],ecx
    L_0042aad8:
        ret 4
    }
}
