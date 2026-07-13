// 00438260: FUN_00438260
// Original size: 240 bytes, actual code: 100 instructions
extern "C" void FUN_00438510(void);
extern "C" void FUN_004386b0(void);
extern "C" void FUN_00462428(void);
extern "C" void FUN_004624e5(void);

extern "C" __declspec(naked) void FUN_00438260(void) {
    __asm {
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x14]
        push  edi
        mov  edi,DWORD PTR [esp+0x14]
        cmp  DWORD PTR [edi+0x14],esi
        mov  ebx,ecx
        jae loc_00438278
        call FUN_00462428
    loc_00438278:
        mov  ebp,DWORD PTR [edi+0x14]
        mov  eax,DWORD PTR [esp+0x1c]
        sub  ebp,esi
        cmp  eax,ebp
        jae loc_00438287
        mov  ebp,eax
    loc_00438287:
        cmp  ebx,edi
        jne loc_004382AA
        push  0xffffffff
        add  ebp,esi
        push  ebp
        mov  ecx,ebx
        call FUN_00438510
        push  esi
        push  0x0
        mov  ecx,ebx
        call FUN_00438510
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret  0xc
    loc_004382AA:
        cmp  ebp,0xfffffffe
        jbe loc_004382B6
        mov  ecx,ebx
        call FUN_004624e5
    loc_004382B6:
        mov  eax,DWORD PTR [ebx+0x18]
        cmp  eax,ebp
        jae loc_004382DE
        mov  eax,DWORD PTR [ebx+0x14]
        push  eax
        push  ebp
        mov  ecx,ebx
        call FUN_004386b0
        test  ebp,ebp
    loc_004382CB:
        jbe loc_0043833A
        mov  ecx,DWORD PTR [edi+0x18]
        mov  eax,0x10
        cmp  ecx,eax
        jb loc_00438308
        mov  edx,DWORD PTR [edi+0x4]
        jmp loc_0043830B
    loc_004382DE:
        test  ebp,ebp
        jne loc_004382CB
        cmp  eax,0x10
        mov  DWORD PTR [ebx+0x14],ebp
        jb loc_004382F9
        mov  eax,DWORD PTR [ebx+0x4]
        pop  edi
        pop  esi
        mov  BYTE PTR [eax],0x0
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret  0xc
    loc_004382F9:
        pop  edi
        lea  eax,[ebx+0x4]
        pop  esi
        mov  BYTE PTR [eax],0x0
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret  0xc
    loc_00438308:
        lea  edx,[edi+0x4]
    loc_0043830B:
        cmp  DWORD PTR [ebx+0x18],eax
        lea  eax,[ebx+0x4]
        jb loc_00438317
        mov  edi,DWORD PTR [eax]
        jmp loc_00438319
    loc_00438317:
        mov  edi,eax
    loc_00438319:
        add  esi,edx
        mov  ecx,ebp
        mov  edx,ecx
        shr  ecx,0x2
        rep movsd
        mov  ecx,edx
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        cmp  DWORD PTR [ebx+0x18],0x10
        mov  DWORD PTR [ebx+0x14],ebp
        jb loc_00438336
        mov  eax,DWORD PTR [eax]
    loc_00438336:
        mov  BYTE PTR [eax+ebp*1],0x0
    loc_0043833A:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,ebx
        pop  ebx
        ret  0xc
    }
}
