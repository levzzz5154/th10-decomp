#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00454ED7..0x00455670: FUN_00454ed7
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00454ed7_00454ed7() {
    __asm {
    L_00454ed7:
        push ebp
    L_00454ed8:
        lea ebp,[esp-1E0h]
    L_00454edf:
        sub esp,260h
    L_00454ee5:
        mov eax,dword ptr [data_00473660]
    L_00454eea:
        mov ecx,dword ptr [ebp+1F0h]
    L_00454ef0:
        xor eax,ebp
    L_00454ef2:
        mov dword ptr [ebp+1DCh],eax
    L_00454ef8:
        mov eax,dword ptr [ebp+1E8h]
    L_00454efe:
        mov dword ptr [ebp-54h],eax
    L_00454f01:
        mov eax,dword ptr [ebp+1ECh]
    L_00454f07:
        push ebx
    L_00454f08:
        mov bl,byte ptr [eax]
    L_00454f0a:
        mov dword ptr [ebp-34h],ecx
    L_00454f0d:
        xor ecx,ecx
    L_00454f0f:
        test bl,bl
    L_00454f11:
        mov dword ptr [ebp-50h],eax
    L_00454f14:
        mov dword ptr [ebp-40h],ecx
    L_00454f17:
        mov dword ptr [ebp-44h],ecx
    L_00454f1a:
        mov dword ptr [ebp-60h],ecx
    L_00454f1d:
        je asm_target_00455658
    L_00454f23:
        push esi
    L_00454f24:
        push edi
    L_00454f25:
        mov edi,eax
    L_00454f27:
        jmp short L_00454f2c
    L_00454f29:
        mov ecx,dword ptr [ebp-70h]
    L_00454f2c:
        inc edi
    L_00454f2d:
        cmp dword ptr [ebp-44h],0
    L_00454f31:
        mov dword ptr [ebp-50h],edi
    L_00454f34:
        jl asm_target_00455656
    L_00454f3a:
        cmp bl,20h
    L_00454f3d:
        jl short L_00454f53
    L_00454f3f:
        cmp bl,78h
    L_00454f42:
        jg short L_00454f53
    L_00454f44:
        movsx eax,bl
    L_00454f47:
        movsx eax,byte ptr [eax+46A770h]
    L_00454f4e:
        and eax,0Fh
    L_00454f51:
        jmp short L_00454f55
    L_00454f53:
        xor eax,eax
    L_00454f55:
        movsx eax,byte ptr [ecx+eax*8+46A790h]
    L_00454f5d:
        push 7
    L_00454f5f:
        sar eax,4
    L_00454f62:
        pop ecx
    L_00454f63:
        cmp eax,ecx
    L_00454f65:
        mov dword ptr [ebp-70h],eax
    L_00454f68:
        ja asm_target_00455649
    L_00454f6e:
        jmp dword ptr [eax*4+455673h]
    L_00454f75:
        xor eax,eax
    L_00454f77:
        or dword ptr [ebp-38h],0FFFFFFFFh
    L_00454f7b:
        mov dword ptr [ebp-6Ch],eax
    L_00454f7e:
        mov dword ptr [ebp-64h],eax
    L_00454f81:
        mov dword ptr [ebp-58h],eax
    L_00454f84:
        mov dword ptr [ebp-4Ch],eax
    L_00454f87:
        mov dword ptr [ebp-30h],eax
    L_00454f8a:
        mov dword ptr [ebp-5Ch],eax
    L_00454f8d:
        jmp asm_target_00455649
    L_00454f92:
        movsx eax,bl
    L_00454f95:
        sub eax,20h
    L_00454f98:
        je short L_00454fd5
    L_00454f9a:
        sub eax,3
    L_00454f9d:
        je short L_00454fcc
    L_00454f9f:
        sub eax,8
    L_00454fa2:
        je short L_00454fc3
    L_00454fa4:
        dec eax
    L_00454fa5:
        dec eax
    L_00454fa6:
        je short L_00454fba
    L_00454fa8:
        sub eax,3
    L_00454fab:
        jne asm_target_00455649
    L_00454fb1:
        or dword ptr [ebp-30h],8
    L_00454fb5:
        jmp asm_target_00455649
    L_00454fba:
        or dword ptr [ebp-30h],4
    L_00454fbe:
        jmp asm_target_00455649
    L_00454fc3:
        or dword ptr [ebp-30h],1
    L_00454fc7:
        jmp asm_target_00455649
    L_00454fcc:
        or byte ptr [ebp-30h],80h
    L_00454fd0:
        jmp asm_target_00455649
    L_00454fd5:
        or dword ptr [ebp-30h],2
    L_00454fd9:
        jmp asm_target_00455649
    L_00454fde:
        cmp bl,2Ah
    L_00454fe1:
        jne short L_00455004
    L_00454fe3:
        add dword ptr [ebp-34h],4
    L_00454fe7:
        mov eax,dword ptr [ebp-34h]
    L_00454fea:
        mov eax,dword ptr [eax-4]
    L_00454fed:
        test eax,eax
    L_00454fef:
        mov dword ptr [ebp-58h],eax
    L_00454ff2:
        jge asm_target_00455649
    L_00454ff8:
        or dword ptr [ebp-30h],4
    L_00454ffc:
        neg dword ptr [ebp-58h]
    L_00454fff:
        jmp asm_target_00455649
    L_00455004:
        mov eax,dword ptr [ebp-58h]
    L_00455007:
        movsx ecx,bl
    L_0045500a:
        lea eax,[eax+eax*4]
    L_0045500d:
        lea eax,[ecx+eax*2-30h]
    L_00455011:
        mov dword ptr [ebp-58h],eax
    L_00455014:
        jmp asm_target_00455649
    L_00455019:
        and dword ptr [ebp-38h],0
    L_0045501d:
        jmp asm_target_00455649
    L_00455022:
        cmp bl,2Ah
    L_00455025:
        jne short L_00455045
    L_00455027:
        add dword ptr [ebp-34h],4
    L_0045502b:
        mov eax,dword ptr [ebp-34h]
    L_0045502e:
        mov eax,dword ptr [eax-4]
    L_00455031:
        test eax,eax
    L_00455033:
        mov dword ptr [ebp-38h],eax
    L_00455036:
        jge asm_target_00455649
    L_0045503c:
        or dword ptr [ebp-38h],0FFFFFFFFh
    L_00455040:
        jmp asm_target_00455649
    L_00455045:
        mov eax,dword ptr [ebp-38h]
    L_00455048:
        movsx ecx,bl
    L_0045504b:
        lea eax,[eax+eax*4]
    L_0045504e:
        lea eax,[ecx+eax*2-30h]
    L_00455052:
        mov dword ptr [ebp-38h],eax
    L_00455055:
        jmp asm_target_00455649
    L_0045505a:
        cmp bl,49h
    L_0045505d:
        je short L_0045508d
    L_0045505f:
        cmp bl,68h
    L_00455062:
        je short L_00455084
    L_00455064:
        cmp bl,6Ch
    L_00455067:
        je short L_0045507b
    L_00455069:
        cmp bl,77h
    L_0045506c:
        jne asm_target_00455649
    L_00455072:
        or byte ptr [ebp-2Fh],8
    L_00455076:
        jmp asm_target_00455649
    L_0045507b:
        or dword ptr [ebp-30h],10h
    L_0045507f:
        jmp asm_target_00455649
    L_00455084:
        or dword ptr [ebp-30h],20h
    L_00455088:
        jmp asm_target_00455649
    L_0045508d:
        mov al,byte ptr [edi]
    L_0045508f:
        cmp al,36h
    L_00455091:
        jne short L_004550a7
    L_00455093:
        cmp byte ptr [edi+1],34h
    L_00455097:
        jne short L_004550a7
    L_00455099:
        inc edi
    L_0045509a:
        inc edi
    L_0045509b:
        or byte ptr [ebp-2Fh],80h
    L_0045509f:
        mov dword ptr [ebp-50h],edi
    L_004550a2:
        jmp asm_target_00455649
    L_004550a7:
        cmp al,33h
    L_004550a9:
        jne short L_004550bf
    L_004550ab:
        cmp byte ptr [edi+1],32h
    L_004550af:
        jne short L_004550bf
    L_004550b1:
        inc edi
    L_004550b2:
        inc edi
    L_004550b3:
        and byte ptr [ebp-2Fh],7Fh
    L_004550b7:
        mov dword ptr [ebp-50h],edi
    L_004550ba:
        jmp asm_target_00455649
    L_004550bf:
        cmp al,64h
    L_004550c1:
        je asm_target_00455649
    L_004550c7:
        cmp al,69h
    L_004550c9:
        je asm_target_00455649
    L_004550cf:
        cmp al,6Fh
    L_004550d1:
        je asm_target_00455649
    L_004550d7:
        cmp al,75h
    L_004550d9:
        je asm_target_00455649
    L_004550df:
        cmp al,78h
    L_004550e1:
        je asm_target_00455649
    L_004550e7:
        cmp al,58h
    L_004550e9:
        je asm_target_00455649
    L_004550ef:
        and dword ptr [ebp-70h],0
    L_004550f3:
        mov ecx,dword ptr [data_004739d8]
    L_004550f9:
        and dword ptr [ebp-5Ch],0
    L_004550fd:
        movzx eax,bl
    L_00455100:
        test byte ptr [ecx+eax*2+1],80h
    L_00455105:
        je short L_0045511a
    L_00455107:
        mov ecx,dword ptr [ebp-54h]
    L_0045510a:
        lea esi,[ebp-44h]
    L_0045510d:
        mov al,bl
    L_0045510f:
        call asm_write_char_00454e2a
    L_00455114:
        mov bl,byte ptr [edi]
    L_00455116:
        inc edi
    L_00455117:
        mov dword ptr [ebp-50h],edi
    L_0045511a:
        mov ecx,dword ptr [ebp-54h]
    L_0045511d:
        lea esi,[ebp-44h]
    L_00455120:
        mov al,bl
    L_00455122:
        call asm_write_char_00454e2a
    L_00455127:
        jmp asm_target_00455649
    L_0045512c:
        movsx eax,bl
    L_0045512f:
        cmp eax,67h
    L_00455132:
        jg asm_target_00455372
    L_00455138:
        cmp eax,65h
    L_0045513b:
        jge asm_target_004551c1
    L_00455141:
        cmp eax,58h
    L_00455144:
        jg asm_target_0045521c
    L_0045514a:
        je asm_target_004553f3
    L_00455150:
        sub eax,43h
    L_00455153:
        je asm_target_004551e1
    L_00455159:
        dec eax
    L_0045515a:
        dec eax
    L_0045515b:
        je short L_004551b7
    L_0045515d:
        dec eax
    L_0045515e:
        dec eax
    L_0045515f:
        je short L_004551b7
    L_00455161:
        sub eax,0Ch
    L_00455164:
        jne asm_target_00455541
    L_0045516a:
        test word ptr [ebp-30h],830h
    L_00455170:
        jne short L_00455176
    L_00455172:
        or byte ptr [ebp-2Fh],8
    L_00455176:
        mov ecx,dword ptr [ebp-38h]
    L_00455179:
        cmp ecx,0FFFFFFFFh
    L_0045517c:
        jne short L_00455183
    L_0045517e:
        mov ecx,7FFFFFFFh
    L_00455183:
        add dword ptr [ebp-34h],4
    L_00455187:
        test word ptr [ebp-30h],810h
    L_0045518d:
        mov eax,dword ptr [ebp-34h]
    L_00455190:
        mov eax,dword ptr [eax-4]
    L_00455193:
        mov dword ptr [ebp-3Ch],eax
    L_00455196:
        je asm_target_004553c8
    L_0045519c:
        test eax,eax
    L_0045519e:
        jne short L_004551a8
    L_004551a0:
        mov eax,dword ptr [data_004731a4]
    L_004551a5:
        mov dword ptr [ebp-3Ch],eax
    L_004551a8:
        mov eax,dword ptr [ebp-3Ch]
    L_004551ab:
        mov dword ptr [ebp-5Ch],1
    L_004551b2:
        jmp asm_target_004553ba
    L_004551b7:
        mov dword ptr [ebp-6Ch],1
    L_004551be:
        add bl,20h
    L_004551c1:
        or dword ptr [ebp-30h],40h
    L_004551c5:
        cmp dword ptr [ebp-38h],0
    L_004551c9:
        lea esi,[ebp-2Ch]
    L_004551cc:
        mov dword ptr [ebp-3Ch],esi
    L_004551cf:
        jge asm_target_004552bc
    L_004551d5:
        mov dword ptr [ebp-38h],6
    L_004551dc:
        jmp asm_target_00455303
    L_004551e1:
        test word ptr [ebp-30h],830h
    L_004551e7:
        jne short L_004551ed
    L_004551e9:
        or byte ptr [ebp-2Fh],8
    L_004551ed:
        add dword ptr [ebp-34h],4
    L_004551f1:
        test word ptr [ebp-30h],810h
    L_004551f7:
        mov eax,dword ptr [ebp-34h]
    L_004551fa:
        je short L_0045525b
    L_004551fc:
        movsx eax,word ptr [eax-4]
    L_00455200:
        push eax
    L_00455201:
        lea eax,[ebp-2Ch]
    L_00455204:
        push eax
    L_00455205:
        call asm_wctomb_0045a16e
    L_0045520a:
        test eax,eax
    L_0045520c:
        pop ecx
    L_0045520d:
        pop ecx
    L_0045520e:
        mov dword ptr [ebp-40h],eax
    L_00455211:
        jge short L_00455268
    L_00455213:
        mov dword ptr [ebp-64h],1
    L_0045521a:
        jmp short L_00455268
    L_0045521c:
        sub eax,5Ah
    L_0045521f:
        je short L_00455273
    L_00455221:
        sub eax,9
    L_00455224:
        je short L_004551ed
    L_00455226:
        dec eax
    L_00455227:
        jne asm_target_00455541
    L_0045522d:
        or dword ptr [ebp-30h],40h
    L_00455231:
        mov dword ptr [ebp-40h],0Ah
    L_00455238:
        mov ebx,dword ptr [ebp-30h]
    L_0045523b:
        mov esi,8000h
    L_00455240:
        test ebx,esi
    L_00455242:
        je asm_target_00455463
    L_00455248:
        mov ecx,dword ptr [ebp-34h]
    L_0045524b:
        mov eax,dword ptr [ecx]
    L_0045524d:
        mov edx,dword ptr [ecx+4]
    L_00455250:
        add ecx,8
    L_00455253:
        mov dword ptr [ebp-34h],ecx
    L_00455256:
        jmp asm_target_0045548b
    L_0045525b:
        mov al,byte ptr [eax-4]
    L_0045525e:
        mov byte ptr [ebp-2Ch],al
    L_00455261:
        mov dword ptr [ebp-40h],1
    L_00455268:
        lea eax,[ebp-2Ch]
    L_0045526b:
        mov dword ptr [ebp-3Ch],eax
    L_0045526e:
        jmp asm_target_00455541
    L_00455273:
        add dword ptr [ebp-34h],4
    L_00455277:
        mov eax,dword ptr [ebp-34h]
    L_0045527a:
        mov eax,dword ptr [eax-4]
    L_0045527d:
        test eax,eax
    L_0045527f:
        je short L_004552ae
    L_00455281:
        mov ecx,dword ptr [eax+4]
    L_00455284:
        test ecx,ecx
    L_00455286:
        je short L_004552ae
    L_00455288:
        test byte ptr [ebp-2Fh],8
    L_0045528c:
        movsx eax,word ptr [eax]
    L_0045528f:
        mov dword ptr [ebp-3Ch],ecx
    L_00455292:
        je short L_004552a5
    L_00455294:
        cdq
    L_00455295:
        sub eax,edx
    L_00455297:
        sar eax,1
    L_00455299:
        mov dword ptr [ebp-5Ch],1
    L_004552a0:
        jmp asm_target_0045553e
    L_004552a5:
        and dword ptr [ebp-5Ch],0
    L_004552a9:
        jmp asm_target_0045553e
    L_004552ae:
        mov eax,dword ptr [data_004731a0]
    L_004552b3:
        mov dword ptr [ebp-3Ch],eax
    L_004552b6:
        push eax
    L_004552b7:
        jmp asm_target_00455367
    L_004552bc:
        jne short L_004552cc
    L_004552be:
        cmp bl,67h
    L_004552c1:
        jne short L_00455303
    L_004552c3:
        mov dword ptr [ebp-38h],1
    L_004552ca:
        jmp short L_00455303
    L_004552cc:
        mov eax,200h
    L_004552d1:
        cmp dword ptr [ebp-38h],eax
    L_004552d4:
        jle short L_004552d9
    L_004552d6:
        mov dword ptr [ebp-38h],eax
    L_004552d9:
        mov edi,0A3h
    L_004552de:
        cmp dword ptr [ebp-38h],edi
    L_004552e1:
        jle short L_00455303
    L_004552e3:
        mov eax,dword ptr [ebp-38h]
    L_004552e6:
        add eax,15Dh
    L_004552eb:
        push eax
    L_004552ec:
        call asm_malloc_00452706
    L_004552f1:
        test eax,eax
    L_004552f3:
        pop ecx
    L_004552f4:
        mov dword ptr [ebp-60h],eax
    L_004552f7:
        je short L_00455300
    L_004552f9:
        mov dword ptr [ebp-3Ch],eax
    L_004552fc:
        mov esi,eax
    L_004552fe:
        jmp short L_00455303
    L_00455300:
        mov dword ptr [ebp-38h],edi
    L_00455303:
        mov eax,dword ptr [ebp-34h]
    L_00455306:
        mov ecx,dword ptr [eax]
    L_00455308:
        push dword ptr [ebp-6Ch]
    L_0045530b:
        add eax,8
    L_0045530e:
        push dword ptr [ebp-38h]
    L_00455311:
        mov dword ptr [ebp-34h],eax
    L_00455314:
        mov eax,dword ptr [eax-4]
    L_00455317:
        mov dword ptr [ebp-7Ch],eax
    L_0045531a:
        movsx eax,bl
    L_0045531d:
        push eax
    L_0045531e:
        lea eax,[ebp-80h]
    L_00455321:
        push esi
    L_00455322:
        push eax
    L_00455323:
        mov dword ptr [ebp-80h],ecx
    L_00455326:
        call dword ptr [data_004739c0]
    L_0045532c:
        mov edi,dword ptr [ebp-30h]
    L_0045532f:
        add esp,14h
    L_00455332:
        and edi,80h
    L_00455338:
        je short L_00455348
    L_0045533a:
        cmp dword ptr [ebp-38h],0
    L_0045533e:
        jne short L_00455348
    L_00455340:
        push esi
    L_00455341:
        call dword ptr [data_004739cc]
    L_00455347:
        pop ecx
    L_00455348:
        cmp bl,67h
    L_0045534b:
        jne short L_00455359
    L_0045534d:
        test edi,edi
    L_0045534f:
        jne short L_00455359
    L_00455351:
        push esi
    L_00455352:
        call dword ptr [data_004739c4]
    L_00455358:
        pop ecx
    L_00455359:
        cmp byte ptr [esi],2Dh
    L_0045535c:
        jne short L_00455366
    L_0045535e:
        or byte ptr [ebp-2Fh],1
    L_00455362:
        inc esi
    L_00455363:
        mov dword ptr [ebp-3Ch],esi
    L_00455366:
        push esi
    L_00455367:
        call asm_strlen_00456720
    L_0045536c:
        pop ecx
    L_0045536d:
        jmp asm_target_0045553e
    L_00455372:
        sub eax,69h
    L_00455375:
        je asm_target_0045522d
    L_0045537b:
        sub eax,5
    L_0045537e:
        je asm_target_00455439
    L_00455384:
        dec eax
    L_00455385:
        je asm_target_0045541f
    L_0045538b:
        dec eax
    L_0045538c:
        je short L_004553ec
    L_0045538e:
        sub eax,3
    L_00455391:
        je asm_target_00455176
    L_00455397:
        dec eax
    L_00455398:
        dec eax
    L_00455399:
        je asm_target_00455231
    L_0045539f:
        sub eax,3
    L_004553a2:
        jne asm_target_00455541
    L_004553a8:
        mov dword ptr [ebp-68h],27h
    L_004553af:
        jmp short L_004553f6
    L_004553b1:
        dec ecx
    L_004553b2:
        cmp word ptr [eax],0
    L_004553b6:
        je short L_004553be
    L_004553b8:
        inc eax
    L_004553b9:
        inc eax
    L_004553ba:
        test ecx,ecx
    L_004553bc:
        jne short L_004553b1
    L_004553be:
        sub eax,dword ptr [ebp-3Ch]
    L_004553c1:
        sar eax,1
    L_004553c3:
        jmp asm_target_0045553e
    L_004553c8:
        test eax,eax
    L_004553ca:
        jne short L_004553d4
    L_004553cc:
        mov eax,dword ptr [data_004731a0]
    L_004553d1:
        mov dword ptr [ebp-3Ch],eax
    L_004553d4:
        mov eax,dword ptr [ebp-3Ch]
    L_004553d7:
        jmp short L_004553e0
    L_004553d9:
        dec ecx
    L_004553da:
        cmp byte ptr [eax],0
    L_004553dd:
        je short L_004553e4
    L_004553df:
        inc eax
    L_004553e0:
        test ecx,ecx
    L_004553e2:
        jne short L_004553d9
    L_004553e4:
        sub eax,dword ptr [ebp-3Ch]
    L_004553e7:
        jmp asm_target_0045553e
    L_004553ec:
        mov dword ptr [ebp-38h],8
    L_004553f3:
        mov dword ptr [ebp-68h],ecx
    L_004553f6:
        test byte ptr [ebp-30h],80h
    L_004553fa:
        mov dword ptr [ebp-40h],10h
    L_00455401:
        je asm_target_00455238
    L_00455407:
        mov al,byte ptr [ebp-68h]
    L_0045540a:
        add al,51h
    L_0045540c:
        mov byte ptr [ebp-48h],30h
    L_00455410:
        mov byte ptr [ebp-47h],al
    L_00455413:
        mov dword ptr [ebp-4Ch],2
    L_0045541a:
        jmp asm_target_00455238
    L_0045541f:
        test byte ptr [ebp-30h],80h
    L_00455423:
        mov dword ptr [ebp-40h],8
    L_0045542a:
        je asm_target_00455238
    L_00455430:
        or byte ptr [ebp-2Fh],2
    L_00455434:
        jmp asm_target_00455238
    L_00455439:
        add dword ptr [ebp-34h],4
    L_0045543d:
        test byte ptr [ebp-30h],20h
    L_00455441:
        mov eax,dword ptr [ebp-34h]
    L_00455444:
        mov eax,dword ptr [eax-4]
    L_00455447:
        je short L_00455452
    L_00455449:
        mov cx,word ptr [ebp-44h]
    L_0045544d:
        mov word ptr [eax],cx
    L_00455450:
        jmp short L_00455457
    L_00455452:
        mov ecx,dword ptr [ebp-44h]
    L_00455455:
        mov dword ptr [eax],ecx
    L_00455457:
        mov dword ptr [ebp-64h],1
    L_0045545e:
        jmp asm_target_00455636
    L_00455463:
        add dword ptr [ebp-34h],4
    L_00455467:
        test bl,20h
    L_0045546a:
        mov eax,dword ptr [ebp-34h]
    L_0045546d:
        je short L_00455481
    L_0045546f:
        test bl,40h
    L_00455472:
        je short L_0045547b
    L_00455474:
        movsx eax,word ptr [eax-4]
    L_00455478:
        cdq
    L_00455479:
        jmp short L_0045548b
    L_0045547b:
        movzx eax,word ptr [eax-4]
    L_0045547f:
        jmp short L_00455478
    L_00455481:
        test bl,40h
    L_00455484:
        mov eax,dword ptr [eax-4]
    L_00455487:
        jne short L_00455478
    L_00455489:
        xor edx,edx
    L_0045548b:
        test bl,40h
    L_0045548e:
        je short L_004554a5
    L_00455490:
        test edx,edx
    L_00455492:
        jg short L_004554a5
    L_00455494:
        jl short L_0045549a
    L_00455496:
        test eax,eax
    L_00455498:
        jae short L_004554a5
    L_0045549a:
        neg eax
    L_0045549c:
        adc edx,0
    L_0045549f:
        neg edx
    L_004554a1:
        or byte ptr [ebp-2Fh],1
    L_004554a5:
        test dword ptr [ebp-30h],esi
    L_004554a8:
        mov ebx,eax
    L_004554aa:
        mov edi,edx
    L_004554ac:
        jne short L_004554b0
    L_004554ae:
        xor edi,edi
    L_004554b0:
        cmp dword ptr [ebp-38h],0
    L_004554b4:
        jge short L_004554bf
    L_004554b6:
        mov dword ptr [ebp-38h],1
    L_004554bd:
        jmp short L_004554d0
    L_004554bf:
        and dword ptr [ebp-30h],0FFFFFFF7h
    L_004554c3:
        mov eax,200h
    L_004554c8:
        cmp dword ptr [ebp-38h],eax
    L_004554cb:
        jle short L_004554d0
    L_004554cd:
        mov dword ptr [ebp-38h],eax
    L_004554d0:
        mov eax,ebx
    L_004554d2:
        or eax,edi
    L_004554d4:
        jne short L_004554da
    L_004554d6:
        and dword ptr [ebp-4Ch],0
    L_004554da:
        lea esi,[ebp+1D3h]
    L_004554e0:
        mov eax,dword ptr [ebp-38h]
    L_004554e3:
        dec dword ptr [ebp-38h]
    L_004554e6:
        test eax,eax
    L_004554e8:
        jg short L_004554f0
    L_004554ea:
        mov eax,ebx
    L_004554ec:
        or eax,edi
    L_004554ee:
        je short L_00455514
    L_004554f0:
        mov eax,dword ptr [ebp-40h]
    L_004554f3:
        cdq
    L_004554f4:
        push edx
    L_004554f5:
        push eax
    L_004554f6:
        push edi
    L_004554f7:
        push ebx
    L_004554f8:
        call asm_aulldvrm_0045a1b0
    L_004554fd:
        add ecx,30h
    L_00455500:
        cmp ecx,39h
    L_00455503:
        mov dword ptr [ebp-74h],ebx
    L_00455506:
        mov ebx,eax
    L_00455508:
        mov edi,edx
    L_0045550a:
        jle short L_0045550f
    L_0045550c:
        add ecx,dword ptr [ebp-68h]
    L_0045550f:
        mov byte ptr [esi],cl
    L_00455511:
        dec esi
    L_00455512:
        jmp short L_004554e0
    L_00455514:
        lea eax,[ebp+1D3h]
    L_0045551a:
        sub eax,esi
    L_0045551c:
        inc esi
    L_0045551d:
        test byte ptr [ebp-2Fh],2
    L_00455521:
        mov dword ptr [ebp-40h],eax
    L_00455524:
        mov dword ptr [ebp-3Ch],esi
    L_00455527:
        je short L_00455541
    L_00455529:
        mov ecx,esi
    L_0045552b:
        cmp byte ptr [ecx],30h
    L_0045552e:
        jne short L_00455534
    L_00455530:
        test eax,eax
    L_00455532:
        jne short L_00455541
    L_00455534:
        dec dword ptr [ebp-3Ch]
    L_00455537:
        mov ecx,dword ptr [ebp-3Ch]
    L_0045553a:
        mov byte ptr [ecx],30h
    L_0045553d:
        inc eax
    L_0045553e:
        mov dword ptr [ebp-40h],eax
    L_00455541:
        cmp dword ptr [ebp-64h],0
    L_00455545:
        jne asm_target_00455636
    L_0045554b:
        mov ebx,dword ptr [ebp-30h]
    L_0045554e:
        test bl,40h
    L_00455551:
        je short L_00455579
    L_00455553:
        test bh,1
    L_00455556:
        je short L_0045555e
    L_00455558:
        mov byte ptr [ebp-48h],2Dh
    L_0045555c:
        jmp short L_00455572
    L_0045555e:
        test bl,1
    L_00455561:
        je short L_00455569
    L_00455563:
        mov byte ptr [ebp-48h],2Bh
    L_00455567:
        jmp short L_00455572
    L_00455569:
        test bl,2
    L_0045556c:
        je short L_00455579
    L_0045556e:
        mov byte ptr [ebp-48h],20h
    L_00455572:
        mov dword ptr [ebp-4Ch],1
    L_00455579:
        mov esi,dword ptr [ebp-58h]
    L_0045557c:
        sub esi,dword ptr [ebp-4Ch]
    L_0045557f:
        sub esi,dword ptr [ebp-40h]
    L_00455582:
        test bl,0Ch
    L_00455585:
        jne short L_00455598
    L_00455587:
        push dword ptr [ebp-54h]
    L_0045558a:
        lea eax,[ebp-44h]
    L_0045558d:
        push esi
    L_0045558e:
        push 20h
    L_00455590:
        call asm_write_multi_char_00454e5d
    L_00455595:
        add esp,0Ch
    L_00455598:
        push dword ptr [ebp-4Ch]
    L_0045559b:
        mov edi,dword ptr [ebp-54h]
    L_0045559e:
        lea eax,[ebp-44h]
    L_004555a1:
        lea ecx,[ebp-48h]
    L_004555a4:
        call asm_write_string_00454e81
    L_004555a9:
        test bl,8
    L_004555ac:
        pop ecx
    L_004555ad:
        je short L_004555c3
    L_004555af:
        test bl,4
    L_004555b2:
        jne short L_004555c3
    L_004555b4:
        push edi
    L_004555b5:
        push esi
    L_004555b6:
        push 30h
    L_004555b8:
        lea eax,[ebp-44h]
    L_004555bb:
        call asm_write_multi_char_00454e5d
    L_004555c0:
        add esp,0Ch
    L_004555c3:
        cmp dword ptr [ebp-5Ch],0
    L_004555c7:
        je short L_00455610
    L_004555c9:
        cmp dword ptr [ebp-40h],0
    L_004555cd:
        jle short L_00455610
    L_004555cf:
        mov eax,dword ptr [ebp-40h]
    L_004555d2:
        mov ebx,dword ptr [ebp-3Ch]
    L_004555d5:
        mov dword ptr [ebp-74h],eax
    L_004555d8:
        dec dword ptr [ebp-74h]
    L_004555db:
        xor eax,eax
    L_004555dd:
        mov ax,word ptr [ebx]
    L_004555e0:
        push eax
    L_004555e1:
        lea eax,[ebp+1D4h]
    L_004555e7:
        push eax
    L_004555e8:
        call asm_wctomb_0045a16e
    L_004555ed:
        inc ebx
    L_004555ee:
        pop ecx
    L_004555ef:
        inc ebx
    L_004555f0:
        test eax,eax
    L_004555f2:
        pop ecx
    L_004555f3:
        jle short L_0045561f
    L_004555f5:
        mov edi,dword ptr [ebp-54h]
    L_004555f8:
        push eax
    L_004555f9:
        lea eax,[ebp-44h]
    L_004555fc:
        lea ecx,[ebp+1D4h]
    L_00455602:
        call asm_write_string_00454e81
    L_00455607:
        cmp dword ptr [ebp-74h],0
    L_0045560b:
        pop ecx
    L_0045560c:
        jne short L_004555d8
    L_0045560e:
        jmp short L_0045561f
    L_00455610:
        push dword ptr [ebp-40h]
    L_00455613:
        mov ecx,dword ptr [ebp-3Ch]
    L_00455616:
        lea eax,[ebp-44h]
    L_00455619:
        call asm_write_string_00454e81
    L_0045561e:
        pop ecx
    L_0045561f:
        test byte ptr [ebp-30h],4
    L_00455623:
        je short L_00455636
    L_00455625:
        push dword ptr [ebp-54h]
    L_00455628:
        lea eax,[ebp-44h]
    L_0045562b:
        push esi
    L_0045562c:
        push 20h
    L_0045562e:
        call asm_write_multi_char_00454e5d
    L_00455633:
        add esp,0Ch
    L_00455636:
        cmp dword ptr [ebp-60h],0
    L_0045563a:
        je short L_00455649
    L_0045563c:
        push dword ptr [ebp-60h]
    L_0045563f:
        call asm_free_00452422
    L_00455644:
        and dword ptr [ebp-60h],0
    L_00455648:
        pop ecx
    L_00455649:
        mov edi,dword ptr [ebp-50h]
    L_0045564c:
        mov bl,byte ptr [edi]
    L_0045564e:
        test bl,bl
    L_00455650:
        jne asm_target_00454f29
    L_00455656:
        pop edi
    L_00455657:
        pop esi
    L_00455658:
        mov ecx,dword ptr [ebp+1DCh]
    L_0045565e:
        mov eax,dword ptr [ebp-44h]
    L_00455661:
        xor ecx,ebp
    L_00455663:
        pop ebx
    L_00455664:
        call asm_security_check_cookie_00458ea5
    L_00455669:
        add ebp,1E0h
    L_0045566f:
        leave
    L_00455670:
        ret
    }
}
