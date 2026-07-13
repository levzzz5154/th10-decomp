// 00420270: FUN_00420270
// Original size: 336 bytes, actual code: 100 instructions
extern "C" void FUN_00413450(void);
extern "C" void FUN_004203c0(void);
extern "C" void FUN_004203f0(void);
extern "C" void FUN_00434d10(void);
extern "C" void FUN_00437d10(void);
extern "C" void FUN_0043e460(void);
extern "C" void FUN_0044c150(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00420270(void) {
    __asm {
        push  ebp
        push  esi
        push  edi
        mov  esi,0x474dd4
        mov  edi,eax
        call FUN_0044c150
        mov  esi,0x492254
        mov  DWORD PTR ds:0x4977b4,0x2
        call FUN_0044c150
        mov  eax,ds:0x49238c
        xor  ebp,ebp
        cmp  eax,ebp
        je loc_004202AD
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR ds:0x49238c,ebp
    loc_004202AD:
        push  ebx
        call FUN_004203f0
        mov  ebx,DWORD PTR ds:0x477708
        call FUN_00413450
        mov  esi,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [esi+0x3ada74]
        add  esi,0x3ada74
        cmp  eax,ebp
        pop  ebx
        je loc_004202DD
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esi],ebp
    loc_004202DD:
        push  ebp
        push  0x4
        mov  edx,0x46df98
        mov  eax,0x492590
        call FUN_0043e460
        call FUN_00437d10
        mov  eax,DWORD PTR [edi+0x10]
        cmp  eax,ebp
        je loc_00420311
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x20]
        mov  eax,DWORD PTR [edi+0x10]
        cmp  eax,ebp
        je loc_00420311
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi+0x10],ebp
    loc_00420311:
        mov  eax,DWORD PTR [edi+0x14]
        cmp  eax,ebp
        je loc_0042032E
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x20]
        mov  eax,DWORD PTR [edi+0x14]
        cmp  eax,ebp
        je loc_0042032E
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi+0x14],ebp
    loc_0042032E:
        mov  eax,DWORD PTR [edi+0xc]
        cmp  eax,ebp
        je loc_0042033E
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [edi+0xc],ebp
    loc_0042033E:
        mov  eax,ds:0x491d44
        cmp  eax,ebp
        je loc_00420385
        lea  esi,[eax+0x4]
        mov  edi,eax
        mov  eax,DWORD PTR [esi]
        cmp  eax,ebp
        je loc_00420359
        push  eax
        call  DWORD PTR ds:0x466288
    loc_00420359:
        mov  eax,DWORD PTR [edi+0x8]
        push  eax
        call  DWORD PTR ds:0x466274
        mov  DWORD PTR [esi],ebp
        mov  esi,DWORD PTR ds:0x491d44
        cmp  esi,ebp
        mov  edi,esi
        je loc_0042037F
        call FUN_004203c0
        push  edi
        call _free
        add  esp,0x4
    loc_0042037F:
        mov  DWORD PTR ds:0x491d44,ebp
    loc_00420385:
        mov  esi,0x497990
        call FUN_00434d10
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        ret
    }
}
