#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436210..0x0043625F: ?MemoryFile_RemoveNode@@
// Naked body preserves the retail register/stack ABI.

// 0x00436210..0x0043625F: ?MemoryFile_RemoveNode@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_RemoveNode_00436210() {
    __asm {
    L_00436210:
        push esi
    L_00436211:
        mov esi,ecx
    L_00436213:
        lea eax,[esi+esi*2]
    L_00436216:
        shl eax,2
    L_00436219:
        mov ecx,dword ptr [eax+477858h]
    L_0043621f:
        test ecx,ecx
    L_00436221:
        je short L_00436238
    L_00436223:
        mov edx,dword ptr [eax+477860h]
    L_00436229:
        test edx,edx
    L_0043622b:
        jne short L_0043623a
    L_0043622d:
        mov edx,dword ptr [eax+47785Ch]
    L_00436233:
        call asm_MemoryFile_RelinkChild_00436260
    L_00436238:
        pop esi
    L_00436239:
        ret
    L_0043623a:
        mov ecx,dword ptr [eax+47785Ch]
    L_00436240:
        test ecx,ecx
    L_00436242:
        je short L_00436233
    L_00436244:
        push edi
    L_00436245:
        mov eax,esi
    L_00436247:
        call asm_MemoryFile_FindPredecessor_00436330
    L_0043624c:
        mov edi,eax
    L_0043624e:
        mov ecx,edi
    L_00436250:
        call asm_MemoryFile_RemoveNode_00436210
    L_00436255:
        mov ecx,edi
    L_00436257:
        pop edi
    L_00436258:
        mov eax,esi
    L_0043625a:
        pop esi
    L_0043625b:
        jmp asm_MemoryFile_ReplaceNode_004362b0
    }
}
