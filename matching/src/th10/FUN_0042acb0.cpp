// 0042ACB0: FUN_0042acb0
// Original size: 288 bytes, actual code: 75 instructions

extern "C" __declspec(naked) void FUN_0042acb0(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        push  edi
        xor  eax,eax
        mov  ecx,0x10df
        mov  edi,ebp
        rep stosd
        xor  edx,edx
        mov  WORD PTR [ebp+0x0],0x5243
        mov  WORD PTR [ebp+0x2],dx
        mov  DWORD PTR [ebp+0x8],0x437c
        lea  eax,[ebp+0x14]
        mov  esi,0x5
        mov  edi,edi
    loc_0042ACE0:
        mov  ecx,0xf4240
        jmp loc_0042ACF0
        nop
        mov  edi,edi
    loc_0042ACF0:
        mov  DWORD PTR [eax-0x4],ecx
        mov  BYTE PTR [eax],0x1
        mov  ebx,DWORD PTR ds:0x46e858
        lea  edi,[eax+0x2]
        mov  DWORD PTR [edi],ebx
        mov  ebx,DWORD PTR ds:0x46e85c
        mov  DWORD PTR [edi+0x4],ebx
        mov  bl,BYTE PTR ds:0x46e860
        mov  DWORD PTR [eax+0xc],edx
        mov  BYTE PTR [eax+0x1],dl
        sub  ecx,0x186a0
        add  eax,0x18
        cmp  ecx,edx
        mov  BYTE PTR [edi+0x8],bl
        jg loc_0042ACF0
        dec  esi
        jne loc_0042ACE0
        xor  esi,esi
        mov  edi,0x4743c0
        mov  edx,0x3
        mov  ebx,0x4743c2
        dec  edi
        mov  ecx,0x1
        lea  eax,[ebp+0x628]
        sub  ebx,edx
        jmp loc_0042AD50
        lea  ebx,[ebx+0x0]
    loc_0042AD50:
        mov  DWORD PTR [eax-0x4],esi
        movsx ebp,BYTE PTR [ecx+edi*1]
        mov  DWORD PTR [eax],ebp
        mov  DWORD PTR [eax+0x8c],ecx
        movsx ebp,BYTE PTR [ecx+0x4743c0]
        mov  DWORD PTR [eax+0x90],ebp
        lea  ebp,[edx-0x1]
        mov  DWORD PTR [eax+0x11c],ebp
        movsx ebp,BYTE PTR [edx+ebx*1]
        mov  DWORD PTR [eax+0x120],ebp
        mov  DWORD PTR [eax+0x1ac],edx
        movsx ebp,BYTE PTR [edx+0x4743c0]
        mov  DWORD PTR [eax+0x1b0],ebp
        lea  ebp,[esi+0x4]
        mov  DWORD PTR [eax+0x23c],ebp
        movsx ebp,BYTE PTR [esi+0x4743c4]
        mov  DWORD PTR [eax+0x240],ebp
        add  ecx,0x5
        add  esi,0x5
        add  edx,0x5
        add  eax,0x2d0
        cmp  ecx,0x6f
        jl loc_0042AD50
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x4
    }
}
