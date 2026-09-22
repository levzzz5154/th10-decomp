#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3304): closest_byte_count=194/194; first_diff=none;
// residual_class=private ESI cursor receiver and AL mode flag, with direct
// SetFilePointer import placement, require the caller's native register
// context. variants_tested=live Ghidra decompilation, callers/callees/xrefs
// and variable audit (callers 0x0044D110 and 0x0044D850; callee
// SetFilePointer), plus MSVC 13.10 exact baseline probe. next_lever=native-
// LTCG cluster with both real callers and this body, preserving the ESI/AL
// handoff; current overlay remains exact.

// 0x0044DD40..0x0044DE01: ArchiveCursor_SeekRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ArchiveCursor_SeekRetail_0044dd40() {
    __asm {
    L_0044dd40:
        push ebx
    L_0044dd41:
        mov bl,al
    L_0044dd43:
        mov eax,dword ptr [esi+7Ch]
    L_0044dd46:
        test eax,eax
    L_0044dd48:
        je short L_0044dd88
    L_0044dd4a:
        mov edx,dword ptr [esi+80h]
    L_0044dd50:
        mov ecx,dword ptr [esi+90h]
    L_0044dd56:
        mov dword ptr [esi+84h],edx
    L_0044dd5c:
        mov eax,dword ptr [ecx+1Ch]
    L_0044dd5f:
        test eax,eax
    L_0044dd61:
        jle short L_0044dd69
    L_0044dd63:
        mov dword ptr [esi+88h],eax
    L_0044dd69:
        test bl,bl
    L_0044dd6b:
        je asm_target_0044ddfe
    L_0044dd71:
        mov ecx,dword ptr [ecx+18h]
    L_0044dd74:
        test ecx,ecx
    L_0044dd76:
        jle asm_target_0044ddfe
    L_0044dd7c:
        add ecx,edx
    L_0044dd7e:
        mov dword ptr [esi+84h],ecx
    L_0044dd84:
        xor eax,eax
    L_0044dd86:
        pop ebx
    L_0044dd87:
        ret
    L_0044dd88:
        mov edx,dword ptr [esi+8Ch]
    L_0044dd8e:
        test edx,edx
    L_0044dd90:
        jne short L_0044dd99
    L_0044dd92:
        mov eax,800401F0h
    L_0044dd97:
        pop ebx
    L_0044dd98:
        ret
    L_0044dd99:
        test bl,bl
    L_0044dd9b:
        je short L_0044ddd6
    L_0044dd9d:
        mov eax,dword ptr [esi+90h]
    L_0044dda3:
        mov ecx,dword ptr [eax+18h]
    L_0044dda6:
        test ecx,ecx
    L_0044dda8:
        jle short L_0044ddd6
    L_0044ddaa:
        mov eax,dword ptr [eax+10h]
    L_0044ddad:
        mov ebx,dword ptr [data_004977a4]
    L_0044ddb3:
        push 0
    L_0044ddb5:
        add eax,ecx
    L_0044ddb7:
        push 0
    L_0044ddb9:
        add eax,ebx
    L_0044ddbb:
        push eax
    L_0044ddbc:
        push edx
    L_0044ddbd:
        call dword ptr [data_004660c8]
    L_0044ddc3:
        mov eax,dword ptr [esi+90h]
    L_0044ddc9:
        mov ecx,dword ptr [eax+1Ch]
    L_0044ddcc:
        sub ecx,dword ptr [eax+18h]
    L_0044ddcf:
        mov dword ptr [esi+8],ecx
    L_0044ddd2:
        xor eax,eax
    L_0044ddd4:
        pop ebx
    L_0044ddd5:
        ret
    L_0044ddd6:
        mov eax,dword ptr [esi+90h]
    L_0044dddc:
        mov ecx,dword ptr [eax+10h]
    L_0044dddf:
        mov eax,dword ptr [data_004977a4]
    L_0044dde4:
        push 0
    L_0044dde6:
        push 0
    L_0044dde8:
        add ecx,eax
    L_0044ddea:
        push ecx
    L_0044ddeb:
        push edx
    L_0044ddec:
        call dword ptr [data_004660c8]
    L_0044ddf2:
        mov edx,dword ptr [esi+90h]
    L_0044ddf8:
        mov eax,dword ptr [edx+1Ch]
    L_0044ddfb:
        mov dword ptr [esi+8],eax
    L_0044ddfe:
        xor eax,eax
    L_0044de00:
        pop ebx
    L_0044de01:
        ret
    }
}
