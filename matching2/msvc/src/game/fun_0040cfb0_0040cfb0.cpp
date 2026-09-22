#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040CFB0..0x0040D1A4: FUN_0040cfb0
// BLOCKED: closest_byte_count=0/501, first_diff=0x0040CFB0,
// residual_class=schema2_hidden_EAX_receiver_with_private_ESI_helper_and_large_object_layout,
// variants_tested=Ghidra_boundary_callers_callees_xrefs_dataflow_legacy_semantic_audit,
// next_lever=compile_schema2_with_real_004018190_and_0040E770_caller_contexts
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040cfb0_0040cfb0() {
    __asm {
    L_0040cfb0:
        push ebx
    L_0040cfb1:
        push ebp
    L_0040cfb2:
        push esi
    L_0040cfb3:
        push edi
    L_0040cfb4:
        push 2518h
    L_0040cfb9:
        mov ebx,eax
    L_0040cfbb:
        call asm_operator_new_00452493
    L_0040cfc0:
        add esp,4
    L_0040cfc3:
        test eax,eax
    L_0040cfc5:
        je short L_0040cfd7
    L_0040cfc7:
        mov ecx,dword ptr [esp+18h]
    L_0040cfcb:
        push ecx
    L_0040cfcc:
        mov esi,eax
    L_0040cfce:
        call asm_FUN_0040d830_0040d830
    L_0040cfd3:
        mov ebp,eax
    L_0040cfd5:
        jmp short L_0040cfd9
    L_0040cfd7:
        xor ebp,ebp
    L_0040cfd9:
        mov eax,ebx
    L_0040cfdb:
        mov ecx,dword ptr [eax]
    L_0040cfdd:
        lea edx,[ebp+1094h]
    L_0040cfe3:
        mov dword ptr [edx],ecx
    L_0040cfe5:
        mov ecx,dword ptr [eax+4]
    L_0040cfe8:
        mov dword ptr [edx+4],ecx
    L_0040cfeb:
        mov eax,dword ptr [eax+8]
    L_0040cfee:
        mov dword ptr [edx+8],eax
    L_0040cff1:
        mov ecx,dword ptr [ebx+0Ch]
    L_0040cff4:
        mov dword ptr [ebp+23F8h],ecx
    L_0040cffa:
        mov edx,dword ptr [ebx+14h]
    L_0040cffd:
        mov dword ptr [ebp+23FCh],edx
    L_0040d003:
        mov eax,dword ptr [ebx+10h]
    L_0040d006:
        mov edx,dword ptr [ebp+2480h]
    L_0040d00c:
        mov dword ptr [ebp+2408h],eax
    L_0040d012:
        mov ecx,dword ptr [ebx+18h]
    L_0040d015:
        shl ecx,0Bh
    L_0040d018:
        xor ecx,edx
    L_0040d01a:
        and ecx,800h
    L_0040d020:
        mov edi,edx
    L_0040d022:
        xor edi,ecx
    L_0040d024:
        mov dword ptr [ebp+2480h],edi
    L_0040d02a:
        mov ecx,dword ptr [data_00474c74]
    L_0040d030:
        mov dl,1
    L_0040d032:
        shl dl,cl
    L_0040d034:
        lea esi,[ebx+20h]
    L_0040d037:
        lea edi,[ebp+1138h]
    L_0040d03d:
        mov ecx,8
    L_0040d042:
        mov byte ptr [ebp+1024h],dl
    L_0040d048:
        rep movsd
    L_0040d04a:
        mov eax,dword ptr [ebp+2468h]
    L_0040d050:
        xor edi,edi
    L_0040d052:
        test al,1
    L_0040d054:
        jne short L_0040d07f
    L_0040d056:
        or eax,1
    L_0040d059:
        mov dword ptr [ebp+245Ch],edi
    L_0040d05f:
        mov dword ptr [ebp+2458h],0FFF0BDC1h
    L_0040d069:
        mov dword ptr [ebp+2460h],edi
    L_0040d06f:
        mov dword ptr [ebp+2464h],476F78h
    L_0040d079:
        mov dword ptr [ebp+2468h],eax
    L_0040d07f:
        mov dword ptr [ebp+245Ch],2
    L_0040d089:
        mov dword ptr [ebp+2460h],40000000h
    L_0040d093:
        mov esi,1
    L_0040d098:
        mov dword ptr [ebp+2458h],esi
    L_0040d09e:
        mov eax,dword ptr [ebx+1Ch]
    L_0040d0a1:
        mov edx,dword ptr [ebp+2480h]
    L_0040d0a7:
        shl eax,12h
    L_0040d0aa:
        xor eax,edx
    L_0040d0ac:
        and eax,40000h
    L_0040d0b1:
        mov ebx,edx
    L_0040d0b3:
        lea ecx,[ebp+103Ch]
    L_0040d0b9:
        xor ebx,eax
    L_0040d0bb:
        push ecx
    L_0040d0bc:
        mov dword ptr [ebp+2480h],ebx
    L_0040d0c2:
        call asm_FUN_0040dc80_0040dc80
    L_0040d0c7:
        mov eax,dword ptr [ebp+2480h]
    L_0040d0cd:
        test ah,ah
    L_0040d0cf:
        jns short L_0040d0f2
    L_0040d0d1:
        mov eax,dword ptr [ebp+2408h]
    L_0040d0d7:
        cmp eax,esi
    L_0040d0d9:
        jne short L_0040d0e2
    L_0040d0db:
        mov eax,0Ah
    L_0040d0e0:
        jmp short L_0040d0ec
    L_0040d0e2:
        cmp eax,4
    L_0040d0e5:
        jne short L_0040d0ec
    L_0040d0e7:
        mov eax,0Bh
    L_0040d0ec:
        mov dword ptr [ebp+2408h],eax
    L_0040d0f2:
        mov eax,dword ptr [esp+14h]
    L_0040d0f6:
        mov edx,dword ptr [eax+64h]
    L_0040d0f9:
        mov ecx,dword ptr [ebp+1128h]
    L_0040d0ff:
        and edx,esi
    L_0040d101:
        add edx,2
    L_0040d104:
        cmp ecx,esi
    L_0040d106:
        mov dword ptr [ebp+2444h],edx
    L_0040d10c:
        mov edx,167h
    L_0040d111:
        mov dword ptr [ebp+2448h],edx
    L_0040d117:
        jne short L_0040d15c
    L_0040d119:
        mov ecx,dword ptr [ebp+112Ch]
    L_0040d11f:
        cmp ecx,34h
    L_0040d122:
        ja short L_0040d15c
    L_0040d124:
        movzx ecx,byte ptr [ecx+40D1BCh]
    L_0040d12b:
        jmp dword ptr [ecx*4+40D1A8h]
    L_0040d132:
        mov dword ptr [ebp+2448h],edx
    L_0040d138:
        jmp short L_0040d15c
    L_0040d13a:
        mov dword ptr [ebp+2448h],164h
    L_0040d144:
        jmp short L_0040d15c
    L_0040d146:
        mov dword ptr [ebp+2448h],16Dh
    L_0040d150:
        jmp short L_0040d15c
    L_0040d152:
        mov dword ptr [ebp+2448h],16Ah
    L_0040d15c:
        mov dword ptr [ebp+244Ch],edi
    L_0040d162:
        cmp dword ptr [eax+58h],edi
    L_0040d165:
        lea ecx,[ebp+116Ch]
    L_0040d16b:
        jne short L_0040d172
    L_0040d16d:
        mov dword ptr [eax+58h],ecx
    L_0040d170:
        jmp short L_0040d18b
    L_0040d172:
        mov edx,dword ptr [eax+5Ch]
    L_0040d175:
        mov esi,dword ptr [edx+4]
    L_0040d178:
        cmp esi,edi
    L_0040d17a:
        je short L_0040d185
    L_0040d17c:
        mov dword ptr [ecx+4],esi
    L_0040d17f:
        mov esi,dword ptr [edx+4]
    L_0040d182:
        mov dword ptr [esi+8],ecx
    L_0040d185:
        mov dword ptr [edx+4],ecx
    L_0040d188:
        mov dword ptr [ecx+8],edx
    L_0040d18b:
        mov edx,dword ptr [eax+60h]
    L_0040d18e:
        mov dword ptr [eax+5Ch],ecx
    L_0040d191:
        mov ecx,dword ptr [eax+64h]
    L_0040d194:
        inc edx
    L_0040d195:
        pop edi
    L_0040d196:
        inc ecx
    L_0040d197:
        pop esi
    L_0040d198:
        mov dword ptr [eax+60h],edx
    L_0040d19b:
        mov dword ptr [eax+64h],ecx
    L_0040d19e:
        mov eax,ebp
    L_0040d1a0:
        pop ebp
    L_0040d1a1:
        pop ebx
    L_0040d1a2:
        ret 8
    }
}
