#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3306): closest_byte_count=0/132; first_diff=0x00401530
// residual_class=private ECX game-thread receiver, EAX string input, and EBX
// three-word vector input.
// variants_tested=readable three-argument cdecl candidate (136-byte extent;
// disassembly compared against 132-byte retail body) and semantic copy loop.
// next_lever=real callers 0x00401630 and 0x00401690 plus this callee in one
// native-LTCG cluster so MSVC can recover the private register convention.

// 0x00401530..0x004015B3: ?GameThread_AppendRecord@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_AppendRecord_00401530() {
    __asm {
    L_00401530:
        mov edx,dword ptr [ecx+896Ch]
    L_00401536:
        cmp edx,100h
    L_0040153c:
        push esi
    L_0040153d:
        mov esi,eax
    L_0040153f:
        jge short L_004015b2
    L_00401541:
        mov eax,edx
    L_00401543:
        imul eax,68h
    L_00401546:
        push edi
    L_00401547:
        lea eax,[eax+ecx+76Ch]
    L_0040154e:
        inc edx
    L_0040154f:
        mov edi,eax
    L_00401551:
        mov dword ptr [ecx+896Ch],edx
    L_00401557:
        sub edi,esi
    L_00401559:
        lea esp,[esp+force_disp32_zero]
    L_00401560:
        mov dl,byte ptr [esi]
    L_00401562:
        mov byte ptr [edi+esi],dl
    L_00401565:
        inc esi
    L_00401566:
        test dl,dl
    L_00401568:
        jne short L_00401560
    L_0040156a:
        mov esi,dword ptr [ebx]
    L_0040156c:
        lea edx,[eax+40h]
    L_0040156f:
        mov dword ptr [edx],esi
    L_00401571:
        mov esi,dword ptr [ebx+4]
    L_00401574:
        mov dword ptr [edx+4],esi
    L_00401577:
        mov esi,dword ptr [ebx+8]
    L_0040157a:
        mov dword ptr [edx+8],esi
    L_0040157d:
        mov edx,dword ptr [ecx+8974h]
    L_00401583:
        mov dword ptr [eax+4Ch],edx
    L_00401586:
        mov edx,dword ptr [ecx+8978h]
    L_0040158c:
        mov dword ptr [eax+50h],edx
    L_0040158f:
        mov edx,dword ptr [ecx+897Ch]
    L_00401595:
        mov dword ptr [eax+54h],edx
    L_00401598:
        mov edx,dword ptr [ecx+8980h]
    L_0040159e:
        mov dword ptr [eax+5Ch],edx
    L_004015a1:
        mov dword ptr [eax+60h],0
    L_004015a8:
        mov ecx,dword ptr [ecx+8988h]
    L_004015ae:
        mov dword ptr [eax+64h],ecx
    L_004015b1:
        pop edi
    L_004015b2:
        pop esi
    L_004015b3:
        ret
    }
}
