// 0044D080: FUN_0044d080
// Original size: 144 bytes, actual code: 46 instructions
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0044d080(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x10]
        push  edi
        xor  edi,edi
        test  eax,eax
        mov  DWORD PTR [esi],0x4705d8
        jbe loc_0044D0BA
    loc_0044D093:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [eax+edi*4]
        test  ecx,ecx
        lea  eax,[eax+edi*4]
        je loc_0044D0B2
        mov  eax,ecx
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx+edi*4],0x0
    loc_0044D0B2:
        mov  eax,DWORD PTR [esi+0x10]
        inc  edi
        cmp  edi,eax
        jb loc_0044D093
    loc_0044D0BA:
        mov  eax,DWORD PTR [esi+0x4]
        test  eax,eax
        je loc_0044D0D1
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x4],0x0
    loc_0044D0D1:
        mov  edi,DWORD PTR [esi+0xc]
        test  edi,edi
        je loc_0044D105
        cmp  DWORD PTR [edi+0x78],0x1
        jne loc_0044D0F5
        mov  eax,DWORD PTR [edi+0x8c]
        push  eax
        call  DWORD PTR ds:0x4660cc
        mov  DWORD PTR [edi+0x8c],0xffffffff
    loc_0044D0F5:
        push  edi
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0xc],0x0
    loc_0044D105:
        pop  edi
        pop  esi
        ret
    }
}
