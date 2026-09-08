#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462250..0x0046227A: __strdup
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strdup_00462250() {
    __asm {
    L_00462250:
        push esi
    L_00462251:
        mov esi,dword ptr [esp+8]
    L_00462255:
        test esi,esi
    L_00462257:
        je short L_00462277
    L_00462259:
        push esi
    L_0046225a:
        call asm_strlen_00456720
    L_0046225f:
        inc eax
    L_00462260:
        push eax
    L_00462261:
        call asm_malloc_00452706
    L_00462266:
        test eax,eax
    L_00462268:
        pop ecx
    L_00462269:
        pop ecx
    L_0046226a:
        je short L_00462277
    L_0046226c:
        push esi
    L_0046226d:
        push eax
    L_0046226e:
        call asm_FUN_0045bd80_0045bd80
    L_00462273:
        pop ecx
    L_00462274:
        pop ecx
    L_00462275:
        pop esi
    L_00462276:
        ret
    L_00462277:
        xor eax,eax
    L_00462279:
        pop esi
    L_0046227a:
        ret
    }
}
