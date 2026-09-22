#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED (D3306): closest_byte_count=0/483; first_diff=0x0044D110
// residual_class=private EAX/ESI streamer arguments, COM vtable callbacks,
// archive reader/seek dependencies, and stack-local PCM fill layout.
// variants_tested=readable raw-vtable/archive candidate (536-byte standalone
// extent; semantic refill/silence model) plus exact naked baseline.
// next_lever=caller cluster 0x0043DDF0/0x0044CE80/0x0044D440 with callees
// 0x0044DD40/0x0044DE10 and real COM callbacks in native-LTCG schema2.

// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.

// 0x0044D110..0x0044D2F2: Streamer_FillBufferRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Streamer_FillBufferRetail_0044d110() {
    __asm {
    L_0044d110:
        sub esp,0Ch
    L_0044d113:
        push ebx
    L_0044d114:
        push ebp
    L_0044d115:
        mov ebp,dword ptr [esp+18h]
    L_0044d119:
        push edi
    L_0044d11a:
        xor edi,edi
    L_0044d11c:
        cmp ebp,edi
    L_0044d11e:
        mov ebx,eax
    L_0044d120:
        mov dword ptr [esp+0Ch],edi
    L_0044d124:
        mov dword ptr [esp+1Ch],edi
    L_0044d128:
        mov dword ptr [esp+10h],edi
    L_0044d12c:
        jne short L_0044d13c
    L_0044d12e:
        pop edi
    L_0044d12f:
        pop ebp
    L_0044d130:
        mov eax,800401F0h
    L_0044d135:
        pop ebx
    L_0044d136:
        add esp,0Ch
    L_0044d139:
        ret 8
    L_0044d13c:
        mov eax,dword ptr [ebp]
    L_0044d13f:
        lea ecx,[esp+14h]
    L_0044d143:
        push ecx
    L_0044d144:
        push ebp
    L_0044d145:
        call dword ptr [eax+24h]
    L_0044d148:
        cmp eax,edi
    L_0044d14a:
        jl asm_target_0044d2ea
    L_0044d150:
        test byte ptr [esp+14h],2
    L_0044d155:
        push esi
    L_0044d156:
        je short L_0044d17d
    L_0044d158:
        mov esi,dword ptr [data_004660ac]
    L_0044d15e:
        mov edi,edi
    L_0044d160:
        mov edx,dword ptr [ebp]
    L_0044d163:
        push ebp
    L_0044d164:
        call dword ptr [edx+50h]
    L_0044d167:
        cmp eax,88780096h
    L_0044d16c:
        jne short L_0044d172
    L_0044d16e:
        push 0Ah
    L_0044d170:
        call esi
    L_0044d172:
        mov eax,dword ptr [ebp]
    L_0044d175:
        push ebp
    L_0044d176:
        call dword ptr [eax+50h]
    L_0044d179:
        test eax,eax
    L_0044d17b:
        jne short L_0044d160
    L_0044d17d:
        mov ecx,dword ptr [ebp]
    L_0044d180:
        push edi
    L_0044d181:
        push edi
    L_0044d182:
        push edi
    L_0044d183:
        lea edx,[esp+2Ch]
    L_0044d187:
        push edx
    L_0044d188:
        mov edx,dword ptr [ebx+8]
    L_0044d18b:
        lea eax,[esp+20h]
    L_0044d18f:
        push eax
    L_0044d190:
        push edx
    L_0044d191:
        push edi
    L_0044d192:
        push ebp
    L_0044d193:
        call dword ptr [ecx+2Ch]
    L_0044d196:
        cmp eax,edi
    L_0044d198:
        jl asm_target_0044d2e9
    L_0044d19e:
        mov esi,dword ptr [ebx+0Ch]
    L_0044d1a1:
        cmp dword ptr [esi+7Ch],edi
    L_0044d1a4:
        je short L_0044d1c7
    L_0044d1a6:
        mov eax,dword ptr [esi+80h]
    L_0044d1ac:
        mov ecx,dword ptr [esi+90h]
    L_0044d1b2:
        mov dword ptr [esi+84h],eax
    L_0044d1b8:
        mov eax,dword ptr [ecx+1Ch]
    L_0044d1bb:
        cmp eax,edi
    L_0044d1bd:
        jle short L_0044d1f8
    L_0044d1bf:
        mov dword ptr [esi+88h],eax
    L_0044d1c5:
        jmp short L_0044d1f8
    L_0044d1c7:
        mov eax,dword ptr [esi+8Ch]
    L_0044d1cd:
        cmp eax,edi
    L_0044d1cf:
        je short L_0044d1f8
    L_0044d1d1:
        mov edx,dword ptr [esi+90h]
    L_0044d1d7:
        mov ecx,dword ptr [edx+10h]
    L_0044d1da:
        mov edx,dword ptr [data_004977a4]
    L_0044d1e0:
        push edi
    L_0044d1e1:
        push edi
    L_0044d1e2:
        add ecx,edx
    L_0044d1e4:
        push ecx
    L_0044d1e5:
        push eax
    L_0044d1e6:
        call dword ptr [data_004660c8]
    L_0044d1ec:
        mov edx,dword ptr [esi+90h]
    L_0044d1f2:
        mov eax,dword ptr [edx+1Ch]
    L_0044d1f5:
        mov dword ptr [esi+8],eax
    L_0044d1f8:
        mov edx,dword ptr [esp+10h]
    L_0044d1fc:
        mov eax,dword ptr [ebx+0Ch]
    L_0044d1ff:
        lea ecx,[esp+14h]
    L_0044d203:
        push ecx
    L_0044d204:
        push edx
    L_0044d205:
        mov edx,dword ptr [esp+28h]
    L_0044d209:
        call asm_ArchiveCursor_ReadRetail_0044de10
    L_0044d20e:
        cmp eax,edi
    L_0044d210:
        jl asm_target_0044d2e9
    L_0044d216:
        mov edi,dword ptr [esp+14h]
    L_0044d21a:
        test edi,edi
    L_0044d21c:
        mov ecx,dword ptr [esp+20h]
    L_0044d220:
        jne short L_0044d243
    L_0044d222:
        mov eax,dword ptr [ebx+0Ch]
    L_0044d225:
        mov edx,dword ptr [eax+90h]
    L_0044d22b:
        cmp word ptr [edx+2Eh],8
    L_0044d230:
        mov edi,dword ptr [esp+10h]
    L_0044d234:
        setne al
    L_0044d237:
        dec al
    L_0044d239:
        and eax,80h
    L_0044d23e:
        movzx eax,al
    L_0044d241:
        jmp short L_0044d2b8
    L_0044d243:
        cmp edi,ecx
    L_0044d245:
        jae asm_target_0044d2d2
    L_0044d24b:
        mov eax,dword ptr [esp+24h]
    L_0044d24f:
        test eax,eax
    L_0044d251:
        je short L_0044d294
    L_0044d253:
        mov esi,dword ptr [ebx+0Ch]
    L_0044d256:
        xor al,al
    L_0044d258:
        call asm_ArchiveCursor_SeekRetail_0044dd40
    L_0044d25d:
        test eax,eax
    L_0044d25f:
        jl asm_target_0044d2e9
    L_0044d265:
        mov ecx,dword ptr [esp+10h]
    L_0044d269:
        mov edx,dword ptr [esp+20h]
    L_0044d26d:
        lea eax,[esp+14h]
    L_0044d271:
        push eax
    L_0044d272:
        lea eax,[edi+ecx]
    L_0044d275:
        push eax
    L_0044d276:
        mov eax,dword ptr [ebx+0Ch]
    L_0044d279:
        sub edx,edi
    L_0044d27b:
        call asm_ArchiveCursor_ReadRetail_0044de10
    L_0044d280:
        test eax,eax
    L_0044d282:
        jl short L_0044d2e9
    L_0044d284:
        mov ecx,dword ptr [esp+14h]
    L_0044d288:
        mov eax,dword ptr [esp+20h]
    L_0044d28c:
        add edi,ecx
    L_0044d28e:
        cmp edi,eax
    L_0044d290:
        jb short L_0044d253
    L_0044d292:
        jmp short L_0044d2d2
    L_0044d294:
        mov edx,dword ptr [ebx+0Ch]
    L_0044d297:
        mov eax,dword ptr [edx+90h]
    L_0044d29d:
        sub ecx,edi
    L_0044d29f:
        cmp word ptr [eax+2Eh],8
    L_0044d2a4:
        setne dl
    L_0044d2a7:
        dec dl
    L_0044d2a9:
        and edx,80h
    L_0044d2af:
        movzx eax,dl
    L_0044d2b2:
        mov edx,dword ptr [esp+10h]
    L_0044d2b6:
        add edi,edx
    L_0044d2b8:
        mov bl,al
    L_0044d2ba:
        mov bh,bl
    L_0044d2bc:
        mov edx,ecx
    L_0044d2be:
        shr ecx,2
    L_0044d2c1:
        mov eax,ebx
    L_0044d2c3:
        shl eax,10h
    L_0044d2c6:
        mov ax,bx
    L_0044d2c9:
        rep stosd
    L_0044d2cb:
        mov ecx,edx
    L_0044d2cd:
        and ecx,3
    L_0044d2d0:
        rep stosb
    L_0044d2d2:
        mov ecx,dword ptr [esp+20h]
    L_0044d2d6:
        mov edx,dword ptr [esp+10h]
    L_0044d2da:
        mov eax,dword ptr [ebp]
    L_0044d2dd:
        push 0
    L_0044d2df:
        push 0
    L_0044d2e1:
        push ecx
    L_0044d2e2:
        push edx
    L_0044d2e3:
        push ebp
    L_0044d2e4:
        call dword ptr [eax+4Ch]
    L_0044d2e7:
        xor eax,eax
    L_0044d2e9:
        pop esi
    L_0044d2ea:
        pop edi
    L_0044d2eb:
        pop ebp
    L_0044d2ec:
        pop ebx
    L_0044d2ed:
        add esp,0Ch
    L_0044d2f0:
        ret 8
    }
}
