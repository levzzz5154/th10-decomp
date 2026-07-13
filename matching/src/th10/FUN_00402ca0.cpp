// 00402CA0: FUN_00402ca0
// Original size: 1008 bytes, actual code: 243 instructions
extern "C" void FUN_00403a30(void);
extern "C" void FUN_004215a0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_00448980(void);
extern "C" void FUN_0044bf40(void);

extern "C" __declspec(naked) void FUN_00402ca0(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x2a18]
        test  al,0x8
        je loc_00402CB8
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00402CB8:
        push  ebx
        push  esi
        xor  ebx,ebx
        test  al,0x4
        push  edi
        je loc_00402CCE
        cmp  DWORD PTR [ebp+0x2a20],0x3c
        jge loc_00402E86
    loc_00402CCE:
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491e64
        mov  DWORD PTR [ebp+0x2b34],eax
        mov  ecx,DWORD PTR ds:0x491e68
        mov  DWORD PTR [ebp+0x2b38],ecx
        lea  esi,[ebp+0x2a4c]
        mov  ecx,0x46
        mov  edi,0x491d7c
        rep movsd
        mov  edi,0x491d7c
        mov  DWORD PTR ds:0x491fac,edi
        call FUN_004215a0
        mov  ecx,DWORD PTR ds:0x491fac
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        add  ecx,0xcc
        push  ecx
        push  eax
        call  DWORD PTR [edx+0xbc]
        mov  eax,ds:0x492378
        mov  edi,0x1
        cmp  eax,edi
        mov  DWORD PTR ds:0x491fb0,ebx
        je loc_00402D63
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  edi
        push  0x1c
        mov  DWORD PTR ds:0x492378,edi
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00402D63:
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  0xe
        push  eax
        call  DWORD PTR [ecx+0xe4]
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x8
        push  0x17
        push  eax
        call  DWORD PTR [edx+0xe4]
        mov  edi,DWORD PTR ds:0x491c10
        mov  eax,0x11
        call FUN_00448980
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x4
        push  0x17
        push  eax
        call  DWORD PTR [ecx+0xe4]
        cmp  DWORD PTR ds:0x492378,ebx
        je loc_00402DF3
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  ebx
        push  0x1c
        mov  DWORD PTR ds:0x492378,ebx
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00402DF3:
        mov  edi,DWORD PTR ds:0x491c10
        mov  eax,0x12
        call FUN_00448980
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x4
        push  0x17
        push  eax
        call  DWORD PTR [ecx+0xe4]
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebp+0x2b60]
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  edi
        push  0x22
        push  eax
        call  DWORD PTR [edx+0xe4]
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebp+0x2b48]
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  edi
        push  0x24
        push  eax
        call  DWORD PTR [ecx+0xe4]
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ebp+0x2b4c]
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  edi
        push  0x25
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00402E86:
        mov  eax,DWORD PTR [ebp+0x2a18]
        test  al,0x4
        je loc_00402E9F
        cmp  DWORD PTR [ebp+0x2a20],0x1e
        jl loc_00402E9F
        mov  BYTE PTR [ebp+0x1eeb],bl
    loc_00402E9F:
        test  al,0x1
        je loc_00402F1C
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  0xe
        push  eax
        call  DWORD PTR [ecx+0xe4]
        mov  eax,ds:0x492378
        mov  edi,0x1
        cmp  eax,edi
        je loc_00402EEF
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  edi
        push  0x1c
        mov  DWORD PTR ds:0x492378,edi
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00402EEF:
        push  0x8
        push  ebp
        call FUN_00403a30
        push  0x9
        push  ebp
        call FUN_00403a30
        push  0xa
        push  ebp
        call FUN_00403a30
        push  0xb
        push  ebp
        call FUN_00403a30
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        jmp loc_00402F21
    loc_00402F1C:
        mov  edi,0x1
    loc_00402F21:
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR [esi+0x73245c],ebx
        mov  DWORD PTR [esi+0x732458],0x80808080
        cmp  DWORD PTR [ebp+0x1eec],ebx
        je loc_00402F4F
        mov  DWORD PTR [esi+0x73245c],edi
        mov  DWORD PTR [esi+0x732458],0xff404040
    loc_00402F4F:
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  0xe
        push  eax
        call  DWORD PTR [ecx+0xe4]
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x8
        push  0x17
        push  eax
        call  DWORD PTR [edx+0xe4]
        cmp  DWORD PTR [ebp+0x2a20],ebx
        jle loc_00402FD5
        push  0xbf800000
        lea  esi,[ebp+0x2a1c]
        call FUN_0044bf40
        cmp  DWORD PTR [ebp+0x2a20],ebx
        jg loc_00402FD5
        mov  eax,DWORD PTR [ebp+0x2a18]
        test  al,0x2
        mov  BYTE PTR [ebp+0x1eeb],0xff
        je loc_00402FBC
        or   eax,0x8
        mov  DWORD PTR [ebp+0x2a18],eax
    loc_00402FBC:
        mov  eax,DWORD PTR [ebp+0x2a18]
        and  eax,0xfffffff9
        mov  DWORD PTR [ebp+0x1ee8],0xffffff
        mov  DWORD PTR [ebp+0x2a18],eax
    loc_00402FD5:
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  0xe
        push  eax
        call  DWORD PTR [ecx+0xe4]
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x8
        push  0x17
        push  eax
        call  DWORD PTR [edx+0xe4]
        cmp  DWORD PTR ds:0x492378,ebx
        je loc_00403038
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  ebx
        push  0x1c
        mov  DWORD PTR ds:0x492378,ebx
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xe4]
    loc_00403038:
        mov  eax,edi
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        ret  0x4
    }
}
