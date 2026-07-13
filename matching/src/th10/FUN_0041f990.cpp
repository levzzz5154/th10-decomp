// 0041F990: FUN_0041f990
// Original size: 304 bytes, actual code: 76 instructions
extern "C" void FUN_00401440(void);
extern "C" void FUN_0041f8d0(void);
extern "C" void FUN_0042af20(void);
extern "C" void FUN_0043d690(void);
extern "C" void FUN_0043db60(void);
extern "C" void FUN_00447280(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b4d0(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_0041f990(void) {
    __asm {
        push  ecx
        mov  edx,DWORD PTR ds:0x491c10
        push  esi
        mov  esi,DWORD PTR ds:0x477820
        mov  DWORD PTR [esp+0x4],ecx
        push  0x46dc50
        mov  ecx,0x1
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [esi+0x3e0],eax
        je loc_0041FA0E
        mov  eax,DWORD PTR [esi+0xc]
        or   DWORD PTR [eax+0x4],0x2
        mov  DWORD PTR [esi+0x3e4],0x1
        call FUN_00401440
        test  eax,eax
        jne loc_0041F9E9
        push  0x46dc28
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        jmp loc_0041FA0E
    loc_0041F9E9:
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46cb5c
        xor  ecx,ecx
        mov  DWORD PTR [esi+0x3e8],0x1
        call FUN_00447280
        test  eax,eax
        mov  ds:0x491fec,eax
        jne loc_0041FA24
    loc_0041FA0E:
        mov  DWORD PTR ds:0x491fb8,0x3
        mov  esi,DWORD PTR [esi+0x8]
        or   DWORD PTR [esi+0x4],0x2
        xor  eax,eax
        pop  esi
        pop  ecx
        ret
    loc_0041FA24:
        push  0x0
        push  0x0
        mov  eax,0x46dc14
        call FUN_0044b360
        test  eax,eax
        mov  ds:0x494514,eax
        jne loc_0041FA4D
        push  0x46dbec
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_0041FA4D:
        push  ebx
        mov  ebx,0x492590
        call FUN_0043db60
        push  0x46dbe0
        call FUN_0044b4d0
        test  eax,eax
        pop  ebx
        je loc_0041FAA5
        test  BYTE PTR ds:0x491d78,0x10
        jne loc_0041FA81
        push  0x46dbe0
        mov  eax,0x492590
        call FUN_0043d690
        jmp loc_0041FAA5
    loc_0041FA81:
        mov  eax,ds:0x46dbe0
        mov  ecx,DWORD PTR ds:0x46dbe4
        mov  dx,WORD PTR ds:0x46dbe8
        mov  ds:0x497698,eax
        mov  DWORD PTR ds:0x49769c,ecx
        mov  WORD PTR ds:0x4976a0,dx
    loc_0041FAA5:
        call FUN_0041f8d0
        mov  esi,DWORD PTR [esi+0x8]
        or   DWORD PTR [esi+0x4],0x2
        call FUN_0042af20
        xor  eax,eax
        pop  esi
        pop  ecx
        ret
    }
}
