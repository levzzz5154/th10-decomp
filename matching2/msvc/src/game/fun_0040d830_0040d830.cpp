#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040D830..0x0040DAD0: FUN_0040d830
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040d830_0040d830() {
    __asm {
    L_0040d830:
        push ebx
    L_0040d831:
        push ebp
    L_0040d832:
        push edi
    L_0040d833:
        xor ebx,ebx
    L_0040d835:
        lea edi,[esi+103Ch]
    L_0040d83b:
        mov dword ptr [esi+1010h],ebx
    L_0040d841:
        mov dword ptr [esi+1014h],ebx
    L_0040d847:
        mov edx,edi
    L_0040d849:
        mov dword ptr [esi],46D0C0h
    L_0040d84f:
        call asm_Entity_ClearAnims_0040cc70
    L_0040d854:
        xor eax,eax
    L_0040d856:
        mov ecx,537h
    L_0040d85b:
        rep stosd
    L_0040d85d:
        mov ecx,dword ptr [esi+1028h]
    L_0040d863:
        mov dword ptr [esi+8],ebx
    L_0040d866:
        mov dword ptr [esi+0Ch],ebx
    L_0040d869:
        mov dword ptr [esi+101Ch],esi
    L_0040d86f:
        and ecx,0FFFFFFFEh
    L_0040d872:
        mov dword ptr [esi+1028h],ecx
    L_0040d878:
        mov dword ptr [esi+1020h],ebx
    L_0040d87e:
        lea eax,[esi+8]
    L_0040d881:
        mov dword ptr [esi+4],eax
    L_0040d884:
        or ebp,0FFFFFFFFh
    L_0040d887:
        mov dword ptr [esi+1018h],ebp
    L_0040d88d:
        mov dword ptr [esi+1030h],eax
    L_0040d893:
        mov dword ptr [esi+1034h],ebx
    L_0040d899:
        mov dword ptr [esi+1038h],ebx
    L_0040d89f:
        mov dword ptr [esi+2514h],esi
    L_0040d8a5:
        mov dword ptr [esi+11BCh],ebx
    L_0040d8ab:
        mov dword ptr [esi+1208h],ebx
    L_0040d8b1:
        mov dword ptr [esi+1244h],ebx
    L_0040d8b7:
        mov dword ptr [esi+1280h],ebx
    L_0040d8bd:
        mov dword ptr [esi+12BCh],ebx
    L_0040d8c3:
        mov dword ptr [esi+12F8h],ebx
    L_0040d8c9:
        xor eax,eax
    L_0040d8cb:
        mov ecx,0Bh
    L_0040d8d0:
        lea edi,[esi+10C0h]
    L_0040d8d6:
        rep stosd
    L_0040d8d8:
        mov ecx,0Bh
    L_0040d8dd:
        lea edi,[esi+1094h]
    L_0040d8e3:
        rep stosd
    L_0040d8e5:
        mov ecx,0Bh
    L_0040d8ea:
        lea edi,[esi+1068h]
    L_0040d8f0:
        rep stosd
    L_0040d8f2:
        mov eax,41C00000h
    L_0040d8f7:
        mov dword ptr [esi+10ECh],eax
    L_0040d8fd:
        mov dword ptr [esi+10F0h],eax
    L_0040d903:
        mov dword ptr [esi+10F4h],eax
    L_0040d909:
        mov dword ptr [esi+10F8h],eax
    L_0040d90f:
        mov dword ptr [esi+248Ch],ebp
    L_0040d915:
        lea edx,[esi+2408h]
    L_0040d91b:
        xor eax,eax
    L_0040d91d:
        mov dword ptr [esi+116Ch],esi
    L_0040d923:
        mov dword ptr [esi+1170h],ebx
    L_0040d929:
        mov dword ptr [esi+1174h],ebx
    L_0040d92f:
        mov edi,edx
    L_0040d931:
        mov ecx,0Fh
    L_0040d936:
        rep stosd
    L_0040d938:
        mov eax,42000000h
    L_0040d93d:
        mov dword ptr [edx+38h],eax
    L_0040d940:
        mov dword ptr [edx+34h],eax
    L_0040d943:
        mov eax,dword ptr [esi+1168h]
    L_0040d949:
        test al,1
    L_0040d94b:
        mov edx,0FFF0BDC1h
    L_0040d950:
        mov ecx,476F78h
    L_0040d955:
        jne short L_0040d978
    L_0040d957:
        or eax,1
    L_0040d95a:
        mov dword ptr [esi+115Ch],ebx
    L_0040d960:
        mov dword ptr [esi+1158h],edx
    L_0040d966:
        mov dword ptr [esi+1160h],ebx
    L_0040d96c:
        mov dword ptr [esi+1164h],ecx
    L_0040d972:
        mov dword ptr [esi+1168h],eax
    L_0040d978:
        mov dword ptr [esi+115Ch],ebx
    L_0040d97e:
        mov dword ptr [esi+1160h],ebx
    L_0040d984:
        mov dword ptr [esi+1158h],ebp
    L_0040d98a:
        mov eax,dword ptr [esi+2468h]
    L_0040d990:
        test al,1
    L_0040d992:
        jne short L_0040d9b5
    L_0040d994:
        or eax,1
    L_0040d997:
        mov dword ptr [esi+245Ch],ebx
    L_0040d99d:
        mov dword ptr [esi+2458h],edx
    L_0040d9a3:
        mov dword ptr [esi+2460h],ebx
    L_0040d9a9:
        mov dword ptr [esi+2464h],ecx
    L_0040d9af:
        mov dword ptr [esi+2468h],eax
    L_0040d9b5:
        mov dword ptr [esi+245Ch],ebx
    L_0040d9bb:
        mov dword ptr [esi+2460h],ebx
    L_0040d9c1:
        mov dword ptr [esi+2458h],ebp
    L_0040d9c7:
        mov eax,dword ptr [esi+247Ch]
    L_0040d9cd:
        test al,1
    L_0040d9cf:
        jne short L_0040d9f2
    L_0040d9d1:
        or eax,1
    L_0040d9d4:
        mov dword ptr [esi+2470h],ebx
    L_0040d9da:
        mov dword ptr [esi+246Ch],edx
    L_0040d9e0:
        mov dword ptr [esi+2474h],ebx
    L_0040d9e6:
        mov dword ptr [esi+2478h],ecx
    L_0040d9ec:
        mov dword ptr [esi+247Ch],eax
    L_0040d9f2:
        mov eax,dword ptr [data_00477704]
    L_0040d9f7:
        mov ecx,dword ptr [esp+10h]
    L_0040d9fb:
        mov dword ptr [esi+2470h],ebx
    L_0040da01:
        mov dword ptr [esi+2474h],ebx
    L_0040da07:
        mov dword ptr [esi+246Ch],ebp
    L_0040da0d:
        mov eax,dword ptr [eax+54h]
    L_0040da10:
        push ecx
    L_0040da11:
        mov dword ptr [esi+102Ch],eax
    L_0040da17:
        call asm_FUN_00450470_00450470
    L_0040da1c:
        mov edx,dword ptr [esi+4]
    L_0040da1f:
        mov dword ptr [edx+4],eax
    L_0040da22:
        mov eax,dword ptr [esi+4]
    L_0040da25:
        mov dword ptr [eax],ebx
    L_0040da27:
        mov dword ptr [esi+23FCh],ebx
    L_0040da2d:
        mov dword ptr [esi+2400h],ebx
    L_0040da33:
        mov dword ptr [esi+2404h],ebx
    L_0040da39:
        pop edi
    L_0040da3a:
        mov dword ptr [esi+2494h],ebp
    L_0040da40:
        mov dword ptr [esi+2498h],ebp
    L_0040da46:
        mov dword ptr [esi+24A4h],ebp
    L_0040da4c:
        mov dword ptr [esi+24A8h],ebp
    L_0040da52:
        mov dword ptr [esi+24B4h],ebp
    L_0040da58:
        mov dword ptr [esi+24B8h],ebp
    L_0040da5e:
        mov dword ptr [esi+24C4h],ebp
    L_0040da64:
        mov dword ptr [esi+24C8h],ebp
    L_0040da6a:
        mov dword ptr [esi+24D4h],ebp
    L_0040da70:
        mov dword ptr [esi+24D8h],ebp
    L_0040da76:
        mov dword ptr [esi+24E4h],ebp
    L_0040da7c:
        mov dword ptr [esi+24E8h],ebp
    L_0040da82:
        mov dword ptr [esi+24F4h],ebp
    L_0040da88:
        mov dword ptr [esi+24F8h],ebp
    L_0040da8e:
        mov dword ptr [esi+2504h],ebp
    L_0040da94:
        mov dword ptr [esi+2508h],ebp
    L_0040da9a:
        pop ebp
    L_0040da9b:
        mov dword ptr [esi+249Ch],ebx
    L_0040daa1:
        mov dword ptr [esi+24ACh],ebx
    L_0040daa7:
        mov dword ptr [esi+24BCh],ebx
    L_0040daad:
        mov dword ptr [esi+24CCh],ebx
    L_0040dab3:
        mov dword ptr [esi+24DCh],ebx
    L_0040dab9:
        mov dword ptr [esi+24ECh],ebx
    L_0040dabf:
        mov dword ptr [esi+24FCh],ebx
    L_0040dac5:
        mov dword ptr [esi+250Ch],ebx
    L_0040dacb:
        mov eax,esi
    L_0040dacd:
        pop ebx
    L_0040dace:
        ret 4
    }
}
