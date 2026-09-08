#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041CFD0..0x0041D169: FUN_0041cfd0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041cfd0_0041cfd0() {
    __asm {
    L_0041cfd0:
        sub esp,0Ch
    L_0041cfd3:
        push ebx
    L_0041cfd4:
        mov ebx,ecx
    L_0041cfd6:
        mov eax,dword ptr [ebx+40h]
    L_0041cfd9:
        mov ecx,dword ptr [ebx+3Ch]
    L_0041cfdc:
        push eax
    L_0041cfdd:
        push ecx
    L_0041cfde:
        lea ecx,[esp+0Ch]
    L_0041cfe2:
        call asm_SetPolar_Vector2_0041f800
    L_0041cfe7:
        fld dword ptr [esp+4]
    L_0041cfeb:
        fadd dword ptr [ebx+24h]
    L_0041cfee:
        mov dword ptr [esp+0Ch],0
    L_0041cff6:
        fstp dword ptr [esp+4]
    L_0041cffa:
        fld dword ptr [esp+8]
    L_0041cffe:
        fadd dword ptr [ebx+28h]
    L_0041d001:
        fstp dword ptr [esp+8]
    L_0041d005:
        fld dword ptr [esp+4]
    L_0041d009:
        fcomp dword ptr [data_00470b40]
    L_0041d00f:
        fnstsw ax
    L_0041d011:
        test ah,41h
    L_0041d014:
        jnp short L_0041d04d
    L_0041d016:
        fld dword ptr [esp+4]
    L_0041d01a:
        fcomp dword ptr [data_00470b3c]
    L_0041d020:
        fnstsw ax
    L_0041d022:
        test ah,1
    L_0041d025:
        je short L_0041d04d
    L_0041d027:
        fld dword ptr [esp+8]
    L_0041d02b:
        fcomp dword ptr [data_00470b04]
    L_0041d031:
        fnstsw ax
    L_0041d033:
        test ah,41h
    L_0041d036:
        jnp short L_0041d04d
    L_0041d038:
        fld dword ptr [esp+8]
    L_0041d03c:
        fcomp dword ptr [data_00470b38]
    L_0041d042:
        fnstsw ax
    L_0041d044:
        test ah,1
    L_0041d047:
        jne asm_target_0041d165
    L_0041d04d:
        push ebp
    L_0041d04e:
        push edi
    L_0041d04f:
        mov edi,dword ptr [ebx+40Ch]
    L_0041d055:
        xor ebp,ebp
    L_0041d057:
        test edi,edi
    L_0041d059:
        jl short L_0041d066
    L_0041d05b:
        push ebp
    L_0041d05c:
        mov ecx,492590h
    L_0041d061:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0041d066:
        fld dword ptr [esp+0Ch]
    L_0041d06a:
        push esi
    L_0041d06b:
        fcomp dword ptr [data_00470b40]
    L_0041d071:
        fnstsw ax
    L_0041d073:
        test ah,5
    L_0041d076:
        jnp short L_0041d089
    L_0041d078:
        fld dword ptr [esp+10h]
    L_0041d07c:
        fcomp dword ptr [data_00470b3c]
    L_0041d082:
        fnstsw ax
    L_0041d084:
        test ah,1
    L_0041d087:
        jne short L_0041d0dd
    L_0041d089:
        fld dword ptr [ebx+3Ch]
    L_0041d08c:
        mov eax,dword ptr [esp+10h]
    L_0041d090:
        mov ecx,dword ptr [esp+14h]
    L_0041d094:
        fchs
    L_0041d096:
        fsub dword ptr [data_00470b18]
    L_0041d09c:
        lea edi,[ebx+424h]
    L_0041d0a2:
        mov edx,edi
    L_0041d0a4:
        mov dword ptr [edx],eax
    L_0041d0a6:
        mov eax,dword ptr [esp+18h]
    L_0041d0aa:
        mov dword ptr [edx+4],ecx
    L_0041d0ad:
        push ecx
    L_0041d0ae:
        fstp dword ptr [esp]
    L_0041d0b1:
        mov dword ptr [edx+8],eax
    L_0041d0b4:
        call asm_Angle_Normalize_0044bc70
    L_0041d0b9:
        fstp dword ptr [ebx+430h]
    L_0041d0bf:
        mov ecx,dword ptr [ebx+13Ch]
    L_0041d0c5:
        mov esi,dword ptr [data_0047781c]
    L_0041d0cb:
        push 0
    L_0041d0cd:
        mov dword ptr [ebx+444h],ecx
    L_0041d0d3:
        mov ebp,1
    L_0041d0d8:
        call asm_FUN_0041c510_0041c510
    L_0041d0dd:
        mov ecx,dword ptr [ebx+404h]
    L_0041d0e3:
        test ecx,8000000h
    L_0041d0e9:
        jne short L_0041d154
    L_0041d0eb:
        fld dword ptr [esp+14h]
    L_0041d0ef:
        fcomp dword ptr [data_00470b04]
    L_0041d0f5:
        fnstsw ax
    L_0041d0f7:
        test ah,5
    L_0041d0fa:
        jnp short L_0041d112
    L_0041d0fc:
        fld dword ptr [esp+14h]
    L_0041d100:
        fcomp dword ptr [data_00470b38]
    L_0041d106:
        fnstsw ax
    L_0041d108:
        test ah,1
    L_0041d10b:
        jne short L_0041d154
    L_0041d10d:
        test ch,4
    L_0041d110:
        je short L_0041d154
    L_0041d112:
        mov eax,dword ptr [esp+10h]
    L_0041d116:
        fld dword ptr [ebx+3Ch]
    L_0041d119:
        mov ecx,dword ptr [esp+14h]
    L_0041d11d:
        fchs
    L_0041d11f:
        mov esi,dword ptr [data_0047781c]
    L_0041d125:
        fstp dword ptr [ebx+430h]
    L_0041d12b:
        lea edi,[ebx+424h]
    L_0041d131:
        mov edx,edi
    L_0041d133:
        mov dword ptr [edx],eax
    L_0041d135:
        mov eax,dword ptr [esp+18h]
    L_0041d139:
        mov dword ptr [edx+4],ecx
    L_0041d13c:
        mov ecx,dword ptr [ebx+13Ch]
    L_0041d142:
        push 0
    L_0041d144:
        mov dword ptr [edx+8],eax
    L_0041d147:
        mov dword ptr [ebx+444h],ecx
    L_0041d14d:
        call asm_FUN_0041c510_0041c510
    L_0041d152:
        jmp short L_0041d158
    L_0041d154:
        test ebp,ebp
    L_0041d156:
        je short L_0041d162
    L_0041d158:
        and dword ptr [ebx+404h],0F7FFF3FFh
    L_0041d162:
        pop esi
    L_0041d163:
        pop edi
    L_0041d164:
        pop ebp
    L_0041d165:
        pop ebx
    L_0041d166:
        add esp,0Ch
    L_0041d169:
        ret
    }
}
