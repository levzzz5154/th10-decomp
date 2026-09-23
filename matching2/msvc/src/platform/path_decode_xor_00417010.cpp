// BLOCKED: retail entry ABI passes the input pointer in EAX.  All five direct
// call sites use that register convention; the repository's ordinary MSVC C++
// calling conventions cannot declare an EAX parameter.  Replacing this body
// with a typed function would require migrating the caller cluster too.
//
// Historical D3307 codegen record: best ordinary-C++ candidate matched 21/41
// bytes (first difference at 0x00417012); five native MSVC 13.10 context
// variants were tried.  This pass did not rerun a build or probe.

#include <string.h>
#include "asm_encoding.hpp"

// Retail strrchr at 0x00452930 (cdecl: string, character).

// 0x00417010..0x00417038: ?Path_DecodeXor@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Path_DecodeXor_00417010() {
    __asm {
    L_00417010:
        push esi
    L_00417011:
        push edi
    L_00417012:
        mov edi,eax
    L_00417014:
        mov cl,77h
    L_00417016:
        mov dl,7
    L_00417018:
        mov esi,497D40h
    L_0041701d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00417020:
        mov al,byte ptr [edi]
    L_00417022:
        xor al,cl
    L_00417024:
        mov byte ptr [esi],al
    L_00417026:
        inc esi
    L_00417027:
        add cl,dl
    L_00417029:
        inc edi
    L_0041702a:
        add dl,10h
    L_0041702d:
        test al,al
    L_0041702f:
        jne short L_00417020
    L_00417031:
        pop edi
    L_00417032:
        mov eax,497D40h
    L_00417037:
        pop esi
    L_00417038:
        ret
    }
}
