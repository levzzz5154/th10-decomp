#include <string.h>

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/math/angle.hpp"

// Recovered semantic definitions: the platform prototypes they call and the
// kernel32 entry point reached through a dllimport slot.
#include "th10/platform/sound_buffer.hpp"
#include "th10/platform/windows_types.hpp"

// 0x0044CE80..0x0044CEF5: Recovery_InitializeInterfaceArray
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_InitializeInterfaceArray_0044ce80() {
    __asm {
    L_0044ce80:
        push ebx
    L_0044ce81:
        mov ebx,eax
    L_0044ce83:
        lea eax,[edi*4]
    L_0044ce8a:
        push eax
    L_0044ce8b:
        mov dword ptr [esi],4705D8h
    L_0044ce91:
        call asm_operator_new_00452493
    L_0044ce96:
        mov dword ptr [esi+4],eax
    L_0044ce99:
        add esp,4
    L_0044ce9c:
        xor eax,eax
    L_0044ce9e:
        test edi,edi
    L_0044cea0:
        jbe short L_0044ceb0
    L_0044cea2:
        mov edx,dword ptr [ebx+eax*4]
    L_0044cea5:
        mov ecx,dword ptr [esi+4]
    L_0044cea8:
        mov dword ptr [ecx+eax*4],edx
    L_0044ceab:
        inc eax
    L_0044ceac:
        cmp eax,edi
    L_0044ceae:
        jb short L_0044cea2
    L_0044ceb0:
        mov eax,dword ptr [esp+8]
    L_0044ceb4:
        mov ecx,dword ptr [esp+0Ch]
    L_0044ceb8:
        mov edx,dword ptr [esi+4]
    L_0044cebb:
        mov dword ptr [esi+8],eax
    L_0044cebe:
        mov dword ptr [esi+10h],edi
    L_0044cec1:
        mov dword ptr [esi+0Ch],ecx
    L_0044cec4:
        mov eax,dword ptr [edx]
    L_0044cec6:
        push 0
    L_0044cec8:
        push eax
    L_0044cec9:
        mov eax,esi
    L_0044cecb:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044ced0:
        xor ebx,ebx
    L_0044ced2:
        test edi,edi
    L_0044ced4:
        jbe short L_0044cee9
    L_0044ced6:
        mov ecx,dword ptr [esi+4]
    L_0044ced9:
        mov eax,dword ptr [ecx+ebx*4]
    L_0044cedc:
        mov edx,dword ptr [eax]
    L_0044cede:
        push 0
    L_0044cee0:
        push eax
    L_0044cee1:
        call dword ptr [edx+34h]
    L_0044cee4:
        inc ebx
    L_0044cee5:
        cmp ebx,edi
    L_0044cee7:
        jb short L_0044ced6
    L_0044cee9:
        mov dword ptr [esi+30h],0
    L_0044cef0:
        mov eax,esi
    L_0044cef2:
        pop ebx
    L_0044cef3:
        ret 8
    }
}
