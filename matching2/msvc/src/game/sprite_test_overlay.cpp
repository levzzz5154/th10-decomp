#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040A940..0x0040ABC6: FUN_0040a940
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040a940_0040a940() {
    __asm {
    L_0040a940:
        sub esp,0Ch
    L_0040a943:
        push ebx
    L_0040a944:
        push esi
    L_0040a945:
        mov esi,dword ptr [data_004776e0]
    L_0040a94b:
        push 46CE50h
    L_0040a950:
        lea ebx,[esp+0Ch]
    L_0040a954:
        mov dword ptr [esp+0Ch],0
    L_0040a95c:
        mov dword ptr [esp+10h],0
    L_0040a964:
        mov dword ptr [esp+14h],0
    L_0040a96c:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040a971:
        mov eax,dword ptr [edi+30h]
    L_0040a974:
        add esp,4
    L_0040a977:
        dec eax
    L_0040a978:
        cmp eax,3
    L_0040a97b:
        ja asm_target_0040abbc
    L_0040a981:
        jmp dword ptr [eax*4+40ABC8h]
    L_0040a988:
        mov esi,dword ptr [data_004776e0]
    L_0040a98e:
        mov dword ptr [esi+8974h],0FFFF4040h
    L_0040a998:
        mov eax,dword ptr [edi+114h]
    L_0040a99e:
        mov ecx,dword ptr [edi+34h]
    L_0040a9a1:
        mov edx,dword ptr [ecx+eax*4]
    L_0040a9a4:
        push edx
    L_0040a9a5:
        push 46CE44h
    L_0040a9aa:
        lea ebx,[esp+10h]
    L_0040a9ae:
        mov dword ptr [esp+10h],42000000h
    L_0040a9b6:
        mov dword ptr [esp+14h],41800000h
    L_0040a9be:
        mov dword ptr [esp+18h],0
    L_0040a9c6:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040a9cb:
        mov eax,dword ptr [data_004776e0]
    L_0040a9d0:
        add esp,8
    L_0040a9d3:
        pop esi
    L_0040a9d4:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_0040a9de:
        mov eax,1
    L_0040a9e3:
        pop ebx
    L_0040a9e4:
        add esp,0Ch
    L_0040a9e7:
        ret
    L_0040a9e8:
        mov eax,dword ptr [edi+38h]
    L_0040a9eb:
        test eax,eax
    L_0040a9ed:
        mov esi,dword ptr [data_004776e0]
    L_0040a9f3:
        mov dword ptr [esp+8],42280000h
    L_0040a9fb:
        mov dword ptr [esp+0Ch],41800000h
    L_0040aa03:
        mov dword ptr [esp+10h],0
    L_0040aa0b:
        lea ebx,[esp+8]
    L_0040aa0f:
        je short L_0040aa2d
    L_0040aa11:
        mov ecx,dword ptr [edi+114h]
    L_0040aa17:
        mov edx,dword ptr [edi+34h]
    L_0040aa1a:
        mov eax,dword ptr [edx+ecx*4]
    L_0040aa1d:
        push eax
    L_0040aa1e:
        push 46CE3Ch
    L_0040aa23:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040aa28:
        add esp,8
    L_0040aa2b:
        jmp short L_0040aa3a
    L_0040aa2d:
        push 46CE2Ch
    L_0040aa32:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040aa37:
        add esp,4
    L_0040aa3a:
        mov eax,dword ptr [data_00477704]
    L_0040aa3f:
        test eax,eax
    L_0040aa41:
        mov esi,dword ptr [data_004776e0]
    L_0040aa47:
        mov edx,dword ptr [edi+1ECh]
    L_0040aa4d:
        mov dword ptr [esp+0Ch],41D00000h
    L_0040aa55:
        lea ebx,[esp+8]
    L_0040aa59:
        je short L_0040aa6f
    L_0040aa5b:
        mov ecx,dword ptr [eax+54h]
    L_0040aa5e:
        mov eax,dword ptr [ecx+8Ch]
    L_0040aa64:
        mov ecx,dword ptr [eax+edx*8]
    L_0040aa67:
        push ecx
    L_0040aa68:
        push 46CE24h
    L_0040aa6d:
        jmp short L_0040aa75
    L_0040aa6f:
        push edx
    L_0040aa70:
        push 46CE1Ch
    L_0040aa75:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040aa7a:
        mov esi,dword ptr [data_004776e0]
    L_0040aa80:
        add esp,8
    L_0040aa83:
        push 46CE14h
    L_0040aa88:
        lea ebx,[esp+0Ch]
    L_0040aa8c:
        mov dword ptr [esp+10h],42100000h
    L_0040aa94:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040aa99:
        fild dword ptr [edi+3Ch]
    L_0040aa9c:
        mov esi,dword ptr [data_004776e0]
    L_0040aaa2:
        push 46CE10h
    L_0040aaa7:
        fmul dword ptr [data_00470c1c]
    L_0040aaad:
        mov dword ptr [esp+10h],42000000h
    L_0040aab5:
        fadd dword ptr [data_00470b48]
    L_0040aabb:
        fstp dword ptr [esp+14h]
    L_0040aabf:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040aac4:
        add esp,8
    L_0040aac7:
        jmp asm_target_0040ab61
    L_0040aacc:
        mov ecx,dword ptr [data_00477704]
    L_0040aad2:
        mov edx,dword ptr [ecx+60h]
    L_0040aad5:
        mov esi,dword ptr [data_004776e0]
    L_0040aadb:
        push edx
    L_0040aadc:
        push 46CE04h
    L_0040aae1:
        lea ebx,[esp+10h]
    L_0040aae5:
        mov dword ptr [esp+10h],43FA0000h
    L_0040aaed:
        mov dword ptr [esp+14h],43700000h
    L_0040aaf5:
        mov dword ptr [esp+18h],0
    L_0040aafd:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040ab02:
        add esp,8
    L_0040ab05:
        pop esi
    L_0040ab06:
        mov eax,1
    L_0040ab0b:
        pop ebx
    L_0040ab0c:
        add esp,0Ch
    L_0040ab0f:
        ret
    L_0040ab10:
        mov esi,dword ptr [data_004776e0]
    L_0040ab16:
        mov dword ptr [esi+8974h],0FFA0A0A0h
    L_0040ab20:
        fld dword ptr [edi+678h]
    L_0040ab26:
        mov dword ptr [esp+8],42000000h
    L_0040ab2e:
        mov dword ptr [esp+0Ch],41800000h
    L_0040ab36:
        mov dword ptr [esp+10h],0
    L_0040ab3e:
        call asm_FUN_00463b2c_00463b2c
    L_0040ab43:
        fld dword ptr [edi+674h]
    L_0040ab49:
        push eax
    L_0040ab4a:
        call asm_FUN_00463b2c_00463b2c
    L_0040ab4f:
        push eax
    L_0040ab50:
        push 46CDF4h
    L_0040ab55:
        lea ebx,[esp+14h]
    L_0040ab59:
        call asm_GameThread_AppendFormattedMarkedRetail_00401690
    L_0040ab5e:
        add esp,0Ch
    L_0040ab61:
        mov eax,dword ptr [data_004776e0]
    L_0040ab66:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_0040ab70:
        test byte ptr [edi+684h],2
    L_0040ab77:
        je short L_0040abbc
    L_0040ab79:
        mov dword ptr [esp+8],43A00000h
    L_0040ab81:
        mov edx,dword ptr [esp+8]
    L_0040ab85:
        lea ecx,[edi+5FCh]
    L_0040ab8b:
        mov dword ptr [ecx],edx
    L_0040ab8d:
        mov dword ptr [esp+0Ch],43700000h
    L_0040ab95:
        mov eax,dword ptr [esp+0Ch]
    L_0040ab99:
        mov dword ptr [ecx+4],eax
    L_0040ab9c:
        mov eax,dword ptr [data_00491c10]
    L_0040aba1:
        mov dword ptr [esp+10h],0
    L_0040aba9:
        mov edx,dword ptr [esp+10h]
    L_0040abad:
        lea esi,[edi+2C8h]
    L_0040abb3:
        push eax
    L_0040abb4:
        mov dword ptr [ecx+8],edx
    L_0040abb7:
        call asm_FUN_00443080_00443080
    L_0040abbc:
        pop esi
    L_0040abbd:
        mov eax,1
    L_0040abc2:
        pop ebx
    L_0040abc3:
        add esp,0Ch
    L_0040abc6:
        ret
        _emit 0x90
        _emit 0xe8
        _emit 0xa9
        _emit 0x40
        _emit 0x00
        _emit 0x88
        _emit 0xa9
        _emit 0x40
        _emit 0x00
        _emit 0x10
        _emit 0xab
        _emit 0x40
        _emit 0x00
        _emit 0xcc
        _emit 0xaa
        _emit 0x40
        _emit 0x00
    }
}

