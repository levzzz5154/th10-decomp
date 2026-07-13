// 00409F90: FUN_00409f90
// Original size: 2480 bytes, actual code: 46 instructions
extern "C" void FUN_004493e0(void);

extern "C" __declspec(naked) void FUN_00409f90(void) {
    __asm {
        push  ebx
        mov  ebx,DWORD PTR ds:0x491c10
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        push  edi
        lea  esi,[ebx+0x3ad090]
        mov  edi,0x4
        nop
    loc_00409FB0:
        mov  edx,DWORD PTR [esi]
        mov  eax,ebx
        call FUN_004493e0
        add  esi,0x4
        dec  edi
        jne loc_00409FB0
        mov  eax,DWORD PTR [ebp+0x58]
        xor  edi,edi
        cmp  eax,edi
        je loc_00409FE0
    loc_00409FC8:
        mov  esi,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        cmp  eax,edi
        je loc_00409FDA
        mov  edx,DWORD PTR [eax]
        push  0x1
        mov  ecx,eax
        call  DWORD PTR [edx+0x14]
    loc_00409FDA:
        cmp  esi,edi
        mov  eax,esi
        jne loc_00409FC8
    loc_00409FE0:
        mov  eax,DWORD PTR [ebp+0x8]
        cmp  eax,edi
        mov  DWORD PTR [ebp+0x64],edi
        mov  DWORD PTR [ebp+0x10],edi
        mov  ecx,0xfffffffd
        je loc_00409FF5
        and  DWORD PTR [eax+0x4],ecx
    loc_00409FF5:
        mov  eax,DWORD PTR [ebp+0xc]
        cmp  eax,edi
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        je loc_0040A003
        and  DWORD PTR [eax+0x4],ecx
    loc_0040A003:
        ret  0x4
    }
}
