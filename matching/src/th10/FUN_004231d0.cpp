// 004231D0: FUN_004231d0
// Original size: 416 bytes, actual code: 102 instructions
extern "C" void FUN_00420a90(void);
extern "C" void FUN_00424480(void);
extern "C" void FUN_0043e460(void);
extern "C" void FUN_00448ac0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_004231d0(void) {
    __asm {
        push  ecx
        mov  eax,ds:0x477810
        cmp  DWORD PTR [eax+0x5c],0x1
        jne loc_004231F7
        mov  eax,ds:0x491ff4
        and  eax,0x1000
        neg  eax
        sbb  eax,eax
        and  eax,0xfffffffe
        add  eax,0x4
        mov  ds:0x491fb8,eax
        pop  ecx
        ret
    loc_004231F7:
        mov  DWORD PTR [edi+0x4],0x6
        mov  ecx,DWORD PTR [edi+0x20]
        xor  edx,edx
        test  cl,0x1
        jne loc_00423222
        or   ecx,0x1
        mov  DWORD PTR [edi+0x14],edx
        mov  DWORD PTR [edi+0x10],0xfff0bdc1
        mov  DWORD PTR [edi+0x18],edx
        mov  DWORD PTR [edi+0x1c],0x476f78
        mov  DWORD PTR [edi+0x20],ecx
    loc_00423222:
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [edi+0x14],edx
        mov  DWORD PTR [edi+0x18],edx
        mov  DWORD PTR [edi+0x10],0xffffffff
        mov  edx,DWORD PTR [eax+0x58]
        push  ebx
        push  ebp
        or   edx,0x10
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [eax+0x58],edx
        mov  ebp,DWORD PTR [ecx+0x8998]
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        push  0x0
        mov  DWORD PTR [ebx+0x35c],ecx
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0xc]
        mov  edx,esi
        call FUN_00448ac0
        mov  eax,DWORD PTR [esp+0xc]
        push  0x1c0
        push  0x180
        push  0x10
        push  0x20
        push  eax
        mov  DWORD PTR [edi+0x1d8],eax
        call FUN_00424480
        mov  edx,DWORD PTR ds:0x47770c
        mov  ebp,DWORD PTR [edx+0x9ec8]
        mov  DWORD PTR [edi+0x2c4],ebp
        call FUN_00449950
        mov  ebx,eax
        mov  ecx,DWORD PTR [ebx+0x35c]
        or   ecx,0x40000000
        push  0x80
        mov  DWORD PTR [ebx+0x35c],ecx
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0xc]
        call FUN_00448ac0
        mov  eax,DWORD PTR [esp+0xc]
        push  0x46e0d8
        push  0x0
        mov  DWORD PTR [edi+0x1d4],eax
        call FUN_00420a90
        test  BYTE PTR ds:0x491d78,0x10
        pop  esi
        pop  ebp
        pop  ebx
        je loc_00423329
        push  0x0
        push  0x4
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
    loc_00423329:
        push  0x0
        push  0x2
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
        mov  ecx,DWORD PTR ds:0x47783c
        mov  BYTE PTR [ecx+0x1d8a3],0x1
        mov  DWORD PTR [edi+0x1e4],0x0
        mov  edx,DWORD PTR ds:0x476f78
        mov  DWORD PTR [edi+0x2c0],edx
        mov  DWORD PTR ds:0x476f78,0x3f800000
        pop  ecx
        ret
    }
}
