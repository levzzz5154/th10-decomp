// 00437D10: FUN_00437d10
// Original size: 160 bytes, actual code: 51 instructions
extern "C" void FUN_00436a30(void);

extern "C" __declspec(naked) void FUN_00437d10(void) {
    __asm {
        push  esi
        mov  esi,0x474cb0
        call FUN_00436a30
        mov  eax,ds:0x4918a0
        mov  esi,DWORD PTR ds:0x466030
        push  eax
        call  esi
        mov  ecx,DWORD PTR ds:0x49189c
        push  ecx
        call  esi
        mov  edx,DWORD PTR ds:0x491898
        push  edx
        call  esi
        mov  eax,ds:0x491894
        push  eax
        call  esi
        mov  ecx,DWORD PTR ds:0x491890
        push  ecx
        call  esi
        mov  edx,DWORD PTR ds:0x49188c
        push  edx
        call  esi
        mov  eax,ds:0x491888
        push  eax
        call  esi
        mov  ecx,DWORD PTR ds:0x491884
        push  ecx
        call  esi
        mov  edx,DWORD PTR ds:0x491880
        push  edx
        call  esi
        mov  eax,ds:0x49187c
        push  eax
        call  esi
        mov  ecx,DWORD PTR ds:0x491878
        push  ecx
        call  esi
        mov  edx,DWORD PTR ds:0x491874
        push  edx
        call  esi
        mov  eax,ds:0x491870
        push  eax
        call  esi
        mov  ecx,DWORD PTR ds:0x49186c
        push  ecx
        call  esi
        mov  edx,DWORD PTR ds:0x491868
        push  edx
        call  esi
        pop  esi
        ret
    }
}
