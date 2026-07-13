// 0044E1A0: FUN_0044e1a0
// Original size: 7024 bytes, actual code: 1934 instructions
extern "C" void FUN_0044bc70(void);
extern "C" void FUN_0044df70(void);
extern "C" void FUN_0044fdb0(void);
extern "C" void FUN_0044fe40(void);
extern "C" void FUN_0044ff00(void);
extern "C" void FUN_0044ff80(void);
extern "C" void FUN_00450030(void);
extern "C" void FUN_00450070(void);
extern "C" void FUN_004500d0(void);
extern "C" void FUN_00450160(void);
extern "C" void FUN_00450190(void);
extern "C" void FUN_004501b0(void);
extern "C" void FUN_004505b0(void);
extern "C" void FUN_00450690(void);
extern "C" void FUN_004506d0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);
extern "C" void FUN_00452730(void);
extern "C" void FUN_00463b2c(void);
extern "C" void FUN_E776FC76(void);

extern "C" __declspec(naked) void FUN_0044e1a0(void) {
    __asm {
        sub  esp,0x108
        push  ebx
        push  ebp
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [esi+0x4]
        lea  ebx,[esi+0x4]
        xor  ebp,ebp
        cmp  eax,ebp
        jne loc_0044E1C6
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        add  esp,0x108
        ret  0x4
    loc_0044E1C6:
        fild  DWORD PTR [eax]
        push  edi
        fcomp DWORD PTR [esi]
        fnstsw ax
        test  ah,0x41
        jp loc_0044FB96
        jmp loc_0044E1E0
        nop
        nop
    loc_0044E1E0:
        mov  edi,DWORD PTR [ebx]
        mov  al,BYTE PTR [edi+0xa]
        test  BYTE PTR [esi+0x101c],al
        je loc_0044FB77
        movsx eax,WORD PTR [edi+0x4]
        cmp  eax,0x57
        ja loc_0044FB68
        movzx ecx,BYTE PTR [eax+0x44fcb4]
        jmp  DWORD PTR [ecx*4+0x44fbc4]
        lea  edi,[esi+0x8]
        mov  eax,edi
        call FUN_004506d0
        cmp  DWORD PTR [esi+0x1008],ebp
        je loc_0044FBB0
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E23A
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [eax+edi*1]
        mov  DWORD PTR [ebx],edx
    loc_0044E23A:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E252
        mov  DWORD PTR [edi+0x1000],eax
        mov  eax,DWORD PTR [edi+eax*1]
        mov  DWORD PTR [esi],eax
    loc_0044E252:
        cmp  DWORD PTR [ebx],ebp
        je loc_0044FBB2
        jmp loc_0044FB77
        mov  edi,DWORD PTR [esi+0x1014]
        push  ebp
        push  0xffffffff
        call FUN_004500d0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1014]
        call FUN_00450190
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [edi+0x10]
        add  ecx,0x4
        shr  ecx,0x2
        mov  edx,DWORD PTR [edi+ecx*4+0x10]
        push  0x1
        push  edx
        push  0x1
        mov  edx,esi
        call FUN_0044ff00
        mov  edi,DWORD PTR [esi+0x1014]
        push  eax
        call FUN_004500d0
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  ecx,eax
        mov  eax,DWORD PTR [esi+0x1014]
        call FUN_00450160
        cmp  eax,ebp
        je loc_0044FB77
        mov  eax,DWORD PTR [eax]
        mov  DWORD PTR [eax+0x4],ebp
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  ecx,eax
        mov  eax,DWORD PTR [esi+0x1014]
        call FUN_00450160
        cmp  eax,ebp
        je loc_0044FB77
        mov  eax,DWORD PTR [eax]
        or   DWORD PTR [eax+0x1020],0x1
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  ecx,eax
        mov  eax,DWORD PTR [esi+0x1014]
        call FUN_00450160
        cmp  eax,ebp
        je loc_0044FB77
        mov  eax,DWORD PTR [eax]
        and  DWORD PTR [eax+0x1020],0xfffffffe
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  ecx,eax
        mov  eax,DWORD PTR [esi+0x1014]
        call FUN_00450160
        cmp  eax,ebp
        je loc_0044FB77
        mov  edi,DWORD PTR [eax]
        push  0x1
        mov  edx,esi
        call FUN_0044fdb0
        mov  DWORD PTR [edi+0x1018],eax
        jmp loc_0044FB77
        push  ebp
        push  esi
        mov  eax,esi
        call FUN_0044df70
        test  eax,eax
        jne loc_0044FBB2
        jmp loc_0044FB85
        mov  eax,DWORD PTR [esi+0x1008]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E3B3
        mov  DWORD PTR [esi+0x1008],eax
        mov  ecx,DWORD PTR [esi+eax*1+0x8]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0x90],ecx
        mov  DWORD PTR [esi+0x1008],eax
        cmp  BYTE PTR [esi+eax*1+0x8],0x66
        jne loc_0044E3B3
        fld  DWORD PTR [esp+0x90]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x90],eax
    loc_0044E3B3:
        cmp  DWORD PTR [esp+0x90],ebp
        jne loc_0044E40F
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E402
        mov  DWORD PTR [esi+0x1008],eax
        mov  edx,DWORD PTR [esi+eax*1+0x8]
        add  eax,0xfffffffc
        mov  DWORD PTR [esi+0x1008],eax
        cmp  BYTE PTR [esi+eax*1+0x8],0x66
        mov  DWORD PTR [esp+0xfc],edx
        jne loc_0044E402
        fld  DWORD PTR [esp+0xfc]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xfc],eax
    loc_0044E402:
        cmp  DWORD PTR [esp+0xfc],ebp
        jne loc_0044FB77
    loc_0044E40F:
        mov  eax,DWORD PTR [ebx]
        fild  DWORD PTR [eax+0x14]
        fstp  DWORD PTR [esi]
        mov  ecx,DWORD PTR [eax+0x10]
        jmp loc_0044FB81
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x10],eax
        fild  DWORD PTR [esp+0x10]
        fsubr DWORD PTR [esi]
        fstp  DWORD PTR [esi]
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        lea  edx,[esi+0x8]
        mov  ecx,eax
        mov  eax,edx
        call FUN_00450690
        jmp loc_0044FB77
        lea  eax,[esi+0x8]
        call FUN_004506d0
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  DWORD PTR [esp+0x10],eax
        lea  eax,[esp+0x10]
        push  eax
        lea  eax,[esi+0x8]
        mov  dl,0x69
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        xor  ecx,ecx
        call FUN_00450030
        mov  edi,eax
        mov  eax,DWORD PTR [esi+0x1008]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044FB77
        mov  DWORD PTR [esi+0x1008],eax
        mov  ecx,DWORD PTR [esi+eax*1+0x8]
        mov  DWORD PTR [edi],ecx
        mov  edx,DWORD PTR [esi+0x1008]
        add  edx,0xfffffffc
        mov  eax,edx
        mov  DWORD PTR [esi+0x1008],edx
        cmp  BYTE PTR [esi+eax*1+0x8],0x66
        jne loc_0044FB77
        fld  DWORD PTR [edi]
        call FUN_00463b2c
        mov  DWORD PTR [edi],eax
        jmp loc_0044FB77
        xor  ecx,ecx
        mov  eax,esi
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        lea  edx,[esp+0x10]
        push  edx
        lea  eax,[esi+0x8]
        mov  dl,0x66
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        xor  ecx,ecx
        mov  eax,esi
        call FUN_00450070
        mov  ecx,DWORD PTR [esi+0x1008]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044FB77
        mov  DWORD PTR [esi+0x1008],ecx
        mov  ecx,DWORD PTR [esi+ecx*1+0x8]
        mov  DWORD PTR [eax],ecx
        mov  edi,DWORD PTR [esi+0x1008]
        add  edi,0xfffffffc
        mov  ecx,edi
        mov  DWORD PTR [esi+0x1008],edi
        mov  cl,BYTE PTR [esi+ecx*1+0x8]
        cmp  cl,0x66
        je loc_0044FB77
        cmp  cl,0x69
        jne loc_0044FB77
        fild  DWORD PTR [eax]
        fstp  DWORD PTR [eax]
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E58A
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x104],edx
        jne loc_0044E58A
        fld  DWORD PTR [esp+0x104]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x104],eax
    loc_0044E58A:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E5C0
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0x20],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044E5C0
        fld  DWORD PTR [esp+0x20]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x20],eax
    loc_0044E5C0:
        mov  edx,DWORD PTR [esp+0x104]
        mov  ebx,DWORD PTR [esp+0x20]
        lea  eax,[esp+0x20]
        push  eax
        add  ebx,edx
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x28],ebx
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E61F
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0x50],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044E61F
        fld  DWORD PTR [esp+0x50]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x50],eax
    loc_0044E61F:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E655
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x24],edx
        jne loc_0044E655
        fld  DWORD PTR [esp+0x24]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x24],eax
    loc_0044E655:
        mov  ebx,DWORD PTR [esp+0x24]
        mov  eax,DWORD PTR [esp+0x50]
        lea  ecx,[esp+0x24]
        sub  ebx,eax
        push  ecx
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x2c],ebx
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E6BA
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0xb0],edx
        jne loc_0044E6BA
        fld  DWORD PTR [esp+0xb0]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xb0],eax
    loc_0044E6BA:
        mov  eax,DWORD PTR [edi+0x1000]
        lea  ecx,[eax-0x4]
        cmp  ecx,ebp
        jl loc_0044E70D
        mov  DWORD PTR [edi+0x1000],ecx
        mov  eax,DWORD PTR [edi+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [edi+0x1000],ecx
        cmp  BYTE PTR [edi+ecx*1],0x66
        mov  DWORD PTR [esp+0x44],eax
        jne loc_0044E711
        fld  DWORD PTR [esp+0x44]
        call FUN_00463b2c
        imul  eax,DWORD PTR [esp+0xb0]
        mov  DWORD PTR [esp+0x44],eax
        lea  eax,[esp+0x44]
        push  eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044E70D:
        mov  eax,DWORD PTR [esp+0x44]
    loc_0044E711:
        imul  eax,DWORD PTR [esp+0xb0]
        mov  DWORD PTR [esp+0x44],eax
        lea  eax,[esp+0x44]
        push  eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E76B
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0x58],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044E76B
        fld  DWORD PTR [esp+0x58]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x58],eax
    loc_0044E76B:
        mov  eax,DWORD PTR [edi+0x1000]
        lea  ecx,[eax-0x4]
        cmp  ecx,ebp
        jl loc_0044E7BB
        mov  DWORD PTR [edi+0x1000],ecx
        mov  eax,DWORD PTR [edi+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [edi+0x1000],ecx
        cmp  BYTE PTR [edi+ecx*1],0x66
        mov  DWORD PTR [esp+0x3c],eax
        jne loc_0044E7BF
        fld  DWORD PTR [esp+0x3c]
        call FUN_00463b2c
        cdq
        idiv  DWORD PTR [esp+0x58]
        lea  edx,[esp+0x3c]
        push  edx
        mov  dl,0x69
        push  0x4
        mov  DWORD PTR [esp+0x44],eax
        mov  eax,edi
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044E7BB:
        mov  eax,DWORD PTR [esp+0x3c]
    loc_0044E7BF:
        cdq
        idiv  DWORD PTR [esp+0x58]
        lea  edx,[esp+0x3c]
        push  edx
        mov  dl,0x69
        push  0x4
        mov  DWORD PTR [esp+0x44],eax
        mov  eax,edi
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044E81F
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xe0],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044E81F
        fld  DWORD PTR [esp+0xe0]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xe0],eax
    loc_0044E81F:
        mov  eax,DWORD PTR [edi+0x1000]
        lea  ecx,[eax-0x4]
        cmp  ecx,ebp
        jl loc_0044E872
        mov  DWORD PTR [edi+0x1000],ecx
        mov  eax,DWORD PTR [edi+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [edi+0x1000],ecx
        cmp  BYTE PTR [edi+ecx*1],0x66
        mov  DWORD PTR [esp+0x28],eax
        jne loc_0044E876
        fld  DWORD PTR [esp+0x28]
        call FUN_00463b2c
        cdq
        idiv  DWORD PTR [esp+0xe0]
        mov  eax,edi
        mov  DWORD PTR [esp+0x28],edx
        lea  edx,[esp+0x28]
        push  edx
        mov  dl,0x69
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044E872:
        mov  eax,DWORD PTR [esp+0x28]
    loc_0044E876:
        cdq
        idiv  DWORD PTR [esp+0xe0]
        mov  eax,edi
        mov  DWORD PTR [esp+0x28],edx
        lea  edx,[esp+0x28]
        push  edx
        mov  dl,0x69
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044E8D2
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x60],edx
        je loc_0044E8D2
        cmp  cl,0x69
        jne loc_0044E8D2
        fild  DWORD PTR [esp+0x60]
        fstp  DWORD PTR [esp+0x60]
    loc_0044E8D2:
        mov  ecx,DWORD PTR [eax+0x1000]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044E921
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x30],edx
        je loc_0044E921
        cmp  cl,0x69
        jne loc_0044E921
        fild  DWORD PTR [esp+0x30]
        lea  ecx,[esp+0x30]
        push  ecx
        mov  dl,0x66
        fadd  DWORD PTR [esp+0x64]
        push  0x4
        fstp  DWORD PTR [esp+0x38]
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044E921:
        fld  DWORD PTR [esp+0x30]
        lea  ecx,[esp+0x30]
        fadd  DWORD PTR [esp+0x60]
        push  ecx
        mov  dl,0x66
        push  0x4
        fstp  DWORD PTR [esp+0x38]
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044E984
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0xb8],edx
        je loc_0044E984
        cmp  cl,0x69
        jne loc_0044E984
        fild  DWORD PTR [esp+0xb8]
        fstp  DWORD PTR [esp+0xb8]
    loc_0044E984:
        mov  ecx,DWORD PTR [eax+0x1000]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044E9D6
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x40],edx
        je loc_0044E9D6
        cmp  cl,0x69
        jne loc_0044E9D6
        fild  DWORD PTR [esp+0x40]
        lea  ecx,[esp+0x40]
        push  ecx
        mov  dl,0x66
        fsub  DWORD PTR [esp+0xbc]
        push  0x4
        fstp  DWORD PTR [esp+0x48]
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044E9D6:
        fld  DWORD PTR [esp+0x40]
        lea  ecx,[esp+0x40]
        fsub  DWORD PTR [esp+0xb8]
        push  ecx
        mov  dl,0x66
        push  0x4
        fstp  DWORD PTR [esp+0x48]
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044EA33
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x68],edx
        je loc_0044EA33
        cmp  cl,0x69
        jne loc_0044EA33
        fild  DWORD PTR [esp+0x68]
        fstp  DWORD PTR [esp+0x68]
    loc_0044EA33:
        mov  ecx,DWORD PTR [eax+0x1000]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044EA82
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x38],edx
        je loc_0044EA82
        cmp  cl,0x69
        jne loc_0044EA82
        fild  DWORD PTR [esp+0x38]
        lea  ecx,[esp+0x38]
        push  ecx
        mov  dl,0x66
        fmul  DWORD PTR [esp+0x6c]
        push  0x4
        fstp  DWORD PTR [esp+0x40]
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044EA82:
        fld  DWORD PTR [esp+0x38]
        lea  ecx,[esp+0x38]
        fmul  DWORD PTR [esp+0x68]
        push  ecx
        mov  dl,0x66
        push  0x4
        fstp  DWORD PTR [esp+0x40]
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044EAE5
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0xf8],edx
        je loc_0044EAE5
        cmp  cl,0x69
        jne loc_0044EAE5
        fild  DWORD PTR [esp+0xf8]
        fstp  DWORD PTR [esp+0xf8]
    loc_0044EAE5:
        mov  ecx,DWORD PTR [eax+0x1000]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044EB37
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x2c],edx
        je loc_0044EB37
        cmp  cl,0x69
        jne loc_0044EB37
        fild  DWORD PTR [esp+0x2c]
        lea  ecx,[esp+0x2c]
        push  ecx
        mov  dl,0x66
        fdiv  DWORD PTR [esp+0xfc]
        push  0x4
        fstp  DWORD PTR [esp+0x34]
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044EB37:
        fld  DWORD PTR [esp+0x2c]
        lea  ecx,[esp+0x2c]
        fdiv  DWORD PTR [esp+0xf8]
        push  ecx
        mov  dl,0x66
        push  0x4
        fstp  DWORD PTR [esp+0x34]
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EB92
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x70],edx
        jne loc_0044EB92
        fld  DWORD PTR [esp+0x70]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x70],eax
    loc_0044EB92:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EBD1
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xc0],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044EBD1
        fld  DWORD PTR [esp+0xc0]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xc0],eax
    loc_0044EBD1:
        mov  eax,DWORD PTR [esp+0x70]
        mov  ebx,DWORD PTR [esp+0xc0]
        xor  edx,edx
        cmp  ebx,eax
        sete  dl
        lea  ecx,[esp+0x10]
        push  ecx
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x18],edx
        mov  dl,0x69
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EC35
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x78],edx
        jne loc_0044EC35
        fld  DWORD PTR [esp+0x78]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x78],eax
    loc_0044EC35:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EC74
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xe8],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044EC74
        fld  DWORD PTR [esp+0xe8]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xe8],eax
    loc_0044EC74:
        mov  eax,DWORD PTR [esp+0x78]
        mov  ebx,DWORD PTR [esp+0xe8]
        xor  edx,edx
        cmp  ebx,eax
        setne dl
        lea  ecx,[esp+0x10]
        push  ecx
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x18],edx
        mov  dl,0x69
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044ECE1
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x80],edx
        jne loc_0044ECE1
        fld  DWORD PTR [esp+0x80]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x80],eax
    loc_0044ECE1:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044ED20
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xc8],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044ED20
        fld  DWORD PTR [esp+0xc8]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xc8],eax
    loc_0044ED20:
        mov  eax,DWORD PTR [esp+0x80]
        mov  ebx,DWORD PTR [esp+0xc8]
        xor  edx,edx
        cmp  ebx,eax
        setl  dl
        lea  ecx,[esp+0x10]
        push  ecx
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x18],edx
        mov  dl,0x69
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044ED90
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x88],edx
        jne loc_0044ED90
        fld  DWORD PTR [esp+0x88]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x88],eax
    loc_0044ED90:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EDCF
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0x108],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044EDCF
        fld  DWORD PTR [esp+0x108]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x108],eax
    loc_0044EDCF:
        mov  eax,DWORD PTR [esp+0x88]
        mov  ebx,DWORD PTR [esp+0x108]
        xor  edx,edx
        cmp  ebx,eax
        setle dl
        lea  ecx,[esp+0x10]
        push  ecx
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x18],edx
        mov  dl,0x69
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EE36
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x48],edx
        jne loc_0044EE36
        fld  DWORD PTR [esp+0x48]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x48],eax
    loc_0044EE36:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EE75
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xd0],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044EE75
        fld  DWORD PTR [esp+0xd0]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xd0],eax
    loc_0044EE75:
        mov  eax,DWORD PTR [esp+0x48]
        mov  ebx,DWORD PTR [esp+0xd0]
        xor  edx,edx
        cmp  ebx,eax
        setg  dl
        lea  ecx,[esp+0x10]
        push  ecx
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x18],edx
        mov  dl,0x69
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EEE2
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0x98],edx
        jne loc_0044EEE2
        fld  DWORD PTR [esp+0x98]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x98],eax
    loc_0044EEE2:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EF21
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xf0],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044EF21
        fld  DWORD PTR [esp+0xf0]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xf0],eax
    loc_0044EF21:
        mov  eax,DWORD PTR [esp+0x98]
        mov  ebx,DWORD PTR [esp+0xf0]
        xor  edx,edx
        cmp  ebx,eax
        setge dl
        lea  ecx,[esp+0x10]
        push  ecx
        mov  eax,edi
        push  0x4
        mov  DWORD PTR [esp+0x18],edx
        mov  dl,0x69
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EF91
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [edi+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0xa0],edx
        jne loc_0044EF91
        fld  DWORD PTR [esp+0xa0]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xa0],eax
    loc_0044EF91:
        mov  ebx,DWORD PTR [esp+0xa0]
        xor  eax,eax
        cmp  ebx,ebp
        sete  al
        lea  ecx,[esp+0x10]
        push  ecx
        mov  dl,0x69
        push  0x4
        mov  DWORD PTR [esp+0x18],eax
        mov  eax,edi
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044EFFA
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [ecx+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [ecx+eax*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0xd8],edx
        je loc_0044EFFA
        cmp  al,0x69
        jne loc_0044EFFA
        fild  DWORD PTR [esp+0xd8]
        fstp  DWORD PTR [esp+0xd8]
    loc_0044EFFA:
        mov  eax,DWORD PTR [ecx+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F039
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [ecx+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [ecx+eax*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0xa8],edx
        je loc_0044F039
        cmp  al,0x69
        jne loc_0044F039
        fild  DWORD PTR [esp+0xa8]
        fstp  DWORD PTR [esp+0xa8]
    loc_0044F039:
        fld  DWORD PTR [esp+0xd8]
        mov  DWORD PTR [esp+0x14],0x1
        fld  DWORD PTR [esp+0xa8]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_0044F05C
        mov  DWORD PTR [esp+0x14],ebp
    loc_0044F05C:
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F0B3
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [ecx+eax*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [ecx+eax*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x100],edx
        je loc_0044F0B3
        cmp  al,0x69
        jne loc_0044F0B3
        fild  DWORD PTR [esp+0x100]
        fstp  DWORD PTR [esp+0x100]
    loc_0044F0B3:
        mov  eax,DWORD PTR [ecx+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F0E9
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x4c],edx
        je loc_0044F0E9
        cmp  al,0x69
        jne loc_0044F0E9
        fild  DWORD PTR [esp+0x4c]
        fstp  DWORD PTR [esp+0x4c]
    loc_0044F0E9:
        fld  DWORD PTR [esp+0x100]
        mov  DWORD PTR [esp+0x14],0x1
        fld  DWORD PTR [esp+0x4c]
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0044F05C
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        mov  DWORD PTR [esp+0x1c],ebp
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F15B
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x5c],edx
        je loc_0044F15B
        cmp  al,0x69
        jne loc_0044F15B
        fild  DWORD PTR [esp+0x5c]
        fstp  DWORD PTR [esp+0x5c]
    loc_0044F15B:
        mov  eax,DWORD PTR [ecx+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F191
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x54],edx
        je loc_0044F191
        cmp  al,0x69
        jne loc_0044F191
        fild  DWORD PTR [esp+0x54]
        fstp  DWORD PTR [esp+0x54]
    loc_0044F191:
        fld  DWORD PTR [esp+0x54]
        mov  DWORD PTR [esp+0x14],0x1
        fcomp DWORD PTR [esp+0x5c]
        fnstsw ax
        test  ah,0x5
        jnp loc_0044F05C
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        mov  DWORD PTR [esp+0x1c],ebp
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F1FE
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x6c],edx
        je loc_0044F1FE
        cmp  al,0x69
        jne loc_0044F1FE
        fild  DWORD PTR [esp+0x6c]
        fstp  DWORD PTR [esp+0x6c]
    loc_0044F1FE:
        mov  eax,DWORD PTR [ecx+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F234
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x64],edx
        je loc_0044F234
        cmp  al,0x69
        jne loc_0044F234
        fild  DWORD PTR [esp+0x64]
        fstp  DWORD PTR [esp+0x64]
    loc_0044F234:
        fld  DWORD PTR [esp+0x64]
        mov  DWORD PTR [esp+0x14],0x1
        fcomp DWORD PTR [esp+0x6c]
        fnstsw ax
        test  ah,0x41
        jnp loc_0044F05C
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        mov  DWORD PTR [esp+0x1c],ebp
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F2A1
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x7c],edx
        je loc_0044F2A1
        cmp  al,0x69
        jne loc_0044F2A1
        fild  DWORD PTR [esp+0x7c]
        fstp  DWORD PTR [esp+0x7c]
    loc_0044F2A1:
        mov  eax,DWORD PTR [ecx+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F2D7
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x74],edx
        je loc_0044F2D7
        cmp  al,0x69
        jne loc_0044F2D7
        fild  DWORD PTR [esp+0x74]
        fstp  DWORD PTR [esp+0x74]
    loc_0044F2D7:
        fld  DWORD PTR [esp+0x74]
        mov  DWORD PTR [esp+0x14],0x1
        fcomp DWORD PTR [esp+0x7c]
        fnstsw ax
        test  ah,0x41
        je loc_0044F05C
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        mov  DWORD PTR [esp+0x1c],ebp
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F34D
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x8c],edx
        je loc_0044F34D
        cmp  al,0x69
        jne loc_0044F34D
        fild  DWORD PTR [esp+0x8c]
        fstp  DWORD PTR [esp+0x8c]
    loc_0044F34D:
        mov  eax,DWORD PTR [ecx+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F38C
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x84],edx
        je loc_0044F38C
        cmp  al,0x69
        jne loc_0044F38C
        fild  DWORD PTR [esp+0x84]
        fstp  DWORD PTR [esp+0x84]
    loc_0044F38C:
        fld  DWORD PTR [esp+0x84]
        mov  DWORD PTR [esp+0x14],0x1
        fcomp DWORD PTR [esp+0x8c]
        fnstsw ax
        test  ah,0x1
        je loc_0044F05C
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        mov  DWORD PTR [esp+0x1c],ebp
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  ecx,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F408
        mov  DWORD PTR [ecx+0x1000],eax
        mov  edx,DWORD PTR [eax+ecx*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [ecx+0x1000],eax
        mov  al,BYTE PTR [eax+ecx*1]
        cmp  al,0x66
        mov  DWORD PTR [esp+0x94],edx
        je loc_0044F408
        cmp  al,0x69
        jne loc_0044F408
        fild  DWORD PTR [esp+0x94]
        fstp  DWORD PTR [esp+0x94]
    loc_0044F408:
        fld  DWORD PTR ds:0x470b04
        mov  DWORD PTR [esp+0x14],0x1
        fld  DWORD PTR [esp+0x94]
        fucompp
        fnstsw ax
        test  ah,0x44
        jnp loc_0044F05C
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,ecx
        push  0x4
        mov  DWORD PTR [esp+0x1c],ebp
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F485
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xa4],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        jne loc_0044F485
        fld  DWORD PTR [esp+0xa4]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xa4],eax
    loc_0044F485:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F4C4
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        mov  DWORD PTR [esp+0x9c],edx
        jne loc_0044F4C4
        fld  DWORD PTR [esp+0x9c]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0x9c],eax
    loc_0044F4C4:
        cmp  DWORD PTR [esp+0x9c],ebp
        jne loc_0044F4DA
        cmp  DWORD PTR [esp+0xa4],ebp
        mov  DWORD PTR [esp+0x14],ebp
        je loc_0044F4E2
    loc_0044F4DA:
        mov  DWORD PTR [esp+0x14],0x1
    loc_0044F4E2:
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F539
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xb4],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        jne loc_0044F539
        fld  DWORD PTR [esp+0xb4]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xb4],eax
    loc_0044F539:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F578
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        mov  DWORD PTR [esp+0xac],edx
        jne loc_0044F578
        fld  DWORD PTR [esp+0xac]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xac],eax
    loc_0044F578:
        cmp  DWORD PTR [esp+0xac],ebp
        je loc_0044F592
        cmp  DWORD PTR [esp+0xb4],ebp
        mov  DWORD PTR [esp+0x14],0x1
        jne loc_0044F596
    loc_0044F592:
        mov  DWORD PTR [esp+0x14],ebp
    loc_0044F596:
        lea  eax,[esp+0x14]
        push  eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F5ED
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xc4],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        jne loc_0044F5ED
        fld  DWORD PTR [esp+0xc4]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xc4],eax
    loc_0044F5ED:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F62C
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        mov  DWORD PTR [esp+0xbc],edx
        jne loc_0044F62C
        fld  DWORD PTR [esp+0xbc]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xbc],eax
    loc_0044F62C:
        mov  eax,DWORD PTR [esp+0xbc]
        xor  eax,DWORD PTR [esp+0xc4]
        lea  ecx,[esp+0x10]
        push  ecx
        mov  DWORD PTR [esp+0x14],eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F695
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        mov  DWORD PTR [esp+0xd4],edx
        jne loc_0044F695
        fld  DWORD PTR [esp+0xd4]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xd4],eax
    loc_0044F695:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F6D4
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xcc],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [eax+edi*1],0x66
        jne loc_0044F6D4
        fld  DWORD PTR [esp+0xcc]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xcc],eax
    loc_0044F6D4:
        mov  edx,DWORD PTR [esp+0xcc]
        or   edx,DWORD PTR [esp+0xd4]
        lea  eax,[esp+0x10]
        push  eax
        mov  DWORD PTR [esp+0x14],edx
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F73D
        mov  DWORD PTR [edi+0x1000],eax
        mov  ecx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [esp+0xe4],ecx
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        jne loc_0044F73D
        fld  DWORD PTR [esp+0xe4]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xe4],eax
    loc_0044F73D:
        mov  eax,DWORD PTR [edi+0x1000]
        add  eax,0xfffffffc
        cmp  eax,ebp
        jl loc_0044F77C
        mov  DWORD PTR [edi+0x1000],eax
        mov  edx,DWORD PTR [eax+edi*1]
        add  eax,0xfffffffc
        mov  DWORD PTR [edi+0x1000],eax
        cmp  BYTE PTR [edi+eax*1],0x66
        mov  DWORD PTR [esp+0xdc],edx
        jne loc_0044F77C
        fld  DWORD PTR [esp+0xdc]
        call FUN_00463b2c
        mov  DWORD PTR [esp+0xdc],eax
    loc_0044F77C:
        mov  eax,DWORD PTR [esp+0xdc]
        and  eax,DWORD PTR [esp+0xe4]
        lea  ecx,[esp+0x10]
        push  ecx
        mov  DWORD PTR [esp+0x14],eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  eax,DWORD PTR [esi+0x1008]
        lea  edi,[esi+0x8]
        lea  ecx,[eax-0x4]
        cmp  ecx,ebp
        jl loc_0044F7F3
        mov  DWORD PTR [edi+0x1000],ecx
        mov  eax,DWORD PTR [ecx+edi*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [edi+0x1000],ecx
        cmp  BYTE PTR [edi+ecx*1],0x66
        mov  DWORD PTR [esp+0x34],eax
        jne loc_0044F7F7
        fld  DWORD PTR [esp+0x34]
        call FUN_00463b2c
        lea  edx,[esp+0x34]
        neg  eax
        push  edx
        mov  DWORD PTR [esp+0x38],eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
    loc_0044F7F3:
        mov  eax,DWORD PTR [esp+0x34]
    loc_0044F7F7:
        lea  edx,[esp+0x34]
        neg  eax
        push  edx
        mov  DWORD PTR [esp+0x38],eax
        mov  dl,0x69
        mov  eax,edi
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044F84D
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [ecx+eax*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0x1c],edx
        je loc_0044F851
        cmp  cl,0x69
        jne loc_0044F851
        fild  DWORD PTR [esp+0x1c]
        fstp  DWORD PTR [esp+0x1c]
    loc_0044F84D:
        mov  edx,DWORD PTR [esp+0x1c]
    loc_0044F851:
        neg  edx
        lea  ecx,[esp+0x1c]
        push  ecx
        mov  DWORD PTR [esp+0x20],edx
        mov  dl,0x66
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        push  ebp
        mov  edx,esi
        call FUN_0044fdb0
        mov  edi,eax
        xor  ecx,ecx
        mov  DWORD PTR [esp+0x10],edi
        call FUN_00450030
        lea  edx,[esp+0x10]
        dec  edi
        push  edx
        mov  DWORD PTR [eax],edi
        lea  eax,[esi+0x8]
        mov  dl,0x69
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044F8DC
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [ecx+eax*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0xec],edx
        je loc_0044F8DC
        cmp  cl,0x69
        jne loc_0044F8DC
        fild  DWORD PTR [esp+0xec]
        fstp  DWORD PTR [esp+0xec]
    loc_0044F8DC:
        fld  DWORD PTR [esp+0xec]
        fsin
        jmp loc_0044F934
        mov  ecx,DWORD PTR [esi+0x1008]
        lea  eax,[esi+0x8]
        add  ecx,0xfffffffc
        cmp  ecx,ebp
        jl loc_0044F92B
        mov  DWORD PTR [eax+0x1000],ecx
        mov  edx,DWORD PTR [eax+ecx*1]
        add  ecx,0xfffffffc
        mov  DWORD PTR [eax+0x1000],ecx
        mov  cl,BYTE PTR [eax+ecx*1]
        cmp  cl,0x66
        mov  DWORD PTR [esp+0xf4],edx
        je loc_0044F92B
        cmp  cl,0x69
        jne loc_0044F92B
        fild  DWORD PTR [esp+0xf4]
        fstp  DWORD PTR [esp+0xf4]
    loc_0044F92B:
        fld  DWORD PTR [esp+0xf4]
        fcos
    loc_0044F934:
        lea  ecx,[esp+0x10]
        push  ecx
        fstp  DWORD PTR [esp+0x14]
        mov  dl,0x66
        push  0x4
        call FUN_004505b0
        jmp loc_0044FB77
        mov  ecx,0x3
        mov  eax,esi
        call FUN_0044fe40
        push  ecx
        mov  ecx,0x2
        fstp  DWORD PTR [esp]
        mov  eax,esi
        call FUN_0044fe40
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        push  ecx
        lea  ecx,[esp+0x114]
        fstp  DWORD PTR [esp]
        call FUN_004501b0
        xor  ecx,ecx
        mov  eax,esi
        call FUN_00450070
        mov  edx,DWORD PTR [esp+0x10c]
        mov  DWORD PTR [eax],edx
        mov  ecx,0x1
        mov  eax,esi
        call FUN_00450070
        mov  ecx,DWORD PTR [esp+0x110]
        mov  DWORD PTR [eax],ecx
        jmp loc_0044FB77
        mov  ecx,0x1
        mov  eax,esi
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x18]
        mov  ecx,0x2
        mov  eax,esi
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x14]
        xor  ecx,ecx
        mov  eax,esi
        call FUN_00450070
        fld  DWORD PTR [esp+0x14]
        fmul  DWORD PTR [esp+0x14]
        fld  DWORD PTR [esp+0x18]
        fmul  DWORD PTR [esp+0x18]
        faddp st(1),st
        fstp  DWORD PTR [eax]
        jmp loc_0044FB77
        xor  ecx,ecx
        mov  eax,esi
        call FUN_00450070
        mov  edi,eax
        xor  ecx,ecx
        mov  eax,esi
        call FUN_0044fe40
        push  ecx
        fstp  DWORD PTR [esp]
        call FUN_0044bc70
        fstp  DWORD PTR [edi]
        jmp loc_0044FB77
        mov  ecx,0x2
        mov  eax,esi
        call FUN_0044fe40
        fstp  DWORD PTR [esp+0x10]
        xor  ecx,ecx
        mov  eax,esi
        call FUN_0044fe40
        fsubr DWORD PTR [esp+0x10]
        mov  ecx,0x3
        mov  eax,esi
        fstp  DWORD PTR [esp+0x14]
        call FUN_0044fe40
        mov  ecx,0x1
        fstp  DWORD PTR [esp+0x10]
        mov  eax,esi
        call FUN_0044fe40
        fsubr DWORD PTR [esp+0x10]
        fld  DWORD PTR [esp+0x14]
        xor  ecx,ecx
        mov  eax,esi
        fpatan
        fstp  DWORD PTR [esp+0x10]
        call FUN_00450070
        mov  edx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [eax],edx
        jmp loc_0044FB77
        push  0x400
        add  edi,0x14
        call _malloc
        add  esp,0x4
        cmp  edi,ebp
        mov  DWORD PTR [esp+0x14],eax
        mov  BYTE PTR [eax],0x0
        je loc_0044FB5D
        mov  ebx,0x1
        mov  DWORD PTR [esp+0x18],0x0
        mov  ebp,0x6
    loc_0044FAA2:
        push  0x25
        push  edi
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        mov  DWORD PTR [esp+0x10],eax
        je loc_0044FB57
        mov  edx,DWORD PTR [esp+0x14]
        mov  eax,edi
        sub  edx,edi
    loc_0044FAC1:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [eax+edx*1],cl
        inc  eax
        test  cl,cl
        jne loc_0044FAC1
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x14]
        mov  ecx,eax
        sub  ecx,edi
        mov  BYTE PTR [ecx+edx*1],0x0
        movsx eax,BYTE PTR [eax+0x1]
        sub  eax,0x25
        je loc_0044FB4A
        sub  eax,0x3f
        je loc_0044FAEE
        sub  eax,0x2
        jne loc_0044FB4A
    loc_0044FAEE:
        mov  ecx,DWORD PTR [esi+0x4]
        mov  eax,DWORD PTR [ecx+0x10]
        mov  edx,DWORD PTR [esp+0x18]
        add  edx,eax
        mov  dl,BYTE PTR [edx+ecx*1+0x14]
        cmp  dl,0x66
        je loc_0044FB21
        cmp  dl,0x67
        je loc_0044FB21
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        add  eax,ebp
        mov  eax,DWORD PTR [ecx+eax*4]
        push  eax
        push  ebx
        mov  edx,esi
        call FUN_0044ff00
        jmp loc_0044FB3B
    loc_0044FB21:
        cdq
        and  edx,0x3
        add  eax,edx
        sar  eax,0x2
        add  eax,ebp
        mov  ecx,DWORD PTR [ecx+eax*4]
        push  ecx
        mov  eax,esi
        mov  ecx,ebx
        call FUN_0044ff80
        fstp  st(0)
    loc_0044FB3B:
        mov  ecx,DWORD PTR [esp+0x18]
        add  ecx,0x8
        add  ebp,0x2
        mov  DWORD PTR [esp+0x18],ecx
        inc  ebx
    loc_0044FB4A:
        mov  edi,DWORD PTR [esp+0x10]
        add  edi,0x2
        jne loc_0044FAA2
    loc_0044FB57:
        mov  eax,DWORD PTR [esp+0x14]
        xor  ebp,ebp
    loc_0044FB5D:
        push  eax
        call _free
        add  esp,0x4
        jmp loc_0044FB77
    loc_0044FB68:
        mov  ecx,DWORD PTR [esi+0x1014]
        mov  edx,DWORD PTR [ecx]
        call  DWORD PTR [edx]
        cmp  eax,0xffffffff
        je loc_0044FBA1
    loc_0044FB77:
        mov  eax,DWORD PTR [esi+0x4]
        movzx ecx,WORD PTR [eax+0x6]
        lea  ebx,[esi+0x4]
    loc_0044FB81:
        add  ecx,eax
        mov  DWORD PTR [ebx],ecx
    loc_0044FB85:
        mov  edx,DWORD PTR [ebx]
        fild  DWORD PTR [edx]
        fcomp DWORD PTR [esi]
        fnstsw ax
        test  ah,0x41
        jnp loc_0044E1E0
    loc_0044FB96:
        fld  DWORD PTR [esp+0x11c]
        fadd  DWORD PTR [esi]
        fstp  DWORD PTR [esi]
    loc_0044FBA1:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x108
        ret  0x4
    loc_0044FBB0:
        mov  DWORD PTR [ebx],ebp
    loc_0044FBB2:
        pop  edi
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        add  esp,0x108
        ret  0x4
        mov  edi,edi
        ja loc_0044FBC1
        inc  esp
        add  BYTE PTR [eax+0xc0044fb],dh
        loop loc_0044FC13
        add  BYTE PTR [ebx+eiz*8+0x44],bl
        add  BYTE PTR [edi],cl
        in   al,0x44
        add  cl,al
        jecxz 0x44fc1f
        add  BYTE PTR [edx-0x1d],dh
        inc  esp
        add  BYTE PTR [edi-0x1e],bl
        inc  esp
        add  BYTE PTR [edx-0x53ffbb1e],al
        loop loc_0044FC2F
        add  bl,dl
        loop loc_0044FC33
        add  dh,bh
        loop loc_0044FC37
        add  BYTE PTR [ecx],ch
        jecxz 0x44fc3b
        add  BYTE PTR [edx-0x1e],dh
        inc  esp
        add  BYTE PTR [ecx-0x6],dh
        inc  esp
        add  BYTE PTR [edi],dh
        in   al,0x44
        add  BYTE PTR [eax-0x1c],dl
        inc  esp
        add  BYTE PTR [ebp-0x1c],bl
        inc  esp
        add  BYTE PTR [edi-0x1c],bh
        inc  esp
        add  bh,cl
        in   al,0x44
    loc_0044FC13:
        add  dl,dh
        in   al,0x44
        add  BYTE PTR [eax-0x1b],cl
        inc  esp
        add  BYTE PTR [edi-0x19ffbb18],dl
        in   eax,0x44
        add  BYTE PTR [eax-0x17],al
        inc  esp
        add  BYTE PTR [eax-0x1a],bh
        inc  esp
        add  al,bh
        jmp FUN_E776FC76
        inc  esp
    loc_0044FC33:
        add  BYTE PTR [ecx-0x22ffbb16],ah
        out  0x44,eax
        add  BYTE PTR [ecx-0x15],bl
        inc  esp
        add  BYTE PTR [eax-0x3ffbb11],bh
        jmp loc_0044FC8B
        add  BYTE PTR [ecx-0x10],dh
        inc  esp
        add  BYTE PTR [edi+0x220044ec],bl
        int1
        inc  esp
        add  BYTE PTR [esi-0x13],cl
        inc  esp
        add  ch,al
        int1
        inc  esp
        add  ch,bh
        in   eax,dx
        inc  esp
        add  BYTE PTR [eax-0xe],ch
        inc  esp
        add  BYTE PTR [eax+0xb0044ee],ah
        repz inc esp
        add  BYTE PTR [edi-0x11],cl
        inc  esp
        add  dh,al
        repz inc esp
        add  BYTE PTR [ebx-0xc],al
        inc  esp
        add  bh,dh
        hlt
        inc  esp
        add  BYTE PTR [ebx+0x530044f5],ch
        test  BYTE PTR [eax+eax*1-0x5],0xf6
        inc  esp
        add  BYTE PTR [edx-0x8],ch
        inc  esp
    loc_0044FC8B:
        add  BYTE PTR [eax-0x18ffbb08],bl
        clc
        inc  esp
        add  BYTE PTR [ebx-0x7],cl
        inc  esp
        add  dh,ch
        stc
        inc  esp
        add  BYTE PTR [esi],bl
        in   al,0x44
        add  BYTE PTR [ebx+0x120044f7],ah
        clc
        inc  esp
        add  BYTE PTR [ecx+edi*8-0x5edffbc],ch
        inc  esp
        add  BYTE PTR [eax-0x5],ch
        inc  esp
        add  BYTE PTR [eax],al
        add  DWORD PTR [ebx],edi
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  eax,DWORD PTR [edx]
        add  eax,DWORD PTR [eax*1+0x9080706]
        or   cl,BYTE PTR [ebx]
        or   al,0xd
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        push  cs
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  edi,DWORD PTR [ebx]
        cmp  ecx,DWORD PTR [edi]
        adc  BYTE PTR [ecx],dl
        adc  dl,BYTE PTR [ebx]
        adc  al,0x3b
        cmp  edi,DWORD PTR [ebx]
        cmp  edx,DWORD PTR ds:0x19181716
        sbb  bl,BYTE PTR [ebx]
        sbb  al,0x1d
        push  ds
        pop  ds
        and  BYTE PTR [ecx],ah
        and  ah,BYTE PTR [ebx]
        and  al,0x25
        es daa
        sub  BYTE PTR [ecx],ch
        sub  ch,BYTE PTR [ebx]
        sub  al,0x2d
        cs das
        xor  BYTE PTR [ecx],dh
        xor  dh,BYTE PTR [ebx]
        xor  al,0x35
        ss aaa
        cmp  BYTE PTR [ecx],bh
        cmp  cl,ah
    }
}
