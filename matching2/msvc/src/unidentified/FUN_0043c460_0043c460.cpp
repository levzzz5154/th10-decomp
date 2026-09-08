#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C460..0x0043C4F9: FUN_0043c460
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c460_0043c460() {
    __asm {
    L_0043c460:
        mov eax,dword ptr [data_004918a4]
    L_0043c465:
        sub esp,8
    L_0043c468:
        test eax,eax
    L_0043c46a:
        push esi
    L_0043c46b:
        mov esi,ecx
    L_0043c46d:
        push edi
    L_0043c46e:
        movzx edi,byte ptr [esi+27h]
    L_0043c472:
        jne short L_0043c4d5
    L_0043c474:
        mov eax,dword ptr [esi+1Ch]
    L_0043c477:
        cmp dword ptr [esi+34h],eax
    L_0043c47a:
        mov dword ptr [esp+8],eax
    L_0043c47e:
        jge short L_0043c4c1
    L_0043c480:
        test edi,edi
    L_0043c482:
        mov dword ptr [esp+0Ch],edi
    L_0043c486:
        fild dword ptr [esp+0Ch]
    L_0043c48a:
        jge short L_0043c492
    L_0043c48c:
        fadd dword ptr [data_00470b98]
    L_0043c492:
        fmul dword ptr [esi+38h]
    L_0043c495:
        fidiv dword ptr [esp+8]
    L_0043c499:
        call asm_FUN_00463b2c_00463b2c
    L_0043c49e:
        mov ecx,edi
    L_0043c4a0:
        sub ecx,eax
    L_0043c4a2:
        mov dword ptr [esi+18h],ecx
    L_0043c4a5:
        jns short L_0043c4e7
    L_0043c4a7:
        mov dword ptr [esi+18h],0
    L_0043c4ae:
        add esi,30h
    L_0043c4b1:
        call asm_FrameTimer_Tick_00404ed0
    L_0043c4b6:
        pop edi
    L_0043c4b7:
        mov eax,1
    L_0043c4bc:
        pop esi
    L_0043c4bd:
        add esp,8
    L_0043c4c0:
        ret
    L_0043c4c1:
        mov ecx,dword ptr [esi+20h]
    L_0043c4c4:
        dec ecx
    L_0043c4c5:
        mov eax,ecx
    L_0043c4c7:
        test eax,eax
    L_0043c4c9:
        mov dword ptr [esi+18h],0
    L_0043c4d0:
        mov dword ptr [esi+20h],ecx
    L_0043c4d3:
        jg short L_0043c4dd
    L_0043c4d5:
        pop edi
    L_0043c4d6:
        xor eax,eax
    L_0043c4d8:
        pop esi
    L_0043c4d9:
        add esp,8
    L_0043c4dc:
        ret
    L_0043c4dd:
        push 0
    L_0043c4df:
        lea eax,[esi+30h]
    L_0043c4e2:
        call asm_Player_SetSchedulerValue_00405410
    L_0043c4e7:
        add esi,30h
    L_0043c4ea:
        call asm_FrameTimer_Tick_00404ed0
    L_0043c4ef:
        pop edi
    L_0043c4f0:
        mov eax,1
    L_0043c4f5:
        pop esi
    L_0043c4f6:
        add esp,8
    L_0043c4f9:
        ret
    }
}
