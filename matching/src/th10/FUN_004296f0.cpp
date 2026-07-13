// 004296F0: FUN_004296f0
// Original size: 192 bytes, actual code: 54 instructions
extern "C" void FUN_004294a0(void);
extern "C" void FUN_0042a200(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_004296f0(void) {
    __asm {
        push  0xffffffff
        push  0x46564b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  esi
        push  0x2d4
        call operator_new
        mov  esi,eax
        add  esp,0x4
        mov  DWORD PTR [esp+0x4],esi
        test  esi,esi
        mov  DWORD PTR [esp+0x10],0x0
        je loc_0042974F
        push  edi
        push  0x42ac60
        push  0x42ac20
        push  0x8
        push  0x24
        lea  eax,[esi+0xa0]
        push  eax
        call _eh_vector_constructor_iterator_
        mov  ecx,0xb5
        xor  eax,eax
        mov  edi,esi
        rep stosd
        pop  edi
        jmp loc_00429751
    loc_0042974F:
        xor  esi,esi
    loc_00429751:
        mov  ecx,DWORD PTR [esp+0x18]
        mov  DWORD PTR [esp+0x10],0xffffffff
        push  ecx
        mov  DWORD PTR [esi+0x10],0x2
        call FUN_0042a200
        test  eax,eax
        je loc_00429791
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
        xor  eax,eax
        pop  esi
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    loc_00429791:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    }
}
