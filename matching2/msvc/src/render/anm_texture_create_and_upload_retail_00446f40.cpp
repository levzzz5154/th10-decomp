// BLOCKED (D3702): closest_byte_count=0/264; first_diff=extent (candidate
// extent 130 vs retail 264).
// residual_class=abi+structural: readable cdecl texture candidate emitted a
// 130-byte body while retail requires EAX/ECX/EBX live-ins, indirect D3D
// calls, and the private texture/image layout.
// variants_tested=live Ghidra decompile, archived semantic model, and MSVC
// 13.10 readable candidate probe (130-byte extent vs 264-byte retail).
// next_lever=native-LTCG cluster with the real ANM caller and D3D interface
// declarations, retaining the EAX/ECX/EBX entry convention.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446C70..0x00446D62: FUN_00446c70
// Naked body preserves the retail register/stack ABI.

// 0x00446F40..0x00447047: AnmTexture_CreateAndUploadRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnmTexture_CreateAndUploadRetail_00446f40() {
    __asm {
    L_00446f40:
        sub esp,14h
    L_00446f43:
        push esi
    L_00446f44:
        push edi
    L_00446f45:
        mov edi,eax
    L_00446f47:
        test byte ptr [data_00491d78],1
    L_00446f4e:
        mov esi,ecx
    L_00446f50:
        mov dword ptr [esp+8],0
    L_00446f58:
        je short L_00446f7b
    L_00446f5a:
        mov eax,dword ptr [edi*4+46F288h]
    L_00446f61:
        cmp eax,15h
    L_00446f64:
        je short L_00446f76
    L_00446f66:
        test eax,eax
    L_00446f68:
        je short L_00446f76
    L_00446f6a:
        cmp eax,14h
    L_00446f6d:
        jne short L_00446f7b
    L_00446f6f:
        mov edi,3
    L_00446f74:
        jmp short L_00446f7b
    L_00446f76:
        mov edi,5
    L_00446f7b:
        mov edx,dword ptr [edi*4+46F288h]
    L_00446f82:
        movsx eax,word ptr [esi+8]
    L_00446f86:
        movsx ecx,word ptr [esi+0Ah]
    L_00446f8a:
        push ebx
    L_00446f8b:
        push 1
    L_00446f8d:
        push edx
    L_00446f8e:
        mov edx,dword ptr [data_00491c30]
    L_00446f94:
        push 0
    L_00446f96:
        push 1
    L_00446f98:
        mov dword ptr [esp+28h],eax
    L_00446f9c:
        mov eax,dword ptr [esp+38h]
    L_00446fa0:
        mov dword ptr [esp+2Ch],ecx
    L_00446fa4:
        mov ecx,dword ptr [esp+34h]
    L_00446fa8:
        push eax
    L_00446fa9:
        push ecx
    L_00446faa:
        push edx
    L_00446fab:
        mov dword ptr [esp+2Ch],0
    L_00446fb3:
        mov dword ptr [esp+30h],0
    L_00446fbb:
        call asm_D3DXCreateTexture_004521a0
    L_00446fc0:
        test eax,eax
    L_00446fc2:
        je short L_00446fdd
    L_00446fc4:
        mov eax,dword ptr [esp+8]
    L_00446fc8:
        test eax,eax
    L_00446fca:
        je short L_00446fd2
    L_00446fcc:
        mov ecx,dword ptr [eax]
    L_00446fce:
        push eax
    L_00446fcf:
        call dword ptr [ecx+8]
    L_00446fd2:
        pop edi
    L_00446fd3:
        or eax,0FFFFFFFFh
    L_00446fd6:
        pop esi
    L_00446fd7:
        add esp,14h
    L_00446fda:
        ret 8
    L_00446fdd:
        mov eax,dword ptr [ebx]
    L_00446fdf:
        mov edx,dword ptr [eax]
    L_00446fe1:
        lea ecx,[esp+8]
    L_00446fe5:
        push ecx
    L_00446fe6:
        push 0
    L_00446fe8:
        push eax
    L_00446fe9:
        call dword ptr [edx+48h]
    L_00446fec:
        movsx eax,word ptr [esi+6]
    L_00446ff0:
        movsx ecx,word ptr [esi+8]
    L_00446ff4:
        push 0
    L_00446ff6:
        shl eax,2
    L_00446ff9:
        imul ecx,dword ptr [eax+46F2A0h]
    L_00447000:
        push 1
    L_00447002:
        lea edx,[esp+14h]
    L_00447006:
        push edx
    L_00447007:
        mov edx,dword ptr [eax+46F288h]
    L_0044700d:
        push 0
    L_0044700f:
        push ecx
    L_00447010:
        mov ecx,dword ptr [esp+1Ch]
    L_00447014:
        push edx
    L_00447015:
        add esi,10h
    L_00447018:
        push esi
    L_00447019:
        lea eax,[esp+28h]
    L_0044701d:
        push eax
    L_0044701e:
        push 0
    L_00447020:
        push ecx
    L_00447021:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_00447026:
        mov eax,dword ptr [esp+8]
    L_0044702a:
        test eax,eax
    L_0044702c:
        mov edx,dword ptr [edi*4+46F2A0h]
    L_00447033:
        mov dword ptr [ebx+0Ch],edx
    L_00447036:
        je short L_0044703e
    L_00447038:
        mov ecx,dword ptr [eax]
    L_0044703a:
        push eax
    L_0044703b:
        call dword ptr [ecx+8]
    L_0044703e:
        pop edi
    L_0044703f:
        xor eax,eax
    L_00447041:
        pop esi
    L_00447042:
        add esp,14h
    L_00447045:
        ret 8
    }
}
