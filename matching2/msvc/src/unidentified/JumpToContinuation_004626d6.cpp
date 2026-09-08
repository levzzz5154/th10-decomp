#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004626D6..0x00462700: _JumpToContinuation
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_JumpToContinuation_004626d6() {
    __asm {
    L_004626d6:
        push ebp
    L_004626d7:
        mov ebp,esp
    L_004626d9:
        push ecx
    L_004626da:
        push ebx
    L_004626db:
        mov eax,dword ptr [ebp+0Ch]
    L_004626de:
        add eax,0Ch
    L_004626e1:
        mov dword ptr [ebp-4],eax
    L_004626e4:
        mov ebx,dword ptr fs:[0]
    L_004626eb:
        mov eax,dword ptr [ebx]
    L_004626ed:
        mov dword ptr fs:[0],eax
    L_004626f3:
        mov eax,dword ptr [ebp+8]
    L_004626f6:
        mov ebx,dword ptr [ebp+0Ch]
    L_004626f9:
        mov esp,dword ptr [ebx-4]
    L_004626fc:
        mov ebp,dword ptr [ebp-4]
    L_004626ff:
        jmp eax
    }
}
