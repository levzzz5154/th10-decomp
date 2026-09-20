// BLOCKED (H2701): closest_byte_count=325; first_diff=unmeasured;
// residual_class=abi/source_shape: the private EBX entry selects a surface
// slot, while the body uses stack-owned output/RECT temporaries, D3D vtable
// calls at offsets 0x48/0x70/0x90/0x78, and the D3DX surface-copy thunk;
// normal C++ surface declarations change the homes and COM call setup.
// variants_tested=exact retail naked wrapper, IDirect3DSurface-style semantic
// copy model, and explicit vtable-plus-stack-RECT model; no compiler-readable
// candidate was byte-measured.
// next_lever=co-compile this body with the real surface-owner caller and
// IL-visible D3D9 vtable bindings in a native-LTCG cluster that pins EBX.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00446D70..0x00446EAF: FUN_00446d70
// Naked body preserves the retail register/stack ABI.

// 0x00448120..0x00448264: FUN_00448120
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00448120_00448120() {
    __asm {
    L_00448120:
        sub esp,18h
    L_00448123:
        push ebp
    L_00448124:
        mov ebp,dword ptr [esp+20h]
    L_00448128:
        mov eax,dword ptr [ebp+ebx*4+3AD560h]
    L_0044812f:
        test eax,eax
    L_00448131:
        je asm_target_0044825e
    L_00448137:
        mov eax,dword ptr [data_00491c30]
    L_0044813c:
        mov ecx,dword ptr [eax]
    L_0044813e:
        lea edx,[esp+20h]
    L_00448142:
        push edx
    L_00448143:
        push 0
    L_00448145:
        push 0
    L_00448147:
        push 0
    L_00448149:
        push eax
    L_0044814a:
        call dword ptr [ecx+48h]
    L_0044814d:
        test eax,eax
    L_0044814f:
        jne asm_target_0044825e
    L_00448155:
        mov eax,dword ptr [ebp+ebx*4+3AD4E0h]
    L_0044815c:
        test eax,eax
    L_0044815e:
        push esi
    L_0044815f:
        lea esi,[ebp+ebx*4+3AD4E0h]
    L_00448166:
        push edi
    L_00448167:
        jne asm_target_00448201
    L_0044816d:
        mov eax,dword ptr [data_00491c30]
    L_00448172:
        mov edx,dword ptr [eax]
    L_00448174:
        push 0
    L_00448176:
        mov ecx,ebx
    L_00448178:
        imul ecx,1Ch
    L_0044817b:
        push esi
    L_0044817c:
        push 1
    L_0044817e:
        push 0
    L_00448180:
        lea edi,[ecx+ebp]
    L_00448183:
        mov ecx,dword ptr [data_00491d14]
    L_00448189:
        push 0
    L_0044818b:
        push ecx
    L_0044818c:
        mov ecx,dword ptr [edi+3AD6E4h]
    L_00448192:
        push ecx
    L_00448193:
        mov ecx,dword ptr [edi+3AD6E0h]
    L_00448199:
        push ecx
    L_0044819a:
        push eax
    L_0044819b:
        call dword ptr [edx+70h]
    L_0044819e:
        test eax,eax
    L_004481a0:
        je short L_004481ce
    L_004481a2:
        mov ecx,dword ptr [data_00491d14]
    L_004481a8:
        mov eax,dword ptr [data_00491c30]
    L_004481ad:
        mov edx,dword ptr [eax]
    L_004481af:
        push 0
    L_004481b1:
        push esi
    L_004481b2:
        push 3
    L_004481b4:
        push ecx
    L_004481b5:
        mov ecx,dword ptr [edi+3AD6E4h]
    L_004481bb:
        push ecx
    L_004481bc:
        mov ecx,dword ptr [edi+3AD6E0h]
    L_004481c2:
        push ecx
    L_004481c3:
        push eax
    L_004481c4:
        call dword ptr [edx+90h]
    L_004481ca:
        test eax,eax
    L_004481cc:
        jne short L_004481ee
    L_004481ce:
        mov eax,dword ptr [ebp+ebx*4+3AD560h]
    L_004481d5:
        mov ecx,dword ptr [esi]
    L_004481d7:
        push 0
    L_004481d9:
        push 1
    L_004481db:
        push 0
    L_004481dd:
        push 0
    L_004481df:
        push eax
    L_004481e0:
        push 0
    L_004481e2:
        push 0
    L_004481e4:
        push ecx
    L_004481e5:
        call asm_D3DXLoadSurfaceFromSurface_004521d6
    L_004481ea:
        test eax,eax
    L_004481ec:
        je short L_00448201
    L_004481ee:
        mov eax,dword ptr [esp+28h]
    L_004481f2:
        mov edx,dword ptr [eax]
    L_004481f4:
        push eax
    L_004481f5:
        call dword ptr [edx+8]
    L_004481f8:
        pop edi
    L_004481f9:
        pop esi
    L_004481fa:
        pop ebp
    L_004481fb:
        add esp,18h
    L_004481fe:
        ret 1Ch
    L_00448201:
        mov ecx,dword ptr [esp+34h]
    L_00448205:
        mov edx,dword ptr [esp+3Ch]
    L_00448209:
        mov eax,dword ptr [esp+38h]
    L_0044820d:
        mov dword ptr [esp+14h],ecx
    L_00448211:
        add ecx,edx
    L_00448213:
        mov edx,dword ptr [esp+2Ch]
    L_00448217:
        mov dword ptr [esp+0Ch],edx
    L_0044821b:
        lea edx,[esp+0Ch]
    L_0044821f:
        push edx
    L_00448220:
        mov edx,dword ptr [esp+2Ch]
    L_00448224:
        mov dword ptr [esp+1Ch],eax
    L_00448228:
        mov dword ptr [esp+20h],ecx
    L_0044822c:
        mov ecx,dword ptr [esp+44h]
    L_00448230:
        push edx
    L_00448231:
        add eax,ecx
    L_00448233:
        mov dword ptr [esp+28h],eax
    L_00448237:
        mov eax,dword ptr [esp+38h]
    L_0044823b:
        lea edx,[esp+1Ch]
    L_0044823f:
        push edx
    L_00448240:
        mov edx,dword ptr [esi]
    L_00448242:
        mov dword ptr [esp+1Ch],eax
    L_00448246:
        mov eax,dword ptr [data_00491c30]
    L_0044824b:
        mov ecx,dword ptr [eax]
    L_0044824d:
        push edx
    L_0044824e:
        push eax
    L_0044824f:
        call dword ptr [ecx+78h]
    L_00448252:
        mov eax,dword ptr [esp+28h]
    L_00448256:
        mov ecx,dword ptr [eax]
    L_00448258:
        push eax
    L_00448259:
        call dword ptr [ecx+8]
    L_0044825c:
        pop edi
    L_0044825d:
        pop esi
    L_0044825e:
        pop ebp
    L_0044825f:
        add esp,18h
    L_00448262:
        ret 1Ch
    }
}
