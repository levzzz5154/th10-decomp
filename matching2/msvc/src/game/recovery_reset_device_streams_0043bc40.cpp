#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0043BC40..0x0043BCC6: Recovery_ResetDeviceStreams
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ResetDeviceStreams_0043bc40() {
    __asm {
    L_0043bc40:
        mov eax,dword ptr [data_00491c30]
    L_0043bc45:
        mov ecx,dword ptr [eax]
    L_0043bc47:
        push 0
    L_0043bc49:
        push 3F800000h
    L_0043bc4e:
        push esi
    L_0043bc4f:
        push 3
    L_0043bc51:
        push 0
    L_0043bc53:
        push 0
    L_0043bc55:
        push eax
    L_0043bc56:
        call dword ptr [ecx+0ACh]
    L_0043bc5c:
        mov eax,dword ptr [data_00491c30]
    L_0043bc61:
        mov edx,dword ptr [eax]
    L_0043bc63:
        push 0
    L_0043bc65:
        push 0
    L_0043bc67:
        push 0
    L_0043bc69:
        push 0
    L_0043bc6b:
        push eax
    L_0043bc6c:
        call dword ptr [edx+44h]
    L_0043bc6f:
        test eax,eax
    L_0043bc71:
        jge short L_0043bc83
    L_0043bc73:
        mov eax,dword ptr [data_00491c30]
    L_0043bc78:
        mov ecx,dword ptr [eax]
    L_0043bc7a:
        push 491D0Ch
    L_0043bc7f:
        push eax
    L_0043bc80:
        call dword ptr [ecx+40h]
    L_0043bc83:
        mov eax,dword ptr [data_00491c30]
    L_0043bc88:
        mov edx,dword ptr [eax]
    L_0043bc8a:
        push 0
    L_0043bc8c:
        push 3F800000h
    L_0043bc91:
        push esi
    L_0043bc92:
        push 3
    L_0043bc94:
        push 0
    L_0043bc96:
        push 0
    L_0043bc98:
        push eax
    L_0043bc99:
        call dword ptr [edx+0ACh]
    L_0043bc9f:
        mov eax,dword ptr [data_00491c30]
    L_0043bca4:
        mov ecx,dword ptr [eax]
    L_0043bca6:
        push 0
    L_0043bca8:
        push 0
    L_0043bcaa:
        push 0
    L_0043bcac:
        push 0
    L_0043bcae:
        push eax
    L_0043bcaf:
        call dword ptr [ecx+44h]
    L_0043bcb2:
        test eax,eax
    L_0043bcb4:
        jge short L_0043bcc6
    L_0043bcb6:
        mov eax,dword ptr [data_00491c30]
    L_0043bcbb:
        mov edx,dword ptr [eax]
    L_0043bcbd:
        push 491D0Ch
    L_0043bcc2:
        push eax
    L_0043bcc3:
        call dword ptr [edx+40h]
    L_0043bcc6:
        ret
    }
}
