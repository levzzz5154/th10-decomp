// 00420670: FUN_00420670
// Original size: 512 bytes, actual code: 152 instructions
extern "C" void FUN_0044b810(void);
extern "C" void _malloc(void);
extern "C" void __beginthread(void);

extern "C" __declspec(naked) void FUN_00420670(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        push  edi
        mov  edi,eax
        mov  eax,DWORD PTR [esi+0x50c]
        xor  ebp,ebp
        cmp  eax,ebp
        je loc_0042069C
        mov  ebx,DWORD PTR ds:0x4660ac
        lea  ebx,[ebx+0x0]
    loc_00420690:
        push  0xa
        call  ebx
        cmp  DWORD PTR [esi+0x50c],ebp
        jne loc_00420690
    loc_0042069C:
        mov  eax,DWORD PTR [esi+0x8]
        lea  edx,[esp+0xc]
        push  edx
        push  ebp
        push  ebp
        push  ebp
        mov  DWORD PTR [esp+0x1c],ebp
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        lea  eax,[esi+0x510]
        xor  ecx,ecx
        mov  edx,eax
        mov  DWORD PTR [edx],ecx
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],ecx
        mov  WORD PTR [edx+0xc],cx
        mov  WORD PTR [eax],0x4d42
        mov  eax,0x36
        mov  ecx,esi
        sub  ecx,edi
        mov  DWORD PTR [esi+0x51a],eax
        mov  DWORD PTR [esi+0x512],eax
        mov  eax,edi
        lea  edx,[ecx+0x528]
        nop
    loc_004206F0:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_004206F0
        mov  eax,DWORD PTR [esi+0xec]
        sub  eax,0x16
        je loc_00420738
        dec  eax
        mov  ecx,0x474f70
        je loc_00420726
        push  0x46deb0
        call FUN_0044b810
        add  esp,0x4
        pop  edi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        add  esp,0xc
        ret
    loc_00420726:
        push  0x46df38
        call FUN_0044b810
        add  esp,0x4
        jmp loc_00420851
    loc_00420738:
        push  0x2c
        call _malloc
        mov  edi,eax
        add  esp,0x4
        cmp  edi,ebp
        mov  DWORD PTR [esi+0x520],edi
        jne loc_00420765
    loc_0042074E:
        push  0x46def0
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        jmp loc_00420851
    loc_00420765:
        xor  eax,eax
        mov  ecx,0xb
        push  0xe1000
        rep stosd
        call _malloc
        add  esp,0x4
        cmp  eax,ebp
        mov  DWORD PTR [esi+0x524],eax
        je loc_0042074E
        add  DWORD PTR [esi+0x512],0xe1000
        mov  edx,DWORD PTR [esi+0x520]
        mov  WORD PTR [edx+0xe],0x18
        mov  eax,DWORD PTR [esi+0x520]
        mov  DWORD PTR [eax],0x28
        mov  ecx,DWORD PTR [esi+0x520]
        mov  DWORD PTR [ecx+0x4],0x280
        mov  edx,DWORD PTR [esi+0x520]
        mov  DWORD PTR [edx+0x8],0x1e0
        mov  eax,DWORD PTR [esi+0x520]
        mov  WORD PTR [eax+0xc],0x1
        mov  ecx,DWORD PTR [esi+0x520]
        push  ebp
        mov  DWORD PTR [ecx+0x10],ebp
        mov  eax,DWORD PTR [esp+0x10]
        mov  edx,DWORD PTR [eax]
        push  ebp
        lea  ecx,[esp+0x18]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x34]
        mov  ebp,0x1df
        xor  edx,edx
        mov  edi,edi
    loc_004207F0:
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [esi+0x524]
        imul  eax,ebp
        mov  edi,DWORD PTR [esp+0x14]
        add  ecx,edx
        add  eax,edi
        mov  edi,0x280
        lea  ebx,[ebx+0x0]
    loc_00420810:
        mov  bx,WORD PTR [eax]
        mov  WORD PTR [ecx],bx
        mov  bl,BYTE PTR [eax+0x2]
        mov  BYTE PTR [ecx+0x2],bl
        add  eax,0x4
        add  ecx,0x3
        dec  edi
        jne loc_00420810
        dec  ebp
        add  edx,0x780
        cmp  ebp,0xffffffff
        jg loc_004207F0
        mov  eax,DWORD PTR [esp+0xc]
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x38]
        push  0x0
        push  0x0
        push  0x420540
        call __beginthread
        add  esp,0xc
        mov  ds:0x492134,eax
    loc_00420851:
        mov  eax,DWORD PTR [esp+0xc]
        test  eax,eax
        je loc_0042085F
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
    loc_0042085F:
        pop  edi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0xc
        ret
    }
}
