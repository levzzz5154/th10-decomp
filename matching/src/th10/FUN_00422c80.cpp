// 00422C80: FUN_00422c80
// Original size: 1360 bytes, actual code: 386 instructions
extern "C" void FUN_00405410(void);
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0040ac90(void);
extern "C" void FUN_0040ace0(void);
extern "C" void FUN_00422c30(void);
extern "C" void FUN_004243f0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00422c80(void) {
    __asm {
        sub  esp,0x14
        push  ebp
        mov  ebp,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [ebp+0x4]
        dec  eax
        cmp  eax,0x4
        ja loc_004231B3
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x4231bc]
        cmp  DWORD PTR [ebp+0x14],0xa
        jl loc_004231B0
        mov  eax,ds:0x477810
        mov  DWORD PTR [ebp+0x4],0x2
        mov  ecx,DWORD PTR [eax+0x5c]
        neg  ecx
        sbb  ecx,ecx
        add  ecx,0x3
        mov  eax,ecx
        test  eax,eax
        mov  DWORD PTR [ebp+0x2c],ecx
        mov  DWORD PTR [ebp+0xf4],0x1
        je loc_00422CE1
        jg loc_00422CDA
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00422CE8
    loc_00422CDA:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00422CE8
    loc_00422CE1:
        mov  DWORD PTR [ebp+0x24],0x0
    loc_00422CE8:
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x7
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        add  esp,0x14
        ret  0x4
        mov  edx,DWORD PTR [ebp+0x24]
        lea  ebx,[ebp+0x24]
        mov  DWORD PTR [ebx+0x4],edx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_00422D24
        test  BYTE PTR ds:0x474e34,al
        je loc_00422D2D
    loc_00422D24:
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_00422D2D:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_00422D41
        test  BYTE PTR ds:0x474e34,al
        je loc_00422D4A
    loc_00422D41:
        push  0x1
        mov  eax,ebx
        call FUN_0044bea0
    loc_00422D4A:
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ecx,DWORD PTR [ebx]
        cmp  eax,ecx
        je loc_00422D78
        xor  esi,esi
        mov  si,cx
        add  si,0x7
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00422D78:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_00422E28
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ebx,DWORD PTR [ebx]
        sub  ebx,0x0
        je loc_00422DF6
        dec  ebx
        je loc_00422DC8
        dec  ebx
        jne loc_00422E1E
        lea  esi,[ebp+0x1d4]
        mov  ebx,0x75
        lea  edi,[esp+0x28]
        call FUN_004497d0
        call FUN_004243f0
        mov  DWORD PTR [ebp+0x4],0x4
        jmp loc_00422E1E
    loc_00422DC8:
        lea  esi,[ebp+0x1d4]
        mov  ebx,0x74
        lea  edi,[esp+0x10]
        call FUN_004497d0
        call FUN_004243f0
        mov  ecx,DWORD PTR ds:0x477810
        mov  edx,DWORD PTR [ecx+0x5c]
        neg  edx
        sbb  edx,edx
        add  edx,0x4
        mov  DWORD PTR [ebp+0x4],edx
        jmp loc_00422E1E
    loc_00422DF6:
        lea  eax,[ebp+0x1d8]
        call FUN_00409e50
        lea  eax,[ebp+0x1d4]
        call FUN_00409e50
        lea  eax,[ebp+0x1dc]
        call FUN_00409e50
        mov  DWORD PTR [ebp+0x4],0x3
    loc_00422E1E:
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
    loc_00422E28:
        mov  eax,ds:0x474e36
        test  ah,0x40
        je loc_00422E9B
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        lea  esi,[ebp+0x1d4]
        mov  ebx,0x75
        lea  edi,[esp+0x14]
        call FUN_004497d0
        call FUN_004243f0
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],0x3
        call FUN_00405410
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_00422E89
        cmp  eax,0x2
        jg loc_00422E7F
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00422E90
    loc_00422E7F:
        mov  eax,0x2
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00422E90
    loc_00422E89:
        mov  DWORD PTR [ebp+0x24],0x2
    loc_00422E90:
        lea  eax,[ebp+0x1d8]
        call FUN_00409e50
    loc_00422E9B:
        mov  eax,ds:0x474e36
        test  ah,0x2
        je loc_00423059
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        lea  esi,[ebp+0x1d4]
        mov  ebx,0x74
        lea  edi,[esp+0x18]
        call FUN_004497d0
        call FUN_004243f0
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],0x3
        call FUN_00405410
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_00422F06
        cmp  eax,0x1
        jg loc_00422EF9
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423059
    loc_00422EF9:
        mov  eax,0x1
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423059
    loc_00422F06:
        mov  DWORD PTR [ebp+0x24],0x1
        jmp loc_00423059
        mov  eax,DWORD PTR [ebp+0x14]
        cmp  eax,0x14
        jl loc_004231B0
        jne loc_00422F69
        lea  eax,[ebp+0x24]
        call FUN_0044be20
        mov  DWORD PTR [ebp+0x2c],0x2
        mov  DWORD PTR [ebp+0xf4],0x1
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        je loc_00422F53
        cmp  ecx,0x1
        jg loc_00422F4A
        dec  ecx
        mov  DWORD PTR [eax],ecx
        jmp loc_00422F59
    loc_00422F4A:
        mov  ecx,0x1
        mov  DWORD PTR [eax],ecx
        jmp loc_00422F59
    loc_00422F53:
        mov  DWORD PTR [eax],0x1
    loc_00422F59:
        lea  eax,[ebp+0x1d4]
        mov  esi,0xe
        call FUN_00449470
    loc_00422F69:
        mov  eax,DWORD PTR [ebp+0x14]
        cmp  eax,0x1e
        jl loc_004231B0
        jne loc_00422F8C
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0xf
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
    loc_00422F8C:
        mov  eax,DWORD PTR [ebp+0x24]
        lea  ebx,[ebp+0x24]
        mov  DWORD PTR [ebx+0x4],eax
        mov  eax,0x10
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00422FB2
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_00422FB2:
        mov  eax,0x20
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00422FCF
        push  0x1
        mov  eax,ebx
        call FUN_0044bea0
    loc_00422FCF:
        mov  ecx,DWORD PTR [ebx+0x4]
        mov  eax,DWORD PTR [ebx]
        cmp  ecx,eax
        je loc_00422FFD
        xor  esi,esi
        mov  si,ax
        add  si,0xf
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00422FFD:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_00423059
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ebx,DWORD PTR [ebx]
        sub  ebx,0x0
        je loc_0042302F
        dec  ebx
        jne loc_0042304F
        mov  ebx,0x78
        lea  edi,[esp+0x1c]
        jmp loc_00423038
    loc_0042302F:
        mov  ebx,0x77
        lea  edi,[esp+0x20]
    loc_00423038:
        lea  esi,[ebp+0x1d4]
        call FUN_004497d0
        call FUN_004243f0
        mov  DWORD PTR [ebp+0x4],0x5
    loc_0042304F:
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
    loc_00423059:
        test  BYTE PTR ds:0x474e36,0x8
        je loc_004231B0
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_0042307C
        jg loc_00423075
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423083
    loc_00423075:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00423083
    loc_0042307C:
        mov  DWORD PTR [ebp+0x24],0x0
    loc_00423083:
        lea  eax,[ebp+0x1d8]
        call FUN_00409e50
        lea  eax,[ebp+0x1d4]
        call FUN_00409e50
        lea  eax,[ebp+0x1dc]
        call FUN_00409e50
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],0x3
        call FUN_00405410
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        add  esp,0x14
        ret  0x4
        cmp  DWORD PTR [ebp+0x14],0x14
        jl loc_004231B0
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,0x0
        lea  esi,[ebp+0x24]
        je loc_0042310B
        dec  eax
        jne loc_0042312F
        mov  eax,esi
        call FUN_0044be70
        movsx esi,WORD PTR [esi]
        add  si,0x7
        lea  eax,[ebp+0x1d4]
        call FUN_00449470
        push  0x0
        lea  eax,[ebp+0x10]
        mov  DWORD PTR [ebp+0x4],0x2
        call FUN_00405410
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        add  esp,0x14
        ret  0x4
    loc_0042310B:
        lea  eax,[ebp+0x1d8]
        call FUN_00409e50
        lea  eax,[ebp+0x1d4]
        call FUN_00409e50
        mov  eax,esi
        mov  DWORD PTR [ebp+0x4],0x3
        call FUN_0044be70
    loc_0042312F:
        push  0x0
        lea  eax,[ebp+0x10]
        call FUN_00405410
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        add  esp,0x14
        ret  0x4
        cmp  DWORD PTR [ebp+0x14],0xc
        jl loc_004231B0
        mov  eax,DWORD PTR [ebp+0x24]
        sub  eax,0x0
        mov  DWORD PTR [ebp+0x4],0x0
        je loc_004231A9
        dec  eax
        je loc_0042317D
        dec  eax
        jne loc_004231B0
        lea  eax,[ebp+0x1d4]
        call FUN_00409e50
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x491fb8,0xa
        pop  ebp
        add  esp,0x14
        ret  0x4
    loc_0042317D:
        lea  eax,[ebp+0x1d8]
        call FUN_00409e50
        lea  eax,[ebp+0x1d4]
        call FUN_00409e50
        push  0x4
        mov  eax,0x491c28
        call FUN_0040ac90
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        add  esp,0x14
        ret  0x4
    loc_004231A9:
        mov  esi,ebp
        call FUN_00422c30
    loc_004231B0:
        pop  edi
        pop  esi
        pop  ebx
    loc_004231B3:
        pop  ebp
        add  esp,0x14
        ret  0x4
        mov  edi,edi
        lahf
        sub  al,0x42
        add  BYTE PTR [edi],al
        sub  eax,0x31430042
        inc  edx
        add  BYTE PTR [edx],dl
        das
        inc  edx
        _emit 0
        _emit 0xbf
        xor  BYTE PTR [edx+0x0],al
    }
}
