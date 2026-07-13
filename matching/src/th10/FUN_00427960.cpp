// 00427960: FUN_00427960
// Original size: 384 bytes, actual code: 95 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00427960(void) {
    __asm {
        sub  esp,0xc
        mov  eax,DWORD PTR [esi+0x88]
        push  ebx
        push  ebp
        push  edi
        mov  edi,DWORD PTR ds:0x477834
        mov  ebx,DWORD PTR [edi+0x4474]
        shl  eax,0x6
        test  ebx,ebx
        mov  ecx,DWORD PTR [eax+edi*1+0x43ac]
        lea  eax,[eax+edi*1+0x43ac]
        mov  DWORD PTR [esi+0x34],ecx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [esp+0x14],ebx
        mov  DWORD PTR [esi+0x38],edx
        jne loc_004279B9
        mov  ebp,DWORD PTR [edi+0x3cc]
        mov  eax,ecx
        mov  ecx,edx
        mov  edx,DWORD PTR [edi+0x3d0]
        sub  eax,ebp
        sub  ecx,edx
        mov  DWORD PTR [esi+0x44],eax
        mov  DWORD PTR [esi+0x48],ecx
        jmp loc_00427A9E
    loc_004279B9:
        mov  edx,DWORD PTR [esi+0x48]
        fld  DWORD PTR ds:0x470b90
        mov  ecx,DWORD PTR [edi+0x3d0]
        mov  ebp,DWORD PTR [esi+0x44]
        mov  eax,DWORD PTR [edi+0x3cc]
        add  ecx,edx
        mov  edx,DWORD PTR [esi+0x88]
        add  eax,ebp
        shl  edx,0x6
        lea  edx,[edx+edi*1+0x43ac]
        mov  DWORD PTR [edx],eax
        mov  DWORD PTR [edx+0x4],ecx
        mov  eax,DWORD PTR [esi+0x88]
        shl  eax,0x3
        lea  ebp,[eax+0x1]
        add  eax,0x7
        cmp  ebp,eax
        jg loc_00427A9C
        lea  ebx,[edi+ebp*8+0x4370]
        jmp loc_00427A10
        lea  ebx,[ebx+0x0]
    loc_00427A10:
        mov  eax,DWORD PTR [esi+0x88]
        shl  eax,0x6
        mov  ecx,DWORD PTR [eax+edi*1+0x436c]
        mov  edx,DWORD PTR [eax+edi*1+0x43ac]
        add  eax,edi
        sub  edx,ecx
        mov  DWORD PTR [esp+0xc],edx
        fild  DWORD PTR [esp+0xc]
        mov  DWORD PTR [esp+0x10],ecx
        fmul  st,st(1)
        fiadd DWORD PTR [esp+0x10]
        call FUN_00463b2c
        mov  DWORD PTR [ebx-0x4],eax
        mov  eax,DWORD PTR [esi+0x88]
        shl  eax,0x6
        mov  ecx,DWORD PTR [eax+edi*1+0x4370]
        mov  edx,DWORD PTR [eax+edi*1+0x43b0]
        add  eax,edi
        sub  edx,ecx
        mov  DWORD PTR [esp+0x10],edx
        fild  DWORD PTR [esp+0x10]
        mov  DWORD PTR [esp+0xc],ecx
        fmul  st,st(1)
        fiadd DWORD PTR [esp+0xc]
        call FUN_00463b2c
        fadd  DWORD PTR ds:0x470b90
        mov  DWORD PTR [ebx],eax
        mov  eax,DWORD PTR [esi+0x88]
        inc  ebp
        lea  ecx,[eax*8+0x7]
        add  ebx,0x8
        cmp  ebp,ecx
        jle loc_00427A10
        mov  ebx,DWORD PTR [esp+0x14]
    loc_00427A9C:
        fstp  st(0)
    loc_00427A9E:
        mov  ebp,DWORD PTR [edi+0x3cc]
        mov  eax,DWORD PTR [esi+0x44]
        mov  edx,DWORD PTR [edi+0x3d0]
        mov  ecx,DWORD PTR [esi+0x48]
        add  eax,ebp
        pop  edi
        add  ecx,edx
        mov  DWORD PTR [esi+0x34],eax
        mov  DWORD PTR [esi+0x38],ecx
        pop  ebp
        mov  DWORD PTR [esi+0x84],ebx
        pop  ebx
        add  esp,0xc
        ret
    }
}
