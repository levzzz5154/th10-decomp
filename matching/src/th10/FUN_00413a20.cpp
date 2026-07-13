// 00413A20: FUN_00413a20
// Original size: 416 bytes, actual code: 81 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_00413a20(void) {
    __asm {
        mov  eax,ds:0x477848
        mov  ecx,DWORD PTR [eax+0x20]
        mov  edx,DWORD PTR ds:0x491c10
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  ecx
        mov  ecx,0x1c
        call FUN_00447280
        xor  ebx,ebx
        cmp  eax,ebx
        mov  DWORD PTR [ebp+0x9e80],eax
        je loc_00413B27
        mov  eax,ds:0x491be8
        cmp  eax,ebx
        je loc_00413ACB
        mov  DWORD PTR [ebp+0x9ebc],eax
        mov  DWORD PTR ds:0x491be8,ebx
    loc_00413A64:
        mov  eax,DWORD PTR [ebp+0x9e70]
        test  al,0x1
        jne loc_00413A97
        or   eax,0x1
        mov  DWORD PTR [ebp+0x9e64],ebx
        mov  DWORD PTR [ebp+0x9e60],0xfff0bdc1
        mov  DWORD PTR [ebp+0x9e68],ebx
        mov  DWORD PTR [ebp+0x9e6c],0x476f78
        mov  DWORD PTR [ebp+0x9e70],eax
    loc_00413A97:
        mov  DWORD PTR [ebp+0x9e64],ebx
        mov  DWORD PTR [ebp+0x9e68],ebx
        or   eax,0xffffffff
        mov  DWORD PTR [ebp+0x9e60],eax
        mov  ecx,DWORD PTR ds:0x474c44
        mov  DWORD PTR [ebp+0x9ec0],eax
        mov  DWORD PTR [ebp+0x9ec4],eax
        mov  DWORD PTR [ebp+0x9e78],ecx
        pop  ebp
        xor  eax,eax
        pop  ebx
        ret  0x4
    loc_00413ACB:
        mov  edx,DWORD PTR ds:0x477848
        mov  eax,ds:0x474c68
        mov  eax,DWORD PTR [edx+eax*4+0x18]
        mov  BYTE PTR ds:0x497c38,bl
        mov  ecx,eax
    loc_00413AE2:
        mov  dl,BYTE PTR [eax]
        inc  eax
        cmp  dl,bl
        jne loc_00413AE2
        push  esi
        push  edi
        mov  edi,0x497c38
        sub  eax,ecx
        mov  esi,ecx
        dec  edi
    loc_00413AF5:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        cmp  cl,bl
        jne loc_00413AF5
        mov  ecx,eax
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        push  ebx
        and  ecx,0x3
        push  ebx
        mov  eax,0x497c38
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        call FUN_0044b360
        cmp  eax,ebx
        pop  edi
        mov  DWORD PTR [ebp+0x9ebc],eax
        pop  esi
        jne loc_00413A64
    loc_00413B27:
        push  0x46cb68
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        ret  0x4
    }
}
