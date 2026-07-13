// 0042D300: FUN_0042d300
// Original size: 288 bytes, actual code: 85 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);

extern "C" __declspec(naked) void FUN_0042d300(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [ebx+0x20]
        cmp  eax,0x4
        ja loc_0042D405
        push  edi
        jmp  DWORD PTR [eax*4+0x42d40c]
        mov  eax,DWORD PTR [ebx+0x424]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_0042D35A
        push  ebx
        mov  edi,0x58
        call FUN_0042c670
        push  ebx
        mov  edi,0x5a
        call FUN_0042c670
        mov  ecx,DWORD PTR [ebx+0x18]
        push  0xf
        push  0x0
        push  ecx
        lea  edi,[esp+0x10]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebx+0x684],edx
    loc_0042D35A:
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_0042c620
        mov  eax,DWORD PTR [ebx+0x2c]
        test  eax,eax
        je loc_0042D37C
        jg loc_0042D375
        dec  eax
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042D383
    loc_0042D375:
        xor  eax,eax
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042D383
    loc_0042D37C:
        mov  DWORD PTR [ebx+0x24],0x0
    loc_0042D383:
        cmp  DWORD PTR [ebx+0x2b4],0xa
        jle loc_0042D404
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c620
        pop  edi
        mov  eax,0x1
        pop  ecx
        ret
        test  DWORD PTR ds:0x474e36,0x160b
        je loc_0042D404
        push  esi
        mov  esi,0x6
        mov  ecx,0x5a
        mov  eax,ebx
        call FUN_0042c770
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c620
        push  0x0
        mov  edi,0x20
        mov  ecx,0x492590
        call FUN_0043dc90
        lea  eax,[ebx+0x684]
        call FUN_00409e50
        pop  esi
        pop  edi
        mov  eax,0x1
        pop  ecx
        ret
        cmp  DWORD PTR [ebx+0x2b4],0x1e
        jl loc_0042D404
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c5c0
    loc_0042D404:
        pop  edi
    loc_0042D405:
        mov  eax,0x1
        pop  ecx
        ret
        adc  eax,0x830042d3
        rol  DWORD PTR [edx+0x0],cl
        mov  al,ds:0x40042d3
        aam  0x42
        add  bh,ch
        rol  DWORD PTR [edx+0x0],cl
    }
}
