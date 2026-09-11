#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004493E0..0x00449417: ?AnimationManager_MarkResourceForRemoval@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_MarkResourceForRemoval_004493e0() {
    __asm {
    L_004493e0:
        push esi
    L_004493e1:
        mov esi,eax
    L_004493e3:
        mov eax,dword ptr [esi+72DAD4h]
    L_004493e9:
        test eax,eax
    L_004493eb:
        push edi
    L_004493ec:
        mov edi,4000000h
    L_004493f1:
        je short L_0044940c
    L_004493f3:
        mov ecx,dword ptr [eax+4]
    L_004493f6:
        mov eax,dword ptr [eax]
    L_004493f8:
        cmp dword ptr [eax+308h],edx
    L_004493fe:
        jne short L_00449406
    L_00449400:
        or dword ptr [eax+35Ch],edi
    L_00449406:
        test ecx,ecx
    L_00449408:
        mov eax,ecx
    L_0044940a:
        jne short L_004493f3
    L_0044940c:
        mov eax,dword ptr [esi+72DADCh]
    L_00449412:
        test eax,eax
    L_00449414:
        TH10_REL8(0x74, 0x00449414, VA_asm_target_00449439)
    L_00449416:
        TH10_REL8(0xeb, 0x00449416, VA_asm_AnimationManager_MarkResourceForRemoval_part_00449420)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_00449420:
        mov ecx,dword ptr [eax+4]
    L_00449423:
        mov eax,dword ptr [eax]
    L_00449425:
        cmp dword ptr [eax+308h],edx
    L_0044942b:
        jne short L_00449433
    L_0044942d:
        or dword ptr [eax+35Ch],edi
    L_00449433:
        test ecx,ecx
    L_00449435:
        mov eax,ecx
    L_00449437:
        jne short L_00449420
    L_00449439:
        pop edi
    L_0044943a:
        pop esi
    L_0044943b:
        ret
    }
}
