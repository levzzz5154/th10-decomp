#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"

// BLOCKED (D3001): closest_byte_count=1454/1454; first_diff=none
// (authoritative probe exact).  The exact dispatch member is preserved;
// readable output is blocked by its this/ECX private state, jump-table
// control flow, and eight private helper ABIs.  variants_tested=retail
// inline-assembly member only; no failed source variant retained.
// next_lever=schema2 caller/callee cluster over FUN_004067D0/FUN_00406240,
// 004073E0, 00408030, 00408750, 0043DD10, 00404F30, 00405410, 00426660,
// and 0043DC90, preserving the command record's ECX receiver and loop state.
// 0x00406D90..0x0040733D: FUN_00406d90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00406d90_00406d90() {
    __asm {
    L_00406d90:
        push ebp
    L_00406d91:
        mov ebp,esp
    L_00406d93:
        and esp,0FFFFFFF8h
    L_00406d96:
        sub esp,210h
    L_00406d9c:
        push ebx
    L_00406d9d:
        push ebp
    L_00406d9e:
        push esi
    L_00406d9f:
        push edi
    L_00406da0:
        mov ebp,ecx
    L_00406da2:
        cmp dword ptr [ebp+45Ch],12h
    L_00406da9:
        jge asm_target_00407336
    L_00406daf:
        nop
    L_00406db0:
        mov edx,dword ptr [ebp+45Ch]
    L_00406db6:
        lea eax,[edx+edx*2]
    L_00406db9:
        mov ecx,dword ptr [ebp+eax*8+474h]
    L_00406dc0:
        lea esi,[ebp+eax*8+464h]
    L_00406dc7:
        xor edi,edi
    L_00406dc9:
        cmp ecx,edi
    L_00406dcb:
        je asm_target_00407336
    L_00406dd1:
        cmp dword ptr [esi+14h],edi
    L_00406dd4:
        jne short L_00406de2
    L_00406dd6:
        cmp dword ptr [ebp+43Ch],edi
    L_00406ddc:
        jne asm_target_00407336
    L_00406de2:
        cmp ecx,80000000h
    L_00406de8:
        jne short L_00406df6
    L_00406dea:
        inc edx
    L_00406deb:
        mov dword ptr [ebp+45Ch],edx
    L_00406df1:
        jmp asm_target_00407329
    L_00406df6:
        mov eax,ecx
    L_00406df8:
        cmp eax,4000h
    L_00406dfd:
        ja asm_target_004070b2
    L_00406e03:
        je asm_target_00407089
    L_00406e09:
        cmp eax,100h
    L_00406e0e:
        ja asm_target_0040703a
    L_00406e14:
        je asm_target_00406f64
    L_00406e1a:
        dec eax
    L_00406e1b:
        cmp eax,7Fh
    L_00406e1e:
        ja asm_target_0040731c
    L_00406e24:
        movzx edx,byte ptr [eax+407354h]
    L_00406e2b:
        jmp dword ptr [edx*4+407340h]
    L_00406e32:
        mov ecx,dword ptr [ebp+43Ch]
    L_00406e38:
        or ecx,1
    L_00406e3b:
        push edi
    L_00406e3c:
        lea eax,[ebp+614h]
    L_00406e42:
        mov dword ptr [ebp+43Ch],ecx
    L_00406e48:
        call asm_Player_SetSchedulerValue_00405410
    L_00406e4d:
        mov dword ptr [ebp+638h],0
    L_00406e57:
        jmp asm_target_0040731c
    L_00406e5c:
        or dword ptr [ebp+43Ch],10h
    L_00406e63:
        mov eax,dword ptr [esi]
    L_00406e65:
        mov dword ptr [ebp+65Ch],eax
    L_00406e6b:
        fld dword ptr [esi+4]
    L_00406e6e:
        fcomp dword ptr [data_00470b50]
    L_00406e74:
        fnstsw ax
    L_00406e76:
        test ah,41h
    L_00406e79:
        jp short L_00406e83
    L_00406e7b:
        fld dword ptr [ebp+3E4h]
    L_00406e81:
        jmp short L_00406ea9
    L_00406e83:
        fld dword ptr [esi+4]
    L_00406e86:
        fcomp dword ptr [data_00470ccc]
    L_00406e8c:
        fnstsw ax
    L_00406e8e:
        test ah,1
    L_00406e91:
        jne short L_00406ea6
    L_00406e93:
        mov ecx,dword ptr [g_player]
    L_00406e99:
        lea eax,[ebp+3B4h]
    L_00406e9f:
        call asm_Entity_AngleFromPoint_00426660
    L_00406ea4:
        jmp short L_00406ea9
    L_00406ea6:
        fld dword ptr [esi+4]
    L_00406ea9:
        push edi
    L_00406eaa:
        fstp dword ptr [ebp+660h]
    L_00406eb0:
        lea eax,[ebp+648h]
    L_00406eb6:
        call asm_Player_SetSchedulerValue_00405410
    L_00406ebb:
        mov ecx,dword ptr [esi+8]
    L_00406ebe:
        mov edx,dword ptr [ebp+65Ch]
    L_00406ec4:
        mov eax,dword ptr [ebp+660h]
    L_00406eca:
        push edx
    L_00406ecb:
        mov dword ptr [ebp+670h],ecx
    L_00406ed1:
        push eax
    L_00406ed2:
        lea ecx,[ebp+664h]
    L_00406ed8:
        call asm_Score_SetPolarVector_00408750
    L_00406edd:
        mov eax,dword ptr [ebp+45Ch]
    L_00406ee3:
        test eax,eax
    L_00406ee5:
        je asm_target_0040731c
    L_00406eeb:
        mov edi,dword ptr [ebp+458h]
    L_00406ef1:
        test edi,edi
    L_00406ef3:
        jl asm_target_0040731c
    L_00406ef9:
        push 0
    L_00406efb:
        mov ecx,492590h
    L_00406f00:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00406f05:
        jmp asm_target_0040731c
    L_00406f0a:
        or dword ptr [ebp+43Ch],20h
    L_00406f11:
        mov ecx,dword ptr [esi]
    L_00406f13:
        mov dword ptr [ebp+690h],ecx
    L_00406f19:
        mov edx,dword ptr [esi+4]
    L_00406f1c:
        push edi
    L_00406f1d:
        lea eax,[ebp+67Ch]
    L_00406f23:
        mov dword ptr [ebp+694h],edx
    L_00406f29:
        call asm_Player_SetSchedulerValue_00405410
    L_00406f2e:
        mov eax,dword ptr [esi+8]
    L_00406f31:
        mov dword ptr [ebp+6A4h],eax
    L_00406f37:
        mov eax,dword ptr [ebp+45Ch]
    L_00406f3d:
        test eax,eax
    L_00406f3f:
        je asm_target_0040731c
    L_00406f45:
        mov edi,dword ptr [ebp+458h]
    L_00406f4b:
        test edi,edi
    L_00406f4d:
        jl asm_target_0040731c
    L_00406f53:
        push 0
    L_00406f55:
        mov ecx,492590h
    L_00406f5a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00406f5f:
        jmp asm_target_0040731c
    L_00406f64:
        mov eax,dword ptr [ebp+43Ch]
    L_00406f6a:
        or eax,ecx
    L_00406f6c:
        mov dword ptr [ebp+43Ch],eax
    L_00406f72:
        fld dword ptr [esi]
    L_00406f74:
        fcomp dword ptr [data_00470b50]
    L_00406f7a:
        fnstsw ax
    L_00406f7c:
        test ah,41h
    L_00406f7f:
        jp short L_00406f89
    L_00406f81:
        fld dword ptr [ebp+3E4h]
    L_00406f87:
        jmp short L_00406fad
    L_00406f89:
        fld dword ptr [esi]
    L_00406f8b:
        fcomp dword ptr [data_00470ccc]
    L_00406f91:
        fnstsw ax
    L_00406f93:
        test ah,1
    L_00406f96:
        jne short L_00406fab
    L_00406f98:
        mov ecx,dword ptr [g_player]
    L_00406f9e:
        lea eax,[ebp+3B4h]
    L_00406fa4:
        call asm_Entity_AngleFromPoint_00426660
    L_00406fa9:
        jmp short L_00406fad
    L_00406fab:
        fld dword ptr [esi]
    L_00406fad:
        fstp dword ptr [ebp+6C8h]
    L_00406fb3:
        fld dword ptr [esi+4]
    L_00406fb6:
        fcomp dword ptr [data_00470cc8]
    L_00406fbc:
        fnstsw ax
    L_00406fbe:
        test ah,41h
    L_00406fc1:
        jne short L_00406fc8
    L_00406fc3:
        fld dword ptr [esi+4]
    L_00406fc6:
        jmp short L_00406fce
    L_00406fc8:
        fld dword ptr [ebp+3D8h]
    L_00406fce:
        fstp dword ptr [ebp+6C4h]
    L_00406fd4:
        mov eax,dword ptr [ebp+6C0h]
    L_00406fda:
        test al,1
    L_00406fdc:
        jne short L_00407007
    L_00406fde:
        or eax,1
    L_00406fe1:
        mov dword ptr [ebp+6B4h],edi
    L_00406fe7:
        mov dword ptr [ebp+6B0h],0FFF0BDC1h
    L_00406ff1:
        mov dword ptr [ebp+6B8h],edi
    L_00406ff7:
        mov dword ptr [ebp+6BCh],476F78h
    L_00407001:
        mov dword ptr [ebp+6C0h],eax
    L_00407007:
        mov dword ptr [ebp+6B4h],edi
    L_0040700d:
        mov dword ptr [ebp+6B8h],edi
    L_00407013:
        mov dword ptr [ebp+6B0h],0FFFFFFFFh
    L_0040701d:
        mov ecx,dword ptr [esi+8]
    L_00407020:
        mov dword ptr [ebp+6D8h],ecx
    L_00407026:
        mov edx,dword ptr [esi+0Ch]
    L_00407029:
        mov dword ptr [ebp+6DCh],edx
    L_0040702f:
        mov dword ptr [ebp+6E0h],edi
    L_00407035:
        jmp asm_target_0040731c
    L_0040703a:
        cmp eax,1000h
    L_0040703f:
        ja short L_00407069
    L_00407041:
        je short L_0040705e
    L_00407043:
        cmp eax,400h
    L_00407048:
        je asm_target_004072ff
    L_0040704e:
        cmp eax,800h
    L_00407053:
        je asm_target_004072ff
    L_00407059:
        jmp asm_target_0040731c
    L_0040705e:
        mov eax,dword ptr [esi+8]
    L_00407061:
        mov dword ptr [ebp+4],eax
    L_00407064:
        jmp asm_target_0040731c
    L_00407069:
        cmp eax,2000h
    L_0040706e:
        jne asm_target_0040731c
    L_00407074:
        mov ecx,dword ptr [esi+8]
    L_00407077:
        inc edx
    L_00407078:
        mov dword ptr [ebp+434h],ecx
    L_0040707e:
        mov dword ptr [ebp+45Ch],edx
    L_00407084:
        jmp asm_target_00407329
    L_00407089:
        mov edx,dword ptr [esi+8]
    L_0040708c:
        mov eax,dword ptr [edx*4+474170h]
    L_00407093:
        mov edx,dword ptr [esi+0Ch]
    L_00407096:
        mov ecx,dword ptr [data_004776f0]
    L_0040709c:
        add eax,edx
    L_0040709e:
        mov edx,dword ptr [ecx+3E0B50h]
    L_004070a4:
        lea esi,[ebp+8]
    L_004070a7:
        push edx
    L_004070a8:
        call asm_FUN_00404f30_00404f30
    L_004070ad:
        jmp asm_target_0040731c
    L_004070b2:
        cmp eax,400000h
    L_004070b7:
        ja asm_target_0040724d
    L_004070bd:
        je asm_target_00407163
    L_004070c3:
        cmp eax,20000h
    L_004070c8:
        ja short L_0040711d
    L_004070ca:
        je short L_00407104
    L_004070cc:
        cmp eax,8000h
    L_004070d1:
        je short L_004070ea
    L_004070d3:
        cmp eax,10000h
    L_004070d8:
        jne asm_target_0040731c
    L_004070de:
        mov esi,ebp
    L_004070e0:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_004070e5:
        jmp asm_target_0040731c
    L_004070ea:
        or dword ptr [ebp+43Ch],ecx
    L_004070f0:
        mov eax,dword ptr [esi+8]
    L_004070f3:
        push eax
    L_004070f4:
        lea eax,[ebp+718h]
    L_004070fa:
        call asm_Player_SetSchedulerValue_00405410
    L_004070ff:
        jmp asm_target_0040731c
    L_00407104:
        mov ecx,dword ptr [ebp+3B4h]
    L_0040710a:
        mov ebx,dword ptr [esi+8]
    L_0040710d:
        push ecx
    L_0040710e:
        mov esi,492590h
    L_00407113:
        call asm_FUN_0043dd10_0043dd10
    L_00407118:
        jmp asm_target_0040731c
    L_0040711d:
        cmp eax,100000h
    L_00407122:
        je short L_00407149
    L_00407124:
        cmp eax,200000h
    L_00407129:
        jne asm_target_0040731c
    L_0040712f:
        or dword ptr [ebp+43Ch],ecx
    L_00407135:
        mov edx,dword ptr [esi+8]
    L_00407138:
        push edx
    L_00407139:
        lea eax,[ebp+780h]
    L_0040713f:
        call asm_Player_SetSchedulerValue_00405410
    L_00407144:
        jmp asm_target_0040731c
    L_00407149:
        or dword ptr [ebp+43Ch],ecx
    L_0040714f:
        mov eax,dword ptr [esi+8]
    L_00407152:
        push eax
    L_00407153:
        lea eax,[ebp+74Ch]
    L_00407159:
        call asm_Player_SetSchedulerValue_00405410
    L_0040715e:
        jmp asm_target_0040731c
    L_00407163:
        xor eax,eax
    L_00407165:
        mov ecx,84h
    L_0040716a:
        lea edi,[esp+10h]
    L_0040716e:
        rep stosd
    L_00407170:
        lea ecx,[ebp+3B4h]
    L_00407176:
        mov eax,dword ptr [ecx]
    L_00407178:
        mov dword ptr [esp+14h],eax
    L_0040717c:
        mov eax,dword ptr [ecx+4]
    L_0040717f:
        mov ecx,dword ptr [ecx+8]
    L_00407182:
        mov dword ptr [esp+18h],eax
    L_00407186:
        mov eax,dword ptr [esi+8]
    L_00407189:
        mov dword ptr [esp+1Ch],ecx
    L_0040718d:
        xor ecx,ecx
    L_0040718f:
        mov ebx,eax
    L_00407191:
        mov word ptr [esp+208h],cx
    L_00407199:
        mov word ptr [esp+10h],cx
    L_0040719e:
        movsx cx,byte ptr [esi+9]
    L_004071a3:
        and eax,0FFh
    L_004071a8:
        mov dword ptr [esp+218h],eax
    L_004071af:
        mov ax,word ptr [esi+0Ch]
    L_004071b3:
        mov word ptr [esp+12h],cx
    L_004071b8:
        mov ecx,dword ptr [esi]
    L_004071ba:
        mov word ptr [esp+204h],ax
    L_004071c2:
        mov eax,dword ptr [esi+4]
    L_004071c5:
        add esi,18h
    L_004071c8:
        mov dword ptr [esp+28h],ecx
    L_004071cc:
        and ebx,80000000h
    L_004071d2:
        inc edx
    L_004071d3:
        mov dword ptr [ebp+45Ch],edx
    L_004071d9:
        mov cx,word ptr [esi+8]
    L_004071dd:
        mov edx,dword ptr [esi+0Ch]
    L_004071e0:
        mov word ptr [esp+206h],cx
    L_004071e8:
        mov ecx,dword ptr [esi+4]
    L_004071eb:
        mov dword ptr [esp+2Ch],eax
    L_004071ef:
        mov eax,dword ptr [esi]
    L_004071f1:
        mov dword ptr [esp+20Ch],edx
    L_004071f8:
        mov edx,dword ptr [data_004776f0]
    L_004071fe:
        mov dword ptr [esp+24h],ecx
    L_00407202:
        mov dword ptr [esp+20h],eax
    L_00407206:
        mov dword ptr [esp+214h],0FFFFFFFFh
    L_00407211:
        lea esi,[ebp+464h]
    L_00407217:
        mov ecx,6Ch
    L_0040721c:
        lea edi,[esp+30h]
    L_00407220:
        push edx
    L_00407221:
        lea eax,[esp+14h]
    L_00407225:
        rep movsd
    L_00407227:
        call asm_EnemyGrid_ScanCellsRetail_004073e0
    L_0040722c:
        mov ecx,dword ptr [ebp+45Ch]
    L_00407232:
        inc ecx
    L_00407233:
        test ebx,ebx
    L_00407235:
        mov dword ptr [ebp+45Ch],ecx
    L_0040723b:
        je asm_target_00407329
    L_00407241:
        mov esi,ebp
    L_00407243:
        call asm_ScoreState_ActivateFromResultRetail_00408030
    L_00407248:
        jmp asm_target_0040731c
    L_0040724d:
        cmp eax,4000000h
    L_00407252:
        ja asm_target_004072f8
    L_00407258:
        je short L_00407289
    L_0040725a:
        cmp eax,1000000h
    L_0040725f:
        je short L_00407274
    L_00407261:
        cmp eax,2000000h
    L_00407266:
        jne asm_target_0040731c
    L_0040726c:
        mov eax,dword ptr [esi+8]
    L_0040726f:
        jmp asm_target_00407323
    L_00407274:
        mov ecx,dword ptr [esi+8]
    L_00407277:
        inc edx
    L_00407278:
        mov dword ptr [ebp+420h],ecx
    L_0040727e:
        mov dword ptr [ebp+45Ch],edx
    L_00407284:
        jmp asm_target_00407329
    L_00407289:
        or dword ptr [ebp+43Ch],4000000h
    L_00407293:
        mov edx,dword ptr [esi]
    L_00407295:
        mov dword ptr [ebp+7C8h],edx
    L_0040729b:
        mov eax,dword ptr [esi+4]
    L_0040729e:
        mov dword ptr [ebp+7CCh],eax
    L_004072a4:
        mov eax,dword ptr [ebp+7C4h]
    L_004072aa:
        test al,1
    L_004072ac:
        jne short L_004072d7
    L_004072ae:
        or eax,1
    L_004072b1:
        mov dword ptr [ebp+7B8h],edi
    L_004072b7:
        mov dword ptr [ebp+7B4h],0FFF0BDC1h
    L_004072c1:
        mov dword ptr [ebp+7BCh],edi
    L_004072c7:
        mov dword ptr [ebp+7C0h],476F78h
    L_004072d1:
        mov dword ptr [ebp+7C4h],eax
    L_004072d7:
        mov dword ptr [ebp+7B8h],edi
    L_004072dd:
        mov dword ptr [ebp+7BCh],edi
    L_004072e3:
        mov dword ptr [ebp+7B4h],0FFFFFFFFh
    L_004072ed:
        mov ecx,dword ptr [esi+8]
    L_004072f0:
        mov dword ptr [ebp+7DCh],ecx
    L_004072f6:
        jmp short L_0040731c
    L_004072f8:
        cmp eax,8000000h
    L_004072fd:
        jne short L_0040731c
    L_004072ff:
        or dword ptr [ebp+43Ch],ecx
    L_00407305:
        mov edx,dword ptr [esi]
    L_00407307:
        mov dword ptr [ebp+6F8h],edx
    L_0040730d:
        mov eax,dword ptr [esi+8]
    L_00407310:
        mov dword ptr [ebp+710h],eax
    L_00407316:
        mov dword ptr [ebp+70Ch],edi
    L_0040731c:
        mov eax,dword ptr [ebp+45Ch]
    L_00407322:
        inc eax
    L_00407323:
        mov dword ptr [ebp+45Ch],eax
    L_00407329:
        cmp dword ptr [ebp+45Ch],12h
    L_00407330:
        jl asm_target_00406db0
    L_00407336:
        pop edi
    L_00407337:
        pop esi
    L_00407338:
        pop ebp
    L_00407339:
        pop ebx
    L_0040733a:
        mov esp,ebp
    L_0040733c:
        pop ebp
    L_0040733d:
        ret
    L_0040733e:
        _emit 0x8b
        _emit 0xff
    L_00407340:
        _emit 0x32
        _emit 0x6e
        _emit 0x40
        _emit 0x00
        _emit 0x5c
        _emit 0x6e
        _emit 0x40
        _emit 0x00
        _emit 0x0a
        _emit 0x6f
        _emit 0x40
        _emit 0x00
        _emit 0x64
        _emit 0x6f
        _emit 0x40
        _emit 0x00
        _emit 0x1c
        _emit 0x73
        _emit 0x40
        _emit 0x00
        _emit 0x00
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x01
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x02
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x03
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x04
        _emit 0x03
    }
}
