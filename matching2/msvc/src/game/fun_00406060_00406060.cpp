#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00402720..0x0040284F: FUN_00402720
// Naked body preserves the retail register/stack ABI.

// 0x00406060..0x00406115: FUN_00406060
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00406060_00406060() {
    __asm {
    L_00406060:
        push 0FFFFFFFFh
    L_00406062:
        push 4658ABh
    L_00406067:
        mov eax,dword ptr fs:[0]
    L_0040606d:
        push eax
    L_0040606e:
        mov dword ptr fs:[0],esp
    L_00406075:
        push ecx
    L_00406076:
        push esi
    L_00406077:
        push 3E0B54h
    L_0040607c:
        call asm_operator_new_00452493
    L_00406081:
        mov esi,eax
    L_00406083:
        add esp,4
    L_00406086:
        mov dword ptr [esp+4],esi
    L_0040608a:
        test esi,esi
    L_0040608c:
        mov dword ptr [esp+10h],0
    L_00406094:
        je short L_004060c8
    L_00406096:
        push edi
    L_00406097:
        push 405DE0h
    L_0040609c:
        push 405D00h
    L_004060a1:
        push 7D1h
    L_004060a6:
        push 7F0h
    L_004060ab:
        lea eax,[esi+60h]
    L_004060ae:
        push eax
    L_004060af:
        call asm_eh_vector_constructor_iterator_0045252d
    L_004060b4:
        mov ecx,0F82D5h
    L_004060b9:
        xor eax,eax
    L_004060bb:
        mov edi,esi
    L_004060bd:
        rep stosd
    L_004060bf:
        mov dword ptr [data_004776f0],esi
    L_004060c5:
        pop edi
    L_004060c6:
        jmp short L_004060ca
    L_004060c8:
        xor esi,esi
    L_004060ca:
        push ebx
    L_004060cb:
        mov ebx,esi
    L_004060cd:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_004060d5:
        call asm_FUN_00405e20_00405e20
    L_004060da:
        test eax,eax
    L_004060dc:
        pop ebx
    L_004060dd:
        je short L_00406104
    L_004060df:
        test esi,esi
    L_004060e1:
        je short L_004060f2
    L_004060e3:
        push esi
    L_004060e4:
        call asm_ItemManager_DestroyRetail_00405f70
    L_004060e9:
        push esi
    L_004060ea:
        call asm_free_004524a1
    L_004060ef:
        add esp,4
    L_004060f2:
        xor eax,eax
    L_004060f4:
        pop esi
    L_004060f5:
        mov ecx,dword ptr [esp+4]
    L_004060f9:
        mov dword ptr fs:[0],ecx
    L_00406100:
        add esp,10h
    L_00406103:
        ret
    L_00406104:
        mov ecx,dword ptr [esp+8]
    L_00406108:
        mov eax,esi
    L_0040610a:
        pop esi
    L_0040610b:
        mov dword ptr fs:[0],ecx
    L_00406112:
        add esp,10h
    L_00406115:
        ret
    }
}
