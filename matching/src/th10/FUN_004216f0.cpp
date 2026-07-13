// 004216F0: FUN_004216f0
// Original size: 480 bytes, actual code: 83 instructions

extern "C" __declspec(naked) void FUN_004216f0(void) {
    __asm {
        sub  esp,0xc
        mov  DWORD PTR [esp],0x0
        mov  eax,DWORD PTR [esp]
        mov  ds:0x491e94,eax
        mov  DWORD PTR [esp+0x4],0x0
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esp+0x8],0x447a0000
        mov  edx,DWORD PTR [esp+0x8]
        mov  DWORD PTR ds:0x491e98,ecx
        mov  DWORD PTR ds:0x491e9c,edx
        mov  DWORD PTR [esp],0x0
        mov  eax,DWORD PTR [esp]
        mov  DWORD PTR [esp+0x4],0x0
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esp+0x8],0x0
        mov  edx,DWORD PTR [esp+0x8]
        mov  ds:0x491ea0,eax
        mov  DWORD PTR [esp],0x0
        mov  eax,DWORD PTR [esp]
        mov  DWORD PTR ds:0x491ea4,ecx
        mov  DWORD PTR ds:0x491ea8,edx
        mov  DWORD PTR [esp+0x4],0x3f800000
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esp+0x8],0x0
        mov  edx,DWORD PTR [esp+0x8]
        mov  ds:0x491eac,eax
        xor  eax,eax
        mov  DWORD PTR ds:0x491eb0,ecx
        mov  ecx,eax
        mov  DWORD PTR ds:0x491eb4,edx
        mov  edx,eax
        mov  DWORD PTR [esp+0x4],eax
        mov  DWORD PTR [esp+0x4],eax
        mov  DWORD PTR [esp+0x8],eax
        mov  DWORD PTR ds:0x491ed0,ecx
        mov  DWORD PTR ds:0x491ed4,edx
        mov  DWORD PTR ds:0x491ed8,ecx
        mov  DWORD PTR [esp+0x8],0x447a0000
        mov  DWORD PTR ds:0x491d7c,edx
        mov  edx,DWORD PTR [esp+0x8]
        mov  DWORD PTR ds:0x491d80,ecx
        mov  DWORD PTR [esp+0x4],eax
        mov  DWORD PTR ds:0x491d88,ecx
        mov  DWORD PTR ds:0x491d90,ecx
        mov  DWORD PTR [esp+0x4],0x3f800000
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR ds:0x491d84,edx
        mov  edx,eax
        mov  DWORD PTR ds:0x491d98,ecx
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR [esp+0x8],eax
        mov  ecx,eax
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR [esp+0x8],eax
        mov  DWORD PTR ds:0x491edc,0x3f060a92
        mov  ds:0x491f60,eax
        mov  ds:0x491f64,eax
        mov  DWORD PTR ds:0x491f68,0x280
        mov  DWORD PTR ds:0x491f6c,0x1e0
        mov  ds:0x491f70,eax
        mov  DWORD PTR ds:0x491f74,0x3f800000
        mov  DWORD PTR ds:0x491f78,0x1
        mov  DWORD PTR ds:0x491d8c,edx
        mov  DWORD PTR ds:0x491d94,edx
        mov  DWORD PTR ds:0x491d9c,edx
        mov  DWORD PTR ds:0x491dc4,0x3f060a92
        mov  DWORD PTR ds:0x491e48,0x20
        mov  DWORD PTR ds:0x491e4c,0x10
        mov  DWORD PTR ds:0x491e50,0x180
        mov  DWORD PTR ds:0x491e54,0x1c0
        mov  ds:0x491e58,eax
        mov  DWORD PTR ds:0x491e5c,0x3f800000
        mov  ds:0x491e60,eax
        mov  DWORD PTR [esp],eax
        mov  DWORD PTR [esp+0x4],eax
        mov  DWORD PTR [esp+0x8],eax
        mov  ds:0x491db8,eax
        mov  DWORD PTR ds:0x491dbc,ecx
        mov  DWORD PTR ds:0x491dc0,edx
        add  esp,0xc
        ret
    }
}
