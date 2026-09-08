#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041E5C0..0x0041E6F4: FUN_0041e5c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041e5c0_0041e5c0() {
    __asm {
    L_0041e5c0:
        mov edx,dword ptr [data_0047781c]
    L_0041e5c6:
        push ebx
    L_0041e5c7:
        push ebp
    L_0041e5c8:
        mov ebp,ecx
    L_0041e5ca:
        push esi
    L_0041e5cb:
        mov esi,dword ptr [esp+10h]
    L_0041e5cf:
        push edi
    L_0041e5d0:
        lea ebx,[ebp+424h]
    L_0041e5d6:
        mov ecx,7Eh
    L_0041e5db:
        mov edi,ebx
    L_0041e5dd:
        rep movsd
    L_0041e5df:
        movsx ecx,word ptr [ebp+464h]
    L_0041e5e6:
        movsx eax,word ptr [ebp+466h]
    L_0041e5ed:
        mov dword ptr [ebp+0Ch],3
    L_0041e5f4:
        mov edi,dword ptr [ecx*4+474170h]
    L_0041e5fb:
        mov ecx,dword ptr [edx+458h]
    L_0041e601:
        lea esi,[ebp+61Ch]
    L_0041e607:
        add eax,edi
    L_0041e609:
        push ecx
    L_0041e60a:
        call asm_FUN_00404f30_00404f30
    L_0041e60f:
        mov edi,2
    L_0041e614:
        push esi
    L_0041e615:
        mov word ptr [ebp+920h],di
    L_0041e61c:
        call asm_FUN_0043ee30_0043ee30
    L_0041e621:
        test byte ptr [ebp+468h],2
    L_0041e628:
        je short L_0041e63c
    L_0041e62a:
        mov edx,dword ptr [esi+35Ch]
    L_0041e630:
        and edx,0FFFFFFDFh
    L_0041e633:
        or edx,10h
    L_0041e636:
        mov dword ptr [esi+35Ch],edx
    L_0041e63c:
        mov eax,dword ptr [ebp+978h]
    L_0041e642:
        mov ecx,dword ptr [data_0047781c]
    L_0041e648:
        and eax,0FC63FFFFh
    L_0041e64d:
        or eax,600000h
    L_0041e652:
        mov dword ptr [ebp+978h],eax
    L_0041e658:
        movsx eax,word ptr [ebp+466h]
    L_0041e65f:
        mov edx,dword ptr [ecx+458h]
    L_0041e665:
        lea esi,[ebp+9C8h]
    L_0041e66b:
        add eax,103h
    L_0041e670:
        push edx
    L_0041e671:
        call asm_FUN_00404f30_00404f30
    L_0041e676:
        push esi
    L_0041e677:
        mov word ptr [ebp+0CCCh],di
    L_0041e67e:
        call asm_FUN_0043ee30_0043ee30
    L_0041e683:
        mov eax,dword ptr [esi+35Ch]
    L_0041e689:
        and eax,0FFFFFFDFh
    L_0041e68c:
        or eax,10h
    L_0041e68f:
        mov dword ptr [esi+35Ch],eax
    L_0041e695:
        mov ecx,dword ptr [ebp+0D24h]
    L_0041e69b:
        mov eax,dword ptr [ebx]
    L_0041e69d:
        and ecx,0FC7FFFFFh
    L_0041e6a3:
        or ecx,400000h
    L_0041e6a9:
        lea edx,[ebp+24h]
    L_0041e6ac:
        mov dword ptr [edx],eax
    L_0041e6ae:
        mov eax,dword ptr [ebx+8]
    L_0041e6b1:
        mov dword ptr [ebp+0D24h],ecx
    L_0041e6b7:
        mov ecx,dword ptr [ebx+4]
    L_0041e6ba:
        mov dword ptr [edx+4],ecx
    L_0041e6bd:
        mov ecx,dword ptr [ebp+448h]
    L_0041e6c3:
        mov dword ptr [edx+8],eax
    L_0041e6c6:
        mov eax,dword ptr [ebp+43Ch]
    L_0041e6cc:
        mov edx,dword ptr [ebp+450h]
    L_0041e6d2:
        pop edi
    L_0041e6d3:
        pop esi
    L_0041e6d4:
        mov dword ptr [ebp+3Ch],eax
    L_0041e6d7:
        mov dword ptr [ebp+40Ch],18h
    L_0041e6e1:
        mov dword ptr [ebp+40h],ecx
    L_0041e6e4:
        mov dword ptr [ebp+44h],40000000h
    L_0041e6eb:
        mov dword ptr [ebp+48h],edx
    L_0041e6ee:
        pop ebp
    L_0041e6ef:
        xor eax,eax
    L_0041e6f1:
        pop ebx
    L_0041e6f2:
        ret 4
    }
}
