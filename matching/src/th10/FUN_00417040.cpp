// 00417040: FUN_00417040
// Original size: 672 bytes, actual code: 171 instructions
extern "C" void FUN_004188a0(void);
extern "C" void FUN_0043e5a0(void);
extern "C" void FUN_0043ee30(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_00417040(void) {
    __asm {
        mov  ecx,DWORD PTR [esi+0x9e78]
        sub  esp,0xc
        push  ebx
        push  ebp
        push  edi
        mov  edi,DWORD PTR ds:0x474c44
        cmp  edi,ecx
        mov  ebp,0x5f5e100
        je loc_004170F4
        mov  eax,edi
        sub  eax,ecx
        cdq
        and  edx,0x1f
        add  eax,edx
        sar  eax,0x5
        cmp  eax,0x8d55e
        mov  ebx,ecx
        jl loc_0041707C
        mov  eax,0x8d55e
        jmp loc_00417085
    loc_0041707C:
        test  eax,eax
        jne loc_00417085
        mov  eax,0x1
    loc_00417085:
        cmp  DWORD PTR [esi+0x9e7c],eax
        jge loc_00417099
        mov  DWORD PTR [esi+0x9e7c],eax
        mov  edi,DWORD PTR ds:0x474c44
    loc_00417099:
        mov  edx,DWORD PTR [esi+0x9e78]
        mov  ecx,DWORD PTR [esi+0x9e7c]
        mov  eax,edi
        sub  eax,edx
        cmp  ecx,eax
        jle loc_004170B3
        mov  DWORD PTR [esi+0x9e7c],eax
    loc_004170B3:
        mov  eax,DWORD PTR [esi+0x9e7c]
        mov  edx,DWORD PTR [esi+0x9e78]
        add  edx,eax
        mov  DWORD PTR [esi+0x9e78],edx
        mov  ecx,DWORD PTR ds:0x474c44
        mov  eax,edx
        cmp  eax,ecx
        jl loc_004170DD
        mov  DWORD PTR [esi+0x9e7c],0x0
    loc_004170DD:
        mov  ecx,DWORD PTR [esi+0x9e78]
        cmp  ecx,ebp
        jl loc_004170F4
        cmp  ebx,ebp
        jge loc_004170F4
        mov  WORD PTR [esi+0x48d8],0x4
    loc_004170F4:
        cmp  DWORD PTR ds:0x474c40,ecx
        jge loc_0041715B
        mov  eax,ds:0x474ca0
        or   eax,0x4
        test  al,0x4
        mov  DWORD PTR ds:0x474c40,ecx
        mov  ecx,DWORD PTR ds:0x474c90
        mov  DWORD PTR ds:0x474c94,ecx
        mov  ds:0x474ca0,eax
        jne loc_0041715B
        mov  edi,DWORD PTR ds:0x47770c
        mov  edx,DWORD PTR [edi+0x9e18]
        lea  ebx,[edi+0x9e18]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [ebx],0x0
        mov  eax,DWORD PTR [edi+0x9ec8]
        push  0x4a
        push  eax
        lea  edi,[esp+0x20]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [ebx],ecx
    loc_0041715B:
        cmp  DWORD PTR [esi+0x9e64],0x14
        jl loc_00417189
        cmp  DWORD PTR ds:0x474c40,ebp
        jl loc_0041717D
        cmp  DWORD PTR [esi+0x9e74],ebp
        jge loc_0041717D
        mov  WORD PTR [esi+0x2420],0x4
    loc_0041717D:
        mov  edx,DWORD PTR ds:0x474c40
        mov  DWORD PTR [esi+0x9e74],edx
    loc_00417189:
        mov  eax,ds:0x474c40
        mov  ecx,DWORD PTR [esi+0x9e78]
        mov  DWORD PTR [esp+0xc],eax
        mov  DWORD PTR [esp+0x10],ecx
        lea  edi,[esi+0x2874]
        mov  DWORD PTR [esp+0x14],0x9
        jmp loc_004171B0
    loc_004171AC:
        mov  eax,DWORD PTR [esp+0xc]
    loc_004171B0:
        test  eax,eax
        lea  ebp,[edi-0x24b8]
        je loc_004171DA
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  ecx,DWORD PTR [esi+0x9ec8]
        mov  ebx,eax
        add  edx,0x8
        mov  eax,ebp
        call FUN_0043e5a0
        mov  DWORD PTR [esp+0xc],ebx
        jmp loc_004171EC
    loc_004171DA:
        mov  ecx,DWORD PTR [esi+0x9ec8]
        mov  edx,0x8
        mov  eax,ebp
        call FUN_0043e5a0
    loc_004171EC:
        mov  eax,DWORD PTR [esp+0x10]
        test  eax,eax
        je loc_00417214
        cdq
        mov  ecx,0xa
        idiv  ecx
        mov  ecx,DWORD PTR [esi+0x9ec8]
        mov  ebx,eax
        add  edx,0x8
        mov  eax,edi
        call FUN_0043e5a0
        mov  DWORD PTR [esp+0x10],ebx
        jmp loc_00417226
    loc_00417214:
        mov  ecx,DWORD PTR [esi+0x9ec8]
        mov  edx,0x8
        mov  eax,edi
        call FUN_0043e5a0
    loc_00417226:
        push  ebp
        call FUN_0043ee30
        push  edi
        call FUN_0043ee30
        mov  eax,DWORD PTR [esp+0x14]
        add  edi,0x3ac
        dec  eax
        mov  DWORD PTR [esp+0x14],eax
        jne loc_004171AC
        mov  edx,DWORD PTR ds:0x474c94
        mov  ecx,DWORD PTR [esi+0x9ec8]
        lea  edi,[esi+0x10]
        add  edx,0x8
        mov  eax,edi
        call FUN_0043e5a0
        mov  edx,DWORD PTR ds:0x474c90
        mov  ecx,DWORD PTR [esi+0x9ec8]
        lea  ebx,[esi+0x24c8]
        add  edx,0x8
        mov  eax,ebx
        call FUN_0043e5a0
        push  edi
        call FUN_0043ee30
        push  ebx
        call FUN_0043ee30
        test  BYTE PTR [esi+0x9eb4],0x20
        pop  edi
        pop  ebp
        pop  ebx
        jne loc_004172DB
        cmp  DWORD PTR ds:0x474c74,0x4
        je loc_004172B1
        mov  eax,ds:0x474c9c
        mov  edx,DWORD PTR [esi+0x9e78]
        cmp  edx,DWORD PTR [eax*4+0x474474]
        jmp loc_004172C4
    loc_004172B1:
        mov  edx,DWORD PTR ds:0x474c9c
        mov  ecx,DWORD PTR [esi+0x9e78]
        cmp  ecx,DWORD PTR [edx*4+0x474488]
    loc_004172C4:
        jl loc_004172DB
        mov  eax,0x474c40
        mov  ecx,0x1
        call FUN_004188a0
        inc  DWORD PTR ds:0x474c9c
    loc_004172DB:
        add  esp,0xc
        ret
    }
}
