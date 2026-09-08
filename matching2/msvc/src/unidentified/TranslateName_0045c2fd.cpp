#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045C2FD..0x0045C35C: _TranslateName
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TranslateName_0045c2fd() {
    __asm {
    L_0045c2fd:
        push ebp
    L_0045c2fe:
        mov ebp,esp
    L_0045c300:
        xor eax,eax
    L_0045c302:
        push ebx
    L_0045c303:
        xor ebx,ebx
    L_0045c305:
        inc eax
    L_0045c306:
        cmp dword ptr [ebp+0Ch],ebx
    L_0045c309:
        jl short L_0045c351
    L_0045c30b:
        push esi
    L_0045c30c:
        push edi
    L_0045c30d:
        test eax,eax
    L_0045c30f:
        je short L_0045c34f
    L_0045c311:
        mov eax,dword ptr [ebp+0Ch]
    L_0045c314:
        add eax,ebx
    L_0045c316:
        cdq
    L_0045c317:
        sub eax,edx
    L_0045c319:
        mov esi,eax
    L_0045c31b:
        mov eax,dword ptr [ebp+8]
    L_0045c31e:
        sar esi,1
    L_0045c320:
        lea edi,[eax+esi*8]
    L_0045c323:
        push dword ptr [edi]
    L_0045c325:
        mov eax,dword ptr [ebp+10h]
    L_0045c328:
        push dword ptr [eax]
    L_0045c32a:
        call asm_stricmp_0046054e
    L_0045c32f:
        test eax,eax
    L_0045c331:
        pop ecx
    L_0045c332:
        pop ecx
    L_0045c333:
        jne short L_0045c33f
    L_0045c335:
        mov ecx,dword ptr [ebp+10h]
    L_0045c338:
        add edi,4
    L_0045c33b:
        mov dword ptr [ecx],edi
    L_0045c33d:
        jmp short L_0045c34a
    L_0045c33f:
        jge short L_0045c347
    L_0045c341:
        dec esi
    L_0045c342:
        mov dword ptr [ebp+0Ch],esi
    L_0045c345:
        jmp short L_0045c34a
    L_0045c347:
        lea ebx,[esi+1]
    L_0045c34a:
        cmp ebx,dword ptr [ebp+0Ch]
    L_0045c34d:
        jle short L_0045c30d
    L_0045c34f:
        pop edi
    L_0045c350:
        pop esi
    L_0045c351:
        xor ecx,ecx
    L_0045c353:
        test eax,eax
    L_0045c355:
        sete cl
    L_0045c358:
        pop ebx
    L_0045c359:
        mov eax,ecx
    L_0045c35b:
        pop ebp
    L_0045c35c:
        ret
    }
}
