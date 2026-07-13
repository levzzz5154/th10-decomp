// 00412A10: FUN_00412a10
// Original size: 144 bytes, actual code: 32 instructions

extern "C" __declspec(naked) void FUN_00412a10(void) {
    __asm {
        mov  edx,DWORD PTR [eax+0x14d8]
        mov  eax,DWORD PTR [edx+0x4]
        mov  edx,DWORD PTR [eax+0x4]
        push  esi
        movzx esi,WORD PTR [edx+0x8]
        push  edi
        mov  edi,0x1
        shl  edi,cl
        test  edi,esi
        je loc_00412A56
        mov  edx,DWORD PTR [edx+ecx*4+0x10]
        test  edx,edx
        jl loc_00412A45
        lea  ecx,[eax+0x8]
        mov  eax,DWORD PTR [ecx+0x1004]
        add  eax,edx
        pop  edi
        add  eax,ecx
        pop  esi
        ret
    loc_00412A45:
        mov  eax,DWORD PTR [eax+0x1014]
        mov  esi,DWORD PTR [eax]
        push  edx
        mov  ecx,eax
        call  DWORD PTR [esi+0x8]
        pop  edi
        pop  esi
        ret
    loc_00412A56:
        pop  edi
        xor  eax,eax
        pop  esi
        ret
    }
}
