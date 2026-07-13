// 00421FA0: FUN_00421fa0
// Original size: 320 bytes, actual code: 101 instructions
extern "C" void FID_conflict:__time32(void);

extern "C" __declspec(naked) void FUN_00421fa0(void) {
    __asm {
        mov  eax,ds:0x474c74
        mov  edx,DWORD PTR ds:0x474c44
        push  ebx
        push  esi
        mov  ecx,eax
        xor  esi,esi
        imul  ecx,ecx,0xf0
        lea  ecx,[ecx+edi*1+0x10]
        jmp loc_00421FC0
        nop
    loc_00421FC0:
        cmp  DWORD PTR [ecx],edx
        jle loc_00421FD3
        inc  esi
        add  ecx,0x18
        cmp  esi,0xa
        jl loc_00421FC0
        pop  esi
        or   eax,0xffffffff
        pop  ebx
        ret
    loc_00421FD3:
        cmp  esi,0xa
        jl loc_00421FDE
        pop  esi
        or   eax,0xffffffff
        pop  ebx
        ret
    loc_00421FDE:
        mov  ecx,0x9
        cmp  esi,ecx
        jge loc_0042202B
    loc_00421FE7:
        lea  edx,[eax+eax*4]
        lea  eax,[ecx+edx*2]
        lea  eax,[eax+eax*2]
        lea  eax,[edi+eax*8]
        lea  edx,[eax-0x8]
        mov  ebx,DWORD PTR [edx]
        add  eax,0x10
        mov  DWORD PTR [eax],ebx
        mov  ebx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [eax+0x4],ebx
        mov  ebx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [eax+0x8],ebx
        mov  ebx,DWORD PTR [edx+0xc]
        mov  DWORD PTR [eax+0xc],ebx
        mov  ebx,DWORD PTR [edx+0x10]
        mov  DWORD PTR [eax+0x10],ebx
        mov  edx,DWORD PTR [edx+0x14]
        dec  ecx
        cmp  ecx,esi
        mov  DWORD PTR [eax+0x14],edx
        mov  eax,ds:0x474c74
        jg loc_00421FE7
        mov  edx,DWORD PTR ds:0x474c44
    loc_0042202B:
        lea  eax,[eax+eax*4]
        lea  eax,[esi+eax*2]
        lea  ecx,[eax+eax*2]
        mov  DWORD PTR [edi+ecx*8+0x10],edx
        mov  eax,ds:0x474c74
        mov  cl,BYTE PTR ds:0x474c90
        lea  edx,[eax+eax*4]
        lea  eax,[esi+edx*2]
        lea  eax,[eax+eax*2]
        mov  BYTE PTR [edi+eax*8+0x15],cl
        mov  eax,ds:0x474c74
        mov  cl,BYTE PTR ds:0x474c7c
        lea  edx,[eax+eax*4]
        lea  eax,[esi+edx*2]
        lea  eax,[eax+eax*2]
        mov  BYTE PTR [edi+eax*8+0x14],cl
        mov  eax,ds:0x474c74
        lea  edx,[eax+eax*4]
        lea  eax,[esi+edx*2]
        lea  eax,[eax+eax*2]
        lea  ecx,[edi+eax*8+0x20]
        push  ecx
        call FID_conflict:__time32
        mov  eax,ds:0x474c74
        lea  edx,[eax+eax*4]
        lea  eax,[esi+edx*2]
        mov  edx,DWORD PTR ds:0x46e354
        lea  eax,[eax+eax*2]
        lea  ecx,[edi+eax*8+0x16]
        mov  DWORD PTR [ecx],edx
        mov  eax,ds:0x46e358
        mov  DWORD PTR [ecx+0x4],eax
        mov  dl,BYTE PTR ds:0x46e35c
        mov  eax,ds:0x477708
        mov  BYTE PTR [ecx+0x8],dl
        fld  QWORD PTR [eax+0x24]
        fdiv  QWORD PTR [eax+0x2c]
        mov  eax,ds:0x474c74
        lea  eax,[eax+eax*4]
        lea  eax,[esi+eax*2]
        add  esp,0x4
        lea  ecx,[eax+eax*2]
        mov  eax,esi
        pop  esi
        pop  ebx
        fmul  DWORD PTR ds:0x470b44
        fsubr DWORD PTR ds:0x470b44
        fstp  DWORD PTR [edi+ecx*8+0x24]
        ret
    }
}
