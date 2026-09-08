#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446C70..0x00446D62: FUN_00446c70
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00446c70_00446c70() {
    __asm {
    L_00446c70:
        sub esp,18h
    L_00446c73:
        test byte ptr [data_00491d78],1
    L_00446c7a:
        mov dword ptr [esp+4],eax
    L_00446c7e:
        je short L_00446ca7
    L_00446c80:
        mov eax,dword ptr [eax*4+46F288h]
    L_00446c87:
        cmp eax,15h
    L_00446c8a:
        je short L_00446c9f
    L_00446c8c:
        test eax,eax
    L_00446c8e:
        je short L_00446c9f
    L_00446c90:
        cmp eax,14h
    L_00446c93:
        jne short L_00446ca7
    L_00446c95:
        mov dword ptr [esp+4],3
    L_00446c9d:
        jmp short L_00446ca7
    L_00446c9f:
        mov dword ptr [esp+4],5
    L_00446ca7:
        mov eax,dword ptr [edi]
    L_00446ca9:
        lea edx,[esp]
    L_00446cac:
        push edx
    L_00446cad:
        push 0
    L_00446caf:
        mov dword ptr [edi+8],ebx
    L_00446cb2:
        mov dword ptr [esp+8],0
    L_00446cba:
        mov ecx,dword ptr [eax]
    L_00446cbc:
        push eax
    L_00446cbd:
        call dword ptr [ecx+48h]
    L_00446cc0:
        mov eax,dword ptr [esp+20h]
    L_00446cc4:
        test eax,eax
    L_00446cc6:
        push 0
    L_00446cc8:
        jne short L_00446ce2
    L_00446cca:
        mov eax,dword ptr [esp+4]
    L_00446cce:
        push 0
    L_00446cd0:
        push 1
    L_00446cd2:
        push 0
    L_00446cd4:
        push ebx
    L_00446cd5:
        push esi
    L_00446cd6:
        push 0
    L_00446cd8:
        push 0
    L_00446cda:
        push eax
    L_00446cdb:
        call asm_D3DXLoadSurfaceFromFileInMemory_004521d0
    L_00446ce0:
        jmp short L_00446d3d
    L_00446ce2:
        mov ecx,dword ptr [esi+30h]
    L_00446ce5:
        lea eax,[ecx+esi]
    L_00446ce8:
        mov dword ptr [esp+0Ch],0
    L_00446cf0:
        mov dword ptr [esp+10h],0
    L_00446cf8:
        movsx edx,word ptr [eax+8]
    L_00446cfc:
        mov dword ptr [esp+14h],edx
    L_00446d00:
        movsx ecx,word ptr [eax+0Ah]
    L_00446d04:
        push 1
    L_00446d06:
        mov dword ptr [esp+1Ch],ecx
    L_00446d0a:
        movsx ecx,word ptr [eax+6]
    L_00446d0e:
        lea edx,[esp+10h]
    L_00446d12:
        push edx
    L_00446d13:
        movsx edx,word ptr [eax+8]
    L_00446d17:
        shl ecx,2
    L_00446d1a:
        imul edx,dword ptr [ecx+46F2A0h]
    L_00446d21:
        mov ecx,dword ptr [ecx+46F288h]
    L_00446d27:
        push 0
    L_00446d29:
        push edx
    L_00446d2a:
        mov edx,dword ptr [esp+14h]
    L_00446d2e:
        push ecx
    L_00446d2f:
        add eax,10h
    L_00446d32:
        push eax
    L_00446d33:
        push 0
    L_00446d35:
        push 0
    L_00446d37:
        push edx
    L_00446d38:
        call asm_D3DXLoadSurfaceFromMemory_004521a6
    L_00446d3d:
        mov eax,dword ptr [esp]
    L_00446d40:
        mov ecx,dword ptr [eax]
    L_00446d42:
        push eax
    L_00446d43:
        call dword ptr [ecx+8]
    L_00446d46:
        mov eax,edi
    L_00446d48:
        call asm_FUN_004465b0_004465b0
    L_00446d4d:
        mov edx,dword ptr [esp+4]
    L_00446d51:
        mov eax,dword ptr [edx*4+46F2A0h]
    L_00446d58:
        mov dword ptr [edi+0Ch],eax
    L_00446d5b:
        xor eax,eax
    L_00446d5d:
        add esp,18h
    L_00446d60:
        ret 8
    }
}

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

