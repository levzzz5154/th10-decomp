// 0043CD30: FUN_0043cd30
// Original size: 1008 bytes, actual code: 229 instructions
extern "C" void FUN_0043d390(void);
extern "C" void FUN_0044b810(void);
extern "C" void FUN_0044c7e0(void);
extern "C" void Ordinal_11(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043cd30(void) {
    __asm {
        sub  esp,0x4c
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x48],eax
        or   eax,0xffffffff
        push  ebp
        push  esi
        mov  esi,ecx
        mov  ebp,DWORD PTR [esp+0x58]
        push  edi
        lea  edi,[esi+0x408]
        mov  ecx,0x80
        rep stosd
        or   eax,0xffffffff
        mov  DWORD PTR [esi+0x620],eax
        mov  DWORD PTR [esi+0x624],eax
        mov  DWORD PTR [esi+0x628],eax
        mov  DWORD PTR [esi+0x62c],eax
        mov  DWORD PTR [esi+0x630],eax
        mov  DWORD PTR [esi+0x634],eax
        mov  DWORD PTR [esi+0x638],eax
        mov  DWORD PTR [esi+0x63c],eax
        mov  DWORD PTR [esi+0x640],eax
        mov  DWORD PTR [esi+0x644],eax
        mov  DWORD PTR [esi+0x648],eax
        push  0x4
        mov  DWORD PTR [esi+0x64c],eax
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0043CDBA
        mov  DWORD PTR [eax],0x0
        mov  edi,eax
        jmp loc_0043CDBC
    loc_0043CDBA:
        xor  edi,edi
    loc_0043CDBC:
        mov  DWORD PTR [esi+0x610],edi
        mov  eax,DWORD PTR [edi]
        test  eax,eax
        je loc_0043CDD4
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi],0x0
    loc_0043CDD4:
        push  0x0
        push  edi
        push  0x0
        call Ordinal_11
        test  eax,eax
        jl loc_0043CFB8
        mov  eax,DWORD PTR [edi]
        mov  edx,DWORD PTR [eax]
        push  0x2
        push  ebp
        push  eax
        call  DWORD PTR [edx+0x18]
        test  eax,eax
        jl loc_0043CFB8
        push  ebx
        push  edi
        mov  ecx,0x10
        mov  edi,0xac44
        mov  ebx,0x2
        call FUN_0044c7e0
        mov  edx,DWORD PTR [esi+0x610]
        mov  eax,DWORD PTR [edx]
        xor  ecx,ecx
        mov  DWORD PTR [esp+0x34],ecx
        mov  DWORD PTR [esp+0x38],ecx
        mov  DWORD PTR [esp+0x3c],ecx
        xor  edx,edx
        mov  DWORD PTR [esp+0x14],edx
        mov  DWORD PTR [esp+0x40],ecx
        mov  DWORD PTR [esp+0x18],edx
        mov  DWORD PTR [esp+0x44],ecx
        mov  DWORD PTR [esp+0x1c],edx
        mov  DWORD PTR [esp+0x20],edx
        xor  edi,edi
        mov  DWORD PTR [esp+0x48],ecx
        mov  DWORD PTR [esi],eax
        mov  WORD PTR [esp+0x16],bx
        push  edi
        mov  WORD PTR [esp+0x28],dx
        mov  DWORD PTR [esp+0x50],ecx
        lea  eax,[esp+0x18]
        lea  ebx,[esi+0x608]
        push  ebx
        mov  DWORD PTR [esp+0x58],ecx
        mov  DWORD PTR [esp+0x4c],eax
        mov  eax,DWORD PTR [esi]
        lea  edx,[esp+0x3c]
        push  edx
        mov  DWORD PTR [esi+0x618],edi
        mov  DWORD PTR [esp+0x60],ecx
        mov  DWORD PTR [esp+0x40],0x24
        mov  DWORD PTR [esp+0x44],0x8008
        mov  DWORD PTR [esp+0x48],0x8000
        mov  WORD PTR [esp+0x30],di
        mov  WORD PTR [esp+0x20],0x1
        mov  DWORD PTR [esp+0x24],0xac44
        mov  DWORD PTR [esp+0x28],0x2b110
        mov  WORD PTR [esp+0x2c],0x4
        mov  WORD PTR [esp+0x2e],0x10
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xc]
        test  eax,eax
        jl loc_0043D02A
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax]
        push  edi
        lea  edx,[esp+0x30]
        push  edx
        lea  edx,[esp+0x30]
        push  edx
        lea  edx,[esp+0x3c]
        push  edx
        lea  edx,[esp+0x20]
        push  edx
        push  0x8000
        push  edi
        push  eax
        call  DWORD PTR [ecx+0x2c]
        test  eax,eax
        jl loc_0043D02A
        mov  edi,DWORD PTR [esp+0x10]
        xor  eax,eax
        mov  ecx,0x2000
        rep stosd
        mov  edx,DWORD PTR [esp+0x2c]
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax]
        push  edx
        mov  edx,DWORD PTR [esp+0x2c]
        push  edx
        mov  edx,DWORD PTR [esp+0x38]
        push  edx
        mov  edx,DWORD PTR [esp+0x1c]
        push  edx
        push  eax
        call  DWORD PTR [ecx+0x4c]
        mov  ebx,DWORD PTR [ebx]
        mov  eax,DWORD PTR [ebx]
        push  0x1
        push  0x0
        push  0x0
        push  ebx
        call  DWORD PTR [eax+0x30]
        push  0x0
        push  0xfa
        mov  eax,0x64
        push  0x0
        push  ebp
        mov  DWORD PTR [esi+0x52c4],eax
        mov  DWORD PTR [esi+0x52c8],eax
        call  DWORD PTR ds:0x466218
        mov  DWORD PTR [esi+0x60c],ebp
        xor  esi,esi
        jmp loc_0043CF60
        nop
        mov  edi,edi
    loc_0043CF60:
        cmp  DWORD PTR ds:0x4977b4,0x2
        je loc_0043D02A
        mov  ecx,DWORD PTR [esi*4+0x474b40]
        push  ecx
        mov  ecx,esi
        mov  edx,0x492590
        call FUN_0043d390
        test  eax,eax
        jne loc_0043D010
        inc  esi
        cmp  esi,0x25
        jl loc_0043CF60
        push  0x46fdac
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        pop  ebx
        pop  edi
        pop  esi
        xor  eax,eax
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_0043CFB8:
        push  0x46fe0c
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  edi,DWORD PTR [esi+0x610]
        add  esp,0x4
        test  edi,edi
        je loc_0043CFF9
        mov  eax,DWORD PTR [edi]
        test  eax,eax
        je loc_0043CFE6
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi],0x0
    loc_0043CFE6:
        push  edi
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x610],0x0
    loc_0043CFF9:
        pop  edi
        pop  esi
        or   eax,0xffffffff
        pop  ebp
        mov  ecx,DWORD PTR [esp+0x48]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    loc_0043D010:
        mov  edx,DWORD PTR [esi*4+0x474b40]
        push  edx
        push  0x46fdd4
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x8
    loc_0043D02A:
        mov  ecx,DWORD PTR [esp+0x58]
        pop  ebx
        pop  edi
        pop  esi
        pop  ebp
        xor  ecx,esp
        or   eax,0xffffffff
        call __security_check_cookie
        add  esp,0x4c
        ret  0x4
    }
}
