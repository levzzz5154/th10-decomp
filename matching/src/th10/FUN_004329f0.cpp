// 004329F0: FUN_004329f0
// Original size: 704 bytes, actual code: 192 instructions
extern "C" void FUN_00401630(void);
extern "C" void _localtime(void);

extern "C" __declspec(naked) void FUN_004329f0(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        and  esp,0xfffffff8
        sub  esp,0x20
        mov  eax,DWORD PTR [edi+0x20]
        push  ebx
        sub  eax,0x2
        push  esi
        mov  eax,0x1
        jne loc_00432C9B
        mov  esi,DWORD PTR [edi+0xfc]
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [ecx+0x8988],eax
        mov  edx,DWORD PTR [edi+0x1d4]
        test  edx,edx
        mov  DWORD PTR [esp+0x1c],0x42400000
        mov  DWORD PTR [esp+0x20],0x43200000
        mov  DWORD PTR [esp+0x24],0x0
        mov  DWORD PTR [esp+0x18],esi
        jne loc_00432B8D
        mov  DWORD PTR [esp+0xc],eax
        imul  esi,esi,0xf0
        mov  eax,0xff
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x14],0xa
        jmp loc_00432A70
    loc_00432A65:
        mov  eax,DWORD PTR [esp+0x10]
        nop
    loc_00432A70:
        mov  edx,eax
        shl  edx,0x8
        or   edx,eax
        shl  edx,0x8
        or   edx,0xff0000ff
        mov  DWORD PTR [ecx+0x8974],edx
        mov  eax,DWORD PTR [edi+0x24]
        mov  edx,DWORD PTR ds:0x47783c
        imul  eax,eax,0x437c
        lea  ebx,[esi+eax*1]
        cmp  DWORD PTR [ebx+edx*1+0x28],0x0
        je loc_00432B19
        lea  eax,[eax+edx*1+0x8]
        lea  eax,[esi+eax*1+0x20]
        push  eax
        call _localtime
        mov  ecx,DWORD PTR [edi+0x24]
        mov  edx,DWORD PTR ds:0x47783c
        imul  ecx,ecx,0x437c
        add  ecx,esi
        add  ecx,edx
        movsx edx,BYTE PTR [ecx+0x1c]
        fld  DWORD PTR [ecx+0x2c]
        mov  edx,DWORD PTR [edx*4+0x47471c]
        push  ecx
        add  ecx,0x1e
        lea  ebx,[esp+0x24]
        fstp  QWORD PTR [esp]
        push  edx
        mov  edx,DWORD PTR [eax+0x4]
        push  edx
        mov  edx,DWORD PTR [eax+0x8]
        push  edx
        mov  edx,DWORD PTR [eax+0xc]
        push  edx
        mov  edx,DWORD PTR [eax+0x10]
        mov  eax,DWORD PTR [eax+0x14]
        inc  edx
        push  edx
        movsx edx,BYTE PTR [ecx-0x1]
        add  eax,0x76c
        push  eax
        mov  eax,DWORD PTR [ecx-0x6]
        push  edx
        mov  edx,DWORD PTR ds:0x4776e0
        push  eax
        push  ecx
        mov  ecx,DWORD PTR [esp+0x38]
        push  ecx
        push  0x46ee84
        push  edx
        call FUN_00401630
        add  esp,0x38
        jmp loc_00432B53
    loc_00432B19:
        mov  eax,DWORD PTR [edi+0x24]
        imul  eax,eax,0x437c
        add  eax,esi
        add  eax,edx
        movsx edx,BYTE PTR [eax+0x1d]
        fld  DWORD PTR [eax+0x2c]
        sub  esp,0x8
        add  eax,0x1e
        lea  ebx,[esp+0x24]
        fstp  QWORD PTR [esp]
        push  edx
        mov  edx,DWORD PTR [eax-0x6]
        push  edx
        push  eax
        mov  eax,DWORD PTR [esp+0x20]
        push  eax
        push  0x46ee50
        push  ecx
        call FUN_00401630
        add  esp,0x20
    loc_00432B53:
        fld  DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esp+0xc]
        fadd  DWORD PTR ds:0x470c0c
        mov  eax,DWORD PTR [esp+0x14]
        sub  edx,0x10
        add  esi,0x18
        fstp  DWORD PTR [esp+0x20]
        inc  ecx
        dec  eax
        mov  DWORD PTR [esp+0xc],ecx
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [esp+0x10],edx
        mov  DWORD PTR [esp+0x14],eax
        jne loc_00432A65
    loc_00432B8D:
        mov  eax,ds:0x47783c
        or   esi,0xffffffff
        mov  DWORD PTR [ecx+0x8974],esi
        mov  edx,DWORD PTR [edi+0x24]
        imul  edx,edx,0x437c
        mov  edx,DWORD PTR [edx+eax*1+0x4c8]
        push  edx
        push  0x46ee48
        push  ecx
        lea  ebx,[esp+0x28]
        mov  DWORD PTR [esp+0x28],0x43a40000
        mov  DWORD PTR [esp+0x2c],0x43bd0000
        call FUN_00401630
        mov  eax,DWORD PTR [edi+0x24]
        mov  ecx,DWORD PTR ds:0x47783c
        imul  eax,eax,0x437c
        mov  ecx,DWORD PTR [eax+ecx*1+0x4cc]
        mov  eax,0x88888889
        imul  ecx
        add  edx,ecx
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cdq
        mov  ebx,0x3c
        idiv  ebx
        mov  eax,0x91a2b3c5
        mov  DWORD PTR [esp+0x2c],0x43c60000
        push  edx
        imul  ecx
        add  edx,ecx
        sar  edx,0xb
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cdq
        idiv  ebx
        mov  eax,0x9b583739
        lea  ebx,[esp+0x2c]
        push  edx
        imul  ecx
        add  edx,ecx
        mov  ecx,DWORD PTR ds:0x4776e0
        sar  edx,0x11
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  eax
        push  0x46ee38
        push  ecx
        call FUN_00401630
        mov  edx,DWORD PTR [edi+0x24]
        mov  ebx,DWORD PTR [esp+0x38]
        imul  edx,edx,0x10df
        mov  eax,ds:0x47783c
        add  edx,ebx
        mov  ecx,DWORD PTR [eax+edx*4+0x4d0]
        mov  edx,DWORD PTR ds:0x4776e0
        push  ecx
        push  0x46ee48
        push  edx
        lea  ebx,[esp+0x48]
        mov  DWORD PTR [esp+0x4c],0x43cf0000
        call FUN_00401630
        mov  eax,ds:0x4776e0
        mov  DWORD PTR [eax+0x8974],esi
        mov  DWORD PTR [eax+0x8988],0x0
        add  esp,0x2c
        mov  eax,0x1
    loc_00432C9B:
        pop  esi
        pop  ebx
        mov  esp,ebp
        pop  ebp
        ret
    }
}
