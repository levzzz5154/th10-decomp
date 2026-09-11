#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418D40..0x00418E2C: StageTipManager_Construct
// Naked body preserves the retail register/stack ABI.

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
