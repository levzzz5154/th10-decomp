// 00428F60: FUN_00428f60
// Original size: 1344 bytes, actual code: 389 instructions
extern "C" void FUN_00418b80(void);
extern "C" void FUN_00418c40(void);
extern "C" void FUN_0042a200(void);
extern "C" void FUN_0042a930(void);
extern "C" void FUN_0042aa50(void);
extern "C" void FUN_0042ab20(void);
extern "C" void FUN_00449ae0(void);
extern "C" void FUN_00449b70(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00428f60(void) {
    __asm {
        push  ebp
        xor  ebp,ebp
        cmp  eax,ebp
        push  esi
        push  edi
        mov  DWORD PTR [ebx+0x10],eax
        jne loc_00429245
        mov  eax,ds:0x474c7c
        mov  ecx,ebx
        mov  DWORD PTR ds:0x477838,ebx
        call FUN_0042ab20
        mov  esi,DWORD PTR ds:0x474c7c
        push  ebx
        call FUN_0042aa50
        push  0x24
        mov  DWORD PTR [ebx+0x9c],eax
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_00428FD5
        xor  ecx,ecx
        mov  edx,eax
        mov  DWORD PTR [edx],ecx
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],ecx
        mov  DWORD PTR [edx+0xc],ecx
        mov  DWORD PTR [edx+0x10],ecx
        mov  DWORD PTR [edx+0x14],ecx
        mov  DWORD PTR [edx+0x18],ecx
        mov  DWORD PTR [edx+0x1c],ecx
        mov  DWORD PTR [edx+0x20],ecx
        mov  DWORD PTR [eax],0x72303174
        mov  WORD PTR [eax+0x4],0x5
        mov  DWORD PTR [eax+0x10],0x100
        jmp loc_00428FD7
    loc_00428FD5:
        xor  eax,eax
    loc_00428FD7:
        push  0x64
        mov  DWORD PTR [ebx+0x14],eax
        call operator_new
        mov  esi,eax
        add  esp,0x4
        cmp  esi,ebp
        je loc_00428FFF
        lea  edx,[esi+0x14]
        call FUN_00418c40
        mov  ecx,0x19
        xor  eax,eax
        mov  edi,esi
        rep stosd
        jmp loc_00429001
    loc_00428FFF:
        xor  esi,esi
    loc_00429001:
        push  0x1c4
        mov  DWORD PTR [ebx+0x18],esi
        call operator_new
        mov  edx,eax
        add  esp,0x4
        cmp  edx,ebp
        je loc_00429024
        mov  ecx,0x71
        xor  eax,eax
        mov  edi,edx
        rep stosd
        jmp loc_00429026
    loc_00429024:
        xor  edx,edx
    loc_00429026:
        mov  eax,ds:0x474c7c
        mov  DWORD PTR [ebx+eax*4+0x1c],edx
        mov  ecx,DWORD PTR ds:0x474c7c
        mov  eax,DWORD PTR [ebx+ecx*4+0x1c]
        mov  edx,DWORD PTR [ebx+0x18]
        mov  ecx,DWORD PTR ds:0x474c68
        mov  DWORD PTR [edx+0x50],ecx
        mov  edx,DWORD PTR [ebx+0x18]
        mov  ecx,DWORD PTR ds:0x474c6c
        mov  DWORD PTR [edx+0x54],ecx
        mov  ecx,DWORD PTR ds:0x474c74
        mov  edx,DWORD PTR [ebx+0x18]
        mov  DWORD PTR [edx+0x58],ecx
        mov  ecx,DWORD PTR ds:0x477810
        cmp  ecx,ebp
        je loc_00429077
        mov  edi,DWORD PTR [ebx+0x18]
        lea  esi,[ecx+0x24]
        add  edi,0x14
        mov  ecx,0xd
        rep movsd
    loc_00429077:
        mov  dx,WORD PTR ds:0x474c7c
        mov  WORD PTR [eax],dx
        mov  cx,WORD PTR ds:0x4918b0
        mov  WORD PTR [eax+0x2],cx
        mov  ecx,DWORD PTR ds:0x491fc4
        mov  DWORD PTR ds:0x4918b4,ebp
        mov  edx,DWORD PTR [eax+0x1c0]
        mov  esi,DWORD PTR [eax+0x1c0]
        xor  edx,ecx
        and  edx,0x1
        xor  esi,edx
        mov  DWORD PTR [eax+0x1c0],esi
        cmp  DWORD PTR ds:0x491fc4,ebp
        je loc_004290BF
        mov  DWORD PTR [eax+0x24],ebp
        mov  DWORD PTR [eax+0x28],ebp
    loc_004290BF:
        mov  ecx,DWORD PTR ds:0x474c44
        mov  DWORD PTR [eax+0xc],ecx
        mov  dx,WORD PTR ds:0x474c48
        mov  WORD PTR [eax+0x10],dx
        mov  ecx,DWORD PTR ds:0x474c4c
        mov  DWORD PTR [eax+0x14],ecx
        mov  edx,DWORD PTR ds:0x474c58
        mov  DWORD PTR [eax+0x18],edx
        mov  ecx,DWORD PTR ds:0x474c70
        mov  DWORD PTR [eax+0x1c],ecx
        mov  edx,DWORD PTR ds:0x474c98
        mov  DWORD PTR [eax+0x20],edx
        mov  ecx,DWORD PTR ds:0x474c90
        mov  DWORD PTR [eax+0x1b4],ecx
        mov  edx,DWORD PTR [ebx+0x18]
        mov  eax,ds:0x474c90
        push  0x24
        mov  DWORD PTR [edx+0x60],eax
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_0042913D
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_0042913F
    loc_0042913D:
        xor  esi,esi
    loc_0042913F:
        mov  ecx,DWORD PTR [esi+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        and  ecx,0xfffffffd
        or   ecx,0x1
        push  edx
        mov  edi,0xb
        mov  DWORD PTR [esi+0x8],0x42a3d0
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],ecx
        call FUN_00449ae0
        push  0x24
        mov  DWORD PTR [ebx+0x8],esi
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_0042919E
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_004291A0
    loc_0042919E:
        xor  esi,esi
    loc_004291A0:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR ds:0x491be4
        and  eax,0xfffffffd
        or   eax,0x1
        push  ecx
        mov  edi,0x1b
        mov  DWORD PTR [esi+0x8],0x42a3e0
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449ae0
        push  0x24
        mov  DWORD PTR [ebx+0x1cc],esi
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_00429202
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_00429204
    loc_00429202:
        xor  esi,esi
    loc_00429204:
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        or   edx,0x1
        push  eax
        mov  edi,0x5
        mov  DWORD PTR [esi+0x8],0x42a430
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449b70
        mov  DWORD PTR [ebx+0xc],esi
        mov  ecx,DWORD PTR ds:0x474c7c
        mov  DWORD PTR [ebx+0x1d0],ecx
    loc_0042923F:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        ret
    loc_00429245:
        cmp  eax,0x1
        jne loc_00429480
        push  ecx
        mov  esi,ebx
        mov  DWORD PTR ds:0x477838,ebx
        call FUN_0042a200
        test  eax,eax
        jne loc_00429499
        mov  esi,DWORD PTR [ebx+0x18]
        mov  edi,DWORD PTR ds:0x477810
        add  esi,0x14
        add  edi,0x24
        mov  ecx,0xd
        rep movsd
        mov  eax,ds:0x474c7c
        lea  edx,[eax+eax*8]
        mov  ecx,DWORD PTR [ebx+edx*4+0xa0]
        mov  esi,DWORD PTR [ebx+edx*4+0xb0]
        mov  DWORD PTR [ebx+edx*4+0xa4],ecx
        mov  DWORD PTR [ebx+edx*4+0xb4],ebp
        lea  eax,[ebx+edx*4+0xa0]
        mov  edx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [eax+0xc],edx
        mov  eax,DWORD PTR [ebx+0x18]
        mov  ecx,DWORD PTR [eax+0x50]
        mov  DWORD PTR ds:0x474c68,ecx
        mov  edx,DWORD PTR [ebx+0x18]
        mov  eax,DWORD PTR [edx+0x54]
        mov  ds:0x474c6c,eax
        mov  ecx,DWORD PTR [ebx+0x18]
        mov  edx,DWORD PTR [ecx+0x58]
        mov  DWORD PTR ds:0x474c74,edx
        mov  ax,WORD PTR [esi+0x2]
        mov  ds:0x4918b0,ax
        mov  DWORD PTR ds:0x4918b4,ebp
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
        mov  ecx,DWORD PTR [esi+0x18]
        push  ecx
        mov  eax,0x474c40
        call FUN_0042a930
        mov  edx,DWORD PTR [esi+0x1c]
        mov  DWORD PTR ds:0x474c70,edx
        mov  eax,DWORD PTR [esi+0x20]
        mov  ds:0x474c98,eax
        mov  ecx,DWORD PTR [esi+0x1b4]
        mov  eax,ds:0x474c7c
        mov  DWORD PTR ds:0x474c90,ecx
        lea  edx,[eax+eax*8]
        mov  eax,DWORD PTR [ebx+edx*4+0xb0]
        mov  ecx,DWORD PTR [eax+0x1b8]
        push  0x24
        mov  DWORD PTR ds:0x474c9c,ecx
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_0042937A
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_0042937C
    loc_0042937A:
        xor  esi,esi
    loc_0042937C:
        mov  edx,DWORD PTR [esi+0x4]
        mov  eax,ds:0x491be4
        and  edx,0xfffffffd
        or   edx,0x1
        push  eax
        mov  edi,0xb
        mov  DWORD PTR [esi+0x8],0x42a3d0
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],edx
        call FUN_00449ae0
        push  0x24
        mov  DWORD PTR [ebx+0x8],esi
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_004293DA
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_004293DC
    loc_004293DA:
        xor  esi,esi
    loc_004293DC:
        mov  ecx,DWORD PTR [esi+0x4]
        mov  edx,DWORD PTR ds:0x491be4
        and  ecx,0xfffffffd
        or   ecx,0x1
        push  edx
        mov  edi,0x1b
        mov  DWORD PTR [esi+0x8],0x42a3e0
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],ecx
        call FUN_00449ae0
        push  0x24
        mov  DWORD PTR [ebx+0x1cc],esi
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_0042943E
        mov  ecx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [eax+0x8],ebp
        mov  DWORD PTR [eax+0xc],ebp
        mov  DWORD PTR [eax+0x10],ebp
        mov  DWORD PTR [eax],ebp
        and  ecx,0xfffffffe
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x14],eax
        mov  DWORD PTR [eax+0x18],ebp
        mov  DWORD PTR [eax+0x1c],ebp
        mov  esi,eax
        jmp loc_00429440
    loc_0042943E:
        xor  esi,esi
    loc_00429440:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR ds:0x491be4
        and  eax,0xfffffffd
        or   eax,0x1
        push  ecx
        mov  edi,0x5
        mov  DWORD PTR [esi+0x8],0x42a430
        mov  DWORD PTR [esi+0xc],ebp
        mov  DWORD PTR [esi+0x10],ebp
        mov  DWORD PTR [esi+0x20],ebx
        mov  DWORD PTR [esi+0x4],eax
        call FUN_00449b70
        pop  edi
        mov  DWORD PTR [ebx+0xc],esi
        pop  esi
        mov  DWORD PTR [ebx+0x1d0],0xffffffff
        xor  eax,eax
        pop  ebp
        ret
    loc_00429480:
        cmp  eax,0x2
        jne loc_0042923F
        push  ecx
        mov  esi,ebx
        call FUN_0042a200
        test  eax,eax
        je loc_0042923F
    loc_00429499:
        pop  edi
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        ret
    }
}
