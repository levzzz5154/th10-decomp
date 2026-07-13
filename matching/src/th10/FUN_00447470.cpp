// 00447470: FUN_00447470
// Original size: 656 bytes, actual code: 200 instructions
extern "C" void FUN_00446eb0(void);
extern "C" void FUN_00446f40(void);
extern "C" void FUN_00447050(void);
extern "C" void FUN_00447940(void);
extern "C" void FUN_0044b8e0(void);

extern "C" __declspec(naked) void FUN_00447470(void) {
    __asm {
        sub  esp,0x68
        push  ebp
        mov  ebp,DWORD PTR [esp+0x80]
        test  ebp,ebp
        push  edi
        jne loc_00447487
        push  0x470274
        jmp loc_00447492
    loc_00447487:
        cmp  DWORD PTR [ebp+0x28],0x4
        je loc_004474AA
        push  0x470254
    loc_00447492:
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        pop  edi
        or   eax,0xffffffff
        pop  ebp
        add  esp,0x68
        ret  0x14
    loc_004474AA:
        mov  cl,BYTE PTR [ebp+0x34]
        shl  eax,0x4
        test  cl,cl
        push  ebx
        push  esi
        mov  DWORD PTR [esp+0x8c],eax
        jne loc_0044753A
        mov  edi,DWORD PTR [ebp+0x1c]
        mov  cl,BYTE PTR [edi+ebp*1]
        add  edi,ebp
        cmp  cl,0x40
        jne loc_004474EC
        mov  ebx,DWORD PTR [esp+0x80]
        mov  edi,DWORD PTR [ebx+0x120]
        mov  esi,DWORD PTR [ebp+0x14]
        mov  ecx,DWORD PTR [ebp+0x10]
        mov  edx,DWORD PTR [ebp+0xc]
        add  edi,eax
        call FUN_00447050
        jmp loc_00447588
    loc_004474EC:
        mov  ecx,DWORD PTR [ebp+0xc]
        mov  edx,DWORD PTR [ebp+0x18]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x84]
        mov  esi,DWORD PTR [ecx+0x120]
        push  edx
        mov  edx,DWORD PTR [esp+0x84]
        add  esi,eax
        mov  eax,DWORD PTR [ebp+0x14]
        push  edx
        mov  edx,DWORD PTR [ebp+0x10]
        call FUN_00446eb0
        test  eax,eax
        je loc_00447581
        push  edi
        push  0x4701b0
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x8
        pop  esi
        pop  ebx
        pop  edi
        or   eax,0xffffffff
        pop  ebp
        add  esp,0x68
        ret  0x14
    loc_0044753A:
        mov  ecx,DWORD PTR [ebp+0x10]
        mov  edx,DWORD PTR [ebp+0xc]
        push  ecx
        mov  ecx,DWORD PTR [ebp+0x30]
        push  edx
        mov  edx,DWORD PTR [esp+0x88]
        mov  ebx,DWORD PTR [edx+0x120]
        add  ebx,eax
        mov  eax,DWORD PTR [ebp+0x14]
        add  ecx,ebp
        call FUN_00446f40
        test  eax,eax
        je loc_00447581
        push  0x47016c
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        pop  esi
        pop  ebx
        pop  edi
        or   eax,0xffffffff
        pop  ebp
        add  esp,0x68
        ret  0x14
    loc_00447581:
        mov  ebx,DWORD PTR [esp+0x80]
    loc_00447588:
        mov  eax,DWORD PTR [ebx+0x120]
        mov  edx,DWORD PTR [ebp+0x2c]
        mov  edi,DWORD PTR [esp+0x8c]
        mov  eax,DWORD PTR [edi+eax*1]
        mov  ecx,DWORD PTR [eax]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x1c]
        mov  eax,DWORD PTR [ebx+0x120]
        mov  eax,DWORD PTR [edi+eax*1]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x24]
        mov  edx,DWORD PTR [ebx+0x120]
        mov  eax,DWORD PTR [edi+edx*1]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x14]
        push  edx
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x44]
        cmp  DWORD PTR [ebp+0x0],0x0
        lea  esi,[ebp+0x40]
        mov  DWORD PTR [esp+0x7c],0x0
        jle loc_004476B8
        jmp loc_004475F0
    loc_004475DE:
        mov  edi,DWORD PTR [esp+0x8c]
        jmp loc_004475F0
        nop
        mov  edi,edi
    loc_004475F0:
        mov  ecx,DWORD PTR [ebx]
        fild  DWORD PTR [esp+0x2c]
        mov  edx,DWORD PTR [ebx+0x120]
        mov  eax,DWORD PTR [esi]
        mov  DWORD PTR [esp+0x34],ecx
        mov  ecx,DWORD PTR [edi+edx*1]
        mov  edx,DWORD PTR [esp+0x2c]
        add  eax,ebp
        test  edx,edx
        mov  DWORD PTR [esp+0x38],ecx
        jge loc_00447619
        fadd  DWORD PTR ds:0x470b98
    loc_00447619:
        fild  DWORD PTR [ebp+0xc]
        mov  ecx,DWORD PTR [esp+0x30]
        test  ecx,ecx
        fdivr st,st(1)
        fstp  DWORD PTR [esp+0x6c]
        fild  DWORD PTR [esp+0x30]
        jge loc_00447634
        fadd  DWORD PTR ds:0x470b98
    loc_00447634:
        fild  DWORD PTR [ebp+0x10]
        mov  edi,DWORD PTR [esp+0x84]
        mov  edx,DWORD PTR [esp+0x80]
        lea  ebx,[esp+0x34]
        fdivr st,st(1)
        fstp  DWORD PTR [esp+0x70]
        fld  DWORD PTR [esp+0x6c]
        fmul  DWORD PTR [eax+0x4]
        fstp  DWORD PTR [esp+0x3c]
        fld  DWORD PTR [esp+0x70]
        fmul  DWORD PTR [eax+0x8]
        fstp  DWORD PTR [esp+0x40]
        fld  DWORD PTR [eax+0xc]
        fadd  DWORD PTR [eax+0x4]
        fmul  DWORD PTR [esp+0x6c]
        fstp  DWORD PTR [esp+0x44]
        fld  DWORD PTR [eax+0x10]
        fadd  DWORD PTR [eax+0x8]
        mov  eax,edi
        fmul  DWORD PTR [esp+0x70]
        fstp  DWORD PTR [esp+0x48]
        fxch  st(1)
        fstp  DWORD PTR [esp+0x50]
        fstp  DWORD PTR [esp+0x4c]
        call FUN_00447940
        mov  eax,DWORD PTR [esp+0x7c]
        mov  ecx,DWORD PTR [ebp+0x0]
        mov  ebx,DWORD PTR [esp+0x80]
        inc  edi
        inc  eax
        add  esi,0x4
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x84],edi
        mov  DWORD PTR [esp+0x7c],eax
        jl loc_004475DE
    loc_004476B8:
        mov  eax,DWORD PTR [ebp+0x4]
        xor  edx,edx
        test  eax,eax
        jle loc_004476EB
        mov  eax,DWORD PTR [esp+0x88]
        shl  eax,0x2
        lea  ecx,[esi+0x4]
        mov  edi,edi
    loc_004476D0:
        mov  esi,DWORD PTR [ecx]
        mov  edi,DWORD PTR [ebx+0x11c]
        add  esi,ebp
        mov  DWORD PTR [eax+edi*1],esi
        mov  esi,DWORD PTR [ebp+0x4]
        add  eax,0x4
        inc  edx
        add  ecx,0x8
        cmp  edx,esi
        jl loc_004476D0
    loc_004476EB:
        pop  esi
        pop  ebx
        pop  edi
        mov  eax,0x1
        pop  ebp
        add  esp,0x68
        ret  0x14
    }
}
