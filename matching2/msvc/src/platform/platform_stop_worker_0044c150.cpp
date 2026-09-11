#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004054B0..0x004054FE: FUN_004054b0
// Naked body preserves the retail register/stack ABI.

// 0x0044C150..0x0044C1B4: ?Platform_StopWorker@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_StopWorker_0044c150() {
    __asm {
    L_0044c150:
        mov eax,dword ptr [esi+4]
    L_0044c153:
        push ebp
    L_0044c154:
        xor ebp,ebp
    L_0044c156:
        cmp eax,ebp
    L_0044c158:
        je short L_0044c1b3
    L_0044c15a:
        push edi
    L_0044c15b:
        mov edi,dword ptr [data_0046611c]
    L_0044c161:
        push 0C8h
    L_0044c166:
        push eax
    L_0044c167:
        mov dword ptr [esi+0Ch],1
    L_0044c16e:
        mov dword ptr [esi+10h],ebp
    L_0044c171:
        call edi
    L_0044c173:
        cmp eax,102h
    L_0044c178:
        jne short L_0044c1a2
    L_0044c17a:
        push ebx
    L_0044c17b:
        mov ebx,dword ptr [data_004660ac]
    L_0044c181:
        push 1
    L_0044c183:
        mov dword ptr [esi+0Ch],1
    L_0044c18a:
        mov dword ptr [esi+10h],ebp
    L_0044c18d:
        call ebx
    L_0044c18f:
        mov eax,dword ptr [esi+4]
    L_0044c192:
        push 0C8h
    L_0044c197:
        push eax
    L_0044c198:
        call edi
    L_0044c19a:
        cmp eax,102h
    L_0044c19f:
        je short L_0044c181
    L_0044c1a1:
        pop ebx
    L_0044c1a2:
        mov ecx,dword ptr [esi+4]
    L_0044c1a5:
        push ecx
    L_0044c1a6:
        call dword ptr [data_004660cc]
    L_0044c1ac:
        mov dword ptr [esi+4],ebp
    L_0044c1af:
        mov dword ptr [esi+18h],ebp
    L_0044c1b2:
        pop edi
    L_0044c1b3:
        pop ebp
    L_0044c1b4:
        ret
    }
}
