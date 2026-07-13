// 004073E0: FUN_004073e0
// Original size: 208 bytes, actual code: 68 instructions
extern "C" void FUN_004067d0(void);
extern "C" void FUN_0043dd10(void);

extern "C" __declspec(naked) void FUN_004073e0(void) {
    __asm {
        push  ecx
        push  ebx
        mov  ebx,eax
        mov  eax,ds:0x477834
        fld  DWORD PTR [eax+0x3c0]
        push  esi
        fsub  DWORD PTR [ebx+0x4]
        fld  DWORD PTR [eax+0x3c4]
        fsub  DWORD PTR [ebx+0x8]
        fld  DWORD PTR ds:0x470b04
        fld  st(1)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0040742C
        fld  DWORD PTR ds:0x470b04
        fld  st(2)
        fucompp
        fnstsw ax
        test  ah,0x44
        jp loc_0040742C
        fstp  st(0)
        mov  DWORD PTR [esp+0x8],0x3fc90fdb
        fstp  st(0)
        jmp loc_00407434
    loc_0040742C:
        fxch  st(1)
        fpatan
        fstp  DWORD PTR [esp+0x8]
    loc_00407434:
        push  edi
        xor  edi,edi
        cmp  WORD PTR [ebx+0x1f6],di
        jle loc_0040747A
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
    loc_00407445:
        xor  esi,esi
        cmp  WORD PTR [ebx+0x1f4],si
        jle loc_0040746D
    loc_00407450:
        mov  eax,DWORD PTR [esp+0x18]
        push  ebp
        push  edi
        push  esi
        push  eax
        call FUN_004067d0
        test  eax,eax
        jne loc_00407479
        movsx ecx,WORD PTR [ebx+0x1f4]
        inc  esi
        cmp  esi,ecx
        jl loc_00407450
    loc_0040746D:
        movsx edx,WORD PTR [ebx+0x1f6]
        inc  edi
        cmp  edi,edx
        jl loc_00407445
    loc_00407479:
        pop  ebp
    loc_0040747A:
        mov  eax,DWORD PTR [ebx+0x1fc]
        test  ah,0x2
        pop  edi
        je loc_0040749A
        mov  eax,DWORD PTR [ebx+0x4]
        mov  ebx,DWORD PTR [ebx+0x200]
        push  eax
        mov  esi,0x492590
        call FUN_0043dd10
    loc_0040749A:
        pop  esi
        xor  eax,eax
        pop  ebx
        pop  ecx
        ret  0x4
    }
}
