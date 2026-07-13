// 0044C8F0: FUN_0044c8f0
// Original size: 768 bytes, actual code: 229 instructions
extern "C" void FUN_0044d6a0(void);
extern "C" void FUN_0044dbf0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044c8f0(void) {
    __asm {
        push  0xffffffff
        push  0x46533b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0x50
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        mov  ebx,edx
        mov  edx,DWORD PTR [esp+0x6c]
        mov  DWORD PTR [esp+0x14],ecx
        mov  ecx,DWORD PTR [esp+0x70]
        mov  DWORD PTR [esp+0x40],edx
        mov  edx,DWORD PTR [esp+0x74]
        mov  DWORD PTR [esp+0x44],ecx
        mov  ecx,DWORD PTR [esp+0x78]
        push  ebp
        mov  ebp,DWORD PTR [esp+0x80]
        mov  DWORD PTR [esp+0x54],eax
        mov  eax,DWORD PTR [esp+0x68]
        push  esi
        mov  esi,DWORD PTR [esp+0x90]
        mov  DWORD PTR [esp+0x50],edx
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x54],ecx
        xor  ecx,ecx
        cmp  edx,ecx
        push  edi
        mov  edi,DWORD PTR [esp+0x74]
        mov  DWORD PTR [esp+0x1c],eax
        jne loc_0044C969
        mov  eax,0x800401f0
        jmp loc_0044CB8E
    loc_0044C969:
        push  0x94
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x14],ecx
        call operator_new
        xor  ecx,ecx
        add  esp,0x4
        cmp  eax,ecx
        je loc_0044C998
        mov  DWORD PTR [eax+0x90],ecx
        mov  DWORD PTR [eax],ecx
        mov  DWORD PTR [eax+0x2c],ecx
        mov  DWORD PTR [eax+0x7c],ecx
        mov  DWORD PTR [esp+0x14],eax
        jmp loc_0044C99C
    loc_0044C998:
        mov  DWORD PTR [esp+0x14],ecx
    loc_0044C99C:
        mov  edx,esi
        mov  esi,DWORD PTR [esp+0x14]
        mov  eax,0x1
        mov  ecx,edi
        call FUN_0044dbf0
        test  eax,eax
        je loc_0044C9EA
        test  esi,esi
        je loc_0044CB12
        cmp  DWORD PTR [esi+0x78],0x1
        jne loc_0044C9D7
        mov  edx,DWORD PTR [esi+0x8c]
        push  edx
        call  DWORD PTR ds:0x4660cc
        mov  DWORD PTR [esi+0x8c],0xffffffff
    loc_0044C9D7:
        push  esi
        call _free
        add  esp,0x4
        mov  eax,0x80004005
        jmp loc_0044CB8E
    loc_0044C9EA:
        mov  esi,DWORD PTR [esp+0x8c]
        mov  ecx,DWORD PTR [esp+0x4c]
        mov  edx,DWORD PTR [esp+0x50]
        xor  eax,eax
        mov  DWORD PTR [esp+0x28],eax
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x30],eax
        mov  DWORD PTR [esp+0x34],eax
        mov  DWORD PTR [esp+0x38],eax
        mov  DWORD PTR [esp+0x3c],eax
        mov  DWORD PTR [esp+0x40],eax
        mov  edi,ebp
        mov  DWORD PTR [esp+0x44],eax
        imul  edi,esi
        mov  DWORD PTR [esp+0x48],eax
        mov  eax,DWORD PTR [esp+0x54]
        mov  DWORD PTR [esp+0x3c],ecx
        mov  ecx,DWORD PTR [esp+0x58]
        mov  DWORD PTR [esp+0x40],edx
        mov  edx,DWORD PTR [esp+0x14]
        mov  DWORD PTR [esp+0x48],ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esp+0x44],eax
        mov  DWORD PTR [esp+0x28],0x24
        or   ebx,0x18188
        mov  DWORD PTR [esp+0x2c],ebx
        mov  DWORD PTR [esp+0x30],edi
        mov  eax,DWORD PTR [edx+0x90]
        add  eax,0x20
        mov  DWORD PTR [esp+0x38],eax
        mov  eax,DWORD PTR [ecx]
        mov  edx,DWORD PTR [eax]
        push  0x0
        lea  ecx,[esp+0x1c]
        push  ecx
        lea  ecx,[esp+0x30]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0xc]
        test  eax,eax
        jl loc_0044CB12
        mov  eax,DWORD PTR [esp+0x18]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x10]
        push  ecx
        push  0x46743c
        push  eax
        call  DWORD PTR [edx]
        test  eax,eax
        jl loc_0044CB12
        lea  edx,[ebp*8+0x0]
        push  edx
        call operator_new
        mov  ebx,eax
        add  esp,0x4
        test  ebx,ebx
        jne loc_0044CABA
        mov  eax,0x8007000e
        jmp loc_0044CB8E
    loc_0044CABA:
        xor  eax,eax
        test  ebp,ebp
        jbe loc_0044CAE5
        lea  ecx,[esi-0x1]
        jmp loc_0044CAD0
        nop
        nop
    loc_0044CAD0:
        mov  edx,DWORD PTR [esp+0x90]
        mov  DWORD PTR [ebx+eax*8],ecx
        mov  DWORD PTR [ebx+eax*8+0x4],edx
        inc  eax
        add  ecx,esi
        cmp  eax,ebp
        jb loc_0044CAD0
    loc_0044CAE5:
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [eax]
        push  ebx
        push  ebp
        push  eax
        call  DWORD PTR [ecx+0xc]
        xor  ebp,ebp
        cmp  eax,ebp
        mov  eax,DWORD PTR [esp+0x10]
        jge loc_0044CB19
        cmp  eax,ebp
        je loc_0044CB09
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [esp+0x10],ebp
    loc_0044CB09:
        push  ebx
        call _free
        add  esp,0x4
    loc_0044CB12:
        mov  eax,0x80004005
        jmp loc_0044CB8E
    loc_0044CB19:
        cmp  eax,ebp
        je loc_0044CB27
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x10],ebp
    loc_0044CB27:
        push  ebx
        call _free
        push  0x78
        call operator_new
        add  esp,0x8
        mov  DWORD PTR [esp+0x24],eax
        cmp  eax,ebp
        mov  DWORD PTR [esp+0x68],ebp
        je loc_0044CB58
        mov  edx,DWORD PTR [esp+0x14]
        mov  ecx,DWORD PTR [esp+0x18]
        push  esi
        push  edx
        push  edi
        push  ecx
        mov  esi,eax
        call FUN_0044d6a0
        jmp loc_0044CB5A
    loc_0044CB58:
        xor  eax,eax
    loc_0044CB5A:
        mov  edx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [edx],eax
        lea  edi,[eax+0x34]
        mov  ecx,0x9
        lea  esi,[esp+0x28]
        rep movsd
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [eax+0x58],ecx
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [esp+0x90]
        mov  DWORD PTR [eax+0x70],ecx
        mov  edx,DWORD PTR [edx]
        mov  DWORD PTR [edx+0x74],0x0
        xor  eax,eax
    loc_0044CB8E:
        mov  ecx,DWORD PTR [esp+0x60]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        mov  ecx,DWORD PTR [esp+0x50]
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x5c
        ret  0x28
    }
}
