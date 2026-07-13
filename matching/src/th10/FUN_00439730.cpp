// 00439730: FUN_00439730
// Original size: 352 bytes, actual code: 98 instructions

extern "C" __declspec(naked) void FUN_00439730(void) {
    __asm {
        sub  esp,0x28
        xor  eax,eax
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR [esp+0x4],eax
        mov  DWORD PTR [esp+0x8],eax
        mov  DWORD PTR [esp+0xc],eax
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x14],eax
        mov  DWORD PTR [esp+0x18],eax
        mov  DWORD PTR [esp+0x1c],eax
        push  esi
        mov  DWORD PTR [esp+0x24],eax
        push  0x4
        mov  DWORD PTR [esp+0x2c],eax
        call  DWORD PTR ds:0x466010
        push  0x7f00
        push  0x0
        mov  DWORD PTR [esp+0x28],eax
        call  DWORD PTR ds:0x466260
        lea  ecx,[esp+0x4]
        push  ecx
        mov  DWORD PTR [esp+0x20],eax
        mov  DWORD PTR [esp+0x18],ebx
        mov  DWORD PTR [esp+0xc],0x4390e0
        mov  DWORD PTR ds:0x4924fc,0x1
        mov  DWORD PTR ds:0x492500,0x0
        mov  DWORD PTR [esp+0x2c],0x46f698
        call  DWORD PTR ds:0x4661f8
        mov  al,ds:0x491d65
        test  al,al
        jne loc_004397E4
        push  0x0
        push  ebx
        push  0x0
        push  0x0
        push  0x1e0
        push  0x280
        push  0x0
        push  0x0
        push  0xcf0000
        push  0x46f66c
        push  0x46f698
        push  0x0
        call  DWORD PTR ds:0x466238
        jmp loc_00439834
    loc_004397E4:
        mov  esi,DWORD PTR ds:0x46625c
        push  ebp
        push  edi
        push  0x7
        call  esi
        push  0x8
        lea  edi,[eax+eax*1+0x280]
        call  esi
        push  0x4
        mov  ebp,eax
        call  esi
        push  0x0
        push  ebx
        push  0x0
        push  0x0
        lea  eax,[eax+ebp*2+0x1e0]
        push  eax
        push  edi
        push  0x80000000
        push  0x80000000
        push  0x100a0000
        push  0x46f66c
        push  0x46f698
        push  0x0
        call  DWORD PTR ds:0x466238
        pop  edi
        pop  ebp
    loc_00439834:
        test  eax,eax
        mov  ds:0x4924f0,eax
        mov  ds:0x491c70,eax
        jne loc_0043984C
        mov  eax,0x1
        pop  esi
        add  esp,0x28
        ret
    loc_0043984C:
        mov  esi,DWORD PTR ds:0x466228
        push  0x0
        push  0xf020
        push  0x112
        push  eax
        call  esi
        push  0x10
        call  DWORD PTR ds:0x4660ac
        mov  edx,DWORD PTR ds:0x4924f0
        push  0x0
        push  0xf120
        push  0x112
        push  edx
        call  esi
        xor  eax,eax
        pop  esi
        add  esp,0x28
        ret
    }
}
