// BLOCKED (D3202): closest_byte_count=8/117; first_diff=0x004362B2
// (authoritative native-LTCG scratch body extent was 115 bytes, so the
// candidate is not promotable despite its exact 8-byte tail).
// residual_class=private source-index-in-EAX / replacement-in-ECX ABI and
// compiler source-shape scheduling around parent/source node pointers, plus
// the shared 0x00477858 compression-tree layout. Live Ghidra topology: caller
// 0x0043625B; adjacent callees/cluster members 0x00436260 and 0x00436330.
// variants_tested=Ghidra complete decompilation, xrefs/callers/callees,
// disassembly/variable audit, legacy MemoryFile_ReplaceNode model, and native
// MSVC 13.10 /GL /LTCG synthetic caller variants. The closest candidate was
// restored after 8/117 matching bytes and a 115-byte extent.
// next_lever=schema2 native-LTCG cluster joining the real 0x00436210 caller,
// 0x00436260 relink, 0x00436330 predecessor, and this body; vary only the
// source-pointer/parent-pointer expression until the EAX/ECX body reaches
// 117 bytes and exact retail scheduling.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436210..0x0043625F: ?MemoryFile_RemoveNode@@
// Naked body preserves the retail register/stack ABI.

// 0x004362B0..0x00436324: ?MemoryFile_ReplaceNode@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_ReplaceNode_004362b0() {
    __asm {
    L_004362b0:
        push ebx
    L_004362b1:
        push esi
    L_004362b2:
        mov esi,eax
    L_004362b4:
        lea eax,[esi+esi*2]
    L_004362b7:
        lea edx,[eax*4+477858h]
    L_004362be:
        mov eax,dword ptr [edx]
    L_004362c0:
        lea eax,[eax+eax*2]
    L_004362c3:
        shl eax,2
    L_004362c6:
        push edi
    L_004362c7:
        cmp dword ptr [eax+47785Ch],esi
    L_004362cd:
        jne short L_004362d7
    L_004362cf:
        mov dword ptr [eax+47785Ch],ecx
    L_004362d5:
        jmp short L_004362dd
    L_004362d7:
        mov dword ptr [eax+477860h],ecx
    L_004362dd:
        lea eax,[ecx+ecx*2]
    L_004362e0:
        shl eax,2
    L_004362e3:
        lea esi,[eax+477858h]
    L_004362e9:
        mov edi,edx
    L_004362eb:
        mov ebx,dword ptr [edi]
    L_004362ed:
        mov dword ptr [esi],ebx
    L_004362ef:
        mov ebx,dword ptr [edi+4]
    L_004362f2:
        mov dword ptr [esi+4],ebx
    L_004362f5:
        mov edi,dword ptr [edi+8]
    L_004362f8:
        mov dword ptr [esi+8],edi
    L_004362fb:
        mov esi,dword ptr [eax+47785Ch]
    L_00436301:
        lea esi,[esi+esi*2]
    L_00436304:
        mov dword ptr [esi*4+477858h],ecx
    L_0043630b:
        mov eax,dword ptr [eax+477860h]
    L_00436311:
        pop edi
    L_00436312:
        lea eax,[eax+eax*2]
    L_00436315:
        pop esi
    L_00436316:
        mov dword ptr [eax*4+477858h],ecx
    L_0043631d:
        mov dword ptr [edx],0
    L_00436323:
        pop ebx
    L_00436324:
        ret
    }
}
