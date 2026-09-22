#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00417040..0x004172DE: FUN_00417040
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00417040_00417040() {
    __asm {
    L_00417040:
        mov ecx,dword ptr [esi+9E78h]
    L_00417046:
        sub esp,0Ch
    L_00417049:
        push ebx
    L_0041704a:
        push ebp
    L_0041704b:
        push edi
    L_0041704c:
        mov edi,dword ptr [data_00474c44]
    L_00417052:
        cmp edi,ecx
    L_00417054:
        mov ebp,5F5E100h
    L_00417059:
        je asm_target_004170f4
    L_0041705f:
        mov eax,edi
    L_00417061:
        sub eax,ecx
    L_00417063:
        cdq
    L_00417064:
        and edx,1Fh
    L_00417067:
        add eax,edx
    L_00417069:
        sar eax,5
    L_0041706c:
        cmp eax,8D55Eh
    L_00417071:
        mov ebx,ecx
    L_00417073:
        jl short L_0041707c
    L_00417075:
        mov eax,8D55Eh
    L_0041707a:
        jmp short L_00417085
    L_0041707c:
        test eax,eax
    L_0041707e:
        jne short L_00417085
    L_00417080:
        mov eax,1
    L_00417085:
        cmp dword ptr [esi+9E7Ch],eax
    L_0041708b:
        jge short L_00417099
    L_0041708d:
        mov dword ptr [esi+9E7Ch],eax
    L_00417093:
        mov edi,dword ptr [data_00474c44]
    L_00417099:
        mov edx,dword ptr [esi+9E78h]
    L_0041709f:
        mov ecx,dword ptr [esi+9E7Ch]
    L_004170a5:
        mov eax,edi
    L_004170a7:
        sub eax,edx
    L_004170a9:
        cmp ecx,eax
    L_004170ab:
        jle short L_004170b3
    L_004170ad:
        mov dword ptr [esi+9E7Ch],eax
    L_004170b3:
        mov eax,dword ptr [esi+9E7Ch]
    L_004170b9:
        mov edx,dword ptr [esi+9E78h]
    L_004170bf:
        add edx,eax
    L_004170c1:
        mov dword ptr [esi+9E78h],edx
    L_004170c7:
        mov ecx,dword ptr [data_00474c44]
    L_004170cd:
        mov eax,edx
    L_004170cf:
        cmp eax,ecx
    L_004170d1:
        jl short L_004170dd
    L_004170d3:
        mov dword ptr [esi+9E7Ch],0
    L_004170dd:
        mov ecx,dword ptr [esi+9E78h]
    L_004170e3:
        cmp ecx,ebp
    L_004170e5:
        jl short L_004170f4
    L_004170e7:
        cmp ebx,ebp
    L_004170e9:
        jge short L_004170f4
    L_004170eb:
        mov word ptr [esi+48D8h],4
    L_004170f4:
        cmp dword ptr [data_00474c40],ecx
    L_004170fa:
        jge short L_0041715b
    L_004170fc:
        mov eax,dword ptr [data_00474ca0]
    L_00417101:
        or eax,4
    L_00417104:
        test al,4
    L_00417106:
        mov dword ptr [data_00474c40],ecx
    L_0041710c:
        mov ecx,dword ptr [data_00474c90]
    L_00417112:
        mov dword ptr [data_00474c94],ecx
    L_00417118:
        mov dword ptr [data_00474ca0],eax
    L_0041711d:
        jne short L_0041715b
    L_0041711f:
        mov edi,dword ptr [data_0047770c]
    L_00417125:
        mov edx,dword ptr [edi+9E18h]
    L_0041712b:
        lea ebx,[edi+9E18h]
    L_00417131:
        push edx
    L_00417132:
        mov edx,dword ptr [data_00491c10]
    L_00417138:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041713d:
        push 0Fh
    L_0041713f:
        mov dword ptr [ebx],0
    L_00417145:
        mov eax,dword ptr [edi+9EC8h]
    L_0041714b:
        push 4Ah
    L_0041714d:
        push eax
    L_0041714e:
        lea edi,[esp+20h]
    L_00417152:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00417157:
        mov ecx,dword ptr [eax]
    L_00417159:
        mov dword ptr [ebx],ecx
    L_0041715b:
        cmp dword ptr [esi+9E64h],14h
    L_00417162:
        jl short L_00417189
    L_00417164:
        cmp dword ptr [data_00474c40],ebp
    L_0041716a:
        jl short L_0041717d
    L_0041716c:
        cmp dword ptr [esi+9E74h],ebp
    L_00417172:
        jge short L_0041717d
    L_00417174:
        mov word ptr [esi+2420h],4
    L_0041717d:
        mov edx,dword ptr [data_00474c40]
    L_00417183:
        mov dword ptr [esi+9E74h],edx
    L_00417189:
        mov eax,dword ptr [data_00474c40]
    L_0041718e:
        mov ecx,dword ptr [esi+9E78h]
    L_00417194:
        mov dword ptr [esp+0Ch],eax
    L_00417198:
        mov dword ptr [esp+10h],ecx
    L_0041719c:
        lea edi,[esi+2874h]
    L_004171a2:
        mov dword ptr [esp+14h],9
    L_004171aa:
        jmp short L_004171b0
    L_004171ac:
        mov eax,dword ptr [esp+0Ch]
    L_004171b0:
        test eax,eax
    L_004171b2:
        lea ebp,[edi-24B8h]
    L_004171b8:
        je short L_004171da
    L_004171ba:
        cdq
    L_004171bb:
        mov ecx,0Ah
    L_004171c0:
        idiv ecx
    L_004171c2:
        mov ecx,dword ptr [esi+9EC8h]
    L_004171c8:
        mov ebx,eax
    L_004171ca:
        add edx,8
    L_004171cd:
        mov eax,ebp
    L_004171cf:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004171d4:
        mov dword ptr [esp+0Ch],ebx
    L_004171d8:
        jmp short L_004171ec
    L_004171da:
        mov ecx,dword ptr [esi+9EC8h]
    L_004171e0:
        mov edx,8
    L_004171e5:
        mov eax,ebp
    L_004171e7:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004171ec:
        mov eax,dword ptr [esp+10h]
    L_004171f0:
        test eax,eax
    L_004171f2:
        je short L_00417214
    L_004171f4:
        cdq
    L_004171f5:
        mov ecx,0Ah
    L_004171fa:
        idiv ecx
    L_004171fc:
        mov ecx,dword ptr [esi+9EC8h]
    L_00417202:
        mov ebx,eax
    L_00417204:
        add edx,8
    L_00417207:
        mov eax,edi
    L_00417209:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0041720e:
        mov dword ptr [esp+10h],ebx
    L_00417212:
        jmp short L_00417226
    L_00417214:
        mov ecx,dword ptr [esi+9EC8h]
    L_0041721a:
        mov edx,8
    L_0041721f:
        mov eax,edi
    L_00417221:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00417226:
        push ebp
    L_00417227:
        call asm_FUN_0043ee30_0043ee30
    L_0041722c:
        push edi
    L_0041722d:
        call asm_FUN_0043ee30_0043ee30
    L_00417232:
        mov eax,dword ptr [esp+14h]
    L_00417236:
        add edi,3ACh
    L_0041723c:
        dec eax
    L_0041723d:
        mov dword ptr [esp+14h],eax
    L_00417241:
        jne asm_target_004171ac
    L_00417247:
        mov edx,dword ptr [data_00474c94]
    L_0041724d:
        mov ecx,dword ptr [esi+9EC8h]
    L_00417253:
        lea edi,[esi+10h]
    L_00417256:
        add edx,8
    L_00417259:
        mov eax,edi
    L_0041725b:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00417260:
        mov edx,dword ptr [data_00474c90]
    L_00417266:
        mov ecx,dword ptr [esi+9EC8h]
    L_0041726c:
        lea ebx,[esi+24C8h]
    L_00417272:
        add edx,8
    L_00417275:
        mov eax,ebx
    L_00417277:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0041727c:
        push edi
    L_0041727d:
        call asm_FUN_0043ee30_0043ee30
    L_00417282:
        push ebx
    L_00417283:
        call asm_FUN_0043ee30_0043ee30
    L_00417288:
        test byte ptr [esi+9EB4h],20h
    L_0041728f:
        pop edi
    L_00417290:
        pop ebp
    L_00417291:
        pop ebx
    L_00417292:
        jne short L_004172db
    L_00417294:
        cmp dword ptr [data_00474c74],4
    L_0041729b:
        je short L_004172b1
    L_0041729d:
        mov eax,dword ptr [data_00474c9c]
    L_004172a2:
        mov edx,dword ptr [esi+9E78h]
    L_004172a8:
        cmp edx,dword ptr [eax*4+474474h]
    L_004172af:
        jmp short L_004172c4
    L_004172b1:
        mov edx,dword ptr [data_00474c9c]
    L_004172b7:
        mov ecx,dword ptr [esi+9E78h]
    L_004172bd:
        cmp ecx,dword ptr [edx*4+474488h]
    L_004172c4:
        jl short L_004172db
    L_004172c6:
        mov eax,474C40h
    L_004172cb:
        mov ecx,1
    L_004172d0:
        call asm_Recovery_IncrementAnimationCount_004188a0
    L_004172d5:
        inc dword ptr [data_00474c9c]
    L_004172db:
        add esp,0Ch
    L_004172de:
        ret
    }
}
// D3603 BLOCKED: native-LTCG readability attempt is not retained. Ghidra
// identifies an ESI receiver plus animation-manager/configuration callees,
// x87-free integer formatting, and a second animation-count private edge.
// closest_byte_count: 0/671; first_diff: 0x00417040; residual_class:
// private ESI receiver, animation private ABI, loop/stack-slot layout.
// variants_tested: Ghidra decompile/disassembly; authoritative assembly probe.
// next_lever: co-compile both real callers and the animation callees in a
// schema-2 native-LTCG cluster.
