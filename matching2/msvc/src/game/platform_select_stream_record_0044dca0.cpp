#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044DCA0..0x0044DCED: ?Platform_SelectStreamRecord@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Platform_SelectStreamRecord_0044dca0() {
    __asm {
    L_0044dca0:
        mov eax,dword ptr [esi+7Ch]
    L_0044dca3:
        test eax,eax
    L_0044dca5:
        jne short L_0044dcb2
    L_0044dca7:
        mov eax,dword ptr [esi+8Ch]
    L_0044dcad:
        cmp eax,0FFFFFFFFh
    L_0044dcb0:
        jne short L_0044dcb8
    L_0044dcb2:
        mov eax,80004005h
    L_0044dcb7:
        ret
    L_0044dcb8:
        test eax,eax
    L_0044dcba:
        mov dword ptr [esi+90h],ecx
    L_0044dcc0:
        je short L_0044dce5
    L_0044dcc2:
        mov ecx,dword ptr [ecx+10h]
    L_0044dcc5:
        mov edx,dword ptr [data_004977a4]
    L_0044dccb:
        push 0
    L_0044dccd:
        push 0
    L_0044dccf:
        add ecx,edx
    L_0044dcd1:
        push ecx
    L_0044dcd2:
        push eax
    L_0044dcd3:
        call dword ptr [data_004660c8]
    L_0044dcd9:
        mov edx,dword ptr [esi+90h]
    L_0044dcdf:
        mov eax,dword ptr [edx+1Ch]
    L_0044dce2:
        mov dword ptr [esi+8],eax
    L_0044dce5:
        mov ecx,dword ptr [esi+8]
    L_0044dce8:
        mov dword ptr [esi+2Ch],ecx
    L_0044dceb:
        xor eax,eax
    L_0044dced:
        ret
    }
}
