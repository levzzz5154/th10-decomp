// 0043B8D0: FUN_0043b8d0
// Original size: 880 bytes, actual code: 164 instructions
extern "C" void FUN_00421d20(void);
extern "C" void FUN_0044b810(void);
extern "C" void DirectInput8Create(void);

extern "C" __declspec(naked) void FUN_0043b8d0(void) {
    __asm {
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x48]
        push  0xfffffffa
        push  eax
        call  DWORD PTR ds:0x46621c
        test  BYTE PTR [esi+0x150],0x8
        je loc_0043B8ED
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043B8ED:
        push  ebx
        push  0x0
        lea  ebx,[esi+0xc]
        push  ebx
        push  0x467aac
        push  0x800
        push  eax
        call DirectInput8Create
        test  eax,eax
        jge loc_0043B926
        push  0x46f9e0
        mov  ecx,0x474f70
        mov  DWORD PTR [ebx],0x0
        call FUN_0044b810
        add  esp,0x4
        pop  ebx
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043B926:
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax]
        push  edi
        push  0x0
        lea  edi,[esi+0x10]
        push  edi
        push  0x46793c
        push  eax
        call  DWORD PTR [ecx+0xc]
        test  eax,eax
        jge loc_0043B969
        mov  eax,DWORD PTR [ebx]
        test  eax,eax
        je loc_0043B950
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [ebx],0x0
    loc_0043B950:
        push  0x46f9e0
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  edi
        pop  ebx
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043B969:
        mov  eax,DWORD PTR [edi]
        mov  ecx,DWORD PTR [eax]
        push  0x4664fc
        push  eax
        call  DWORD PTR [ecx+0x2c]
        test  eax,eax
        mov  eax,DWORD PTR [edi]
        jge loc_0043B9B7
        test  eax,eax
        je loc_0043B98C
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [edi],0x0
    loc_0043B98C:
        mov  eax,DWORD PTR [ebx]
        test  eax,eax
        je loc_0043B99E
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [ebx],0x0
    loc_0043B99E:
        push  0x46f9b0
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  edi
        pop  ebx
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043B9B7:
        mov  ecx,DWORD PTR [esi+0x48]
        mov  edx,DWORD PTR [eax]
        push  0x16
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x34]
        test  eax,eax
        jge loc_0043B9F7
        mov  eax,DWORD PTR [edi]
        test  eax,eax
        je loc_0043B9D9
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [edi],0x0
    loc_0043B9D9:
        call FUN_00421d20
        push  0x46f97c
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  edi
        pop  ebx
        or   eax,0xffffffff
        pop  esi
        ret
    loc_0043B9F7:
        mov  edi,DWORD PTR [edi]
        mov  eax,DWORD PTR [edi]
        push  edi
        call  DWORD PTR [eax+0x1c]
        push  0x46f954
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  ebx,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [ebx]
        add  esp,0x4
        push  0x1
        push  0x0
        push  0x43baf0
        push  0x4
        push  ebx
        call  DWORD PTR [ecx+0x10]
        mov  eax,DWORD PTR [esi+0x14]
        test  eax,eax
        je loc_0043BA81
        mov  edx,DWORD PTR [eax]
        push  0x466704
        push  eax
        call  DWORD PTR [edx+0x2c]
        mov  edx,DWORD PTR [esi+0x48]
        mov  eax,DWORD PTR [esi+0x14]
        mov  ecx,DWORD PTR [eax]
        push  0xa
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x34]
        mov  DWORD PTR ds:0x491c44,0x2c
        mov  eax,DWORD PTR [esi+0x14]
        mov  ecx,DWORD PTR [eax]
        push  0x491c44
        push  eax
        call  DWORD PTR [ecx+0xc]
        mov  esi,DWORD PTR [esi+0x14]
        mov  edx,DWORD PTR [esi]
        push  0x0
        push  0x0
        push  0x43bb30
        push  esi
        call  DWORD PTR [edx+0x10]
        push  0x46f934
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_0043BA81:
        pop  edi
        pop  ebx
        xor  eax,eax
        pop  esi
        ret
    }
}
