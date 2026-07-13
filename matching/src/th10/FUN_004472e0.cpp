// 004472E0: FUN_004472e0
// Original size: 224 bytes, actual code: 65 instructions
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b8e0(void);
extern "C" void _sprintf(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004472e0(void) {
    __asm {
        sub  esp,0x10c
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x108],eax
        mov  eax,DWORD PTR [esp+0x110]
        test  eax,eax
        push  ebx
        push  edi
        mov  ebx,ecx
        mov  edi,edx
        jne loc_0044730C
        push  0x470274
        jmp loc_00447317
    loc_0044730C:
        cmp  DWORD PTR [eax+0x28],0x4
        je loc_00447329
        push  0x470254
    loc_00447317:
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x4
        or   eax,0xffffffff
        jmp loc_0044739D
    loc_00447329:
        mov  cl,BYTE PTR [eax+0x34]
        test  cl,cl
        push  esi
        jne loc_00447397
        mov  esi,DWORD PTR [eax+0x1c]
        add  esi,eax
        cmp  BYTE PTR [esi],0x40
        je loc_00447397
        push  esi
        lea  eax,[esp+0x14]
        push  0x46e1c8
        push  eax
        call _sprintf
        add  esp,0xc
        push  0x1
        lea  ecx,[esp+0x10]
        push  ecx
        lea  eax,[esp+0x18]
        call FUN_0044b360
        test  eax,eax
        jne loc_0044737A
        push  esi
        push  0x470210
        mov  edi,0x474f70
        call FUN_0044b8e0
        add  esp,0x8
        or   eax,0xffffffff
        jmp loc_0044739C
    loc_0044737A:
        mov  edx,DWORD PTR [edi+0x120]
        mov  esi,DWORD PTR [esp+0xc]
        shl  ebx,0x4
        mov  ecx,ebx
        mov  DWORD PTR [edx+ecx*1+0x8],esi
        mov  edx,DWORD PTR [edi+0x120]
        mov  DWORD PTR [edx+ecx*1+0x4],eax
    loc_00447397:
        mov  eax,0x1
    loc_0044739C:
        pop  esi
    loc_0044739D:
        mov  ecx,DWORD PTR [esp+0x110]
        pop  edi
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x10c
        ret  0x4
    }
}
