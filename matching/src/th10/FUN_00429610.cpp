// 00429610: FUN_00429610
// Original size: 224 bytes, actual code: 58 instructions
extern "C" void FUN_00428f60(void);
extern "C" void FUN_004294a0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00429610(void) {
    __asm {
        push  0xffffffff
        push  0x46566b
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
        je loc_0042966F
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
        jmp loc_00429671
    loc_0042966F:
        xor  esi,esi
    loc_00429671:
        mov  ecx,DWORD PTR [esp+0x1c]
        mov  eax,DWORD PTR [esp+0x18]
        push  ebx
        mov  ebx,esi
        mov  DWORD PTR [esp+0x14],0xffffffff
        call FUN_00428f60
        test  eax,eax
        pop  ebx
        je loc_004296B5
        test  esi,esi
        je loc_004296A1
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
    loc_004296A1:
        xor  eax,eax
        pop  esi
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x8
    loc_004296B5:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x8
    }
}
