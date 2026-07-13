// 0042AA50: FUN_0042aa50
// Original size: 208 bytes, actual code: 40 instructions
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0042aa50(void) {
    __asm {
        push  0x6284
        call operator_new
        mov  edx,eax
        add  esp,0x4
        test  edx,edx
        je loc_0042AA9E
        push  edi
        xor  eax,eax
        mov  ecx,0x18a1
        mov  edi,edx
        rep stosd
        mov  DWORD PTR [edx+0x5460],edx
        lea  eax,[edx+0x5464]
        mov  DWORD PTR [edx+0x6274],eax
        mov  DWORD PTR [edx+0x6278],edx
        mov  DWORD PTR [edx+0x627c],0x0
        mov  DWORD PTR [edx+0x6280],0x0
        pop  edi
        jmp loc_0042AAA0
    loc_0042AA9E:
        xor  edx,edx
    loc_0042AAA0:
        lea  eax,[edx+0x6278]
        mov  edx,DWORD PTR [esp+0x4]
        lea  ecx,[esi+esi*2+0xf]
        lea  ecx,[edx+ecx*4]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_0042AAC2
    loc_0042AAB8:
        mov  ecx,DWORD PTR [ecx+0x4]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        jne loc_0042AAB8
    loc_0042AAC2:
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_0042AAD2
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_0042AAD2:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
        ret  0x4
    }
}
