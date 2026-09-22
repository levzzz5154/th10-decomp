// BLOCKED (H2801): closest_byte_count=103; first_diff=unmeasured (no
// compiler-readable candidate reached the private entry symbol);
// residual_class=private_abi/source_shape: retail receives the input cursor
// in EDX, destination in ESI, and byte count on the stack, while retaining
// the count in EBP and driving the zero-fill with REP STOSD/STOSB before the
// multibyte line-copy loop. Ghidra has no function at 0044C000; live
// disassembly confirms the isolated 103-byte gap between FUN_0044BF40 and
// FUN_0044C100, with no target xrefs/callers/callees or PCode.
// variants_tested=exact retail naked wrapper; IDA memset plus multibyte
// line-copy reconstruction; standard cdecl/fastcall declarations; and
// unsigned-char versus BYTE pointer/count spellings. The ordinary
// declarations cannot name EDX/ESI simultaneously, and no readable body was
// byte-measured without an LTCG context.
// next_lever=native-LTCG cluster with a synthetic caller that pins EDX/ESI
// and preserves the REP memset/source-loop shape; this region is still
// kind=asm in regions.json, so retain the exact wrapper in H2801.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C000..0x0044C066: FUN_0044c000
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c000_0044c000() {
    __asm {
    L_0044c000:
        push ebx
    L_0044c001:
        push ebp
    L_0044c002:
        mov ebp,dword ptr [esp+0Ch]
    L_0044c006:
        mov ecx,ebp
    L_0044c008:
        mov ebx,ecx
    L_0044c00a:
        shr ecx,2
    L_0044c00d:
        push edi
    L_0044c00e:
        xor eax,eax
    L_0044c010:
        mov edi,esi
    L_0044c012:
        rep stosd
    L_0044c014:
        mov ecx,ebx
    L_0044c016:
        and ecx,3
    L_0044c019:
        rep stosb
    L_0044c01b:
        mov al,byte ptr [edx]
    L_0044c01d:
        cmp al,0Ah
    L_0044c01f:
        je short L_0044c052
    L_0044c021:
        mov ecx,esi
    L_0044c023:
        cmp al,0Dh
    L_0044c025:
        je short L_0044c052
    L_0044c027:
        test ebp,ebp
    L_0044c029:
        je short L_0044c052
    L_0044c02b:
        mov byte ptr [ecx],al
    L_0044c02d:
        mov al,byte ptr [edx]
    L_0044c02f:
        inc ecx
    L_0044c030:
        cmp al,81h
    L_0044c032:
        jb short L_0044c038
    L_0044c034:
        cmp al,9Fh
    L_0044c036:
        jbe short L_0044c040
    L_0044c038:
        cmp al,0E0h
    L_0044c03a:
        jb short L_0044c048
    L_0044c03c:
        cmp al,0FCh
    L_0044c03e:
        ja short L_0044c048
    L_0044c040:
        mov al,byte ptr [edx+1]
    L_0044c043:
        inc edx
    L_0044c044:
        dec ebp
    L_0044c045:
        mov byte ptr [ecx],al
    L_0044c047:
        inc ecx
    L_0044c048:
        mov al,byte ptr [edx+1]
    L_0044c04b:
        inc edx
    L_0044c04c:
        dec ebp
    L_0044c04d:
        cmp al,0Ah
    L_0044c04f:
        jne short L_0044c023
    L_0044c051:
        inc edx
    L_0044c052:
        mov al,byte ptr [edx]
    L_0044c054:
        cmp al,0Ah
    L_0044c056:
        je short L_0044c05c
    L_0044c058:
        cmp al,0Dh
    L_0044c05a:
        jne short L_0044c05f
    L_0044c05c:
        inc edx
    L_0044c05d:
        jmp short L_0044c052
    L_0044c05f:
        pop edi
    L_0044c060:
        pop ebp
    L_0044c061:
        mov eax,edx
    L_0044c063:
        pop ebx
    L_0044c064:
        ret 4
    }
}
