#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// BLOCKED: closest_byte_count=87/301; first_diff=0x0043D122;
// residual_class=EAX receiver ABI, virtual-release slot shape, and private ESI
// receiver for MidiWorker_StopRetail (0x0043DAB0);
// variants_tested=live Ghidra decompile/callers (0x0043D120, 0x00438AD0,
// 0x0043DAB0) and MSVC 13.10 readable offset-layout/vtable candidate
// (323-byte extent, 87 matching bytes); next_lever=schema2 native-LTCG with
// the real window caller and MidiWorker stop body visible.

// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.

// 0x0043D120..0x0043D24C: FUN_0043d120
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d120_0043d120() {
    __asm {
    L_0043d120:
        push ebp
    L_0043d121:
        push esi
    L_0043d122:
        mov esi,eax
    L_0043d124:
        mov eax,dword ptr [esi+1F84h]
    L_0043d12a:
        xor ebp,ebp
    L_0043d12c:
        cmp eax,ebp
    L_0043d12e:
        push edi
    L_0043d12f:
        je short L_0043d140
    L_0043d131:
        push eax
    L_0043d132:
        call asm_free_00452422
    L_0043d137:
        add esp,4
    L_0043d13a:
        mov dword ptr [esi+1F84h],ebp
    L_0043d140:
        push ebx
    L_0043d141:
        lea edi,[esi+8]
    L_0043d144:
        mov ebx,80h
    L_0043d149:
        lea esp,[esp+force_disp32_zero]
    L_0043d150:
        mov eax,dword ptr [edi+200h]
    L_0043d156:
        cmp eax,ebp
    L_0043d158:
        je short L_0043d166
    L_0043d15a:
        mov ecx,dword ptr [eax]
    L_0043d15c:
        push eax
    L_0043d15d:
        call dword ptr [ecx+8]
    L_0043d160:
        mov dword ptr [edi+200h],ebp
    L_0043d166:
        mov eax,dword ptr [edi]
    L_0043d168:
        cmp eax,ebp
    L_0043d16a:
        je short L_0043d174
    L_0043d16c:
        mov edx,dword ptr [eax]
    L_0043d16e:
        push eax
    L_0043d16f:
        call dword ptr [edx+8]
    L_0043d172:
        mov dword ptr [edi],ebp
    L_0043d174:
        add edi,4
    L_0043d177:
        dec ebx
    L_0043d178:
        jne short L_0043d150
    L_0043d17a:
        lea edi,[esi+5230h]
    L_0043d180:
        mov ebx,25h
    L_0043d185:
        mov eax,dword ptr [edi]
    L_0043d187:
        cmp eax,ebp
    L_0043d189:
        je short L_0043d196
    L_0043d18b:
        push eax
    L_0043d18c:
        call asm_free_00452422
    L_0043d191:
        add esp,4
    L_0043d194:
        mov dword ptr [edi],ebp
    L_0043d196:
        add edi,4
    L_0043d199:
        dec ebx
    L_0043d19a:
        jne short L_0043d185
    L_0043d19c:
        cmp dword ptr [esi+610h],ebp
    L_0043d1a2:
        pop ebx
    L_0043d1a3:
        je asm_target_0043d247
    L_0043d1a9:
        mov eax,dword ptr [esi+60Ch]
    L_0043d1af:
        push 1
    L_0043d1b1:
        push eax
    L_0043d1b2:
        call dword ptr [data_00466214]
    L_0043d1b8:
        call asm_MidiWorker_StopRetail_0043dab0
    L_0043d1bd:
        mov eax,dword ptr [esi+608h]
    L_0043d1c3:
        mov dword ptr [esi],ebp
    L_0043d1c5:
        mov ecx,dword ptr [eax]
    L_0043d1c7:
        push eax
    L_0043d1c8:
        call dword ptr [ecx+48h]
    L_0043d1cb:
        mov eax,dword ptr [esi+608h]
    L_0043d1d1:
        cmp eax,ebp
    L_0043d1d3:
        je short L_0043d1e1
    L_0043d1d5:
        mov edx,dword ptr [eax]
    L_0043d1d7:
        push eax
    L_0043d1d8:
        call dword ptr [edx+8]
    L_0043d1db:
        mov dword ptr [esi+608h],ebp
    L_0043d1e1:
        mov ecx,dword ptr [esi+5208h]
    L_0043d1e7:
        cmp ecx,ebp
    L_0043d1e9:
        je short L_0043d1f7
    L_0043d1eb:
        mov eax,dword ptr [ecx]
    L_0043d1ed:
        push 1
    L_0043d1ef:
        call dword ptr [eax]
    L_0043d1f1:
        mov dword ptr [esi+5208h],ebp
    L_0043d1f7:
        mov edi,dword ptr [esi+610h]
    L_0043d1fd:
        cmp edi,ebp
    L_0043d1ff:
        je short L_0043d21e
    L_0043d201:
        mov eax,dword ptr [edi]
    L_0043d203:
        cmp eax,ebp
    L_0043d205:
        je short L_0043d20f
    L_0043d207:
        mov ecx,dword ptr [eax]
    L_0043d209:
        push eax
    L_0043d20a:
        call dword ptr [ecx+8]
    L_0043d20d:
        mov dword ptr [edi],ebp
    L_0043d20f:
        push edi
    L_0043d210:
        call asm_free_004524a1
    L_0043d215:
        add esp,4
    L_0043d218:
        mov dword ptr [esi+610h],ebp
    L_0043d21e:
        add esi,1EC0h
    L_0043d224:
        mov edi,10h
    L_0043d229:
        lea esp,[esp+force_disp32_zero]
    L_0043d230:
        mov eax,dword ptr [esi]
    L_0043d232:
        cmp eax,ebp
    L_0043d234:
        je short L_0043d241
    L_0043d236:
        push eax
    L_0043d237:
        call asm_free_00452422
    L_0043d23c:
        add esp,4
    L_0043d23f:
        mov dword ptr [esi],ebp
    L_0043d241:
        add esi,4
    L_0043d244:
        dec edi
    L_0043d245:
        jne short L_0043d230
    L_0043d247:
        pop edi
    L_0043d248:
        pop esi
    L_0043d249:
        xor eax,eax
    L_0043d24b:
        pop ebp
    L_0043d24c:
        ret
    }
}
