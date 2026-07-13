// 0041A050: FUN_0041a050
// Original size: 80 bytes, actual code: 31 instructions
extern "C" void FUN_0041a0a0(void);
extern "C" void FUN_00452730(void);

extern "C" __declspec(naked) void FUN_0041a050(void) {
    __asm {
        mov  edx,edi
        sub  edx,eax
    loc_0041A054:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edx+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_0041A054
        push  0x3a
        push  edi
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        jne loc_0041A074
        mov  eax,edi
        jmp FUN_0041a0a0
    loc_0041A074:
        push  esi
        lea  ecx,[eax+0x1]
        mov  esi,ebx
        sub  esi,ecx
        nop
    loc_0041A080:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [esi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_0041A080
        mov  BYTE PTR [eax],dl
        mov  eax,edi
        call FUN_0041a0a0
        mov  eax,ebx
        pop  esi
        jmp FUN_0041a0a0
    }
}
