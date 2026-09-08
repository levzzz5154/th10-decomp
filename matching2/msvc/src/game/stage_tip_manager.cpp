#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418D40..0x00418E2C: StageTipManager_Construct
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTipManager_Construct_00418d40() {
    __asm {
    L_00418d40:
        xor eax,eax
    L_00418d42:
        push edi
    L_00418d43:
        mov ecx,6Ah
    L_00418d48:
        mov edi,edx
    L_00418d4a:
        rep stosd
    L_00418d4c:
        or dword ptr [edx],2
    L_00418d4f:
        mov dword ptr [edx+18h],edx
    L_00418d52:
        mov dword ptr [edx+24h],edx
    L_00418d55:
        xor eax,eax
    L_00418d57:
        mov dword ptr [edx+1Ch],eax
    L_00418d5a:
        mov dword ptr [edx+20h],eax
    L_00418d5d:
        mov dword ptr [edx+28h],eax
    L_00418d60:
        mov dword ptr [edx+2Ch],eax
    L_00418d63:
        mov dword ptr [edx+30h],edx
    L_00418d66:
        mov dword ptr [edx+34h],eax
    L_00418d69:
        mov dword ptr [edx+38h],eax
    L_00418d6c:
        mov dword ptr [edx+3Ch],edx
    L_00418d6f:
        mov dword ptr [edx+40h],eax
    L_00418d72:
        mov dword ptr [edx+44h],eax
    L_00418d75:
        mov dword ptr [edx+48h],edx
    L_00418d78:
        mov dword ptr [edx+4Ch],eax
    L_00418d7b:
        mov dword ptr [edx+50h],eax
    L_00418d7e:
        mov dword ptr [edx+54h],edx
    L_00418d81:
        mov dword ptr [edx+58h],eax
    L_00418d84:
        mov dword ptr [edx+5Ch],eax
    L_00418d87:
        mov dword ptr [edx+60h],edx
    L_00418d8a:
        mov dword ptr [edx+64h],eax
    L_00418d8d:
        mov dword ptr [edx+68h],eax
    L_00418d90:
        mov dword ptr [edx+6Ch],edx
    L_00418d93:
        mov dword ptr [edx+70h],eax
    L_00418d96:
        mov dword ptr [edx+74h],eax
    L_00418d99:
        mov dword ptr [edx+78h],edx
    L_00418d9c:
        mov dword ptr [edx+84h],edx
    L_00418da2:
        mov dword ptr [edx+7Ch],eax
    L_00418da5:
        mov dword ptr [edx+80h],eax
    L_00418dab:
        mov dword ptr [edx+88h],eax
    L_00418db1:
        mov dword ptr [edx+8Ch],eax
    L_00418db7:
        mov dword ptr [edx+90h],edx
    L_00418dbd:
        mov dword ptr [edx+94h],eax
    L_00418dc3:
        mov dword ptr [edx+98h],eax
    L_00418dc9:
        mov dword ptr [edx+9Ch],edx
    L_00418dcf:
        mov dword ptr [edx+0A0h],eax
    L_00418dd5:
        mov dword ptr [edx+0A4h],eax
    L_00418ddb:
        mov dword ptr [edx+0A8h],edx
    L_00418de1:
        mov dword ptr [edx+0ACh],eax
    L_00418de7:
        mov dword ptr [edx+0B0h],eax
    L_00418ded:
        mov dword ptr [edx+0B4h],edx
    L_00418df3:
        mov dword ptr [edx+0B8h],eax
    L_00418df9:
        mov dword ptr [edx+0BCh],eax
    L_00418dff:
        mov dword ptr [edx+0C0h],edx
    L_00418e05:
        mov dword ptr [edx+0C4h],eax
    L_00418e0b:
        mov dword ptr [edx+0C8h],eax
    L_00418e11:
        mov dword ptr [edx+0CCh],edx
    L_00418e17:
        mov dword ptr [edx+0D0h],eax
    L_00418e1d:
        mov dword ptr [edx+0D4h],eax
    L_00418e23:
        mov dword ptr [data_00477814],edx
    L_00418e29:
        mov eax,edx
    L_00418e2b:
        pop edi
    L_00418e2c:
        ret
    }
}

