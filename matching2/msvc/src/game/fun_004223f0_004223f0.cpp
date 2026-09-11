#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422150..0x004221DD: MainMenu_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.

// 0x004223F0..0x004224A2: FUN_004223f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004223f0_004223f0() {
    __asm {
    L_004223f0:
        mov eax,dword ptr [esi+4]
    L_004223f3:
        cmp eax,0Dh
    L_004223f6:
        ja short L_00422450
    L_004223f8:
        movzx eax,byte ptr [eax+4224B0h]
    L_004223ff:
        jmp dword ptr [eax*4+4224A4h]
    L_00422406:
        test byte ptr [data_00474ca0],20h
    L_0042240d:
        jne short L_00422450
    L_0042240f:
        test byte ptr [data_00474e36],8
    L_00422416:
        jne short L_00422421
    L_00422418:
        test byte ptr [data_00491ff4],10h
    L_0042241f:
        je short L_00422450
    L_00422421:
        mov ecx,dword ptr [data_00477810]
    L_00422427:
        mov eax,dword ptr [ecx+8]
    L_0042242a:
        test eax,eax
    L_0042242c:
        je short L_00422450
    L_0042242e:
        test byte ptr [eax+4],2
    L_00422432:
        je short L_00422450
    L_00422434:
        cmp dword ptr [ecx+14h],1Eh
    L_00422438:
        jl short L_00422450
    L_0042243a:
        push esi
    L_0042243b:
        call asm_FUN_00422ab0_00422ab0
    L_00422440:
        jmp short L_00422450
    L_00422442:
        push esi
    L_00422443:
        call asm_FUN_00422c80_00422c80
    L_00422448:
        jmp short L_00422450
    L_0042244a:
        push esi
    L_0042244b:
        call asm_FUN_004236f0_004236f0
    L_00422450:
        mov edx,dword ptr [esi+14h]
    L_00422453:
        mov ecx,dword ptr [esi+1Ch]
    L_00422456:
        mov dword ptr [esi+10h],edx
    L_00422459:
        fld dword ptr [ecx]
    L_0042245b:
        fcomp dword ptr [data_00470b68]
    L_00422461:
        fnstsw ax
    L_00422463:
        test ah,41h
    L_00422466:
        jne short L_0042248d
    L_00422468:
        fld dword ptr [ecx]
    L_0042246a:
        fcomp dword ptr [data_00470b64]
    L_00422470:
        fnstsw ax
    L_00422472:
        test ah,5
    L_00422475:
        jp short L_0042248d
    L_00422477:
        fld dword ptr [esi+18h]
    L_0042247a:
        inc edx
    L_0042247b:
        fadd dword ptr [data_00470afc]
    L_00422481:
        mov dword ptr [esi+14h],edx
    L_00422484:
        mov eax,1
    L_00422489:
        fstp dword ptr [esi+18h]
    L_0042248c:
        ret
    L_0042248d:
        fld dword ptr [ecx]
    L_0042248f:
        fadd dword ptr [esi+18h]
    L_00422492:
        fst dword ptr [esi+18h]
    L_00422495:
        call asm_FUN_00463b2c_00463b2c
    L_0042249a:
        mov dword ptr [esi+14h],eax
    L_0042249d:
        mov eax,1
    L_004224a2:
        ret
        _emit 0x90
        _emit 0x06
        _emit 0x24
        _emit 0x42
        _emit 0x00
        _emit 0x42
        _emit 0x24
        _emit 0x42
        _emit 0x00
        _emit 0x4a
        _emit 0x24
        _emit 0x42
        _emit 0x00
        _emit 0x00
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x01
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
        _emit 0x02
    }
}
