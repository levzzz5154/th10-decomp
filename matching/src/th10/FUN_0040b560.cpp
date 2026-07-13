// 0040B560: FUN_0040b560
// Original size: 592 bytes, actual code: 181 instructions
extern "C" void FUN_0040ba90(void);
extern "C" void FUN_00448d50(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b810(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0040b560(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x4657bb
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0xc
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x24]
        push  esi
        push  0x24
        call operator_new
        xor  ebx,ebx
        add  esp,0x4
        cmp  eax,ebx
        je loc_0040B5B0
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        mov  esi,eax
        jmp loc_0040B5B2
    loc_0040B5B0:
        xor  esi,esi
    loc_0040B5B2:
        mov  eax,DWORD PTR [esi+0x4]
        or   eax,0x3
        push  edi
        mov  DWORD PTR [esi+0x4],eax
        mov  eax,ds:0x491be4
        push  eax
        mov  edi,0x1c
        mov  DWORD PTR [esi+0x8],0x40ba70
        mov  DWORD PTR [esi+0xc],ebx
        mov  DWORD PTR [esi+0x10],ebx
        mov  DWORD PTR [esi+0x20],ebp
        call FUN_00449ae0
        push  0x24
        mov  DWORD PTR [ebp+0x8],esi
        call operator_new
        add  esp,0x4
        cmp  eax,ebx
        je loc_0040B60E
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebx
        mov  DWORD PTR [eax+0xc],ebx
        mov  DWORD PTR [eax+0x10],ebx
        mov  DWORD PTR [eax],ebx
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebx
        mov  DWORD PTR [eax+0x1c],ebx
        mov  esi,eax
        jmp loc_0040B610
    loc_0040B60E:
        xor  esi,esi
    loc_0040B610:
        mov  edi,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR ds:0x491be4
        or   edi,0x3
        mov  DWORD PTR [esi+0x4],edi
        push  ecx
        mov  edi,0x6
        mov  DWORD PTR [esi+0x8],0x40ba80
        mov  DWORD PTR [esi+0xc],ebx
        mov  DWORD PTR [esi+0x10],ebx
        mov  DWORD PTR [esi+0x20],ebp
        call FUN_00449b70
        mov  eax,ds:0x4776e0
        mov  DWORD PTR [ebp+0xc],esi
        mov  ecx,DWORD PTR [eax+0x89a4]
        cmp  ecx,ebx
        lea  esi,[eax+0x89a4]
        mov  DWORD PTR [esp+0x10],0x43f00000
        mov  DWORD PTR [esp+0x14],0x43c40000
        mov  DWORD PTR [esp+0x18],0x0
        jne loc_0040B684
        mov  eax,DWORD PTR [eax+0x8994]
        push  edi
        lea  edx,[esp+0x30]
        push  edx
        push  eax
        lea  edi,[esp+0x1c]
        call FUN_00448d50
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [esi],eax
    loc_0040B684:
        mov  eax,ds:0x474c68
        mov  ecx,DWORD PTR ds:0x474c6c
        lea  edx,[ecx+eax*2]
        add  eax,edx
        mov  DWORD PTR [ebp+0x1c],eax
        cmp  DWORD PTR ds:0x474c90,ebx
        mov  ecx,0x1
        jne loc_0040B6B2
        cmp  DWORD PTR ds:0x474c74,ecx
        jl loc_0040B6B2
        add  eax,0x6
        mov  DWORD PTR [ebp+0x1c],eax
    loc_0040B6B2:
        mov  edx,DWORD PTR [ebp+0x1c]
        mov  eax,ds:0x47783c
        cmp  BYTE PTR [edx+eax*1+0x1d882],bl
        jne loc_0040B6C6
        or   DWORD PTR [ebp+0x20],ecx
    loc_0040B6C6:
        cmp  BYTE PTR [eax+0x1d88e],bl
        jne loc_0040B6D2
        or   DWORD PTR [ebp+0x20],0x2
    loc_0040B6D2:
        mov  edx,DWORD PTR [ebp+0x1c]
        mov  BYTE PTR [edx+eax*1+0x1d882],cl
        cmp  DWORD PTR [ebp+0x1c],0x6
        jl loc_0040B6E8
        mov  BYTE PTR [eax+0x1d88e],cl
    loc_0040B6E8:
        mov  eax,DWORD PTR [ebp+0x1c]
        mov  eax,DWORD PTR [eax*4+0x474440]
        mov  BYTE PTR ds:0x497c38,bl
        mov  esi,eax
        lea  ebx,[ebx+0x0]
    loc_0040B700:
        mov  cl,BYTE PTR [eax]
        inc  eax
        cmp  cl,bl
        jne loc_0040B700
        mov  edi,0x497c38
        sub  eax,esi
        dec  edi
        nop
    loc_0040B710:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        cmp  cl,bl
        jne loc_0040B710
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
        mov  DWORD PTR [ebp+0x14],eax
        pop  edi
        jne loc_0040B763
        push  0x46cb68
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret  0x4
    loc_0040B763:
        push  0xec
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp+0x28],eax
        cmp  eax,ebx
        mov  DWORD PTR [esp+0x20],ebx
        je loc_0040B78D
        mov  ecx,DWORD PTR [ebp+0x14]
        mov  edx,DWORD PTR [ecx+0x4]
        add  edx,ecx
        push  edx
        push  eax
        call FUN_0040ba90
        jmp loc_0040B78F
    loc_0040B78D:
        xor  eax,eax
    loc_0040B78F:
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [ebp+0x18],eax
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret  0x4
    }
}
