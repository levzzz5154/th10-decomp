// 00422220: FUN_00422220
// Original size: 320 bytes, actual code: 100 instructions
extern "C" void FUN_004294a0(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00422220(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        push  ebp
        mov  ebp,DWORD PTR ds:0x4660b4
        push  esi
        mov  esi,DWORD PTR [eax+0x8]
        test  esi,esi
        push  edi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00422264
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00422264:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  esi,DWORD PTR [ecx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00422298
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00422298:
        mov  edi,DWORD PTR [esp+0x14]
        add  edi,0x1ec
        mov  ebx,0x19
    loc_004222A7:
        mov  esi,DWORD PTR [edi]
        test  esi,esi
        je loc_004222BC
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
    loc_004222BC:
        add  edi,0x4
        dec  ebx
        jne loc_004222A7
        mov  edx,DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [edx+0x1dc]
        test  ecx,ecx
        je loc_0042233F
        mov  edx,DWORD PTR ds:0x491c10
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        je loc_004222ED
    loc_004222E0:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_00422306
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004222E0
    loc_004222ED:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_0042233F
    loc_004222F7:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00422306
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004222F7
        jmp loc_0042233F
    loc_00422306:
        mov  eax,DWORD PTR [eax]
        test  eax,eax
        je loc_0042233F
        mov  esi,DWORD PTR [eax+0x35c]
        mov  ecx,DWORD PTR [eax+0x18]
        mov  edx,0x4000000
        or   esi,edx
        test  ecx,ecx
        mov  DWORD PTR [eax+0x35c],esi
        jne loc_0042233F
        mov  eax,DWORD PTR [eax+0x14]
        test  eax,eax
        je loc_0042233F
        nop
    loc_00422330:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_00422330
    loc_0042233F:
        mov  ecx,DWORD PTR [esp+0x14]
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        mov  DWORD PTR [ecx+0x1dc],eax
        mov  ds:0x477830,eax
        pop  ebx
        ret  0x4
    }
}
