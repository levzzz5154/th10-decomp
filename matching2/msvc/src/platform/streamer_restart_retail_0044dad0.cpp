#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// BLOCKED (D3505): closest_byte_count=37/213; first_diff=0x0044DAD0;
// residual_class=private EDI receiver, hidden ECX refill flag, EAX/ESI
// streamer helper arguments, and virtual-release stack/receiver setup.
// variants_tested=standalone typed Streamer::Restart candidate (216-byte
// extent, 37/213 equal, first diff at entry); live-Ghidra decompile, caller
// 0x0043DDF0, and callees 0x0044D300/0x0044D110/SetFilePointer.
// next_lever=native-LTCG schema2 cluster with the real 0x0043DDF0 caller,
// 0x0044D300 and 0x0044D110, and the COM/vtable release edge co-compiled.

// 0x0043A910..0x0043A9AB: FUN_0043a910
// Naked body preserves the retail register/stack ABI.

// 0x0044DAD0..0x0044DBA4: Streamer_RestartRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Streamer_RestartRetail_0044dad0() {
    __asm {
    L_0044dad0:
        push ecx
    L_0044dad1:
        mov eax,dword ptr [edi+4]
    L_0044dad4:
        mov ecx,dword ptr [eax]
    L_0044dad6:
        push ebp
    L_0044dad7:
        xor ebp,ebp
    L_0044dad9:
        cmp ecx,ebp
    L_0044dadb:
        je asm_target_0044db9d
    L_0044dae1:
        cmp dword ptr [edi+0Ch],ebp
    L_0044dae4:
        je asm_target_0044db9d
    L_0044daea:
        push ebx
    L_0044daeb:
        push esi
    L_0044daec:
        mov dword ptr [edi+5Ch],ebp
    L_0044daef:
        mov dword ptr [edi+60h],ebp
    L_0044daf2:
        mov dword ptr [edi+64h],ebp
    L_0044daf5:
        mov dword ptr [edi+68h],ebp
    L_0044daf8:
        mov esi,dword ptr [eax]
    L_0044dafa:
        lea ebx,[esp+0Ch]
    L_0044dafe:
        call asm_Platform_RunInterface_0044d300
    L_0044db03:
        cmp eax,ebp
    L_0044db05:
        jl asm_target_0044db98
    L_0044db0b:
        cmp dword ptr [esp+0Ch],ebp
    L_0044db0f:
        je short L_0044db23
    L_0044db11:
        mov eax,dword ptr [edi+4]
    L_0044db14:
        mov ecx,dword ptr [eax]
    L_0044db16:
        push ebp
    L_0044db17:
        push ecx
    L_0044db18:
        mov eax,edi
    L_0044db1a:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0044db1f:
        cmp eax,ebp
    L_0044db21:
        jl short L_0044db98
    L_0044db23:
        mov esi,dword ptr [edi+0Ch]
    L_0044db26:
        cmp dword ptr [esi+7Ch],ebp
    L_0044db29:
        je short L_0044db5b
    L_0044db2b:
        mov edx,dword ptr [esi+80h]
    L_0044db31:
        mov eax,dword ptr [esi+90h]
    L_0044db37:
        mov dword ptr [esi+84h],edx
    L_0044db3d:
        mov eax,dword ptr [eax+1Ch]
    L_0044db40:
        cmp eax,ebp
    L_0044db42:
        jle short L_0044db8c
    L_0044db44:
        mov dword ptr [esi+88h],eax
    L_0044db4a:
        mov edx,dword ptr [edi+4]
    L_0044db4d:
        mov eax,dword ptr [edx]
    L_0044db4f:
        mov ecx,dword ptr [eax]
    L_0044db51:
        push ebp
    L_0044db52:
        push eax
    L_0044db53:
        call dword ptr [ecx+34h]
    L_0044db56:
        pop esi
    L_0044db57:
        pop ebx
    L_0044db58:
        pop ebp
    L_0044db59:
        pop ecx
    L_0044db5a:
        ret
    L_0044db5b:
        mov eax,dword ptr [esi+8Ch]
    L_0044db61:
        cmp eax,ebp
    L_0044db63:
        je short L_0044db8c
    L_0044db65:
        mov ecx,dword ptr [esi+90h]
    L_0044db6b:
        mov edx,dword ptr [ecx+10h]
    L_0044db6e:
        mov ecx,dword ptr [data_004977a4]
    L_0044db74:
        push ebp
    L_0044db75:
        push ebp
    L_0044db76:
        add edx,ecx
    L_0044db78:
        push edx
    L_0044db79:
        push eax
    L_0044db7a:
        call dword ptr [data_004660c8]
    L_0044db80:
        mov eax,dword ptr [esi+90h]
    L_0044db86:
        mov ecx,dword ptr [eax+1Ch]
    L_0044db89:
        mov dword ptr [esi+8],ecx
    L_0044db8c:
        mov edx,dword ptr [edi+4]
    L_0044db8f:
        mov eax,dword ptr [edx]
    L_0044db91:
        mov ecx,dword ptr [eax]
    L_0044db93:
        push ebp
    L_0044db94:
        push eax
    L_0044db95:
        call dword ptr [ecx+34h]
    L_0044db98:
        pop esi
    L_0044db99:
        pop ebx
    L_0044db9a:
        pop ebp
    L_0044db9b:
        pop ecx
    L_0044db9c:
        ret
    L_0044db9d:
        mov eax,800401F0h
    L_0044dba2:
        pop ebp
    L_0044dba3:
        pop ecx
    L_0044dba4:
        ret
    }
}
