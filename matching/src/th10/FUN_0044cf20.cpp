// 0044CF20: FUN_0044cf20
// Original size: 352 bytes, actual code: 133 instructions
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0044cf20(void) {
    __asm {
        push  ecx
        mov  eax,DWORD PTR [esi+0x10]
        push  ebx
        push  ebp
        xor  ebx,ebx
        push  edi
        xor  edi,edi
        cmp  eax,ebx
        mov  DWORD PTR [esi+0x30],ebx
        jbe loc_0044CF55
    loc_0044CF32:
        mov  eax,DWORD PTR [esi+0x4]
        mov  ecx,DWORD PTR [eax+edi*4]
        cmp  ecx,ebx
        lea  eax,[eax+edi*4]
        je loc_0044CF4D
        mov  eax,ecx
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx+edi*4],ebx
    loc_0044CF4D:
        mov  eax,DWORD PTR [esi+0x10]
        inc  edi
        cmp  edi,eax
        jb loc_0044CF32
    loc_0044CF55:
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,ebx
        je loc_0044CF68
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x4],ebx
    loc_0044CF68:
        mov  eax,DWORD PTR [esi+0x10]
        shl  eax,0x2
        push  eax
        mov  DWORD PTR [esp+0x10],ebx
        call operator_new
        mov  DWORD PTR [esi+0x4],eax
        mov  eax,DWORD PTR [esi+0x10]
        add  esp,0x4
        cmp  eax,ebx
        jbe loc_0044D03C
        lea  ebp,[esi+0x34]
        nop
    loc_0044CF90:
        mov  ecx,DWORD PTR [esi+0x58]
        mov  eax,DWORD PTR [ecx]
        mov  ecx,DWORD PTR [esi+0x4]
        mov  edx,DWORD PTR [eax]
        push  0x0
        lea  edi,[ebx*4+0x0]
        add  ecx,edi
        push  ecx
        push  ebp
        push  eax
        call  DWORD PTR [edx+0xc]
        test  eax,eax
        jl loc_0044D068
        mov  edx,DWORD PTR [esi+0x4]
        mov  edi,DWORD PTR [edi+edx*1]
        mov  eax,DWORD PTR [edi]
        lea  ecx,[esp+0xc]
        push  ecx
        push  0x46743c
        push  edi
        call  DWORD PTR [eax]
        test  eax,eax
        jl loc_0044D068
        push  0x80
        call operator_new
        mov  edi,eax
        add  esp,0x4
        test  edi,edi
        je loc_0044D043
        xor  eax,eax
    loc_0044CFE5:
        mov  edx,DWORD PTR [esi+0x6c]
        lea  ecx,[eax+0x1]
        imul  edx,ecx
        dec  edx
        mov  DWORD PTR [edi+eax*8],edx
        mov  edx,DWORD PTR [esi+0x70]
        mov  DWORD PTR [edi+eax*8+0x4],edx
        mov  eax,ecx
        cmp  eax,0x10
        jb loc_0044CFE5
        mov  eax,DWORD PTR [esp+0xc]
        mov  ecx,DWORD PTR [eax]
        push  edi
        push  0x10
        push  eax
        call  DWORD PTR [ecx+0xc]
        test  eax,eax
        mov  eax,DWORD PTR [esp+0xc]
        jl loc_0044D04D
        test  eax,eax
        je loc_0044D027
        mov  edx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [edx+0x8]
        mov  DWORD PTR [esp+0xc],0x0
    loc_0044D027:
        push  edi
        call _free
        mov  eax,DWORD PTR [esi+0x10]
        add  esp,0x4
        inc  ebx
        cmp  ebx,eax
        jb loc_0044CF90
    loc_0044D03C:
        pop  edi
        pop  ebp
        xor  eax,eax
        pop  ebx
        pop  ecx
        ret
    loc_0044D043:
        pop  edi
        pop  ebp
        mov  eax,0x8007000e
        pop  ebx
        pop  ecx
        ret
    loc_0044D04D:
        test  eax,eax
        je loc_0044D05F
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esp+0xc],0x0
    loc_0044D05F:
        push  edi
        call _free
        add  esp,0x4
    loc_0044D068:
        pop  edi
        pop  ebp
        mov  eax,0x80004005
        pop  ebx
        pop  ecx
        ret
    }
}
