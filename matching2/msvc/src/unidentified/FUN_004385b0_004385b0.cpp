#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004385B0..0x00438679: FUN_004385b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004385b0_004385b0() {
    __asm {
    L_004385b0:
        push ebp
    L_004385b1:
        push esi
    L_004385b2:
        mov esi,dword ptr [esp+0Ch]
    L_004385b6:
        cmp esi,0FFFFFFFEh
    L_004385b9:
        mov ebp,ecx
    L_004385bb:
        jbe short L_004385c2
    L_004385bd:
        call asm_FUN_004624e5_004624e5
    L_004385c2:
        mov eax,dword ptr [ebp+18h]
    L_004385c5:
        cmp eax,esi
    L_004385c7:
        jae short L_004385e2
    L_004385c9:
        mov eax,dword ptr [ebp+14h]
    L_004385cc:
        push eax
    L_004385cd:
        push esi
    L_004385ce:
        mov ecx,ebp
    L_004385d0:
        call asm_Grow_LegacyString_004386b0
    L_004385d5:
        xor eax,eax
    L_004385d7:
        cmp eax,esi
    L_004385d9:
        sbb eax,eax
    L_004385db:
        pop esi
    L_004385dc:
        neg eax
    L_004385de:
        pop ebp
    L_004385df:
        ret 8
    L_004385e2:
        mov cl,byte ptr [esp+10h]
    L_004385e6:
        test cl,cl
    L_004385e8:
        je short L_00438646
    L_004385ea:
        cmp esi,10h
    L_004385ed:
        jae short L_00438646
    L_004385ef:
        push ebx
    L_004385f0:
        mov ebx,dword ptr [ebp+14h]
    L_004385f3:
        cmp esi,ebx
    L_004385f5:
        jae short L_004385f9
    L_004385f7:
        mov ebx,esi
    L_004385f9:
        cmp eax,10h
    L_004385fc:
        jb short L_00438629
    L_004385fe:
        test ebx,ebx
    L_00438600:
        mov eax,dword ptr [ebp+4]
    L_00438603:
        push edi
    L_00438604:
        lea edi,[ebp+4]
    L_00438607:
        jbe short L_0043861f
    L_00438609:
        mov ecx,ebx
    L_0043860b:
        mov edx,ecx
    L_0043860d:
        shr ecx,2
    L_00438610:
        mov esi,eax
    L_00438612:
        rep movsd
    L_00438614:
        mov ecx,edx
    L_00438616:
        and ecx,3
    L_00438619:
        rep movsb
    L_0043861b:
        mov esi,dword ptr [esp+14h]
    L_0043861f:
        push eax
    L_00438620:
        call asm_free_004524a1
    L_00438625:
        add esp,4
    L_00438628:
        pop edi
    L_00438629:
        mov dword ptr [ebp+14h],ebx
    L_0043862c:
        xor eax,eax
    L_0043862e:
        mov dword ptr [ebp+18h],0Fh
    L_00438635:
        mov byte ptr [ebx+ebp+4],0
    L_0043863a:
        cmp eax,esi
    L_0043863c:
        pop ebx
    L_0043863d:
        sbb eax,eax
    L_0043863f:
        pop esi
    L_00438640:
        neg eax
    L_00438642:
        pop ebp
    L_00438643:
        ret 8
    L_00438646:
        test esi,esi
    L_00438648:
        jne short L_0043866d
    L_0043864a:
        cmp eax,10h
    L_0043864d:
        mov dword ptr [ebp+14h],esi
    L_00438650:
        jb short L_00438666
    L_00438652:
        mov ebp,dword ptr [ebp+4]
    L_00438655:
        xor eax,eax
    L_00438657:
        cmp eax,esi
    L_00438659:
        sbb eax,eax
    L_0043865b:
        pop esi
    L_0043865c:
        mov byte ptr [ebp],0
    L_00438660:
        neg eax
    L_00438662:
        pop ebp
    L_00438663:
        ret 8
    L_00438666:
        add ebp,4
    L_00438669:
        mov byte ptr [ebp],0
    L_0043866d:
        xor eax,eax
    L_0043866f:
        cmp eax,esi
    L_00438671:
        sbb eax,eax
    L_00438673:
        pop esi
    L_00438674:
        neg eax
    L_00438676:
        pop ebp
    L_00438677:
        ret 8
    }
}
