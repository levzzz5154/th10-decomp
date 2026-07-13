// 00439890: FUN_00439890
// Original size: 1168 bytes, actual code: 304 instructions
extern "C" void FUN_00439d20(void);
extern "C" void FUN_0043bcd0(void);
extern "C" void FUN_0044b810(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void D3DXMatrixLookAtLH(void);
extern "C" void D3DXMatrixPerspectiveFovLH(void);

extern "C" __declspec(naked) void FUN_00439890(void) {
    __asm {
        sub  esp,0x70
        push  ebx
        push  ebp
        push  esi
        push  edi
        xor  eax,eax
        lea  edx,[esp+0x38]
        push  edx
        mov  ecx,0xe
        lea  edi,[esp+0x4c]
        rep stosd
        mov  eax,ds:0x491c2c
        mov  ecx,DWORD PTR [eax]
        xor  ebx,ebx
        push  ebx
        push  eax
        mov  BYTE PTR [esp+0x1f],0x1
        call  DWORD PTR [ecx+0x20]
        cmp  BYTE PTR ds:0x491d65,bl
        mov  edi,0x80000000
        jne loc_00439991
        test  BYTE PTR ds:0x491d78,0x1
        je loc_004398E7
        mov  DWORD PTR [esp+0x50],0x17
        mov  BYTE PTR ds:0x491d62,0x1
        jmp loc_00439920
    loc_004398E7:
        mov  al,ds:0x491d62
        cmp  al,0xff
        jne loc_00439912
        push  0x46f640
        mov  ecx,0x474f70
        mov  DWORD PTR [esp+0x54],0x16
        mov  BYTE PTR ds:0x491d62,bl
        call FUN_0044b810
        add  esp,0x4
        jmp loc_00439920
    loc_00439912:
        xor  ecx,ecx
        cmp  al,bl
        setne cl
        add  ecx,0x16
        mov  DWORD PTR [esp+0x50],ecx
    loc_00439920:
        cmp  BYTE PTR ds:0x492518,bl
        je loc_00439935
        mov  ebp,0x1
        mov  DWORD PTR ds:0x491fdc,ebp
        jmp loc_0043996E
    loc_00439935:
        cmp  DWORD PTR ds:0x491fdc,ebx
        jne loc_00439969
        mov  esi,0x1
        push  0x46f614
        mov  ecx,0x474f70
        mov  DWORD PTR [esp+0x7c],0x3c
        mov  DWORD PTR [esp+0x80],esi
        call FUN_0044b810
        add  esp,0x4
        mov  DWORD PTR [esp+0x60],esi
        jmp loc_004399A6
    loc_00439969:
        mov  ebp,0x1
    loc_0043996E:
        push  0x46f5f0
        mov  ecx,0x474f70
        mov  DWORD PTR [esp+0x7c],ebx
        mov  DWORD PTR [esp+0x64],ebp
        mov  DWORD PTR [esp+0x80],edi
        call FUN_0044b810
        add  esp,0x4
        jmp loc_004399AB
    loc_00439991:
        mov  edx,DWORD PTR [esp+0x44]
        mov  eax,0x1
        mov  DWORD PTR [esp+0x50],edx
        mov  DWORD PTR [esp+0x60],eax
        mov  DWORD PTR [esp+0x68],eax
    loc_004399A6:
        mov  ebp,0x1
    loc_004399AB:
        mov  eax,ds:0x491ff4
        or   eax,0x2
        mov  DWORD PTR [esp+0x48],0x280
        mov  DWORD PTR [esp+0x4c],0x1e0
        mov  DWORD PTR [esp+0x6c],ebp
        mov  DWORD PTR [esp+0x70],0x50
        mov  DWORD PTR [esp+0x74],ebp
        mov  ds:0x491ff4,eax
        mov  DWORD PTR ds:0x491fe0,ebp
        xor  esi,esi
    loc_004399E0:
        test  BYTE PTR ds:0x491d78,0x2
        jne loc_00439A65
        mov  eax,ds:0x491c2c
        mov  ecx,DWORD PTR [eax]
        push  0x491c30
        lea  edx,[esp+0x4c]
        push  edx
        mov  edx,DWORD PTR ds:0x4924f0
        push  0x40
        push  edx
        push  ebp
        push  ebx
        push  eax
        call  DWORD PTR [ecx+0x40]
        test  eax,eax
        jge loc_00439B4F
        cmp  esi,ebx
        je loc_00439A27
        push  0x46f5cc
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00439A27:
        mov  eax,ds:0x491c2c
        mov  ecx,DWORD PTR [eax]
        push  0x491c30
        lea  edx,[esp+0x4c]
        push  edx
        mov  edx,DWORD PTR ds:0x4924f0
        push  0x20
        push  edx
        push  ebp
        push  ebx
        push  eax
        call  DWORD PTR [ecx+0x40]
        test  eax,eax
        jge loc_00439B33
        cmp  esi,ebx
        je loc_00439A65
        push  0x46f5ac
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00439A65:
        mov  eax,ds:0x491c2c
        mov  ecx,DWORD PTR [eax]
        push  0x491c30
        lea  edx,[esp+0x4c]
        push  edx
        mov  edx,DWORD PTR ds:0x4924f0
        push  0x20
        push  edx
        push  0x2
        push  ebx
        push  eax
        call  DWORD PTR [ecx+0x40]
        test  eax,eax
        jge loc_00439B13
        cmp  DWORD PTR ds:0x491fdc,ebx
        jne loc_00439AB9
        push  0x46f584
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        mov  DWORD PTR [esp+0x78],ebx
        mov  DWORD PTR ds:0x491fe0,ebx
        mov  esi,ebp
        jmp loc_004399E0
    loc_00439AB9:
        cmp  DWORD PTR [esp+0x7c],edi
        jne loc_00439AE2
        push  0x46f54c
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        mov  DWORD PTR [esp+0x7c],ebp
        mov  DWORD PTR [esp+0x60],0x3
        jmp loc_004399E0
    loc_00439AE2:
        push  0x46f514
        mov  edi,0x474f70
        call FUN_0044b8e0
        mov  eax,ds:0x491c2c
        add  esp,0x4
        cmp  eax,ebx
        je loc_00439B09
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR ds:0x491c2c,ebx
    loc_00439B09:
        pop  edi
        pop  esi
        mov  eax,ebp
        pop  ebp
        pop  ebx
        add  esp,0x70
        ret
    loc_00439B13:
        push  0x46f4d8
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  eax,ds:0x491ff4
        add  esp,0x4
        and  eax,0xfffffffe
        mov  BYTE PTR [esp+0x13],bl
        jmp loc_00439B68
    loc_00439B33:
        push  0x46f4c4
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  eax,ds:0x491ff4
        add  esp,0x4
        and  eax,0xfffffffe
        jmp loc_00439B68
    loc_00439B4F:
        push  0x46f4a8
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  eax,ds:0x491ff4
        add  esp,0x4
        or   eax,ebp
    loc_00439B68:
        fld  QWORD PTR ds:0x470c00
        mov  ds:0x491ff4,eax
        fptan
        lea  edx,[esp+0x14]
        push  edx
        mov  ecx,0xe
        lea  esi,[esp+0x4c]
        mov  edi,0x491d0c
        lea  eax,[esp+0x24]
        rep movsd
        push  eax
        lea  ecx,[esp+0x34]
        push  ecx
        push  0x491c74
        mov  DWORD PTR [esp+0x3c],0x43a00000
        mov  DWORD PTR [esp+0x40],0xc3700000
        mov  DWORD PTR [esp+0x30],0x43a00000
        mov  DWORD PTR [esp+0x34],0xc3700000
        mov  DWORD PTR [esp+0x38],0x0
        mov  DWORD PTR [esp+0x24],0x0
        mov  DWORD PTR [esp+0x28],0x3f800000
        mov  DWORD PTR [esp+0x2c],0x0
        fstp  st(0)
        fdivr DWORD PTR ds:0x470bfc
        fchs
        fstp  DWORD PTR [esp+0x44]
        call D3DXMatrixLookAtLH
        push  0x461c4000
        push  0x42c80000
        push  0x3faaaaab
        push  0x3f060a92
        push  0x491cb4
        call D3DXMatrixPerspectiveFovLH
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x491c74
        push  0x2
        push  eax
        call  DWORD PTR [edx+0xb0]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x491cb4
        push  0x3
        push  eax
        call  DWORD PTR [ecx+0xb0]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x491cf4
        push  eax
        call  DWORD PTR [edx+0xc0]
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x492000
        push  eax
        call  DWORD PTR [ecx+0x1c]
        test  BYTE PTR ds:0x492090,0x40
        jne loc_00439C72
        push  0x46f458
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00439C72:
        cmp  DWORD PTR ds:0x492058,0x100
        ja loc_00439C90
        push  0x46f408
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00439C90:
        test  BYTE PTR ds:0x491d78,0x1
        jne loc_00439CF2
        cmp  BYTE PTR [esp+0x13],bl
        je loc_00439CF2
        mov  ecx,DWORD PTR [esp+0x50]
        mov  eax,ds:0x491c2c
        mov  edx,DWORD PTR [eax]
        push  0x15
        push  0x3
        push  ebx
        push  ecx
        push  ebp
        push  ebx
        push  eax
        call  DWORD PTR [edx+0x28]
        test  eax,eax
        jne loc_00439CC3
        or   DWORD PTR ds:0x491ff4,0x4
        jmp loc_00439CF2
    loc_00439CC3:
        mov  esi,DWORD PTR ds:0x491ff4
        mov  edx,DWORD PTR ds:0x491d78
        or   edx,ebp
        and  esi,0xfffffffb
        push  0x46f3c0
        mov  ecx,0x474f70
        mov  DWORD PTR ds:0x491ff4,esi
        mov  DWORD PTR ds:0x491d78,edx
        call FUN_0044b810
        add  esp,0x4
    loc_00439CF2:
        call FUN_00439d20
        push  0xff000000
        call FUN_0043bcd0
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR ds:0x4924f4,ebx
        mov  DWORD PTR ds:0x491fe4,ebx
        xor  eax,eax
        pop  ebx
        add  esp,0x70
        ret
    }
}
