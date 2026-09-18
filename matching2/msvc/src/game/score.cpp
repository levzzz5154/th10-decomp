#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/game/score.hpp"

extern "C" void* __cdecl memset(void* destination, int value, unsigned int size);


// 0x00408750..0x0040876D: Score_SetPolarVector
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Score_SetPolarVector_00408750() {
    __asm {
    L_00408750:
        push ecx
    L_00408751:
        mov dword ptr [esp],ecx
    L_00408754:
        mov eax,dword ptr [esp]
    L_00408757:
        fld dword ptr [esp+8]
    L_0040875b:
        fsincos
    L_0040875d:
        fmul dword ptr [esp+0Ch]
    L_00408761:
        fstp dword ptr [eax]
    L_00408763:
        fmul dword ptr [esp+0Ch]
    L_00408767:
        fstp dword ptr [eax+4]
    L_0040876a:
        pop ecx
    L_0040876b:
        ret 8
    }
}


// 0x00408D60..0x00408ED9: FUN_00408d60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00408d60_00408d60() {
    __asm {
    L_00408d60:
        mov al,byte ptr [edi+378Ch]
    L_00408d66:
        sub esp,1Ch
    L_00408d69:
        test al,1
    L_00408d6b:
        je asm_target_00409178
    L_00408d71:
        cmp dword ptr [edi+3738h],3Ch
    L_00408d78:
        jl short L_00408d86
    L_00408d7a:
        mov eax,dword ptr [data_004776e8]
    L_00408d7f:
        and dword ptr [eax+2A18h],0FFFFFFFEh
    L_00408d86:
        cmp dword ptr [edi+3738h],12Ch
    L_00408d90:
        push ebx
    L_00408d91:
        push ebp
    L_00408d92:
        push esi
    L_00408d93:
        jl short L_00408de2
    L_00408d95:
        test byte ptr [edi+378Ch],8
    L_00408d9c:
        jne short L_00408de2
    L_00408d9e:
        mov ecx,dword ptr [edi+3794h]
    L_00408da4:
        mov eax,66666667h
    L_00408da9:
        imul ecx
    L_00408dab:
        sar edx,2
    L_00408dae:
        mov eax,edx
    L_00408db0:
        shr eax,1Fh
    L_00408db3:
        add edx,eax
    L_00408db5:
        mov eax,ecx
    L_00408db7:
        mov ecx,dword ptr [edi+3798h]
    L_00408dbd:
        sub eax,edx
    L_00408dbf:
        cdq
    L_00408dc0:
        sub ecx,12Ch
    L_00408dc6:
        idiv ecx
    L_00408dc8:
        mov ecx,dword ptr [edi+3790h]
    L_00408dce:
        mov esi,0Ah
    L_00408dd3:
        sub ecx,eax
    L_00408dd5:
        mov eax,ecx
    L_00408dd7:
        cdq
    L_00408dd8:
        idiv esi
    L_00408dda:
        sub ecx,edx
    L_00408ddc:
        mov dword ptr [edi+3790h],ecx
    L_00408de2:
        lea edx,[edi+10h]
    L_00408de5:
        push edx
    L_00408de6:
        call asm_FUN_0043ee30_0043ee30
    L_00408deb:
        lea eax,[edi+3BCh]
    L_00408df1:
        push eax
    L_00408df2:
        call asm_FUN_0043ee30_0043ee30
    L_00408df7:
        mov edx,dword ptr [edi+3738h]
    L_00408dfd:
        mov ecx,dword ptr [edi+3740h]
    L_00408e03:
        mov dword ptr [edi+3734h],edx
    L_00408e09:
        fld dword ptr [ecx]
    L_00408e0b:
        fcomp dword ptr [data_00470b68]
    L_00408e11:
        fnstsw ax
    L_00408e13:
        test ah,41h
    L_00408e16:
        jne short L_00408e42
    L_00408e18:
        fld dword ptr [ecx]
    L_00408e1a:
        fcomp dword ptr [data_00470b64]
    L_00408e20:
        fnstsw ax
    L_00408e22:
        test ah,5
    L_00408e25:
        jp short L_00408e42
    L_00408e27:
        fld dword ptr [edi+373Ch]
    L_00408e2d:
        inc edx
    L_00408e2e:
        fadd dword ptr [data_00470afc]
    L_00408e34:
        mov dword ptr [edi+3738h],edx
    L_00408e3a:
        fstp dword ptr [edi+373Ch]
    L_00408e40:
        jmp short L_00408e5b
    L_00408e42:
        fld dword ptr [ecx]
    L_00408e44:
        fadd dword ptr [edi+373Ch]
    L_00408e4a:
        fst dword ptr [edi+373Ch]
    L_00408e50:
        call asm_FUN_00463b2c_00463b2c
    L_00408e55:
        mov dword ptr [edi+3738h],eax
    L_00408e5b:
        cmp dword ptr [edi+3738h],78h
    L_00408e62:
        jl asm_target_00408f7c
    L_00408e68:
        test byte ptr [edi+378Ch],4
    L_00408e6f:
        jne asm_target_00408efb
    L_00408e75:
        mov ecx,dword ptr [data_00477834]
    L_00408e7b:
        fld dword ptr [ecx+3C4h]
    L_00408e81:
        fcomp dword ptr [data_00470c80]
    L_00408e87:
        fnstsw ax
    L_00408e89:
        test ah,5
    L_00408e8c:
        jp asm_target_00408f7c
    L_00408e92:
        lea ebp,[edi+768h]
    L_00408e98:
        mov ebx,3
    L_00408e9d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00408ea0:
        mov esi,3
    L_00408ea5:
        mov eax,ebp
    L_00408ea7:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00408eac:
        add ebp,4
    L_00408eaf:
        dec ebx
    L_00408eb0:
        jne short L_00408ea0
    L_00408eb2:
        lea eax,[edi+0A7Ch]
    L_00408eb8:
        mov ecx,8
    L_00408ebd:
        TH10_NOP_LEA_ECX_DISP8()
    L_00408ec0:
        mov word ptr [eax],3
    L_00408ec5:
        add eax,3ACh
    L_00408eca:
        dec ecx
    L_00408ecb:
        jne short L_00408ec0
    L_00408ecd:
        lea eax,[edi+27DCh]
    L_00408ed3:
        mov ecx,5
    L_00408ed8:
        TH10_REL8(0xeb, 0x00408ed8, VA_asm_FUN_00408d60_part_00408ee0)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00408ee0:
        mov word ptr [eax],3
    L_00408ee5:
        add eax,3ACh
    L_00408eea:
        dec ecx
    L_00408eeb:
        jne short L_00408ee0
    L_00408eed:
        mov eax,dword ptr [edi+378Ch]
    L_00408ef3:
        or eax,4
    L_00408ef6:
        jmp asm_target_00408f76
    L_00408efb:
        mov edx,dword ptr [data_00477834]
    L_00408f01:
        fld dword ptr [edx+3C4h]
    L_00408f07:
        fcomp dword ptr [data_00470bf4]
    L_00408f0d:
        fnstsw ax
    L_00408f0f:
        test ah,41h
    L_00408f12:
        TH10_REL8(0x75, 0x00408f12, VA_asm_target_00408f7c)
    L_00408f14:
        lea ebp,[edi+768h]
    L_00408f1a:
        mov ebx,3
    L_00408f1f:
        nop
    L_00408f20:
        mov esi,2
    L_00408f25:
        mov eax,ebp
    L_00408f27:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00408f2c:
        add ebp,4
    L_00408f2f:
        dec ebx
    L_00408f30:
        jne short L_00408f20
    L_00408f32:
        lea eax,[edi+0A7Ch]
    L_00408f38:
        mov ecx,8
    L_00408f3d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00408f40:
        mov word ptr [eax],2
    L_00408f45:
        add eax,3ACh
    L_00408f4a:
        dec ecx
    L_00408f4b:
        jne short L_00408f40
    L_00408f4d:
        lea eax,[edi+27DCh]
    L_00408f53:
        mov ecx,5
    L_00408f58:
        TH10_REL8(0xeb, 0x00408f58, VA_asm_FUN_00408d60_part_00408f60)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00408f60:
        mov word ptr [eax],2
    L_00408f65:
        add eax,3ACh
    L_00408f6a:
        dec ecx
    L_00408f6b:
        jne short L_00408f60
    L_00408f6d:
        mov eax,dword ptr [edi+378Ch]
    L_00408f73:
        and eax,0FFFFFFFBh
    L_00408f76:
        mov dword ptr [edi+378Ch],eax
    L_00408f7c:
        test byte ptr [edi+378Ch],2
    L_00408f83:
        je short L_00408feb
    L_00408f85:
        mov ecx,dword ptr [edi+3790h]
    L_00408f8b:
        mov esi,989680h
    L_00408f90:
        lea ebx,[edi+778h]
    L_00408f96:
        mov dword ptr [esp+0Ch],8
    L_00408f9e:
        mov edi,edi
    L_00408fa0:
        mov eax,ecx
    L_00408fa2:
        cdq
    L_00408fa3:
        idiv esi
    L_00408fa5:
        mov ecx,dword ptr [data_0047770c]
    L_00408fab:
        mov ecx,dword ptr [ecx+9EC8h]
    L_00408fb1:
        mov ebp,edx
    L_00408fb3:
        lea edx,[eax+1Eh]
    L_00408fb6:
        mov eax,ebx
    L_00408fb8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00408fbd:
        push ebx
    L_00408fbe:
        call asm_FUN_0043ee30_0043ee30
    L_00408fc3:
        mov eax,66666667h
    L_00408fc8:
        imul esi
    L_00408fca:
        sar edx,2
    L_00408fcd:
        mov eax,edx
    L_00408fcf:
        shr eax,1Fh
    L_00408fd2:
        add eax,edx
    L_00408fd4:
        mov esi,eax
    L_00408fd6:
        mov eax,dword ptr [esp+0Ch]
    L_00408fda:
        add ebx,3ACh
    L_00408fe0:
        dec eax
    L_00408fe1:
        mov ecx,ebp
    L_00408fe3:
        mov dword ptr [esp+0Ch],eax
    L_00408fe7:
        jne short L_00408fa0
    L_00408fe9:
        jmp short L_0040900f
    L_00408feb:
        mov ecx,dword ptr [data_0047770c]
    L_00408ff1:
        mov ecx,dword ptr [ecx+9EC8h]
    L_00408ff7:
        lea esi,[edi+0ED0h]
    L_00408ffd:
        mov edx,29h
    L_00409002:
        mov eax,esi
    L_00409004:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00409009:
        push esi
    L_0040900a:
        call asm_FUN_0043ee30_0043ee30
    L_0040900f:
        mov eax,dword ptr [data_00474c68]
    L_00409014:
        mov edx,dword ptr [data_00474c6c]
    L_0040901a:
        mov esi,dword ptr [data_0047783c]
    L_00409020:
        lea ecx,[edx+eax*2]
    L_00409023:
        add ecx,eax
    L_00409025:
        mov eax,dword ptr [edi+3788h]
    L_0040902b:
        imul ecx,437Ch
    L_00409031:
        lea edx,[eax+eax*8]
    L_00409034:
        shl edx,4
    L_00409037:
        add ecx,esi
    L_00409039:
        mov eax,dword ptr [edx+ecx+624h]
    L_00409040:
        cmp eax,64h
    L_00409043:
        jl short L_0040904a
    L_00409045:
        mov eax,63h
    L_0040904a:
        cdq
    L_0040904b:
        mov ecx,0Ah
    L_00409050:
        idiv ecx
    L_00409052:
        mov esi,dword ptr [data_0047770c]
    L_00409058:
        mov ecx,dword ptr [esi+9EC8h]
    L_0040905e:
        lea ebx,[edi+24D8h]
    L_00409064:
        mov ebp,edx
    L_00409066:
        lea edx,[eax+1Eh]
    L_00409069:
        mov eax,ebx
    L_0040906b:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00409070:
        mov ecx,dword ptr [esi+9EC8h]
    L_00409076:
        lea edx,[ebp+1Eh]
    L_00409079:
        lea eax,[edi+2884h]
    L_0040907f:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00409084:
        mov eax,dword ptr [data_00474c68]
    L_00409089:
        mov edx,dword ptr [data_00474c6c]
    L_0040908f:
        mov ebp,dword ptr [data_0047783c]
    L_00409095:
        lea ecx,[edx+eax*2]
    L_00409098:
        add ecx,eax
    L_0040909a:
        mov eax,dword ptr [edi+3788h]
    L_004090a0:
        imul ecx,437Ch
    L_004090a6:
        lea edx,[eax+eax*8]
    L_004090a9:
        shl edx,4
    L_004090ac:
        add ecx,ebp
    L_004090ae:
        mov eax,dword ptr [edx+ecx+628h]
    L_004090b5:
        cmp eax,64h
    L_004090b8:
        jl short L_004090bf
    L_004090ba:
        mov eax,63h
    L_004090bf:
        cdq
    L_004090c0:
        mov ecx,0Ah
    L_004090c5:
        idiv ecx
    L_004090c7:
        mov ecx,dword ptr [esi+9EC8h]
    L_004090cd:
        mov ebp,edx
    L_004090cf:
        lea edx,[eax+1Eh]
    L_004090d2:
        lea eax,[edi+2FDCh]
    L_004090d8:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004090dd:
        mov ecx,dword ptr [esi+9EC8h]
    L_004090e3:
        lea edx,[ebp+1Eh]
    L_004090e6:
        lea eax,[edi+3388h]
    L_004090ec:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004090f1:
        mov esi,5
    L_004090f6:
        push ebx
    L_004090f7:
        call asm_FUN_0043ee30_0043ee30
    L_004090fc:
        add ebx,3ACh
    L_00409102:
        dec esi
    L_00409103:
        jne short L_004090f6
    L_00409105:
        mov edx,dword ptr [data_00477704]
    L_0040910b:
        mov eax,dword ptr [edx+10h]
    L_0040910e:
        fld dword ptr [eax+1068h]
    L_00409114:
        lea esi,[edi+379Ch]
    L_0040911a:
        fsub dword ptr [esi]
    L_0040911c:
        add eax,1068h
    L_00409121:
        fld dword ptr [eax+4]
    L_00409124:
        mov edx,dword ptr [data_00491c10]
    L_0040912a:
        fsub dword ptr [esi+4]
    L_0040912d:
        fld dword ptr [eax+8]
    L_00409130:
        fsub dword ptr [esi+8]
    L_00409133:
        fstp dword ptr [esp+18h]
    L_00409137:
        fxch
    L_00409139:
        fmul dword ptr [data_00470c84]
    L_0040913f:
        fstp dword ptr [esp+1Ch]
    L_00409143:
        fmul dword ptr [data_00470c84]
    L_00409149:
        fld dword ptr [esp+18h]
    L_0040914d:
        fmul dword ptr [data_00470c84]
    L_00409153:
        fld dword ptr [esp+1Ch]
    L_00409157:
        fadd dword ptr [esi]
    L_00409159:
        fstp dword ptr [esi]
    L_0040915b:
        fxch
    L_0040915d:
        fadd dword ptr [esi+4]
    L_00409160:
        fstp dword ptr [esi+4]
    L_00409163:
        fadd dword ptr [esi+8]
    L_00409166:
        fstp dword ptr [esi+8]
    L_00409169:
        mov eax,dword ptr [edi+774h]
    L_0040916f:
        push eax
    L_00409170:
        call asm_AnimationManager_SetTranslatedPosition_00449350
    L_00409175:
        pop esi
    L_00409176:
        pop ebp
    L_00409177:
        pop ebx
    L_00409178:
        mov eax,1
    L_0040917d:
        add esp,1Ch
    L_00409180:
        ret
    }
}



