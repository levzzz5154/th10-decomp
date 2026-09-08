#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00455FE7..0x004561C3: FUN_00455fe7
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00455fe7_00455fe7() {
    __asm {
    L_00455fe7:
        push ebp
    L_00455fe8:
        lea ebp,[esp-78h]
    L_00455fec:
        sub esp,94h
    L_00455ff2:
        mov eax,dword ptr [data_00473660]
    L_00455ff7:
        push ebx
    L_00455ff8:
        push esi
    L_00455ff9:
        xor eax,ebp
    L_00455ffb:
        mov esi,ecx
    L_00455ffd:
        xor ebx,ebx
    L_00455fff:
        cmp esi,ebx
    L_00456001:
        push edi
    L_00456002:
        mov dword ptr [ebp+74h],eax
    L_00456005:
        mov edi,edx
    L_00456007:
        je short L_00456028
    L_00456009:
        cmp edi,ebx
    L_0045600b:
        je short L_00456019
    L_0045600d:
        push edi
    L_0045600e:
        call asm_FUN_00455d53_00455d53
    L_00456013:
        pop ecx
    L_00456014:
        jmp asm_target_0045611f
    L_00456019:
        lea eax,[esi+esi*2]
    L_0045601c:
        mov esi,dword ptr [eax*4+47334Ch]
    L_00456023:
        jmp asm_target_00456121
    L_00456028:
        cmp edi,ebx
    L_0045602a:
        mov dword ptr [ebp-18h],1
    L_00456031:
        mov dword ptr [ebp-14h],ebx
    L_00456034:
        je asm_target_0045611a
    L_0045603a:
        cmp byte ptr [edi],4Ch
    L_0045603d:
        jne asm_target_00456139
    L_00456043:
        cmp byte ptr [edi+1],43h
    L_00456047:
        jne asm_target_00456139
    L_0045604d:
        cmp byte ptr [edi+2],5Fh
    L_00456051:
        jne asm_target_00456139
    L_00456057:
        push 46AA04h
    L_0045605c:
        push edi
    L_0045605d:
        call asm_strpbrk_0045ccd0
    L_00456062:
        mov ebx,eax
    L_00456064:
        test ebx,ebx
    L_00456066:
        pop ecx
    L_00456067:
        pop ecx
    L_00456068:
        je asm_target_00456135
    L_0045606e:
        sub eax,edi
    L_00456070:
        mov dword ptr [ebp-18h],eax
    L_00456073:
        je asm_target_00456135
    L_00456079:
        cmp byte ptr [ebx],3Bh
    L_0045607c:
        je asm_target_00456135
    L_00456082:
        mov dword ptr [ebp-1Ch],1
    L_00456089:
        mov esi,473354h
    L_0045608e:
        jmp short L_00456093
    L_00456090:
        mov eax,dword ptr [ebp-18h]
    L_00456093:
        push eax
    L_00456094:
        push edi
    L_00456095:
        push dword ptr [esi]
    L_00456097:
        call asm_strncmp_00452f80
    L_0045609c:
        add esp,0Ch
    L_0045609f:
        test eax,eax
    L_004560a1:
        jne short L_004560b0
    L_004560a3:
        push dword ptr [esi]
    L_004560a5:
        call asm_strlen_00456720
    L_004560aa:
        cmp dword ptr [ebp-18h],eax
    L_004560ad:
        pop ecx
    L_004560ae:
        je short L_004560be
    L_004560b0:
        inc dword ptr [ebp-1Ch]
    L_004560b3:
        add esi,0Ch
    L_004560b6:
        cmp esi,473384h
    L_004560bc:
        jle short L_00456090
    L_004560be:
        inc ebx
    L_004560bf:
        push 46A9FCh
    L_004560c4:
        push ebx
    L_004560c5:
        call asm_strcspn_0045be80
    L_004560ca:
        mov edi,eax
    L_004560cc:
        test edi,edi
    L_004560ce:
        pop ecx
    L_004560cf:
        pop ecx
    L_004560d0:
        jne short L_004560d7
    L_004560d2:
        cmp byte ptr [ebx],3Bh
    L_004560d5:
        jne short L_00456135
    L_004560d7:
        mov esi,dword ptr [ebp-1Ch]
    L_004560da:
        cmp esi,5
    L_004560dd:
        jg short L_00456102
    L_004560df:
        push edi
    L_004560e0:
        lea eax,[ebp-10h]
    L_004560e3:
        push ebx
    L_004560e4:
        push eax
    L_004560e5:
        call asm_strncpy_00452960
    L_004560ea:
        lea eax,[ebp-10h]
    L_004560ed:
        push eax
    L_004560ee:
        mov byte ptr [ebp+edi-10h],0
    L_004560f3:
        call asm_FUN_00455d53_00455d53
    L_004560f8:
        add esp,10h
    L_004560fb:
        test eax,eax
    L_004560fd:
        je short L_00456102
    L_004560ff:
        inc dword ptr [ebp-14h]
    L_00456102:
        add edi,ebx
    L_00456104:
        cmp byte ptr [edi],0
    L_00456107:
        je short L_00456113
    L_00456109:
        inc edi
    L_0045610a:
        cmp byte ptr [edi],0
    L_0045610d:
        jne asm_target_00456057
    L_00456113:
        xor esi,esi
    L_00456115:
        cmp dword ptr [ebp-14h],esi
    L_00456118:
        je short L_00456121
    L_0045611a:
        call asm_FUN_00455b19_00455b19
    L_0045611f:
        mov esi,eax
    L_00456121:
        mov eax,esi
    L_00456123:
        mov ecx,dword ptr [ebp+74h]
    L_00456126:
        pop edi
    L_00456127:
        pop esi
    L_00456128:
        xor ecx,ebp
    L_0045612a:
        pop ebx
    L_0045612b:
        call asm_security_check_cookie_00458ea5
    L_00456130:
        add ebp,78h
    L_00456133:
        leave
    L_00456134:
        ret
    L_00456135:
        xor eax,eax
    L_00456137:
        jmp short L_00456123
    L_00456139:
        push ebx
    L_0045613a:
        push ebx
    L_0045613b:
        push ebx
    L_0045613c:
        lea eax,[ebp-10h]
    L_0045613f:
        push eax
    L_00456140:
        push edi
    L_00456141:
        call asm_FUN_00455bf3_00455bf3
    L_00456146:
        mov esi,eax
    L_00456148:
        add esp,14h
    L_0045614b:
        cmp esi,ebx
    L_0045614d:
        je short L_00456121
    L_0045614f:
        mov edi,47334Ch
    L_00456154:
        xor esi,esi
    L_00456156:
        mov ebx,edi
    L_00456158:
        cmp ebx,edi
    L_0045615a:
        je short L_00456183
    L_0045615c:
        push dword ptr [ebx]
    L_0045615e:
        lea eax,[ebp-10h]
    L_00456161:
        push eax
    L_00456162:
        call asm_strcmp_0045bf30
    L_00456167:
        test eax,eax
    L_00456169:
        pop ecx
    L_0045616a:
        pop ecx
    L_0045616b:
        je short L_00456180
    L_0045616d:
        lea eax,[ebp-10h]
    L_00456170:
        push eax
    L_00456171:
        call asm_FUN_00455d53_00455d53
    L_00456176:
        test eax,eax
    L_00456178:
        pop ecx
    L_00456179:
        jne short L_00456180
    L_0045617b:
        and dword ptr [ebp-18h],eax
    L_0045617e:
        jmp short L_00456183
    L_00456180:
        inc dword ptr [ebp-14h]
    L_00456183:
        add ebx,0Ch
    L_00456186:
        inc esi
    L_00456187:
        cmp ebx,473388h
    L_0045618d:
        jle short L_00456158
    L_0045618f:
        xor edi,edi
    L_00456191:
        cmp dword ptr [ebp-18h],edi
    L_00456194:
        je short L_004561b4
    L_00456196:
        call asm_FUN_00455b19_00455b19
    L_0045619b:
        push dword ptr [data_0047334c]
    L_004561a1:
        mov esi,eax
    L_004561a3:
        call asm_free_00452422
    L_004561a8:
        pop ecx
    L_004561a9:
        mov dword ptr [data_0047334c],edi
    L_004561af:
        jmp asm_target_00456121
    L_004561b4:
        cmp dword ptr [ebp-14h],edi
    L_004561b7:
        jne asm_target_0045611a
    L_004561bd:
        xor esi,esi
    L_004561bf:
        jmp asm_target_00456121
    }
}
