// 0042E5A0: FUN_0042e5a0
// Original size: 4000 bytes, actual code: 1204 instructions
extern "C" void FUN_0043e460(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0042e5a0(void) {
    __asm {
        movsx eax,BYTE PTR ds:0x491d68
        push  ebx
        push  ebp
        push  esi
        xor  ebx,ebx
        push  ebx
        mov  ds:0x497854,eax
        push  0x8
        mov  edx,0x46ece8
        mov  eax,0x492590
        call FUN_0043e460
        movsx eax,BYTE PTR ds:0x491d69
        cmp  eax,ebx
        mov  ds:0x497858,eax
        je loc_0042E60F
        fild  DWORD PTR ds:0x497854
        fmul  DWORD PTR ds:0x470b00
        fsubr DWORD PTR ds:0x470afc
        fld  st(0)
        fmulp st(1),st
        fld  st(0)
        fmul  st,st(1)
        fsubr DWORD PTR ds:0x470afc
        fmul  DWORD PTR ds:0x470b80
        call FUN_00463b2c
        fstp  st(0)
        mov  ecx,0xffffec78
        sub  ecx,eax
        mov  DWORD PTR ds:0x49785c,ecx
        jmp loc_0042E619
    loc_0042E60F:
        mov  DWORD PTR ds:0x49785c,0xffffd8f0
    loc_0042E619:
        mov  edx,DWORD PTR [edi+0x2c8]
        mov  esi,DWORD PTR ds:0x491c10
        push  edx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E637
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E637:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x25
        je loc_0042E666
        jmp loc_0042E650
        nop
        nop
    loc_0042E650:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED23
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E650
    loc_0042E666:
        xor  eax,eax
    loc_0042E668:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E69D
        movsx edx,BYTE PTR ds:0x491d68
        mov  eax,0x51eb851f
        imul  edx
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042E69D:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E6B5
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E6B5:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x26
        je loc_0042E6D7
    loc_0042E6C1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED2C
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E6C1
    loc_0042E6D7:
        xor  eax,eax
    loc_0042E6D9:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E717
        movsx edx,BYTE PTR ds:0x491d68
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042E717:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E72F
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E72F:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E756
        mov  ecx,0x27
        jmp loc_0042E740
        nop
    loc_0042E740:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED35
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E740
    loc_0042E756:
        xor  eax,eax
    loc_0042E758:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E785
        movsx eax,BYTE PTR ds:0x491d68
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
    loc_0042E785:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E79D
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E79D:
        add  eax,0x10
        cmp  eax,ebx
        mov  ebp,0x29
        je loc_0042E7C6
        nop
    loc_0042E7B0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],bp
        je loc_0042ED3E
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E7B0
    loc_0042E7C6:
        xor  eax,eax
    loc_0042E7C8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E7FD
        movsx edx,BYTE PTR ds:0x491d68
        mov  eax,0x51eb851f
        imul  edx
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x3d]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042E7FD:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E815
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E815:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x2a
        je loc_0042E837
    loc_0042E821:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED47
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E821
    loc_0042E837:
        xor  eax,eax
    loc_0042E839:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E87C
        movsx edx,BYTE PTR ds:0x491d68
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x3d
        call FUN_0043e5a0
        mov  ebp,0x29
    loc_0042E87C:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E894
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E894:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042E8B6
        mov  ecx,0x2b
    loc_0042E8A0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED50
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E8A0
    loc_0042E8B6:
        xor  eax,eax
    loc_0042E8B8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E8EA
        movsx eax,BYTE PTR ds:0x491d68
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x3d
        call FUN_0043e5a0
        mov  ebp,0x29
    loc_0042E8EA:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E902
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E902:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x2d
        je loc_0042E926
        mov  edi,edi
    loc_0042E910:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED59
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E910
    loc_0042E926:
        xor  eax,eax
    loc_0042E928:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E95D
        movsx edx,BYTE PTR ds:0x491d69
        mov  eax,0x51eb851f
        imul  edx
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x33]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042E95D:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E975
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E975:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x2e
        je loc_0042E997
    loc_0042E981:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED62
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042E981
    loc_0042E997:
        xor  eax,eax
    loc_0042E999:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042E9DC
        movsx edx,BYTE PTR ds:0x491d69
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
        mov  ebp,0x29
    loc_0042E9DC:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042E9F4
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042E9F4:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EA16
        mov  ecx,0x2f
    loc_0042EA00:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED6B
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EA00
    loc_0042EA16:
        xor  eax,eax
    loc_0042EA18:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042EA4A
        movsx eax,BYTE PTR ds:0x491d69
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x33
        call FUN_0043e5a0
        mov  ebp,0x29
    loc_0042EA4A:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EA62
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EA62:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x31
        je loc_0042EA86
        mov  edi,edi
    loc_0042EA70:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED74
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EA70
    loc_0042EA86:
        xor  eax,eax
    loc_0042EA88:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042EABD
        movsx edx,BYTE PTR ds:0x491d69
        mov  eax,0x51eb851f
        imul  edx
        sar  edx,0x5
        mov  eax,edx
        shr  eax,0x1f
        lea  edx,[edx+eax*1+0x3d]
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        call FUN_0043e5a0
    loc_0042EABD:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EAD5
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EAD5:
        add  eax,0x10
        cmp  eax,ebx
        mov  ecx,0x32
        je loc_0042EAF7
    loc_0042EAE1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED7D
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EAE1
    loc_0042EAF7:
        xor  eax,eax
    loc_0042EAF9:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042EB3C
        movsx edx,BYTE PTR ds:0x491d69
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x2
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x3d
        call FUN_0043e5a0
        mov  ebp,0x29
    loc_0042EB3C:
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EB54
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EB54:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EB76
        mov  ecx,0x33
    loc_0042EB60:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED86
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EB60
    loc_0042EB76:
        xor  eax,eax
    loc_0042EB78:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,eax
        cmp  ecx,ebx
        je loc_0042EBAA
        movsx eax,BYTE PTR ds:0x491d69
        cdq
        mov  ebp,0xa
        idiv  ebp
        mov  eax,ecx
        mov  ecx,DWORD PTR [ecx+0x308]
        add  edx,0x3d
        call FUN_0043e5a0
        mov  ebp,0x29
    loc_0042EBAA:
        mov  al,ds:0x491d68
        cmp  al,0xa
        mov  ecx,DWORD PTR [edi+0x2c8]
        mov  edx,esi
        push  ecx
        jge loc_0042EDB3
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EBCF
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EBCF:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EBF6
        mov  ecx,0x25
        jmp loc_0042EBE0
        nop
    loc_0042EBE0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED8F
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EBE0
    loc_0042EBF6:
        xor  eax,eax
    loc_0042EBF8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ecx,0xfffffffd
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EC28
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EC28:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EC56
        mov  ecx,0x26
        jmp loc_0042EC40
        nop
        nop
    loc_0042EC40:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042ED98
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EC40
    loc_0042EC56:
        xor  eax,eax
    loc_0042EC58:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ecx,0xfffffffd
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EC88
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EC88:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042ECA6
        nop
    loc_0042EC90:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],bp
        je loc_0042EDA1
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EC90
    loc_0042ECA6:
        xor  eax,eax
    loc_0042ECA8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042ECD8
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042ECD8:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042ED06
        mov  ecx,0x2a
        jmp loc_0042ECF0
        nop
        nop
    loc_0042ECF0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042EDAA
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042ECF0
    loc_0042ED06:
        xor  eax,eax
    loc_0042ED08:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ecx,0xfffffffd
        jmp loc_0042F07E
    loc_0042ED23:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E668
    loc_0042ED2C:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E6D9
    loc_0042ED35:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E758
    loc_0042ED3E:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E7C8
    loc_0042ED47:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E839
    loc_0042ED50:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E8B8
    loc_0042ED59:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E928
    loc_0042ED62:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042E999
    loc_0042ED6B:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EA18
    loc_0042ED74:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EA88
    loc_0042ED7D:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EAF9
    loc_0042ED86:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EB78
    loc_0042ED8F:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EBF8
    loc_0042ED98:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EC58
    loc_0042EDA1:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042ECA8
    loc_0042EDAA:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042ED08
    loc_0042EDB3:
        cmp  al,0x64
        jge loc_0042EF1C
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EDCA
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EDCA:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EDF6
        mov  ecx,0x25
        jmp loc_0042EDE0
        nop
        nop
    loc_0042EDE0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042EEFB
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EDE0
    loc_0042EDF6:
        xor  eax,eax
    loc_0042EDF8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ecx,0xfffffffd
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EE28
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EE28:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EE56
        mov  ecx,0x26
        jmp loc_0042EE40
        nop
        nop
    loc_0042EE40:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042EF04
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EE40
    loc_0042EE56:
        xor  eax,eax
    loc_0042EE58:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ecx,0x2
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EE88
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EE88:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EEA2
        nop
    loc_0042EE90:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],bp
        je loc_0042EF0D
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EE90
    loc_0042EEA2:
        xor  eax,eax
    loc_0042EEA4:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EED4
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EED4:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F066
        mov  ecx,0x2a
    loc_0042EEE4:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042EF13
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EEE4
        jmp loc_0042F066
    loc_0042EEFB:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EDF8
    loc_0042EF04:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EE58
    loc_0042EF0D:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EEA4
    loc_0042EF13:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F068
    loc_0042EF1C:
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EF2B
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EF2B:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EF56
        mov  ecx,0x25
        jmp loc_0042EF40
        nop
    loc_0042EF40:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F1F4
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EF40
    loc_0042EF56:
        xor  eax,eax
    loc_0042EF58:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ecx,0x2
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EF88
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EF88:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042EFB6
        mov  ecx,0x26
        jmp loc_0042EFA0
        nop
        nop
    loc_0042EFA0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F1FD
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EFA0
    loc_0042EFB6:
        xor  eax,eax
    loc_0042EFB8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ecx,0x2
        mov  DWORD PTR [eax],ecx
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042EFE8
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042EFE8:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F006
        nop
    loc_0042EFF0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],bp
        je loc_0042F206
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042EFF0
    loc_0042F006:
        xor  eax,eax
    loc_0042F008:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ebp,0x2
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F038
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F038:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F066
        mov  ecx,0x2a
        jmp loc_0042F050
        nop
        nop
    loc_0042F050:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042EF13
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F050
    loc_0042F066:
        xor  eax,eax
    loc_0042F068:
        mov  edx,esi
        push  eax
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ecx,0x2
    loc_0042F07E:
        mov  DWORD PTR [eax],ecx
        mov  al,ds:0x491d69
        cmp  al,0xa
        mov  ecx,DWORD PTR [edi+0x2c8]
        mov  edx,esi
        push  ecx
        jge loc_0042F230
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F0A5
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F0A5:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F0C7
        mov  ecx,0x2d
    loc_0042F0B1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F20F
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F0B1
    loc_0042F0C7:
        xor  eax,eax
    loc_0042F0C9:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F0F9
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F0F9:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F126
        mov  ecx,0x2e
        jmp loc_0042F110
        nop
        mov  edi,edi
    loc_0042F110:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F218
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F110
    loc_0042F126:
        xor  eax,eax
    loc_0042F128:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F158
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F158:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F186
        mov  ecx,0x31
        jmp loc_0042F170
        nop
        nop
    loc_0042F170:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F221
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F170
    loc_0042F186:
        xor  eax,eax
    loc_0042F188:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F1B8
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F1B8:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F1D6
        mov  ecx,0x32
    loc_0042F1C4:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F22A
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F1C4
    loc_0042F1D6:
        xor  eax,eax
    loc_0042F1D8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        pop  esi
        and  ecx,0xfffffffd
        pop  ebp
        mov  DWORD PTR [eax],ecx
        pop  ebx
        ret
    loc_0042F1F4:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EF58
    loc_0042F1FD:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042EFB8
    loc_0042F206:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F008
    loc_0042F20F:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F0C9
    loc_0042F218:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F128
    loc_0042F221:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F188
    loc_0042F22A:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F1D8
    loc_0042F230:
        cmp  al,0x64
        jge loc_0042F3A8
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F247
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F247:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F276
        mov  ecx,0x2d
        jmp loc_0042F260
        nop
        nop
    loc_0042F260:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F387
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F260
    loc_0042F276:
        xor  eax,eax
    loc_0042F278:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F2A8
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F2A8:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F2D6
        mov  ecx,0x2e
        jmp loc_0042F2C0
        nop
        nop
    loc_0042F2C0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F390
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F2C0
    loc_0042F2D6:
        xor  eax,eax
    loc_0042F2D8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ebp,0x2
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F308
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F308:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F326
        mov  ecx,0x31
    loc_0042F314:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F399
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F314
    loc_0042F326:
        xor  eax,eax
    loc_0042F328:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        and  ebp,0xfffffffd
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F358
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F358:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F506
        mov  ecx,0x32
        jmp loc_0042F370
        lea  ebx,[ebx+0x0]
    loc_0042F370:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F39F
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F370
        jmp loc_0042F506
    loc_0042F387:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F278
    loc_0042F390:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F2D8
    loc_0042F399:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F328
    loc_0042F39F:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F508
    loc_0042F3A8:
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F3B7
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F3B7:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F3E6
        mov  ecx,0x2d
        jmp loc_0042F3D0
        nop
        nop
    loc_0042F3D0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F524
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F3D0
    loc_0042F3E6:
        xor  eax,eax
    loc_0042F3E8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ebp,0x2
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F418
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F418:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F446
        mov  ecx,0x2e
        jmp loc_0042F430
        nop
        nop
    loc_0042F430:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F52D
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F430
    loc_0042F446:
        xor  eax,eax
    loc_0042F448:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ebp,0x2
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F478
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F478:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F4A6
        mov  ecx,0x31
        jmp loc_0042F490
        nop
        nop
    loc_0042F490:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F536
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F490
    loc_0042F4A6:
        xor  eax,eax
    loc_0042F4A8:
        push  eax
        mov  edx,esi
        call FUN_004491c0
        mov  ebp,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        or   ebp,0x2
        mov  DWORD PTR [eax],ebp
        mov  ecx,DWORD PTR [edi+0x2c8]
        push  ecx
        mov  edx,esi
        call FUN_004491c0
        cmp  eax,ebx
        jne loc_0042F4D8
        mov  DWORD PTR [edi+0x2c8],ebx
    loc_0042F4D8:
        add  eax,0x10
        cmp  eax,ebx
        je loc_0042F506
        mov  ecx,0x32
        jmp loc_0042F4F0
        nop
        nop
    loc_0042F4F0:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_0042F39F
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_0042F4F0
    loc_0042F506:
        xor  eax,eax
    loc_0042F508:
        mov  edx,esi
        push  eax
        call FUN_004491c0
        mov  ecx,DWORD PTR [eax+0x35c]
        add  eax,0x35c
        pop  esi
        or   ecx,0x2
        pop  ebp
        mov  DWORD PTR [eax],ecx
        pop  ebx
        ret
    loc_0042F524:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F3E8
    loc_0042F52D:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F448
    loc_0042F536:
        mov  eax,DWORD PTR [eax]
        mov  eax,DWORD PTR [eax]
        jmp loc_0042F4A8
    }
}
