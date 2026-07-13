// 00427E90: FUN_00427e90
// Original size: 720 bytes, actual code: 218 instructions
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);
extern "C" void FUN_0044bc70(void);
extern "C" void FUN_0044c5d0(void);

extern "C" __declspec(naked) void FUN_00427e90(void) {
    __asm {
        sub  esp,0x14
        push  ebx
        mov  ebx,DWORD PTR [esp+0x1c]
        push  esi
        mov  esi,DWORD PTR [esp+0x24]
        mov  al,BYTE PTR [esi+0x1d]
        xor  ecx,ecx
        cmp  al,0x3
        push  edi
        lea  edi,[ebx+0x49c]
        jne loc_00427EBE
        movsx eax,BYTE PTR [esi+0x1c]
        cmp  DWORD PTR [ebx+eax*4+0x42f4],ecx
        jne loc_00428152
    loc_00427EBE:
        xor  eax,eax
    loc_00427EC0:
        cmp  DWORD PTR [edi+0x40],ecx
        je loc_00427EDB
        inc  eax
        add  edi,0x5c
        cmp  eax,0x80
        jl loc_00427EC0
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        add  esp,0x14
        ret  0xc
    loc_00427EDB:
        mov  eax,DWORD PTR [edi+0x10]
        test  al,0x1
        mov  DWORD PTR [edi+0x40],0x1
        mov  DWORD PTR [edi+0x58],esi
        jne loc_00427F05
        or   eax,0x1
        mov  DWORD PTR [edi+0x4],ecx
        mov  DWORD PTR [edi],0xfff0bdc1
        mov  DWORD PTR [edi+0x8],ecx
        mov  DWORD PTR [edi+0xc],0x476f78
        mov  DWORD PTR [edi+0x10],eax
    loc_00427F05:
        mov  DWORD PTR [edi+0x4],ecx
        mov  DWORD PTR [edi+0x8],ecx
        mov  DWORD PTR [edi],0xffffffff
        mov  al,BYTE PTR [esi+0x1c]
        test  al,al
        push  ebp
        jne loc_00427F3A
        lea  ebp,[edi+0x14]
        lea  ecx,[ebx+0x3c0]
        mov  eax,DWORD PTR [ecx]
        mov  edx,ebp
        mov  DWORD PTR [edx],eax
        mov  eax,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x4],eax
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x10],ebp
        mov  DWORD PTR [edx+0x8],ecx
        jmp loc_00427F91
    loc_00427F3A:
        movsx edx,al
        imul  edx,edx,0x98
        fild  DWORD PTR [edx+ebx*1+0x3244]
        fmul  DWORD PTR ds:0x470b00
        fstp  DWORD PTR [esp+0x18]
        fild  DWORD PTR [edx+ebx*1+0x3248]
        mov  ecx,DWORD PTR [esp+0x18]
        lea  eax,[edx+ebx*1+0x3244]
        lea  eax,[edi+0x14]
        fmul  DWORD PTR ds:0x470b00
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [esp+0x20],0x0
        mov  ecx,DWORD PTR [esp+0x20]
        fstp  DWORD PTR [esp+0x1c]
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x4],edx
        mov  DWORD PTR [eax+0x8],ecx
        mov  ebp,eax
    loc_00427F91:
        cmp  BYTE PTR [esi+0x1d],0x3
        jne loc_00427FA6
        movsx edx,BYTE PTR [esi+0x1c]
        mov  DWORD PTR [ebx+edx*4+0x42f4],0x1
    loc_00427FA6:
        mov  eax,DWORD PTR [esi+0x18]
        mov  DWORD PTR [edi+0x2c],eax
        mov  ecx,DWORD PTR [esi+0x14]
        push  ecx
        call FUN_0044bc70
        fstp  DWORD PTR [edi+0x30]
        test  BYTE PTR [ebp+0x28],0x1
        jne loc_00427FD7
        mov  edx,DWORD PTR [ebp+0x18]
        mov  eax,DWORD PTR [ebp+0x1c]
        push  edx
        push  eax
        lea  ecx,[ebp+0xc]
        call FUN_0044c5d0
        mov  DWORD PTR [ebp+0x14],0x0
        jmp loc_00427FF2
    loc_00427FD7:
        fld  DWORD PTR [ebp+0x24]
        push  ecx
        fadd  DWORD PTR [ebp+0x20]
        fstp  DWORD PTR [ebp+0x20]
        fld  DWORD PTR [ebp+0x18]
        fadd  DWORD PTR [ebp+0x1c]
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [ebp+0x1c]
    loc_00427FF2:
        fld  DWORD PTR [esi+0x4]
        fsub  DWORD PTR [edi+0x20]
        fadd  DWORD PTR [ebp+0x0]
        fstp  DWORD PTR [ebp+0x0]
        fld  DWORD PTR [esi+0x8]
        fsub  DWORD PTR [edi+0x24]
        fadd  DWORD PTR [edi+0x18]
        fstp  DWORD PTR [edi+0x18]
        movsx ebp,WORD PTR [esi+0x1e]
        mov  ecx,DWORD PTR [ebx+0x10]
        mov  esi,DWORD PTR ds:0x491c10
        add  ebp,0x5
        mov  DWORD PTR [esp+0x14],ecx
        call FUN_00449950
        mov  ecx,DWORD PTR [esp+0x14]
        mov  ebx,eax
        mov  eax,DWORD PTR [ebx+0x35c]
        push  ebp
        or   eax,0x40000000
        push  ebx
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],eax
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x14]
        mov  edx,esi
        call FUN_004489d0
        mov  edx,DWORD PTR [esp+0x14]
        mov  eax,edx
        mov  DWORD PTR [edi+0x44],edx
        xor  edx,edx
        cmp  eax,edx
        jne loc_0042806C
    loc_00428068:
        xor  ecx,ecx
        jmp loc_004280A7
    loc_0042806C:
        mov  ecx,DWORD PTR [esi+0x72dad4]
        cmp  ecx,edx
        je loc_00428083
    loc_00428076:
        mov  ebx,DWORD PTR [ecx]
        cmp  DWORD PTR [ebx],eax
        je loc_004280A1
        mov  ecx,DWORD PTR [ecx+0x4]
        cmp  ecx,edx
        jne loc_00428076
    loc_00428083:
        mov  ecx,DWORD PTR [esi+0x72dadc]
        cmp  ecx,edx
        je loc_00428068
        nop
    loc_00428090:
        mov  ebx,DWORD PTR [ecx]
        cmp  DWORD PTR [ebx],eax
        je loc_004280A1
        mov  ecx,DWORD PTR [ecx+0x4]
        cmp  ecx,edx
        jne loc_00428090
        xor  ecx,ecx
        jmp loc_004280A7
    loc_004280A1:
        mov  ecx,DWORD PTR [ecx]
        cmp  ecx,edx
        jne loc_004280AA
    loc_004280A7:
        mov  DWORD PTR [edi+0x44],edx
    loc_004280AA:
        mov  eax,DWORD PTR [ecx+0x35c]
        test  eax,0x8000000
        mov  ebx,DWORD PTR [esp+0x2c]
        je loc_004280CA
        mov  ebp,DWORD PTR [ebx+0x14]
        or   eax,0x4
        mov  DWORD PTR [ecx+0x2c],ebp
        mov  DWORD PTR [ecx+0x35c],eax
    loc_004280CA:
        cmp  BYTE PTR [ebx+0x1d],0x3
        jne loc_0042811D
        mov  eax,DWORD PTR [esp+0x28]
        mov  ebp,DWORD PTR [eax+0x10]
        call FUN_00449950
        mov  ebx,eax
        mov  edx,DWORD PTR [ebx+0x35c]
        push  0x10
        or   edx,0x40000000
        push  ebx
        mov  ecx,ebp
        mov  DWORD PTR [ebx+0x20],0xf
        mov  DWORD PTR [ebx+0x35c],edx
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x14]
        call FUN_004489d0
        mov  ecx,DWORD PTR [esp+0x14]
        mov  ebx,DWORD PTR [esp+0x2c]
        mov  DWORD PTR [edi+0x48],ecx
        jmp loc_00428120
    loc_0042811D:
        mov  DWORD PTR [edi+0x48],edx
    loc_00428120:
        mov  eax,DWORD PTR [ebx+0x24]
        test  eax,eax
        pop  ebp
        je loc_00428135
        mov  edx,DWORD PTR [esp+0x2c]
        mov  ecx,DWORD PTR [esp+0x24]
        push  edx
        mov  edx,edi
        call  eax
    loc_00428135:
        mov  ax,WORD PTR [ebx+0x22]
        test  ax,ax
        jl loc_00428152
        mov  ecx,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [ecx]
        movsx ebx,ax
        push  edx
        mov  esi,0x492590
        call FUN_0043dd10
    loc_00428152:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebx
        add  esp,0x14
        ret  0xc
    }
}
