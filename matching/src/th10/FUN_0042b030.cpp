// 0042B030: FUN_0042b030
// Original size: 432 bytes, actual code: 145 instructions
extern "C" void FUN_00435dc0(void);
extern "C" void FUN_0044b0d0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_0042b030(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [ebx]
        test  eax,eax
        push  ebp
        push  esi
        push  edi
        je loc_0042B198
        cmp  DWORD PTR [eax],0x30314854
        jne loc_0042B183
        cmp  WORD PTR [eax+0x8],0x3
        jne loc_0042B183
        mov  ecx,DWORD PTR [eax+0x10]
        push  ecx
        push  0x10
        push  0x35
        add  eax,0x18
        push  ecx
        push  eax
        mov  al,0xac
        call FUN_0044b0d0
        mov  eax,DWORD PTR [ebx]
        lea  esi,[eax+0x18]
        mov  eax,DWORD PTR [eax+0x14]
        shl  eax,0x2
        push  eax
        call _malloc
        mov  ecx,DWORD PTR [ebx]
        add  esp,0x4
        mov  DWORD PTR [ebx+0x4],eax
        mov  edx,DWORD PTR [ecx+0x14]
        push  edx
        push  eax
        mov  eax,DWORD PTR [ecx+0x10]
        push  eax
        push  esi
        call FUN_00435dc0
        mov  ecx,DWORD PTR [ebx]
        mov  eax,DWORD PTR [ecx+0x14]
        test  eax,eax
        mov  edx,DWORD PTR [ebx+0x4]
        mov  DWORD PTR [esp+0xc],eax
        jle loc_0042B1D0
    loc_0042B0A5:
        mov  ax,WORD PTR [edx]
        cmp  ax,0x5243
        jne loc_0042B10F
        cmp  WORD PTR [edx+0x2],0x0
        jne loc_0042B161
        xor  ecx,ecx
        lea  eax,[edx+0xc]
        mov  esi,0xb3e
    loc_0042B0C3:
        movzx ebp,BYTE PTR [eax-0x3]
        movzx edi,BYTE PTR [eax-0x4]
        add  edi,ebp
        movzx ebp,BYTE PTR [eax-0x2]
        add  edi,ebp
        movzx ebp,BYTE PTR [eax-0x1]
        add  edi,ebp
        movzx ebp,BYTE PTR [eax+0x1]
        add  edi,ebp
        movzx ebp,BYTE PTR [eax]
        add  ebp,ecx
        add  eax,0x6
        dec  esi
        lea  ecx,[edi+ebp*1]
        jne loc_0042B0C3
        cmp  ecx,DWORD PTR [edx+0x4]
        jne loc_0042B161
        cmp  DWORD PTR [edx+0x8],0x437c
        jne loc_0042B161
        mov  eax,DWORD PTR [edx+0xc]
        imul  eax,eax,0x437c
        mov  ecx,0x10df
        lea  edi,[eax+ebx*1+0x8]
        jmp loc_0042B15D
    loc_0042B10F:
        cmp  ax,0x5453
        jne loc_0042B183
        cmp  WORD PTR [edx+0x2],0x0
        jne loc_0042B161
        xor  ecx,ecx
        lea  eax,[edx+0xa]
        mov  esi,0x110
    loc_0042B126:
        movzx ebp,BYTE PTR [eax-0x1]
        movzx edi,BYTE PTR [eax-0x2]
        add  edi,ebp
        movzx ebp,BYTE PTR [eax+0x1]
        add  edi,ebp
        movzx ebp,BYTE PTR [eax]
        add  ebp,ecx
        add  eax,0x4
        dec  esi
        lea  ecx,[edi+ebp*1]
        jne loc_0042B126
        cmp  ecx,DWORD PTR [edx+0x4]
        jne loc_0042B161
        cmp  DWORD PTR [edx+0x8],0x448
        jne loc_0042B161
        lea  edi,[ebx+0x1d86c]
        mov  ecx,0x112
    loc_0042B15D:
        mov  esi,edx
        rep movsd
    loc_0042B161:
        mov  ecx,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [edx+0x8]
        sub  ecx,eax
        mov  DWORD PTR [esp+0xc],ecx
        js loc_0042B183
        add  edx,eax
        mov  eax,ecx
        test  eax,eax
        jg loc_0042B0A5
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        pop  ecx
        ret
    loc_0042B183:
        mov  eax,DWORD PTR [ebx]
        test  eax,eax
        je loc_0042B198
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx],0x0
    loc_0042B198:
        push  0x18
        call _malloc
        mov  DWORD PTR [ebx],eax
        add  esp,0x4
        xor  ecx,ecx
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        mov  DWORD PTR [eax+0xc],ecx
        mov  DWORD PTR [eax+0x10],ecx
        mov  DWORD PTR [eax+0x14],ecx
        mov  edx,DWORD PTR [ebx]
        mov  DWORD PTR [edx],0x30314854
        mov  eax,DWORD PTR [ebx]
        mov  WORD PTR [eax+0x8],0x3
        mov  ecx,DWORD PTR [ebx]
        mov  DWORD PTR [ecx+0xc],0x100
    loc_0042B1D0:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        pop  ecx
        ret
    }
}
