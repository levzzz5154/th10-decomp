// BLOCKED (D3801): closest_byte_count=0/781; first_diff=none (exact retail
// naked baseline; no readable candidate retained).
// residual_class=private EAX receiver passed to FUN_00436af0, followed by the
// 256-step seed/palette update and 15 CreateFontA handle initializations.
// variants_tested=live Ghidra decompilation plus caller xref 0x00420260;
// typed cache/font loop candidate; exact MSVC 13.10 naked baseline
// probe=781/781.
// next_lever=expose a receiver-aware 00436AF0 surface call, or recover its
// effects as a verified semantic implementation, before removing this bridge.
// audit=matching2/reference/recovery_notes/font_cache_init_00437a00.md
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00437A00..0x00437D0C: FUN_00437a00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00437a00_00437a00() {
    __asm {
    L_00437a00:
        push 1Ah
    L_00437a02:
        push 40h
    L_00437a04:
        push 400h
    L_00437a09:
        mov eax,474CB0h
    L_00437a0e:
        call asm_FUN_00436af0_00436af0
    L_00437a13:
        test al,al
    L_00437a15:
        jne short L_00437a2a
    L_00437a17:
        push 15h
    L_00437a19:
        push 40h
    L_00437a1b:
        push 400h
    L_00437a20:
        mov eax,474CB0h
    L_00437a25:
        call asm_FUN_00436af0_00436af0
    L_00437a2a:
        push esi
    L_00437a2b:
        mov esi,dword ptr [data_004918b4]
    L_00437a31:
        xor edx,edx
    L_00437a33:
        mov eax,dword ptr [data_004918b0]
    L_00437a38:
        xor eax,9630h
    L_00437a3d:
        xor ecx,ecx
    L_00437a3f:
        sub eax,6553h
    L_00437a44:
        mov cx,ax
    L_00437a47:
        shr cx,0Eh
    L_00437a4b:
        shl eax,2
    L_00437a4e:
        add ecx,eax
    L_00437a50:
        mov word ptr [data_004918b0],cx
    L_00437a57:
        shr cx,9
    L_00437a5b:
        inc esi
    L_00437a5c:
        mov byte ptr [edx+474CB0h],cl
    L_00437a62:
        inc edx
    L_00437a63:
        cmp edx,100h
    L_00437a69:
        jb short L_00437a33
    L_00437a6b:
        push 46F36Ch
    L_00437a70:
        push 11h
    L_00437a72:
        push 4
    L_00437a74:
        push 0
    L_00437a76:
        push 0
    L_00437a78:
        push 80h
    L_00437a7d:
        push 0
    L_00437a7f:
        push 0
    L_00437a81:
        push 0
    L_00437a83:
        push 190h
    L_00437a88:
        push 0
    L_00437a8a:
        push 0
    L_00437a8c:
        push 0
    L_00437a8e:
        mov dword ptr [data_004918b4],esi
    L_00437a94:
        mov esi,dword ptr [data_00466034]
    L_00437a9a:
        push 20h
    L_00437a9c:
        call esi
    L_00437a9e:
        push 46F36Ch
    L_00437aa3:
        push 11h
    L_00437aa5:
        push 4
    L_00437aa7:
        push 0
    L_00437aa9:
        push 0
    L_00437aab:
        push 80h
    L_00437ab0:
        push 0
    L_00437ab2:
        push 0
    L_00437ab4:
        push 0
    L_00437ab6:
        push 190h
    L_00437abb:
        push 0
    L_00437abd:
        push 0
    L_00437abf:
        push 0
    L_00437ac1:
        push 22h
    L_00437ac3:
        mov dword ptr [data_004918a0],eax
    L_00437ac8:
        call esi
    L_00437aca:
        push 46F36Ch
    L_00437acf:
        push 11h
    L_00437ad1:
        push 4
    L_00437ad3:
        push 0
    L_00437ad5:
        push 0
    L_00437ad7:
        push 80h
    L_00437adc:
        push 0
    L_00437ade:
        push 0
    L_00437ae0:
        push 0
    L_00437ae2:
        push 190h
    L_00437ae7:
        push 0
    L_00437ae9:
        push 0
    L_00437aeb:
        push 0
    L_00437aed:
        push 24h
    L_00437aef:
        mov dword ptr [data_0049189c],eax
    L_00437af4:
        call esi
    L_00437af6:
        push 46F36Ch
    L_00437afb:
        push 11h
    L_00437afd:
        push 4
    L_00437aff:
        push 0
    L_00437b01:
        push 0
    L_00437b03:
        push 80h
    L_00437b08:
        push 0
    L_00437b0a:
        push 0
    L_00437b0c:
        push 0
    L_00437b0e:
        push 190h
    L_00437b13:
        push 0
    L_00437b15:
        push 0
    L_00437b17:
        push 0
    L_00437b19:
        push 26h
    L_00437b1b:
        mov dword ptr [data_00491898],eax
    L_00437b20:
        call esi
    L_00437b22:
        push 46F36Ch
    L_00437b27:
        push 11h
    L_00437b29:
        push 4
    L_00437b2b:
        push 0
    L_00437b2d:
        push 0
    L_00437b2f:
        push 80h
    L_00437b34:
        push 0
    L_00437b36:
        push 0
    L_00437b38:
        push 0
    L_00437b3a:
        push 190h
    L_00437b3f:
        push 0
    L_00437b41:
        push 0
    L_00437b43:
        push 0
    L_00437b45:
        push 28h
    L_00437b47:
        mov dword ptr [data_00491894],eax
    L_00437b4c:
        call esi
    L_00437b4e:
        push 46F36Ch
    L_00437b53:
        push 11h
    L_00437b55:
        push 4
    L_00437b57:
        push 0
    L_00437b59:
        push 0
    L_00437b5b:
        push 80h
    L_00437b60:
        push 0
    L_00437b62:
        push 0
    L_00437b64:
        push 0
    L_00437b66:
        push 190h
    L_00437b6b:
        push 0
    L_00437b6d:
        push 0
    L_00437b6f:
        push 0
    L_00437b71:
        push 2Ah
    L_00437b73:
        mov dword ptr [data_00491890],eax
    L_00437b78:
        call esi
    L_00437b7a:
        push 46F36Ch
    L_00437b7f:
        push 11h
    L_00437b81:
        push 4
    L_00437b83:
        push 0
    L_00437b85:
        push 0
    L_00437b87:
        push 80h
    L_00437b8c:
        push 0
    L_00437b8e:
        push 0
    L_00437b90:
        push 0
    L_00437b92:
        push 190h
    L_00437b97:
        push 0
    L_00437b99:
        push 0
    L_00437b9b:
        push 0
    L_00437b9d:
        push 2Ch
    L_00437b9f:
        mov dword ptr [data_0049188c],eax
    L_00437ba4:
        call esi
    L_00437ba6:
        push 46F36Ch
    L_00437bab:
        push 11h
    L_00437bad:
        push 4
    L_00437baf:
        push 0
    L_00437bb1:
        push 0
    L_00437bb3:
        push 80h
    L_00437bb8:
        push 0
    L_00437bba:
        push 0
    L_00437bbc:
        push 0
    L_00437bbe:
        push 190h
    L_00437bc3:
        push 0
    L_00437bc5:
        push 0
    L_00437bc7:
        push 0
    L_00437bc9:
        push 2Eh
    L_00437bcb:
        mov dword ptr [data_00491888],eax
    L_00437bd0:
        call esi
    L_00437bd2:
        push 46F36Ch
    L_00437bd7:
        push 11h
    L_00437bd9:
        push 4
    L_00437bdb:
        push 0
    L_00437bdd:
        push 0
    L_00437bdf:
        push 80h
    L_00437be4:
        push 0
    L_00437be6:
        push 0
    L_00437be8:
        push 0
    L_00437bea:
        push 190h
    L_00437bef:
        push 0
    L_00437bf1:
        push 0
    L_00437bf3:
        push 0
    L_00437bf5:
        push 30h
    L_00437bf7:
        mov dword ptr [data_00491884],eax
    L_00437bfc:
        call esi
    L_00437bfe:
        push 46F36Ch
    L_00437c03:
        push 11h
    L_00437c05:
        push 4
    L_00437c07:
        push 0
    L_00437c09:
        push 0
    L_00437c0b:
        push 80h
    L_00437c10:
        push 0
    L_00437c12:
        push 0
    L_00437c14:
        push 0
    L_00437c16:
        push 190h
    L_00437c1b:
        push 0
    L_00437c1d:
        push 0
    L_00437c1f:
        push 0
    L_00437c21:
        push 32h
    L_00437c23:
        mov dword ptr [data_00491880],eax
    L_00437c28:
        call esi
    L_00437c2a:
        mov dword ptr [data_0049187c],eax
    L_00437c2f:
        push 46F36Ch
    L_00437c34:
        push 11h
    L_00437c36:
        push 4
    L_00437c38:
        push 0
    L_00437c3a:
        push 0
    L_00437c3c:
        push 80h
    L_00437c41:
        push 0
    L_00437c43:
        push 0
    L_00437c45:
        push 0
    L_00437c47:
        push 190h
    L_00437c4c:
        push 0
    L_00437c4e:
        push 0
    L_00437c50:
        push 0
    L_00437c52:
        push 34h
    L_00437c54:
        call esi
    L_00437c56:
        push 46F36Ch
    L_00437c5b:
        push 11h
    L_00437c5d:
        push 4
    L_00437c5f:
        push 0
    L_00437c61:
        push 0
    L_00437c63:
        push 80h
    L_00437c68:
        push 0
    L_00437c6a:
        push 0
    L_00437c6c:
        push 0
    L_00437c6e:
        push 190h
    L_00437c73:
        push 0
    L_00437c75:
        push 0
    L_00437c77:
        push 0
    L_00437c79:
        push 36h
    L_00437c7b:
        mov dword ptr [data_00491878],eax
    L_00437c80:
        call esi
    L_00437c82:
        push 46F36Ch
    L_00437c87:
        push 11h
    L_00437c89:
        push 4
    L_00437c8b:
        push 0
    L_00437c8d:
        push 0
    L_00437c8f:
        push 80h
    L_00437c94:
        push 0
    L_00437c96:
        push 0
    L_00437c98:
        push 0
    L_00437c9a:
        push 190h
    L_00437c9f:
        push 0
    L_00437ca1:
        push 0
    L_00437ca3:
        push 0
    L_00437ca5:
        push 38h
    L_00437ca7:
        mov dword ptr [data_00491874],eax
    L_00437cac:
        call esi
    L_00437cae:
        push 46F36Ch
    L_00437cb3:
        push 11h
    L_00437cb5:
        push 4
    L_00437cb7:
        push 0
    L_00437cb9:
        push 0
    L_00437cbb:
        push 80h
    L_00437cc0:
        push 0
    L_00437cc2:
        push 0
    L_00437cc4:
        push 0
    L_00437cc6:
        push 190h
    L_00437ccb:
        push 0
    L_00437ccd:
        push 0
    L_00437ccf:
        push 0
    L_00437cd1:
        push 3Ah
    L_00437cd3:
        mov dword ptr [data_00491870],eax
    L_00437cd8:
        call esi
    L_00437cda:
        push 46F36Ch
    L_00437cdf:
        push 11h
    L_00437ce1:
        push 4
    L_00437ce3:
        push 0
    L_00437ce5:
        push 0
    L_00437ce7:
        push 80h
    L_00437cec:
        push 0
    L_00437cee:
        push 0
    L_00437cf0:
        push 0
    L_00437cf2:
        push 190h
    L_00437cf7:
        push 0
    L_00437cf9:
        push 0
    L_00437cfb:
        push 0
    L_00437cfd:
        push 3Ch
    L_00437cff:
        mov dword ptr [data_0049186c],eax
    L_00437d04:
        call esi
    L_00437d06:
        mov dword ptr [data_00491868],eax
    L_00437d0b:
        pop esi
    L_00437d0c:
        ret
    }
}
