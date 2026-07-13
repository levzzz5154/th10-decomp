// 00420870: FUN_00420870
// Original size: 544 bytes, actual code: 131 instructions
extern "C" void FUN_00418c40(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b540(void);
extern "C" void FUN_0044b810(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00420870(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  edi
        mov  edx,0x491d48
        call FUN_00418c40
        push  0x1
        lea  eax,[esp+0x10]
        push  eax
        mov  eax,ebx
        call FUN_0044b360
        test  eax,eax
        jne loc_0042089C
        push  0x46de7c
        jmp loc_00420942
    loc_0042089C:
        push  esi
        mov  esi,eax
        mov  ecx,0xd
        mov  edi,0x491d48
        push  eax
        rep movsd
        call _free
        mov  al,ds:0x491d62
        add  esp,0x4
        cmp  al,0x2
        pop  esi
        jae loc_0042093D
        mov  cl,BYTE PTR ds:0x491d63
        mov  al,0x3
        cmp  cl,al
        jae loc_0042093D
        cmp  BYTE PTR ds:0x491d64,0x2
        jae loc_0042093D
        cmp  BYTE PTR ds:0x491d65,0x2
        jae loc_0042093D
        cmp  BYTE PTR ds:0x491d66,al
        jae loc_0042093D
        cmp  BYTE PTR ds:0x491d67,al
        jae loc_0042093D
        cmp  DWORD PTR ds:0x491d48,0x100003
        jne loc_0042093D
        cmp  DWORD PTR [esp+0xc],0x34
        jne loc_0042093D
        mov  ecx,DWORD PTR ds:0x491d4c
        mov  edx,DWORD PTR ds:0x491d50
        mov  eax,ds:0x491d54
        mov  DWORD PTR ds:0x474e88,ecx
        mov  ecx,DWORD PTR ds:0x491d58
        mov  DWORD PTR ds:0x474e8c,edx
        mov  dx,WORD PTR ds:0x491d5c
        mov  ds:0x474e90,eax
        mov  DWORD PTR ds:0x474e94,ecx
        mov  WORD PTR ds:0x474e98,dx
        jmp loc_00420959
    loc_0042093D:
        push  0x46de48
    loc_00420942:
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        mov  edx,0x491d48
        call FUN_00418c40
    loc_00420959:
        test  BYTE PTR [ebp+0x150],0x4
        mov  DWORD PTR [ebp+0x3b4],0x0
        je loc_0042097E
        push  0x46de2c
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_0042097E:
        test  BYTE PTR [ebp+0x150],0x1
        je loc_00420999
        push  0x46de04
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00420999:
        mov  al,BYTE PTR [ebp+0x13d]
        test  al,al
        je loc_004209B5
        push  0x46dde4
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_004209B5:
        test  BYTE PTR [ebp+0x150],0x2
        je loc_004209D0
        push  0x46ddbc
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_004209D0:
        test  BYTE PTR [ebp+0x150],0x8
        je loc_004209EB
        push  0x46dd84
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_004209EB:
        test  BYTE PTR [ebp+0x150],0x10
        je loc_00420A06
        push  0x46dd64
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00420A06:
        test  BYTE PTR [ebp+0x150],0x20
        je loc_00420A2B
        push  0x46dd4c
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        mov  DWORD PTR ds:0x491fdc,0x1
    loc_00420A2B:
        test  BYTE PTR [ebp+0x150],0x40
        je loc_00420A46
        push  0x46dd28
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_00420A46:
        push  0x491d48
        push  ebx
        mov  edi,0x34
        call FUN_0044b540
        test  eax,eax
        je loc_00420A7F
        push  ebx
        push  0x46dd08
        mov  edi,0x474f70
        call FUN_0044b8e0
        push  0x46dcb0
        call FUN_0044b8e0
        add  esp,0xc
        pop  edi
        or   eax,0xffffffff
        pop  ebp
        ret  0x4
    loc_00420A7F:
        pop  edi
        xor  eax,eax
        pop  ebp
        ret  0x4
    }
}
