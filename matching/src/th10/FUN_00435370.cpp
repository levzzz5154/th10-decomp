// 00435370: FUN_00435370
// Original size: 240 bytes, actual code: 80 instructions
extern "C" void FUN_00435610(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_00435370(void) {
    __asm {
        sub  esp,0x10c
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x118]
        push  esi
        push  edi
        mov  esi,ecx
        mov  DWORD PTR [esp+0x118],eax
        mov  eax,DWORD PTR [esi]
        xor  edi,edi
        mov  DWORD PTR [esp+0x10],edi
        call  DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [esp+0x124]
        mov  ebx,eax
        mov  al,BYTE PTR [eax]
        test  al,al
        je loc_004353F6
        jmp loc_004353B0
        nop
    loc_004353B0:
        cmp  al,0x72
        je loc_004353C6
        cmp  al,0x77
        je loc_004353D4
        cmp  al,0x61
        je loc_004353E2
        mov  al,BYTE PTR [ebx+0x1]
        inc  ebx
        test  al,al
        jne loc_004353B0
        jmp loc_00435444
    loc_004353C6:
        mov  DWORD PTR [esi+0x8],0x80000000
        mov  edi,0x3
        jmp loc_004353F6
    loc_004353D4:
        push  ebp
        call  DWORD PTR ds:0x4660c0
        mov  edi,0x2
        jmp loc_004353EF
    loc_004353E2:
        mov  DWORD PTR [esp+0x10],0x1
        mov  edi,0x4
    loc_004353EF:
        mov  DWORD PTR [esi+0x8],0x40000000
    loc_004353F6:
        cmp  BYTE PTR [ebx],0x0
        je loc_00435429
        mov  eax,ebp
        lea  ecx,[esp+0x14]
        call FUN_00435610
        mov  ecx,DWORD PTR [esi+0x8]
        push  0x0
        push  0x8000080
        push  edi
        push  0x0
        push  0x1
        push  ecx
        lea  edx,[esp+0x2c]
        push  edx
        call  DWORD PTR ds:0x4660c4
        cmp  eax,0xffffffff
        mov  DWORD PTR [esi+0x4],eax
        jne loc_0043542D
    loc_00435429:
        xor  al,al
        jmp loc_00435444
    loc_0043542D:
        mov  ecx,DWORD PTR [esp+0x10]
        test  ecx,ecx
        je loc_00435442
        push  0x2
        push  0x0
        push  0x0
        push  eax
        call  DWORD PTR ds:0x4660c8
    loc_00435442:
        mov  al,0x1
    loc_00435444:
        mov  ecx,DWORD PTR [esp+0x118]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x10c
        ret  0x8
    }
}
