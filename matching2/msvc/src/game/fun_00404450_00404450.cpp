#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x00404450..0x004044B4: FUN_00404450
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00404450_00404450() {
    __asm {
    L_00404450:
        push ecx
    L_00404451:
        push ebx
    L_00404452:
        push ebp
    L_00404453:
        mov ebp,dword ptr [esp+10h]
    L_00404457:
        mov eax,dword ptr [ebp+8]
    L_0040445a:
        mov ebx,dword ptr [eax+4]
    L_0040445d:
        mov ecx,2
    L_00404462:
        or ebx,ecx
    L_00404464:
        mov dword ptr [eax+4],ebx
    L_00404467:
        mov eax,dword ptr [ebp+0Ch]
    L_0040446a:
        push esi
    L_0040446b:
        push edi
    L_0040446c:
        or dword ptr [eax+4],ecx
    L_0040446f:
        mov eax,dword ptr [ebp+2A40h]
    L_00404475:
        or dword ptr [eax+4],ecx
    L_00404478:
        mov ecx,dword ptr [ebp+10h]
    L_0040447b:
        xor eax,eax
    L_0040447d:
        cmp word ptr [ecx],ax
    L_00404480:
        mov dword ptr [esp+18h],eax
    L_00404484:
        mov dword ptr [esp+10h],eax
    L_00404488:
        jle asm_target_00404518
    L_0040448e:
        mov edi,edi
    L_00404490:
        mov edx,dword ptr [ebp+14h]
    L_00404493:
        mov ecx,dword ptr [edx+eax*4]
    L_00404496:
        mov byte ptr [ecx+3],1
    L_0040449a:
        mov edx,dword ptr [ebp+14h]
    L_0040449d:
        mov edi,dword ptr [edx+eax*4]
    L_004044a0:
        add edi,1Ch
    L_004044a3:
        cmp word ptr [edi],0
    L_004044a7:
        TH10_REL8(0x7c, 0x004044a7, VA_asm_target_004044fb)
    L_004044a9:
        mov ebx,dword ptr [esp+18h]
    L_004044ad:
        imul ebx,3ACh
    L_004044b3:
        TH10_REL8(0xeb, 0x004044b3, VA_asm_FUN_00404450_part_004044c0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00

    L_004044c0:
        mov esi,dword ptr [ebp+17Ch]
    L_004044c6:
        mov ecx,dword ptr [ebp+178h]
    L_004044cc:
        movsx eax,word ptr [edi+4]
    L_004044d0:
        add esi,ebx
    L_004044d2:
        push ecx
    L_004044d3:
        call asm_FUN_00404f30_00404f30
    L_004044d8:
        mov eax,dword ptr [esp+18h]
    L_004044dc:
        movsx edx,word ptr [edi+2]
    L_004044e0:
        mov word ptr [edi+6],ax
    L_004044e4:
        inc eax
    L_004044e5:
        add edi,edx
    L_004044e7:
        add ebx,3ACh
    L_004044ed:
        cmp word ptr [edi],0
    L_004044f1:
        mov dword ptr [esp+18h],eax
    L_004044f5:
        jge short L_004044c0
    L_004044f7:
        mov eax,dword ptr [esp+10h]
    L_004044fb:
        mov ecx,dword ptr [ebp+10h]
    L_004044fe:
        movsx edx,word ptr [ecx]
    L_00404501:
        inc eax
    L_00404502:
        cmp eax,edx
    L_00404504:
        mov dword ptr [esp+10h],eax
    L_00404508:
        TH10_REL8(0x7c, 0x00404508, VA_asm_target_00404490)
    L_0040450a:
        mov eax,dword ptr [ebp+1Ch]
    L_0040450d:
        pop edi
    L_0040450e:
        pop esi
    L_0040450f:
        mov dword ptr [ebp+4Ch],eax
    L_00404512:
        pop ebp
    L_00404513:
        pop ebx
    L_00404514:
        pop ecx
    L_00404515:
        ret 4
    L_00404518:
        mov ecx,dword ptr [ebp+1Ch]
    L_0040451b:
        pop edi
    L_0040451c:
        pop esi
    L_0040451d:
        mov dword ptr [ebp+4Ch],ecx
    L_00404520:
        pop ebp
    L_00404521:
        pop ebx
    L_00404522:
        pop ecx
    L_00404523:
        ret 4
    }
}
