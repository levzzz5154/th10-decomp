// 004386B0: FUN_004386b0
// Original size: 115 bytes, actual code: 42 instructions
extern "C" void FUN_0043874c(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_004386b0(void) {
    __asm {
        push  ebp
        mov  ebp,esp
        push  0xffffffff
        push  0x465370
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        sub  esp,0xc
        mov  eax,DWORD PTR [ebp+0x8]
        push  ebx
        push  esi
        mov  ebx,eax
        or   ebx,0xf
        cmp  ebx,0xfffffffe
        push  edi
        mov  esi,ecx
        mov  DWORD PTR [ebp-0x10],esp
        mov  DWORD PTR [ebp-0x14],esi
        jbe loc_004386E7
        mov  ebx,eax
        jmp loc_00438709
    loc_004386E7:
        mov  edi,DWORD PTR [esi+0x18]
        mov  eax,0xaaaaaaab
        mul  ebx
        mov  ecx,edi
        shr  ecx,1
        shr  edx,1
        cmp  edx,ecx
        jae loc_00438709
        mov  eax,0xfffffffe
        sub  eax,ecx
        cmp  edi,eax
        ja loc_00438709
        lea  ebx,[ecx+edi*1]
    loc_00438709:
        lea  ecx,[ebx+0x1]
        push  ecx
        mov  DWORD PTR [ebp-0x4],0x0
        call operator_new
        mov  edx,eax
        add  esp,0x4
        mov  DWORD PTR [ebp+0x8],edx
        jmp FUN_0043874c
    }
}
