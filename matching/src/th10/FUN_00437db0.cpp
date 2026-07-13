// 00437DB0: FUN_00437db0
// Original size: 560 bytes, actual code: 184 instructions
extern "C" void FUN_00436da0(void);
extern "C" void FUN_00437160(void);
extern "C" void D3DXLoadSurfaceFromMemory(void);

extern "C" __declspec(naked) void FUN_00437db0(void) {
    __asm {
        sub  esp,0x14
        push  ebx
        mov  ebx,DWORD PTR [esp+0x24]
        cmp  ebx,0x11
        push  ebp
        push  esi
        push  edi
        jg loc_00437DCB
        mov  edx,DWORD PTR ds:0x4918a0
        jmp loc_00437E81
    loc_00437DCB:
        cmp  ebx,0x12
        jg loc_00437DDB
        mov  edx,DWORD PTR ds:0x49189c
        jmp loc_00437E81
    loc_00437DDB:
        cmp  ebx,0x13
        jg loc_00437DEB
        mov  edx,DWORD PTR ds:0x491898
        jmp loc_00437E81
    loc_00437DEB:
        cmp  ebx,0x14
        jg loc_00437DFB
        mov  edx,DWORD PTR ds:0x491894
        jmp loc_00437E81
    loc_00437DFB:
        cmp  ebx,0x15
        jg loc_00437E08
        mov  edx,DWORD PTR ds:0x491890
        jmp loc_00437E81
    loc_00437E08:
        cmp  ebx,0x16
        jg loc_00437E15
        mov  edx,DWORD PTR ds:0x49188c
        jmp loc_00437E81
    loc_00437E15:
        cmp  ebx,0x17
        jg loc_00437E22
        mov  edx,DWORD PTR ds:0x491888
        jmp loc_00437E81
    loc_00437E22:
        cmp  ebx,0x18
        jg loc_00437E2F
        mov  edx,DWORD PTR ds:0x491884
        jmp loc_00437E81
    loc_00437E2F:
        cmp  ebx,0x19
        jg loc_00437E3C
        mov  edx,DWORD PTR ds:0x491880
        jmp loc_00437E81
    loc_00437E3C:
        cmp  ebx,0x1a
        jg loc_00437E49
        mov  edx,DWORD PTR ds:0x49187c
        jmp loc_00437E81
    loc_00437E49:
        cmp  ebx,0x1b
        jg loc_00437E56
        mov  edx,DWORD PTR ds:0x491878
        jmp loc_00437E81
    loc_00437E56:
        cmp  ebx,0x1c
        jg loc_00437E63
        mov  edx,DWORD PTR ds:0x491874
        jmp loc_00437E81
    loc_00437E63:
        cmp  ebx,0x1d
        jg loc_00437E70
        mov  edx,DWORD PTR ds:0x491870
        jmp loc_00437E81
    loc_00437E70:
        cmp  ebx,0x1e
        mov  edx,DWORD PTR ds:0x49186c
        jle loc_00437E81
        mov  edx,DWORD PTR ds:0x491868
    loc_00437E81:
        cmp  ebx,0x11
        jge loc_00437E92
        mov  DWORD PTR [esp+0x30],0x11
        mov  ebx,DWORD PTR [esp+0x30]
    loc_00437E92:
        mov  ecx,DWORD PTR ds:0x474dbc
        mov  edi,DWORD PTR ds:0x474dd0
        mov  esi,ecx
        shr  ecx,0x2
        xor  eax,eax
        rep stosd
        mov  ecx,esi
        and  ecx,0x3
        rep stosb
        mov  esi,DWORD PTR ds:0x474dc4
        push  edx
        push  esi
        call  DWORD PTR ds:0x46602c
        lea  ebx,[ebx+ebx*1+0x6]
        push  ebx
        mov  ecx,0x474cb0
        mov  DWORD PTR [esp+0x14],eax
        call FUN_00437160
        push  0x1
        push  esi
        call  DWORD PTR ds:0x46601c
        mov  eax,DWORD PTR [esp+0x38]
        lea  edi,[eax+0x1]
        nop
    loc_00437EE0:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00437EE0
        push  0x0
        sub  eax,edi
        push  esi
        mov  edi,eax
        call  DWORD PTR ds:0x466018
        mov  eax,DWORD PTR [esp+0x38]
        mov  ebp,DWORD PTR [esp+0x2c]
        push  edi
        push  eax
        add  ebp,ebp
        push  0x2
        lea  ecx,[ebp+0x2]
        push  ecx
        push  esi
        call  DWORD PTR ds:0x466014
        mov  edx,DWORD PTR [esp+0x34]
        push  edx
        push  esi
        call  DWORD PTR ds:0x466018
        mov  eax,DWORD PTR [esp+0x38]
        push  edi
        push  eax
        push  0x0
        push  ebp
        push  esi
        call  DWORD PTR ds:0x466014
        mov  edi,DWORD PTR [esp+0x10]
        mov  ebp,DWORD PTR ds:0x46602c
        push  edi
        push  esi
        call  ebp
        push  ebx
        mov  ecx,0x474cb0
        call FUN_00437160
        push  ebx
        push  0x474cb0
        call FUN_00436da0
        push  edi
        push  esi
        call  ebp
        mov  esi,DWORD PTR [esp+0x28]
        mov  edx,DWORD PTR [esi]
        mov  eax,DWORD PTR [esi+0x8]
        mov  ecx,DWORD PTR [esp+0x30]
        sub  eax,edx
        xor  edi,edi
        lea  eax,[eax+eax*1+0x16]
        cmp  eax,0x400
        lea  edx,[ecx+ecx*1+0x2]
        mov  DWORD PTR [esp+0x14],edi
        mov  DWORD PTR [esp+0x18],edi
        mov  DWORD PTR [esp+0x1c],eax
        mov  DWORD PTR [esp+0x20],edx
        jle loc_00437F89
        mov  DWORD PTR [esp+0x1c],0x400
    loc_00437F89:
        mov  eax,DWORD PTR [esp+0x3c]
        mov  ecx,DWORD PTR [eax]
        lea  edx,[esp+0x30]
        push  edx
        push  edi
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  ecx,DWORD PTR ds:0x474dc0
        mov  edx,DWORD PTR ds:0x474db0
        push  edi
        push  0x4
        lea  eax,[esp+0x1c]
        push  eax
        mov  eax,ds:0x474dd0
        push  edi
        push  ecx
        mov  ecx,DWORD PTR [esp+0x44]
        push  edx
        push  eax
        push  esi
        push  edi
        push  ecx
        call D3DXLoadSurfaceFromMemory
        mov  eax,DWORD PTR [esp+0x30]
        cmp  eax,edi
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        je loc_00437FD4
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
    loc_00437FD4:
        add  esp,0x14
        ret  0x18
    }
}
