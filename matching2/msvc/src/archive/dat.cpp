#include "asm_encoding.hpp"
#include "asm_symbols.hpp"








// 0x004350D0..0x00435216: FUN_004350d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004350d0_004350d0() {
    __asm {
    L_004350d0:
        push 0FFFFFFFFh
    L_004350d2:
        push 4653CBh
    L_004350d7:
        mov eax,dword ptr fs:[0]
    L_004350dd:
        push eax
    L_004350de:
        mov dword ptr fs:[0],esp
    L_004350e5:
        sub esp,8
    L_004350e8:
        push ebp
    L_004350e9:
        mov ebp,dword ptr [esp+20h]
    L_004350ed:
        push esi
    L_004350ee:
        lea esi,[ebp+1]
    L_004350f1:
        mov eax,esi
    L_004350f3:
        shl eax,4
    L_004350f6:
        add eax,4
    L_004350f9:
        push edi
    L_004350fa:
        push eax
    L_004350fb:
        call asm_operator_new_00452493
    L_00435100:
        add esp,4
    L_00435103:
        mov dword ptr [esp+10h],eax
    L_00435107:
        test eax,eax
    L_00435109:
        mov dword ptr [esp+1Ch],0
    L_00435111:
        je short L_00435133
    L_00435113:
        push 435250h
    L_00435118:
        push 4352C0h
    L_0043511d:
        push esi
    L_0043511e:
        lea edi,[eax+4]
    L_00435121:
        push 10h
    L_00435123:
        push edi
    L_00435124:
        mov dword ptr [eax],esi
    L_00435126:
        mov dword ptr [esp+20h],edi
    L_0043512a:
        call asm_eh_vector_constructor_iterator_0045252d
    L_0043512f:
        test edi,edi
    L_00435131:
        jne short L_00435149
    L_00435133:
        pop edi
    L_00435134:
        pop esi
    L_00435135:
        xor eax,eax
    L_00435137:
        pop ebp
    L_00435138:
        mov ecx,dword ptr [esp+8]
    L_0043513c:
        mov dword ptr fs:[0],ecx
    L_00435143:
        add esp,14h
    L_00435146:
        ret 0Ch
    L_00435149:
        test ebp,ebp
    L_0043514b:
        mov esi,dword ptr [esp+24h]
    L_0043514f:
        jle asm_target_004351ed
    L_00435155:
        mov ecx,dword ptr [esp+28h]
    L_00435159:
        lea ebp,[edi+8]
    L_0043515c:
        mov dword ptr [esp+24h],ecx
    L_00435160:
        mov eax,esi
    L_00435162:
        lea edx,[eax+1]
    L_00435165:
        mov cl,byte ptr [eax]
    L_00435167:
        inc eax
    L_00435168:
        test cl,cl
    L_0043516a:
        jne short L_00435165
    L_0043516c:
        sub eax,edx
    L_0043516e:
        inc eax
    L_0043516f:
        push eax
    L_00435170:
        call asm_malloc_00452706
    L_00435175:
        add esp,4
    L_00435178:
        test eax,eax
    L_0043517a:
        je short L_00435190
    L_0043517c:
        mov edi,eax
    L_0043517e:
        mov ecx,esi
    L_00435180:
        sub edi,esi
    L_00435182:
        mov dl,byte ptr [ecx]
    L_00435184:
        mov byte ptr [edi+ecx],dl
    L_00435187:
        inc ecx
    L_00435188:
        test dl,dl
    L_0043518a:
        jne short L_00435182
    L_0043518c:
        mov edi,dword ptr [esp+0Ch]
    L_00435190:
        mov dword ptr [ebp-8],eax
    L_00435193:
        mov eax,esi
    L_00435195:
        lea edx,[eax+1]
    L_00435198:
        mov cl,byte ptr [eax]
    L_0043519a:
        inc eax
    L_0043519b:
        test cl,cl
    L_0043519d:
        jne short L_00435198
    L_0043519f:
        sub eax,edx
    L_004351a1:
        inc eax
    L_004351a2:
        mov ecx,eax
    L_004351a4:
        and ecx,80000003h
    L_004351aa:
        jns short L_004351b1
    L_004351ac:
        dec ecx
    L_004351ad:
        or ecx,0FFFFFFFCh
    L_004351b0:
        inc ecx
    L_004351b1:
        je short L_004351bc
    L_004351b3:
        mov edx,4
    L_004351b8:
        sub edx,ecx
    L_004351ba:
        add eax,edx
    L_004351bc:
        add esi,eax
    L_004351be:
        mov eax,dword ptr [esi]
    L_004351c0:
        mov dword ptr [ebp-4],eax
    L_004351c3:
        mov ecx,dword ptr [esi+4]
    L_004351c6:
        mov eax,dword ptr [esp+24h]
    L_004351ca:
        add esi,4
    L_004351cd:
        add esi,4
    L_004351d0:
        mov dword ptr [ebp],ecx
    L_004351d3:
        mov edx,dword ptr [esi]
    L_004351d5:
        mov dword ptr [ebp+4],edx
    L_004351d8:
        add esi,4
    L_004351db:
        add ebp,10h
    L_004351de:
        dec eax
    L_004351df:
        mov dword ptr [esp+24h],eax
    L_004351e3:
        jne asm_target_00435160
    L_004351e9:
        mov ebp,dword ptr [esp+28h]
    L_004351ed:
        mov ecx,dword ptr [esp+2Ch]
    L_004351f1:
        shl ebp,4
    L_004351f4:
        lea eax,[edi+ebp]
    L_004351f7:
        mov dword ptr [eax+4],ecx
    L_004351fa:
        mov ecx,dword ptr [esp+14h]
    L_004351fe:
        mov dword ptr [eax+8],0
    L_00435205:
        mov eax,edi
    L_00435207:
        pop edi
    L_00435208:
        pop esi
    L_00435209:
        pop ebp
    L_0043520a:
        mov dword ptr fs:[0],ecx
    L_00435211:
        add esp,14h
    L_00435214:
        ret 0Ch
    }
}
