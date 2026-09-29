#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 2026-09-26: the new semantic candidate passes 623 retail caller/state
// comparisons. See reference/recovery_notes/dat_archive_load_index_00434f70.md.
// Its private ABI and MSVC bytes remain unverified; older probes follow.
// BLOCKED (D3705): closest_byte_count=340/350; first_diff=0x00434f70
// residual_class=private ESI receiver plus virtual-reader call ABI, stack-local
// header placement, AL key flow, and helper cleanup ordering. The typed
// explicit-receiver candidate reached a 340-byte body but began with a stack
// receiver/prologue instead of retail's ESI-based sub-esp/mov sequence.
// variants_tested=live Ghidra pseudocode translated to typed archive-reader,
// decrypt/decompress, allocation, index-build, and failure-cleanup calls;
// candidate extent was 340/350 and was restored.
// next_lever=caller-inclusive native-LTCG cluster over 00434F70, callers
// 00434C30/00434CA0, DecryptDatBuffer, and the reader/decompress dependencies,
// preserving the ESI receiver and AL key convention.

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434F70..0x004350CD: ?DatArchive_LoadIndex@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_LoadIndex_00434f70() {
    __asm {
    L_00434f70:
        sub esp,14h
    L_00434f73:
        mov ecx,dword ptr [esi+0Ch]
    L_00434f76:
        test ecx,ecx
    L_00434f78:
        mov dword ptr [esp],0
    L_00434f7f:
        jne short L_00434f89
    L_00434f81:
        xor al,al
    L_00434f83:
        add esp,14h
    L_00434f86:
        ret 4
    L_00434f89:
        mov edx,dword ptr [data_00474908]
    L_00434f8f:
        mov eax,dword ptr [ecx]
    L_00434f91:
        push ebx
    L_00434f92:
        push ebp
    L_00434f93:
        push edi
    L_00434f94:
        push edx
    L_00434f95:
        mov edx,dword ptr [esp+28h]
    L_00434f99:
        push edx
    L_00434f9a:
        call dword ptr [eax]
    L_00434f9c:
        test al,al
    L_00434f9e:
        je asm_target_004350ae
    L_00434fa4:
        mov ecx,dword ptr [esi+0Ch]
    L_00434fa7:
        mov eax,dword ptr [ecx]
    L_00434fa9:
        push 10h
    L_00434fab:
        lea edx,[esp+14h]
    L_00434faf:
        push edx
    L_00434fb0:
        call dword ptr [eax+8]
    L_00434fb3:
        test eax,eax
    L_00434fb5:
        je asm_target_004350ae
    L_00434fbb:
        push 10h
    L_00434fbd:
        push 10h
    L_00434fbf:
        push 37h
    L_00434fc1:
        lea eax,[esp+1Ch]
    L_00434fc5:
        push 10h
    L_00434fc7:
        push eax
    L_00434fc8:
        mov al,1Bh
    L_00434fca:
        call asm_DecryptDatBuffer_0044b0d0
    L_00434fcf:
        cmp dword ptr [esp+10h],31414854h
    L_00434fd7:
        jne asm_target_004350ae
    L_00434fdd:
        mov ecx,dword ptr [esp+14h]
    L_00434fe1:
        mov eax,dword ptr [esp+18h]
    L_00434fe5:
        sub ecx,75BCD15h
    L_00434feb:
        mov dword ptr [esp+14h],ecx
    L_00434fef:
        mov ecx,dword ptr [esp+1Ch]
    L_00434ff3:
        add ecx,0F7E7F8ACh
    L_00434ff9:
        mov dword ptr [esi+4],ecx
    L_00434ffc:
        mov ecx,dword ptr [esi+0Ch]
    L_00434fff:
        sub eax,3ADE68B1h
    L_00435004:
        mov dword ptr [esp+18h],eax
    L_00435008:
        mov edx,dword ptr [ecx]
    L_0043500a:
        call dword ptr [edx+14h]
    L_0043500d:
        mov ebp,dword ptr [esp+18h]
    L_00435011:
        mov ecx,dword ptr [esi+0Ch]
    L_00435014:
        sub eax,ebp
    L_00435016:
        mov ebp,eax
    L_00435018:
        mov eax,dword ptr [ecx]
    L_0043501a:
        push 0
    L_0043501c:
        push ebp
    L_0043501d:
        call dword ptr [eax+18h]
    L_00435020:
        mov ebx,dword ptr [esp+18h]
    L_00435024:
        push ebx
    L_00435025:
        call asm_malloc_00452706
    L_0043502a:
        mov edi,eax
    L_0043502c:
        add esp,4
    L_0043502f:
        test edi,edi
    L_00435031:
        je short L_004350ae
    L_00435033:
        mov ecx,dword ptr [esi+0Ch]
    L_00435036:
        mov edx,dword ptr [ecx]
    L_00435038:
        push ebx
    L_00435039:
        push edi
    L_0043503a:
        call dword ptr [edx+8]
    L_0043503d:
        test eax,eax
    L_0043503f:
        je short L_00435094
    L_00435041:
        push ebx
    L_00435042:
        push 80h
    L_00435047:
        push 9Bh
    L_0043504c:
        push ebx
    L_0043504d:
        push edi
    L_0043504e:
        mov al,3Eh
    L_00435050:
        call asm_DecryptDatBuffer_0044b0d0
    L_00435055:
        mov eax,dword ptr [esp+14h]
    L_00435059:
        push eax
    L_0043505a:
        push 0
    L_0043505c:
        push ebx
    L_0043505d:
        push edi
    L_0043505e:
        call asm_DecompressDatLzss_00435dc0
    L_00435063:
        mov ebx,eax
    L_00435065:
        test ebx,ebx
    L_00435067:
        je short L_00435098
    L_00435069:
        mov ecx,dword ptr [esi+4]
    L_0043506c:
        push ebp
    L_0043506d:
        push ecx
    L_0043506e:
        push ebx
    L_0043506f:
        call asm_FUN_004350d0_004350d0
    L_00435074:
        test eax,eax
    L_00435076:
        mov dword ptr [esi],eax
    L_00435078:
        je short L_00435098
    L_0043507a:
        push edi
    L_0043507b:
        call asm_free_00452422
    L_00435080:
        push ebx
    L_00435081:
        call asm_free_00452422
    L_00435086:
        add esp,8
    L_00435089:
        pop edi
    L_0043508a:
        pop ebp
    L_0043508b:
        mov al,1
    L_0043508d:
        pop ebx
    L_0043508e:
        add esp,14h
    L_00435091:
        ret 4
    L_00435094:
        mov ebx,dword ptr [esp+0Ch]
    L_00435098:
        push edi
    L_00435099:
        call asm_free_00452422
    L_0043509e:
        add esp,4
    L_004350a1:
        test ebx,ebx
    L_004350a3:
        je short L_004350ae
    L_004350a5:
        push ebx
    L_004350a6:
        call asm_free_00452422
    L_004350ab:
        add esp,4
    L_004350ae:
        mov ecx,dword ptr [esi+0Ch]
    L_004350b1:
        test ecx,ecx
    L_004350b3:
        je short L_004350bc
    L_004350b5:
        mov edx,dword ptr [ecx]
    L_004350b7:
        push 1
    L_004350b9:
        call dword ptr [edx+1Ch]
    L_004350bc:
        pop edi
    L_004350bd:
        pop ebp
    L_004350be:
        mov dword ptr [esi+0Ch],0
    L_004350c5:
        xor al,al
    L_004350c7:
        pop ebx
    L_004350c8:
        add esp,14h
    L_004350cb:
        ret 4
    }
}
