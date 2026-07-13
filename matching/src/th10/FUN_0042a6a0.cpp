// 0042A6A0: FUN_0042a6a0
// Original size: 512 bytes, actual code: 87 instructions
extern "C" void FUN_00418b80(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0042a6a0(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [ebx+0x10]
        test  eax,eax
        jne loc_0042A71E
        push  edi
        push  0x1c4
        call operator_new
        mov  edx,eax
        add  esp,0x4
        xor  eax,eax
        test  edx,edx
        je loc_0042A6C9
        mov  ecx,0x71
        mov  edi,edx
        rep stosd
        mov  eax,edx
    loc_0042A6C9:
        mov  ecx,DWORD PTR ds:0x474c7c
        mov  DWORD PTR [ebx+ecx*4+0x1c],eax
        mov  edx,DWORD PTR ds:0x474c7c
        mov  eax,DWORD PTR [ebx+edx*4+0x1c]
        mov  cx,WORD PTR ds:0x4918b0
        mov  WORD PTR [eax+0x2],cx
        mov  dx,WORD PTR ds:0x474c7c
        mov  DWORD PTR ds:0x4918b4,0x0
        mov  ecx,DWORD PTR [eax+0x1c0]
        mov  WORD PTR [eax],dx
        mov  edi,DWORD PTR ds:0x491fc4
        mov  edx,DWORD PTR [eax+0x1c0]
        xor  ecx,edi
        and  ecx,0x1
        xor  edx,ecx
        mov  DWORD PTR [eax+0x1c0],edx
        pop  edi
        pop  ecx
        ret
    loc_0042A71E:
        cmp  eax,0x1
        jne loc_0042A802
        mov  eax,ds:0x474c7c
        lea  edx,[eax+eax*8]
        mov  ecx,DWORD PTR [ebx+edx*4+0xa0]
        lea  eax,[ebx+edx*4+0xa0]
        mov  edx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0xc],edx
        mov  DWORD PTR [eax+0x14],0x0
        push  esi
        mov  esi,DWORD PTR [eax+0x10]
        mov  ax,WORD PTR [esi+0x2]
        mov  ds:0x4918b0,ax
        mov  DWORD PTR ds:0x4918b4,0x0
        mov  ecx,DWORD PTR [esi+0xc]
        mov  DWORD PTR ds:0x474c44,ecx
        mov  dx,WORD PTR [esi+0x10]
        mov  WORD PTR ds:0x474c48,dx
        mov  eax,DWORD PTR [esi+0x14]
        lea  eax,[eax+eax*4]
        shl  eax,1
        push  eax
        mov  ecx,0x474c40
        call FUN_00418b80
        test  BYTE PTR ds:0x474c64,0x1
        mov  eax,DWORD PTR [esi+0x18]
        mov  DWORD PTR [esp+0x4],eax
        jne loc_0042A7B5
        mov  ecx,DWORD PTR ds:0x474c64
        or   ecx,0x1
        mov  DWORD PTR ds:0x474c60,0x476f78
        mov  DWORD PTR ds:0x474c64,ecx
    loc_0042A7B5:
        fild  DWORD PTR [esp+0x4]
        mov  ds:0x474c58,eax
        dec  eax
        mov  ds:0x474c54,eax
        fstp  DWORD PTR ds:0x474c5c
        mov  ecx,DWORD PTR [esi+0x1c]
        mov  DWORD PTR ds:0x474c70,ecx
        mov  edx,DWORD PTR [esi+0x20]
        mov  DWORD PTR ds:0x474c98,edx
        mov  eax,DWORD PTR [esi+0x1b4]
        mov  ds:0x474c90,eax
        mov  eax,ds:0x474c7c
        lea  ecx,[eax+eax*8]
        mov  edx,DWORD PTR [ebx+ecx*4+0xb0]
        mov  eax,DWORD PTR [edx+0x1b8]
        mov  ds:0x474c9c,eax
        pop  esi
    loc_0042A802:
        pop  ecx
        ret
    }
}
