#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004470C0..0x00447270: FUN_004470c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004470c0_004470c0() {
    __asm {
    L_004470c0:
        sub esp,110h
    L_004470c6:
        mov eax,dword ptr [data_00473660]
    L_004470cb:
        xor eax,esp
    L_004470cd:
        push ebp
    L_004470ce:
        mov ebp,dword ptr [esp+120h]
    L_004470d5:
        push edi
    L_004470d6:
        mov edi,dword ptr [esp+120h]
    L_004470dd:
        cmp edi,21h
    L_004470e0:
        mov dword ptr [esp+114h],eax
    L_004470e7:
        mov eax,dword ptr [esp+11Ch]
    L_004470ee:
        mov dword ptr [esp+8],eax
    L_004470f2:
        jl short L_0044710d
    L_004470f4:
        push 470384h
    L_004470f9:
        mov edi,474F70h
    L_004470fe:
        call asm_TextLog_AppendLine_0044b8e0
    L_00447103:
        add esp,4
    L_00447106:
        xor eax,eax
    L_00447108:
        jmp asm_target_00447258
    L_0044710d:
        push ebx
    L_0044710e:
        push esi
    L_0044710f:
        push ebp
    L_00447110:
        lea ecx,[esp+1Ch]
    L_00447114:
        push 46E1C8h
    L_00447119:
        push ecx
    L_0044711a:
        call asm_sprintf_00452ae8
    L_0044711f:
        add esp,0Ch
    L_00447122:
        push 0
    L_00447124:
        push 0
    L_00447126:
        lea eax,[esp+20h]
    L_0044712a:
        call asm_FUN_0044b360_0044b360
    L_0044712f:
        push 130h
    L_00447134:
        mov ebx,eax
    L_00447136:
        mov dword ptr [esp+18h],0
    L_0044713e:
        call asm_operator_new_00452493
    L_00447143:
        mov esi,eax
    L_00447145:
        add esp,4
    L_00447148:
        test esi,esi
    L_0044714a:
        je short L_00447160
    L_0044714c:
        mov ecx,4Ch
    L_00447151:
        xor eax,eax
    L_00447153:
        mov edi,esi
    L_00447155:
        rep stosd
    L_00447157:
        mov edi,dword ptr [esp+128h]
    L_0044715e:
        jmp short L_00447162
    L_00447160:
        xor esi,esi
    L_00447162:
        test ebx,ebx
    L_00447164:
        mov edx,dword ptr [esp+10h]
    L_00447168:
        mov dword ptr [edx+edi*4+3AD06Ch],esi
    L_0044716f:
        je asm_target_00447250
    L_00447175:
        lea edx,[esi+4]
    L_00447178:
        mov dword ptr [esi],edi
    L_0044717a:
        mov dword ptr [esi+108h],ebx
    L_00447180:
        mov eax,ebp
    L_00447182:
        sub edx,ebp
    L_00447184:
        mov cl,byte ptr [eax]
    L_00447186:
        mov byte ptr [edx+eax],cl
    L_00447189:
        inc eax
    L_0044718a:
        test cl,cl
    L_0044718c:
        jne short L_00447184
    L_0044718e:
        mov edx,dword ptr [ebx+38h]
    L_00447191:
        test edx,edx
    L_00447193:
        mov edi,dword ptr [ebx]
    L_00447195:
        mov ebp,dword ptr [ebx+4]
    L_00447198:
        mov eax,ebx
    L_0044719a:
        mov ecx,1
    L_0044719f:
        mov dword ptr [esp+10h],edi
    L_004471a3:
        je short L_004471b8
    L_004471a5:
        add eax,edx
    L_004471a7:
        add ebp,dword ptr [eax+4]
    L_004471aa:
        add edi,dword ptr [eax]
    L_004471ac:
        mov edx,dword ptr [eax+38h]
    L_004471af:
        inc ecx
    L_004471b0:
        test edx,edx
    L_004471b2:
        jne short L_004471a5
    L_004471b4:
        mov dword ptr [esp+10h],edi
    L_004471b8:
        mov dword ptr [esi+10Ch],ecx
    L_004471be:
        shl ecx,4
    L_004471c1:
        mov edi,ecx
    L_004471c3:
        push edi
    L_004471c4:
        call asm_malloc_00452706
    L_004471c9:
        mov edx,eax
    L_004471cb:
        mov ecx,edi
    L_004471cd:
        mov dword ptr [esi+120h],edx
    L_004471d3:
        mov edi,edx
    L_004471d5:
        mov edx,ecx
    L_004471d7:
        shr ecx,2
    L_004471da:
        xor eax,eax
    L_004471dc:
        rep stosd
    L_004471de:
        mov ecx,edx
    L_004471e0:
        and ecx,3
    L_004471e3:
        rep stosb
    L_004471e5:
        mov edi,dword ptr [esp+14h]
    L_004471e9:
        mov eax,edi
    L_004471eb:
        imul eax,44h
    L_004471ee:
        push eax
    L_004471ef:
        call asm_malloc_00452706
    L_004471f4:
        lea ecx,[ebp*4]
    L_004471fb:
        push ecx
    L_004471fc:
        mov dword ptr [esi+118h],eax
    L_00447202:
        call asm_malloc_00452706
    L_00447207:
        add esp,0Ch
    L_0044720a:
        push ebx
    L_0044720b:
        xor ecx,ecx
    L_0044720d:
        mov edx,esi
    L_0044720f:
        mov dword ptr [esi+11Ch],eax
    L_00447215:
        mov dword ptr [esi+110h],ebp
    L_0044721b:
        mov dword ptr [esi+114h],edi
    L_00447221:
        call asm_FUN_004472e0_004472e0
    L_00447226:
        test eax,eax
    L_00447228:
        jl short L_00447250
    L_0044722a:
        lea ebx,[ebx+force_disp32_zero]
    L_00447230:
        mov edx,dword ptr [esp+14h]
    L_00447234:
        mov eax,dword ptr [ebx+38h]
    L_00447237:
        inc edx
    L_00447238:
        test eax,eax
    L_0044723a:
        mov dword ptr [esp+14h],edx
    L_0044723e:
        je short L_00447254
    L_00447240:
        add ebx,eax
    L_00447242:
        mov ecx,edx
    L_00447244:
        push ebx
    L_00447245:
        mov edx,esi
    L_00447247:
        call asm_FUN_004472e0_004472e0
    L_0044724c:
        test eax,eax
    L_0044724e:
        jge short L_00447230
    L_00447250:
        xor eax,eax
    L_00447252:
        jmp short L_00447256
    L_00447254:
        mov eax,esi
    L_00447256:
        pop esi
    L_00447257:
        pop ebx
    L_00447258:
        mov ecx,dword ptr [esp+114h]
    L_0044725f:
        pop edi
    L_00447260:
        pop ebp
    L_00447261:
        xor ecx,esp
    L_00447263:
        call asm_security_check_cookie_00458ea5
    L_00447268:
        add esp,110h
    L_0044726e:
        ret 0Ch
    }
}