// 0x00418E30..0x00418EB2: StageTipRuntime_InitializeRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTipRuntime_InitializeRetail_00418e30() {
    __asm {
    L_00418e30:
        push esi
    L_00418e31:
        push edi
    L_00418e32:
        push 4198A0h
    L_00418e37:
        call asm_SchedulerCallback_Create_00449ed0
    L_00418e3c:
        mov esi,eax
    L_00418e3e:
        mov edx,dword ptr [esi+4]
    L_00418e41:
        mov eax,dword ptr [data_00491be4]
    L_00418e46:
        and edx,0FFFFFFFDh
    L_00418e49:
        push eax
    L_00418e4a:
        mov edi,19h
    L_00418e4f:
        mov dword ptr [esi+20h],ebx
    L_00418e52:
        mov dword ptr [esi+4],edx
    L_00418e55:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00418e5a:
        push 4198B0h
    L_00418e5f:
        mov dword ptr [ebx+8],esi
    L_00418e62:
        call asm_SchedulerCallback_Create_00449ed0
    L_00418e67:
        mov ecx,dword ptr [data_00491be4]
    L_00418e6d:
        mov esi,eax
    L_00418e6f:
        and dword ptr [esi+4],0FFFFFFFDh
    L_00418e73:
        push ecx
    L_00418e74:
        mov edi,2Ch
    L_00418e79:
        mov dword ptr [esi+20h],ebx
    L_00418e7c:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00418e81:
        mov dword ptr [ebx+0Ch],esi
    L_00418e84:
        mov dword ptr [ebx+10h],0
    L_00418e8b:
        mov al,byte ptr [data_00491d6a]
    L_00418e90:
        test al,al
    L_00418e92:
        pop edi
    L_00418e93:
        pop esi
    L_00418e94:
        je short L_00418eb0
    L_00418e96:
        push 0
    L_00418e98:
        push 46D6D8h
    L_00418e9d:
        push ebx
    L_00418e9e:
        call asm_FUN_00419960_00419960
    L_00418ea3:
        push 1
    L_00418ea5:
        push 46D6C4h
    L_00418eaa:
        push ebx
    L_00418eab:
        call asm_FUN_00419960_00419960
    L_00418eb0:
        xor eax,eax
    L_00418eb2:
        ret
    }
}

