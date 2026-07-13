// 0040D830: FUN_0040d830
// Original size: 688 bytes, actual code: 141 instructions
extern "C" void FUN_0040cc70(void);
extern "C" void FUN_00450470(void);

extern "C" __declspec(naked) void FUN_0040d830(void) {
    __asm {
        push  ebx
        push  ebp
        push  edi
        xor  ebx,ebx
        lea  edi,[esi+0x103c]
        mov  DWORD PTR [esi+0x1010],ebx
        mov  DWORD PTR [esi+0x1014],ebx
        mov  edx,edi
        mov  DWORD PTR [esi],0x46d0c0
        call FUN_0040cc70
        xor  eax,eax
        mov  ecx,0x537
        rep stosd
        mov  ecx,DWORD PTR [esi+0x1028]
        mov  DWORD PTR [esi+0x8],ebx
        mov  DWORD PTR [esi+0xc],ebx
        mov  DWORD PTR [esi+0x101c],esi
        and  ecx,0xfffffffe
        mov  DWORD PTR [esi+0x1028],ecx
        mov  DWORD PTR [esi+0x1020],ebx
        lea  eax,[esi+0x8]
        mov  DWORD PTR [esi+0x4],eax
        or   ebp,0xffffffff
        mov  DWORD PTR [esi+0x1018],ebp
        mov  DWORD PTR [esi+0x1030],eax
        mov  DWORD PTR [esi+0x1034],ebx
        mov  DWORD PTR [esi+0x1038],ebx
        mov  DWORD PTR [esi+0x2514],esi
        mov  DWORD PTR [esi+0x11bc],ebx
        mov  DWORD PTR [esi+0x1208],ebx
        mov  DWORD PTR [esi+0x1244],ebx
        mov  DWORD PTR [esi+0x1280],ebx
        mov  DWORD PTR [esi+0x12bc],ebx
        mov  DWORD PTR [esi+0x12f8],ebx
        xor  eax,eax
        mov  ecx,0xb
        lea  edi,[esi+0x10c0]
        rep stosd
        mov  ecx,0xb
        lea  edi,[esi+0x1094]
        rep stosd
        mov  ecx,0xb
        lea  edi,[esi+0x1068]
        rep stosd
        mov  eax,0x41c00000
        mov  DWORD PTR [esi+0x10ec],eax
        mov  DWORD PTR [esi+0x10f0],eax
        mov  DWORD PTR [esi+0x10f4],eax
        mov  DWORD PTR [esi+0x10f8],eax
        mov  DWORD PTR [esi+0x248c],ebp
        lea  edx,[esi+0x2408]
        xor  eax,eax
        mov  DWORD PTR [esi+0x116c],esi
        mov  DWORD PTR [esi+0x1170],ebx
        mov  DWORD PTR [esi+0x1174],ebx
        mov  edi,edx
        mov  ecx,0xf
        rep stosd
        mov  eax,0x42000000
        mov  DWORD PTR [edx+0x38],eax
        mov  DWORD PTR [edx+0x34],eax
        mov  eax,DWORD PTR [esi+0x1168]
        test  al,0x1
        mov  edx,0xfff0bdc1
        mov  ecx,0x476f78
        jne loc_0040D978
        or   eax,0x1
        mov  DWORD PTR [esi+0x115c],ebx
        mov  DWORD PTR [esi+0x1158],edx
        mov  DWORD PTR [esi+0x1160],ebx
        mov  DWORD PTR [esi+0x1164],ecx
        mov  DWORD PTR [esi+0x1168],eax
    loc_0040D978:
        mov  DWORD PTR [esi+0x115c],ebx
        mov  DWORD PTR [esi+0x1160],ebx
        mov  DWORD PTR [esi+0x1158],ebp
        mov  eax,DWORD PTR [esi+0x2468]
        test  al,0x1
        jne loc_0040D9B5
        or   eax,0x1
        mov  DWORD PTR [esi+0x245c],ebx
        mov  DWORD PTR [esi+0x2458],edx
        mov  DWORD PTR [esi+0x2460],ebx
        mov  DWORD PTR [esi+0x2464],ecx
        mov  DWORD PTR [esi+0x2468],eax
    loc_0040D9B5:
        mov  DWORD PTR [esi+0x245c],ebx
        mov  DWORD PTR [esi+0x2460],ebx
        mov  DWORD PTR [esi+0x2458],ebp
        mov  eax,DWORD PTR [esi+0x247c]
        test  al,0x1
        jne loc_0040D9F2
        or   eax,0x1
        mov  DWORD PTR [esi+0x2470],ebx
        mov  DWORD PTR [esi+0x246c],edx
        mov  DWORD PTR [esi+0x2474],ebx
        mov  DWORD PTR [esi+0x2478],ecx
        mov  DWORD PTR [esi+0x247c],eax
    loc_0040D9F2:
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR [esi+0x2470],ebx
        mov  DWORD PTR [esi+0x2474],ebx
        mov  DWORD PTR [esi+0x246c],ebp
        mov  eax,DWORD PTR [eax+0x54]
        push  ecx
        mov  DWORD PTR [esi+0x102c],eax
        call FUN_00450470
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx+0x4],eax
        mov  eax,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax],ebx
        mov  DWORD PTR [esi+0x23fc],ebx
        mov  DWORD PTR [esi+0x2400],ebx
        mov  DWORD PTR [esi+0x2404],ebx
        pop  edi
        mov  DWORD PTR [esi+0x2494],ebp
        mov  DWORD PTR [esi+0x2498],ebp
        mov  DWORD PTR [esi+0x24a4],ebp
        mov  DWORD PTR [esi+0x24a8],ebp
        mov  DWORD PTR [esi+0x24b4],ebp
        mov  DWORD PTR [esi+0x24b8],ebp
        mov  DWORD PTR [esi+0x24c4],ebp
        mov  DWORD PTR [esi+0x24c8],ebp
        mov  DWORD PTR [esi+0x24d4],ebp
        mov  DWORD PTR [esi+0x24d8],ebp
        mov  DWORD PTR [esi+0x24e4],ebp
        mov  DWORD PTR [esi+0x24e8],ebp
        mov  DWORD PTR [esi+0x24f4],ebp
        mov  DWORD PTR [esi+0x24f8],ebp
        mov  DWORD PTR [esi+0x2504],ebp
        mov  DWORD PTR [esi+0x2508],ebp
        pop  ebp
        mov  DWORD PTR [esi+0x249c],ebx
        mov  DWORD PTR [esi+0x24ac],ebx
        mov  DWORD PTR [esi+0x24bc],ebx
        mov  DWORD PTR [esi+0x24cc],ebx
        mov  DWORD PTR [esi+0x24dc],ebx
        mov  DWORD PTR [esi+0x24ec],ebx
        mov  DWORD PTR [esi+0x24fc],ebx
        mov  DWORD PTR [esi+0x250c],ebx
        mov  eax,esi
        pop  ebx
        ret  0x4
    }
}
