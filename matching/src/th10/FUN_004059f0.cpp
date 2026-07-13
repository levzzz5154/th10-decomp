// 004059F0: FUN_004059f0
// Original size: 208 bytes, actual code: 76 instructions

extern "C" __declspec(naked) void FUN_004059f0(void) {
    __asm {
        mov  edx,DWORD PTR [ecx+0x28]
        test  edx,edx
        jne loc_004059FA
        xor  eax,eax
        ret
    loc_004059FA:
        fld  DWORD PTR [eax+0x4]
        xor  edx,edx
        fsub  DWORD PTR [ecx+0x34]
        fld  DWORD PTR [eax]
        fsub  DWORD PTR [ecx+0x30]
        fld  DWORD PTR [ecx+0x3c]
        fld  st(1)
        fmul  st,st(2)
        fld  st(3)
        fmul  st,st(4)
        faddp st(1),st
        fld  st(1)
        fmul  st,st(2)
        fcompp
        fstp  st(0)
        fnstsw ax
        fstp  st(0)
        test  ah,0x41
        fstp  st(0)
        jne loc_00405A68
        mov  eax,DWORD PTR [ecx+0x44]
        test  eax,eax
        mov  eax,ds:0x4776f4
        mov  cl,BYTE PTR [eax+0x378c]
        jne loc_00405A46
        test  cl,0x1
        je loc_00405A53
        mov  edx,0x3
        mov  eax,edx
        ret
    loc_00405A46:
        test  cl,0x1
        je loc_00405A53
        mov  edx,0x26
        mov  eax,edx
        ret
    loc_00405A53:
        mov  eax,ds:0x477704
        mov  edx,DWORD PTR [eax+0x10]
        neg  edx
        sbb  edx,edx
        and  edx,0x21
        add  edx,0x5
        mov  eax,edx
        ret
    loc_00405A68:
        mov  eax,ds:0x4776f4
        test  BYTE PTR [eax+0x378c],0x1
        je loc_00405A8F
        cmp  DWORD PTR [ecx+0x44],0x1
        jne loc_00405AB7
        mov  edx,DWORD PTR ds:0x474c68
        neg  edx
        sbb  edx,edx
        and  edx,0xfffffffd
        add  edx,0x1a
        mov  eax,edx
        ret
    loc_00405A8F:
        mov  eax,ds:0x477704
        push  esi
        mov  esi,DWORD PTR [eax+0x10]
        test  esi,esi
        pop  esi
        je loc_00405AB7
        mov  eax,DWORD PTR [ecx+0x44]
        test  eax,eax
        jne loc_00405AB7
        mov  eax,ds:0x474c68
        xor  edx,edx
        test  eax,eax
        sete  dl
        lea  edx,[edx*4+0x10]
    loc_00405AB7:
        mov  eax,edx
        ret
    }
}
