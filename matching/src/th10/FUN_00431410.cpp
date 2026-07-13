// 00431410: FUN_00431410
// Original size: 432 bytes, actual code: 101 instructions
extern "C" void FUN_00401630(void);

extern "C" __declspec(naked) void FUN_00431410(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x20]
        sub  esp,0xc
        cmp  eax,0x2
        jl loc_004315AA
        cmp  eax,0x3
        jg loc_004315AA
        mov  edx,DWORD PTR ds:0x4776e0
        push  esi
        mov  esi,0x1
        mov  DWORD PTR [edx+0x8988],esi
        cmp  DWORD PTR [edi+0x2b4],0xa
        mov  DWORD PTR [esp+0x4],0x42a00000
        mov  DWORD PTR [esp+0x8],0x42a00000
        mov  DWORD PTR [esp+0xc],0x0
        jge loc_00431465
        cmp  DWORD PTR [edi+0x20],0x3
        jne loc_00431595
    loc_00431465:
        mov  eax,ds:0x474c68
        test  eax,eax
        mov  DWORD PTR [esp+0x8],0x43580000
        mov  DWORD PTR [esp+0x4],0x43280000
        je loc_00431486
        mov  DWORD PTR [esp+0x4],0x43940000
    loc_00431486:
        push  ebx
        jmp loc_00431490
    loc_00431489:
        mov  eax,ds:0x474c68
        mov  edi,edi
    loc_00431490:
        mov  ebx,DWORD PTR [edi+0x24]
        lea  ecx,[esi-0x1]
        cmp  ebx,ecx
        mov  ecx,DWORD PTR ds:0x47783c
        jne loc_00431509
        mov  ebx,DWORD PTR ds:0x474c6c
        lea  ebx,[ebx+eax*2]
        add  ebx,eax
        mov  eax,ds:0x474c74
        imul  ebx,ebx,0x437c
        lea  eax,[eax+eax*2]
        lea  eax,[esi+eax*2]
        add  ebx,ecx
        cmp  BYTE PTR [ebx+eax*8+0x4e1],0x0
        je loc_004314FD
        cmp  DWORD PTR [edi+0x20],0x3
        jne loc_004314F1
        mov  eax,DWORD PTR [edi+0x2b4]
        and  eax,0x80000003
        jns loc_004314E0
        dec  eax
        or   eax,0xfffffffc
        inc  eax
    loc_004314E0:
        cmp  eax,0x2
        jl loc_004314F1
        mov  DWORD PTR [edx+0x8974],0xff000000
        jmp loc_00431513
    loc_004314F1:
        mov  DWORD PTR [edx+0x8974],0xffffff00
        jmp loc_00431513
    loc_004314FD:
        mov  DWORD PTR [edx+0x8974],0xffdfdfdf
        jmp loc_00431513
    loc_00431509:
        mov  DWORD PTR [edx+0x8974],0xff808080
    loc_00431513:
        mov  eax,ds:0x474c68
        mov  ebx,DWORD PTR ds:0x474c6c
        lea  ebx,[ebx+eax*2]
        add  ebx,eax
        mov  eax,ds:0x474c74
        imul  ebx,ebx,0x437c
        add  ebx,ecx
        lea  eax,[eax+eax*2]
        lea  eax,[esi+eax*2]
        mov  cl,BYTE PTR [ebx+eax*8+0x4e1]
        lea  eax,[ebx+eax*8]
        test  cl,cl
        mov  ecx,DWORD PTR [esi*4+0x47471c]
        lea  ebx,[esp+0x8]
        jne loc_00431560
        push  ecx
        push  0x46f008
        push  edx
        call FUN_00401630
        add  esp,0xc
        jmp loc_00431576
    loc_00431560:
        mov  eax,DWORD PTR [eax+0x4dc]
        push  eax
        push  ecx
        push  0x46effc
        push  edx
        call FUN_00401630
        add  esp,0x10
    loc_00431576:
        fld  DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR ds:0x4776e0
        fadd  DWORD PTR ds:0x470c0c
        inc  esi
        cmp  esi,0x7
        fstp  DWORD PTR [esp+0xc]
        jl loc_00431489
        pop  ebx
    loc_00431595:
        mov  DWORD PTR [edx+0x8974],0xffffffff
        mov  DWORD PTR [edx+0x8988],0x0
        pop  esi
    loc_004315AA:
        mov  eax,0x1
        add  esp,0xc
        ret
    }
}
