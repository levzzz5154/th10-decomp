#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x00447A50..0x00447ADC: Recovery_MarkLogState
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_MarkLogState_00447a50() {
    __asm {
    L_00447a50:
        sub esp,84h
    L_00447a56:
        mov eax,dword ptr [data_00473660]
    L_00447a5b:
        mov ecx,dword ptr [esp+90h]
    L_00447a62:
        xor eax,esp
    L_00447a64:
        push ebx
    L_00447a65:
        push ebp
    L_00447a66:
        movzx ebp,byte ptr [esi+3A0h]
    L_00447a6d:
        mov dword ptr [esp+88h],eax
    L_00447a74:
        push edi
    L_00447a75:
        lea eax,[esp+0A0h]
    L_00447a7c:
        push eax
    L_00447a7d:
        push ecx
    L_00447a7e:
        lea edx,[esp+14h]
    L_00447a82:
        push edx
    L_00447a83:
        call asm_vsprintf_004524a6
    L_00447a88:
        mov eax,dword ptr [esi+360h]
    L_00447a8e:
        mov ecx,dword ptr [esp+0A4h]
    L_00447a95:
        mov edi,dword ptr [esi+394h]
    L_00447a9b:
        mov edx,dword ptr [edi+4]
    L_00447a9e:
        add esp,0Ch
    L_00447aa1:
        shr eax,1
    L_00447aa3:
        and eax,1
    L_00447aa6:
        push eax
    L_00447aa7:
        push ecx
    L_00447aa8:
        push 0
    L_00447aaa:
        push edx
    L_00447aab:
        lea ebx,[esp+1Ch]
    L_00447aaf:
        mov eax,ebp
    L_00447ab1:
        call asm_Recovery_DispatchRandomText_004479d0
    L_00447ab6:
        mov eax,dword ptr [esi+35Ch]
    L_00447abc:
        mov ecx,dword ptr [esp+8Ch]
    L_00447ac3:
        pop edi
    L_00447ac4:
        pop ebp
    L_00447ac5:
        or eax,1
    L_00447ac8:
        pop ebx
    L_00447ac9:
        xor ecx,esp
    L_00447acb:
        mov dword ptr [esi+35Ch],eax
    L_00447ad1:
        call asm_security_check_cookie_00458ea5
    L_00447ad6:
        add esp,84h
    L_00447adc:
        ret
    }
}
