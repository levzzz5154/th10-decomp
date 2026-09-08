#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BED0..0x0045BF2F: _memset
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memset_0045bed0() {
    __asm {
    L_0045bed0:
        mov edx,dword ptr [esp+0Ch]
    L_0045bed4:
        mov ecx,dword ptr [esp+4]
    L_0045bed8:
        test edx,edx
    L_0045beda:
        je short L_0045bf2b
    L_0045bedc:
        xor eax,eax
    L_0045bede:
        mov al,byte ptr [esp+8]
    L_0045bee2:
        push edi
    L_0045bee3:
        mov edi,ecx
    L_0045bee5:
        cmp edx,4
    L_0045bee8:
        jb short L_0045bf1b
    L_0045beea:
        neg ecx
    L_0045beec:
        and ecx,3
    L_0045beef:
        je short L_0045befd
    L_0045bef1:
        sub edx,ecx
    L_0045bef3:
        mov byte ptr [edi],al
    L_0045bef5:
        add edi,1
    L_0045bef8:
        sub ecx,1
    L_0045befb:
        jne short L_0045bef3
    L_0045befd:
        mov ecx,eax
    L_0045beff:
        shl eax,8
    L_0045bf02:
        add eax,ecx
    L_0045bf04:
        mov ecx,eax
    L_0045bf06:
        shl eax,10h
    L_0045bf09:
        add eax,ecx
    L_0045bf0b:
        mov ecx,edx
    L_0045bf0d:
        and edx,3
    L_0045bf10:
        shr ecx,2
    L_0045bf13:
        je short L_0045bf1b
    L_0045bf15:
        rep stosd
    L_0045bf17:
        test edx,edx
    L_0045bf19:
        je short L_0045bf25
    L_0045bf1b:
        mov byte ptr [edi],al
    L_0045bf1d:
        add edi,1
    L_0045bf20:
        sub edx,1
    L_0045bf23:
        jne short L_0045bf1b
    L_0045bf25:
        mov eax,dword ptr [esp+8]
    L_0045bf29:
        pop edi
    L_0045bf2a:
        ret
    L_0045bf2b:
        mov eax,dword ptr [esp+4]
    L_0045bf2f:
        ret
    }
}
