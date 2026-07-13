// 0044B540: FUN_0044b540
// Original size: 224 bytes, actual code: 65 instructions

extern "C" __declspec(naked) void FUN_0044b540(void) {
    __asm {
        push  ecx
        push  esi
        push  0x4922a4
        call  DWORD PTR ds:0x4660b0
        mov  al,ds:0x49231e
        push  0x0
        push  0x80
        push  0x2
        push  0x0
        inc  al
        push  0x1
        mov  ds:0x49231e,al
        mov  eax,DWORD PTR [esp+0x20]
        push  0x40000000
        push  eax
        call  DWORD PTR ds:0x4660c4
        mov  esi,eax
        cmp  esi,0xffffffff
        push  0x0
        jne loc_0044B5C2
        push  0x0
        lea  ecx,[esp+0x14]
        push  ecx
        push  0x400
        call  DWORD PTR ds:0x46610c
        push  eax
        push  0x0
        push  0x1300
        call  DWORD PTR ds:0x466124
        mov  edx,DWORD PTR [esp+0xc]
        push  edx
        call  DWORD PTR ds:0x466128
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        mov  eax,esi
        pop  esi
        pop  ecx
        ret  0x8
    loc_0044B5C2:
        mov  ecx,DWORD PTR [esp+0x14]
        lea  eax,[esp+0x8]
        push  eax
        push  edi
        push  ecx
        push  esi
        call  DWORD PTR ds:0x4660d4
        cmp  edi,DWORD PTR [esp+0x4]
        push  esi
        je loc_0044B5FC
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        mov  eax,0xfffffffe
        pop  esi
        pop  ecx
        ret  0x8
    loc_0044B5FC:
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        xor  eax,eax
        pop  esi
        pop  ecx
        ret  0x8
    }
}
