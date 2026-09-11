#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421FA0..0x00421FBC: FUN_00421fa0
// Naked body preserves the retail register/stack ABI.

// 0x00421FA0..0x00421FBC: FUN_00421fa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421fa0_00421fa0() {
    __asm {
    L_00421fa0:
        mov eax,dword ptr [data_00474c74]
    L_00421fa5:
        mov edx,dword ptr [data_00474c44]
    L_00421fab:
        push ebx
    L_00421fac:
        push esi
    L_00421fad:
        mov ecx,eax
    L_00421faf:
        xor esi,esi
    L_00421fb1:
        imul ecx,0F0h
    L_00421fb7:
        lea ecx,[ecx+edi+10h]
    L_00421fbb:
        TH10_REL8(0xeb, 0x00421fbb, VA_asm_FUN_00421fa0_part_00421fc0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00421fc0:
        cmp dword ptr [ecx],edx
    L_00421fc2:
        jle short L_00421fd3
    L_00421fc4:
        inc esi
    L_00421fc5:
        add ecx,18h
    L_00421fc8:
        cmp esi,0Ah
    L_00421fcb:
        jl short L_00421fc0
    L_00421fcd:
        pop esi
    L_00421fce:
        or eax,0FFFFFFFFh
    L_00421fd1:
        pop ebx
    L_00421fd2:
        ret
    L_00421fd3:
        cmp esi,0Ah
    L_00421fd6:
        jl short L_00421fde
    L_00421fd8:
        pop esi
    L_00421fd9:
        or eax,0FFFFFFFFh
    L_00421fdc:
        pop ebx
    L_00421fdd:
        ret
    L_00421fde:
        mov ecx,9
    L_00421fe3:
        cmp esi,ecx
    L_00421fe5:
        jge short L_0042202b
    L_00421fe7:
        lea edx,[eax+eax*4]
    L_00421fea:
        lea eax,[ecx+edx*2]
    L_00421fed:
        lea eax,[eax+eax*2]
    L_00421ff0:
        lea eax,[edi+eax*8]
    L_00421ff3:
        lea edx,[eax-8]
    L_00421ff6:
        mov ebx,dword ptr [edx]
    L_00421ff8:
        add eax,10h
    L_00421ffb:
        mov dword ptr [eax],ebx
    L_00421ffd:
        mov ebx,dword ptr [edx+4]
    L_00422000:
        mov dword ptr [eax+4],ebx
    L_00422003:
        mov ebx,dword ptr [edx+8]
    L_00422006:
        mov dword ptr [eax+8],ebx
    L_00422009:
        mov ebx,dword ptr [edx+0Ch]
    L_0042200c:
        mov dword ptr [eax+0Ch],ebx
    L_0042200f:
        mov ebx,dword ptr [edx+10h]
    L_00422012:
        mov dword ptr [eax+10h],ebx
    L_00422015:
        mov edx,dword ptr [edx+14h]
    L_00422018:
        dec ecx
    L_00422019:
        cmp ecx,esi
    L_0042201b:
        mov dword ptr [eax+14h],edx
    L_0042201e:
        mov eax,dword ptr [data_00474c74]
    L_00422023:
        jg short L_00421fe7
    L_00422025:
        mov edx,dword ptr [data_00474c44]
    L_0042202b:
        lea eax,[eax+eax*4]
    L_0042202e:
        lea eax,[esi+eax*2]
    L_00422031:
        lea ecx,[eax+eax*2]
    L_00422034:
        mov dword ptr [edi+ecx*8+10h],edx
    L_00422038:
        mov eax,dword ptr [data_00474c74]
    L_0042203d:
        mov cl,byte ptr [data_00474c90]
    L_00422043:
        lea edx,[eax+eax*4]
    L_00422046:
        lea eax,[esi+edx*2]
    L_00422049:
        lea eax,[eax+eax*2]
    L_0042204c:
        mov byte ptr [edi+eax*8+15h],cl
    L_00422050:
        mov eax,dword ptr [data_00474c74]
    L_00422055:
        mov cl,byte ptr [data_00474c7c]
    L_0042205b:
        lea edx,[eax+eax*4]
    L_0042205e:
        lea eax,[esi+edx*2]
    L_00422061:
        lea eax,[eax+eax*2]
    L_00422064:
        mov byte ptr [edi+eax*8+14h],cl
    L_00422068:
        mov eax,dword ptr [data_00474c74]
    L_0042206d:
        lea edx,[eax+eax*4]
    L_00422070:
        lea eax,[esi+edx*2]
    L_00422073:
        lea eax,[eax+eax*2]
    L_00422076:
        lea ecx,[edi+eax*8+20h]
    L_0042207a:
        push ecx
    L_0042207b:
        call asm_FID_conflict___time32_00452b71
    L_00422080:
        mov eax,dword ptr [data_00474c74]
    L_00422085:
        lea edx,[eax+eax*4]
    L_00422088:
        lea eax,[esi+edx*2]
    L_0042208b:
        mov edx,dword ptr [data_0046e354]
    L_00422091:
        lea eax,[eax+eax*2]
    L_00422094:
        lea ecx,[edi+eax*8+16h]
    L_00422098:
        mov dword ptr [ecx],edx
    L_0042209a:
        mov eax,dword ptr [data_0046e358]
    L_0042209f:
        mov dword ptr [ecx+4],eax
    L_004220a2:
        mov dl,byte ptr [data_0046e35c]
    L_004220a8:
        mov eax,dword ptr [data_00477708]
    L_004220ad:
        mov byte ptr [ecx+8],dl
    L_004220b0:
        fld qword ptr [eax+24h]
    L_004220b3:
        fdiv qword ptr [eax+2Ch]
    L_004220b6:
        mov eax,dword ptr [data_00474c74]
    L_004220bb:
        lea eax,[eax+eax*4]
    L_004220be:
        lea eax,[esi+eax*2]
    L_004220c1:
        add esp,4
    L_004220c4:
        lea ecx,[eax+eax*2]
    L_004220c7:
        mov eax,esi
    L_004220c9:
        pop esi
    L_004220ca:
        pop ebx
    L_004220cb:
        fmul dword ptr [data_00470b44]
    L_004220d1:
        fsubr dword ptr [data_00470b44]
    L_004220d7:
        fstp dword ptr [edi+ecx*8+24h]
    L_004220db:
        ret
    }
}
