#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A750..0x0043A903: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a750() {
    __asm {
    L_0043a750:
        push 8
    L_0043a752:
        lea eax,[esi+8]
    L_0043a755:
        push eax
    L_0043a756:
        mov dword ptr [esi],46F810h
    L_0043a75c:
        call dword ptr [data_00466290]
    L_0043a762:
        mov dword ptr [esi],46F80Ch
    L_0043a768:
        xor ecx,ecx
    L_0043a76a:
        xor eax,eax
    L_0043a76c:
        mov dword ptr [esi+4],eax
    L_0043a76f:
        mov dword ptr [esi+13Ch],eax
    L_0043a775:
        mov dword ptr [esi+140h],eax
    L_0043a77b:
        mov dword ptr [esi+138h],eax
    L_0043a781:
        mov dword ptr [esi+120h],eax
    L_0043a787:
        mov dword ptr [esi+124h],eax
    L_0043a78d:
        mov dword ptr [esi+118h],eax
    L_0043a793:
        mov byte ptr [esi+2C4h],al
    L_0043a799:
        mov dword ptr [esi+2C8h],eax
    L_0043a79f:
        mov dword ptr [esi+2CCh],eax
    L_0043a7a5:
        mov dword ptr [esi+2D0h],eax
    L_0043a7ab:
        mov dword ptr [esi+2D4h],eax
    L_0043a7b1:
        mov dword ptr [esi+2D8h],eax
    L_0043a7b7:
        mov dword ptr [esi+2DCh],eax
    L_0043a7bd:
        mov dword ptr [esi+2E0h],eax
    L_0043a7c3:
        mov dword ptr [esi+98h],ecx
    L_0043a7c9:
        mov dword ptr [esi+9Ch],ecx
    L_0043a7cf:
        mov dword ptr [esi+0A0h],ecx
    L_0043a7d5:
        mov dword ptr [esi+0A4h],ecx
    L_0043a7db:
        mov dword ptr [esi+0A8h],ecx
    L_0043a7e1:
        mov dword ptr [esi+0ACh],ecx
    L_0043a7e7:
        mov dword ptr [esi+0B0h],ecx
    L_0043a7ed:
        mov dword ptr [esi+0B4h],ecx
    L_0043a7f3:
        mov dword ptr [esi+0B8h],ecx
    L_0043a7f9:
        mov dword ptr [esi+0BCh],ecx
    L_0043a7ff:
        mov dword ptr [esi+0C0h],ecx
    L_0043a805:
        mov dword ptr [esi+0C4h],ecx
    L_0043a80b:
        mov dword ptr [esi+0C8h],ecx
    L_0043a811:
        mov dword ptr [esi+0CCh],ecx
    L_0043a817:
        mov dword ptr [esi+0D0h],ecx
    L_0043a81d:
        mov dword ptr [esi+0D4h],ecx
    L_0043a823:
        mov dword ptr [esi+0D8h],ecx
    L_0043a829:
        mov dword ptr [esi+0DCh],ecx
    L_0043a82f:
        mov dword ptr [esi+0E0h],ecx
    L_0043a835:
        mov dword ptr [esi+0E4h],ecx
    L_0043a83b:
        mov dword ptr [esi+0E8h],ecx
    L_0043a841:
        mov dword ptr [esi+0ECh],ecx
    L_0043a847:
        mov dword ptr [esi+0F0h],ecx
    L_0043a84d:
        mov dword ptr [esi+0F4h],ecx
    L_0043a853:
        mov dword ptr [esi+0F8h],ecx
    L_0043a859:
        mov dword ptr [esi+0FCh],ecx
    L_0043a85f:
        mov dword ptr [esi+100h],ecx
    L_0043a865:
        mov dword ptr [esi+104h],ecx
    L_0043a86b:
        mov dword ptr [esi+108h],ecx
    L_0043a871:
        mov dword ptr [esi+10Ch],ecx
    L_0043a877:
        mov dword ptr [esi+110h],ecx
    L_0043a87d:
        xor edx,edx
    L_0043a87f:
        mov dword ptr [esi+114h],ecx
    L_0043a885:
        mov dword ptr [esi+14h],edx
    L_0043a888:
        mov dword ptr [esi+18h],edx
    L_0043a88b:
        mov dword ptr [esi+1Ch],edx
    L_0043a88e:
        mov dword ptr [esi+20h],edx
    L_0043a891:
        mov dword ptr [esi+24h],edx
    L_0043a894:
        mov dword ptr [esi+28h],edx
    L_0043a897:
        mov dword ptr [esi+2Ch],edx
    L_0043a89a:
        mov dword ptr [esi+30h],edx
    L_0043a89d:
        mov dword ptr [esi+34h],edx
    L_0043a8a0:
        mov dword ptr [esi+38h],edx
    L_0043a8a3:
        mov dword ptr [esi+3Ch],edx
    L_0043a8a6:
        mov dword ptr [esi+40h],edx
    L_0043a8a9:
        mov dword ptr [esi+44h],edx
    L_0043a8ac:
        mov dword ptr [esi+48h],edx
    L_0043a8af:
        mov dword ptr [esi+4Ch],edx
    L_0043a8b2:
        mov dword ptr [esi+50h],edx
    L_0043a8b5:
        mov dword ptr [esi+54h],edx
    L_0043a8b8:
        mov dword ptr [esi+58h],edx
    L_0043a8bb:
        mov dword ptr [esi+5Ch],edx
    L_0043a8be:
        mov dword ptr [esi+60h],edx
    L_0043a8c1:
        mov dword ptr [esi+64h],edx
    L_0043a8c4:
        mov dword ptr [esi+68h],edx
    L_0043a8c7:
        mov dword ptr [esi+6Ch],edx
    L_0043a8ca:
        mov dword ptr [esi+70h],edx
    L_0043a8cd:
        mov dword ptr [esi+74h],edx
    L_0043a8d0:
        mov dword ptr [esi+78h],edx
    L_0043a8d3:
        mov dword ptr [esi+7Ch],edx
    L_0043a8d6:
        mov dword ptr [esi+80h],edx
    L_0043a8dc:
        mov dword ptr [esi+84h],edx
    L_0043a8e2:
        mov dword ptr [esi+88h],edx
    L_0043a8e8:
        mov dword ptr [esi+8Ch],edx
    L_0043a8ee:
        mov dword ptr [esi+90h],edx
    L_0043a8f4:
        mov dword ptr [esi+94h],eax
    L_0043a8fa:
        mov dword ptr [esi+10h],0FFFFFFFFh
    L_0043a901:
        mov eax,esi
    L_0043a903:
        ret
    }
}
