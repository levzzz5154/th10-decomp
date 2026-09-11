#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00401000..0x004010FA: GameThread_ConstructOverlay
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameThread_Construct_00401000() {
    __asm {
    L_00401000:
        mov dword ptr [esi],46CB14h
    L_00401006:
        mov eax,dword ptr [esi+80h]
    L_0040100c:
        lea edx,[esi+14h]
    L_0040100f:
        push ebx
    L_00401010:
        mov ebx,0FFFFFFFEh
    L_00401015:
        push edi
    L_00401016:
        and eax,ebx
    L_00401018:
        mov dword ptr [edx+6Ch],eax
    L_0040101b:
        and dword ptr [edx+0B0h],ebx
    L_00401021:
        and dword ptr [edx+0FCh],ebx
    L_00401027:
        and dword ptr [edx+128h],ebx
    L_0040102d:
        and dword ptr [edx+174h],ebx
    L_00401033:
        and dword ptr [edx+1B0h],ebx
    L_00401039:
        and dword ptr [edx+1FCh],ebx
    L_0040103f:
        and dword ptr [edx+228h],ebx
    L_00401045:
        and dword ptr [edx+378h],ebx
    L_0040104b:
        xor eax,eax
    L_0040104d:
        mov edi,edx
    L_0040104f:
        mov ecx,0EBh
    L_00401054:
        rep stosd
    L_00401056:
        mov word ptr [edx+384h],0FFFFh
    L_0040105f:
        mov eax,dword ptr [esi+42Ch]
    L_00401065:
        lea edx,[esi+3C0h]
    L_0040106b:
        and eax,ebx
    L_0040106d:
        mov dword ptr [edx+6Ch],eax
    L_00401070:
        and dword ptr [edx+0B0h],ebx
    L_00401076:
        and dword ptr [edx+0FCh],ebx
    L_0040107c:
        and dword ptr [edx+128h],ebx
    L_00401082:
        and dword ptr [edx+174h],ebx
    L_00401088:
        and dword ptr [edx+1B0h],ebx
    L_0040108e:
        and dword ptr [edx+1FCh],ebx
    L_00401094:
        and dword ptr [edx+228h],ebx
    L_0040109a:
        and dword ptr [edx+378h],ebx
    L_004010a0:
        xor eax,eax
    L_004010a2:
        mov ecx,0EBh
    L_004010a7:
        mov edi,edx
    L_004010a9:
        rep stosd
    L_004010ab:
        mov word ptr [edx+384h],0FFFFh
    L_004010b4:
        mov ecx,226Bh
    L_004010b9:
        mov edi,esi
    L_004010bb:
        rep stosd
    L_004010bd:
        or dword ptr [esi+4],2
    L_004010c1:
        mov eax,3F800000h
    L_004010c6:
        mov dword ptr [data_004776e0],esi
    L_004010cc:
        mov dword ptr [esi+8974h],0FFFFFFFFh
    L_004010d6:
        mov dword ptr [esi+8978h],eax
    L_004010dc:
        mov dword ptr [esi+897Ch],eax
    L_004010e2:
        pop edi
    L_004010e3:
        mov dword ptr [esi+8984h],0
    L_004010ed:
        mov dword ptr [esi+898Ch],9
    L_004010f7:
        mov eax,esi
    L_004010f9:
        pop ebx
    L_004010fa:
        ret
    }
}





