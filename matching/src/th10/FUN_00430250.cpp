// 00430250: FUN_00430250
// Original size: 208 bytes, actual code: 49 instructions
extern "C" void FUN_0042f8b0(void);
extern "C" void FUN_0043dc90(void);

extern "C" __declspec(naked) void FUN_00430250(void) {
    __asm {
        push  esi
        mov  si,WORD PTR [eax+ecx*2+0x59cc]
        push  edi
        movsx edi,si
        cmp  edi,edx
        je loc_00430315
        test  ecx,ecx
        je loc_0043027B
        movsx edi,WORD PTR [eax+0x59cc]
        cmp  edi,edx
        jne loc_0043027B
        mov  WORD PTR [eax+0x59cc],si
    loc_0043027B:
        cmp  ecx,0x1
        je loc_0043029A
        movsx esi,WORD PTR [eax+0x59ce]
        cmp  esi,edx
        jne loc_0043029A
        mov  si,WORD PTR [eax+ecx*2+0x59cc]
        mov  WORD PTR [eax+0x59ce],si
    loc_0043029A:
        cmp  ecx,0x2
        je loc_004302B9
        movsx esi,WORD PTR [eax+0x59d0]
        cmp  esi,edx
        jne loc_004302B9
        mov  si,WORD PTR [eax+ecx*2+0x59cc]
        mov  WORD PTR [eax+0x59d0],si
    loc_004302B9:
        cmp  ecx,0x3
        je loc_004302D8
        movsx esi,WORD PTR [eax+0x59d2]
        cmp  esi,edx
        jne loc_004302D8
        mov  si,WORD PTR [eax+ecx*2+0x59cc]
        mov  WORD PTR [eax+0x59d2],si
    loc_004302D8:
        cmp  ecx,0x4
        je loc_004302F7
        movsx esi,WORD PTR [eax+0x59d4]
        cmp  esi,edx
        jne loc_004302F7
        mov  si,WORD PTR [eax+ecx*2+0x59cc]
        mov  WORD PTR [eax+0x59d4],si
    loc_004302F7:
        mov  WORD PTR [eax+ecx*2+0x59cc],dx
        call FUN_0042f8b0
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00430315:
        pop  edi
        pop  esi
        ret
    }
}
