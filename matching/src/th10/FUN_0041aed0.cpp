// 0041AED0: FUN_0041aed0
// Original size: 256 bytes, actual code: 58 instructions
extern "C" void FUN_0041ad90(void);
extern "C" void FUN_0041adf0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);
extern "C" void _eh_vector_constructor_iterator_(void);

extern "C" __declspec(naked) void FUN_0041aed0(void) {
    __asm {
        push  0xffffffff
        push  0x46580b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  esi
        push  0x21cec0
        call operator_new
        mov  esi,eax
        add  esp,0x4
        mov  DWORD PTR [esp+0x4],esi
        test  esi,esi
        mov  DWORD PTR [esp+0x10],0x0
        je loc_0041AF3B
        push  edi
        push  0x41ad60
        push  0x41acf0
        push  0x896
        push  0x3f0
        lea  eax,[esi+0x14]
        push  eax
        call _eh_vector_constructor_iterator_
        xor  eax,eax
        mov  ecx,0x873b0
        mov  edi,esi
        rep stosd
        or   DWORD PTR [esi],0x2
        mov  DWORD PTR ds:0x477818,esi
        pop  edi
        jmp loc_0041AF3D
    loc_0041AF3B:
        xor  esi,esi
    loc_0041AF3D:
        push  ebx
        mov  ebx,esi
        mov  DWORD PTR [esp+0x14],0xffffffff
        call FUN_0041ad90
        test  eax,eax
        pop  ebx
        je loc_0041AF77
        test  esi,esi
        je loc_0041AF65
        push  esi
        call FUN_0041adf0
        push  esi
        call _free
        add  esp,0x4
    loc_0041AF65:
        xor  eax,eax
        pop  esi
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    loc_0041AF77:
        mov  ecx,DWORD PTR [esp+0x8]
        mov  eax,esi
        pop  esi
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    }
}
