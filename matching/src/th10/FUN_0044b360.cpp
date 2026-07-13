// 0044B360: FUN_0044b360
// Original size: 368 bytes, actual code: 130 instructions
extern "C" void FUN_00434dd0(void);
extern "C" void _malloc(void);
extern "C" void _strrchr(void);
extern "C" void __stricmp(void);

extern "C" __declspec(naked) void FUN_0044b360(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        push  edi
        push  0x4922a4
        mov  esi,eax
        call  DWORD PTR ds:0x4660b0
        mov  cl,BYTE PTR ds:0x49231e
        mov  eax,DWORD PTR [esp+0x18]
        inc  cl
        test  eax,eax
        mov  BYTE PTR ds:0x49231e,cl
        jne loc_0044B41F
        push  0x5c
        push  esi
        call _strrchr
        add  esp,0x8
        test  eax,eax
        jne loc_0044B3A2
        mov  eax,esi
        jmp loc_0044B3A3
    loc_0044B3A2:
        inc  eax
    loc_0044B3A3:
        push  0x2f
        push  eax
        call _strrchr
        mov  ebx,eax
        add  esp,0x8
        test  ebx,ebx
        jne loc_0044B3B8
        mov  ebx,esi
        jmp loc_0044B3B9
    loc_0044B3B8:
        inc  ebx
    loc_0044B3B9:
        mov  edi,DWORD PTR ds:0x497990
        test  edi,edi
        je loc_0044B3E8
        mov  esi,DWORD PTR ds:0x497994
        test  esi,esi
        jle loc_0044B3E8
        nop
    loc_0044B3D0:
        mov  eax,DWORD PTR [edi]
        push  eax
        push  ebx
        call __stricmp
        add  esp,0x8
        test  eax,eax
        je loc_0044B41A
        dec  esi
        add  edi,0x10
        test  esi,esi
        jg loc_0044B3D0
    loc_0044B3E8:
        xor  edi,edi
    loc_0044B3EA:
        test  ebp,ebp
        mov  DWORD PTR [esp+0x14],edi
        je loc_0044B3F5
        mov  DWORD PTR [ebp+0x0],edi
    loc_0044B3F5:
        test  edi,edi
        je loc_0044B462
        push  edi
        call _malloc
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        je loc_0044B462
        push  esi
        push  0x497990
        mov  ecx,ebx
        call FUN_00434dd0
        jmp loc_0044B4A8
    loc_0044B41A:
        mov  edi,DWORD PTR [edi+0x8]
        jmp loc_0044B3EA
    loc_0044B41F:
        push  0x0
        push  0x8000080
        push  0x3
        push  0x0
        push  0x1
        push  0x80000000
        push  esi
        call  DWORD PTR ds:0x4660c4
        mov  edi,eax
        cmp  edi,0xffffffff
        je loc_0044B462
        push  0x0
        push  edi
        call  DWORD PTR ds:0x4660d8
        push  eax
        mov  DWORD PTR [esp+0x18],eax
        call _malloc
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        jne loc_0044B482
        push  edi
        call  DWORD PTR ds:0x4660cc
    loc_0044B462:
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        mov  al,ds:0x49231e
        pop  edi
        pop  esi
        dec  al
        pop  ebp
        mov  ds:0x49231e,al
        xor  eax,eax
        pop  ebx
        ret  0x8
    loc_0044B482:
        mov  edx,DWORD PTR [esp+0x14]
        push  0x0
        lea  ecx,[esp+0x18]
        push  ecx
        push  edx
        push  esi
        push  edi
        call  DWORD PTR ds:0x4660d0
        test  ebp,ebp
        je loc_0044B4A1
        mov  eax,DWORD PTR [esp+0x14]
        mov  DWORD PTR [ebp+0x0],eax
    loc_0044B4A1:
        push  edi
        call  DWORD PTR ds:0x4660cc
    loc_0044B4A8:
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        mov  al,ds:0x49231e
        dec  al
        pop  edi
        mov  ds:0x49231e,al
        mov  eax,esi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x8
    }
}
