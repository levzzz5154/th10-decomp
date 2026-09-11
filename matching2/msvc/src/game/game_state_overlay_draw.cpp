#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00415800..0x00415816: FUN_00415800
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00415800_00415800() {
    __asm {
    L_00415800:
        sub esp,10h
    L_00415803:
        push ebp
    L_00415804:
        mov ebp,dword ptr [esp+18h]
    L_00415808:
        push esi
    L_00415809:
        push edi
    L_0041580a:
        lea esi,[ebp+24C8h]
    L_00415810:
        mov edi,0Ah
    L_00415815:
        TH10_REL8(0xeb, 0x00415815, VA_asm_FUN_00415800_part_00415820)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_00415820:
        mov ecx,dword ptr [data_00491c10]
    L_00415826:
        lea eax,[esi-24B8h]
    L_0041582c:
        call asm_FUN_004451c0_004451c0
    L_00415831:
        mov ecx,dword ptr [data_00491c10]
    L_00415837:
        mov eax,esi
    L_00415839:
        call asm_FUN_004451c0_004451c0
    L_0041583e:
        add esi,3ACh
    L_00415844:
        dec edi
    L_00415845:
        jne short L_00415820
    L_00415847:
        lea esi,[ebp+4980h]
    L_0041584d:
        mov edi,9
    L_00415852:
        mov ecx,dword ptr [data_00491c10]
    L_00415858:
        mov eax,esi
    L_0041585a:
        call asm_FUN_004451c0_004451c0
    L_0041585f:
        add esi,3ACh
    L_00415865:
        dec edi
    L_00415866:
        jne short L_00415852
    L_00415868:
        lea esi,[ebp+6A8Ch]
    L_0041586e:
        mov edi,4
    L_00415873:
        mov ecx,dword ptr [data_00491c10]
    L_00415879:
        mov eax,esi
    L_0041587b:
        call asm_FUN_004451c0_004451c0
    L_00415880:
        add esi,3ACh
    L_00415886:
        dec edi
    L_00415887:
        jne short L_00415873
    L_00415889:
        lea esi,[ebp+8094h]
    L_0041588f:
        mov edi,7
    L_00415894:
        TH10_REL8(0xeb, 0x00415894, VA_asm_FUN_00415800_part_004158a0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004158a0:
        mov ecx,dword ptr [data_00491c10]
    L_004158a6:
        mov eax,esi
    L_004158a8:
        call asm_FUN_004451c0_004451c0
    L_004158ad:
        add esi,3ACh
    L_004158b3:
        dec edi
    L_004158b4:
        jne short L_004158a0
    L_004158b6:
        mov eax,dword ptr [data_00474c58]
    L_004158bb:
        test eax,eax
    L_004158bd:
        push ebx
    L_004158be:
        je short L_0041593c
    L_004158c0:
        fild dword ptr [data_00474c58]
    L_004158c6:
        movzx ebx,byte ptr [ebp+8393h]
    L_004158cd:
        shl ebx,18h
    L_004158d0:
        fmul dword ptr [data_00470cb8]
    L_004158d6:
        lea edi,[esp+10h]
    L_004158da:
        mov dword ptr [esp+10h],424C0000h
    L_004158e2:
        mov dword ptr [esp+14h],43E68000h
    L_004158ea:
        fadd dword ptr [data_00470d2c]
    L_004158f0:
        mov dword ptr [esp+1Ch],43E78000h
    L_004158f8:
        fstp dword ptr [esp+18h]
    L_004158fc:
        call asm_FUN_0043bda0_0043bda0
    L_00415901:
        movzx ebx,byte ptr [ebp+8393h]
    L_00415908:
        fld dword ptr [esp+18h]
    L_0041590c:
        fsub dword ptr [data_00470afc]
    L_00415912:
        shl ebx,18h
    L_00415915:
        or ebx,0FFFFFFh
    L_0041591b:
        mov dword ptr [esp+10h],42480000h
    L_00415923:
        fstp dword ptr [esp+18h]
    L_00415927:
        mov dword ptr [esp+14h],43E60000h
    L_0041592f:
        mov dword ptr [esp+1Ch],43E70000h
    L_00415937:
        call asm_FUN_0043bda0_0043bda0
    L_0041593c:
        fld dword ptr [ebp+9E84h]
    L_00415942:
        fcomp dword ptr [data_00470b04]
    L_00415948:
        fnstsw ax
    L_0041594a:
        test ah,41h
    L_0041594d:
        jne asm_target_00415a3c
    L_00415953:
        fld dword ptr [ebp+9E84h]
    L_00415959:
        mov ebx,0FF000000h
    L_0041595e:
        fmul dword ptr [data_00470d28]
    L_00415964:
        lea edi,[esp+10h]
    L_00415968:
        mov dword ptr [esp+10h],42240000h
    L_00415970:
        mov dword ptr [esp+14h],41B80000h
    L_00415978:
        fadd dword ptr [data_00470d24]
    L_0041597e:
        mov dword ptr [esp+1Ch],41C80000h
    L_00415986:
        fstp dword ptr [esp+18h]
    L_0041598a:
        call asm_FUN_0043bda0_0043bda0
    L_0041598f:
        fld dword ptr [esp+18h]
    L_00415993:
        or ebx,0FFFFFFFFh
    L_00415996:
        fsub dword ptr [data_00470afc]
    L_0041599c:
        mov dword ptr [esp+10h],42200000h
    L_004159a4:
        mov dword ptr [esp+14h],41B00000h
    L_004159ac:
        mov dword ptr [esp+1Ch],41C00000h
    L_004159b4:
        fstp dword ptr [esp+18h]
    L_004159b8:
        call asm_FUN_0043bda0_0043bda0
    L_004159bd:
        lea esi,[ebp+9E94h]
    L_004159c3:
        mov dword ptr [esp+24h],4
    L_004159cb:
        TH10_REL8(0xeb, 0x004159cb, VA_asm_FUN_00415800_part_004159d0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004159d0:
        fld dword ptr [data_00470b04]
    L_004159d6:
        fld dword ptr [esi]
    L_004159d8:
        fucompp
    L_004159da:
        fnstsw ax
    L_004159dc:
        test ah,44h
    L_004159df:
        jnp short L_00415a2e
    L_004159e1:
        fld dword ptr [esi]
    L_004159e3:
        fcomp dword ptr [ebp+9E84h]
    L_004159e9:
        fnstsw ax
    L_004159eb:
        test ah,5
    L_004159ee:
        jp short L_004159f4
    L_004159f0:
        fld dword ptr [esi]
    L_004159f2:
        jmp short L_004159fa
    L_004159f4:
        fld dword ptr [ebp+9E84h]
    L_004159fa:
        fmul dword ptr [data_00470d28]
    L_00415a00:
        mov ebx,dword ptr [esi+4]
    L_00415a03:
        lea edi,[esp+10h]
    L_00415a07:
        mov dword ptr [esp+10h],42200000h
    L_00415a0f:
        fadd dword ptr [data_00470c64]
    L_00415a15:
        mov dword ptr [esp+14h],41B00000h
    L_00415a1d:
        mov dword ptr [esp+1Ch],41C00000h
    L_00415a25:
        fstp dword ptr [esp+18h]
    L_00415a29:
        call asm_FUN_0043bda0_0043bda0
    L_00415a2e:
        mov eax,dword ptr [esp+24h]
    L_00415a32:
        add esi,8
    L_00415a35:
        dec eax
    L_00415a36:
        mov dword ptr [esp+24h],eax
    L_00415a3a:
        jne short L_004159d0
    L_00415a3c:
        mov ecx,dword ptr [data_00477704]
    L_00415a42:
        test ecx,ecx
    L_00415a44:
        pop ebx
    L_00415a45:
        je asm_target_00415ac6
    L_00415a4b:
        mov eax,dword ptr [ecx+10h]
    L_00415a4e:
        test eax,eax
    L_00415a50:
        je short L_00415a81
    L_00415a52:
        mov eax,dword ptr [eax+2480h]
    L_00415a58:
        mov edx,eax
    L_00415a5a:
        shr edx,4
    L_00415a5d:
        not edx
    L_00415a5f:
        test dl,1
    L_00415a62:
        je short L_00415a81
    L_00415a64:
        not eax
    L_00415a66:
        test al,1
    L_00415a68:
        je short L_00415a81
    L_00415a6a:
        mov ecx,dword ptr [data_00491c10]
    L_00415a70:
        lea eax,[ebp+9A48h]
    L_00415a76:
        call asm_FUN_004451c0_004451c0
    L_00415a7b:
        mov ecx,dword ptr [data_00477704]
    L_00415a81:
        test ecx,ecx
    L_00415a83:
        TH10_REL8(0x74, 0x00415a83, VA_asm_target_00415ac6)
    L_00415a85:
        mov eax,dword ptr [ebp+9EC0h]
    L_00415a8b:
        test eax,eax
    L_00415a8d:
        TH10_REL8(0x7c, 0x00415a8d, VA_asm_target_00415ac6)
    L_00415a8f:
        mov eax,dword ptr [ecx+10h]
    L_00415a92:
        test eax,eax
    L_00415a94:
        TH10_REL8(0x74, 0x00415a94, VA_asm_target_00415ac6)
    L_00415a96:
        mov eax,dword ptr [ebp+9EB8h]
    L_00415a9c:
        test eax,eax
    L_00415a9e:
        TH10_REL8(0x75, 0x00415a9e, VA_asm_target_00415ac6)
    L_00415aa0:
        lea esi,[ebp+793Ch]
    L_00415aa6:
        mov edi,2
    L_00415aab:
        TH10_REL8(0xeb, 0x00415aab, VA_asm_FUN_00415800_part_00415ab0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00415ab0:
        mov ecx,dword ptr [data_00491c10]
    L_00415ab6:
        mov eax,esi
    L_00415ab8:
        call asm_FUN_004451c0_004451c0
    L_00415abd:
        add esi,3ACh
    L_00415ac3:
        dec edi
    L_00415ac4:
        jne short L_00415ab0
    L_00415ac6:
        pop edi
    L_00415ac7:
        pop esi
    L_00415ac8:
        mov eax,1
    L_00415acd:
        pop ebp
    L_00415ace:
        add esp,10h
    L_00415ad1:
        ret 4
    }
}
