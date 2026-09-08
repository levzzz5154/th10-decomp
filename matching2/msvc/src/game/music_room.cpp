#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00426520..0x00426589: ParameterFile_LoadAndRelocateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ParameterFile_LoadAndRelocateRetail_00426520() {
    __asm {
    L_00426520:
        push 0
    L_00426522:
        push 0
    L_00426524:
        call asm_FUN_0044b360_0044b360
    L_00426529:
        test eax,eax
    L_0042652b:
        mov dword ptr [esi+45Ch],eax
    L_00426531:
        jne short L_00426537
    L_00426533:
        or eax,0FFFFFFFFh
    L_00426536:
        ret
    L_00426537:
        fld qword ptr [data_00470c50]
    L_0042653d:
        xor edx,edx
    L_0042653f:
        fsin
    L_00426541:
        fld st(0)
    L_00426543:
        fmul dword ptr [eax+10h]
    L_00426546:
        fstp dword ptr [eax+18h]
    L_00426549:
        mov eax,dword ptr [esi+45Ch]
    L_0042654f:
        fld st(0)
    L_00426551:
        fmul dword ptr [eax+14h]
    L_00426554:
        fstp dword ptr [eax+1Ch]
    L_00426557:
        mov eax,dword ptr [esi+45Ch]
    L_0042655d:
        fld st(0)
    L_0042655f:
        fmul dword ptr [eax+10h]
    L_00426562:
        fstp dword ptr [eax+18h]
    L_00426565:
        mov eax,dword ptr [esi+45Ch]
    L_0042656b:
        fmul dword ptr [eax+14h]
    L_0042656e:
        fstp dword ptr [eax+1Ch]
    L_00426571:
        mov eax,dword ptr [esi+45Ch]
    L_00426577:
        cmp word ptr [eax+2],dx
    L_0042657b:
        jbe asm_target_00426602
    L_00426581:
        push ebx
    L_00426582:
        mov ecx,110h
    L_00426587:
        push edi
    L_00426588:
        TH10_REL8(0xeb, 0x00426588, VA_asm_ParameterFile_LoadAndRelocateRetail_part_00426590)
    }
}

// 0x00426590..0x004265A8: ParameterFile_LoadAndRelocateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ParameterFile_LoadAndRelocateRetail_part_00426590() {
    __asm {
    L_00426590:
        mov eax,dword ptr [esi+45Ch]
    L_00426596:
        add dword ptr [ecx+eax],eax
    L_00426599:
        mov eax,dword ptr [esi+45Ch]
    L_0042659f:
        mov eax,dword ptr [ecx+eax]
    L_004265a2:
        cmp byte ptr [eax],0
    L_004265a5:
        TH10_REL8(0x7c, 0x004265a5, VA_asm_target_004265ee)
    L_004265a7:
        TH10_REL8(0xeb, 0x004265a7, VA_asm_ParameterFile_LoadAndRelocateRetail_part_004265b0)
    }
}

// 0x004265B0..0x00426604: ParameterFile_LoadAndRelocateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ParameterFile_LoadAndRelocateRetail_part_004265b0() {
    __asm {
    L_004265b0:
        mov edi,dword ptr [eax+24h]
    L_004265b3:
        mov edi,dword ptr [edi*4+47476Ch]
    L_004265ba:
        mov dword ptr [eax+24h],edi
    L_004265bd:
        mov edi,dword ptr [eax+28h]
    L_004265c0:
        mov edi,dword ptr [edi*4+474778h]
    L_004265c7:
        mov dword ptr [eax+28h],edi
    L_004265ca:
        mov edi,dword ptr [eax+2Ch]
    L_004265cd:
        mov edi,dword ptr [edi*4+491BF4h]
    L_004265d4:
        mov dword ptr [eax+2Ch],edi
    L_004265d7:
        mov edi,dword ptr [eax+30h]
    L_004265da:
        mov edi,dword ptr [edi*4+491BF8h]
    L_004265e1:
        mov dword ptr [eax+30h],edi
    L_004265e4:
        mov bl,byte ptr [eax+34h]
    L_004265e7:
        add eax,34h
    L_004265ea:
        test bl,bl
    L_004265ec:
        jge short L_004265b0
    L_004265ee:
        mov eax,dword ptr [esi+45Ch]
    L_004265f4:
        movzx eax,word ptr [eax+2]
    L_004265f8:
        inc edx
    L_004265f9:
        add ecx,8
    L_004265fc:
        cmp edx,eax
    L_004265fe:
        TH10_REL8(0x7c, 0x004265fe, VA_asm_ParameterFile_LoadAndRelocateRetail_part_00426590)
    L_00426600:
        pop edi
    L_00426601:
        pop ebx
    L_00426602:
        xor eax,eax
    L_00426604:
        ret
    }
}