// 0x0040AC20..0x0040AC8C: ?UpdateInputState@@
// Advances the sixteen key-repeat counters and then publishes the pressed and
// released edge masks derived from the current and previous key words.
struct KeyRepeatState {
    unsigned char unknown_00[4];
    unsigned short pressed;              // +0x04
    unsigned char unknown_06[0x26];
    unsigned short held_keys;            // +0x2C
    unsigned short previous_keys;        // +0x2E
    unsigned short repeat_flags;         // +0x30
    unsigned short new_press;            // +0x32
    unsigned short new_release;          // +0x34
    unsigned short unknown_36;
    unsigned short repeat_counters[16];  // +0x38
    unsigned short Update();
};
typedef char KeyRepeatState_size_must_be_88[sizeof(KeyRepeatState) == 0x58 ? 1 : -1];

unsigned short KeyRepeatState::Update() {
    unsigned short held = held_keys;
    pressed = 0;
    unsigned short* counter = repeat_counters;
    for (int index = 0; index < 16; ++index) {
        if (held & 1) {
            if (++*counter >= 26) {
                repeat_flags |= 1;
                *counter -= 8;
            }
        } else {
            *counter = 0;
        }
        held >>= 1;
        ++counter;
    }
    unsigned short now = held_keys;
    unsigned short before = previous_keys;
    unsigned short changed = now ^ before;
    new_press = changed & now;
    unsigned short released = changed & ~now;
    new_release = released;
    return released;
}
// 0x0040AD20..0x0040AD40: clamp the requested signed value to the
// counter's current upper bound. Negative requests become UINT_MAX.
unsigned int __fastcall UpdateBoundedCounter(
        unsigned int requested, unsigned int* counter) {
    unsigned int value = counter[2];
    if (value) {
        if ((int)requested >= (int)value)
            --value;
        else
            value = (((int)requested < 0) - 1) & requested;
    } else {
        value = requested;
    }
    *counter = value;
    return value;
}
// 0x0041BEB0..0x0041BECD: FUN_0041beb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041beb0_0041beb0() {
    __asm {
    L_0041beb0:
        push ecx
    L_0041beb1:
        mov dword ptr [esp],ecx
    L_0041beb4:
        mov eax,dword ptr [esp]
    L_0041beb7:
        fld dword ptr [esp+8]
    L_0041bebb:
        fsincos
    L_0041bebd:
        fmul dword ptr [esp+0Ch]
    L_0041bec1:
        fstp dword ptr [eax]
    L_0041bec3:
        fmul dword ptr [esp+0Ch]
    L_0041bec7:
        fstp dword ptr [eax+4]
    L_0041beca:
        pop ecx
    L_0041becb:
        ret 8
    }
}

