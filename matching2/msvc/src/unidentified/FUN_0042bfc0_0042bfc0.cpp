#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BFC0..0x0042C35D: FUN_0042bfc0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042bfc0_0042bfc0() {
    __asm {
    L_0042bfc0:
        sub esp,144h
    L_0042bfc6:
        mov eax,dword ptr [data_00473660]
    L_0042bfcb:
        xor eax,esp
    L_0042bfcd:
        push ebx
    L_0042bfce:
        push ebp
    L_0042bfcf:
        push esi
    L_0042bfd0:
        mov dword ptr [esp+14Ch],eax
    L_0042bfd7:
        mov esi,ecx
    L_0042bfd9:
        mov eax,dword ptr [esi+30h]
    L_0042bfdc:
        xor ebx,ebx
    L_0042bfde:
        sub eax,ebx
    L_0042bfe0:
        push edi
    L_0042bfe1:
        je asm_target_0042c1d6
    L_0042bfe7:
        dec eax
    L_0042bfe8:
        je short L_0042c036
    L_0042bfea:
        sub eax,3
    L_0042bfed:
        jne asm_target_0042c340
    L_0042bff3:
        mov edi,dword ptr [esi+2DCh]
    L_0042bff9:
        push 3F800000h
    L_0042bffe:
        call asm_EclVm_TickChildren_0044fd10
    L_0042c003:
        mov ecx,dword ptr [esi+2DCh]
    L_0042c009:
        cmp ecx,ebx
    L_0042c00b:
        je short L_0042c024
    L_0042c00d:
        mov eax,dword ptr [ecx+4]
    L_0042c010:
        cmp dword ptr [eax+4],ebx
    L_0042c013:
        jne asm_target_0042c340
    L_0042c019:
        cmp ecx,ebx
    L_0042c01b:
        je short L_0042c024
    L_0042c01d:
        mov edx,dword ptr [ecx]
    L_0042c01f:
        push 1
    L_0042c021:
        call dword ptr [edx+14h]
    L_0042c024:
        mov dword ptr [esi+2DCh],ebx
    L_0042c02a:
        mov dword ptr [esi+30h],1
    L_0042c031:
        jmp asm_target_0042c340
    L_0042c036:
        mov eax,dword ptr [esi+3Ch]
    L_0042c039:
        lea edi,[esi+3Ch]
    L_0042c03c:
        mov dword ptr [edi+4],eax
    L_0042c03f:
        mov cl,byte ptr [data_00474e36]
    L_0042c045:
        mov al,20h
    L_0042c047:
        test cl,al
    L_0042c049:
        jne short L_0042c053
    L_0042c04b:
        test byte ptr [data_00474e34],al
    L_0042c051:
        je short L_0042c05c
    L_0042c053:
        push 1
    L_0042c055:
        mov eax,edi
    L_0042c057:
        call asm_MenuCursor_Advance_0044bea0
    L_0042c05c:
        mov cl,byte ptr [data_00474e36]
    L_0042c062:
        mov al,10h
    L_0042c064:
        test cl,al
    L_0042c066:
        jne short L_0042c070
    L_0042c068:
        test byte ptr [data_00474e34],al
    L_0042c06e:
        je short L_0042c079
    L_0042c070:
        push 0FFFFFFFFh
    L_0042c072:
        mov eax,edi
    L_0042c074:
        call asm_MenuCursor_Advance_0044bea0
    L_0042c079:
        mov edi,dword ptr [edi]
    L_0042c07b:
        sub edi,ebx
    L_0042c07d:
        je asm_target_0042c154
    L_0042c083:
        dec edi
    L_0042c084:
        je short L_0042c0ae
    L_0042c086:
        dec edi
    L_0042c087:
        jne asm_target_0042c340
    L_0042c08d:
        test dword ptr [data_00474e36],1001h
    L_0042c097:
        je asm_target_0042c340
    L_0042c09d:
        push 3
    L_0042c09f:
        mov eax,491C28h
    L_0042c0a4:
        call asm_SetInputMode_0040ac90
    L_0042c0a9:
        jmp asm_target_0042c340
    L_0042c0ae:
        cmp dword ptr [esi+2D8h],ebx
    L_0042c0b4:
        je asm_target_0042c340
    L_0042c0ba:
        mov ecx,dword ptr [esi+1ECh]
    L_0042c0c0:
        lea ebp,[esi+1ECh]
    L_0042c0c6:
        mov dword ptr [ebp+4],ecx
    L_0042c0c9:
        mov eax,80h
    L_0042c0ce:
        mov ecx,474E30h
    L_0042c0d3:
        call asm_InputMaskActive_0040ace0
    L_0042c0d8:
        test ax,ax
    L_0042c0db:
        je short L_0042c0e6
    L_0042c0dd:
        push 1
    L_0042c0df:
        mov eax,ebp
    L_0042c0e1:
        call asm_MenuCursor_Advance_0044bea0
    L_0042c0e6:
        mov eax,40h
    L_0042c0eb:
        mov ecx,474E30h
    L_0042c0f0:
        call asm_InputMaskActive_0040ace0
    L_0042c0f5:
        test ax,ax
    L_0042c0f8:
        je short L_0042c103
    L_0042c0fa:
        push 0FFFFFFFFh
    L_0042c0fc:
        mov eax,ebp
    L_0042c0fe:
        call asm_MenuCursor_Advance_0044bea0
    L_0042c103:
        test dword ptr [data_00474e38],1001h
    L_0042c10d:
        je asm_target_0042c340
    L_0042c113:
        mov ecx,dword ptr [esi+2DCh]
    L_0042c119:
        cmp ecx,ebx
    L_0042c11b:
        je short L_0042c12a
    L_0042c11d:
        mov edx,dword ptr [ecx]
    L_0042c11f:
        push 1
    L_0042c121:
        call dword ptr [edx+14h]
    L_0042c124:
        mov dword ptr [esi+2DCh],ebx
    L_0042c12a:
        mov edi,dword ptr [esi+2D8h]
    L_0042c130:
        mov eax,dword ptr [ebp]
    L_0042c133:
        mov ecx,dword ptr [edi+8Ch]
    L_0042c139:
        mov eax,dword ptr [ecx+eax*8]
    L_0042c13c:
        push eax
    L_0042c13d:
        call asm_FUN_00450500_00450500
    L_0042c142:
        mov dword ptr [esi+2DCh],eax
    L_0042c148:
        mov dword ptr [esi+30h],4
    L_0042c14f:
        jmp asm_target_0042c340
    L_0042c154:
        mov edx,dword ptr [esi+114h]
    L_0042c15a:
        lea edi,[esi+114h]
    L_0042c160:
        mov dword ptr [edi+4],edx
    L_0042c163:
        mov cl,byte ptr [data_00474e36]
    L_0042c169:
        mov al,80h
    L_0042c16b:
        test cl,al
    L_0042c16d:
        jne short L_0042c177
    L_0042c16f:
        test byte ptr [data_00474e34],al
    L_0042c175:
        je short L_0042c180
    L_0042c177:
        push 1
    L_0042c179:
        mov eax,edi
    L_0042c17b:
        call asm_MenuCursor_Advance_0044bea0
    L_0042c180:
        mov cl,byte ptr [data_00474e36]
    L_0042c186:
        mov al,40h
    L_0042c188:
        test cl,al
    L_0042c18a:
        jne short L_0042c194
    L_0042c18c:
        test byte ptr [data_00474e34],al
    L_0042c192:
        je short L_0042c19d
    L_0042c194:
        push 0FFFFFFFFh
    L_0042c196:
        mov eax,edi
    L_0042c198:
        call asm_MenuCursor_Advance_0044bea0
    L_0042c19d:
        test dword ptr [data_00474e36],1001h
    L_0042c1a7:
        je asm_target_0042c340
    L_0042c1ad:
        mov ecx,dword ptr [esi+2D4h]
    L_0042c1b3:
        and ecx,0FFFFFFFDh
    L_0042c1b6:
        push esi
    L_0042c1b7:
        lea eax,[esi+10h]
    L_0042c1ba:
        mov edi,42BE10h
    L_0042c1bf:
        mov dword ptr [esi+2D4h],ecx
    L_0042c1c5:
        call asm_FUN_0044c1c0_0044c1c0
    L_0042c1ca:
        mov dword ptr [esi+30h],2
    L_0042c1d1:
        jmp asm_target_0042c340
    L_0042c1d6:
        call asm_FUN_0042bad0_0042bad0
    L_0042c1db:
        mov ebx,dword ptr [data_004660a0]
    L_0042c1e1:
        lea eax,[esp+10h]
    L_0042c1e5:
        push eax
    L_0042c1e6:
        push 46CEA8h
    L_0042c1eb:
        xor ebp,ebp
    L_0042c1ed:
        call ebx
    L_0042c1ef:
        mov edi,eax
    L_0042c1f1:
        cmp edi,0FFFFFFFFh
    L_0042c1f4:
        je short L_0042c207
    L_0042c1f6:
        lea ecx,[esp+10h]
    L_0042c1fa:
        push ecx
    L_0042c1fb:
        push edi
    L_0042c1fc:
        inc ebp
    L_0042c1fd:
        call dword ptr [data_004660a4]
    L_0042c203:
        test eax,eax
    L_0042c205:
        jne short L_0042c1f6
    L_0042c207:
        push edi
    L_0042c208:
        call dword ptr [data_004660a8]
    L_0042c20e:
        xor edi,edi
    L_0042c210:
        cmp ebp,edi
    L_0042c212:
        mov dword ptr [esi+38h],ebp
    L_0042c215:
        je asm_target_0042c298
    L_0042c21b:
        lea edx,[ebp*4]
    L_0042c222:
        push edx
    L_0042c223:
        call asm_malloc_00452706
    L_0042c228:
        add esp,4
    L_0042c22b:
        mov dword ptr [esi+34h],eax
    L_0042c22e:
        lea eax,[esp+10h]
    L_0042c232:
        push eax
    L_0042c233:
        push 46CEA8h
    L_0042c238:
        call ebx
    L_0042c23a:
        test ebp,ebp
    L_0042c23c:
        mov ebx,eax
    L_0042c23e:
        jle short L_0042c28f
    L_0042c240:
        lea eax,[esp+3Ch]
    L_0042c244:
        lea edx,[eax+1]
    L_0042c247:
        mov cl,byte ptr [eax]
    L_0042c249:
        inc eax
    L_0042c24a:
        test cl,cl
    L_0042c24c:
        jne short L_0042c247
    L_0042c24e:
        sub eax,edx
    L_0042c250:
        inc eax
    L_0042c251:
        push eax
    L_0042c252:
        call asm_malloc_00452706
    L_0042c257:
        mov ecx,dword ptr [esi+34h]
    L_0042c25a:
        mov dword ptr [ecx+edi*4],eax
    L_0042c25d:
        mov edx,dword ptr [esi+34h]
    L_0042c260:
        mov edx,dword ptr [edx+edi*4]
    L_0042c263:
        add esp,4
    L_0042c266:
        lea ecx,[esp+3Ch]
    L_0042c26a:
        lea ebx,[ebx+force_disp32_zero]
    L_0042c270:
        mov al,byte ptr [ecx]
    L_0042c272:
        inc ecx
    L_0042c273:
        mov byte ptr [edx],al
    L_0042c275:
        inc edx
    L_0042c276:
        test al,al
    L_0042c278:
        jne short L_0042c270
    L_0042c27a:
        lea eax,[esp+10h]
    L_0042c27e:
        push eax
    L_0042c27f:
        push ebx
    L_0042c280:
        call dword ptr [data_004660a4]
    L_0042c286:
        test eax,eax
    L_0042c288:
        je short L_0042c28f
    L_0042c28a:
        inc edi
    L_0042c28b:
        cmp edi,ebp
    L_0042c28d:
        jl short L_0042c240
    L_0042c28f:
        push ebx
    L_0042c290:
        call dword ptr [data_004660a8]
    L_0042c296:
        xor edi,edi
    L_0042c298:
        mov ecx,1
    L_0042c29d:
        mov dword ptr [esi+44h],3
    L_0042c2a4:
        mov dword ptr [esi+10Ch],ecx
    L_0042c2aa:
        mov eax,dword ptr [esi+44h]
    L_0042c2ad:
        cmp eax,edi
    L_0042c2af:
        je short L_0042c2c0
    L_0042c2b1:
        jg short L_0042c2b9
    L_0042c2b3:
        dec eax
    L_0042c2b4:
        mov dword ptr [esi+3Ch],eax
    L_0042c2b7:
        jmp short L_0042c2c3
    L_0042c2b9:
        xor eax,eax
    L_0042c2bb:
        mov dword ptr [esi+3Ch],eax
    L_0042c2be:
        jmp short L_0042c2c3
    L_0042c2c0:
        mov dword ptr [esi+3Ch],edi
    L_0042c2c3:
        mov eax,ebp
    L_0042c2c5:
        cmp eax,edi
    L_0042c2c7:
        mov dword ptr [esi+11Ch],ebp
    L_0042c2cd:
        mov dword ptr [esi+1E4h],ecx
    L_0042c2d3:
        je short L_0042c2ea
    L_0042c2d5:
        jg short L_0042c2e0
    L_0042c2d7:
        dec eax
    L_0042c2d8:
        mov dword ptr [esi+114h],eax
    L_0042c2de:
        jmp short L_0042c2f0
    L_0042c2e0:
        xor eax,eax
    L_0042c2e2:
        mov dword ptr [esi+114h],eax
    L_0042c2e8:
        jmp short L_0042c2f0
    L_0042c2ea:
        mov dword ptr [esi+114h],edi
    L_0042c2f0:
        mov eax,ecx
    L_0042c2f2:
        cmp eax,edi
    L_0042c2f4:
        mov dword ptr [esi+1F4h],ecx
    L_0042c2fa:
        mov dword ptr [esi+2BCh],ecx
    L_0042c300:
        je short L_0042c317
    L_0042c302:
        jg short L_0042c30d
    L_0042c304:
        dec eax
    L_0042c305:
        mov dword ptr [esi+1ECh],eax
    L_0042c30b:
        jmp short L_0042c31d
    L_0042c30d:
        xor eax,eax
    L_0042c30f:
        mov dword ptr [esi+1ECh],eax
    L_0042c315:
        jmp short L_0042c31d
    L_0042c317:
        mov dword ptr [esi+1ECh],edi
    L_0042c31d:
        mov dword ptr [esi+30h],ecx
    L_0042c320:
        mov dword ptr [esi+2C4h],edi
    L_0042c326:
        mov dword ptr [esi+2C8h],42000000h
    L_0042c330:
        mov dword ptr [esi+2CCh],edi
    L_0042c336:
        mov dword ptr [esi+2D0h],3E8h
    L_0042c340:
        mov ecx,dword ptr [esp+150h]
    L_0042c347:
        pop edi
    L_0042c348:
        pop esi
    L_0042c349:
        pop ebp
    L_0042c34a:
        pop ebx
    L_0042c34b:
        xor ecx,esp
    L_0042c34d:
        mov eax,1
    L_0042c352:
        call asm_security_check_cookie_00458ea5
    L_0042c357:
        add esp,144h
    L_0042c35d:
        ret
    }
}
