#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0043DC90..0x0043DD0A: ?AnimationManager_QueueResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_QueueResource_0043dc90() {
    __asm {
    L_0043dc90:
        push ebx
    L_0043dc91:
        movsx ebx,word ptr [edi*8+4749CEh]
    L_0043dc99:
        push ebp
    L_0043dc9a:
        mov ebp,dword ptr [esp+0Ch]
    L_0043dc9e:
        push esi
    L_0043dc9f:
        xor eax,eax
    L_0043dca1:
        lea edx,[ecx+620h]
    L_0043dca7:
        mov esi,dword ptr [edx]
    L_0043dca9:
        test esi,esi
    L_0043dcab:
        jl short L_0043dcdf
    L_0043dcad:
        cmp esi,edi
    L_0043dcaf:
        je short L_0043dcc0
    L_0043dcb1:
        inc eax
    L_0043dcb2:
        add edx,4
    L_0043dcb5:
        cmp eax,0Ch
    L_0043dcb8:
        jl short L_0043dca7
    L_0043dcba:
        pop esi
    L_0043dcbb:
        pop ebp
    L_0043dcbc:
        pop ebx
    L_0043dcbd:
        ret 4
    L_0043dcc0:
        mov edx,dword ptr [ecx+eax*4+650h]
    L_0043dcc7:
        cmp edx,80h
    L_0043dccd:
        jge short L_0043dd05
    L_0043dccf:
        mov esi,eax
    L_0043dcd1:
        shl esi,7
    L_0043dcd4:
        add esi,edx
    L_0043dcd6:
        mov dword ptr [ecx+esi*4+680h],ebp
    L_0043dcdd:
        jmp short L_0043dcfe
    L_0043dcdf:
        cmp eax,0Ch
    L_0043dce2:
        jge short L_0043dd05
    L_0043dce4:
        mov edx,eax
    L_0043dce6:
        mov dword ptr [ecx+eax*4+620h],edi
    L_0043dced:
        shl edx,9
    L_0043dcf0:
        mov dword ptr [ecx+edi*4+408h],ebx
    L_0043dcf7:
        mov dword ptr [edx+ecx+680h],ebp
    L_0043dcfe:
        inc dword ptr [ecx+eax*4+650h]
    L_0043dd05:
        pop esi
    L_0043dd06:
        pop ebp
    L_0043dd07:
        pop ebx
    L_0043dd08:
        ret 4
    }
}
