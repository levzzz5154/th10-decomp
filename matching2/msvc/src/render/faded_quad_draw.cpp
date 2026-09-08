#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004445C0..0x00444751: FUN_004445c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004445c0_004445c0() {
    __asm {
    L_004445c0:
        sub esp,4Ch
    L_004445c3:
        push ebx
    L_004445c4:
        push ebp
    L_004445c5:
        mov ebp,dword ptr [esp+58h]
    L_004445c9:
        push esi
    L_004445ca:
        mov esi,dword ptr [esp+60h]
    L_004445ce:
        push edi
    L_004445cf:
        push ebp
    L_004445d0:
        mov eax,esi
    L_004445d2:
        call asm_FUN_00444240_00444240
    L_004445d7:
        fld dword ptr [data_00491e78]
    L_004445dd:
        fsub dword ptr [data_00491e7c]
    L_004445e3:
        mov eax,dword ptr [esi+35Ch]
    L_004445e9:
        test ah,ah
    L_004445eb:
        fstp dword ptr [esp+14h]
    L_004445ef:
        jns short L_004445f9
    L_004445f1:
        mov ebx,dword ptr [esi+300h]
    L_004445f7:
        jmp short L_004445ff
    L_004445f9:
        mov ebx,dword ptr [esi+2FCh]
    L_004445ff:
        mov dword ptr [esp+10h],ebx
    L_00444603:
        mov esi,4978D3h
    L_00444608:
        lea edi,[esp+1Ch]
    L_0044460c:
        add ebp,3ADA78h
    L_00444612:
        mov eax,dword ptr [esp+60h]
    L_00444616:
        add eax,3AD0F0h
    L_0044461b:
        push eax
    L_0044461c:
        push ebp
    L_0044461d:
        push edi
    L_0044461e:
        call asm_D3DXVec3Transform_004521c4
    L_00444623:
        fld dword ptr [edi]
    L_00444625:
        fsub dword ptr [data_00491d7c]
    L_0044462b:
        fld dword ptr [edi+4]
    L_0044462e:
        fsub dword ptr [data_00491d80]
    L_00444634:
        fld dword ptr [edi+8]
    L_00444637:
        fsub dword ptr [data_00491d84]
    L_0044463d:
        fld st(0)
    L_0044463f:
        fmul st,st(1)
    L_00444641:
        fld st(2)
    L_00444643:
        fmul st,st(3)
    L_00444645:
        faddp st(1),st
    L_00444647:
        fld st(3)
    L_00444649:
        fmul st,st(4)
    L_0044464b:
        faddp st(1),st
    L_0044464d:
        fsqrt
    L_0044464f:
        fstp st(3)
    L_00444651:
        fstp st(0)
    L_00444653:
        fstp st(0)
    L_00444655:
        fld dword ptr [data_00491e78]
    L_0044465b:
        fcomp
    L_0044465d:
        fnstsw ax
    L_0044465f:
        test ah,5
    L_00444662:
        jp asm_target_004446f7
    L_00444668:
        fsubr dword ptr [data_00491e78]
    L_0044466e:
        fdiv dword ptr [esp+14h]
    L_00444672:
        fcom dword ptr [data_00470afc]
    L_00444678:
        fnstsw ax
    L_0044467a:
        test ah,1
    L_0044467d:
        jne short L_0044468f
    L_0044467f:
        mov eax,dword ptr [data_00491e90]
    L_00444684:
        mov cl,byte ptr [esp+13h]
    L_00444688:
        mov dword ptr [esi-3],eax
    L_0044468b:
        mov byte ptr [esi],cl
    L_0044468d:
        jmp short L_004446fa
    L_0044468f:
        movzx edx,bl
    L_00444692:
        mov dword ptr [esp+18h],edx
    L_00444696:
        fild dword ptr [esp+18h]
    L_0044469a:
        fsub dword ptr [data_00491e80]
    L_004446a0:
        fmul st,st(1)
    L_004446a2:
        call asm_FUN_00463b2c_00463b2c
    L_004446a7:
        movzx edx,bh
    L_004446aa:
        mov dword ptr [esp+18h],edx
    L_004446ae:
        mov cl,bl
    L_004446b0:
        sub cl,al
    L_004446b2:
        fild dword ptr [esp+18h]
    L_004446b6:
        mov byte ptr [esi-3],cl
    L_004446b9:
        fsub dword ptr [data_00491e84]
    L_004446bf:
        fmul st,st(1)
    L_004446c1:
        call asm_FUN_00463b2c_00463b2c
    L_004446c6:
        movzx edx,byte ptr [esp+12h]
    L_004446cb:
        mov dword ptr [esp+18h],edx
    L_004446cf:
        mov cl,bh
    L_004446d1:
        sub cl,al
    L_004446d3:
        fild dword ptr [esp+18h]
    L_004446d7:
        mov byte ptr [esi-2],cl
    L_004446da:
        fsub dword ptr [data_00491e88]
    L_004446e0:
        fmul st,st(1)
    L_004446e2:
        call asm_FUN_00463b2c_00463b2c
    L_004446e7:
        mov cx,word ptr [esp+12h]
    L_004446ec:
        mov dl,cl
    L_004446ee:
        sub dl,al
    L_004446f0:
        mov byte ptr [esi-1],dl
    L_004446f3:
        mov byte ptr [esi],ch
    L_004446f5:
        jmp short L_004446fa
    L_004446f7:
        mov dword ptr [esi-3],ebx
    L_004446fa:
        add esi,1Ch
    L_004446fd:
        fstp st(0)
    L_004446ff:
        add ebp,14h
    L_00444702:
        add edi,10h
    L_00444705:
        cmp esi,497943h
    L_0044470b:
        jl asm_target_00444612
    L_00444711:
        mov eax,dword ptr [esp+64h]
    L_00444715:
        mov ecx,dword ptr [esp+60h]
    L_00444719:
        push 2
    L_0044471b:
        call asm_FUN_00442670_00442670
    L_00444720:
        pop edi
    L_00444721:
        pop esi
    L_00444722:
        pop ebp
    L_00444723:
        mov dword ptr [data_00497920],3F800000h
    L_0044472d:
        mov dword ptr [data_00497904],3F800000h
    L_00444737:
        mov dword ptr [data_004978e8],3F800000h
    L_00444741:
        mov dword ptr [data_004978cc],3F800000h
    L_0044474b:
        pop ebx
    L_0044474c:
        add esp,4Ch
    L_0044474f:
        ret 8
    }
}