// 0x0041C1C0..0x0041C282: ScoreExtendedObject_DestroyRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreExtendedObject_DestroyRetail_0041c1c0() {
    __asm {
    L_0041c1c0:
        mov eax,dword ptr [esp+4]
    L_0041c1c4:
        push ebx
    L_0041c1c5:
        mov ebx,dword ptr [data_004660b0]
    L_0041c1cb:
        push ebp
    L_0041c1cc:
        mov ebp,dword ptr [data_004660b4]
    L_0041c1d2:
        push esi
    L_0041c1d3:
        mov esi,dword ptr [eax+8]
    L_0041c1d6:
        test esi,esi
    L_0041c1d8:
        push edi
    L_0041c1d9:
        mov edi,dword ptr [data_00491be4]
    L_0041c1df:
        je short L_0041c204
    L_0041c1e1:
        push 492274h
    L_0041c1e6:
        call ebx
    L_0041c1e8:
        inc byte ptr [data_0049231c]
    L_0041c1ee:
        mov ecx,esi
    L_0041c1f0:
        mov edx,edi
    L_0041c1f2:
        call asm_Scheduler_Remove_00449f60
    L_0041c1f7:
        push 492274h
    L_0041c1fc:
        call ebp
    L_0041c1fe:
        dec byte ptr [data_0049231c]
    L_0041c204:
        mov ecx,dword ptr [esp+14h]
    L_0041c208:
        mov esi,dword ptr [ecx+0Ch]
    L_0041c20b:
        test esi,esi
    L_0041c20d:
        mov edi,dword ptr [data_00491be4]
    L_0041c213:
        je short L_0041c238
    L_0041c215:
        push 492274h
    L_0041c21a:
        call ebx
    L_0041c21c:
        inc byte ptr [data_0049231c]
    L_0041c222:
        mov ecx,esi
    L_0041c224:
        mov edx,edi
    L_0041c226:
        call asm_Scheduler_Remove_00449f60
    L_0041c22b:
        push 492274h
    L_0041c230:
        call ebp
    L_0041c232:
        dec byte ptr [data_0049231c]
    L_0041c238:
        mov edx,dword ptr [esp+14h]
    L_0041c23c:
        mov esi,dword ptr [edx+18h]
    L_0041c23f:
        test esi,esi
    L_0041c241:
        je short L_0041c272
    L_0041c243:
        mov eax,dword ptr [esi]
    L_0041c245:
        mov edi,dword ptr [esi+8]
    L_0041c248:
        mov ecx,esi
    L_0041c24a:
        call dword ptr [eax+10h]
    L_0041c24d:
        mov ecx,dword ptr [esi+4]
    L_0041c250:
        mov edx,dword ptr [esi+8]
    L_0041c253:
        mov dword ptr [ecx+8],edx
    L_0041c256:
        mov eax,dword ptr [esi+8]
    L_0041c259:
        test eax,eax
    L_0041c25b:
        je short L_0041c263
    L_0041c25d:
        mov ecx,dword ptr [esi+4]
    L_0041c260:
        mov dword ptr [eax+4],ecx
    L_0041c263:
        push esi
    L_0041c264:
        call asm_free_004524a1
    L_0041c269:
        add esp,4
    L_0041c26c:
        test edi,edi
    L_0041c26e:
        mov esi,edi
    L_0041c270:
        jne short L_0041c243
    L_0041c272:
        pop edi
    L_0041c273:
        pop esi
    L_0041c274:
        pop ebp
    L_0041c275:
        mov dword ptr [data_0047781c],0
    L_0041c27f:
        pop ebx
    L_0041c280:
        ret 4
    }
}







