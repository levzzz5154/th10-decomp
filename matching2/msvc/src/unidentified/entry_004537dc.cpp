#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004537DC..0x00453976: entry
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_entry_004537dc() {
    __asm {
    L_004537dc:
        push 60h
    L_004537de:
        push 46A770h
    L_004537e3:
        call asm_SEH_prolog_00454bbc
    L_004537e8:
        mov edi,94h
    L_004537ed:
        mov eax,edi
    L_004537ef:
        call asm_chkstk_00458ec0
    L_004537f4:
        mov dword ptr [ebp-18h],esp
    L_004537f7:
        mov esi,esp
    L_004537f9:
        mov dword ptr [esi],edi
    L_004537fb:
        push esi
    L_004537fc:
        call dword ptr [data_0046612c]
    L_00453802:
        mov ecx,dword ptr [esi+10h]
    L_00453805:
        mov dword ptr [data_00477470],ecx
    L_0045380b:
        mov eax,dword ptr [esi+4]
    L_0045380e:
        mov dword ptr [data_0047747c],eax
    L_00453813:
        mov edx,dword ptr [esi+8]
    L_00453816:
        mov dword ptr [data_00477480],edx
    L_0045381c:
        mov esi,dword ptr [esi+0Ch]
    L_0045381f:
        and esi,7FFFh
    L_00453825:
        mov dword ptr [data_00477474],esi
    L_0045382b:
        cmp ecx,2
    L_0045382e:
        je short L_0045383c
    L_00453830:
        or esi,8000h
    L_00453836:
        mov dword ptr [data_00477474],esi
    L_0045383c:
        shl eax,8
    L_0045383f:
        add eax,edx
    L_00453841:
        mov dword ptr [data_00477478],eax
    L_00453846:
        xor esi,esi
    L_00453848:
        push esi
    L_00453849:
        mov edi,dword ptr [data_00466198]
    L_0045384f:
        call edi
    L_00453851:
        cmp word ptr [eax],5A4Dh
    L_00453856:
        jne short L_00453877
    L_00453858:
        mov ecx,dword ptr [eax+3Ch]
    L_0045385b:
        add ecx,eax
    L_0045385d:
        cmp dword ptr [ecx],4550h
    L_00453863:
        jne short L_00453877
    L_00453865:
        movzx eax,word ptr [ecx+18h]
    L_00453869:
        cmp eax,10Bh
    L_0045386e:
        je short L_0045388f
    L_00453870:
        cmp eax,20Bh
    L_00453875:
        je short L_0045387c
    L_00453877:
        mov dword ptr [ebp-1Ch],esi
    L_0045387a:
        jmp short L_004538a3
    L_0045387c:
        cmp dword ptr [ecx+84h],0Eh
    L_00453883:
        jbe short L_00453877
    L_00453885:
        xor eax,eax
    L_00453887:
        cmp dword ptr [ecx+0F8h],esi
    L_0045388d:
        jmp short L_0045389d
    L_0045388f:
        cmp dword ptr [ecx+74h],0Eh
    L_00453893:
        jbe short L_00453877
    L_00453895:
        xor eax,eax
    L_00453897:
        cmp dword ptr [ecx+0E8h],esi
    L_0045389d:
        setne al
    L_004538a0:
        mov dword ptr [ebp-1Ch],eax
    L_004538a3:
        push 1
    L_004538a5:
        call asm_heap_init_004539cb
    L_004538aa:
        pop ecx
    L_004538ab:
        test eax,eax
    L_004538ad:
        jne short L_004538b7
    L_004538af:
        push 1Ch
    L_004538b1:
        call asm_fast_error_exit_00453762
    L_004538b6:
        pop ecx
    L_004538b7:
        call asm_mtinit_0045654a
    L_004538bc:
        test eax,eax
    L_004538be:
        jne short L_004538c8
    L_004538c0:
        push 10h
    L_004538c2:
        call asm_fast_error_exit_00453762
    L_004538c7:
        pop ecx
    L_004538c8:
        call asm_RTC_Initialize_00459776
    L_004538cd:
        mov dword ptr [ebp-4],esi
    L_004538d0:
        call asm_ioinit_0045952c
    L_004538d5:
        test eax,eax
    L_004538d7:
        jge short L_004538e1
    L_004538d9:
        push 1Bh
    L_004538db:
        call asm_amsg_exit_0045373d
    L_004538e0:
        pop ecx
    L_004538e1:
        call dword ptr [data_00466194]
    L_004538e7:
        mov dword ptr [data_00499348],eax
    L_004538ec:
        call asm_crtGetEnvironmentStringsA_0045940a
    L_004538f1:
        mov dword ptr [data_00477204],eax
    L_004538f6:
        call asm_setargv_00459368
    L_004538fb:
        test eax,eax
    L_004538fd:
        jge short L_00453907
    L_004538ff:
        push 8
    L_00453901:
        call asm_amsg_exit_0045373d
    L_00453906:
        pop ecx
    L_00453907:
        call asm_setenvp_00459135
    L_0045390c:
        test eax,eax
    L_0045390e:
        jge short L_00453918
    L_00453910:
        push 9
    L_00453912:
        call asm_amsg_exit_0045373d
    L_00453917:
        pop ecx
    L_00453918:
        push 1
    L_0045391a:
        call asm_cinit_004575bf
    L_0045391f:
        pop ecx
    L_00453920:
        mov dword ptr [ebp-28h],eax
    L_00453923:
        cmp eax,esi
    L_00453925:
        je short L_0045392e
    L_00453927:
        push eax
    L_00453928:
        call asm_amsg_exit_0045373d
    L_0045392d:
        pop ecx
    L_0045392e:
        mov dword ptr [ebp-44h],esi
    L_00453931:
        lea eax,[ebp-70h]
    L_00453934:
        push eax
    L_00453935:
        call dword ptr [data_00466108]
    L_0045393b:
        call asm_wincmdln_004590d8
    L_00453940:
        mov dword ptr [ebp-20h],eax
    L_00453943:
        test byte ptr [ebp-44h],1
    L_00453947:
        je short L_0045394f
    L_00453949:
        movzx eax,word ptr [ebp-40h]
    L_0045394d:
        jmp short L_00453952
    L_0045394f:
        push 0Ah
    L_00453951:
        pop eax
    L_00453952:
        push eax
    L_00453953:
        push dword ptr [ebp-20h]
    L_00453956:
        push esi
    L_00453957:
        push esi
    L_00453958:
        call edi
    L_0045395a:
        push eax
    L_0045395b:
        call asm_GameMain_00438ad0
    L_00453960:
        mov edi,eax
    L_00453962:
        mov dword ptr [ebp-2Ch],edi
    L_00453965:
        cmp dword ptr [ebp-1Ch],esi
    L_00453968:
        jne short L_00453970
    L_0045396a:
        push edi
    L_0045396b:
        call asm_exit_004576ec
    L_00453970:
        call asm_cexit_0045770e
    L_00453975:
        TH10_REL8(0xeb, 0x00453975, VA_asm_entry_part_004539a2)
        _emit 0x8b
        _emit 0x45
        _emit 0xec
        _emit 0x8b
        _emit 0x08
        _emit 0x8b
        _emit 0x09
        _emit 0x89
        _emit 0x4d
        _emit 0xdc
        _emit 0x50
        _emit 0x51
        _emit 0xe8
        _emit 0x46
        _emit 0x3e
        _emit 0x00
        _emit 0x00
        _emit 0x59
        _emit 0x59
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0x8b
        _emit 0x7d
        _emit 0xdc
        _emit 0x83
        _emit 0x7d
        _emit 0xe4
        _emit 0x00
        _emit 0x75
        _emit 0x06
        _emit 0x57
        _emit 0xe8
        _emit 0x60
        _emit 0x3d
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0x7b
        _emit 0x3d
        _emit 0x00
        _emit 0x00

    L_004539a2:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004539a6:
        mov eax,edi
    L_004539a8:
        lea esp,[ebp-7Ch]
    L_004539ab:
        call asm_SEH_epilog_00454bf7
    L_004539b0:
        ret
    }
}
