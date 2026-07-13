// 004224C0: FUN_004224c0
// Original size: 416 bytes, actual code: 115 instructions
extern "C" void FUN_00401630(void);

extern "C" __declspec(naked) void FUN_004224c0(void) {
    __asm {
        push  ecx
        mov  eax,ds:0x4746d8
        lea  edx,[eax+0x1]
        nop
    loc_004224D0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_004224D0
        mov  ecx,DWORD PTR ds:0x4776e0
        push  ebx
        push  esi
        mov  esi,DWORD PTR [esp+0x10]
        push  edi
        sub  eax,edx
        mov  edi,eax
        lea  eax,[esi+0x2b4]
        push  eax
        push  0x46e1c8
        push  ecx
        lea  ebx,[esp+0x24]
        call FUN_00401630
        mov  eax,DWORD PTR [esi+0x1e0]
        lea  edx,[eax+eax*8]
        mov  DWORD PTR [esp+0x18],edx
        fild  DWORD PTR [esp+0x18]
        add  esp,0xc
        cmp  eax,0x8
        fadd  DWORD PTR [esp+0x18]
        fstp  DWORD PTR [esp+0x18]
        jne loc_0042252D
        fld  DWORD PTR [esp+0x18]
        fsub  DWORD PTR ds:0x470c10
        fstp  DWORD PTR [esp+0x18]
    loc_0042252D:
        mov  eax,ds:0x4776e0
        push  0x46e1c4
        push  eax
        lea  ebx,[esp+0x20]
        mov  DWORD PTR [eax+0x8974],0xffffff00
        call FUN_00401630
        mov  eax,ds:0x4776e0
        or   ecx,0xffffffff
        add  esp,0x8
        xor  esi,esi
        test  edi,edi
        mov  DWORD PTR [eax+0x8974],ecx
        mov  DWORD PTR [esp+0x18],0x42e00000
        mov  DWORD PTR [esp+0x1c],0x43a00000
        mov  DWORD PTR [esp+0x20],0x0
        jle loc_00422647
        push  ebp
        lea  ebp,[edi-0x3]
        jmp loc_00422590
    loc_00422584:
        mov  eax,ds:0x4776e0
        nop
    loc_00422590:
        mov  edx,DWORD PTR [esp+0x18]
        mov  ebx,DWORD PTR [edx+0xfc]
        xor  ecx,ecx
        cmp  ebx,esi
        setne cl
        dec  ecx
        and  ecx,0x7f7e80
        add  ecx,0xff808080
        cmp  esi,ebp
        mov  DWORD PTR [eax+0x8974],ecx
        jge loc_004225C5
        mov  ecx,DWORD PTR ds:0x4746d8
        movsx edx,BYTE PTR [ecx+esi*1]
        push  edx
        jmp loc_004225DE
    loc_004225C5:
        jne loc_004225CE
        mov  ecx,0x81
        jmp loc_004225DD
    loc_004225CE:
        lea  ecx,[edi-0x2]
        xor  edx,edx
        cmp  esi,ecx
        setne dl
        add  edx,0x7f
        mov  ecx,edx
    loc_004225DD:
        push  ecx
    loc_004225DE:
        push  0x46e1c0
        lea  ebx,[esp+0x24]
        push  eax
        call FUN_00401630
        xor  edx,edx
        mov  eax,esi
        mov  ecx,0xd
        div  ecx
        add  esp,0xc
        cmp  edx,0xc
        jne loc_00422618
        fld  DWORD PTR [esp+0x20]
        mov  DWORD PTR [esp+0x1c],0x42e00000
        fadd  DWORD PTR ds:0x470b48
        fstp  DWORD PTR [esp+0x20]
        jmp loc_00422626
    loc_00422618:
        fld  DWORD PTR [esp+0x1c]
        fadd  DWORD PTR ds:0x470c0c
        fstp  DWORD PTR [esp+0x1c]
    loc_00422626:
        inc  esi
        cmp  esi,edi
        jl loc_00422584
        mov  edx,DWORD PTR ds:0x4776e0
        pop  ebp
        pop  edi
        pop  esi
        mov  DWORD PTR [edx+0x8974],0xffffffff
        pop  ebx
        pop  ecx
        ret  0x10
    loc_00422647:
        pop  edi
        pop  esi
        mov  DWORD PTR [eax+0x8974],ecx
        pop  ebx
        pop  ecx
        ret  0x10
    }
}
