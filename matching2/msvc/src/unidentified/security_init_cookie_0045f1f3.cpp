#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F1F3..0x0045F258: ___security_init_cookie
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_security_init_cookie_0045f1f3() {
    __asm {
    L_0045f1f3:
        push ebp
    L_0045f1f4:
        mov ebp,esp
    L_0045f1f6:
        sub esp,10h
    L_0045f1f9:
        mov eax,dword ptr [data_00473660]
    L_0045f1fe:
        test eax,eax
    L_0045f200:
        je short L_0045f209
    L_0045f202:
        cmp eax,0BB40E64Eh
    L_0045f207:
        jne short L_0045f257
    L_0045f209:
        push esi
    L_0045f20a:
        lea eax,[ebp-8]
    L_0045f20d:
        push eax
    L_0045f20e:
        call dword ptr [data_004661b0]
    L_0045f214:
        mov esi,dword ptr [ebp-4]
    L_0045f217:
        xor esi,dword ptr [ebp-8]
    L_0045f21a:
        call dword ptr [data_004661b4]
    L_0045f220:
        xor esi,eax
    L_0045f222:
        call dword ptr [data_0046619c]
    L_0045f228:
        xor esi,eax
    L_0045f22a:
        call dword ptr [data_004660f0]
    L_0045f230:
        xor esi,eax
    L_0045f232:
        lea eax,[ebp-10h]
    L_0045f235:
        push eax
    L_0045f236:
        call dword ptr [data_004660fc]
    L_0045f23c:
        mov eax,dword ptr [ebp-0Ch]
    L_0045f23f:
        xor eax,dword ptr [ebp-10h]
    L_0045f242:
        xor esi,eax
    L_0045f244:
        mov dword ptr [data_00473660],esi
    L_0045f24a:
        jne short L_0045f256
    L_0045f24c:
        mov dword ptr [data_00473660],0BB40E64Eh
    L_0045f256:
        pop esi
    L_0045f257:
        leave
    L_0045f258:
        ret
    }
}
