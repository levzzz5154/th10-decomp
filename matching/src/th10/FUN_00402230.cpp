// 00402230: FUN_00402230
// Original size: 528 bytes, actual code: 133 instructions
extern "C" void FUN_00403850(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);
extern "C" void FUN_0044b8e0(void);

extern "C" __declspec(naked) void FUN_00402230(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        test  ebp,ebp
        push  edi
        mov  ebx,eax
        jne loc_00402248
        mov  DWORD PTR ds:0x4776e8,ebx
        jmp loc_0040224E
    loc_00402248:
        mov  DWORD PTR ds:0x4776e4,ebx
    loc_0040224E:
        mov  eax,ds:0x474c7c
        push  ecx
        mov  DWORD PTR [ebx+0x2a30],eax
        call FUN_00403850
        test  eax,eax
        je loc_00402281
        push  0x46cc70
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        pop  edi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        add  esp,0xc
        ret  0x4
    loc_00402281:
        lea  eax,[ebx+0x2a4c]
        mov  edi,eax
        push  esi
        mov  DWORD PTR [esp+0x10],0x0
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,0x46
        mov  esi,0x491d7c
        rep movsd
        mov  DWORD PTR [eax],edx
        mov  DWORD PTR [esp+0x14],0x0
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [esp+0x18],0xc4160000
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [eax+0x8],edx
        mov  DWORD PTR [esp+0x10],0x0
        mov  ecx,DWORD PTR [esp+0x10]
        lea  eax,[ebx+0x2a58]
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [esp+0x14],0x43960000
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [esp+0x18],0x44160000
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [eax+0x8],ecx
        mov  DWORD PTR [esp+0x10],0x0
        mov  eax,DWORD PTR [esp+0x10]
        lea  edx,[ebx+0x2a64]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [esp+0x14],0x3f800000
        mov  ecx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [esp+0x18],0x0
        mov  eax,DWORD PTR [esp+0x18]
        mov  DWORD PTR [edx+0x8],eax
        mov  DWORD PTR [esp+0x10],0x0
        mov  edx,DWORD PTR [esp+0x10]
        lea  ecx,[ebx+0x2a88]
        mov  DWORD PTR [ecx],edx
        mov  DWORD PTR [esp+0x14],0x0
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x18],0x0
        mov  edx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [ecx+0x4],eax
        push  0x403050
        mov  DWORD PTR [ecx+0x8],edx
        mov  DWORD PTR [ebx+0x1ee0],0x4b12a310
        call FUN_00449ed0
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        lea  edi,[ebp+0xc]
        push  eax
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449ae0
        push  0x403060
        mov  DWORD PTR [ebx+0x8],esi
        call FUN_00449ed0
        mov  ecx,DWORD PTR ds:0x491be4
        mov  esi,eax
        and  DWORD PTR [esi+0x4],0xfffffffd
        lea  edi,[ebp+0x7]
        push  ecx
        mov  DWORD PTR [esi+0x20],ebx
        call FUN_00449b70
        push  0x403070
        mov  DWORD PTR [ebx+0xc],esi
        call FUN_00449ed0
        mov  edx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        and  eax,0xfffffffd
        lea  edi,[ebp+0xa]
        push  edx
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        xor  ecx,ecx
        mov  DWORD PTR [ebx+0x2a40],esi
        mov  DWORD PTR [ebx+0x2a34],ecx
        mov  eax,DWORD PTR [ebx+0x48]
        test  al,0x1
        pop  esi
        jne loc_00402407
        or   eax,0x1
        mov  DWORD PTR [ebx+0x3c],ecx
        mov  DWORD PTR [ebx+0x38],0xfff0bdc1
        mov  DWORD PTR [ebx+0x40],ecx
        mov  DWORD PTR [ebx+0x44],0x476f78
        mov  DWORD PTR [ebx+0x48],eax
    loc_00402407:
        mov  DWORD PTR [ebx+0x3c],ecx
        mov  DWORD PTR [ebx+0x40],ecx
        mov  DWORD PTR [ebx+0x38],0xffffffff
        mov  eax,DWORD PTR [ebx+0x2a18]
        pop  edi
        or   eax,0x1
        mov  DWORD PTR [ebx+0x2a18],eax
        pop  ebp
        mov  DWORD PTR [ebx+0x94],ecx
        mov  DWORD PTR [ebx+0xe0],ecx
        xor  eax,eax
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
