// 004462F0: FUN_004462f0
// Original size: 704 bytes, actual code: 113 instructions

extern "C" __declspec(naked) void FUN_004462f0(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        push  esi
        push  edi
        xor  ebp,ebp
        mov  DWORD PTR [eax+0x3ada80],ebp
        mov  DWORD PTR [eax+0x3adabc],ebp
        mov  DWORD PTR [eax+0x3adaa8],ebp
        mov  DWORD PTR [eax+0x3ada94],ebp
        mov  DWORD PTR [eax+0x3adaac],ebp
        mov  DWORD PTR [eax+0x3ada84],ebp
        mov  DWORD PTR [eax+0x3ada9c],ebp
        mov  DWORD PTR [eax+0x3ada88],ebp
        mov  ecx,0x43000000
        mov  DWORD PTR [eax+0x3adab4],ecx
        mov  DWORD PTR [eax+0x3ada8c],ecx
        mov  DWORD PTR [eax+0x3adab8],ecx
        mov  DWORD PTR [eax+0x3adaa4],ecx
        mov  ecx,0x3f800000
        mov  DWORD PTR [eax+0x3adac4],ecx
        mov  DWORD PTR [eax+0x3adab0],ecx
        mov  DWORD PTR [eax+0x3adac0],ecx
        mov  DWORD PTR [eax+0x3ada98],ecx
        mov  edx,0xc3000000
        mov  DWORD PTR [eax+0x3adaa0],edx
        mov  DWORD PTR [eax+0x3ada78],edx
        mov  DWORD PTR [eax+0x3ada90],edx
        mov  DWORD PTR [eax+0x3ada7c],edx
        lea  esi,[eax+0x3ada78]
        mov  ecx,esi
        mov  edx,DWORD PTR [ecx]
        mov  DWORD PTR ds:0x497930,edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR ds:0x497934,edx
        mov  ecx,DWORD PTR [ecx+0x8]
        mov  DWORD PTR ds:0x497938,ecx
        mov  edx,DWORD PTR [eax+0x3ada8c]
        mov  DWORD PTR ds:0x497948,edx
        mov  ecx,DWORD PTR [eax+0x3ada90]
        mov  DWORD PTR ds:0x49794c,ecx
        mov  edx,DWORD PTR [eax+0x3ada94]
        mov  DWORD PTR ds:0x497950,edx
        mov  ecx,DWORD PTR [eax+0x3adaa0]
        mov  DWORD PTR ds:0x497960,ecx
        mov  edx,DWORD PTR [eax+0x3adaa4]
        mov  DWORD PTR ds:0x497964,edx
        mov  ecx,DWORD PTR [eax+0x3adaa8]
        mov  DWORD PTR ds:0x497968,ecx
        mov  edx,DWORD PTR [eax+0x3adab4]
        mov  DWORD PTR ds:0x497978,edx
        mov  ecx,DWORD PTR [eax+0x3adab8]
        mov  DWORD PTR ds:0x49797c,ecx
        mov  edx,DWORD PTR [eax+0x3adabc]
        mov  DWORD PTR ds:0x497980,edx
        mov  ecx,DWORD PTR [eax+0x3ada84]
        mov  DWORD PTR ds:0x497940,ecx
        mov  edx,DWORD PTR [eax+0x3ada88]
        mov  DWORD PTR ds:0x497944,edx
        mov  ecx,DWORD PTR [eax+0x3ada98]
        mov  DWORD PTR ds:0x497958,ecx
        mov  edx,DWORD PTR [eax+0x3ada9c]
        mov  DWORD PTR ds:0x49795c,edx
        mov  ecx,DWORD PTR [eax+0x3adaac]
        push  ebp
        mov  DWORD PTR ds:0x497970,ecx
        mov  edx,DWORD PTR [eax+0x3adab0]
        lea  ebx,[eax+0x3ada74]
        push  ebx
        push  0x1
        mov  DWORD PTR ds:0x497974,edx
        mov  ecx,DWORD PTR [eax+0x3adac0]
        push  0x102
        mov  DWORD PTR ds:0x497988,ecx
        mov  edx,DWORD PTR [eax+0x3adac4]
        mov  ecx,DWORD PTR ds:0x491c30
        push  ebp
        push  0x50
        mov  DWORD PTR ds:0x49798c,edx
        mov  eax,DWORD PTR [ecx]
        push  ecx
        call  DWORD PTR [eax+0x68]
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax]
        push  ebp
        lea  edx,[esp+0x14]
        push  edx
        push  ebp
        push  ebp
        push  eax
        call  DWORD PTR [ecx+0x2c]
        mov  edi,DWORD PTR [esp+0x10]
        mov  ecx,0x14
        rep movsd
        mov  eax,DWORD PTR [ebx]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x30]
        mov  ecx,DWORD PTR [ebx]
        mov  eax,ds:0x491c30
        mov  edx,DWORD PTR [eax]
        push  0x14
        push  ebp
        push  ecx
        push  ebp
        push  eax
        call  DWORD PTR [edx+0x190]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        pop  ecx
        ret
    }
}
