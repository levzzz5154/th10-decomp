#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// Complete typed candidate: reference/semantic_candidates/music_cursor.cpp.
// File mode subtracts the request before ReadFile and ignores its BOOL. Memory
// mode preserves forward word-copy overlap and output aliasing. See current
// recovery_notes/music_cursor_and_stream_refill.md for differential evidence.

// 0x0044DE10..0x0044DED9: ArchiveCursor_ReadRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ArchiveCursor_ReadRetail_0044de10() {
    __asm {
    L_0044de10:
        mov ecx,dword ptr [eax+7Ch]
    L_0044de13:
        test ecx,ecx
    L_0044de15:
        push ebx
    L_0044de16:
        mov ebx,dword ptr [esp+8]
    L_0044de1a:
        push esi
    L_0044de1b:
        push edi
    L_0044de1c:
        mov edi,dword ptr [esp+14h]
    L_0044de20:
        je short L_0044de91
    L_0044de22:
        mov ecx,dword ptr [eax+84h]
    L_0044de28:
        test ecx,ecx
    L_0044de2a:
        jne short L_0044de37
    L_0044de2c:
        pop edi
    L_0044de2d:
        pop esi
    L_0044de2e:
        mov eax,800401F0h
    L_0044de33:
        pop ebx
    L_0044de34:
        ret 8
    L_0044de37:
        test edi,edi
    L_0044de39:
        je short L_0044de41
    L_0044de3b:
        mov dword ptr [edi],0
    L_0044de41:
        mov ebx,dword ptr [eax+88h]
    L_0044de47:
        mov ecx,dword ptr [eax+80h]
    L_0044de4d:
        mov esi,dword ptr [eax+84h]
    L_0044de53:
        push ebp
    L_0044de54:
        lea ebp,[esi+edx]
    L_0044de57:
        lea edi,[ecx+ebx]
    L_0044de5a:
        cmp ebp,edi
    L_0044de5c:
        pop ebp
    L_0044de5d:
        jbe short L_0044de65
    L_0044de5f:
        sub ecx,esi
    L_0044de61:
        add ecx,ebx
    L_0044de63:
        mov edx,ecx
    L_0044de65:
        mov edi,dword ptr [esp+10h]
    L_0044de69:
        mov ecx,edx
    L_0044de6b:
        mov ebx,ecx
    L_0044de6d:
        shr ecx,2
    L_0044de70:
        rep movsd
    L_0044de72:
        mov ecx,ebx
    L_0044de74:
        and ecx,3
    L_0044de77:
        rep movsb
    L_0044de79:
        add dword ptr [eax+84h],edx
    L_0044de7f:
        mov eax,dword ptr [esp+14h]
    L_0044de83:
        test eax,eax
    L_0044de85:
        je short L_0044de89
    L_0044de87:
        mov dword ptr [eax],edx
    L_0044de89:
        pop edi
    L_0044de8a:
        pop esi
    L_0044de8b:
        xor eax,eax
    L_0044de8d:
        pop ebx
    L_0044de8e:
        ret 8
    L_0044de91:
        mov esi,dword ptr [eax+8Ch]
    L_0044de97:
        test esi,esi
    L_0044de99:
        je short L_0044de2c
    L_0044de9b:
        test ebx,ebx
    L_0044de9d:
        je short L_0044decf
    L_0044de9f:
        test edi,edi
    L_0044dea1:
        je short L_0044decf
    L_0044dea3:
        mov ecx,dword ptr [eax+8]
    L_0044dea6:
        cmp edx,ecx
    L_0044dea8:
        jbe short L_0044deac
    L_0044deaa:
        mov edx,ecx
    L_0044deac:
        sub ecx,edx
    L_0044deae:
        push 0
    L_0044deb0:
        mov dword ptr [eax+8],ecx
    L_0044deb3:
        lea eax,[esp+14h]
    L_0044deb7:
        push eax
    L_0044deb8:
        push edx
    L_0044deb9:
        push ebx
    L_0044deba:
        push esi
    L_0044debb:
        call dword ptr [data_004660d0]
    L_0044dec1:
        mov ecx,dword ptr [esp+10h]
    L_0044dec5:
        mov dword ptr [edi],ecx
    L_0044dec7:
        pop edi
    L_0044dec8:
        pop esi
    L_0044dec9:
        xor eax,eax
    L_0044decb:
        pop ebx
    L_0044decc:
        ret 8
    L_0044decf:
        pop edi
    L_0044ded0:
        pop esi
    L_0044ded1:
        mov eax,80070057h
    L_0044ded6:
        pop ebx
    L_0044ded7:
        ret 8
    }
}
// BLOCKED (D3303): closest_byte_count=0/202; first_diff=none;
// residual_class=private EAX cursor and EDX size ABI, with ReadFile's
// indirect slot and rep-move codegen required to match exactly.
// variants_tested=live Ghidra decompilation/topology and MSVC 13.10 readable
// stdcall translation (260/202 extent); next_lever=native-LTCG
// cluster/schema2 with callers 0044D110 and 0044D850 plus ReadFile slot
// binding.
// Current assembly overlay remains exact.
