// 00447BB0: FUN_00447bb0
// Original size: 960 bytes, actual code: 61 instructions
extern "C" void FUN_004479d0(void);
extern "C" void _vsprintf(void);
extern "C" void __security_check_cookie(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_00447bb0(void) {
    __asm {
        sub  esp,0x84
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebx
        mov  DWORD PTR [esp+0x84],eax
        mov  al,BYTE PTR [esi+0x3a0]
        test  al,al
        push  ebp
        push  edi
        mov  ebp,0x11
        jbe loc_00447BD9
        movzx ebp,al
    loc_00447BD9:
        mov  ecx,DWORD PTR [esp+0x9c]
        lea  eax,[esp+0xa0]
        push  eax
        push  ecx
        lea  edx,[esp+0x14]
        push  edx
        call _vsprintf
        lea  eax,[esp+0x18]
        add  esp,0xc
        lea  edx,[eax+0x1]
        nop
    loc_00447C00:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00447C00
        mov  ecx,DWORD PTR [esi+0x360]
        mov  edi,DWORD PTR [esi+0x394]
        fld  DWORD PTR [edi+0x34]
        sub  eax,edx
        mov  edx,DWORD PTR [esp+0x98]
        lea  ebx,[ebp-0x1]
        imul  ebx,eax
        shr  ecx,1
        and  ecx,0x1
        push  ecx
        push  edx
        shr  ebx,0x2
        call FUN_00463b2c
        cdq
        sub  eax,edx
        sar  eax,1
        sub  eax,ebx
        push  eax
        mov  eax,DWORD PTR [edi+0x4]
        push  eax
        lea  ebx,[esp+0x1c]
        mov  eax,ebp
        call FUN_004479d0
        mov  eax,DWORD PTR [esi+0x35c]
        mov  ecx,DWORD PTR [esp+0x8c]
        pop  edi
        pop  ebp
        or   eax,0x1
        pop  ebx
        xor  ecx,esp
        mov  DWORD PTR [esi+0x35c],eax
        call __security_check_cookie
        add  esp,0x84
        ret
    }
}
