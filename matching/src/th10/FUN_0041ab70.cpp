// 0041AB70: FUN_0041ab70
// Original size: 496 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_0041ab70(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR [esp+0x8]
        mov  DWORD PTR [eax+0x1b4],esi
        movzx esi,BYTE PTR [esp+0xc]
        mov  DWORD PTR [eax+0x1b8],esi
        mov  esi,DWORD PTR [edx]
        mov  DWORD PTR [eax+0x180],esi
        mov  edx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [eax+0x184],edx
        mov  edx,DWORD PTR [ecx]
        mov  DWORD PTR [eax+0x188],edx
        mov  ecx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [eax+0x18c],ecx
        mov  ecx,DWORD PTR [eax+0x1b0]
        xor  edx,edx
        test  cl,0x1
        pop  esi
        jne loc_0041ABDF
        or   ecx,0x1
        mov  DWORD PTR [eax+0x1a4],edx
        mov  DWORD PTR [eax+0x1a0],0xfff0bdc1
        mov  DWORD PTR [eax+0x1a8],edx
        mov  DWORD PTR [eax+0x1ac],0x476f78
        mov  DWORD PTR [eax+0x1b0],ecx
    loc_0041ABDF:
        mov  DWORD PTR [eax+0x1a4],edx
        mov  DWORD PTR [eax+0x1a8],edx
        mov  DWORD PTR [eax+0x1a0],0xffffffff
        ret  0x8
    }
}
