// 0044CBF0: FUN_0044cbf0
// Original size: 656 bytes, actual code: 194 instructions
extern "C" void FUN_0044d6a0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044cbf0(void) {
    __asm {
        push  0xffffffff
        push  0x46531b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0x4c
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        mov  ebx,DWORD PTR [esp+0x64]
        mov  DWORD PTR [esp+0x10],ecx
        mov  ecx,DWORD PTR [esp+0x74]
        push  ebp
        mov  ebp,DWORD PTR [esp+0x84]
        push  esi
        mov  DWORD PTR [esp+0x48],ecx
        mov  ecx,DWORD PTR [esp+0x84]
        mov  esi,edx
        mov  edx,DWORD PTR [esp+0x78]
        mov  DWORD PTR [esp+0x54],eax
        mov  eax,DWORD PTR [esp+0x68]
        push  edi
        mov  DWORD PTR [esp+0x54],ecx
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x48],edx
        mov  edx,DWORD PTR [esp+0x84]
        xor  edi,edi
        cmp  ecx,edi
        mov  DWORD PTR [esp+0x18],eax
        mov  DWORD PTR [esp+0x50],edx
        jne loc_0044CC68
        mov  eax,0x800401f0
        jmp loc_0044CE5B
    loc_0044CC68:
        push  0x94
        mov  DWORD PTR [esp+0x18],edi
        mov  DWORD PTR [esp+0x14],edi
        call operator_new
        add  esp,0x4
        cmp  eax,edi
        je loc_0044CC91
        mov  DWORD PTR [eax+0x90],edi
        mov  DWORD PTR [eax],edi
        mov  DWORD PTR [eax+0x2c],edi
        mov  DWORD PTR [eax+0x7c],edi
        mov  edi,eax
    loc_0044CC91:
        mov  edx,DWORD PTR [esp+0x78]
        mov  eax,DWORD PTR [esp+0x74]
        mov  DWORD PTR [edi+0x90],edx
        mov  edx,DWORD PTR [esp+0x48]
        mov  DWORD PTR [edi+0x88],eax
        mov  eax,DWORD PTR [esp+0x4c]
        mov  DWORD PTR [edi+0x80],ebx
        mov  DWORD PTR [edi+0x84],ebx
        xor  ecx,ecx
        mov  DWORD PTR [edi+0x7c],0x1
        mov  DWORD PTR [esp+0x24],ecx
        mov  DWORD PTR [esp+0x28],ecx
        mov  DWORD PTR [esp+0x2c],ecx
        mov  DWORD PTR [esp+0x30],ecx
        mov  DWORD PTR [esp+0x34],ecx
        mov  DWORD PTR [esp+0x38],ecx
        mov  DWORD PTR [esp+0x3c],ecx
        mov  ebx,ebp
        imul  ebx,DWORD PTR [esp+0x90]
        mov  DWORD PTR [esp+0x40],ecx
        mov  DWORD PTR [esp+0x44],ecx
        mov  ecx,DWORD PTR [esp+0x50]
        mov  DWORD PTR [esp+0x38],edx
        mov  edx,DWORD PTR [esp+0x54]
        mov  DWORD PTR [esp+0x40],ecx
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x3c],eax
        mov  DWORD PTR [esp+0x24],0x24
        or   esi,0x18188
        mov  DWORD PTR [esp+0x28],esi
        mov  DWORD PTR [esp+0x2c],ebx
        mov  DWORD PTR [esp+0x44],edx
        mov  eax,DWORD PTR [edi+0x90]
        add  eax,0x20
        mov  DWORD PTR [esp+0x34],eax
        mov  eax,DWORD PTR [ecx]
        mov  edx,DWORD PTR [eax]
        push  0x0
        lea  ecx,[esp+0x18]
        push  ecx
        lea  ecx,[esp+0x2c]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0xc]
        test  eax,eax
        jl loc_0044CDD9
        mov  eax,DWORD PTR [esp+0x14]
        mov  edx,DWORD PTR [eax]
        lea  ecx,[esp+0x10]
        push  ecx
        push  0x46743c
        push  eax
        call  DWORD PTR [edx]
        test  eax,eax
        jl loc_0044CDD9
        lea  edx,[ebp*8+0x0]
        push  edx
        call operator_new
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        jne loc_0044CD82
        mov  eax,0x8007000e
        jmp loc_0044CE5B
    loc_0044CD82:
        xor  eax,eax
        test  ebp,ebp
        jbe loc_0044CDAC
        mov  ecx,DWORD PTR [esp+0x90]
        dec  ecx
    loc_0044CD90:
        mov  edx,DWORD PTR [esp+0x94]
        mov  DWORD PTR [esi+eax*8+0x4],edx
        mov  edx,DWORD PTR [esp+0x90]
        mov  DWORD PTR [esi+eax*8],ecx
        inc  eax
        add  ecx,edx
        cmp  eax,ebp
        jb loc_0044CD90
    loc_0044CDAC:
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [eax]
        push  esi
        push  ebp
        push  eax
        call  DWORD PTR [ecx+0xc]
        xor  ebp,ebp
        cmp  eax,ebp
        mov  eax,DWORD PTR [esp+0x10]
        jge loc_0044CDE3
        cmp  eax,ebp
        je loc_0044CDD0
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [esp+0x10],ebp
    loc_0044CDD0:
        push  esi
        call _free
        add  esp,0x4
    loc_0044CDD9:
        mov  eax,0x80004005
        jmp loc_0044CE5B
    loc_0044CDE3:
        cmp  eax,ebp
        je loc_0044CDF1
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0x10],ebp
    loc_0044CDF1:
        push  esi
        call _free
        push  0x78
        call operator_new
        add  esp,0x8
        mov  DWORD PTR [esp+0x20],eax
        cmp  eax,ebp
        mov  DWORD PTR [esp+0x64],ebp
        je loc_0044CE25
        mov  edx,DWORD PTR [esp+0x90]
        mov  ecx,DWORD PTR [esp+0x14]
        push  edx
        push  edi
        push  ebx
        push  ecx
        mov  esi,eax
        call FUN_0044d6a0
        jmp loc_0044CE27
    loc_0044CE25:
        xor  eax,eax
    loc_0044CE27:
        mov  edx,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [edx],eax
        lea  edi,[eax+0x34]
        mov  ecx,0x9
        lea  esi,[esp+0x24]
        rep movsd
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [eax+0x58],ecx
        mov  eax,DWORD PTR [edx]
        mov  ecx,DWORD PTR [esp+0x94]
        mov  DWORD PTR [eax+0x70],ecx
        mov  edx,DWORD PTR [edx]
        mov  DWORD PTR [edx+0x74],0x0
        xor  eax,eax
    loc_0044CE5B:
        mov  ecx,DWORD PTR [esp+0x5c]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        mov  ecx,DWORD PTR [esp+0x4c]
        pop  ebx
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x58
        ret  0x2c
    }
}