// 0x0044B010..0x0044B076: ?Input_UpdateKeyboardState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_UpdateKeyboardState_0044b010() {
    __asm {
    L_0044b010:
        push edi
    L_0044b011:
        xor eax,eax
    L_0044b013:
        mov ecx,40h
    L_0044b018:
        mov edi,edx
    L_0044b01a:
        rep stosd
    L_0044b01c:
        mov eax,dword ptr [data_004924fc]
    L_0044b021:
        test eax,eax
    L_0044b023:
        pop edi
    L_0044b024:
        je short L_0044b037
    L_0044b026:
        mov eax,dword ptr [data_00491ff4]
    L_0044b02b:
        test ah,2
    L_0044b02e:
        push edx
    L_0044b02f:
        jne short L_0044b03a
    L_0044b031:
        call dword ptr [data_00466208]
    L_0044b037:
        xor eax,eax
    L_0044b039:
        ret
    L_0044b03a:
        mov eax,dword ptr [data_00491c38]
    L_0044b03f:
        mov ecx,dword ptr [eax]
    L_0044b041:
        push 100h
    L_0044b046:
        push eax
    L_0044b047:
        call dword ptr [ecx+24h]
    L_0044b04a:
        cmp eax,8007001Eh
    L_0044b04f:
        jne short L_0044b062
    L_0044b051:
        mov eax,dword ptr [data_00491c38]
    L_0044b056:
        mov edx,dword ptr [eax]
    L_0044b058:
        push eax
    L_0044b059:
        call dword ptr [edx+1Ch]
    L_0044b05c:
        mov eax,1
    L_0044b061:
        ret
    L_0044b062:
        test eax,eax
    L_0044b064:
        je short L_0044b071
    L_0044b066:
        mov eax,dword ptr [data_00491c38]
    L_0044b06b:
        mov ecx,dword ptr [eax]
    L_0044b06d:
        push eax
    L_0044b06e:
        call dword ptr [ecx+1Ch]
    L_0044b071:
        mov eax,1
    L_0044b076:
        ret
    }
}

