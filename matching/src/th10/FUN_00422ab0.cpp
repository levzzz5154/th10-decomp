// 00422AB0: FUN_00422ab0
// Original size: 384 bytes, actual code: 97 instructions
extern "C" void FUN_0040c4d0(void);
extern "C" void FUN_00424480(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0043e460(void);
extern "C" void FUN_00448ac0(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00422ab0(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  DWORD PTR [ebp+0x4],0x1
        mov  eax,DWORD PTR [ebp+0x20]
        push  esi
        xor  ecx,ecx
        test  al,0x1
        push  edi
        jne loc_00422AE2
        or   eax,0x1
        mov  DWORD PTR [ebp+0x14],ecx
        mov  DWORD PTR [ebp+0x10],0xfff0bdc1
        mov  DWORD PTR [ebp+0x18],ecx
        mov  DWORD PTR [ebp+0x1c],0x476f78
        mov  DWORD PTR [ebp+0x20],eax
    loc_00422AE2:
        mov  eax,ds:0x477810
        mov  DWORD PTR [ebp+0x14],ecx
        mov  DWORD PTR [ebp+0x18],ecx
        mov  DWORD PTR [ebp+0x10],0xffffffff
        or   DWORD PTR [eax+0x58],0x10
        mov  eax,ds:0x4776e0
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [eax+0x8998]
        call FUN_00449950
        mov  ebx,eax
        mov  edx,DWORD PTR [ebx+0x35c]
        push  0x0
        or   edx,0x40000000
        push  ebx
        mov  ecx,edi
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],edx
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x14]
        mov  edx,esi
        call FUN_00448ac0
        mov  eax,DWORD PTR [esp+0x14]
        push  0x1c0
        push  0x180
        push  0x10
        push  0x20
        push  eax
        mov  DWORD PTR [ebp+0x1d8],eax
        call FUN_00424480
        mov  ecx,DWORD PTR ds:0x47770c
        mov  edi,DWORD PTR [ecx+0x9ec8]
        mov  DWORD PTR [ebp+0x2c4],edi
        call FUN_00449950
        mov  ebx,eax
        mov  edx,DWORD PTR [ebx+0x35c]
        push  0x79
        or   edx,0x40000000
        push  ebx
        mov  ecx,edi
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x14]
        call FUN_00448ac0
        mov  edx,DWORD PTR [esp+0x14]
        lea  esi,[ebp+0x1d4]
        mov  eax,esi
        mov  DWORD PTR [esi],edx
        call FUN_0040c4d0
        push  0x0
        mov  edi,0x20
        mov  ecx,0x492590
        call FUN_0043dc90
        push  0x0
        push  0x6
        mov  edx,0x46e0c0
        mov  eax,ecx
        call FUN_0043e460
        mov  eax,ds:0x477810
        mov  ecx,DWORD PTR [eax+0x5c]
        test  ecx,ecx
        je loc_00422C11
        mov  ebx,0x75
        lea  edi,[esp+0x14]
        call FUN_004497d0
        mov  edx,DWORD PTR ds:0x491c10
        mov  esi,eax
        mov  ecx,DWORD PTR [esi]
        push  ecx
        call FUN_004492a0
        mov  DWORD PTR [esi],0x0
    loc_00422C11:
        mov  edx,DWORD PTR ds:0x476f78
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x2c0],edx
        pop  ebp
        mov  DWORD PTR ds:0x476f78,0x3f800000
        pop  ebx
        ret  0x4
    }
}
