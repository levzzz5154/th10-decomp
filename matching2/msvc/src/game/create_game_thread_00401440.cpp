#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.

// 0x00401440..0x00401484: CreateGameThread
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CreateGameThread_00401440() {
    __asm {
    L_00401440:
        push esi
    L_00401441:
        push 89ACh
    L_00401446:
        call asm_operator_new_00452493
    L_0040144b:
        add esp,4
    L_0040144e:
        test eax,eax
    L_00401450:
        je short L_0040145d
    L_00401452:
        mov esi,eax
    L_00401454:
        call asm_GameThread_Construct_00401000
    L_00401459:
        mov esi,eax
    L_0040145b:
        jmp short L_0040145f
    L_0040145d:
        xor esi,esi
    L_0040145f:
        mov eax,esi
    L_00401461:
        call asm_LoadGameThreadResources_00401110
    L_00401466:
        test eax,eax
    L_00401468:
        je short L_00401481
    L_0040146a:
        test esi,esi
    L_0040146c:
        je short L_0040147d
    L_0040146e:
        push esi
    L_0040146f:
        call asm_DestroyGameThread_00401260
    L_00401474:
        push esi
    L_00401475:
        call asm_free_004524a1
    L_0040147a:
        add esp,4
    L_0040147d:
        xor eax,eax
    L_0040147f:
        pop esi
    L_00401480:
        ret
    L_00401481:
        mov eax,esi
    L_00401483:
        pop esi
    L_00401484:
        ret
    }
}
