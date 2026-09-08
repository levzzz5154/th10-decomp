#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456E90..0x00457047: cvtdate
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_cvtdate_00456e90() {
    __asm {
    L_00456e90:
        push ebp
    L_00456e91:
        mov ebp,esp
    L_00456e93:
        push ecx
    L_00456e94:
        push ecx
    L_00456e95:
        push ebx
    L_00456e96:
        push esi
    L_00456e97:
        push edi
    L_00456e98:
        mov edi,dword ptr [ebp+10h]
    L_00456e9b:
        mov esi,eax
    L_00456e9d:
        mov eax,edi
    L_00456e9f:
        push 4
    L_00456ea1:
        cdq
    L_00456ea2:
        pop ebx
    L_00456ea3:
        idiv ebx
    L_00456ea5:
        cmp dword ptr [ebp+0Ch],1
    L_00456ea9:
        jne asm_target_00456f98
    L_00456eaf:
        test edx,edx
    L_00456eb1:
        mov dword ptr [ebp-8],edx
    L_00456eb4:
        jne short L_00456ec2
    L_00456eb6:
        mov eax,edi
    L_00456eb8:
        push 64h
    L_00456eba:
        cdq
    L_00456ebb:
        pop ebx
    L_00456ebc:
        idiv ebx
    L_00456ebe:
        test edx,edx
    L_00456ec0:
        jne short L_00456ee1
    L_00456ec2:
        lea eax,[edi+76Ch]
    L_00456ec8:
        cdq
    L_00456ec9:
        mov ebx,190h
    L_00456ece:
        idiv ebx
    L_00456ed0:
        test edx,edx
    L_00456ed2:
        je short L_00456ee1
    L_00456ed4:
        mov eax,esi
    L_00456ed6:
        shl eax,2
    L_00456ed9:
        mov esi,dword ptr [eax+473C58h]
    L_00456edf:
        jmp short L_00456eec
    L_00456ee1:
        mov eax,esi
    L_00456ee3:
        shl eax,2
    L_00456ee6:
        mov esi,dword ptr [eax+473C24h]
    L_00456eec:
        mov dword ptr [ebp+0Ch],eax
    L_00456eef:
        lea eax,[edi+12Bh]
    L_00456ef5:
        cdq
    L_00456ef6:
        lea ebx,[edi-1]
    L_00456ef9:
        mov edi,190h
    L_00456efe:
        idiv edi
    L_00456f00:
        push 64h
    L_00456f02:
        pop edi
    L_00456f03:
        inc esi
    L_00456f04:
        push 4
    L_00456f06:
        mov dword ptr [ebp-4],eax
    L_00456f09:
        mov eax,ebx
    L_00456f0b:
        cdq
    L_00456f0c:
        idiv edi
    L_00456f0e:
        mov edx,dword ptr [ebp-4]
    L_00456f11:
        pop edi
    L_00456f12:
        push 7
    L_00456f14:
        sub edx,eax
    L_00456f16:
        mov eax,dword ptr [ebp+10h]
    L_00456f19:
        dec eax
    L_00456f1a:
        mov ebx,edx
    L_00456f1c:
        cdq
    L_00456f1d:
        idiv edi
    L_00456f1f:
        mov edi,dword ptr [ebp+10h]
    L_00456f22:
        mov edx,edi
    L_00456f24:
        imul edx,16Dh
    L_00456f2a:
        add eax,esi
    L_00456f2c:
        add eax,ebx
    L_00456f2e:
        lea eax,[edx+eax-63DBh]
    L_00456f35:
        cdq
    L_00456f36:
        pop ebx
    L_00456f37:
        idiv ebx
    L_00456f39:
        mov eax,dword ptr [ebp+14h]
    L_00456f3c:
        imul eax,7
    L_00456f3f:
        sub eax,edx
    L_00456f41:
        add eax,dword ptr [ebp+18h]
    L_00456f44:
        cmp edx,dword ptr [ebp+18h]
    L_00456f47:
        jg short L_00456f4f
    L_00456f49:
        lea esi,[esi+eax-7]
    L_00456f4d:
        jmp short L_00456f51
    L_00456f4f:
        add esi,eax
    L_00456f51:
        cmp dword ptr [ebp+14h],5
    L_00456f55:
        jne short L_00456fcd
    L_00456f57:
        cmp dword ptr [ebp-8],0
    L_00456f5b:
        jne short L_00456f69
    L_00456f5d:
        mov eax,edi
    L_00456f5f:
        push 64h
    L_00456f61:
        cdq
    L_00456f62:
        pop ebx
    L_00456f63:
        idiv ebx
    L_00456f65:
        test edx,edx
    L_00456f67:
        jne short L_00456f86
    L_00456f69:
        lea eax,[edi+76Ch]
    L_00456f6f:
        cdq
    L_00456f70:
        mov ebx,190h
    L_00456f75:
        idiv ebx
    L_00456f77:
        test edx,edx
    L_00456f79:
        je short L_00456f86
    L_00456f7b:
        mov eax,dword ptr [ebp+0Ch]
    L_00456f7e:
        mov eax,dword ptr [eax+473C5Ch]
    L_00456f84:
        jmp short L_00456f8f
    L_00456f86:
        mov eax,dword ptr [ebp+0Ch]
    L_00456f89:
        mov eax,dword ptr [eax+473C28h]
    L_00456f8f:
        cmp esi,eax
    L_00456f91:
        jle short L_00456fcd
    L_00456f93:
        sub esi,7
    L_00456f96:
        jmp short L_00456fcd
    L_00456f98:
        test edx,edx
    L_00456f9a:
        jne short L_00456fa8
    L_00456f9c:
        mov eax,edi
    L_00456f9e:
        push 64h
    L_00456fa0:
        cdq
    L_00456fa1:
        pop ebx
    L_00456fa2:
        idiv ebx
    L_00456fa4:
        test edx,edx
    L_00456fa6:
        jne short L_00456fc3
    L_00456fa8:
        lea eax,[edi+76Ch]
    L_00456fae:
        cdq
    L_00456faf:
        mov ebx,190h
    L_00456fb4:
        idiv ebx
    L_00456fb6:
        test edx,edx
    L_00456fb8:
        je short L_00456fc3
    L_00456fba:
        mov esi,dword ptr [esi*4+473C58h]
    L_00456fc1:
        jmp short L_00456fca
    L_00456fc3:
        mov esi,dword ptr [esi*4+473C24h]
    L_00456fca:
        add esi,dword ptr [ebp+1Ch]
    L_00456fcd:
        imul ecx,3Ch
    L_00456fd0:
        add ecx,dword ptr [ebp+20h]
    L_00456fd3:
        imul ecx,3Ch
    L_00456fd6:
        cmp dword ptr [ebp+8],1
    L_00456fda:
        jne short L_00456ffc
    L_00456fdc:
        add ecx,dword ptr [ebp+24h]
    L_00456fdf:
        mov dword ptr [data_004735bc],esi
    L_00456fe5:
        imul ecx,3E8h
    L_00456feb:
        add ecx,dword ptr [ebp+28h]
    L_00456fee:
        mov dword ptr [data_004735b8],edi
    L_00456ff4:
        mov dword ptr [data_004735c0],ecx
    L_00456ffa:
        jmp short L_00457043
    L_00456ffc:
        add ecx,dword ptr [data_00473528]
    L_00457002:
        mov dword ptr [data_004735c8],esi
    L_00457008:
        add ecx,dword ptr [ebp+24h]
    L_0045700b:
        imul ecx,3E8h
    L_00457011:
        add ecx,dword ptr [ebp+28h]
    L_00457014:
        mov dword ptr [data_004735cc],ecx
    L_0045701a:
        jns short L_00457025
    L_0045701c:
        add ecx,5265C00h
    L_00457022:
        dec esi
    L_00457023:
        jmp short L_00457031
    L_00457025:
        mov eax,5265C00h
    L_0045702a:
        cmp ecx,eax
    L_0045702c:
        jl short L_0045703d
    L_0045702e:
        sub ecx,eax
    L_00457030:
        inc esi
    L_00457031:
        mov dword ptr [data_004735cc],ecx
    L_00457037:
        mov dword ptr [data_004735c8],esi
    L_0045703d:
        mov dword ptr [data_004735c4],edi
    L_00457043:
        pop edi
    L_00457044:
        pop esi
    L_00457045:
        pop ebx
    L_00457046:
        leave
    L_00457047:
        ret
    }
}
