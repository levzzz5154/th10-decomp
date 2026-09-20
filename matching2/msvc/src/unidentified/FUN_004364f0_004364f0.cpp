// BLOCKED (H2701): closest_byte_count=107; first_diff=0x0043650E;
// residual_class=allocator: the BufferFile::Seek readable candidate preserves
// the retail 107-byte extent and control flow, but MSVC chooses EDX for the
// backward-origin base/limit compare where retail holds the base in ESI.
// variants_tested=48 materially different BufferFile::Seek switch variants
// (all six origin orders and break versus return-failure exits), including
// the tree/goto source shape recorded in memory-file-recovery/seek.cpp; the
// closest candidate still diverges at 0x0043650E.
// next_lever=force the backward-origin base value to remain live in ESI with
// a faithful alias/source boundary or a register-allocation compiler lever;
// retain the exact wrapper until that single allocator residual is removed.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004364F0..0x0043655A: FUN_004364f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004364f0_004364f0() {
    __asm {
    L_004364f0:
        mov eax,dword ptr [esp+8]
    L_004364f4:
        sub eax,0
    L_004364f7:
        push esi
    L_004364f8:
        je short L_00436540
    L_004364fa:
        dec eax
    L_004364fb:
        je short L_00436525
    L_004364fd:
        dec eax
    L_004364fe:
        jne short L_0043653a
    L_00436500:
        mov edx,dword ptr [esp+8]
    L_00436504:
        test edx,edx
    L_00436506:
        jg short L_0043653a
    L_00436508:
        mov eax,edx
    L_0043650a:
        jge short L_0043650e
    L_0043650c:
        neg eax
    L_0043650e:
        mov esi,dword ptr [ecx+4]
    L_00436511:
        cmp eax,esi
    L_00436513:
        jae short L_0043653a
    L_00436515:
        mov eax,dword ptr [ecx+0Ch]
    L_00436518:
        add eax,esi
    L_0043651a:
        add eax,edx
    L_0043651c:
        mov dword ptr [ecx+8],eax
    L_0043651f:
        mov al,1
    L_00436521:
        pop esi
    L_00436522:
        ret 8
    L_00436525:
        mov edx,dword ptr [ecx+4]
    L_00436528:
        mov esi,dword ptr [ecx+0Ch]
    L_0043652b:
        mov eax,dword ptr [ecx+8]
    L_0043652e:
        add esi,edx
    L_00436530:
        mov edx,dword ptr [esp+8]
    L_00436534:
        sub esi,eax
    L_00436536:
        cmp esi,edx
    L_00436538:
        jg short L_0043651a
    L_0043653a:
        xor al,al
    L_0043653c:
        pop esi
    L_0043653d:
        ret 8
    L_00436540:
        mov eax,dword ptr [esp+8]
    L_00436544:
        test eax,eax
    L_00436546:
        jl short L_0043653a
    L_00436548:
        cmp eax,dword ptr [ecx+4]
    L_0043654b:
        jae short L_0043653a
    L_0043654d:
        mov edx,dword ptr [ecx+0Ch]
    L_00436550:
        add edx,eax
    L_00436552:
        mov dword ptr [ecx+8],edx
    L_00436555:
        mov al,1
    L_00436557:
        pop esi
    L_00436558:
        ret 8
    }
}
