#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3304): closest_byte_count=2452/2452; first_diff=none;
// residual_class=private EAX object receiver plus ECX selector token and
// repeated hidden Find/Configure register handoffs; a standalone readable
// declaration cannot preserve the private ABI or retail loop scheduling.
// variants_tested=live Ghidra decompilation, callers/callees/xrefs and
// variable audit (callers 0x0042F540 and 0x00430250; callees 0x004491C0 and
// 0x0043E5A0), plus MSVC 13.10 exact baseline probe. next_lever=schema2
// native-LTCG cluster joining both real callers, this body, Find, and
// ConfigureFromResource; current overlay remains exact.


// 0x0042F8B0..0x0042F953: FUN_0042f8b0
// Naked body preserves the retail register/stack ABI.

// 0x0042F8B0..0x0042F953: FUN_0042f8b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042f8b0_0042f8b0() {
    __asm {
    L_0042f8b0:
        push ebx
    L_0042f8b1:
        push esi
    L_0042f8b2:
        push edi
    L_0042f8b3:
        mov edi,dword ptr [data_00491c10]
    L_0042f8b9:
        mov esi,eax
    L_0042f8bb:
        mov eax,dword ptr [esi+2CCh]
    L_0042f8c1:
        push eax
    L_0042f8c2:
        mov edx,edi
    L_0042f8c4:
        call asm_AnimationManager_Find_004491c0
    L_0042f8c9:
        xor ebx,ebx
    L_0042f8cb:
        cmp eax,ebx
    L_0042f8cd:
        jne short L_0042f8d5
    L_0042f8cf:
        mov dword ptr [esi+2CCh],ebx
    L_0042f8d5:
        add eax,10h
    L_0042f8d8:
        cmp eax,ebx
    L_0042f8da:
        je short L_0042f8f7
    L_0042f8dc:
        mov ecx,43h
    L_0042f8e1:
        mov edx,dword ptr [eax]
    L_0042f8e3:
        cmp word ptr [edx+38Ah],cx
    L_0042f8ea:
        je asm_target_0043018d
    L_0042f8f0:
        mov eax,dword ptr [eax+4]
    L_0042f8f3:
        cmp eax,ebx
    L_0042f8f5:
        jne short L_0042f8e1
    L_0042f8f7:
        xor eax,eax
    L_0042f8f9:
        push eax
    L_0042f8fa:
        mov edx,edi
    L_0042f8fc:
        call asm_AnimationManager_Find_004491c0
    L_0042f901:
        mov ecx,eax
    L_0042f903:
        cmp ecx,ebx
    L_0042f905:
        je short L_0042f92e
    L_0042f907:
        movsx edx,word ptr [esi+59CCh]
    L_0042f90e:
        mov eax,66666667h
    L_0042f913:
        imul edx
    L_0042f915:
        sar edx,2
    L_0042f918:
        mov eax,edx
    L_0042f91a:
        shr eax,1Fh
    L_0042f91d:
        lea edx,[edx+eax+33h]
    L_0042f921:
        mov eax,ecx
    L_0042f923:
        mov ecx,dword ptr [ecx+308h]
    L_0042f929:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042f92e:
        mov ecx,dword ptr [esi+2CCh]
    L_0042f934:
        push ecx
    L_0042f935:
        mov edx,edi
    L_0042f937:
        call asm_AnimationManager_Find_004491c0
    L_0042f93c:
        cmp eax,ebx
    L_0042f93e:
        jne short L_0042f946
    L_0042f940:
        mov dword ptr [esi+2CCh],ebx
    L_0042f946:
        add eax,10h
    L_0042f949:
        cmp eax,ebx
    L_0042f94b:
        TH10_REL8(0x74, 0x0042f94b, VA_asm_target_0042f976)
    L_0042f94d:
        mov ecx,44h
    L_0042f952:
        TH10_REL8(0xeb, 0x0042f952, VA_asm_FUN_0042f8b0_part_0042f960)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x03
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042f960:
        mov edx,dword ptr [eax]
    L_0042f962:
        cmp word ptr [edx+38Ah],cx
    L_0042f969:
        je asm_target_00430196
    L_0042f96f:
        mov eax,dword ptr [eax+4]
    L_0042f972:
        cmp eax,ebx
    L_0042f974:
        jne short L_0042f960
    L_0042f976:
        xor eax,eax
    L_0042f978:
        push ebp
    L_0042f979:
        push eax
    L_0042f97a:
        mov edx,edi
    L_0042f97c:
        call asm_AnimationManager_Find_004491c0
    L_0042f981:
        mov ecx,eax
    L_0042f983:
        cmp ecx,ebx
    L_0042f985:
        je short L_0042f9a6
    L_0042f987:
        movsx eax,word ptr [esi+59CCh]
    L_0042f98e:
        cdq
    L_0042f98f:
        mov ebp,0Ah
    L_0042f994:
        idiv ebp
    L_0042f996:
        mov eax,ecx
    L_0042f998:
        mov ecx,dword ptr [ecx+308h]
    L_0042f99e:
        add edx,33h
    L_0042f9a1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042f9a6:
        mov ecx,dword ptr [esi+2CCh]
    L_0042f9ac:
        push ecx
    L_0042f9ad:
        mov edx,edi
    L_0042f9af:
        call asm_AnimationManager_Find_004491c0
    L_0042f9b4:
        cmp eax,ebx
    L_0042f9b6:
        jne short L_0042f9be
    L_0042f9b8:
        mov dword ptr [esi+2CCh],ebx
    L_0042f9be:
        add eax,10h
    L_0042f9c1:
        cmp eax,ebx
    L_0042f9c3:
        je short L_0042f9e6
    L_0042f9c5:
        mov ecx,4Dh
    L_0042f9ca:
        lea ebx,[ebx+force_disp32_zero]
    L_0042f9d0:
        mov edx,dword ptr [eax]
    L_0042f9d2:
        cmp word ptr [edx+38Ah],cx
    L_0042f9d9:
        je asm_target_0043019f
    L_0042f9df:
        mov eax,dword ptr [eax+4]
    L_0042f9e2:
        cmp eax,ebx
    L_0042f9e4:
        jne short L_0042f9d0
    L_0042f9e6:
        xor eax,eax
    L_0042f9e8:
        push eax
    L_0042f9e9:
        mov edx,edi
    L_0042f9eb:
        call asm_AnimationManager_Find_004491c0
    L_0042f9f0:
        mov ecx,eax
    L_0042f9f2:
        cmp ecx,ebx
    L_0042f9f4:
        je short L_0042fa1d
    L_0042f9f6:
        movsx edx,word ptr [esi+59CCh]
    L_0042f9fd:
        mov eax,66666667h
    L_0042fa02:
        imul edx
    L_0042fa04:
        sar edx,2
    L_0042fa07:
        mov eax,edx
    L_0042fa09:
        shr eax,1Fh
    L_0042fa0c:
        lea edx,[edx+eax+33h]
    L_0042fa10:
        mov eax,ecx
    L_0042fa12:
        mov ecx,dword ptr [ecx+308h]
    L_0042fa18:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fa1d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fa23:
        push ecx
    L_0042fa24:
        mov edx,edi
    L_0042fa26:
        call asm_AnimationManager_Find_004491c0
    L_0042fa2b:
        cmp eax,ebx
    L_0042fa2d:
        jne short L_0042fa35
    L_0042fa2f:
        mov dword ptr [esi+2CCh],ebx
    L_0042fa35:
        add eax,10h
    L_0042fa38:
        cmp eax,ebx
    L_0042fa3a:
        je short L_0042fa57
    L_0042fa3c:
        mov ecx,4Eh
    L_0042fa41:
        mov edx,dword ptr [eax]
    L_0042fa43:
        cmp word ptr [edx+38Ah],cx
    L_0042fa4a:
        je asm_target_004301a8
    L_0042fa50:
        mov eax,dword ptr [eax+4]
    L_0042fa53:
        cmp eax,ebx
    L_0042fa55:
        jne short L_0042fa41
    L_0042fa57:
        xor eax,eax
    L_0042fa59:
        push eax
    L_0042fa5a:
        mov edx,edi
    L_0042fa5c:
        call asm_AnimationManager_Find_004491c0
    L_0042fa61:
        mov ecx,eax
    L_0042fa63:
        cmp ecx,ebx
    L_0042fa65:
        je short L_0042fa86
    L_0042fa67:
        movsx eax,word ptr [esi+59CCh]
    L_0042fa6e:
        cdq
    L_0042fa6f:
        mov ebp,0Ah
    L_0042fa74:
        idiv ebp
    L_0042fa76:
        mov eax,ecx
    L_0042fa78:
        mov ecx,dword ptr [ecx+308h]
    L_0042fa7e:
        add edx,33h
    L_0042fa81:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fa86:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fa8c:
        push ecx
    L_0042fa8d:
        mov edx,edi
    L_0042fa8f:
        call asm_AnimationManager_Find_004491c0
    L_0042fa94:
        cmp eax,ebx
    L_0042fa96:
        jne short L_0042fa9e
    L_0042fa98:
        mov dword ptr [esi+2CCh],ebx
    L_0042fa9e:
        add eax,10h
    L_0042faa1:
        cmp eax,ebx
    L_0042faa3:
        je short L_0042fac6
    L_0042faa5:
        mov ecx,45h
    L_0042faaa:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fab0:
        mov edx,dword ptr [eax]
    L_0042fab2:
        cmp word ptr [edx+38Ah],cx
    L_0042fab9:
        je asm_target_004301b1
    L_0042fabf:
        mov eax,dword ptr [eax+4]
    L_0042fac2:
        cmp eax,ebx
    L_0042fac4:
        jne short L_0042fab0
    L_0042fac6:
        xor eax,eax
    L_0042fac8:
        push eax
    L_0042fac9:
        mov edx,edi
    L_0042facb:
        call asm_AnimationManager_Find_004491c0
    L_0042fad0:
        mov ecx,eax
    L_0042fad2:
        cmp ecx,ebx
    L_0042fad4:
        je short L_0042fafd
    L_0042fad6:
        movsx edx,word ptr [esi+59CEh]
    L_0042fadd:
        mov eax,66666667h
    L_0042fae2:
        imul edx
    L_0042fae4:
        sar edx,2
    L_0042fae7:
        mov eax,edx
    L_0042fae9:
        shr eax,1Fh
    L_0042faec:
        lea edx,[edx+eax+33h]
    L_0042faf0:
        mov eax,ecx
    L_0042faf2:
        mov ecx,dword ptr [ecx+308h]
    L_0042faf8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fafd:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fb03:
        push ecx
    L_0042fb04:
        mov edx,edi
    L_0042fb06:
        call asm_AnimationManager_Find_004491c0
    L_0042fb0b:
        cmp eax,ebx
    L_0042fb0d:
        jne short L_0042fb15
    L_0042fb0f:
        mov dword ptr [esi+2CCh],ebx
    L_0042fb15:
        add eax,10h
    L_0042fb18:
        cmp eax,ebx
    L_0042fb1a:
        je short L_0042fb37
    L_0042fb1c:
        mov ecx,46h
    L_0042fb21:
        mov edx,dword ptr [eax]
    L_0042fb23:
        cmp word ptr [edx+38Ah],cx
    L_0042fb2a:
        je asm_target_004301ba
    L_0042fb30:
        mov eax,dword ptr [eax+4]
    L_0042fb33:
        cmp eax,ebx
    L_0042fb35:
        jne short L_0042fb21
    L_0042fb37:
        xor eax,eax
    L_0042fb39:
        push eax
    L_0042fb3a:
        mov edx,edi
    L_0042fb3c:
        call asm_AnimationManager_Find_004491c0
    L_0042fb41:
        mov ecx,eax
    L_0042fb43:
        cmp ecx,ebx
    L_0042fb45:
        je short L_0042fb66
    L_0042fb47:
        movsx eax,word ptr [esi+59CEh]
    L_0042fb4e:
        cdq
    L_0042fb4f:
        mov ebp,0Ah
    L_0042fb54:
        idiv ebp
    L_0042fb56:
        mov eax,ecx
    L_0042fb58:
        mov ecx,dword ptr [ecx+308h]
    L_0042fb5e:
        add edx,33h
    L_0042fb61:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fb66:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fb6c:
        push ecx
    L_0042fb6d:
        mov edx,edi
    L_0042fb6f:
        call asm_AnimationManager_Find_004491c0
    L_0042fb74:
        cmp eax,ebx
    L_0042fb76:
        jne short L_0042fb7e
    L_0042fb78:
        mov dword ptr [esi+2CCh],ebx
    L_0042fb7e:
        add eax,10h
    L_0042fb81:
        cmp eax,ebx
    L_0042fb83:
        je short L_0042fba6
    L_0042fb85:
        mov ecx,4Fh
    L_0042fb8a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fb90:
        mov edx,dword ptr [eax]
    L_0042fb92:
        cmp word ptr [edx+38Ah],cx
    L_0042fb99:
        je asm_target_004301c3
    L_0042fb9f:
        mov eax,dword ptr [eax+4]
    L_0042fba2:
        cmp eax,ebx
    L_0042fba4:
        jne short L_0042fb90
    L_0042fba6:
        xor eax,eax
    L_0042fba8:
        push eax
    L_0042fba9:
        mov edx,edi
    L_0042fbab:
        call asm_AnimationManager_Find_004491c0
    L_0042fbb0:
        mov ecx,eax
    L_0042fbb2:
        cmp ecx,ebx
    L_0042fbb4:
        je short L_0042fbdd
    L_0042fbb6:
        movsx edx,word ptr [esi+59CEh]
    L_0042fbbd:
        mov eax,66666667h
    L_0042fbc2:
        imul edx
    L_0042fbc4:
        sar edx,2
    L_0042fbc7:
        mov eax,edx
    L_0042fbc9:
        shr eax,1Fh
    L_0042fbcc:
        lea edx,[edx+eax+33h]
    L_0042fbd0:
        mov eax,ecx
    L_0042fbd2:
        mov ecx,dword ptr [ecx+308h]
    L_0042fbd8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fbdd:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fbe3:
        push ecx
    L_0042fbe4:
        mov edx,edi
    L_0042fbe6:
        call asm_AnimationManager_Find_004491c0
    L_0042fbeb:
        cmp eax,ebx
    L_0042fbed:
        jne short L_0042fbf5
    L_0042fbef:
        mov dword ptr [esi+2CCh],ebx
    L_0042fbf5:
        add eax,10h
    L_0042fbf8:
        cmp eax,ebx
    L_0042fbfa:
        je short L_0042fc17
    L_0042fbfc:
        mov ecx,50h
    L_0042fc01:
        mov edx,dword ptr [eax]
    L_0042fc03:
        cmp word ptr [edx+38Ah],cx
    L_0042fc0a:
        je asm_target_004301cc
    L_0042fc10:
        mov eax,dword ptr [eax+4]
    L_0042fc13:
        cmp eax,ebx
    L_0042fc15:
        jne short L_0042fc01
    L_0042fc17:
        xor eax,eax
    L_0042fc19:
        push eax
    L_0042fc1a:
        mov edx,edi
    L_0042fc1c:
        call asm_AnimationManager_Find_004491c0
    L_0042fc21:
        mov ecx,eax
    L_0042fc23:
        cmp ecx,ebx
    L_0042fc25:
        je short L_0042fc46
    L_0042fc27:
        movsx eax,word ptr [esi+59CEh]
    L_0042fc2e:
        cdq
    L_0042fc2f:
        mov ebp,0Ah
    L_0042fc34:
        idiv ebp
    L_0042fc36:
        mov eax,ecx
    L_0042fc38:
        mov ecx,dword ptr [ecx+308h]
    L_0042fc3e:
        add edx,33h
    L_0042fc41:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fc46:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fc4c:
        push ecx
    L_0042fc4d:
        mov edx,edi
    L_0042fc4f:
        call asm_AnimationManager_Find_004491c0
    L_0042fc54:
        cmp eax,ebx
    L_0042fc56:
        jne short L_0042fc5e
    L_0042fc58:
        mov dword ptr [esi+2CCh],ebx
    L_0042fc5e:
        add eax,10h
    L_0042fc61:
        cmp eax,ebx
    L_0042fc63:
        je short L_0042fc86
    L_0042fc65:
        mov ecx,47h
    L_0042fc6a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fc70:
        mov edx,dword ptr [eax]
    L_0042fc72:
        cmp word ptr [edx+38Ah],cx
    L_0042fc79:
        je asm_target_004301d5
    L_0042fc7f:
        mov eax,dword ptr [eax+4]
    L_0042fc82:
        cmp eax,ebx
    L_0042fc84:
        jne short L_0042fc70
    L_0042fc86:
        xor eax,eax
    L_0042fc88:
        push eax
    L_0042fc89:
        mov edx,edi
    L_0042fc8b:
        call asm_AnimationManager_Find_004491c0
    L_0042fc90:
        mov ecx,eax
    L_0042fc92:
        cmp ecx,ebx
    L_0042fc94:
        je short L_0042fcbd
    L_0042fc96:
        movsx edx,word ptr [esi+59D0h]
    L_0042fc9d:
        mov eax,66666667h
    L_0042fca2:
        imul edx
    L_0042fca4:
        sar edx,2
    L_0042fca7:
        mov eax,edx
    L_0042fca9:
        shr eax,1Fh
    L_0042fcac:
        lea edx,[edx+eax+33h]
    L_0042fcb0:
        mov eax,ecx
    L_0042fcb2:
        mov ecx,dword ptr [ecx+308h]
    L_0042fcb8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fcbd:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fcc3:
        push ecx
    L_0042fcc4:
        mov edx,edi
    L_0042fcc6:
        call asm_AnimationManager_Find_004491c0
    L_0042fccb:
        cmp eax,ebx
    L_0042fccd:
        jne short L_0042fcd5
    L_0042fccf:
        mov dword ptr [esi+2CCh],ebx
    L_0042fcd5:
        add eax,10h
    L_0042fcd8:
        cmp eax,ebx
    L_0042fcda:
        je short L_0042fcf7
    L_0042fcdc:
        mov ecx,48h
    L_0042fce1:
        mov edx,dword ptr [eax]
    L_0042fce3:
        cmp word ptr [edx+38Ah],cx
    L_0042fcea:
        je asm_target_004301de
    L_0042fcf0:
        mov eax,dword ptr [eax+4]
    L_0042fcf3:
        cmp eax,ebx
    L_0042fcf5:
        jne short L_0042fce1
    L_0042fcf7:
        xor eax,eax
    L_0042fcf9:
        push eax
    L_0042fcfa:
        mov edx,edi
    L_0042fcfc:
        call asm_AnimationManager_Find_004491c0
    L_0042fd01:
        mov ecx,eax
    L_0042fd03:
        cmp ecx,ebx
    L_0042fd05:
        je short L_0042fd26
    L_0042fd07:
        movsx eax,word ptr [esi+59D0h]
    L_0042fd0e:
        cdq
    L_0042fd0f:
        mov ebp,0Ah
    L_0042fd14:
        idiv ebp
    L_0042fd16:
        mov eax,ecx
    L_0042fd18:
        mov ecx,dword ptr [ecx+308h]
    L_0042fd1e:
        add edx,33h
    L_0042fd21:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fd26:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fd2c:
        push ecx
    L_0042fd2d:
        mov edx,edi
    L_0042fd2f:
        call asm_AnimationManager_Find_004491c0
    L_0042fd34:
        cmp eax,ebx
    L_0042fd36:
        jne short L_0042fd3e
    L_0042fd38:
        mov dword ptr [esi+2CCh],ebx
    L_0042fd3e:
        add eax,10h
    L_0042fd41:
        cmp eax,ebx
    L_0042fd43:
        je short L_0042fd66
    L_0042fd45:
        mov ecx,51h
    L_0042fd4a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fd50:
        mov edx,dword ptr [eax]
    L_0042fd52:
        cmp word ptr [edx+38Ah],cx
    L_0042fd59:
        je asm_target_004301e7
    L_0042fd5f:
        mov eax,dword ptr [eax+4]
    L_0042fd62:
        cmp eax,ebx
    L_0042fd64:
        jne short L_0042fd50
    L_0042fd66:
        xor eax,eax
    L_0042fd68:
        push eax
    L_0042fd69:
        mov edx,edi
    L_0042fd6b:
        call asm_AnimationManager_Find_004491c0
    L_0042fd70:
        mov ecx,eax
    L_0042fd72:
        cmp ecx,ebx
    L_0042fd74:
        je short L_0042fd9d
    L_0042fd76:
        movsx edx,word ptr [esi+59D0h]
    L_0042fd7d:
        mov eax,66666667h
    L_0042fd82:
        imul edx
    L_0042fd84:
        sar edx,2
    L_0042fd87:
        mov eax,edx
    L_0042fd89:
        shr eax,1Fh
    L_0042fd8c:
        lea edx,[edx+eax+33h]
    L_0042fd90:
        mov eax,ecx
    L_0042fd92:
        mov ecx,dword ptr [ecx+308h]
    L_0042fd98:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fd9d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fda3:
        push ecx
    L_0042fda4:
        mov edx,edi
    L_0042fda6:
        call asm_AnimationManager_Find_004491c0
    L_0042fdab:
        cmp eax,ebx
    L_0042fdad:
        jne short L_0042fdb5
    L_0042fdaf:
        mov dword ptr [esi+2CCh],ebx
    L_0042fdb5:
        add eax,10h
    L_0042fdb8:
        cmp eax,ebx
    L_0042fdba:
        je short L_0042fdd7
    L_0042fdbc:
        mov ecx,52h
    L_0042fdc1:
        mov edx,dword ptr [eax]
    L_0042fdc3:
        cmp word ptr [edx+38Ah],cx
    L_0042fdca:
        je asm_target_004301f0
    L_0042fdd0:
        mov eax,dword ptr [eax+4]
    L_0042fdd3:
        cmp eax,ebx
    L_0042fdd5:
        jne short L_0042fdc1
    L_0042fdd7:
        xor eax,eax
    L_0042fdd9:
        push eax
    L_0042fdda:
        mov edx,edi
    L_0042fddc:
        call asm_AnimationManager_Find_004491c0
    L_0042fde1:
        mov ecx,eax
    L_0042fde3:
        cmp ecx,ebx
    L_0042fde5:
        je short L_0042fe06
    L_0042fde7:
        movsx eax,word ptr [esi+59D0h]
    L_0042fdee:
        cdq
    L_0042fdef:
        mov ebp,0Ah
    L_0042fdf4:
        idiv ebp
    L_0042fdf6:
        mov eax,ecx
    L_0042fdf8:
        mov ecx,dword ptr [ecx+308h]
    L_0042fdfe:
        add edx,33h
    L_0042fe01:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fe06:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fe0c:
        push ecx
    L_0042fe0d:
        mov edx,edi
    L_0042fe0f:
        call asm_AnimationManager_Find_004491c0
    L_0042fe14:
        cmp eax,ebx
    L_0042fe16:
        jne short L_0042fe1e
    L_0042fe18:
        mov dword ptr [esi+2CCh],ebx
    L_0042fe1e:
        add eax,10h
    L_0042fe21:
        cmp eax,ebx
    L_0042fe23:
        je short L_0042fe46
    L_0042fe25:
        mov ecx,49h
    L_0042fe2a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fe30:
        mov edx,dword ptr [eax]
    L_0042fe32:
        cmp word ptr [edx+38Ah],cx
    L_0042fe39:
        je asm_target_004301f9
    L_0042fe3f:
        mov eax,dword ptr [eax+4]
    L_0042fe42:
        cmp eax,ebx
    L_0042fe44:
        jne short L_0042fe30
    L_0042fe46:
        xor eax,eax
    L_0042fe48:
        push eax
    L_0042fe49:
        mov edx,edi
    L_0042fe4b:
        call asm_AnimationManager_Find_004491c0
    L_0042fe50:
        mov ecx,eax
    L_0042fe52:
        cmp ecx,ebx
    L_0042fe54:
        je short L_0042fe7d
    L_0042fe56:
        movsx edx,word ptr [esi+59D2h]
    L_0042fe5d:
        mov eax,66666667h
    L_0042fe62:
        imul edx
    L_0042fe64:
        sar edx,2
    L_0042fe67:
        mov eax,edx
    L_0042fe69:
        shr eax,1Fh
    L_0042fe6c:
        lea edx,[edx+eax+33h]
    L_0042fe70:
        mov eax,ecx
    L_0042fe72:
        mov ecx,dword ptr [ecx+308h]
    L_0042fe78:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fe7d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042fe83:
        push ecx
    L_0042fe84:
        mov edx,edi
    L_0042fe86:
        call asm_AnimationManager_Find_004491c0
    L_0042fe8b:
        cmp eax,ebx
    L_0042fe8d:
        jne short L_0042fe95
    L_0042fe8f:
        mov dword ptr [esi+2CCh],ebx
    L_0042fe95:
        add eax,10h
    L_0042fe98:
        cmp eax,ebx
    L_0042fe9a:
        je short L_0042feb7
    L_0042fe9c:
        mov ecx,4Ah
    L_0042fea1:
        mov edx,dword ptr [eax]
    L_0042fea3:
        cmp word ptr [edx+38Ah],cx
    L_0042feaa:
        je asm_target_00430202
    L_0042feb0:
        mov eax,dword ptr [eax+4]
    L_0042feb3:
        cmp eax,ebx
    L_0042feb5:
        jne short L_0042fea1
    L_0042feb7:
        xor eax,eax
    L_0042feb9:
        push eax
    L_0042feba:
        mov edx,edi
    L_0042febc:
        call asm_AnimationManager_Find_004491c0
    L_0042fec1:
        mov ecx,eax
    L_0042fec3:
        cmp ecx,ebx
    L_0042fec5:
        je short L_0042fee6
    L_0042fec7:
        movsx eax,word ptr [esi+59D2h]
    L_0042fece:
        cdq
    L_0042fecf:
        mov ebp,0Ah
    L_0042fed4:
        idiv ebp
    L_0042fed6:
        mov eax,ecx
    L_0042fed8:
        mov ecx,dword ptr [ecx+308h]
    L_0042fede:
        add edx,33h
    L_0042fee1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042fee6:
        mov ecx,dword ptr [esi+2CCh]
    L_0042feec:
        push ecx
    L_0042feed:
        mov edx,edi
    L_0042feef:
        call asm_AnimationManager_Find_004491c0
    L_0042fef4:
        cmp eax,ebx
    L_0042fef6:
        jne short L_0042fefe
    L_0042fef8:
        mov dword ptr [esi+2CCh],ebx
    L_0042fefe:
        add eax,10h
    L_0042ff01:
        cmp eax,ebx
    L_0042ff03:
        je short L_0042ff26
    L_0042ff05:
        mov ecx,53h
    L_0042ff0a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042ff10:
        mov edx,dword ptr [eax]
    L_0042ff12:
        cmp word ptr [edx+38Ah],cx
    L_0042ff19:
        je asm_target_0043020b
    L_0042ff1f:
        mov eax,dword ptr [eax+4]
    L_0042ff22:
        cmp eax,ebx
    L_0042ff24:
        jne short L_0042ff10
    L_0042ff26:
        xor eax,eax
    L_0042ff28:
        push eax
    L_0042ff29:
        mov edx,edi
    L_0042ff2b:
        call asm_AnimationManager_Find_004491c0
    L_0042ff30:
        mov ecx,eax
    L_0042ff32:
        cmp ecx,ebx
    L_0042ff34:
        je short L_0042ff5d
    L_0042ff36:
        movsx edx,word ptr [esi+59D2h]
    L_0042ff3d:
        mov eax,66666667h
    L_0042ff42:
        imul edx
    L_0042ff44:
        sar edx,2
    L_0042ff47:
        mov eax,edx
    L_0042ff49:
        shr eax,1Fh
    L_0042ff4c:
        lea edx,[edx+eax+33h]
    L_0042ff50:
        mov eax,ecx
    L_0042ff52:
        mov ecx,dword ptr [ecx+308h]
    L_0042ff58:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042ff5d:
        mov ecx,dword ptr [esi+2CCh]
    L_0042ff63:
        push ecx
    L_0042ff64:
        mov edx,edi
    L_0042ff66:
        call asm_AnimationManager_Find_004491c0
    L_0042ff6b:
        cmp eax,ebx
    L_0042ff6d:
        jne short L_0042ff75
    L_0042ff6f:
        mov dword ptr [esi+2CCh],ebx
    L_0042ff75:
        add eax,10h
    L_0042ff78:
        cmp eax,ebx
    L_0042ff7a:
        je short L_0042ff97
    L_0042ff7c:
        mov ecx,54h
    L_0042ff81:
        mov edx,dword ptr [eax]
    L_0042ff83:
        cmp word ptr [edx+38Ah],cx
    L_0042ff8a:
        je asm_target_00430214
    L_0042ff90:
        mov eax,dword ptr [eax+4]
    L_0042ff93:
        cmp eax,ebx
    L_0042ff95:
        jne short L_0042ff81
    L_0042ff97:
        xor eax,eax
    L_0042ff99:
        push eax
    L_0042ff9a:
        mov edx,edi
    L_0042ff9c:
        call asm_AnimationManager_Find_004491c0
    L_0042ffa1:
        mov ecx,eax
    L_0042ffa3:
        cmp ecx,ebx
    L_0042ffa5:
        je short L_0042ffc6
    L_0042ffa7:
        movsx eax,word ptr [esi+59D2h]
    L_0042ffae:
        cdq
    L_0042ffaf:
        mov ebp,0Ah
    L_0042ffb4:
        idiv ebp
    L_0042ffb6:
        mov eax,ecx
    L_0042ffb8:
        mov ecx,dword ptr [ecx+308h]
    L_0042ffbe:
        add edx,33h
    L_0042ffc1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0042ffc6:
        mov ecx,dword ptr [esi+2CCh]
    L_0042ffcc:
        push ecx
    L_0042ffcd:
        mov edx,edi
    L_0042ffcf:
        call asm_AnimationManager_Find_004491c0
    L_0042ffd4:
        cmp eax,ebx
    L_0042ffd6:
        jne short L_0042ffde
    L_0042ffd8:
        mov dword ptr [esi+2CCh],ebx
    L_0042ffde:
        add eax,10h
    L_0042ffe1:
        cmp eax,ebx
    L_0042ffe3:
        je short L_00430006
    L_0042ffe5:
        mov ecx,4Bh
    L_0042ffea:
        lea ebx,[ebx+force_disp32_zero]
    L_0042fff0:
        mov edx,dword ptr [eax]
    L_0042fff2:
        cmp word ptr [edx+38Ah],cx
    L_0042fff9:
        je asm_target_0043021d
    L_0042ffff:
        mov eax,dword ptr [eax+4]
    L_00430002:
        cmp eax,ebx
    L_00430004:
        jne short L_0042fff0
    L_00430006:
        xor eax,eax
    L_00430008:
        push eax
    L_00430009:
        mov edx,edi
    L_0043000b:
        call asm_AnimationManager_Find_004491c0
    L_00430010:
        mov ecx,eax
    L_00430012:
        cmp ecx,ebx
    L_00430014:
        je short L_0043003d
    L_00430016:
        movsx edx,word ptr [esi+59D4h]
    L_0043001d:
        mov eax,66666667h
    L_00430022:
        imul edx
    L_00430024:
        sar edx,2
    L_00430027:
        mov eax,edx
    L_00430029:
        shr eax,1Fh
    L_0043002c:
        lea edx,[edx+eax+33h]
    L_00430030:
        mov eax,ecx
    L_00430032:
        mov ecx,dword ptr [ecx+308h]
    L_00430038:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043003d:
        mov ecx,dword ptr [esi+2CCh]
    L_00430043:
        push ecx
    L_00430044:
        mov edx,edi
    L_00430046:
        call asm_AnimationManager_Find_004491c0
    L_0043004b:
        cmp eax,ebx
    L_0043004d:
        jne short L_00430055
    L_0043004f:
        mov dword ptr [esi+2CCh],ebx
    L_00430055:
        add eax,10h
    L_00430058:
        cmp eax,ebx
    L_0043005a:
        je short L_00430077
    L_0043005c:
        mov ecx,4Ch
    L_00430061:
        mov edx,dword ptr [eax]
    L_00430063:
        cmp word ptr [edx+38Ah],cx
    L_0043006a:
        je asm_target_00430226
    L_00430070:
        mov eax,dword ptr [eax+4]
    L_00430073:
        cmp eax,ebx
    L_00430075:
        jne short L_00430061
    L_00430077:
        xor eax,eax
    L_00430079:
        push eax
    L_0043007a:
        mov edx,edi
    L_0043007c:
        call asm_AnimationManager_Find_004491c0
    L_00430081:
        mov ecx,eax
    L_00430083:
        cmp ecx,ebx
    L_00430085:
        je short L_004300a6
    L_00430087:
        movsx eax,word ptr [esi+59D4h]
    L_0043008e:
        cdq
    L_0043008f:
        mov ebp,0Ah
    L_00430094:
        idiv ebp
    L_00430096:
        mov eax,ecx
    L_00430098:
        mov ecx,dword ptr [ecx+308h]
    L_0043009e:
        add edx,33h
    L_004300a1:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004300a6:
        mov ecx,dword ptr [esi+2CCh]
    L_004300ac:
        push ecx
    L_004300ad:
        mov edx,edi
    L_004300af:
        call asm_AnimationManager_Find_004491c0
    L_004300b4:
        cmp eax,ebx
    L_004300b6:
        pop ebp
    L_004300b7:
        jne short L_004300bf
    L_004300b9:
        mov dword ptr [esi+2CCh],ebx
    L_004300bf:
        add eax,10h
    L_004300c2:
        cmp eax,ebx
    L_004300c4:
        TH10_REL8(0x74, 0x004300c4, VA_asm_target_004300e6)
    L_004300c6:
        mov ecx,55h
    L_004300cb:
        TH10_REL8(0xeb, 0x004300cb, VA_asm_FUN_0042f8b0_part_004300d0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004300d0:
        mov edx,dword ptr [eax]
    L_004300d2:
        cmp word ptr [edx+38Ah],cx
    L_004300d9:
        je asm_target_0043022f
    L_004300df:
        mov eax,dword ptr [eax+4]
    L_004300e2:
        cmp eax,ebx
    L_004300e4:
        jne short L_004300d0
    L_004300e6:
        xor eax,eax
    L_004300e8:
        push eax
    L_004300e9:
        mov edx,edi
    L_004300eb:
        call asm_AnimationManager_Find_004491c0
    L_004300f0:
        mov ecx,eax
    L_004300f2:
        cmp ecx,ebx
    L_004300f4:
        je short L_0043011d
    L_004300f6:
        movsx edx,word ptr [esi+59D4h]
    L_004300fd:
        mov eax,66666667h
    L_00430102:
        imul edx
    L_00430104:
        sar edx,2
    L_00430107:
        mov eax,edx
    L_00430109:
        shr eax,1Fh
    L_0043010c:
        lea edx,[edx+eax+33h]
    L_00430110:
        mov eax,ecx
    L_00430112:
        mov ecx,dword ptr [ecx+308h]
    L_00430118:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043011d:
        mov ecx,dword ptr [esi+2CCh]
    L_00430123:
        push ecx
    L_00430124:
        mov edx,edi
    L_00430126:
        call asm_AnimationManager_Find_004491c0
    L_0043012b:
        cmp eax,ebx
    L_0043012d:
        jne short L_00430135
    L_0043012f:
        mov dword ptr [esi+2CCh],ebx
    L_00430135:
        add eax,10h
    L_00430138:
        cmp eax,ebx
    L_0043013a:
        je short L_00430157
    L_0043013c:
        mov ecx,56h
    L_00430141:
        mov edx,dword ptr [eax]
    L_00430143:
        cmp word ptr [edx+38Ah],cx
    L_0043014a:
        je asm_target_00430238
    L_00430150:
        mov eax,dword ptr [eax+4]
    L_00430153:
        cmp eax,ebx
    L_00430155:
        jne short L_00430141
    L_00430157:
        xor eax,eax
    L_00430159:
        push eax
    L_0043015a:
        mov edx,edi
    L_0043015c:
        call asm_AnimationManager_Find_004491c0
    L_00430161:
        mov ecx,eax
    L_00430163:
        cmp ecx,ebx
    L_00430165:
        pop edi
    L_00430166:
        je asm_target_00430241
    L_0043016c:
        movsx eax,word ptr [esi+59D4h]
    L_00430173:
        cdq
    L_00430174:
        mov esi,0Ah
    L_00430179:
        idiv esi
    L_0043017b:
        pop esi
    L_0043017c:
        mov eax,ecx
    L_0043017e:
        mov ecx,dword ptr [ecx+308h]
    L_00430184:
        pop ebx
    L_00430185:
        add edx,33h
    L_00430188:
        jmp asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0043018d:
        mov eax,dword ptr [eax]
    L_0043018f:
        mov eax,dword ptr [eax]
    L_00430191:
        jmp asm_target_0042f8f9
    L_00430196:
        mov eax,dword ptr [eax]
    L_00430198:
        mov eax,dword ptr [eax]
    L_0043019a:
        jmp asm_target_0042f978
    L_0043019f:
        mov eax,dword ptr [eax]
    L_004301a1:
        mov eax,dword ptr [eax]
    L_004301a3:
        jmp asm_target_0042f9e8
    L_004301a8:
        mov eax,dword ptr [eax]
    L_004301aa:
        mov eax,dword ptr [eax]
    L_004301ac:
        jmp asm_target_0042fa59
    L_004301b1:
        mov eax,dword ptr [eax]
    L_004301b3:
        mov eax,dword ptr [eax]
    L_004301b5:
        jmp asm_target_0042fac8
    L_004301ba:
        mov eax,dword ptr [eax]
    L_004301bc:
        mov eax,dword ptr [eax]
    L_004301be:
        jmp asm_target_0042fb39
    L_004301c3:
        mov eax,dword ptr [eax]
    L_004301c5:
        mov eax,dword ptr [eax]
    L_004301c7:
        jmp asm_target_0042fba8
    L_004301cc:
        mov eax,dword ptr [eax]
    L_004301ce:
        mov eax,dword ptr [eax]
    L_004301d0:
        jmp asm_target_0042fc19
    L_004301d5:
        mov eax,dword ptr [eax]
    L_004301d7:
        mov eax,dword ptr [eax]
    L_004301d9:
        jmp asm_target_0042fc88
    L_004301de:
        mov eax,dword ptr [eax]
    L_004301e0:
        mov eax,dword ptr [eax]
    L_004301e2:
        jmp asm_target_0042fcf9
    L_004301e7:
        mov eax,dword ptr [eax]
    L_004301e9:
        mov eax,dword ptr [eax]
    L_004301eb:
        jmp asm_target_0042fd68
    L_004301f0:
        mov eax,dword ptr [eax]
    L_004301f2:
        mov eax,dword ptr [eax]
    L_004301f4:
        jmp asm_target_0042fdd9
    L_004301f9:
        mov eax,dword ptr [eax]
    L_004301fb:
        mov eax,dword ptr [eax]
    L_004301fd:
        jmp asm_target_0042fe48
    L_00430202:
        mov eax,dword ptr [eax]
    L_00430204:
        mov eax,dword ptr [eax]
    L_00430206:
        jmp asm_target_0042feb9
    L_0043020b:
        mov eax,dword ptr [eax]
    L_0043020d:
        mov eax,dword ptr [eax]
    L_0043020f:
        jmp asm_target_0042ff28
    L_00430214:
        mov eax,dword ptr [eax]
    L_00430216:
        mov eax,dword ptr [eax]
    L_00430218:
        jmp asm_target_0042ff99
    L_0043021d:
        mov eax,dword ptr [eax]
    L_0043021f:
        mov eax,dword ptr [eax]
    L_00430221:
        jmp asm_target_00430008
    L_00430226:
        mov eax,dword ptr [eax]
    L_00430228:
        mov eax,dword ptr [eax]
    L_0043022a:
        jmp asm_target_00430079
    L_0043022f:
        mov eax,dword ptr [eax]
    L_00430231:
        mov eax,dword ptr [eax]
    L_00430233:
        jmp asm_target_004300e8
    L_00430238:
        mov eax,dword ptr [eax]
    L_0043023a:
        mov eax,dword ptr [eax]
    L_0043023c:
        jmp asm_target_00430159
    L_00430241:
        pop esi
    L_00430242:
        pop ebx
    L_00430243:
        ret
    }
}
