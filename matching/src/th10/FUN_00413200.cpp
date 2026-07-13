// 00413200: FUN_00413200
// Original size: 112 bytes, actual code: 9 instructions

extern "C" __declspec(naked) void FUN_00413200(void) {
    __asm {
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_00413210
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00413210:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
        ret
    }
}
