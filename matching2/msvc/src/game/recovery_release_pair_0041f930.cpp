#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0041F930..0x0041F98A: ?Recovery_ReleasePair@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleasePair_0041f930() {
    __asm {
    L_0041f930:
        push esi
    L_0041f931:
        mov esi,dword ptr [data_00491c10]
    L_0041f937:
        add esi,3AD084h
    L_0041f93d:
        push edi
    L_0041f93e:
        mov edi,dword ptr [esi]
    L_0041f940:
        test edi,edi
    L_0041f942:
        je short L_0041f95a
    L_0041f944:
        call asm_FUN_00447810_00447810
    L_0041f949:
        mov eax,dword ptr [esi]
    L_0041f94b:
        push eax
    L_0041f94c:
        call asm_free_004524a1
    L_0041f951:
        add esp,4
    L_0041f954:
        mov dword ptr [esi],0
    L_0041f95a:
        mov esi,dword ptr [data_00491c10]
    L_0041f960:
        mov edi,dword ptr [esi+3AD088h]
    L_0041f966:
        add esi,3AD088h
    L_0041f96c:
        test edi,edi
    L_0041f96e:
        je short L_0041f986
    L_0041f970:
        call asm_FUN_00447810_00447810
    L_0041f975:
        mov ecx,dword ptr [esi]
    L_0041f977:
        push ecx
    L_0041f978:
        call asm_free_004524a1
    L_0041f97d:
        add esp,4
    L_0041f980:
        mov dword ptr [esi],0
    L_0041f986:
        pop edi
    L_0041f987:
        xor eax,eax
    L_0041f989:
        pop esi
    L_0041f98a:
        ret
    }
}
