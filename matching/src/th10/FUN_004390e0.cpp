// 004390E0: FUN_004390e0
// Original size: 272 bytes, actual code: 98 instructions
extern "C" void FUN_0043aeb0(void);

extern "C" __declspec(naked) void FUN_004390e0(void) {
    __asm {
        push  ebx
        mov  ebx,DWORD PTR [esp+0x10]
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        push  esi
        mov  esi,DWORD PTR [esp+0x1c]
        push  edi
        mov  edi,DWORD PTR [esp+0x18]
        cmp  edi,0x20
        ja loc_004391A1
        je loc_0043914B
        cmp  edi,0x10
        je loc_00439135
        cmp  edi,0x14
        je loc_0043913F
        cmp  edi,0x1c
        jne loc_004391D8
        xor  eax,eax
        test  ebx,ebx
        push  esi
        sete  al
        push  ebx
        push  edi
        push  ebp
        mov  DWORD PTR ds:0x4924fc,ebx
        mov  ds:0x492500,eax
        call  DWORD PTR ds:0x466248
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x10
    loc_00439135:
        or   DWORD PTR ds:0x491ff4,0x80
    loc_0043913F:
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x10
    loc_0043914B:
        mov  al,ds:0x491d65
        test  al,al
        jne loc_00439179
        mov  eax,ds:0x492500
        test  eax,eax
        jne loc_00439179
        push  0x0
        call  DWORD PTR ds:0x466230
        push  0x0
        call  DWORD PTR ds:0x466224
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x10
    loc_00439179:
        push  0x7f00
        push  0x0
        call  DWORD PTR ds:0x466260
        push  eax
        call  DWORD PTR ds:0x466224
        push  0x1
        call  DWORD PTR ds:0x466230
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x10
    loc_004391A1:
        cmp  edi,0x201
        je loc_004391D1
        cmp  edi,0x3c9
        jne loc_004391D8
        mov  edx,DWORD PTR ds:0x491fe8
        test  edx,edx
        je loc_004391D8
        call FUN_0043aeb0
        push  esi
        push  ebx
        push  edi
        push  ebp
        call  DWORD PTR ds:0x466248
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x10
    loc_004391D1:
        push  ebp
        call  DWORD PTR ds:0x4661f0
    loc_004391D8:
        push  esi
        push  ebx
        push  edi
        push  ebp
        call  DWORD PTR ds:0x466248
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x10
    }
}