// 0x0044B080..0x0044B0CA: ?Input_NormalizeKeyboardState@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Input_NormalizeKeyboardState_0044b080() {
    __asm {
    L_0044b080:
        sub esp,104h
    L_0044b086:
        mov eax,dword ptr [data_00473660]
    L_0044b08b:
        xor eax,esp
    L_0044b08d:
        mov dword ptr [esp+100h],eax
    L_0044b094:
        lea eax,[esp]
    L_0044b097:
        push eax
    L_0044b098:
        call dword ptr [data_00466208]
    L_0044b09e:
        xor eax,eax
    L_0044b0a0:
        and byte ptr [esp+eax],7Fh
    L_0044b0a4:
        inc eax
    L_0044b0a5:
        cmp eax,100h
    L_0044b0aa:
        jl short L_0044b0a0
    L_0044b0ac:
        lea ecx,[esp]
    L_0044b0af:
        push ecx
    L_0044b0b0:
        call dword ptr [data_00466204]
    L_0044b0b6:
        mov ecx,dword ptr [esp+100h]
    L_0044b0bd:
        xor ecx,esp
    L_0044b0bf:
        call asm_security_check_cookie_00458ea5
    L_0044b0c4:
        add esp,104h
    L_0044b0ca:
        ret
    }
}
