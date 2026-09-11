#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043E9D0..0x0043EA57: FUN_0043e9d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043e9d0_0043e9d0() {
    __asm {
    L_0043e9d0:
        sub esp,10Ch
    L_0043e9d6:
        mov eax,dword ptr [data_00473660]
    L_0043e9db:
        xor eax,esp
    L_0043e9dd:
        mov dword ptr [esp+108h],eax
    L_0043e9e4:
        mov eax,dword ptr [esp+110h]
    L_0043e9eb:
        push eax
    L_0043e9ec:
        lea eax,[esp+8]
    L_0043e9f0:
        push 46E1C8h
    L_0043e9f5:
        push eax
    L_0043e9f6:
        call asm_sprintf_00452ae8
    L_0043e9fb:
        lea eax,[esp+10h]
    L_0043e9ff:
        add esp,0Ch
    L_0043ea02:
        lea edx,[eax+1]
    L_0043ea05:
        mov cl,byte ptr [eax]
    L_0043ea07:
        inc eax
    L_0043ea08:
        test cl,cl
    L_0043ea0a:
        jne short L_0043ea05
    L_0043ea0c:
        sub eax,edx
    L_0043ea0e:
        lea eax,[esp+eax+4]
    L_0043ea12:
        lea ecx,[esp+4]
    L_0043ea16:
        push ecx
    L_0043ea17:
        mov byte ptr [eax-3],6Dh
    L_0043ea1b:
        mov byte ptr [eax-2],61h
    L_0043ea1f:
        mov byte ptr [eax-1],70h
    L_0043ea23:
        call asm_File_ProbeExists_0044b4d0
    L_0043ea28:
        test eax,eax
    L_0043ea2a:
        TH10_REL8(0x74, 0x0043ea2a, VA_asm_target_0043ea93)
    L_0043ea2c:
        push 1
    L_0043ea2e:
        lea edx,[esp+4]
    L_0043ea32:
        push edx
    L_0043ea33:
        lea eax,[esp+0Ch]
    L_0043ea37:
        call asm_FUN_0044b360_0044b360
    L_0043ea3c:
        mov ecx,dword ptr [esi+110h]
    L_0043ea42:
        mov edx,dword ptr [esi+114h]
    L_0043ea48:
        mov dword ptr [esi+12Ch],eax
    L_0043ea4e:
        add ecx,edx
    L_0043ea50:
        xor eax,eax
    L_0043ea52:
        test ecx,ecx
    L_0043ea54:
        TH10_REL8(0x7e, 0x0043ea54, VA_asm_target_0043ea9d)
    L_0043ea56:
        TH10_REL8(0xeb, 0x0043ea56, VA_asm_FUN_0043e9d0_part_0043ea60)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0043ea60:
        mov ecx,dword ptr [esi+12Ch]
    L_0043ea66:
        add dword ptr [ecx+eax*4],ecx
    L_0043ea69:
        mov edx,dword ptr [esi+110h]
    L_0043ea6f:
        mov ecx,dword ptr [esi+114h]
    L_0043ea75:
        inc eax
    L_0043ea76:
        add edx,ecx
    L_0043ea78:
        cmp eax,edx
    L_0043ea7a:
        jl short L_0043ea60
    L_0043ea7c:
        mov ecx,dword ptr [esp+108h]
    L_0043ea83:
        xor ecx,esp
    L_0043ea85:
        call asm_security_check_cookie_00458ea5
    L_0043ea8a:
        add esp,10Ch
    L_0043ea90:
        ret 4
    L_0043ea93:
        mov dword ptr [esi+12Ch],0
    L_0043ea9d:
        mov ecx,dword ptr [esp+108h]
    L_0043eaa4:
        xor ecx,esp
    L_0043eaa6:
        call asm_security_check_cookie_00458ea5
    L_0043eaab:
        add esp,10Ch
    L_0043eab1:
        ret 4
    }
}
