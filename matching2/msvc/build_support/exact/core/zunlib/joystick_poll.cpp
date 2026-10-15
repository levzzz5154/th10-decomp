// BLOCKED (H2501): see reference/recovery_notes/
// joystick_binding_reader_0044a190_allocator_findings_2026_10_11.md for the
// current models and what is settled. Older summary:
// closest_byte_count=800/833; first_diff=unmeasured;
// residual_class=MSVC register allocation and reload selection: retail keeps
// the binding pointer in EBX and flags in ESI, then rematerializes the device
// argument across joyGetPosEx, while the candidate unifies the loads;
// variants_tested=about 120 source families, project flag sweeps, aligned
// state/JOYINFOEX locals, and a native /GL+/LTCG link;
// next_lever=find a faithful aliasing/source boundary that forces the device
// reload and retail EBX/ESI homes; retain the exact wrapper until then.

#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

// 0x0044A190..0x0044A35C: FUN_0044a190
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044a190_0044a190() {
    __asm {
    L_0044a190:
        push ebp
    L_0044a191:
        mov ebp,esp
    L_0044a193:
        and esp,0FFFFFFF8h
    L_0044a196:
        sub esp,154h
    L_0044a19c:
        mov eax,dword ptr [data_00473660]
    L_0044a1a1:
        xor eax,ebp
    L_0044a1a3:
        mov dword ptr [esp+150h],eax
    L_0044a1aa:
        mov eax,dword ptr [ebp+8]
    L_0044a1ad:
        imul eax,6Ah
    L_0044a1b0:
        add eax,474E30h
    L_0044a1b5:
        push ebx
    L_0044a1b6:
        mov ebx,eax
    L_0044a1b8:
        mov eax,dword ptr [data_00491ff4]
    L_0044a1bd:
        test ah,4
    L_0044a1c0:
        push esi
    L_0044a1c1:
        push edi
    L_0044a1c2:
        mov esi,ecx
    L_0044a1c4:
        jne asm_target_0044a32e
    L_0044a1ca:
        xor eax,eax
    L_0044a1cc:
        mov ecx,0Dh
    L_0044a1d1:
        lea edi,[esp+14h]
    L_0044a1d5:
        rep stosd
    L_0044a1d7:
        mov edi,dword ptr [ebp+0Ch]
    L_0044a1da:
        xor ecx,ecx
    L_0044a1dc:
        test edi,edi
    L_0044a1de:
        setne cl
    L_0044a1e1:
        lea eax,[esp+14h]
    L_0044a1e5:
        push eax
    L_0044a1e6:
        mov dword ptr [esp+18h],34h
    L_0044a1ee:
        mov dword ptr [esp+1Ch],0FFh
    L_0044a1f6:
        push ecx
    L_0044a1f7:
        call dword ptr [imp_joyGetPosEx]
    L_0044a1fd:
        test eax,eax
    L_0044a1ff:
        jne asm_target_0044a3c2
    L_0044a205:
        mov cx,word ptr [ebx+58h]
    L_0044a209:
        test cx,cx
    L_0044a20c:
        mov edx,dword ptr [esp+34h]
    L_0044a210:
        jl short L_0044a223
    L_0044a212:
        mov eax,1
    L_0044a217:
        shl eax,cl
    L_0044a219:
        and eax,edx
    L_0044a21b:
        neg eax
    L_0044a21d:
        sbb eax,eax
    L_0044a21f:
        neg eax
    L_0044a221:
        or esi,eax
    L_0044a223:
        mov cx,word ptr [ebx+5Ah]
    L_0044a227:
        test cx,cx
    L_0044a22a:
        jl short L_0044a23e
    L_0044a22c:
        mov eax,1
    L_0044a231:
        shl eax,cl
    L_0044a233:
        and eax,edx
    L_0044a235:
        neg eax
    L_0044a237:
        sbb eax,eax
    L_0044a239:
        and eax,2
    L_0044a23c:
        or esi,eax
    L_0044a23e:
        mov cx,word ptr [ebx+5Eh]
    L_0044a242:
        test cx,cx
    L_0044a245:
        jl short L_0044a259
    L_0044a247:
        mov eax,1
    L_0044a24c:
        shl eax,cl
    L_0044a24e:
        and eax,edx
    L_0044a250:
        neg eax
    L_0044a252:
        sbb eax,eax
    L_0044a254:
        and eax,8
    L_0044a257:
        or esi,eax
    L_0044a259:
        mov cx,word ptr [ebx+5Ch]
    L_0044a25d:
        test cx,cx
    L_0044a260:
        jl short L_0044a274
    L_0044a262:
        mov eax,1
    L_0044a267:
        shl eax,cl
    L_0044a269:
        and eax,edx
    L_0044a26b:
        neg eax
    L_0044a26d:
        sbb eax,eax
    L_0044a26f:
        and eax,4
    L_0044a272:
        or esi,eax
    L_0044a274:
        mov bx,word ptr [ebx+68h]
    L_0044a278:
        test bx,bx
    L_0044a27b:
        jl short L_0044a293
    L_0044a27d:
        mov eax,1
    L_0044a282:
        mov cl,bl
    L_0044a284:
        shl eax,cl
    L_0044a286:
        and eax,edx
    L_0044a288:
        neg eax
    L_0044a28a:
        sbb eax,eax
    L_0044a28c:
        and eax,100h
    L_0044a291:
        or esi,eax
    L_0044a293:
        mov eax,dword ptr [ebp+0Ch]
    L_0044a296:
        imul eax,194h
    L_0044a29c:
        mov edx,dword ptr [eax+4918E0h]
    L_0044a2a2:
        mov edi,dword ptr [eax+4918DCh]
    L_0044a2a8:
        mov ebx,dword ptr [eax+4918E0h]
    L_0044a2ae:
        mov ecx,edx
    L_0044a2b0:
        sub ecx,edi
    L_0044a2b2:
        add edi,edx
    L_0044a2b4:
        mov edx,dword ptr [esp+1Ch]
    L_0044a2b8:
        shr edi,1
    L_0044a2ba:
        shr ecx,2
    L_0044a2bd:
        add edi,ecx
    L_0044a2bf:
        cmp edi,edx
    L_0044a2c1:
        sbb edi,edi
    L_0044a2c3:
        add ebx,dword ptr [eax+4918DCh]
    L_0044a2c9:
        and edi,80h
    L_0044a2cf:
        shr ebx,1
    L_0044a2d1:
        sub ebx,ecx
    L_0044a2d3:
        cmp edx,ebx
    L_0044a2d5:
        sbb edx,edx
    L_0044a2d7:
        and edx,40h
    L_0044a2da:
        or edi,edx
    L_0044a2dc:
        mov edx,dword ptr [eax+4918E8h]
    L_0044a2e2:
        or esi,edi
    L_0044a2e4:
        mov edi,dword ptr [eax+4918E4h]
    L_0044a2ea:
        mov ebx,edi
    L_0044a2ec:
        add ebx,edx
    L_0044a2ee:
        mov ecx,edx
    L_0044a2f0:
        sub ecx,edi
    L_0044a2f2:
        shr ecx,2
    L_0044a2f5:
        shr ebx,1
    L_0044a2f7:
        sub ebx,ecx
    L_0044a2f9:
        mov eax,ebx
    L_0044a2fb:
        mov ebx,dword ptr [esp+20h]
    L_0044a2ff:
        cmp ebx,eax
    L_0044a301:
        sbb eax,eax
    L_0044a303:
        add edi,edx
    L_0044a305:
        shr edi,1
    L_0044a307:
        add edi,ecx
    L_0044a309:
        and eax,10h
    L_0044a30c:
        cmp edi,ebx
    L_0044a30e:
        sbb ecx,ecx
    L_0044a310:
        and ecx,20h
    L_0044a313:
        or eax,ecx
    L_0044a315:
        or eax,esi
    L_0044a317:
        pop edi
    L_0044a318:
        pop esi
    L_0044a319:
        pop ebx
    L_0044a31a:
        mov ecx,dword ptr [esp+150h]
    L_0044a321:
        xor ecx,ebp
    L_0044a323:
        call asm_security_check_cookie_00458ea5
    L_0044a328:
        mov esp,ebp
    L_0044a32a:
        pop ebp
    L_0044a32b:
        ret 8
    L_0044a32e:
        mov edx,dword ptr [ebp+0Ch]
    L_0044a331:
        mov eax,dword ptr [edx*4+491C3Ch]
    L_0044a338:
        mov ecx,dword ptr [eax]
    L_0044a33a:
        push eax
    L_0044a33b:
        call dword ptr [ecx+64h]
    L_0044a33e:
        test eax,eax
    L_0044a340:
        TH10_REL8(0x7d, 0x0044a340, VA_asm_target_0044a397)
    L_0044a342:
        mov ebx,dword ptr [ebp+0Ch]
    L_0044a345:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a34c:
        mov edx,dword ptr [eax]
    L_0044a34e:
        push eax
    L_0044a34f:
        xor edi,edi
    L_0044a351:
        call dword ptr [edx+1Ch]
    L_0044a354:
        cmp eax,8007001Eh
    L_0044a359:
        TH10_REL8(0x75, 0x0044a359, VA_asm_target_0044a3c2)
    L_0044a35b:
        TH10_REL8(0xeb, 0x0044a35b, VA_asm_FUN_0044a190_part_0044a360)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0044a360:
        mov eax,dword ptr [ebx*4+491C3Ch]
    L_0044a367:
        mov ecx,dword ptr [eax]
    L_0044a369:
        push eax
    L_0044a36a:
        call dword ptr [ecx+1Ch]
    L_0044a36d:
        inc edi
    L_0044a36e:
        cmp edi,190h
    L_0044a374:
        jge short L_0044a3c2
    L_0044a376:
        cmp eax,8007001Eh
    L_0044a37b:
        je short L_0044a360
    L_0044a37d:
        mov ax,si
    L_0044a380:
        pop edi
    L_0044a381:
        pop esi
    L_0044a382:
        pop ebx
    L_0044a383:
        mov ecx,dword ptr [esp+150h]
    L_0044a38a:
        xor ecx,ebp
    L_0044a38c:
        call asm_security_check_cookie_00458ea5
    L_0044a391:
        mov esp,ebp
    L_0044a393:
        pop ebp
    L_0044a394:
        ret 8
    L_0044a397:
        mov edx,dword ptr [ebp+0Ch]
    L_0044a39a:
        xor eax,eax
    L_0044a39c:
        mov ecx,44h
    L_0044a3a1:
        lea edi,[esp+48h]
    L_0044a3a5:
        rep stosd
    L_0044a3a7:
        mov eax,dword ptr [edx*4+491C3Ch]
    L_0044a3ae:
        mov ecx,dword ptr [eax]
    L_0044a3b0:
        lea edx,[esp+48h]
    L_0044a3b4:
        push edx
    L_0044a3b5:
        push 110h
    L_0044a3ba:
        push eax
    L_0044a3bb:
        call dword ptr [ecx+24h]
    L_0044a3be:
        test eax,eax
    L_0044a3c0:
        jge short L_0044a3dc
    L_0044a3c2:
        mov ax,si
    L_0044a3c5:
        pop edi
    L_0044a3c6:
        pop esi
    L_0044a3c7:
        pop ebx
    L_0044a3c8:
        mov ecx,dword ptr [esp+150h]
    L_0044a3cf:
        xor ecx,ebp
    L_0044a3d1:
        call asm_security_check_cookie_00458ea5
    L_0044a3d6:
        mov esp,ebp
    L_0044a3d8:
        pop ebp
    L_0044a3d9:
        ret 8
    L_0044a3dc:
        mov ax,word ptr [ebx+58h]
    L_0044a3e0:
        test ax,ax
    L_0044a3e3:
        jl short L_0044a3f2
    L_0044a3e5:
        movsx eax,ax
    L_0044a3e8:
        movzx eax,byte ptr [esp+eax+78h]
    L_0044a3ed:
        shr eax,7
    L_0044a3f0:
        or esi,eax
    L_0044a3f2:
        mov ax,word ptr [ebx+5Ah]
    L_0044a3f6:
        test ax,ax
    L_0044a3f9:
        jl short L_0044a40b
    L_0044a3fb:
        movsx ecx,ax
    L_0044a3fe:
        movzx eax,byte ptr [esp+ecx+78h]
    L_0044a403:
        shr eax,6
    L_0044a406:
        and eax,2
    L_0044a409:
        or esi,eax
    L_0044a40b:
        mov ax,word ptr [ebx+5Eh]
    L_0044a40f:
        test ax,ax
    L_0044a412:
        jl short L_0044a424
    L_0044a414:
        movsx edx,ax
    L_0044a417:
        movzx eax,byte ptr [esp+edx+78h]
    L_0044a41c:
        shr eax,4
    L_0044a41f:
        and eax,8
    L_0044a422:
        or esi,eax
    L_0044a424:
        mov ax,word ptr [ebx+5Ch]
    L_0044a428:
        test ax,ax
    L_0044a42b:
        jl short L_0044a43d
    L_0044a42d:
        movsx eax,ax
    L_0044a430:
        movzx eax,byte ptr [esp+eax+78h]
    L_0044a435:
        shr eax,5
    L_0044a438:
        and eax,4
    L_0044a43b:
        or esi,eax
    L_0044a43d:
        mov bx,word ptr [ebx+68h]
    L_0044a441:
        test bx,bx
    L_0044a444:
        jl short L_0044a457
    L_0044a446:
        movsx ecx,bx
    L_0044a449:
        movzx eax,byte ptr [esp+ecx+78h]
    L_0044a44e:
        and eax,80h
    L_0044a453:
        shl eax,1
    L_0044a455:
        or esi,eax
    L_0044a457:
        movsx ecx,word ptr [data_00491d5e]
    L_0044a45e:
        mov ebx,dword ptr [esp+48h]
    L_0044a462:
        movsx eax,word ptr [data_00491d60]
    L_0044a469:
        mov edi,dword ptr [esp+4Ch]
    L_0044a46d:
        neg ecx
    L_0044a46f:
        xor edx,edx
    L_0044a471:
        cmp ebx,ecx
    L_0044a473:
        setge dl
    L_0044a476:
        xor ebx,ebx
    L_0044a478:
        mov ecx,eax
    L_0044a47a:
        neg ecx
    L_0044a47c:
        dec edx
    L_0044a47d:
        and edx,40h
    L_0044a480:
        cmp edi,ecx
    L_0044a482:
        movsx edi,word ptr [data_00491d5e]
    L_0044a489:
        setge bl
    L_0044a48c:
        xor ecx,ecx
    L_0044a48e:
        dec ebx
    L_0044a48f:
        and ebx,10h
    L_0044a492:
        or edx,ebx
    L_0044a494:
        cmp dword ptr [esp+48h],edi
    L_0044a498:
        mov edi,dword ptr [esp+4Ch]
    L_0044a49c:
        setle cl
    L_0044a49f:
        dec ecx
    L_0044a4a0:
        and ecx,80h
    L_0044a4a6:
        or edx,ecx
    L_0044a4a8:
        xor ecx,ecx
    L_0044a4aa:
        cmp edi,eax
    L_0044a4ac:
        setle cl
    L_0044a4af:
        pop edi
    L_0044a4b0:
        dec ecx
    L_0044a4b1:
        and ecx,20h
    L_0044a4b4:
        or edx,ecx
    L_0044a4b6:
        mov ecx,dword ptr [esp+158h]
    L_0044a4bd:
        or edx,esi
    L_0044a4bf:
        pop esi
    L_0044a4c0:
        xor ecx,ebp
    L_0044a4c2:
        mov ax,dx
    L_0044a4c5:
        pop ebx
    L_0044a4c6:
        call asm_security_check_cookie_00458ea5
    L_0044a4cb:
        mov esp,ebp
    L_0044a4cd:
        pop ebp
    L_0044a4ce:
        ret 8
    }
}