// 0x0041A120..0x0041A1FB: StageTip_CreateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTip_CreateRetail_0041a120() {
    __asm {
    L_0041a120:
        push esi
    L_0041a121:
        push 88h
    L_0041a126:
        call asm_operator_new_00452493
    L_0041a12b:
        mov edx,eax
    L_0041a12d:
        add esp,4
    L_0041a130:
        test edx,edx
    L_0041a132:
        je short L_0041a168
    L_0041a134:
        push edi
    L_0041a135:
        xor eax,eax
    L_0041a137:
        mov ecx,22h
    L_0041a13c:
        mov edi,edx
    L_0041a13e:
        rep stosd
    L_0041a140:
        mov dword ptr [edx+10h],eax
    L_0041a143:
        mov dword ptr [edx+14h],eax
    L_0041a146:
        mov dword ptr [edx+0Ch],edx
    L_0041a149:
        or eax,0FFFFFFFFh
    L_0041a14c:
        mov dword ptr [edx+84h],eax
    L_0041a152:
        mov dword ptr [edx+6Ch],12Ch
    L_0041a159:
        mov dword ptr [edx+7Ch],3F800000h
    L_0041a160:
        mov dword ptr [edx+70h],eax
    L_0041a163:
        mov esi,edx
    L_0041a165:
        pop edi
    L_0041a166:
        jmp short L_0041a16a
    L_0041a168:
        xor esi,esi
    L_0041a16a:
        mov eax,dword ptr [data_00474c7c]
    L_0041a16f:
        mov edx,dword ptr [esp+8]
    L_0041a173:
        lea eax,[eax+eax*2+1Eh]
    L_0041a177:
        lea eax,[edx+eax*4]
    L_0041a17a:
        mov edx,dword ptr [eax+4]
    L_0041a17d:
        test edx,edx
    L_0041a17f:
        lea ecx,[esi+0Ch]
    L_0041a182:
        je short L_0041a18e
    L_0041a184:
        mov eax,dword ptr [eax+4]
    L_0041a187:
        mov edx,dword ptr [eax+4]
    L_0041a18a:
        test edx,edx
    L_0041a18c:
        jne short L_0041a184
    L_0041a18e:
        mov edx,dword ptr [eax+4]
    L_0041a191:
        test edx,edx
    L_0041a193:
        je short L_0041a19e
    L_0041a195:
        mov dword ptr [ecx+4],edx
    L_0041a198:
        mov edx,dword ptr [eax+4]
    L_0041a19b:
        mov dword ptr [edx+8],ecx
    L_0041a19e:
        mov dword ptr [eax+4],ecx
    L_0041a1a1:
        mov dword ptr [ecx+8],eax
    L_0041a1a4:
        mov dword ptr [esi+70h],1Eh
    L_0041a1ab:
        mov ecx,dword ptr [ebx]
    L_0041a1ad:
        mov eax,esi
    L_0041a1af:
        mov dword ptr [eax],ecx
    L_0041a1b1:
        mov edx,dword ptr [ebx+4]
    L_0041a1b4:
        mov dword ptr [eax+4],edx
    L_0041a1b7:
        mov ecx,dword ptr [ebx+8]
    L_0041a1ba:
        mov edx,dword ptr [esp+0Ch]
    L_0041a1be:
        push 40h
    L_0041a1c0:
        mov dword ptr [eax+8],ecx
    L_0041a1c3:
        push edx
    L_0041a1c4:
        lea eax,[esi+1Ch]
    L_0041a1c7:
        push eax
    L_0041a1c8:
        call asm_strncpy_00452960
    L_0041a1cd:
        mov dword ptr [esi+64h],0
    L_0041a1d4:
        mov ecx,dword ptr [data_00474c84]
    L_0041a1da:
        mov dword ptr [esi+68h],ecx
    L_0041a1dd:
        mov eax,dword ptr [data_00474c84]
    L_0041a1e2:
        add esp,0Ch
    L_0041a1e5:
        test eax,eax
    L_0041a1e7:
        mov eax,dword ptr [data_00474c8c]
    L_0041a1ec:
        jne short L_0041a1f3
    L_0041a1ee:
        mov eax,dword ptr [data_00474c88]
    L_0041a1f3:
        mov dword ptr [esi+60h],eax
    L_0041a1f6:
        mov eax,esi
    L_0041a1f8:
        pop esi
    L_0041a1f9:
        ret 8
    }
}

// 0x00424650..0x004246B7: StageTip_CreateUrgent
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTip_CreateUrgent_00424650() {
    __asm {
    L_00424650:
        mov eax,dword ptr [data_00474c7c]
    L_00424655:
        lea eax,[eax+eax*2]
    L_00424658:
        mov eax,dword ptr [esi+eax*4+7Ch]
    L_0042465c:
        test eax,eax
    L_0042465e:
        je short L_00424676
    L_00424660:
        mov edx,dword ptr [eax+4]
    L_00424663:
        mov eax,dword ptr [eax]
    L_00424665:
        mov ecx,dword ptr [eax+70h]
    L_00424668:
        test ecx,ecx
    L_0042466a:
        jle short L_00424670
    L_0042466c:
        dec ecx
    L_0042466d:
        mov dword ptr [eax+70h],ecx
    L_00424670:
        test edx,edx
    L_00424672:
        mov eax,edx
    L_00424674:
        jne short L_00424660
    L_00424676:
        mov ecx,dword ptr [esp+4]
    L_0042467a:
        push ebx
    L_0042467b:
        mov ebx,dword ptr [esp+0Ch]
    L_0042467f:
        push ecx
    L_00424680:
        push esi
    L_00424681:
        call asm_StageTip_CreateRetail_0041a120
    L_00424686:
        mov edx,dword ptr [eax+60h]
    L_00424689:
        add edx,0FFFFFFC4h
    L_0042468c:
        mov ecx,edx
    L_0042468e:
        test ecx,ecx
    L_00424690:
        mov dword ptr [eax+60h],edx
    L_00424693:
        pop ebx
    L_00424694:
        jg short L_0042469d
    L_00424696:
        mov dword ptr [eax+60h],1
    L_0042469d:
        mov dword ptr [eax+6Ch],5Ah
    L_004246a4:
        mov dword ptr [eax+84h],0FFFF8080h
    L_004246ae:
        mov dword ptr [eax+70h],1Eh
    L_004246b5:
        ret 8
    }
}
