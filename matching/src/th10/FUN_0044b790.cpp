// 0044B790: FUN_0044b790
// Original size: 80 bytes, actual code: 32 instructions
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_0044b790(void) {
    __asm {
        push  ecx
        cmp  DWORD PTR ds:0x474c38,0xffffffff
        jne loc_0044B79E
        xor  eax,eax
        pop  ecx
        ret
    loc_0044B79E:
        push  esi
        push  edi
        call _malloc
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        jne loc_0044B7BF
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        xor  eax,eax
        pop  esi
        pop  ecx
        ret
    loc_0044B7BF:
        mov  edx,DWORD PTR ds:0x474c38
        push  0x0
        lea  ecx,[esp+0x8]
        push  ecx
        push  edi
        push  esi
        push  edx
        call  DWORD PTR ds:0x4660d0
        mov  eax,esi
        pop  esi
        pop  ecx
        ret
    }
}
