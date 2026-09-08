#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046363A..0x004636A0: CatchIt
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CatchIt_0046363a() {
    __asm {
    L_0046363a:
        push ebp
    L_0046363b:
        mov ebp,esp
    L_0046363d:
        test ecx,ecx
    L_0046363f:
        je short L_0046364e
    L_00463641:
        push ebx
    L_00463642:
        push dword ptr [ebp+8]
    L_00463645:
        mov edx,esi
    L_00463647:
        call asm_BuildCatchObject_00463399
    L_0046364c:
        pop ecx
    L_0046364d:
        pop ecx
    L_0046364e:
        cmp dword ptr [ebp+1Ch],0
    L_00463652:
        push dword ptr [ebp+8]
    L_00463655:
        jne short L_0046365a
    L_00463657:
        push esi
    L_00463658:
        jmp short L_0046365d
    L_0046365a:
        push dword ptr [ebp+1Ch]
    L_0046365d:
        call asm_UnwindNestedFrames_0046271b
    L_00463662:
        push dword ptr [edi]
    L_00463664:
        push dword ptr [ebp+14h]
    L_00463667:
        push dword ptr [ebp+10h]
    L_0046366a:
        push esi
    L_0046366b:
        call asm_FrameUnwindToState_00462e7e
    L_00463670:
        mov eax,dword ptr [edi+4]
    L_00463673:
        push 100h
    L_00463678:
        push dword ptr [ebp+18h]
    L_0046367b:
        inc eax
    L_0046367c:
        push dword ptr [ebp+14h]
    L_0046367f:
        mov dword ptr [esi+8],eax
    L_00463682:
        push dword ptr [ebp+0Ch]
    L_00463685:
        mov ecx,dword ptr [ebx+0Ch]
    L_00463688:
        push esi
    L_00463689:
        push dword ptr [ebp+8]
    L_0046368c:
        call asm_CallCatchBlock_004631d5
    L_00463691:
        add esp,28h
    L_00463694:
        test eax,eax
    L_00463696:
        je short L_0046369f
    L_00463698:
        push esi
    L_00463699:
        push eax
    L_0046369a:
        call asm_JumpToContinuation_004626d6
    L_0046369f:
        pop ebp
    L_004636a0:
        ret
    }
}
