// 00438AD0: GameMain
// Original size: 1552 bytes, actual code: 416 instructions
extern "C" void FUN_00420270(void);
extern "C" void FUN_00420470(void);
extern "C" void FUN_00420870(void);
extern "C" void FUN_00438880(void);
extern "C" void FUN_00438a30(void);
extern "C" void FUN_004392e0(void);
extern "C" void FUN_00439390(void);
extern "C" void FUN_00439540(void);
extern "C" void FUN_00439730(void);
extern "C" void FUN_00439890(void);
extern "C" void FUN_00439d20(void);
extern "C" void FUN_00439ff0(void);
extern "C" void FUN_0043a1c0(void);
extern "C" void FUN_0043a910(void);
extern "C" void FUN_0043ae20(void);
extern "C" void FUN_0043cc40(void);
extern "C" void FUN_0043d120(void);
extern "C" void FUN_0043ddf0(void);
extern "C" void GameStateInit(void);
extern "C" void FUN_00446220(void);
extern "C" void FUN_00449aa0(void);
extern "C" void FUN_0044a0c0(void);
extern "C" void FUN_0044b080(void);
extern "C" void FUN_0044b540(void);
extern "C" void FUN_0044b810(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void Direct3DCreate9(void);
extern "C" void WINNLSEnableIME(void);
extern "C" void _free(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void GameMain(void) {
    __asm {
        sub  esp,0x20
        mov  eax,DWORD PTR [esp+0x24]
        push  ebp
        push  esi
        push  edi
        xor  ebp,ebp
        push  0xa004
        mov  DWORD PTR [esp+0x10],ebp
        mov  ds:0x4924f8,eax
        call operator_new
        mov  edx,eax
        add  esp,0x4
        cmp  edx,ebp
        je loc_00438B0B
        mov  ecx,0x2801
        xor  eax,eax
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [edx+0xa000],ebp
        jmp loc_00438B0D
    loc_00438B0B:
        xor  edx,edx
    loc_00438B0D:
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b8
        mov  DWORD PTR ds:0x491be0,edx
        mov  esi,0x492274
        mov  edi,0x7
    loc_00438B24:
        push  esi
        call  ebx
        add  esi,0x18
        dec  edi
        jne loc_00438B24
        push  0x46f77c
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        call FUN_00439ff0
        cmp  eax,0xffffffff
        je loc_00438DD0
        mov  esi,DWORD PTR [esp+0x34]
        mov  DWORD PTR ds:0x491c28,esi
        call FUN_004392e0
        push  0x491c28
        mov  ebx,0x46f770
        call FUN_00420870
        test  eax,eax
        jne loc_00438DCE
        mov  eax,ds:0x491d78
        test  ah,0x1
        je loc_00438B9E
        push  0x0
        push  0x43a3a0
        push  0x0
        push  0xcb
        push  esi
        call  DWORD PTR ds:0x466264
        cmp  eax,0x6
        setne cl
        mov  BYTE PTR ds:0x491d65,cl
    loc_00438B9E:
        call FUN_0043a1c0
        xor  ebp,ebp
    loc_00438BA5:
        push  0x48
        call operator_new
        add  esp,0x4
        cmp  eax,ebp
        je loc_00438BBA
        call FUN_00449aa0
        jmp loc_00438BBC
    loc_00438BBA:
        xor  eax,eax
    loc_00438BBC:
        push  0x20
        mov  ds:0x491be4,eax
        call Direct3DCreate9
        cmp  eax,ebp
        mov  ds:0x491c2c,eax
        jne loc_00438BE8
        push  0x46f6a0
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        jmp loc_00438DD0
    loc_00438BE8:
        mov  ebx,esi
        call FUN_00439730
        test  eax,eax
        jne loc_00438DCE
        mov  edx,DWORD PTR ds:0x4924f0
        push  0x4977b0
        push  eax
        push  0x492590
        push  0x43ccf0
        push  eax
        mov  ecx,0x14b4
        mov  edi,0x492590
        rep stosd
        push  eax
        mov  DWORD PTR ds:0x4977b8,edx
        call  DWORD PTR ds:0x466118
        mov  ds:0x4977a8,eax
        call FUN_00439890
        test  eax,eax
        jne loc_00438DCE
        call FUN_0044a0c0
        call FUN_0044b080
        push  0x732460
        call operator_new
        xor  ebx,ebx
        add  esp,0x4
        cmp  eax,ebx
        je loc_00438C5E
        push  eax
        call GameStateInit
        jmp loc_00438C60
    loc_00438C5E:
        xor  eax,eax
    loc_00438C60:
        mov  ds:0x491c10,eax
        cmp  BYTE PTR ds:0x491d65,bl
        jne loc_00438C82
        push  ebx
        push  ebx
        call WINNLSEnableIME
        push  ebx
        call  DWORD PTR ds:0x466230
        push  ebx
        call  DWORD PTR ds:0x466224
    loc_00438C82:
        fld  QWORD PTR ds:0x470b70
        fstp  QWORD PTR ds:0x492540
        call FUN_00439540
        mov  eax,ds:0x4924f0
        fst  QWORD PTR ds:0x492540
        fst  QWORD PTR ds:0x492538
        push  eax
        fst  QWORD PTR ds:0x492528
        fstp  QWORD PTR ds:0x492530
        call  DWORD PTR ds:0x4661f0
        call FUN_00420470
        cmp  eax,ebx
        mov  DWORD PTR [esp+0x10],eax
        je loc_00438CDA
        cmp  eax,0xffffffff
        je loc_00438D95
        mov  DWORD PTR [esp+0x10],0x2
        jmp loc_00438D95
    loc_00438CDA:
        cmp  DWORD PTR ds:0x4924f4,ebx
        mov  DWORD PTR [esp+0x10],ebx
        mov  BYTE PTR ds:0x492504,0xfc
        jne loc_00438D95
    loc_00438CF1:
        push  0x1
        push  ebx
        push  ebx
        push  ebx
        lea  ecx,[esp+0x24]
        push  ecx
        call  DWORD PTR ds:0x46623c
        test  eax,eax
        je loc_00438D1D
        lea  edx,[esp+0x14]
        push  edx
        call  DWORD PTR ds:0x46622c
        lea  eax,[esp+0x14]
        push  eax
        call  DWORD PTR ds:0x466254
        jmp loc_00438D89
    loc_00438D1D:
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xc]
        cmp  eax,ebx
        jne loc_00438D48
        push  0x4924f0
        call FUN_00439390
        cmp  eax,ebx
        mov  DWORD PTR [esp+0x10],eax
        jne loc_00438D95
        mov  eax,ds:0x491ff4
        and  eax,0xffffffef
        jmp loc_00438D84
    loc_00438D48:
        cmp  eax,0x88760869
        jne loc_00438D89
        mov  eax,ds:0x491c10
        call FUN_00438a30
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x491d0c
        push  eax
        call  DWORD PTR [edx+0x40]
        test  eax,eax
        jne loc_00438D95
        call FUN_00439d20
        mov  eax,ds:0x491ff4
        mov  DWORD PTR ds:0x491fd4,0x3
        or   eax,0x10
    loc_00438D84:
        mov  ds:0x491ff4,eax
    loc_00438D89:
        cmp  DWORD PTR ds:0x4924f4,ebx
        je loc_00438CF1
    loc_00438D95:
        mov  eax,0x491c28
        call FUN_00420270
        mov  eax,ds:0x491be4
        cmp  eax,ebx
        mov  esi,eax
        je loc_00438DB9
        push  eax
        call FUN_00438880
        push  esi
        call _free
        add  esp,0x4
    loc_00438DB9:
        mov  DWORD PTR ds:0x491be4,ebx
        nop
    loc_00438DC0:
        push  0x492590
        call FUN_0043ddf0
        test  eax,eax
        jne loc_00438DC0
    loc_00438DCE:
        xor  ebp,ebp
    loc_00438DD0:
        mov  edi,0x2
        mov  esi,0x492590
        mov  DWORD PTR ds:0x4977b4,edi
        call FUN_0043cc40
        mov  eax,esi
        call FUN_0043d120
        mov  eax,ds:0x491c10
        cmp  eax,ebp
        mov  esi,eax
        je loc_00438E06
        push  eax
        call FUN_00446220
        push  esi
        call _free
        add  esp,0x4
    loc_00438E06:
        mov  eax,ds:0x491c30
        cmp  eax,ebp
        mov  DWORD PTR ds:0x491c10,ebp
        je loc_00438E35
        mov  ecx,DWORD PTR [eax]
        push  0x491d0c
        push  eax
        call  DWORD PTR [ecx+0x40]
        mov  eax,ds:0x491c30
        cmp  eax,ebp
        je loc_00438E35
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR ds:0x491c30,ebp
    loc_00438E35:
        mov  eax,ds:0x491c2c
        cmp  eax,ebp
        je loc_00438E4A
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR ds:0x491c2c,ebp
    loc_00438E4A:
        mov  eax,ds:0x4924f0
        cmp  eax,ebp
        je loc_00438E7F
        push  ebp
        push  eax
        call  DWORD PTR ds:0x46624c
        mov  edx,DWORD PTR ds:0x4924f0
        push  ebp
        push  ebp
        push  ebp
        push  ebp
        push  ebp
        push  edx
        call  DWORD PTR ds:0x4661f4
        mov  eax,ds:0x4924f0
        push  eax
        call  DWORD PTR ds:0x466220
        mov  DWORD PTR ds:0x4924f0,ebp
    loc_00438E7F:
        push  0x1
        call  DWORD PTR ds:0x466230
        cmp  DWORD PTR [esp+0x10],edi
        jne loc_00438EFA
        mov  ecx,0x474f70
        push  0x46f6f0
        mov  DWORD PTR ds:0x476f70,ecx
        mov  BYTE PTR ds:0x474f70,0x0
        call FUN_0044b810
        mov  al,ds:0x491d65
        add  esp,0x4
        test  al,al
        jne loc_00438EBD
        push  0x1
        push  ebp
        call WINNLSEnableIME
    loc_00438EBD:
        mov  edi,DWORD PTR ds:0x46623c
        mov  esi,0x3c
    loc_00438EC8:
        push  0x1
        push  ebp
        push  ebp
        push  ebp
        lea  ecx,[esp+0x24]
        push  ecx
        call  edi
        test  eax,eax
        je loc_00438EEE
        lea  edx,[esp+0x14]
        push  edx
        call  DWORD PTR ds:0x46622c
        lea  eax,[esp+0x14]
        push  eax
        call  DWORD PTR ds:0x466254
    loc_00438EEE:
        dec  esi
        jne loc_00438EC8
        mov  esi,DWORD PTR [esp+0x34]
        jmp loc_00438BA5
    loc_00438EFA:
        push  0x491d48
        push  0x46f770
        mov  edi,0x34
        call FUN_0044b540
        mov  edi,DWORD PTR ds:0x491fe8
        cmp  edi,ebp
        pop  ebx
        je loc_00438F3D
        call FUN_0043ae20
        mov  eax,ds:0x491fe8
        cmp  eax,ebp
        mov  esi,eax
        je loc_00438F37
        call FUN_0043a910
        push  esi
        call _free
        add  esp,0x4
    loc_00438F37:
        mov  DWORD PTR ds:0x491fe8,ebp
    loc_00438F3D:
        cmp  DWORD PTR ds:0x476f70,0x474f70
        je loc_00438F9A
        push  0x46f7cc
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  al,ds:0x476f74
        add  esp,0x4
        test  al,al
        je loc_00438F77
        push  0x10
        push  0x46f7c8
        push  0x474f70
        push  ebp
        call  DWORD PTR ds:0x466234
    loc_00438F77:
        mov  eax,0x474f70
        lea  edx,[eax+0x1]
        nop
    loc_00438F80:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00438F80
        sub  eax,edx
        push  0x474f70
        push  0x46f7bc
        mov  edi,eax
        call FUN_0044b540
    loc_00438F9A:
        mov  ebp,DWORD PTR ds:0x4660bc
        mov  esi,0x492274
        mov  edi,0x7
        lea  ebx,[ebx+0x0]
    loc_00438FB0:
        push  esi
        call  ebp
        add  esi,0x18
        dec  edi
        jne loc_00438FB0
        mov  ecx,DWORD PTR ds:0x49251c
        mov  esi,DWORD PTR ds:0x466258
        push  0x2
        push  0x0
        push  ecx
        push  0x11
        call  esi
        mov  edx,DWORD PTR ds:0x492520
        push  0x2
        push  0x0
        push  edx
        push  0x55
        call  esi
        mov  eax,ds:0x492524
        push  0x2
        push  0x0
        push  eax
        push  0x56
        call  esi
        push  0x1
        push  0x0
        call WINNLSEnableIME
        mov  eax,ds:0x491be0
        test  eax,eax
        mov  edi,eax
        je loc_00439032
        mov  ecx,DWORD PTR [eax+0xa000]
        test  ecx,ecx
        je loc_00439029
        xor  esi,esi
        jmp loc_00439010
        nop
    loc_00439010:
        mov  eax,DWORD PTR [edi+esi*4]
        test  eax,eax
        je loc_00439020
        push  eax
        call _free
        add  esp,0x4
    loc_00439020:
        inc  esi
        cmp  esi,0x2800
        jl loc_00439010
    loc_00439029:
        push  edi
        call _free
        add  esp,0x4
    loc_00439032:
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        add  esp,0x20
        ret  0x10
    }
}
