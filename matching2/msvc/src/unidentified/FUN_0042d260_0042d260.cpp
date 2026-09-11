#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042D260..0x0042D2B3: FUN_0042d260
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042d260_0042d260() {
    __asm {
    L_0042d260:
        push edi
    L_0042d261:
        mov edi,eax
    L_0042d263:
        mov eax,dword ptr [edi+1Ch]
    L_0042d266:
        add eax,0FFFFFFF7h
    L_0042d269:
        cmp eax,7
    L_0042d26c:
        ja short L_0042d2ad
    L_0042d26e:
        jmp dword ptr [eax*4+42D2B4h]
    L_0042d275:
        push edi
    L_0042d276:
        call asm_FUN_00431ba0_00431ba0
    L_0042d27b:
        mov eax,1
    L_0042d280:
        pop edi
    L_0042d281:
        ret
    L_0042d282:
        call asm_FUN_004329f0_004329f0
    L_0042d287:
        mov eax,1
    L_0042d28c:
        pop edi
    L_0042d28d:
        ret
    L_0042d28e:
        push edi
    L_0042d28f:
        call asm_FUN_00433230_00433230
    L_0042d294:
        mov eax,1
    L_0042d299:
        pop edi
    L_0042d29a:
        ret
    L_0042d29b:
        push edi
    L_0042d29c:
        call asm_FUN_00433b30_00433b30
    L_0042d2a1:
        mov eax,1
    L_0042d2a6:
        pop edi
    L_0042d2a7:
        ret
    L_0042d2a8:
        call asm_FUN_00431410_00431410
    L_0042d2ad:
        mov eax,1
    L_0042d2b2:
        pop edi
    L_0042d2b3:
        ret
        _emit 0xa8
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0xad
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0x82
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0x75
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0xad
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0xad
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0x8e
        _emit 0xd2
        _emit 0x42
        _emit 0x00
        _emit 0x9b
        _emit 0xd2
        _emit 0x42
        _emit 0x00
    }
}
