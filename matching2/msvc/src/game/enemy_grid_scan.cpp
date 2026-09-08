#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004073E0..0x004074A1: EnemyGrid_ScanCellsRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EnemyGrid_ScanCellsRetail_004073e0() {
    __asm {
    L_004073e0:
        push ecx
    L_004073e1:
        push ebx
    L_004073e2:
        mov ebx,eax
    L_004073e4:
        mov eax,dword ptr [data_00477834]
    L_004073e9:
        fld dword ptr [eax+3C0h]
    L_004073ef:
        push esi
    L_004073f0:
        fsub dword ptr [ebx+4]
    L_004073f3:
        fld dword ptr [eax+3C4h]
    L_004073f9:
        fsub dword ptr [ebx+8]
    L_004073fc:
        fld dword ptr [data_00470b04]
    L_00407402:
        fld st(1)
    L_00407404:
        fucompp
    L_00407406:
        fnstsw ax
    L_00407408:
        test ah,44h
    L_0040740b:
        jp short L_0040742c
    L_0040740d:
        fld dword ptr [data_00470b04]
    L_00407413:
        fld st(2)
    L_00407415:
        fucompp
    L_00407417:
        fnstsw ax
    L_00407419:
        test ah,44h
    L_0040741c:
        jp short L_0040742c
    L_0040741e:
        fstp st(0)
    L_00407420:
        mov dword ptr [esp+8],3FC90FDBh
    L_00407428:
        fstp st(0)
    L_0040742a:
        jmp short L_00407434
    L_0040742c:
        fxch
    L_0040742e:
        fpatan
    L_00407430:
        fstp dword ptr [esp+8]
    L_00407434:
        push edi
    L_00407435:
        xor edi,edi
    L_00407437:
        cmp word ptr [ebx+1F6h],di
    L_0040743e:
        jle short L_0040747a
    L_00407440:
        push ebp
    L_00407441:
        mov ebp,dword ptr [esp+10h]
    L_00407445:
        xor esi,esi
    L_00407447:
        cmp word ptr [ebx+1F4h],si
    L_0040744e:
        jle short L_0040746d
    L_00407450:
        mov eax,dword ptr [esp+18h]
    L_00407454:
        push ebp
    L_00407455:
        push edi
    L_00407456:
        push esi
    L_00407457:
        push eax
    L_00407458:
        call asm_FUN_004067d0_004067d0
    L_0040745d:
        test eax,eax
    L_0040745f:
        jne short L_00407479
    L_00407461:
        movsx ecx,word ptr [ebx+1F4h]
    L_00407468:
        inc esi
    L_00407469:
        cmp esi,ecx
    L_0040746b:
        jl short L_00407450
    L_0040746d:
        movsx edx,word ptr [ebx+1F6h]
    L_00407474:
        inc edi
    L_00407475:
        cmp edi,edx
    L_00407477:
        jl short L_00407445
    L_00407479:
        pop ebp
    L_0040747a:
        mov eax,dword ptr [ebx+1FCh]
    L_00407480:
        test ah,2
    L_00407483:
        pop edi
    L_00407484:
        je short L_0040749a
    L_00407486:
        mov eax,dword ptr [ebx+4]
    L_00407489:
        mov ebx,dword ptr [ebx+200h]
    L_0040748f:
        push eax
    L_00407490:
        mov esi,492590h
    L_00407495:
        call asm_FUN_0043dd10_0043dd10
    L_0040749a:
        pop esi
    L_0040749b:
        xor eax,eax
    L_0040749d:
        pop ebx
    L_0040749e:
        pop ecx
    L_0040749f:
        ret 4
    }
}
