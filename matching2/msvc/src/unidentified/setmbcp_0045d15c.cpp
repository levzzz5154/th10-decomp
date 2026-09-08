#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045D15C..0x0045D2A2: __setmbcp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_setmbcp_0045d15c() {
    __asm {
    L_0045d15c:
        push 14h
    L_0045d15e:
        push 46C548h
    L_0045d163:
        call asm_SEH_prolog_00454bbc
    L_0045d168:
        or dword ptr [ebp-20h],0FFFFFFFFh
    L_0045d16c:
        push 0Dh
    L_0045d16e:
        call asm_lock_00453c0c
    L_0045d173:
        pop ecx
    L_0045d174:
        xor edi,edi
    L_0045d176:
        mov dword ptr [ebp-4],edi
    L_0045d179:
        mov dword ptr [data_00477690],edi
    L_0045d17f:
        mov eax,dword ptr [ebp+8]
    L_0045d182:
        cmp eax,0FFFFFFFEh
    L_0045d185:
        jne short L_0045d199
    L_0045d187:
        mov dword ptr [data_00477690],1
    L_0045d191:
        call dword ptr [data_00466048]
    L_0045d197:
        jmp short L_0045d1c4
    L_0045d199:
        cmp eax,0FFFFFFFDh
    L_0045d19c:
        jne short L_0045d1b0
    L_0045d19e:
        mov dword ptr [data_00477690],1
    L_0045d1a8:
        call dword ptr [data_0046604c]
    L_0045d1ae:
        jmp short L_0045d1c4
    L_0045d1b0:
        cmp eax,0FFFFFFFCh
    L_0045d1b3:
        jne short L_0045d1c4
    L_0045d1b5:
        mov dword ptr [data_00477690],1
    L_0045d1bf:
        mov eax,dword ptr [data_00477664]
    L_0045d1c4:
        mov dword ptr [ebp+8],eax
    L_0045d1c7:
        cmp eax,dword ptr [data_004980a4]
    L_0045d1cd:
        je asm_target_0045d28e
    L_0045d1d3:
        mov esi,dword ptr [data_00497f94]
    L_0045d1d9:
        mov dword ptr [ebp-24h],esi
    L_0045d1dc:
        cmp esi,edi
    L_0045d1de:
        je short L_0045d1e4
    L_0045d1e0:
        cmp dword ptr [esi],edi
    L_0045d1e2:
        je short L_0045d1f4
    L_0045d1e4:
        push 220h
    L_0045d1e9:
        call asm_malloc_00452706
    L_0045d1ee:
        pop ecx
    L_0045d1ef:
        mov esi,eax
    L_0045d1f1:
        mov dword ptr [ebp-24h],esi
    L_0045d1f4:
        cmp esi,edi
    L_0045d1f6:
        je short L_0045d277
    L_0045d1f8:
        push dword ptr [ebp+8]
    L_0045d1fb:
        call asm_FUN_0045cfb8_0045cfb8
    L_0045d200:
        pop ecx
    L_0045d201:
        mov dword ptr [ebp-20h],eax
    L_0045d204:
        cmp eax,edi
    L_0045d206:
        jne short L_0045d277
    L_0045d208:
        mov dword ptr [esi],edi
    L_0045d20a:
        mov eax,dword ptr [data_004980a4]
    L_0045d20f:
        mov dword ptr [esi+4],eax
    L_0045d212:
        mov eax,dword ptr [data_00497f98]
    L_0045d217:
        mov dword ptr [esi+8],eax
    L_0045d21a:
        mov eax,dword ptr [data_00497f90]
    L_0045d21f:
        mov dword ptr [esi+0Ch],eax
    L_0045d222:
        xor eax,eax
    L_0045d224:
        mov dword ptr [ebp-1Ch],eax
    L_0045d227:
        cmp eax,5
    L_0045d22a:
        jge short L_0045d23c
    L_0045d22c:
        mov cx,word ptr [eax*2+4980B0h]
    L_0045d234:
        mov word ptr [esi+eax*2+10h],cx
    L_0045d239:
        inc eax
    L_0045d23a:
        jmp short L_0045d224
    L_0045d23c:
        xor eax,eax
    L_0045d23e:
        mov dword ptr [ebp-1Ch],eax
    L_0045d241:
        cmp eax,101h
    L_0045d246:
        jge short L_0045d255
    L_0045d248:
        mov cl,byte ptr [eax+497FA0h]
    L_0045d24e:
        mov byte ptr [eax+esi+1Ch],cl
    L_0045d252:
        inc eax
    L_0045d253:
        jmp short L_0045d23e
    L_0045d255:
        xor eax,eax
    L_0045d257:
        mov dword ptr [ebp-1Ch],eax
    L_0045d25a:
        cmp eax,100h
    L_0045d25f:
        jge short L_0045d271
    L_0045d261:
        mov cl,byte ptr [eax+4980C0h]
    L_0045d267:
        mov byte ptr [eax+esi+11Dh],cl
    L_0045d26e:
        inc eax
    L_0045d26f:
        jmp short L_0045d257
    L_0045d271:
        mov dword ptr [data_00497f94],esi
    L_0045d277:
        cmp dword ptr [ebp-20h],0FFFFFFFFh
    L_0045d27b:
        jne short L_0045d291
    L_0045d27d:
        cmp esi,dword ptr [data_00497f94]
    L_0045d283:
        je short L_0045d291
    L_0045d285:
        push esi
    L_0045d286:
        call asm_free_00452422
    L_0045d28b:
        pop ecx
    L_0045d28c:
        jmp short L_0045d291
    L_0045d28e:
        mov dword ptr [ebp-20h],edi
    L_0045d291:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045d295:
        call asm_FUN_0045d2a3_0045d2a3
    L_0045d29a:
        mov eax,dword ptr [ebp-20h]
    L_0045d29d:
        call asm_SEH_epilog_00454bf7
    L_0045d2a2:
        ret
    }
}
