// 00438420: FUN_00438420
// Original size: 240 bytes, actual code: 105 instructions
extern "C" void FUN_00438260(void);
extern "C" void FUN_004386b0(void);
extern "C" void FUN_004624e5(void);

extern "C" __declspec(naked) void FUN_00438420(void) {
    __asm {
        push  ebx
        mov  ebx,ecx
        mov  edx,DWORD PTR [ebx+0x18]
        cmp  edx,0x10
        push  esi
        push  edi
        jb loc_00438432
        mov  eax,DWORD PTR [ebx+0x4]
        jmp loc_00438435
    loc_00438432:
        lea  eax,[ebx+0x4]
    loc_00438435:
        mov  esi,DWORD PTR [esp+0x10]
        cmp  esi,eax
        jb loc_00438471
        cmp  edx,0x10
        lea  eax,[ebx+0x4]
        jb loc_00438449
        mov  ecx,DWORD PTR [eax]
        jmp loc_0043844B
    loc_00438449:
        mov  ecx,eax
    loc_0043844B:
        mov  edi,DWORD PTR [ebx+0x14]
        add  edi,ecx
        cmp  edi,esi
        jbe loc_00438471
        cmp  edx,0x10
        jb loc_0043845B
        mov  eax,DWORD PTR [eax]
    loc_0043845B:
        mov  ecx,DWORD PTR [esp+0x14]
        push  ecx
        sub  esi,eax
        push  esi
        push  ebx
        mov  ecx,ebx
        call FUN_00438260
        pop  edi
        pop  esi
        pop  ebx
        ret  0x8
    loc_00438471:
        push  ebp
        mov  ebp,DWORD PTR [esp+0x18]
        cmp  ebp,0xfffffffe
        jbe loc_00438482
        mov  ecx,ebx
        call FUN_004624e5
    loc_00438482:
        mov  eax,DWORD PTR [ebx+0x18]
        cmp  eax,ebp
        jae loc_004384A4
        mov  edx,DWORD PTR [ebx+0x14]
        push  edx
        push  ebp
        mov  ecx,ebx
        call FUN_004386b0
        test  ebp,ebp
    loc_00438497:
        jbe loc_00438501
        cmp  DWORD PTR [ebx+0x18],0x10
        jb loc_004384CE
        mov  edi,DWORD PTR [ebx+0x4]
        jmp loc_004384D1
    loc_004384A4:
        test  ebp,ebp
        jne loc_00438497
        cmp  eax,0x10
        mov  DWORD PTR [ebx+0x14],ebp
        jb loc_004384BF
        mov  eax,DWORD PTR [ebx+0x4]
        pop  ebp
        pop  edi
        mov  BYTE PTR [eax],0x0
        pop  esi
        mov  eax,ebx
        pop  ebx
        ret  0x8
    loc_004384BF:
        pop  ebp
        lea  eax,[ebx+0x4]
        pop  edi
        mov  BYTE PTR [eax],0x0
        pop  esi
        mov  eax,ebx
        pop  ebx
        ret  0x8
    loc_004384CE:
        lea  edi,[ebx+0x4]
    loc_004384D1:
        mov  ecx,ebp
        mov  eax,ecx
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        cmp  DWORD PTR [ebx+0x18],0x10
        mov  DWORD PTR [ebx+0x14],ebp
        jb loc_004384FA
        mov  eax,DWORD PTR [ebx+0x4]
        mov  BYTE PTR [eax+ebp*1],0x0
        pop  ebp
        pop  edi
        pop  esi
        mov  eax,ebx
        pop  ebx
        ret  0x8
    loc_004384FA:
        lea  eax,[ebx+0x4]
        mov  BYTE PTR [eax+ebp*1],0x0
    loc_00438501:
        pop  ebp
        pop  edi
        pop  esi
        mov  eax,ebx
        pop  ebx
        ret  0x8
    }
}