// 0x004473C0..0x0044746D: AnmArchive_AdvanceScriptCursorRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnmArchive_AdvanceScriptCursorRetail_004473c0() {
    __asm {
    L_004473c0:
        push ecx
    L_004473c1:
        push ebx
    L_004473c2:
        push ebp
    L_004473c3:
        mov ebp,dword ptr [esp+14h]
    L_004473c7:
        push esi
    L_004473c8:
        mov esi,dword ptr [ebp+108h]
    L_004473ce:
        xor edx,edx
    L_004473d0:
        xor ecx,ecx
    L_004473d2:
        push edi
    L_004473d3:
        xor ebx,ebx
    L_004473d5:
        mov dword ptr [esp+10h],ecx
    L_004473d9:
        xor edi,edi
    L_004473db:
        mov dword ptr [esp+1Ch],edx
    L_004473df:
        nop
    L_004473e0:
        mov eax,dword ptr [ebp+124h]
    L_004473e6:
        dec eax
    L_004473e7:
        cmp ecx,eax
    L_004473e9:
        jne short L_0044740a
    L_004473eb:
        mov ecx,dword ptr [esp+18h]
    L_004473ef:
        mov eax,dword ptr [esp+1Ch]
    L_004473f3:
        push esi
    L_004473f4:
        push ebx
    L_004473f5:
        push edi
    L_004473f6:
        push ebp
    L_004473f7:
        push ecx
    L_004473f8:
        call asm_FUN_00447470_00447470
    L_004473fd:
        test eax,eax
    L_004473ff:
        jl short L_00447446
    L_00447401:
        mov ecx,dword ptr [esp+10h]
    L_00447405:
        mov edx,1
    L_0044740a:
        add edi,dword ptr [esi]
    L_0044740c:
        add ebx,dword ptr [esi+4]
    L_0044740f:
        inc dword ptr [esp+1Ch]
    L_00447413:
        mov eax,dword ptr [esi+38h]
    L_00447416:
        test eax,eax
    L_00447418:
        je short L_0044745a
    L_0044741a:
        add esi,eax
    L_0044741c:
        mov eax,dword ptr [ebp+124h]
    L_00447422:
        inc ecx
    L_00447423:
        cmp ecx,eax
    L_00447425:
        mov dword ptr [esp+10h],ecx
    L_00447429:
        je short L_0044742f
    L_0044742b:
        test edx,edx
    L_0044742d:
        je short L_004473e0
    L_0044742f:
        mov eax,dword ptr [ebp+124h]
    L_00447435:
        pop edi
    L_00447436:
        inc eax
    L_00447437:
        mov dword ptr [ebp+124h],eax
    L_0044743d:
        pop esi
    L_0044743e:
        mov eax,ebp
    L_00447440:
        pop ebp
    L_00447441:
        pop ebx
    L_00447442:
        pop ecx
    L_00447443:
        ret 8
    L_00447446:
        pop edi
    L_00447447:
        pop esi
    L_00447448:
        mov dword ptr [ebp+124h],0
    L_00447452:
        pop ebp
    L_00447453:
        xor eax,eax
    L_00447455:
        pop ebx
    L_00447456:
        pop ecx
    L_00447457:
        ret 8
    L_0044745a:
        pop edi
    L_0044745b:
        pop esi
    L_0044745c:
        mov dword ptr [ebp+124h],0
    L_00447466:
        mov eax,ebp
    L_00447468:
        pop ebp
    L_00447469:
        pop ebx
    L_0044746a:
        pop ecx
    L_0044746b:
        ret 8
    }
}
