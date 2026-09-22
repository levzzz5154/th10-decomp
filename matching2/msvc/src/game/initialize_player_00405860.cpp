// BLOCKED (D3506): closest_byte_count=0/397; first_diff=0x00405860;
// residual_class=stack object input with private EAX/EDI/ESI live values,
// compiler-sensitive call sequencing across three animation/player callees,
// and the caller's real LTCG register context.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee topology, and MSVC 13.10 probe path (the wrapper is exact);
// no readable candidate was byte-measured without changing the fixed-address
// ownership manifest.
// next_lever=native-LTCG schema-2 cluster over caller 0x00425730 and callees
// 0x00448DB0, 0x0043DD10, 0x004054B0, and 0x00405500, then measure all
// 397 bytes before ownership promotion.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530..0x004045A6: FUN_00404530
// Naked body preserves the retail register/stack ABI.

// 0x00405860..0x004059EC: InitializePlayer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_InitializePlayer_00405860() {
    __asm {
    L_00405860:
        push ebp
    L_00405861:
        mov ebp,dword ptr [esp+8]
    L_00405865:
        mov eax,dword ptr [ebp+28h]
    L_00405868:
        xor ecx,ecx
    L_0040586a:
        cmp eax,ecx
    L_0040586c:
        je short L_00405875
    L_0040586e:
        or eax,0FFFFFFFFh
    L_00405871:
        pop ebp
    L_00405872:
        ret 4
    L_00405875:
        mov edx,1
    L_0040587a:
        mov dword ptr [ebp+28h],edx
    L_0040587d:
        mov eax,dword ptr [ebp+24h]
    L_00405880:
        test al,dl
    L_00405882:
        jne short L_0040589d
    L_00405884:
        or eax,edx
    L_00405886:
        mov dword ptr [ebp+18h],ecx
    L_00405889:
        mov dword ptr [ebp+14h],0FFF0BDC1h
    L_00405890:
        mov dword ptr [ebp+1Ch],ecx
    L_00405893:
        mov dword ptr [ebp+20h],476F78h
    L_0040589a:
        mov dword ptr [ebp+24h],eax
    L_0040589d:
        mov eax,dword ptr [data_00477834]
    L_004058a2:
        mov dword ptr [ebp+18h],ecx
    L_004058a5:
        mov dword ptr [ebp+1Ch],ecx
    L_004058a8:
        mov dword ptr [ebp+14h],0FFFFFFFFh
    L_004058af:
        push esi
    L_004058b0:
        add eax,3C0h
    L_004058b5:
        mov dword ptr [ebp+3Ch],42000000h
    L_004058bc:
        mov dword ptr [ebp+40h],40800000h
    L_004058c3:
        mov esi,dword ptr [eax]
    L_004058c5:
        push edi
    L_004058c6:
        lea edi,[ebp+30h]
    L_004058c9:
        mov ecx,edi
    L_004058cb:
        mov dword ptr [ecx],esi
    L_004058cd:
        mov esi,dword ptr [eax+4]
    L_004058d0:
        mov dword ptr [ecx+4],esi
    L_004058d3:
        mov eax,dword ptr [eax+8]
    L_004058d6:
        mov dword ptr [ecx+8],eax
    L_004058d9:
        mov eax,dword ptr [data_004776f4]
    L_004058de:
        test byte ptr [eax+378Ch],dl
    L_004058e4:
        je short L_004058f6
    L_004058e6:
        mov ecx,dword ptr [eax+3788h]
    L_004058ec:
        cmp ecx,5Dh
    L_004058ef:
        jl short L_004058f6
    L_004058f1:
        cmp ecx,60h
    L_004058f4:
        jle short L_00405912
    L_004058f6:
        cmp dword ptr [eax+3788h],6Dh
    L_004058fd:
        je short L_00405912
    L_004058ff:
        mov eax,dword ptr [data_00474c68]
    L_00405904:
        neg eax
    L_00405906:
        sbb eax,eax
    L_00405908:
        and eax,7
    L_0040590b:
        add eax,190h
    L_00405910:
        jmp short L_00405917
    L_00405912:
        mov eax,1B9h
    L_00405917:
        mov edx,dword ptr [data_004776f0]
    L_0040591d:
        push ebx
    L_0040591e:
        push eax
    L_0040591f:
        mov eax,dword ptr [edx+3E0B50h]
    L_00405925:
        lea ecx,[esp+18h]
    L_00405929:
        push ecx
    L_0040592a:
        push eax
    L_0040592b:
        call asm_PlayerAnimation_Create_00448db0
    L_00405930:
        mov edx,dword ptr [edi]
    L_00405932:
        mov ecx,dword ptr [eax]
    L_00405934:
        push edx
    L_00405935:
        mov ebx,26h
    L_0040593a:
        mov esi,492590h
    L_0040593f:
        mov dword ptr [ebp+2Ch],ecx
    L_00405942:
        call asm_FUN_0043dd10_0043dd10
    L_00405947:
        movsx eax,word ptr [data_00474c48]
    L_0040594e:
        cdq
    L_0040594f:
        mov ecx,14h
    L_00405954:
        idiv ecx
    L_00405956:
        mov esi,dword ptr [data_0047770c]
    L_0040595c:
        imul edx,64h
    L_0040595f:
        mov ecx,eax
    L_00405961:
        mov eax,66666667h
    L_00405966:
        imul edx
    L_00405968:
        sar edx,3
    L_0040596b:
        mov eax,edx
    L_0040596d:
        shr eax,1Fh
    L_00405970:
        add eax,edx
    L_00405972:
        push eax
    L_00405973:
        mov edx,ecx
    L_00405975:
        call asm_FUN_004054b0_004054b0
    L_0040597a:
        mov esi,dword ptr [data_004776f4]
    L_00405980:
        mov eax,esi
    L_00405982:
        call asm_Player_ClearExpiredFlagsRetail_00405500
    L_00405987:
        mov eax,dword ptr [data_00474c98]
    L_0040598c:
        sub eax,80h
    L_00405991:
        cmp eax,400h
    L_00405996:
        mov dword ptr [data_00474c98],eax
    L_0040599b:
        pop ebx
    L_0040599c:
        jle short L_004059aa
    L_0040599e:
        mov dword ptr [data_00474c98],400h
    L_004059a8:
        jmp short L_004059bb
    L_004059aa:
        cmp eax,0FFFFFC00h
    L_004059af:
        jge short L_004059bb
    L_004059b1:
        mov dword ptr [data_00474c98],0FFFFFC00h
    L_004059bb:
        mov cl,byte ptr [esi+378Ch]
    L_004059c1:
        mov eax,1
    L_004059c6:
        test cl,al
    L_004059c8:
        je short L_004059de
    L_004059ca:
        cmp dword ptr [esi+3738h],3Ch
    L_004059d1:
        jl short L_004059de
    L_004059d3:
        pop edi
    L_004059d4:
        mov dword ptr [ebp+44h],eax
    L_004059d7:
        pop esi
    L_004059d8:
        xor eax,eax
    L_004059da:
        pop ebp
    L_004059db:
        ret 4
    L_004059de:
        pop edi
    L_004059df:
        pop esi
    L_004059e0:
        mov dword ptr [ebp+44h],0
    L_004059e7:
        xor eax,eax
    L_004059e9:
        pop ebp
    L_004059ea:
        ret 4
    }
}
