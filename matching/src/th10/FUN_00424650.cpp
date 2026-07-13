// 00424650: FUN_00424650
// Original size: 112 bytes, actual code: 33 instructions
extern "C" void FUN_0041a120(void);

extern "C" __declspec(naked) void FUN_00424650(void) {
    __asm {
        mov  eax,ds:0x474c7c
        lea  eax,[eax+eax*2]
        mov  eax,DWORD PTR [esi+eax*4+0x7c]
        test  eax,eax
        je loc_00424676
    loc_00424660:
        mov  edx,DWORD PTR [eax+0x4]
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax+0x70]
        test  ecx,ecx
        jle loc_00424670
        dec  ecx
        mov  DWORD PTR [eax+0x70],ecx
    loc_00424670:
        test  edx,edx
        mov  eax,edx
        jne loc_00424660
    loc_00424676:
        mov  ecx,DWORD PTR [esp+0x4]
        push  ebx
        mov  ebx,DWORD PTR [esp+0xc]
        push  ecx
        push  esi
        call FUN_0041a120
        mov  edx,DWORD PTR [eax+0x60]
        add  edx,0xffffffc4
        mov  ecx,edx
        test  ecx,ecx
        mov  DWORD PTR [eax+0x60],edx
        pop  ebx
        jg loc_0042469D
        mov  DWORD PTR [eax+0x60],0x1
    loc_0042469D:
        mov  DWORD PTR [eax+0x6c],0x5a
        mov  DWORD PTR [eax+0x84],0xffff8080
        mov  DWORD PTR [eax+0x70],0x1e
        ret  0x8
    }
}
