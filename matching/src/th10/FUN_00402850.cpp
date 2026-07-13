// 00402850: FUN_00402850
// Original size: 1104 bytes, actual code: 288 instructions
extern "C" void FUN_00403a30(void);
extern "C" void FUN_00405300(void);
extern "C" void FUN_00405410(void);
extern "C" void FUN_00420cd0(void);
extern "C" void FUN_004215a0(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_00442f50(void);
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_00402850(void) {
    __asm {
        sub  esp,0x20
        push  ebp
        mov  ebp,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [ebp+0x2a18]
        test  al,0x8
        je loc_0040286E
        mov  eax,0x1
        pop  ebp
        add  esp,0x20
        ret  0x4
    loc_0040286E:
        test  al,0x4
        push  ebx
        push  esi
        push  edi
        je loc_00402882
        cmp  DWORD PTR [ebp+0x2a20],0x3c
        jge loc_00402A40
    loc_00402882:
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
        mov  esi,DWORD PTR ds:0x491c10
        xor  ebx,ebx
        mov  DWORD PTR ds:0x491fb0,ebx
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x1
        push  0xe
        push  eax
        call  DWORD PTR [edx+0xe4]
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
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  0x3f800000
        push  ebx
        push  0x2
        push  ebx
        push  ebx
        push  eax
        call  DWORD PTR [ecx+0xac]
        test  BYTE PTR [ebp+0x2a18],0x4
        je loc_004029F4
        cmp  DWORD PTR [ebp+0x2a34],0x22
        jge loc_004029F4
        mov  eax,ds:0x491c30
        push  ebx
        push  0x3f800000
        push  ebx
        push  0x1
        lea  ecx,[esp+0x20]
        push  ecx
        push  0x1
        mov  DWORD PTR [esp+0x28],0x20
        mov  DWORD PTR [esp+0x2c],0x10
        mov  DWORD PTR [esp+0x30],0x1a0
        mov  DWORD PTR [esp+0x34],0x1d0
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xac]
        jmp loc_00402A42
    loc_004029F4:
        mov  ecx,DWORD PTR [ebp+0x2b60]
        mov  eax,ds:0x491c30
        push  ebx
        push  0x3f800000
        and  ecx,0xffffff
        push  ecx
        push  0x1
        lea  ecx,[esp+0x30]
        push  ecx
        push  0x1
        mov  DWORD PTR [esp+0x38],0x20
        mov  DWORD PTR [esp+0x3c],0x10
        mov  DWORD PTR [esp+0x40],0x1a0
        mov  DWORD PTR [esp+0x44],0x1d0
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xac]
        jmp loc_00402A42
    loc_00402A40:
        xor  ebx,ebx
    loc_00402A42:
        mov  eax,DWORD PTR [ebp+0x2a18]
        test  al,0x4
        je loc_00402A95
        cmp  DWORD PTR [ebp+0x2a20],0x1e
        jge loc_00402A86
        push  ebx
        push  ebx
        push  ebx
        push  0x1e
        push  0x3
        mov  ebx,0xf
        call FUN_0043c8b0
        mov  ecx,DWORD PTR [ebp+0x2a18]
        or   ecx,0x1
        push  0x1
        lea  eax,[ebp+0x2a1c]
        mov  DWORD PTR [ebp+0x2a18],ecx
        call FUN_00405410
        xor  ebx,ebx
        jmp loc_00402A95
    loc_00402A86:
        and  eax,0xfffffffe
        mov  BYTE PTR [ebp+0x1eeb],bl
        mov  DWORD PTR [ebp+0x2a18],eax
    loc_00402A95:
        cmp  BYTE PTR [ebp+0x1eeb],bl
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,0x1
        je loc_00402ABA
        mov  eax,DWORD PTR [ebp+0x1ee8]
        mov  DWORD PTR [esi+0x73245c],edi
        mov  DWORD PTR [esi+0x732458],eax
    loc_00402ABA:
        test  BYTE PTR [ebp+0x2a18],0x1
        mov  DWORD PTR [ebp+0x2a0c],ebx
        mov  DWORD PTR [ebp+0x2a10],ebx
        mov  DWORD PTR [ebp+0x2a14],ebx
        je loc_00402C34
        cmp  DWORD PTR [ebp+0x514],ebx
        je loc_00402BAA
        xor  ebx,ebx
        mov  esi,0x491c28
        call FUN_00405300
        mov  edi,esi
        call FUN_00420cd0
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  ebx
        push  0xe
        push  eax
        call  DWORD PTR [edx+0xe4]
        lea  esi,[ebp+0x180]
        mov  edi,0x8
        lea  ebx,[ebx+0x0]
    loc_00402B30:
        mov  eax,DWORD PTR [esi+0x394]
        test  eax,eax
        je loc_00402B47
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
    loc_00402B47:
        add  esi,0x3ac
        dec  edi
        jne loc_00402B30
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,ds:0x491c30
        mov  ecx,DWORD PTR [eax]
        push  0x1
        push  0xe
        push  eax
        call  DWORD PTR [ecx+0xe4]
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
        mov  esi,DWORD PTR ds:0x491c10
        mov  DWORD PTR ds:0x491fb0,0x0
        xor  ebx,ebx
    loc_00402BAA:
        mov  eax,ds:0x492378
        mov  edi,0x1
        cmp  eax,edi
        je loc_00402BD4
        call FUN_00442f50
        mov  eax,ds:0x491c30
        push  edi
        push  0x1c
        mov  DWORD PTR ds:0x492378,edi
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0xe4]
    loc_00402BD4:
        push  ebx
        push  ebp
        call FUN_00403a30
        push  edi
        push  ebp
        call FUN_00403a30
        push  0x2
        push  ebp
        call FUN_00403a30
        push  0x3
        push  ebp
        call FUN_00403a30
        push  0x4
        push  ebp
        call FUN_00403a30
        push  0x5
        push  ebp
        call FUN_00403a30
        push  0x6
        push  ebp
        call FUN_00403a30
        push  0x7
        push  ebp
        call FUN_00403a30
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,DWORD PTR [ebp+0x1ee4]
        cmp  eax,ebx
        mov  esi,DWORD PTR ds:0x491c10
        je loc_00402C34
        inc  eax
        mov  DWORD PTR [ebp+0x1ee4],eax
    loc_00402C34:
        mov  DWORD PTR [esi+0x73245c],ebx
        mov  DWORD PTR [esi+0x732458],0x80808080
        cmp  DWORD PTR [ebp+0x1eec],ebx
        je loc_00402C5C
        mov  DWORD PTR [esi+0x73245c],edi
        mov  DWORD PTR [esi+0x732458],0xff404040
    loc_00402C5C:
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
        mov  eax,edi
        pop  edi
        pop  esi
        pop  ebx
        pop  ebp
        add  esp,0x20
        ret  0x4
    }
}
