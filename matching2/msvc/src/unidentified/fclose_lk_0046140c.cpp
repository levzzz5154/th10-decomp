#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046140C..0x00461457: __fclose_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_fclose_lk_0046140c() {
    __asm {
    L_0046140c:
        push esi
    L_0046140d:
        mov esi,dword ptr [esp+8]
    L_00461411:
        push edi
    L_00461412:
        or edi,0FFFFFFFFh
    L_00461415:
        test byte ptr [esi+0Ch],83h
    L_00461419:
        je short L_0046144f
    L_0046141b:
        push esi
    L_0046141c:
        call asm_flush_0045fbf6
    L_00461421:
        push esi
    L_00461422:
        mov edi,eax
    L_00461424:
        call asm_freebuf_00462225
    L_00461429:
        push dword ptr [esi+10h]
    L_0046142c:
        call asm_close_0046218a
    L_00461431:
        add esp,0Ch
    L_00461434:
        test eax,eax
    L_00461436:
        jge short L_0046143d
    L_00461438:
        or edi,0FFFFFFFFh
    L_0046143b:
        jmp short L_0046144f
    L_0046143d:
        mov eax,dword ptr [esi+1Ch]
    L_00461440:
        test eax,eax
    L_00461442:
        je short L_0046144f
    L_00461444:
        push eax
    L_00461445:
        call asm_free_00452422
    L_0046144a:
        and dword ptr [esi+1Ch],0
    L_0046144e:
        pop ecx
    L_0046144f:
        and dword ptr [esi+0Ch],0
    L_00461453:
        mov eax,edi
    L_00461455:
        pop edi
    L_00461456:
        pop esi
    L_00461457:
        ret
    }
}
