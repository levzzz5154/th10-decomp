// 00437FE0: FUN_00437fe0
// Original size: 528 bytes, actual code: 174 instructions
extern "C" void FUN_00436ca0(void);
extern "C" void FUN_00436da0(void);
extern "C" void FUN_00437160(void);
extern "C" void D3DXLoadSurfaceFromMemory(void);

extern "C" __declspec(naked) void FUN_00437fe0(void) {
    __asm {
        sub  esp,0x14
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x28]
        cmp  ebp,0x11
        push  esi
        push  edi
        jg loc_00437FFB
        mov  edi,DWORD PTR ds:0x4918a0
        jmp loc_004380B1
    loc_00437FFB:
        cmp  ebp,0x12
        jg loc_0043800B
        mov  edi,DWORD PTR ds:0x49189c
        jmp loc_004380B1
    loc_0043800B:
        cmp  ebp,0x13
        jg loc_0043801B
        mov  edi,DWORD PTR ds:0x491898
        jmp loc_004380B1
    loc_0043801B:
        cmp  ebp,0x14
        jg loc_0043802B
        mov  edi,DWORD PTR ds:0x491894
        jmp loc_004380B1
    loc_0043802B:
        cmp  ebp,0x15
        jg loc_00438038
        mov  edi,DWORD PTR ds:0x491890
        jmp loc_004380B1
    loc_00438038:
        cmp  ebp,0x16
        jg loc_00438045
        mov  edi,DWORD PTR ds:0x49188c
        jmp loc_004380B1
    loc_00438045:
        cmp  ebp,0x17
        jg loc_00438052
        mov  edi,DWORD PTR ds:0x491888
        jmp loc_004380B1
    loc_00438052:
        cmp  ebp,0x18
        jg loc_0043805F
        mov  edi,DWORD PTR ds:0x491884
        jmp loc_004380B1
    loc_0043805F:
        cmp  ebp,0x19
        jg loc_0043806C
        mov  edi,DWORD PTR ds:0x491880
        jmp loc_004380B1
    loc_0043806C:
        cmp  ebp,0x1a
        jg loc_00438079
        mov  edi,DWORD PTR ds:0x49187c
        jmp loc_004380B1
    loc_00438079:
        cmp  ebp,0x1b
        jg loc_00438086
        mov  edi,DWORD PTR ds:0x491878
        jmp loc_004380B1
    loc_00438086:
        cmp  ebp,0x1c
        jg loc_00438093
        mov  edi,DWORD PTR ds:0x491874
        jmp loc_004380B1
    loc_00438093:
        cmp  ebp,0x1d
        jg loc_004380A0
        mov  edi,DWORD PTR ds:0x491870
        jmp loc_004380B1
    loc_004380A0:
        cmp  ebp,0x1e
        mov  edi,DWORD PTR ds:0x49186c
        jle loc_004380B1
        mov  edi,DWORD PTR ds:0x491868
    loc_004380B1:
        cmp  ebp,0x11
        jge loc_004380BB
        mov  ebp,0x11
    loc_004380BB:
        mov  ecx,DWORD PTR [esp+0x34]
        mov  esi,0x474cb0
        call FUN_00436ca0
        mov  esi,DWORD PTR ds:0x474dc4
        mov  ebx,DWORD PTR ds:0x46602c
        push  edi
        push  esi
        call  ebx
        lea  edi,[ebp+ebp*1+0x6]
        push  edi
        mov  ecx,0x474cb0
        mov  DWORD PTR [esp+0x34],eax
        call FUN_00437160
        push  0x1
        push  esi
        call  DWORD PTR ds:0x46601c
        mov  eax,DWORD PTR [esp+0x38]
        lea  ecx,[eax+0x1]
        nop
    loc_00438100:
        mov  dl,BYTE PTR [eax]
        inc  eax
        test  dl,dl
        jne loc_00438100
        sub  eax,ecx
        mov  DWORD PTR [esp+0x10],eax
        mov  eax,DWORD PTR [esp+0x34]
        push  eax
        push  esi
        call  DWORD PTR ds:0x466018
        mov  ecx,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [esp+0x38]
        mov  eax,DWORD PTR [esp+0x2c]
        push  ecx
        push  edx
        push  0x0
        lea  ecx,[eax+eax*1]
        push  ecx
        push  esi
        call  DWORD PTR ds:0x466014
        mov  edx,DWORD PTR [esp+0x30]
        push  edx
        push  esi
        call  ebx
        push  edi
        mov  ecx,0x474cb0
        call FUN_00437160
        push  edi
        push  0x474cb0
        call FUN_00436da0
        mov  eax,DWORD PTR [esp+0x30]
        push  eax
        push  esi
        call  ebx
        mov  esi,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [esi+0x8]
        sub  eax,DWORD PTR [esi]
        xor  edi,edi
        lea  eax,[eax+eax*1+0x16]
        cmp  eax,0x400
        lea  ecx,[ebp+ebp*1+0x2]
        mov  DWORD PTR [esp+0x14],edi
        mov  DWORD PTR [esp+0x18],edi
        mov  DWORD PTR [esp+0x1c],eax
        mov  DWORD PTR [esp+0x20],ecx
        jle loc_0043818C
        mov  DWORD PTR [esp+0x1c],0x400
    loc_0043818C:
        mov  eax,DWORD PTR [esp+0x3c]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x34]
        push  ecx
        push  edi
        push  eax
        call  DWORD PTR [edx+0x48]
        mov  eax,ds:0x474dc0
        mov  ecx,DWORD PTR ds:0x474db0
        push  edi
        push  0x4
        lea  edx,[esp+0x1c]
        push  edx
        mov  edx,DWORD PTR ds:0x474dd0
        push  edi
        push  eax
        mov  eax,DWORD PTR [esp+0x48]
        push  ecx
        push  edx
        push  esi
        push  edi
        push  eax
        call D3DXLoadSurfaceFromMemory
        mov  eax,DWORD PTR [esp+0x34]
        cmp  eax,edi
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        je loc_004381D7
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_004381D7:
        add  esp,0x14
        ret  0x18
    }
}
