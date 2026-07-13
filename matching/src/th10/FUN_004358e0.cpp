// 004358E0: FUN_004358e0
// Original size: 208 bytes, actual code: 70 instructions
extern "C" void FUN_00434ef0(void);
extern "C" void FUN_00435370(void);
extern "C" void FUN_004356f0(void);
extern "C" void FUN_00452730(void);

extern "C" __declspec(naked) void FUN_004358e0(void) {
    __asm {
        push  0xffffffff
        mov  eax,fs:0x0
        push  0x465388
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0xc
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  esi,ecx
        call FUN_004356f0
        mov  ebp,eax
        xor  edi,edi
        cmp  ebp,edi
        je loc_00435939
        push  0x2f
        push  esi
        call FUN_00452730
        add  esp,0x8
        cmp  eax,edi
        je loc_0043591D
        lea  esi,[eax+0x1]
    loc_0043591D:
        mov  ebx,esi
        mov  eax,ebp
        call FUN_00434ef0
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        mov  ecx,DWORD PTR [esp+0xc]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret
    loc_00435939:
        mov  ebx,0x46f230
        mov  DWORD PTR [esp+0x10],ebx
        mov  DWORD PTR [esp+0x14],0xffffffff
        mov  DWORD PTR [esp+0x18],edi
        mov  DWORD PTR [esp+0x24],edi
        mov  eax,ds:0x474908
        push  eax
        push  esi
        lea  ecx,[esp+0x18]
        call FUN_00435370
        mov  eax,DWORD PTR [esp+0x14]
        cmp  eax,0xffffffff
        je loc_00435979
        push  edi
        push  eax
        call  DWORD PTR ds:0x4660d8
        mov  edi,eax
        mov  eax,DWORD PTR [esp+0x14]
    loc_00435979:
        cmp  eax,0xffffffff
        mov  DWORD PTR [esp+0x10],ebx
        je loc_00435989
        push  eax
        call  DWORD PTR ds:0x4660cc
    loc_00435989:
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  eax,edi
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x18
        ret
    }
}
