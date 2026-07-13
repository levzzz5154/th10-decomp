// 00406060: FUN_00406060
// Original size: 256 bytes, actual code: 57 instructions
extern "C" void FUN_00405e20(void);
extern "C" void FUN_00405f70(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00406060(void) {
    __asm {
        push  0xffffffff
        push  0x4658ab
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  esi
        push  0x3e0b54
        call operator_new
        mov  esi,eax
        add  esp,0x4
        mov  DWORD PTR [esp+0x4],esi
        test  esi,esi
        mov  DWORD PTR [esp+0x10],0x0
        je loc_004060C8
        push  edi
        push  0x405de0
        push  0x405d00
        push  0x7d1
        push  0x7f0
        lea  eax,[esi+0x60]
        push  eax
        call _eh_vector_constructor_iterator_
        mov  ecx,0xf82d5
        xor  eax,eax
        mov  edi,esi
        rep stosd
        mov  DWORD PTR ds:0x4776f0,esi
        pop  edi
        jmp loc_004060CA
    loc_004060C8:
        xor  esi,esi
    loc_004060CA:
        push  ebx
        mov  ebx,esi
        mov  DWORD PTR [esp+0x14],0xffffffff
        call FUN_00405e20
        test  eax,eax
        pop  ebx
        je loc_00406104
        test  esi,esi
        je loc_004060F2
        push  esi
        call FUN_00405f70
        push  esi
        call _free
        add  esp,0x4
    loc_004060F2:
        xor  eax,eax
        pop  esi
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    loc_00406104:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    }
}
