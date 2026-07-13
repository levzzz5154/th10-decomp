// 00450700: FUN_00450700
// Original size: 7424 bytes, actual code: 2564 instructions
extern "C" void FUN_00450470(void);

extern "C" __declspec(naked) void FUN_00450700(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0x102c]
        push  ecx
        call FUN_00450470
        mov  edx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [edx+0x4],eax
        mov  eax,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax],0x0
        xor  eax,eax
        ret
        jmp  DWORD PTR ds:0x466000
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        int3
        jl loc_004507AB
        inc  esi
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+eax*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004507BB
        inc  esi
        add  BYTE PTR [ecx],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+eax*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004507CB
        inc  esi
        add  BYTE PTR [edx],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+eax*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004507DB
        inc  esi
        add  BYTE PTR [ebx],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+eax*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004507EB
        inc  esi
        add  BYTE PTR [eax+eax*1],al
        add  BYTE PTR [eax],al
        or   al,0x4
        add  BYTE PTR [eax+0x0],al
        jl loc_004507FB
        inc  esi
        add  BYTE PTR ds:0xc000000,al
        add  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045080B
        inc  esi
        add  BYTE PTR [esi],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+eax*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045081B
        inc  esi
        add  BYTE PTR [edi],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+eax*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045082B
        inc  esi
        add  BYTE PTR [eax],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+ecx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045083B
        inc  esi
        add  BYTE PTR [ecx],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+ecx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045084B
        inc  esi
        add  BYTE PTR [edx],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+ecx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045085B
        inc  esi
        add  BYTE PTR [ebx],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+ecx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045086B
        inc  esi
        add  BYTE PTR [eax+eax*1],cl
        add  BYTE PTR [eax],al
        or   al,0xc
        add  BYTE PTR [eax+0x0],al
        jl loc_0045087B
        inc  esi
        add  BYTE PTR ds:0xc000000,cl
        or   eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045088B
        inc  esi
        add  BYTE PTR [esi],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+ecx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045089B
        inc  esi
        add  BYTE PTR [edi],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+ecx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004508AB
        inc  esi
        add  BYTE PTR [eax],dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+edx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004508BB
        inc  esi
        add  BYTE PTR [ecx],dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+edx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004508CB
        inc  esi
        add  BYTE PTR [edx],dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+edx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004508DB
        inc  esi
        add  BYTE PTR [ebx],dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+edx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004508EB
        inc  esi
        add  BYTE PTR [eax+eax*1],dl
        add  BYTE PTR [eax],al
        or   al,0x14
        add  BYTE PTR [eax+0x0],al
        jl loc_004508FB
        inc  esi
        add  BYTE PTR ds:0xc000000,dl
        adc  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045090B
        inc  esi
        add  BYTE PTR [esi],dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+edx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045091B
        inc  esi
        add  BYTE PTR [edi],dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045092B
        inc  esi
        add  BYTE PTR [eax],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+ebx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045093B
        inc  esi
        add  BYTE PTR [ecx],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+ebx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045094B
        inc  esi
        add  BYTE PTR [edx],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+ebx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045095B
        inc  esi
        add  BYTE PTR [ebx],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+ebx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045096B
        inc  esi
        add  BYTE PTR [eax+eax*1],bl
        add  BYTE PTR [eax],al
        or   al,0x1c
        add  BYTE PTR [eax+0x0],al
        jl loc_0045097B
        inc  esi
        add  BYTE PTR ds:0xc000000,bl
        sbb  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045098B
        inc  esi
        add  BYTE PTR [esi],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+ebx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045099B
        inc  esi
        add  BYTE PTR [edi],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+ebx*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004509AB
        inc  esi
        add  BYTE PTR [eax],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+eiz*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004509BB
        inc  esi
        add  BYTE PTR [ecx],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+eiz*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004509CB
        inc  esi
        add  BYTE PTR [edx],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+eiz*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004509DB
        inc  esi
        add  BYTE PTR [ebx],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+eiz*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004509EB
        inc  esi
        add  BYTE PTR [eax+eax*1],ah
        add  BYTE PTR [eax],al
        or   al,0x24
        add  BYTE PTR [eax+0x0],al
        jl loc_004509FB
        inc  esi
        add  BYTE PTR ds:0xc000000,ah
        and  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_00450A0B
        inc  esi
        add  BYTE PTR [esi],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+eiz*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A1B
        inc  esi
        add  BYTE PTR [edi],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+eiz*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A2B
        inc  esi
        add  BYTE PTR [eax],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+ebp*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A3B
        inc  esi
        add  BYTE PTR [ecx],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+ebp*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A4B
        inc  esi
        add  BYTE PTR [edx],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+ebp*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A5B
        inc  esi
        add  BYTE PTR [ebx],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+ebp*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A6B
        inc  esi
        add  BYTE PTR [eax+eax*1],ch
        add  BYTE PTR [eax],al
        or   al,0x2c
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A7B
        inc  esi
        add  BYTE PTR ds:0xc000000,ch
        sub  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_00450A8B
        inc  esi
        add  BYTE PTR [esi],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+ebp*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450A9B
        inc  esi
        add  BYTE PTR [edi],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+ebp*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450AAB
        inc  esi
        add  BYTE PTR [eax],dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+esi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450ABB
        inc  esi
        add  BYTE PTR [ecx],dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+esi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450ACB
        inc  esi
        add  BYTE PTR [edx],dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+esi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450ADB
        inc  esi
        add  BYTE PTR [ebx],dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+esi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450AEB
        inc  esi
        add  BYTE PTR [eax+eax*1],dh
        add  BYTE PTR [eax],al
        or   al,0x34
        add  BYTE PTR [eax+0x0],al
        jl loc_00450AFB
        inc  esi
        add  BYTE PTR ds:0xc000000,dh
        xor  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_00450B0B
        inc  esi
        add  BYTE PTR [esi],dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+esi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B1B
        inc  esi
        add  BYTE PTR [edi],dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+esi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B2B
        inc  esi
        add  BYTE PTR [eax],bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+edi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B3B
        inc  esi
        add  BYTE PTR [ecx],bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+edi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B4B
        inc  esi
        add  BYTE PTR [edx],bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+edi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B5B
        inc  esi
        add  BYTE PTR [ebx],bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+edi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B6B
        inc  esi
        add  BYTE PTR [eax+eax*1],bh
        add  BYTE PTR [eax],al
        or   al,0x3c
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B7B
        inc  esi
        add  BYTE PTR ds:0xc000000,bh
        cmp  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_00450B8B
        inc  esi
        add  BYTE PTR [esi],bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+edi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450B9B
        inc  esi
        add  BYTE PTR [edi],bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*1],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450BAB
        inc  esi
        add  BYTE PTR [eax+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x40
        add  BYTE PTR [eax+0x0],al
        jl loc_00450BBB
        inc  esi
        add  BYTE PTR [ecx+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x41
        add  BYTE PTR [eax+0x0],al
        jl loc_00450BCB
        inc  esi
        add  BYTE PTR [edx+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x42
        add  BYTE PTR [eax+0x0],al
        jl loc_00450BDB
        inc  esi
        add  BYTE PTR [ebx+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x43
        add  BYTE PTR [eax+0x0],al
        jl loc_00450BEB
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],al
        add  BYTE PTR [esp+eax*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450BFB
        inc  esi
        add  BYTE PTR [ebp+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x45
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C0B
        inc  esi
        add  BYTE PTR [esi+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x46
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C1B
        inc  esi
        add  BYTE PTR [edi+0x0],al
        add  BYTE PTR [eax],al
        or   al,0x47
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C2B
        inc  esi
        add  BYTE PTR [eax+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x48
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C3B
        inc  esi
        add  BYTE PTR [ecx+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x49
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C4B
        inc  esi
        add  BYTE PTR [edx+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x4a
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C5B
        inc  esi
        add  BYTE PTR [ebx+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x4b
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C6B
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],cl
        add  BYTE PTR [esp+ecx*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C7B
        inc  esi
        add  BYTE PTR [ebp+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x4d
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C8B
        inc  esi
        add  BYTE PTR [esi+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x4e
        add  BYTE PTR [eax+0x0],al
        jl loc_00450C9B
        inc  esi
        add  BYTE PTR [edi+0x0],cl
        add  BYTE PTR [eax],al
        or   al,0x4f
        add  BYTE PTR [eax+0x0],al
        jl loc_00450CAB
        inc  esi
        add  BYTE PTR [eax+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x50
        add  BYTE PTR [eax+0x0],al
        jl loc_00450CBB
        inc  esi
        add  BYTE PTR [ecx+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x51
        add  BYTE PTR [eax+0x0],al
        jl loc_00450CCB
        inc  esi
        add  BYTE PTR [edx+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x52
        add  BYTE PTR [eax+0x0],al
        jl loc_00450CDB
        inc  esi
        add  BYTE PTR [ebx+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x53
        add  BYTE PTR [eax+0x0],al
        jl loc_00450CEB
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],dl
        add  BYTE PTR [esp+edx*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450CFB
        inc  esi
        add  BYTE PTR [ebp+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x55
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D0B
        inc  esi
        add  BYTE PTR [esi+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x56
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D1B
        inc  esi
        add  BYTE PTR [edi+0x0],dl
        add  BYTE PTR [eax],al
        or   al,0x57
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D2B
        inc  esi
        add  BYTE PTR [eax+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x58
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D3B
        inc  esi
        add  BYTE PTR [ecx+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x59
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D4B
        inc  esi
        add  BYTE PTR [edx+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x5a
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D5B
        inc  esi
        add  BYTE PTR [ebx+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x5b
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D6B
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],bl
        add  BYTE PTR [esp+ebx*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D7B
        inc  esi
        add  BYTE PTR [ebp+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x5d
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D8B
        inc  esi
        add  BYTE PTR [esi+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x5e
        add  BYTE PTR [eax+0x0],al
        jl loc_00450D9B
        inc  esi
        add  BYTE PTR [edi+0x0],bl
        add  BYTE PTR [eax],al
        or   al,0x5f
        add  BYTE PTR [eax+0x0],al
        jl loc_00450DAB
        inc  esi
        add  BYTE PTR [eax+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x60
        add  BYTE PTR [eax+0x0],al
        jl loc_00450DBB
        inc  esi
        add  BYTE PTR [ecx+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x61
        add  BYTE PTR [eax+0x0],al
        jl loc_00450DCB
        inc  esi
        add  BYTE PTR [edx+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x62
        add  BYTE PTR [eax+0x0],al
        jl loc_00450DDB
        inc  esi
        add  BYTE PTR [ebx+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x63
        add  BYTE PTR [eax+0x0],al
        jl loc_00450DEB
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],ah
        add  BYTE PTR [esp+eiz*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450DFB
        inc  esi
        add  BYTE PTR [ebp+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x65
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E0B
        inc  esi
        add  BYTE PTR [esi+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x66
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E1B
        inc  esi
        add  BYTE PTR [edi+0x0],ah
        add  BYTE PTR [eax],al
        or   al,0x67
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E2B
        inc  esi
        add  BYTE PTR [eax+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x68
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E3B
        inc  esi
        add  BYTE PTR [ecx+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x69
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E4B
        inc  esi
        add  BYTE PTR [edx+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x6a
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E5B
        inc  esi
        add  BYTE PTR [ebx+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x6b
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E6B
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],ch
        add  BYTE PTR [esp+ebp*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E7B
        inc  esi
        add  BYTE PTR [ebp+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x6d
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E8B
        inc  esi
        add  BYTE PTR [esi+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x6e
        add  BYTE PTR [eax+0x0],al
        jl loc_00450E9B
        inc  esi
        add  BYTE PTR [edi+0x0],ch
        add  BYTE PTR [eax],al
        or   al,0x6f
        add  BYTE PTR [eax+0x0],al
        jl loc_00450EAB
        inc  esi
        add  BYTE PTR [eax+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x70
        add  BYTE PTR [eax+0x0],al
        jl loc_00450EBB
        inc  esi
        add  BYTE PTR [ecx+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x71
        add  BYTE PTR [eax+0x0],al
        jl loc_00450ECB
        inc  esi
        add  BYTE PTR [edx+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x72
        add  BYTE PTR [eax+0x0],al
        jl loc_00450EDB
        inc  esi
        add  BYTE PTR [ebx+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x73
        add  BYTE PTR [eax+0x0],al
        jl loc_00450EEB
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],dh
        add  BYTE PTR [esp+esi*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450EFB
        inc  esi
        add  BYTE PTR [ebp+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x75
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F0B
        inc  esi
        add  BYTE PTR [esi+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x76
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F1B
        inc  esi
        add  BYTE PTR [edi+0x0],dh
        add  BYTE PTR [eax],al
        or   al,0x77
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F2B
        inc  esi
        add  BYTE PTR [eax+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x78
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F3B
        inc  esi
        add  BYTE PTR [ecx+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x79
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F4B
        inc  esi
        add  BYTE PTR [edx+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x7a
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F5B
        inc  esi
        add  BYTE PTR [ebx+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x7b
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F6B
        inc  esi
        add  BYTE PTR [eax+eax*1+0x0],bh
        add  BYTE PTR [esp+edi*2],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F7B
        inc  esi
        add  BYTE PTR [ebp+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x7d
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F8B
        inc  esi
        add  BYTE PTR [esi+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x7e
        add  BYTE PTR [eax+0x0],al
        jl loc_00450F9B
        inc  esi
        add  BYTE PTR [edi+0x0],bh
        add  BYTE PTR [eax],al
        or   al,0x7f
        add  BYTE PTR [eax+0x0],al
        jl loc_00450FAB
        inc  esi
        add  BYTE PTR [eax+0xc000000],al
        add  BYTE PTR [eax],0x80
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jl loc_00450FBB
        inc  esi
        add  BYTE PTR [ecx+0xc000000],al
        add  DWORD PTR [eax],0x80
        add  BYTE PTR [ecx+edi*2+0x46],bh
        add  BYTE PTR [edx+0xc000000],al
        add  BYTE PTR [eax],0x80
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jl loc_00450FDB
        inc  esi
        add  BYTE PTR [ebx+0xc000000],al
        add  DWORD PTR [eax],0xffffff80
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jl loc_00450FEB
        inc  esi
        add  BYTE PTR [eax+eax*1-0x7bf40000],al
        add  BYTE PTR [eax+0x0],al
        jl loc_00450FFB
        inc  esi
        add  BYTE PTR [ebp+0xc000000],al
        test  DWORD PTR [eax],eax
    loc_00450F8B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045100B
        inc  esi
        add  BYTE PTR [esi+0xc000000],al
        xchg  BYTE PTR [eax],al
    loc_00450F9B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045101B
        inc  esi
        add  BYTE PTR [edi+0xc000000],al
        xchg  DWORD PTR [eax],eax
    loc_00450FAB:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045102B
        inc  esi
        add  BYTE PTR [eax+0xc000000],cl
        mov  BYTE PTR [eax],al
    loc_00450FBB:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045103B
        inc  esi
        add  BYTE PTR [ecx+0xc000000],cl
        mov  DWORD PTR [eax],eax
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045104B
        inc  esi
        add  BYTE PTR [edx+0xc000000],cl
        mov  al,BYTE PTR [eax]
    loc_00450FDB:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045105B
        inc  esi
        add  BYTE PTR [ebx+0xc000000],cl
        mov  eax,DWORD PTR [eax]
    loc_00450FEB:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045106B
        inc  esi
        add  BYTE PTR [eax+eax*1-0x73f40000],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045107B
        inc  esi
        add  BYTE PTR [ebp+0xc000000],cl
        lea  eax,[eax]
    loc_0045100B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045108B
        inc  esi
        add  BYTE PTR [esi+0xc000000],cl
        mov  es,WORD PTR [eax]
    loc_0045101B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045109B
        inc  esi
        add  BYTE PTR [edi+0xc000000],cl
        pop  DWORD PTR [eax]
    loc_0045102B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_004510AB
        inc  esi
        add  BYTE PTR [eax+0xc000000],dl
        nop
        add  BYTE PTR [eax+0x0],al
        jl loc_004510BB
        inc  esi
        add  BYTE PTR [ecx+0xc000000],dl
        xchg  ecx,eax
        add  BYTE PTR [eax+0x0],al
        jl loc_004510CB
        inc  esi
        add  BYTE PTR [edx+0xc000000],dl
        xchg  edx,eax
        add  BYTE PTR [eax+0x0],al
        jl loc_004510DB
        inc  esi
        add  BYTE PTR [ebx+0xc000000],dl
        xchg  ebx,eax
        add  BYTE PTR [eax+0x0],al
        jl loc_004510EB
        inc  esi
        add  BYTE PTR [eax+eax*1-0x6bf40000],dl
        add  BYTE PTR [eax+0x0],al
        jl loc_004510FB
        inc  esi
        add  BYTE PTR [ebp+0xc000000],dl
        xchg  ebp,eax
        add  BYTE PTR [eax+0x0],al
        jl loc_0045110B
        inc  esi
        add  BYTE PTR [esi+0xc000000],dl
        xchg  esi,eax
        add  BYTE PTR [eax+0x0],al
        jl loc_0045111B
        inc  esi
        add  BYTE PTR [edi+0xc000000],dl
        xchg  edi,eax
        add  BYTE PTR [eax+0x0],al
        jl loc_0045112B
        inc  esi
        add  BYTE PTR [eax+0xc000000],bl
        cwde
        add  BYTE PTR [eax+0x0],al
        jl loc_0045113B
        inc  esi
        add  BYTE PTR [ecx+0xc000000],bl
        cdq
        add  BYTE PTR [eax+0x0],al
        jl loc_0045114B
        inc  esi
        add  BYTE PTR [edx+0xc000000],bl
        call FUN_00000000:0x8000
        jl loc_0045115B
        inc  esi
        add  BYTE PTR [ebx+0xc000000],bl
        fwait
        add  BYTE PTR [eax+0x0],al
        jl loc_0045116B
        inc  esi
        add  BYTE PTR [eax+eax*1-0x63f40000],bl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045117B
        inc  esi
        add  BYTE PTR [ebp+0xc000000],bl
        popf
        add  BYTE PTR [eax+0x0],al
        jl loc_0045118B
        inc  esi
        add  BYTE PTR [esi+0xc000000],bl
        sahf
        add  BYTE PTR [eax+0x0],al
        jl loc_0045119B
        inc  esi
        add  BYTE PTR [edi+0xc000000],bl
        lahf
        add  BYTE PTR [eax+0x0],al
        jl loc_004511AB
        inc  esi
        add  BYTE PTR [eax+0xc000000],ah
        mov  al,ds:0x8000
        add  BYTE PTR [eax],al
        jl loc_004511BB
        inc  esi
        add  BYTE PTR [ecx+0xc000000],ah
        mov  eax,ds:0x8000
        add  BYTE PTR [eax],al
        jl loc_004511CB
        inc  esi
        add  BYTE PTR [edx+0xc000000],ah
        mov  ds:0x8000,al
        add  BYTE PTR [eax],al
        jl loc_004511DB
        inc  esi
        add  BYTE PTR [ebx+0xc000000],ah
        mov  ds:0x8000,eax
        add  BYTE PTR [eax],al
        jl loc_004511EB
        inc  esi
        add  BYTE PTR [eax+eax*1-0x5bf40000],ah
        add  BYTE PTR [eax+0x0],al
        jl loc_004511FB
        inc  esi
        add  BYTE PTR [ebp+0xc000000],ah
        movs  DWORD PTR es:[edi],DWORD PTR ds:[esi]
        add  BYTE PTR [eax+0x0],al
        jl loc_0045120B
        inc  esi
        add  BYTE PTR [esi+0xc000000],ah
        cmps  BYTE PTR ds:[esi],BYTE PTR es:[edi]
        add  BYTE PTR [eax+0x0],al
        jl loc_0045121B
        inc  esi
        add  BYTE PTR [edi+0xc000000],ah
        cmps  DWORD PTR ds:[esi],DWORD PTR es:[edi]
        add  BYTE PTR [eax+0x0],al
        jl loc_0045122B
        inc  esi
        add  BYTE PTR [eax+0xc000000],ch
        test  al,0x0
    loc_004511BB:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045123B
        inc  esi
        add  BYTE PTR [ecx+0xc000000],ch
        test  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045124B
        inc  esi
        add  BYTE PTR [edx+0xc000000],ch
        stos  BYTE PTR es:[edi],al
        add  BYTE PTR [eax+0x0],al
        jl loc_0045125B
        inc  esi
        add  BYTE PTR [ebx+0xc000000],ch
        stos  DWORD PTR es:[edi],eax
        add  BYTE PTR [eax+0x0],al
        jl loc_0045126B
        inc  esi
        add  BYTE PTR [eax+eax*1-0x53f40000],ch
        add  BYTE PTR [eax+0x0],al
        jl loc_0045127B
        inc  esi
        add  BYTE PTR [ebp+0xc000000],ch
        lods  eax,DWORD PTR ds:[esi]
        add  BYTE PTR [eax+0x0],al
        jl loc_0045128B
        inc  esi
        add  BYTE PTR [esi+0xc000000],ch
        scas  al,BYTE PTR es:[edi]
        add  BYTE PTR [eax+0x0],al
        jl loc_0045129B
        inc  esi
        add  BYTE PTR [edi+0xc000000],ch
        scas  eax,DWORD PTR es:[edi]
        add  BYTE PTR [eax+0x0],al
        jl loc_004512AB
        inc  esi
        add  BYTE PTR [eax+0xc000000],dh
        mov  al,0x0
    loc_0045123B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_004512BB
        inc  esi
        add  BYTE PTR [ecx+0xc000000],dh
        mov  cl,0x0
    loc_0045124B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_004512CB
        inc  esi
        add  BYTE PTR [edx+0xc000000],dh
        mov  dl,0x0
    loc_0045125B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_004512DB
        inc  esi
        add  BYTE PTR [ebx+0xc000000],dh
        mov  bl,0x0
    loc_0045126B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_004512EB
        inc  esi
        add  BYTE PTR [eax+eax*1-0x4bf40000],dh
        add  BYTE PTR [eax+0x0],al
        jl loc_004512FB
        inc  esi
        add  BYTE PTR [ebp+0xc000000],dh
        mov  ch,0x0
    loc_0045128B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045130B
        inc  esi
        add  BYTE PTR [esi+0xc000000],dh
        mov  dh,0x0
    loc_0045129B:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045131B
        inc  esi
        add  BYTE PTR [edi+0xc000000],dh
        mov  bh,0x0
    loc_004512AB:
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        jl loc_0045132B
        inc  esi
        add  BYTE PTR [eax+0xc000000],bh
        mov  eax,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045133B
        inc  esi
        add  BYTE PTR [ecx+0xc000000],bh
        mov  ecx,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045134B
        inc  esi
        add  BYTE PTR [edx+0xc000000],bh
        mov  edx,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045135B
        inc  esi
        add  BYTE PTR [ebx+0xc000000],bh
        mov  ebx,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045136B
        inc  esi
        add  BYTE PTR [eax+eax*1-0x43f40000],bh
        add  BYTE PTR [eax+0x0],al
        jl loc_0045137B
        inc  esi
        add  BYTE PTR [ebp+0xc000000],bh
        mov  ebp,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045138B
        inc  esi
        add  BYTE PTR [esi+0xc000000],bh
        mov  esi,0x8000
        add  BYTE PTR [eax],al
        jl loc_0045139B
        inc  esi
        add  BYTE PTR [edi+0xc000000],bh
        mov  edi,0x8000
        add  BYTE PTR [eax],al
        jl loc_004513AB
        inc  esi
        add  al,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004513BB
        inc  esi
        add  cl,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004513CB
        inc  esi
        add  dl,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004513DB
        inc  esi
        add  bl,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004513EB
        inc  esi
        add  ah,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004513FB
        inc  esi
        add  ch,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045140B
        inc  esi
        add  dh,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045141B
        inc  esi
        add  bh,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+eax*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045142B
        inc  esi
        add  al,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045143B
        inc  esi
        add  cl,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045144B
        inc  esi
        add  dl,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045145B
        inc  esi
        add  bl,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045146B
        inc  esi
        add  ah,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045147B
        inc  esi
        add  ch,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045148B
        inc  esi
        add  dh,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045149B
        inc  esi
        add  bh,cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+ecx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004514AB
        inc  esi
        add  al,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004514BB
        inc  esi
        add  cl,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004514CB
        inc  esi
        add  dl,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004514DB
        inc  esi
        add  bl,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004514EB
        inc  esi
        add  ah,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004514FB
        inc  esi
        add  ch,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045150B
        inc  esi
        add  dh,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045151B
        inc  esi
        add  bh,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045152B
        inc  esi
        add  al,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045153B
        inc  esi
        add  cl,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045154B
        inc  esi
        add  dl,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045155B
        inc  esi
        add  bl,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045156B
        inc  esi
        add  ah,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045157B
        inc  esi
        add  ch,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045158B
        inc  esi
        add  dh,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045159B
        inc  esi
        add  bh,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+ebx*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004515AB
        inc  esi
        add  al,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004515BB
        inc  esi
        add  cl,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004515CB
        inc  esi
        add  dl,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004515DB
        inc  esi
        add  bl,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004515EB
        inc  esi
        add  ah,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004515FB
        inc  esi
        add  ch,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [eiz*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045160B
        inc  esi
        add  dh,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045161B
        inc  esi
        add  bh,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+eiz*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045162B
        inc  esi
        add  al,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045163B
        inc  esi
        add  cl,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045164B
        inc  esi
        add  dl,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045165B
        inc  esi
        add  bl,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045166B
        inc  esi
        add  ah,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045167B
        inc  esi
        add  ch,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebp*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045168B
        inc  esi
        add  dh,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045169B
        inc  esi
        add  bh,ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+ebp*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004516AB
        inc  esi
        add  al,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004516BB
        inc  esi
        add  cl,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004516CB
        inc  esi
        add  dl,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004516DB
        inc  esi
        add  bl,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004516EB
        inc  esi
        add  ah,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_004516FB
        inc  esi
        add  ch,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045170B
        inc  esi
        add  dh,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045171B
        inc  esi
        add  bh,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+esi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045172B
        inc  esi
        add  al,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045173B
        inc  esi
        add  cl,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ecx+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045174B
        inc  esi
        add  dl,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edx+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045175B
        inc  esi
        add  bl,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045176B
        inc  esi
        add  ah,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esp+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045177B
        inc  esi
        add  ch,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi*8+0x8000],cl
        add  BYTE PTR [eax],al
        jl loc_0045178B
        inc  esi
        add  dh,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [esi+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        jl loc_0045179B
        inc  esi
        add  bh,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        add  BYTE PTR [eax+0x0],al
        cld
        jns loc_00451779
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x100]
        in   al,dx
        jns loc_00451789
        add  BYTE PTR [eax+eax*1],al
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x100]
        fdivr QWORD PTR [ecx+0x46]
        add  BYTE PTR [eax],cl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x100]
        int3
        jns loc_004517A9
        add  BYTE PTR [eax+eax*1],cl
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x100]
        mov  esp,0x10004679
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00451779:
        (bad]
        inc  DWORD PTR [eax+0x100]
        lods  al,BYTE PTR ds:[esi]
        jns loc_004517C9
        add  BYTE PTR [eax+eax*1],dl
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x100]
        pushf
        jns loc_004517D9
        add  BYTE PTR [eax],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x100]
        pushf
        jns loc_004517E9
        add  BYTE PTR [eax+eax*1],bl
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x100]
        ins  BYTE PTR es:[edi],dx
        jns loc_004517F9
        add  BYTE PTR [eax],ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],dl
        (bad]
        inc  DWORD PTR [eax+0x0]
        ins  BYTE PTR es:[edi],dx
        jns loc_00451809
        add  BYTE PTR [eax+eax*1],ah
        add  BYTE PTR [eax],al
        adc  bh,bh
        inc  DWORD PTR [eax+0x0]
        ins  BYTE PTR es:[edi],dx
        jns loc_00451819
        add  BYTE PTR [eax],ch
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],dl
    loc_004517D9:
        (bad]
        inc  DWORD PTR [eax+0x0]
        ins  BYTE PTR es:[edi],dx
        jns loc_00451829
        add  BYTE PTR [eax+eax*1],ch
        add  BYTE PTR [eax],al
        adc  bh,bh
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xor  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xor  DWORD PTR [eax],eax
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xor  al,BYTE PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xor  eax,DWORD PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xor  al,0x0
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xor  eax,0xc000000
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR ss:[eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        aaa
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmp  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmp  DWORD PTR [eax],eax
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmp  al,BYTE PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmp  eax,DWORD PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmp  al,0x0
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmp  eax,0xc000000
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR ds:[eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        aas
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  ecx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  edx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  ebx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  esp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  ebp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  esi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        inc  edi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  ecx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  edx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  ebx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  esp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  ebp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  esi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        dec  edi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  ecx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  edx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  ebx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  esp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  ebp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  esi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  edi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  ecx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  edx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  ebx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  esp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  ebp
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  esi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  edi
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pusha
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        popa
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        bound eax,QWORD PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        arpl  WORD PTR [eax],eax
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR fs:[eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR gs:[eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [bx+si],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  0xc000000
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        imul  eax,DWORD PTR [eax],0xff0c0000
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        push  0x0
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        imul  eax,DWORD PTR [eax],0x0
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        ins  BYTE PTR es:[edi],dx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        ins  DWORD PTR es:[edi],dx
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        outs  dx,BYTE PTR ds:[esi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        outs  dx,DWORD PTR ds:[esi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jo loc_00451BF6
    loc_00451BF6:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jno loc_00451C06
    loc_00451C06:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jb loc_00451C16
    loc_00451C16:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jae loc_00451C26
    loc_00451C26:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        je loc_00451C36
    loc_00451C36:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jne loc_00451C46
    loc_00451C46:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jbe loc_00451C56
    loc_00451C56:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        ja loc_00451C66
    loc_00451C66:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        js loc_00451C76
    loc_00451C76:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jns loc_00451C86
    loc_00451C86:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jp loc_00451C96
    loc_00451C96:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jnp loc_00451CA6
    loc_00451CA6:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jl loc_00451CB6
    loc_00451CB6:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jge loc_00451CC6
    loc_00451CC6:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jle loc_00451CD6
    loc_00451CD6:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        jg loc_00451CE6
    loc_00451CE6:
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  DWORD PTR [eax],0xff0c0000
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  DWORD PTR [eax],0x0
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        test  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        test  DWORD PTR [eax],eax
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  DWORD PTR [eax],eax
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  DWORD PTR [eax],eax
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  al,BYTE PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  eax,DWORD PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  WORD PTR [eax],es
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        lea  eax,[eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  es,WORD PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pop  DWORD PTR [eax]
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        nop
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  ecx,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  edx,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  ebx,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  esp,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  ebp,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  esi,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        xchg  edi,eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cwde
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cdq
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        call FUN_0000FFFF:0xc000000
        add  BYTE PTR [eax],0x0
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        fwait
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        pushf
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        popf
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        sahf
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        lahf
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  al,ds:0xc000000
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  eax,ds:0xc000000
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  ds:0xc000000,al
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        mov  ds:0xc000000,eax
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        movs  BYTE PTR es:[edi],BYTE PTR ds:[esi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        movs  DWORD PTR es:[edi],DWORD PTR ds:[esi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmps  BYTE PTR ds:[esi],BYTE PTR es:[edi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        cmps  DWORD PTR ds:[esi],DWORD PTR es:[edi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        test  al,0x0
        add  BYTE PTR [eax],al
        or   al,0xff
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        test  eax,0xc000000
        (bad]
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        stos  BYTE PTR es:[edi],al
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        stos  DWORD PTR es:[edi],eax
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        lods  al,BYTE PTR ds:[esi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        lods  eax,DWORD PTR ds:[esi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        scas  al,BYTE PTR es:[edi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        add  BYTE PTR [eax],al
        add  BYTE PTR [eax],al
        scas  eax,DWORD PTR es:[edi]
        add  BYTE PTR [eax],al
        add  BYTE PTR [edi+edi*8],cl
        inc  DWORD PTR [eax+0x0]
        cld
        jns loc_00452039
        add  BYTE PTR [eax+0x3000000],dh
        (bad]
        inc  DWORD PTR [eax+0x200]
        in   al,dx
        jns loc_00452049
        add  BYTE PTR [eax+eax*1-0xfd0000],dh
        inc  DWORD PTR [eax+0x200]
        fdivr QWORD PTR [ecx+0x46]
        add  BYTE PTR [eax+0x3000000],bh
        (bad]
        inc  DWORD PTR [eax+0x200]
        int3
        jns loc_00452069
        add  BYTE PTR [eax+eax*1-0xfd0000],bh
        inc  DWORD PTR [eax+0x200]
        mov  esp,0xc0004679
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452039:
        (bad]
        inc  DWORD PTR [eax+0x200]
        lods  al,BYTE PTR ds:[esi]
        jns loc_00452089
        add  ah,al
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452049:
        (bad]
        inc  DWORD PTR [eax+0x200]
        pushf
        jns loc_00452099
        add  BYTE PTR [eax],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x200]
        pushf
        jns loc_004520A9
        add  BYTE PTR [eax+eax*1],bl
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x200]
        cld
        jns loc_004520B9
        add  al,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x300]
        in   al,dx
        jns loc_004520C9
        add  ah,dl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452089:
        (bad]
        inc  DWORD PTR [eax+0x300]
        fdivr QWORD PTR [ecx+0x46]
        add  al,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452099:
        (bad]
        inc  DWORD PTR [eax+0x300]
        int3
        jns loc_004520E9
        add  ah,bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_004520A9:
        (bad]
        inc  DWORD PTR [eax+0x300]
        mov  esp,0xe0004679
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_004520B9:
        (bad]
        inc  DWORD PTR [eax+0x300]
        lods  al,BYTE PTR ds:[esi]
        jns loc_00452109
        add  ah,ah
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_004520C9:
        (bad]
        inc  DWORD PTR [eax+0x300]
        pushf
        jns loc_00452119
        add  BYTE PTR [eax],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x300]
        pushf
        jns loc_00452129
        add  BYTE PTR [eax+eax*1],bl
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x300]
        cld
        jns loc_00452139
        add  al,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x400]
        in   al,dx
        jns loc_00452149
        add  ah,dh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452109:
        (bad]
        inc  DWORD PTR [eax+0x400]
        fdivr QWORD PTR [ecx+0x46]
        add  al,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452119:
        (bad]
        inc  DWORD PTR [eax+0x400]
        int3
        jns loc_00452169
        add  ah,bh
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
    loc_00452129:
        (bad]
        inc  DWORD PTR [eax+0x400]
        mov  esp,0x4679
        add  DWORD PTR [eax],eax
        add  BYTE PTR [ebx],al
    loc_00452139:
        (bad]
        inc  DWORD PTR [eax+0x400]
        lods  al,BYTE PTR ds:[esi]
        jns loc_00452189
        add  BYTE PTR [ecx+eax*1],al
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x400]
        pushf
        jns loc_00452199
        add  BYTE PTR [eax],bl
        add  BYTE PTR [eax],al
        add  BYTE PTR [ebx],al
        (bad]
        inc  DWORD PTR [eax+0x400]
        pushf
        jns loc_004521A9
        add  BYTE PTR [eax+eax*1],bl
        add  BYTE PTR [eax],al
        add  edi,edi
        inc  DWORD PTR [eax+0x400]
        jmp  DWORD PTR ds:0x466008
        jmp  DWORD PTR ds:0x4662b4
        jmp  DWORD PTR ds:0x4662bc
        jmp  DWORD PTR ds:0x4662f8
        jmp  DWORD PTR ds:0x4662f4
        jmp  DWORD PTR ds:0x4662f0
        jmp  DWORD PTR ds:0x4662ec
        jmp  DWORD PTR ds:0x4662e8
        jmp  DWORD PTR ds:0x4662e4
        jmp  DWORD PTR ds:0x4662e0
        jmp  DWORD PTR ds:0x4662dc
        jmp  DWORD PTR ds:0x4662d8
        jmp  DWORD PTR ds:0x4662d4
        jmp  DWORD PTR ds:0x4662d0
        jmp  DWORD PTR ds:0x4662cc
        jmp  DWORD PTR ds:0x4662c8
        jmp  DWORD PTR ds:0x4662c4
        jmp  DWORD PTR ds:0x4662c0
        jmp  DWORD PTR ds:0x466270
        jmp  DWORD PTR ds:0x466274
        jmp  DWORD PTR ds:0x466278
        jmp  DWORD PTR ds:0x4662ac
        jmp  DWORD PTR ds:0x4662a8
        jmp  DWORD PTR ds:0x4662a4
        jmp  DWORD PTR ds:0x4662a0
        jmp  DWORD PTR ds:0x46629c
        jmp  DWORD PTR ds:0x466298
        jmp  DWORD PTR ds:0x466294
        jmp  DWORD PTR ds:0x466290
        jmp  DWORD PTR ds:0x46628c
        jmp  DWORD PTR ds:0x466288
        jmp  DWORD PTR ds:0x466284
        jmp  DWORD PTR ds:0x466280
        jmp  DWORD PTR ds:0x46627c
        jmp  DWORD PTR ds:0x4660a0
        jmp  DWORD PTR ds:0x4660a4
        jmp  DWORD PTR ds:0x4660a8
        jmp  DWORD PTR ds:0x4660ac
        jmp  DWORD PTR ds:0x4660b0
        jmp  DWORD PTR ds:0x4660b4
        jmp  DWORD PTR ds:0x4660b8
        jmp  DWORD PTR ds:0x4660bc
        jmp  DWORD PTR ds:0x4660c0
        jmp  DWORD PTR ds:0x4660c4
        jmp  DWORD PTR ds:0x4660c8
        jmp  DWORD PTR ds:0x4660cc
        jmp  DWORD PTR ds:0x4660d0
        jmp  DWORD PTR ds:0x4660d4
        jmp  DWORD PTR ds:0x4660d8
        jmp  DWORD PTR ds:0x4660dc
        jmp  DWORD PTR ds:0x4660e0
        jmp  DWORD PTR ds:0x4660e4
        jmp  DWORD PTR ds:0x4660e8
        jmp  DWORD PTR ds:0x4660ec
        jmp  DWORD PTR ds:0x4661dc
        jmp  DWORD PTR ds:0x4660f4
        jmp  DWORD PTR ds:0x4660f8
        jmp  DWORD PTR ds:0x4660fc
        jmp  DWORD PTR ds:0x466100
        jmp  DWORD PTR ds:0x466104
        jmp  DWORD PTR ds:0x466108
        jmp  DWORD PTR ds:0x46610c
        jmp  DWORD PTR ds:0x466110
        jmp  DWORD PTR ds:0x466114
        jmp  DWORD PTR ds:0x466118
        jmp  DWORD PTR ds:0x46611c
        jmp  DWORD PTR ds:0x466120
        jmp  DWORD PTR ds:0x466124
        jmp  DWORD PTR ds:0x466128
        jmp  DWORD PTR ds:0x46612c
        jmp  DWORD PTR ds:0x466130
        jmp  DWORD PTR ds:0x466268
        jmp  DWORD PTR ds:0x4661f4
        jmp  DWORD PTR ds:0x4661f8
        jmp  DWORD PTR ds:0x4661fc
        jmp  DWORD PTR ds:0x466264
        jmp  DWORD PTR ds:0x466260
        jmp  DWORD PTR ds:0x46625c
        jmp  DWORD PTR ds:0x466258
        jmp  DWORD PTR ds:0x466254
        jmp  DWORD PTR ds:0x466250
        jmp  DWORD PTR ds:0x46624c
        jmp  DWORD PTR ds:0x466248
        jmp  DWORD PTR ds:0x466244
        jmp  DWORD PTR ds:0x466240
        jmp  DWORD PTR ds:0x46623c
        jmp  DWORD PTR ds:0x466238
        jmp  DWORD PTR ds:0x466234
        jmp  DWORD PTR ds:0x466230
        jmp  DWORD PTR ds:0x46622c
        jmp  DWORD PTR ds:0x466228
        jmp  DWORD PTR ds:0x4661f0
        jmp  DWORD PTR ds:0x466224
        jmp  DWORD PTR ds:0x466220
        jmp  DWORD PTR ds:0x46621c
        jmp  DWORD PTR ds:0x466218
        jmp  DWORD PTR ds:0x466214
        jmp  DWORD PTR ds:0x466210
        jmp  DWORD PTR ds:0x46620c
        jmp  DWORD PTR ds:0x466208
        jmp  DWORD PTR ds:0x466204
        jmp  DWORD PTR ds:0x466200
        jmp  DWORD PTR ds:0x466034
        jmp  DWORD PTR ds:0x466030
        jmp  DWORD PTR ds:0x46602c
        jmp  DWORD PTR ds:0x466028
        jmp  DWORD PTR ds:0x466024
        jmp  DWORD PTR ds:0x466020
        jmp  DWORD PTR ds:0x46601c
        _emit 0xff
        _emit 0x25
    }
}
