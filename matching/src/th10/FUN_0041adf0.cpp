// 0041ADF0: FUN_0041adf0
// Original size: 224 bytes, actual code: 57 instructions
extern "C" void FUN_00449f60(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_0041adf0(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x46541c
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x18],0x0
        mov  eax,DWORD PTR [esp+0x20]
        mov  esi,DWORD PTR [eax+0x8]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        mov  ebx,DWORD PTR ds:0x4660b0
        mov  ebp,DWORD PTR ds:0x4660b4
        je loc_0041AE51
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041AE51:
        mov  ecx,DWORD PTR [esp+0x20]
        mov  esi,DWORD PTR [ecx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0041AE85
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041AE85:
        push  0x41ad60
        mov  DWORD PTR [esp+0x1c],0xffffffff
        mov  edx,DWORD PTR [esp+0x24]
        push  0x896
        push  0x3f0
        add  edx,0x14
        push  edx
        mov  DWORD PTR ds:0x477818,0x0
        call _eh_vector_destructor_iterator_
        mov  ecx,DWORD PTR [esp+0x10]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
