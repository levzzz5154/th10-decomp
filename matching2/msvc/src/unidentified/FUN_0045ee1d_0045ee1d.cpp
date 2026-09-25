#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045EE1D..0x0045EF12: FUN_0045ee1d
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045ee1d_0045ee1d() {
    __asm {
    L_0045ee1d:
        push 3Ch
    L_0045ee1f:
        push 46C648h
    L_0045ee24:
        call asm_SEH_prolog_00454bbc
    L_0045ee29:
        xor ebx,ebx
    L_0045ee2b:
        cmp dword ptr [data_00477694],ebx
    L_0045ee31:
        jne short L_0045ee6b
    L_0045ee33:
        push ebx
    L_0045ee34:
        push ebx
    L_0045ee35:
        xor esi,esi
    L_0045ee37:
        inc esi
    L_0045ee38:
        push esi
    L_0045ee39:
        push 46B5C4h
    L_0045ee3e:
        push 100h
    L_0045ee43:
        push ebx
    L_0045ee44:
        call dword ptr [data_0046603c]
    L_0045ee4a:
        test eax,eax
    L_0045ee4c:
        je short L_0045ee56
    L_0045ee4e:
        mov dword ptr [data_00477694],esi
    L_0045ee54:
        jmp short L_0045ee6b
    L_0045ee56:
        call dword ptr [data_0046610c]
    L_0045ee5c:
        cmp eax,78h
    L_0045ee5f:
        jne short L_0045ee6b
    L_0045ee61:
        mov dword ptr [data_00477694],2
    L_0045ee6b:
        cmp dword ptr [ebp+14h],ebx
    L_0045ee6e:
        jle short L_0045ee8b
    L_0045ee70:
        mov ecx,dword ptr [ebp+14h]
    L_0045ee73:
        mov eax,dword ptr [ebp+10h]
    L_0045ee76:
        dec ecx
    L_0045ee77:
        cmp byte ptr [eax],bl
    L_0045ee79:
        je short L_0045ee83
    L_0045ee7b:
        inc eax
    L_0045ee7c:
        cmp ecx,ebx
    L_0045ee7e:
        jne short L_0045ee76
    L_0045ee80:
        or ecx,0FFFFFFFFh
    L_0045ee83:
        or eax,0FFFFFFFFh
    L_0045ee86:
        sub eax,ecx
    L_0045ee88:
        add dword ptr [ebp+14h],eax
    L_0045ee8b:
        mov eax,dword ptr [data_00477694]
    L_0045ee90:
        cmp eax,2
    L_0045ee93:
        je asm_target_0045f075
    L_0045ee99:
        cmp eax,ebx
    L_0045ee9b:
        je asm_target_0045f075
    L_0045eea1:
        cmp eax,1
    L_0045eea4:
        jne asm_target_0045f0ab
    L_0045eeaa:
        xor edi,edi
    L_0045eeac:
        mov dword ptr [ebp-2Ch],edi
    L_0045eeaf:
        mov dword ptr [ebp-3Ch],ebx
    L_0045eeb2:
        mov dword ptr [ebp-38h],ebx
    L_0045eeb5:
        cmp dword ptr [ebp+20h],ebx
    L_0045eeb8:
        jne short L_0045eec2
    L_0045eeba:
        mov eax,dword ptr [data_00477664]
    L_0045eebf:
        mov dword ptr [ebp+20h],eax
    L_0045eec2:
        push ebx
    L_0045eec3:
        push ebx
    L_0045eec4:
        push dword ptr [ebp+14h]
    L_0045eec7:
        push dword ptr [ebp+10h]
    L_0045eeca:
        xor eax,eax
    L_0045eecc:
        cmp dword ptr [ebp+24h],ebx
    L_0045eecf:
        setne al
    L_0045eed2:
        lea eax,[eax*8+1]
    L_0045eed9:
        push eax
    L_0045eeda:
        push dword ptr [ebp+20h]
    L_0045eedd:
        call dword ptr [data_00466104]
    L_0045eee3:
        mov esi,eax
    L_0045eee5:
        mov dword ptr [ebp-34h],esi
    L_0045eee8:
        cmp esi,ebx
    L_0045eeea:
        je asm_target_0045f0ab
    L_0045eef0:
        mov dword ptr [ebp-4],1
    L_0045eef7:
        lea eax,[esi+esi]
    L_0045eefa:
        add eax,3
    L_0045eefd:
        and eax,0FFFFFFFCh
    L_0045ef00:
        call asm_chkstk_00458ec0
    L_0045ef05:
        mov dword ptr [ebp-18h],esp
    L_0045ef08:
        mov eax,esp
    L_0045ef0a:
        mov dword ptr [ebp-1Ch],eax
    L_0045ef0d:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045ef11:
        TH10_REL8(0xeb, 0x0045ef11, VA_asm_FUN_0045ee1d_part_0045ef2e)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0xe8
        _emit 0x72
        _emit 0x9e
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x89
        _emit 0x5d
        _emit 0xe4
        _emit 0x83
        _emit 0x4d
        _emit 0xfc
        _emit 0xff
        _emit 0x8b
        _emit 0x7d
        _emit 0xd4
        _emit 0x8b
        _emit 0x75
        _emit 0xcc

    L_0045ef2e:
        cmp dword ptr [ebp-1Ch],ebx
    L_0045ef31:
        jne short L_0045ef4f
    L_0045ef33:
        lea eax,[esi+esi]
    L_0045ef36:
        push eax
    L_0045ef37:
        call asm_malloc_00452706
    L_0045ef3c:
        pop ecx
    L_0045ef3d:
        mov dword ptr [ebp-1Ch],eax
    L_0045ef40:
        cmp eax,ebx
    L_0045ef42:
        je asm_target_0045f0ab
    L_0045ef48:
        mov dword ptr [ebp-3Ch],1
    L_0045ef4f:
        push esi
    L_0045ef50:
        push dword ptr [ebp-1Ch]
    L_0045ef53:
        push dword ptr [ebp+14h]
    L_0045ef56:
        push dword ptr [ebp+10h]
    L_0045ef59:
        push 1
    L_0045ef5b:
        push dword ptr [ebp+20h]
    L_0045ef5e:
        call dword ptr [data_00466104]
    L_0045ef64:
        test eax,eax
    L_0045ef66:
        je asm_target_0045f052
    L_0045ef6c:
        push ebx
    L_0045ef6d:
        push ebx
    L_0045ef6e:
        push esi
    L_0045ef6f:
        push dword ptr [ebp-1Ch]
    L_0045ef72:
        push dword ptr [ebp+0Ch]
    L_0045ef75:
        push dword ptr [ebp+8]
    L_0045ef78:
        call dword ptr [data_0046603c]
    L_0045ef7e:
        mov edi,eax
    L_0045ef80:
        mov dword ptr [ebp-2Ch],edi
    L_0045ef83:
        cmp edi,ebx
    L_0045ef85:
        je asm_target_0045f052
    L_0045ef8b:
        test byte ptr [ebp+0Dh],4
    L_0045ef8f:
        je short L_0045efbe
    L_0045ef91:
        cmp dword ptr [ebp+1Ch],ebx
    L_0045ef94:
        je asm_target_0045f052
    L_0045ef9a:
        cmp edi,dword ptr [ebp+1Ch]
    L_0045ef9d:
        jg asm_target_0045f052
    L_0045efa3:
        push dword ptr [ebp+1Ch]
    L_0045efa6:
        push dword ptr [ebp+18h]
    L_0045efa9:
        push esi
    L_0045efaa:
        push dword ptr [ebp-1Ch]
    L_0045efad:
        push dword ptr [ebp+0Ch]
    L_0045efb0:
        push dword ptr [ebp+8]
    L_0045efb3:
        call dword ptr [data_0046603c]
    L_0045efb9:
        jmp asm_target_0045f052
    L_0045efbe:
        mov dword ptr [ebp-4],2
    L_0045efc5:
        lea eax,[edi+edi]
    L_0045efc8:
        add eax,3
    L_0045efcb:
        and eax,0FFFFFFFCh
    L_0045efce:
        call asm_chkstk_00458ec0
    L_0045efd3:
        mov dword ptr [ebp-18h],esp
    L_0045efd6:
        mov eax,esp
    L_0045efd8:
        mov dword ptr [ebp-20h],eax
    L_0045efdb:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045efdf:
        TH10_REL8(0xeb, 0x0045efdf, VA_asm_FUN_0045ee1d_part_0045effc)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0xe8
        _emit 0xa4
        _emit 0x9d
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x89
        _emit 0x5d
        _emit 0xe0
        _emit 0x83
        _emit 0x4d
        _emit 0xfc
        _emit 0xff
        _emit 0x8b
        _emit 0x7d
        _emit 0xd4
        _emit 0x8b
        _emit 0x75
        _emit 0xcc

    L_0045effc:
        cmp dword ptr [ebp-20h],ebx
    L_0045efff:
        jne short L_0045f019
    L_0045f001:
        lea eax,[edi+edi]
    L_0045f004:
        push eax
    L_0045f005:
        call asm_malloc_00452706
    L_0045f00a:
        pop ecx
    L_0045f00b:
        mov dword ptr [ebp-20h],eax
    L_0045f00e:
        cmp eax,ebx
    L_0045f010:
        je short L_0045f052
    L_0045f012:
        mov dword ptr [ebp-38h],1
    L_0045f019:
        push edi
    L_0045f01a:
        push dword ptr [ebp-20h]
    L_0045f01d:
        push esi
    L_0045f01e:
        push dword ptr [ebp-1Ch]
    L_0045f021:
        push dword ptr [ebp+0Ch]
    L_0045f024:
        push dword ptr [ebp+8]
    L_0045f027:
        call dword ptr [data_0046603c]
    L_0045f02d:
        test eax,eax
    L_0045f02f:
        je short L_0045f052
    L_0045f031:
        push ebx
    L_0045f032:
        push ebx
    L_0045f033:
        cmp dword ptr [ebp+1Ch],ebx
    L_0045f036:
        jne short L_0045f03c
    L_0045f038:
        push ebx
    L_0045f039:
        push ebx
    L_0045f03a:
        jmp short L_0045f042
    L_0045f03c:
        push dword ptr [ebp+1Ch]
    L_0045f03f:
        push dword ptr [ebp+18h]
    L_0045f042:
        push edi
    L_0045f043:
        push dword ptr [ebp-20h]
    L_0045f046:
        push ebx
    L_0045f047:
        push dword ptr [ebp+20h]
    L_0045f04a:
        call dword ptr [data_00466154]
    L_0045f050:
        mov edi,eax
    L_0045f052:
        cmp dword ptr [ebp-38h],ebx
    L_0045f055:
        je short L_0045f060
    L_0045f057:
        push dword ptr [ebp-20h]
    L_0045f05a:
        call asm_free_00452422
    L_0045f05f:
        pop ecx
    L_0045f060:
        cmp dword ptr [ebp-3Ch],ebx
    L_0045f063:
        je short L_0045f06e
    L_0045f065:
        push dword ptr [ebp-1Ch]
    L_0045f068:
        call asm_free_00452422
    L_0045f06d:
        pop ecx
    L_0045f06e:
        mov eax,edi
    L_0045f070:
        jmp asm_target_0045f1ea
    L_0045f075:
        mov dword ptr [ebp-28h],ebx
    L_0045f078:
        xor edi,edi
    L_0045f07a:
        mov dword ptr [ebp-30h],ebx
    L_0045f07d:
        mov dword ptr [ebp-40h],ebx
    L_0045f080:
        cmp dword ptr [ebp+8],ebx
    L_0045f083:
        jne short L_0045f08d
    L_0045f085:
        mov eax,dword ptr [data_00477654]
    L_0045f08a:
        mov dword ptr [ebp+8],eax
    L_0045f08d:
        cmp dword ptr [ebp+20h],ebx
    L_0045f090:
        jne short L_0045f09a
    L_0045f092:
        mov eax,dword ptr [data_00477664]
    L_0045f097:
        mov dword ptr [ebp+20h],eax
    L_0045f09a:
        push dword ptr [ebp+8]
    L_0045f09d:
        call asm_FUN_004601a1_004601a1
    L_0045f0a2:
        pop ecx
    L_0045f0a3:
        mov dword ptr [ebp-44h],eax
    L_0045f0a6:
        cmp eax,0FFFFFFFFh
    L_0045f0a9:
        jne short L_0045f0b2
    L_0045f0ab:
        xor eax,eax
    L_0045f0ad:
        jmp asm_target_0045f1ea
    L_0045f0b2:
        cmp eax,dword ptr [ebp+20h]
    L_0045f0b5:
        je asm_target_0045f1ad
    L_0045f0bb:
        push ebx
    L_0045f0bc:
        push ebx
    L_0045f0bd:
        lea ecx,[ebp+14h]
    L_0045f0c0:
        push ecx
    L_0045f0c1:
        push dword ptr [ebp+10h]
    L_0045f0c4:
        push eax
    L_0045f0c5:
        push dword ptr [ebp+20h]
    L_0045f0c8:
        call asm_FUN_004601e8_004601e8
    L_0045f0cd:
        add esp,18h
    L_0045f0d0:
        mov dword ptr [ebp-28h],eax
    L_0045f0d3:
        cmp eax,ebx
    L_0045f0d5:
        je short L_0045f0ab
    L_0045f0d7:
        push ebx
    L_0045f0d8:
        push ebx
    L_0045f0d9:
        push dword ptr [ebp+14h]
    L_0045f0dc:
        push eax
    L_0045f0dd:
        push dword ptr [ebp+0Ch]
    L_0045f0e0:
        push dword ptr [ebp+8]
    L_0045f0e3:
        call dword ptr [data_00466040]
    L_0045f0e9:
        mov esi,eax
    L_0045f0eb:
        mov dword ptr [ebp-24h],esi
    L_0045f0ee:
        cmp esi,ebx
    L_0045f0f0:
        je asm_target_0045f19c
    L_0045f0f6:
        mov dword ptr [ebp-4],ebx
    L_0045f0f9:
        add eax,3
    L_0045f0fc:
        and eax,0FFFFFFFCh
    L_0045f0ff:
        call asm_chkstk_00458ec0
    L_0045f104:
        mov dword ptr [ebp-18h],esp
    L_0045f107:
        mov edi,esp
    L_0045f109:
        mov dword ptr [ebp-48h],edi
    L_0045f10c:
        push esi
    L_0045f10d:
        push ebx
    L_0045f10e:
        push edi
    L_0045f10f:
        call asm_memset_0045bed0
    L_0045f114:
        add esp,0Ch
    L_0045f117:
        TH10_REL8(0xeb, 0x0045f117, VA_asm_FUN_0045ee1d_part_0045f129)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0xe8
        _emit 0x6c
        _emit 0x9c
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x33
        _emit 0xff

    L_0045f129:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045f12d:
        cmp edi,ebx
    L_0045f12f:
        jne short L_0045f154
    L_0045f131:
        push dword ptr [ebp-24h]
    L_0045f134:
        call asm_malloc_00452706
    L_0045f139:
        pop ecx
    L_0045f13a:
        mov edi,eax
    L_0045f13c:
        cmp edi,ebx
    L_0045f13e:
        je short L_0045f171
    L_0045f140:
        push dword ptr [ebp-24h]
    L_0045f143:
        push ebx
    L_0045f144:
        push edi
    L_0045f145:
        call asm_memset_0045bed0
    L_0045f14a:
        add esp,0Ch
    L_0045f14d:
        mov dword ptr [ebp-40h],1
    L_0045f154:
        push dword ptr [ebp-24h]
    L_0045f157:
        push edi
    L_0045f158:
        push dword ptr [ebp+14h]
    L_0045f15b:
        push dword ptr [ebp-28h]
    L_0045f15e:
        push dword ptr [ebp+0Ch]
    L_0045f161:
        push dword ptr [ebp+8]
    L_0045f164:
        call dword ptr [data_00466040]
    L_0045f16a:
        mov dword ptr [ebp-24h],eax
    L_0045f16d:
        cmp eax,ebx
    L_0045f16f:
        jne short L_0045f175
    L_0045f171:
        xor esi,esi
    L_0045f173:
        jmp short L_0045f19f
    L_0045f175:
        push dword ptr [ebp+1Ch]
    L_0045f178:
        push dword ptr [ebp+18h]
    L_0045f17b:
        lea eax,[ebp-24h]
    L_0045f17e:
        push eax
    L_0045f17f:
        push edi
    L_0045f180:
        push dword ptr [ebp+20h]
    L_0045f183:
        push dword ptr [ebp-44h]
    L_0045f186:
        call asm_FUN_004601e8_004601e8
    L_0045f18b:
        add esp,18h
    L_0045f18e:
        mov esi,eax
    L_0045f190:
        mov dword ptr [ebp-30h],esi
    L_0045f193:
        neg esi
    L_0045f195:
        sbb esi,esi
    L_0045f197:
        and esi,dword ptr [ebp-24h]
    L_0045f19a:
        jmp short L_0045f19f
    L_0045f19c:
        mov esi,dword ptr [ebp-4Ch]
    L_0045f19f:
        cmp dword ptr [ebp-40h],ebx
    L_0045f1a2:
        je short L_0045f1c7
    L_0045f1a4:
        push edi
    L_0045f1a5:
        call asm_free_00452422
    L_0045f1aa:
        pop ecx
    L_0045f1ab:
        jmp short L_0045f1c7
    L_0045f1ad:
        push dword ptr [ebp+1Ch]
    L_0045f1b0:
        push dword ptr [ebp+18h]
    L_0045f1b3:
        push dword ptr [ebp+14h]
    L_0045f1b6:
        push dword ptr [ebp+10h]
    L_0045f1b9:
        push dword ptr [ebp+0Ch]
    L_0045f1bc:
        push dword ptr [ebp+8]
    L_0045f1bf:
        call dword ptr [data_00466040]
    L_0045f1c5:
        mov esi,eax
    L_0045f1c7:
        cmp dword ptr [ebp-28h],ebx
    L_0045f1ca:
        je short L_0045f1d5
    L_0045f1cc:
        push dword ptr [ebp-28h]
    L_0045f1cf:
        call asm_free_00452422
    L_0045f1d4:
        pop ecx
    L_0045f1d5:
        mov eax,dword ptr [ebp-30h]
    L_0045f1d8:
        cmp eax,ebx
    L_0045f1da:
        je short L_0045f1e8
    L_0045f1dc:
        cmp dword ptr [ebp+18h],eax
    L_0045f1df:
        je short L_0045f1e8
    L_0045f1e1:
        push eax
    L_0045f1e2:
        call asm_free_00452422
    L_0045f1e7:
        pop ecx
    L_0045f1e8:
        mov eax,esi
    L_0045f1ea:
        lea esp,[ebp-58h]
    L_0045f1ed:
        call asm_SEH_epilog_00454bf7
    L_0045f1f2:
        ret
    }
}
