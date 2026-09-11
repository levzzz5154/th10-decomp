#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x0043E460..0x0043E46C: ?AnimationManager_RegisterResource@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_RegisterResource_0043e460() {
    __asm {
    L_0043e460:
        push esi
    L_0043e461:
        mov esi,eax
    L_0043e463:
        xor eax,eax
    L_0043e465:
        lea ecx,[esi+1F88h]
    L_0043e46b:
        TH10_REL8(0xeb, 0x0043e46b, VA_asm_AnimationManager_RegisterResource_part_0043e470)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0043e470:
        cmp dword ptr [ecx],0
    L_0043e473:
        je short L_0043e485
    L_0043e475:
        inc eax
    L_0043e476:
        add ecx,10Ch
    L_0043e47c:
        cmp eax,1Fh
    L_0043e47f:
        jl short L_0043e470
    L_0043e481:
        pop esi
    L_0043e482:
        ret 8
    L_0043e485:
        imul eax,10Ch
    L_0043e48b:
        lea ecx,[eax+esi]
    L_0043e48e:
        mov eax,dword ptr [esp+8]
    L_0043e492:
        mov dword ptr [ecx+1F88h],eax
    L_0043e498:
        mov eax,dword ptr [esp+0Ch]
    L_0043e49c:
        lea esi,[ecx+1F94h]
    L_0043e4a2:
        mov dword ptr [ecx+1F8Ch],eax
    L_0043e4a8:
        mov eax,edx
    L_0043e4aa:
        sub esi,edx
    L_0043e4ac:
        TH10_NOP_LEA_ESP_DISP8()
    L_0043e4b0:
        mov dl,byte ptr [eax]
    L_0043e4b2:
        mov byte ptr [esi+eax],dl
    L_0043e4b5:
        inc eax
    L_0043e4b6:
        test dl,dl
    L_0043e4b8:
        jne short L_0043e4b0
    L_0043e4ba:
        mov dword ptr [ecx+1F90h],0
    L_0043e4c4:
        pop esi
    L_0043e4c5:
        ret 8
    }
}
