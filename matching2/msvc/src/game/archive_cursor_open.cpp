// BLOCKED (D3506): closest_byte_count=0/173; first_diff=0x0044DBF0;
// residual_class=private EAX mode/ECX filename/EDX record/ESI cursor inputs,
// conditional Win32 import sequencing, and the cursor caller's native ABI.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee and global audits, and MSVC 13.10 probe path (the wrapper is
// exact); no readable candidate was byte-measured without changing the
// fixed-address ownership manifest.
// next_lever=native-LTCG schema-2 cluster over caller 0x0044C8F0 and this
// body, with 0x004660C4/0x004660C8 and the ArchiveCursor layout bound at
// retail addresses, then measure all 173 bytes.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DBF0..0x0044DC9C: ArchiveCursor_Open
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ArchiveCursor_Open_0044dbf0() {
    __asm {
    L_0044dbf0:
        cmp eax,1
    L_0044dbf3:
        push edi
    L_0044dbf4:
        mov edi,edx
    L_0044dbf6:
        mov dword ptr [esi+78h],eax
    L_0044dbf9:
        mov dword ptr [esi+7Ch],0
    L_0044dc00:
        jne asm_target_0044dc99
    L_0044dc06:
        test ecx,ecx
    L_0044dc08:
        jne short L_0044dc11
    L_0044dc0a:
        mov eax,80070057h
    L_0044dc0f:
        pop edi
    L_0044dc10:
        ret
    L_0044dc11:
        push 0
    L_0044dc13:
        push 8000080h
    L_0044dc18:
        push 3
    L_0044dc1a:
        push 0
    L_0044dc1c:
        push 1
    L_0044dc1e:
        push 80000000h
    L_0044dc23:
        push ecx
    L_0044dc24:
        call dword ptr [data_004660c4]
    L_0044dc2a:
        cmp eax,0FFFFFFFFh
    L_0044dc2d:
        mov dword ptr [esi+8Ch],eax
    L_0044dc33:
        jne short L_0044dc3c
    L_0044dc35:
        mov eax,80004005h
    L_0044dc3a:
        pop edi
    L_0044dc3b:
        ret
    L_0044dc3c:
        mov ecx,dword ptr [esi+7Ch]
    L_0044dc3f:
        test ecx,ecx
    L_0044dc41:
        mov dword ptr [esi+90h],edi
    L_0044dc47:
        je short L_0044dc6c
    L_0044dc49:
        mov eax,dword ptr [esi+80h]
    L_0044dc4f:
        mov dword ptr [esi+84h],eax
    L_0044dc55:
        mov eax,dword ptr [edi+1Ch]
    L_0044dc58:
        test eax,eax
    L_0044dc5a:
        jle short L_0044dc93
    L_0044dc5c:
        mov ecx,dword ptr [esi+8]
    L_0044dc5f:
        mov dword ptr [esi+88h],eax
    L_0044dc65:
        mov dword ptr [esi+2Ch],ecx
    L_0044dc68:
        xor eax,eax
    L_0044dc6a:
        pop edi
    L_0044dc6b:
        ret
    L_0044dc6c:
        test eax,eax
    L_0044dc6e:
        je short L_0044dc93
    L_0044dc70:
        mov ecx,dword ptr [edi+10h]
    L_0044dc73:
        mov edi,dword ptr [data_004977a4]
    L_0044dc79:
        push 0
    L_0044dc7b:
        push 0
    L_0044dc7d:
        add ecx,edi
    L_0044dc7f:
        push ecx
    L_0044dc80:
        push eax
    L_0044dc81:
        call dword ptr [data_004660c8]
    L_0044dc87:
        mov edx,dword ptr [esi+90h]
    L_0044dc8d:
        mov eax,dword ptr [edx+1Ch]
    L_0044dc90:
        mov dword ptr [esi+8],eax
    L_0044dc93:
        mov ecx,dword ptr [esi+8]
    L_0044dc96:
        mov dword ptr [esi+2Ch],ecx
    L_0044dc99:
        xor eax,eax
    L_0044dc9b:
        pop edi
    L_0044dc9c:
        ret
    }
}
