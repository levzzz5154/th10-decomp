// 0040D530: FUN_0040d530
// Original size: 336 bytes, actual code: 95 instructions
extern "C" void FUN_00409f90(void);
extern "C" void FUN_0040d680(void);
extern "C" void FUN_00447810(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040d530(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,eax
        push  edi
        call FUN_00409f90
        mov  esi,DWORD PTR [edi+0x8]
        test  esi,esi
        mov  ebx,DWORD PTR ds:0x491be4
        mov  ebp,DWORD PTR ds:0x4660b0
        je loc_0040D577
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,ebx
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_0040D577:
        mov  esi,DWORD PTR [edi+0xc]
        test  esi,esi
        mov  ebx,DWORD PTR ds:0x491be4
        je loc_0040D5AB
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,ebx
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_0040D5AB:
        mov  esi,0xc
    loc_0040D5B0:
        mov  eax,DWORD PTR [edi+0x54]
        mov  eax,DWORD PTR [esi+eax*1]
        test  eax,eax
        je loc_0040D5C3
        push  eax
        call _free
        add  esp,0x4
    loc_0040D5C3:
        add  esi,0x4
        cmp  esi,0x8c
        jl loc_0040D5B0
        mov  esi,DWORD PTR [edi+0x54]
        test  esi,esi
        je loc_0040D5E3
        call FUN_0040d680
        push  esi
        call _free
        add  esp,0x4
    loc_0040D5E3:
        xor  eax,eax
        mov  DWORD PTR [edi+0x54],eax
        test  BYTE PTR ds:0x474ca0,0x9
        jne loc_0040D651
        mov  ebp,0x9
        mov  ebx,0x3ad090
        mov  DWORD PTR [esp+0x10],0x4
    loc_0040D603:
        test  ebp,ebp
        jl loc_0040D632
        cmp  ebp,0x21
        jae loc_0040D632
        mov  ecx,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebx+ecx*1]
        test  edi,edi
        lea  esi,[ebx+ecx*1]
        je loc_0040D632
        call FUN_00447810
        mov  edx,DWORD PTR [esi]
        push  edx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_0040D632:
        mov  eax,DWORD PTR [esp+0x10]
        add  ebx,0x4
        inc  ebp
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_0040D603
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR ds:0x477704,0x0
        pop  ebx
        pop  ecx
        ret
    loc_0040D651:
        pop  edi
        pop  esi
        pop  ebp
        mov  ds:0x477704,eax
        pop  ebx
        pop  ecx
        ret
    }
}
