#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461F31..0x00462106: FUN_00461f31
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461f31_00461f31() {
    __asm {
    L_00461f31:
        push ebp
    L_00461f32:
        mov ebp,esp
    L_00461f34:
        sub esp,10h
    L_00461f37:
        mov eax,dword ptr [ebp+8]
    L_00461f3a:
        push ebx
    L_00461f3b:
        xor ebx,ebx
    L_00461f3d:
        cmp eax,ebx
    L_00461f3f:
        push edi
    L_00461f40:
        mov dword ptr [ebp-10h],ebx
    L_00461f43:
        jne short L_00461f4a
    L_00461f45:
        or eax,0FFFFFFFFh
    L_00461f48:
        jmp short L_00461fab
    L_00461f4a:
        push esi
    L_00461f4b:
        mov esi,dword ptr [eax]
    L_00461f4d:
        cmp esi,ebx
    L_00461f4f:
        mov dword ptr [ebp-8],esi
    L_00461f52:
        je short L_00461fa7
    L_00461f54:
        push 3Dh
    L_00461f56:
        push esi
    L_00461f57:
        call asm_FUN_0046227b_0046227b
    L_00461f5c:
        cmp eax,ebx
    L_00461f5e:
        pop ecx
    L_00461f5f:
        pop ecx
    L_00461f60:
        mov dword ptr [ebp-0Ch],eax
    L_00461f63:
        je short L_00461fa7
    L_00461f65:
        cmp esi,eax
    L_00461f67:
        je short L_00461fa7
    L_00461f69:
        xor ecx,ecx
    L_00461f6b:
        cmp byte ptr [eax+1],cl
    L_00461f6e:
        mov eax,dword ptr [data_00477490]
    L_00461f73:
        sete cl
    L_00461f76:
        cmp eax,dword ptr [data_00477494]
    L_00461f7c:
        mov dword ptr [ebp-4],ecx
    L_00461f7f:
        jne short L_00461f8d
    L_00461f81:
        mov edi,eax
    L_00461f83:
        call asm_copy_environ_00461ed0
    L_00461f88:
        mov dword ptr [data_00477490],eax
    L_00461f8d:
        cmp eax,ebx
    L_00461f8f:
        jne short L_00461fe6
    L_00461f91:
        cmp dword ptr [ebp+0Ch],ebx
    L_00461f94:
        je short L_00461faf
    L_00461f96:
        cmp dword ptr [data_00477498],ebx
    L_00461f9c:
        je short L_00461faf
    L_00461f9e:
        call asm_wtomb_environ_004610f4
    L_00461fa3:
        test eax,eax
    L_00461fa5:
        je short L_00461fe6
    L_00461fa7:
        or eax,0FFFFFFFFh
    L_00461faa:
        pop esi
    L_00461fab:
        pop edi
    L_00461fac:
        pop ebx
    L_00461fad:
        leave
    L_00461fae:
        ret
    L_00461faf:
        cmp dword ptr [ebp-4],ebx
    L_00461fb2:
        je short L_00461fb8
    L_00461fb4:
        xor eax,eax
    L_00461fb6:
        jmp short L_00461faa
    L_00461fb8:
        push 4
    L_00461fba:
        call asm_malloc_00452706
    L_00461fbf:
        cmp eax,ebx
    L_00461fc1:
        pop ecx
    L_00461fc2:
        mov dword ptr [data_00477490],eax
    L_00461fc7:
        je short L_00461fa7
    L_00461fc9:
        mov dword ptr [eax],ebx
    L_00461fcb:
        cmp dword ptr [data_00477498],ebx
    L_00461fd1:
        jne short L_00461fe6
    L_00461fd3:
        push 4
    L_00461fd5:
        call asm_malloc_00452706
    L_00461fda:
        cmp eax,ebx
    L_00461fdc:
        pop ecx
    L_00461fdd:
        mov dword ptr [data_00477498],eax
    L_00461fe2:
        je short L_00461fa7
    L_00461fe4:
        mov dword ptr [eax],ebx
    L_00461fe6:
        mov edi,dword ptr [ebp-0Ch]
    L_00461fe9:
        mov ebx,dword ptr [data_00477490]
    L_00461fef:
        sub edi,esi
    L_00461ff1:
        push esi
    L_00461ff2:
        call asm_findenv_00461e83
    L_00461ff7:
        mov edi,eax
    L_00461ff9:
        test edi,edi
    L_00461ffb:
        pop ecx
    L_00461ffc:
        jl short L_0046204d
    L_00461ffe:
        cmp dword ptr [ebx],0
    L_00462001:
        je short L_0046204d
    L_00462003:
        lea esi,[ebx+edi*4]
    L_00462006:
        push dword ptr [esi]
    L_00462008:
        call asm_free_00452422
    L_0046200d:
        xor eax,eax
    L_0046200f:
        cmp dword ptr [ebp-4],eax
    L_00462012:
        pop ecx
    L_00462013:
        jne short L_0046202d
    L_00462015:
        mov ecx,dword ptr [ebp-8]
    L_00462018:
        mov dword ptr [esi],ecx
    L_0046201a:
        mov ecx,dword ptr [ebp+8]
    L_0046201d:
        mov esi,dword ptr [ebp-8]
    L_00462020:
        mov dword ptr [ecx],eax
    L_00462022:
        jmp short L_0046208e
    L_00462024:
        mov ecx,dword ptr [esi+4]
    L_00462027:
        inc edi
    L_00462028:
        mov dword ptr [esi],ecx
    L_0046202a:
        lea esi,[ebx+edi*4]
    L_0046202d:
        cmp dword ptr [esi],eax
    L_0046202f:
        jne short L_00462024
    L_00462031:
        mov eax,edi
    L_00462033:
        shl eax,2
    L_00462036:
        push eax
    L_00462037:
        push dword ptr [data_00477490]
    L_0046203d:
        call asm_FUN_00457395_00457395
    L_00462042:
        test eax,eax
    L_00462044:
        mov esi,dword ptr [ebp-8]
    L_00462047:
        pop ecx
    L_00462048:
        pop ecx
    L_00462049:
        je short L_0046208e
    L_0046204b:
        jmp short L_00462089
    L_0046204d:
        cmp dword ptr [ebp-4],0
    L_00462051:
        jne asm_target_004620f5
    L_00462057:
        test edi,edi
    L_00462059:
        jge short L_0046205d
    L_0046205b:
        neg edi
    L_0046205d:
        lea eax,[edi*4+8]
    L_00462064:
        push eax
    L_00462065:
        push dword ptr [data_00477490]
    L_0046206b:
        call asm_FUN_00457395_00457395
    L_00462070:
        test eax,eax
    L_00462072:
        pop ecx
    L_00462073:
        pop ecx
    L_00462074:
        je asm_target_00461fa7
    L_0046207a:
        lea ecx,[eax+edi*4]
    L_0046207d:
        and dword ptr [ecx+4],0
    L_00462081:
        mov dword ptr [ecx],esi
    L_00462083:
        mov ecx,dword ptr [ebp+8]
    L_00462086:
        and dword ptr [ecx],0
    L_00462089:
        mov dword ptr [data_00477490],eax
    L_0046208e:
        cmp dword ptr [ebp+0Ch],0
    L_00462092:
        je short L_004620e0
    L_00462094:
        push esi
    L_00462095:
        call asm_strlen_00456720
    L_0046209a:
        inc eax
    L_0046209b:
        inc eax
    L_0046209c:
        push eax
    L_0046209d:
        call asm_malloc_00452706
    L_004620a2:
        mov edi,eax
    L_004620a4:
        test edi,edi
    L_004620a6:
        pop ecx
    L_004620a7:
        pop ecx
    L_004620a8:
        je short L_004620e0
    L_004620aa:
        push esi
    L_004620ab:
        push edi
    L_004620ac:
        call asm_FUN_0045bd80_0045bd80
    L_004620b1:
        mov eax,edi
    L_004620b3:
        sub eax,esi
    L_004620b5:
        add eax,dword ptr [ebp-0Ch]
    L_004620b8:
        pop ecx
    L_004620b9:
        pop ecx
    L_004620ba:
        mov ecx,dword ptr [ebp-4]
    L_004620bd:
        mov byte ptr [eax],0
    L_004620c0:
        inc eax
    L_004620c1:
        neg ecx
    L_004620c3:
        sbb ecx,ecx
    L_004620c5:
        not ecx
    L_004620c7:
        and ecx,eax
    L_004620c9:
        push ecx
    L_004620ca:
        push edi
    L_004620cb:
        call dword ptr [data_004661a8]
    L_004620d1:
        test eax,eax
    L_004620d3:
        jne short L_004620d9
    L_004620d5:
        or dword ptr [ebp-10h],0FFFFFFFFh
    L_004620d9:
        push edi
    L_004620da:
        call asm_free_00452422
    L_004620df:
        pop ecx
    L_004620e0:
        cmp dword ptr [ebp-4],0
    L_004620e4:
        je short L_004620ed
    L_004620e6:
        push esi
    L_004620e7:
        call asm_free_00452422
    L_004620ec:
        pop ecx
    L_004620ed:
        mov eax,dword ptr [ebp-10h]
    L_004620f0:
        jmp asm_target_00461faa
    L_004620f5:
        push esi
    L_004620f6:
        call asm_free_00452422
    L_004620fb:
        mov eax,dword ptr [ebp+8]
    L_004620fe:
        and dword ptr [eax],0
    L_00462101:
        pop ecx
    L_00462102:
        jmp asm_target_00461fb4
    }
}
