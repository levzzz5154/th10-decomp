#include "asm_encoding.hpp"
#include "asm_symbols.hpp"





// 0x0043DDF0..0x0043DE24: FUN_0043ddf0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ddf0_0043ddf0() {
    __asm {
    L_0043ddf0:
        sub esp,0Ch
    L_0043ddf3:
        push ebp
    L_0043ddf4:
        mov ebp,dword ptr [esp+14h]
    L_0043ddf8:
        mov eax,dword ptr [ebp+610h]
    L_0043ddfe:
        test eax,eax
    L_0043de00:
        jne short L_0043de0b
    L_0043de02:
        xor eax,eax
    L_0043de04:
        pop ebp
    L_0043de05:
        add esp,0Ch
    L_0043de08:
        ret 4
    L_0043de0b:
        push ebx
    L_0043de0c:
        push edi
    L_0043de0d:
        lea ebx,[ebp+1F88h]
    L_0043de13:
        mov dword ptr [esp+10h],ebx
    L_0043de17:
        push esi
    L_0043de18:
        mov eax,dword ptr [ebx]
    L_0043de1a:
        dec eax
    L_0043de1b:
        cmp eax,7
    L_0043de1e:
        mov edi,1
    L_0043de23:
        TH10_REL8(0xeb, 0x0043de23, VA_asm_FUN_0043ddf0_part_0043de30)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x64
        _emit 0x24
        _emit 0x00

    L_0043de30:
        mov dword ptr [esp+20h],0
    L_0043de38:
        ja asm_target_0043e212
    L_0043de3e:
        jmp dword ptr [eax*4+43E37Ch]
    L_0043de45:
        mov eax,dword ptr [ebp+5208h]
    L_0043de4b:
        test eax,eax
    L_0043de4d:
        je asm_target_0043e0e5
    L_0043de53:
        mov ecx,dword ptr [ebp+52C4h]
    L_0043de59:
        push ecx
    L_0043de5a:
        call asm_Platform_SetOperationDeadline_0044d4e0
    L_0043de5f:
        jmp asm_target_0043e0e5
    L_0043de64:
        test byte ptr [data_00491d78],10h
    L_0043de6b:
        je short L_0043de94
    L_0043de6d:
        mov eax,dword ptr [ebx+8]
    L_0043de70:
        test eax,eax
    L_0043de72:
        jne asm_target_0043e20f
    L_0043de78:
        mov esi,ebp
    L_0043de7a:
        call asm_MidiWorker_StopRetail_0043dab0
    L_0043de7f:
        mov edx,dword ptr [ebx+4]
    L_0043de82:
        lea eax,[ebx+0Ch]
    L_0043de85:
        push edx
    L_0043de86:
        call asm_FUN_0043d7d0_0043d7d0
    L_0043de8b:
        mov dword ptr [esp+20h],edi
    L_0043de8f:
        jmp asm_target_0043e0e5
    L_0043de94:
        mov ecx,dword ptr [ebx+4]
    L_0043de97:
        lea eax,[ebx+0Ch]
    L_0043de9a:
        push ecx
    L_0043de9b:
        mov esi,ebp
    L_0043de9d:
        call asm_FUN_0043d7d0_0043d7d0
    L_0043dea2:
        mov dword ptr [esp+20h],edi
    L_0043dea6:
        jmp asm_target_0043e0e5
    L_0043deab:
        test byte ptr [data_00491d78],10h
    L_0043deb2:
        je asm_target_0043df6b
    L_0043deb8:
        mov eax,dword ptr [ebx+4]
    L_0043debb:
        test eax,eax
    L_0043debd:
        jl asm_target_0043df6b
    L_0043dec3:
        mov ecx,dword ptr [ebx+8]
    L_0043dec6:
        test ecx,ecx
    L_0043dec8:
        jne short L_0043dede
    L_0043deca:
        mov esi,ebp
    L_0043decc:
        call asm_FUN_0043d950_0043d950
    L_0043ded1:
        test eax,eax
    L_0043ded3:
        je asm_target_0043e20f
    L_0043ded9:
        jmp asm_target_0043e0e5
    L_0043dede:
        cmp ecx,2
    L_0043dee1:
        jne short L_0043df03
    L_0043dee3:
        mov edi,dword ptr [ebp+5208h]
    L_0043dee9:
        test edi,edi
    L_0043deeb:
        je asm_target_0043e20f
    L_0043def1:
        call asm_Streamer_RestartRetail_0044dad0
    L_0043def6:
        test eax,eax
    L_0043def8:
        jge asm_target_0043e20f
    L_0043defe:
        jmp asm_target_0043e0e5
    L_0043df03:
        cmp ecx,5
    L_0043df06:
        jne short L_0043df54
    L_0043df08:
        mov eax,dword ptr [ebp+5208h]
    L_0043df0e:
        mov ecx,dword ptr [eax+4]
    L_0043df11:
        test ecx,ecx
    L_0043df13:
        je short L_0043df22
    L_0043df15:
        mov edx,dword ptr [eax+10h]
    L_0043df18:
        test edx,edx
    L_0043df1a:
        ja short L_0043df20
    L_0043df1c:
        xor ecx,ecx
    L_0043df1e:
        jmp short L_0043df22
    L_0043df20:
        mov ecx,dword ptr [ecx]
    L_0043df22:
        mov edx,dword ptr [eax+0Ch]
    L_0043df25:
        mov eax,dword ptr [edx+90h]
    L_0043df2b:
        mov edi,dword ptr [eax+1Ch]
    L_0043df2e:
        xor edx,edx
    L_0043df30:
        test edi,edi
    L_0043df32:
        setne dl
    L_0043df35:
        mov eax,edx
    L_0043df37:
        push eax
    L_0043df38:
        push ecx
    L_0043df39:
        mov dword ptr [ebx+4],eax
    L_0043df3c:
        mov eax,dword ptr [ebp+5208h]
    L_0043df42:
        call asm_Streamer_FillBufferRetail_0044d110
    L_0043df47:
        test eax,eax
    L_0043df49:
        jge asm_target_0043e20f
    L_0043df4f:
        jmp asm_target_0043e0e5
    L_0043df54:
        cmp ecx,7
    L_0043df57:
        je asm_target_0043e17a
    L_0043df5d:
        cmp ecx,14h
    L_0043df60:
        jl asm_target_0043e20f
    L_0043df66:
        jmp asm_target_0043e0e5
    L_0043df6b:
        mov ecx,dword ptr [ebp+5208h]
    L_0043df71:
        test ecx,ecx
    L_0043df73:
        je asm_target_0043e0e5
    L_0043df79:
        mov eax,dword ptr [ebx+8]
    L_0043df7c:
        test eax,eax
    L_0043df7e:
        je asm_target_0043e204
    L_0043df84:
        cmp eax,edi
    L_0043df86:
        je asm_target_0043e123
    L_0043df8c:
        cmp eax,2
    L_0043df8f:
        je asm_target_0043e13e
    L_0043df95:
        cmp eax,3
    L_0043df98:
        jne short L_0043dfd9
    L_0043df9a:
        mov eax,dword ptr [ecx+4]
    L_0043df9d:
        test eax,eax
    L_0043df9f:
        jne short L_0043dfa5
    L_0043dfa1:
        xor esi,esi
    L_0043dfa3:
        jmp short L_0043dfb2
    L_0043dfa5:
        mov edx,dword ptr [ecx+10h]
    L_0043dfa8:
        test edx,edx
    L_0043dfaa:
        ja short L_0043dfb0
    L_0043dfac:
        xor esi,esi
    L_0043dfae:
        jmp short L_0043dfb2
    L_0043dfb0:
        mov esi,dword ptr [eax]
    L_0043dfb2:
        mov edi,ecx
    L_0043dfb4:
        call asm_Streamer_RestartRetail_0044dad0
    L_0043dfb9:
        mov eax,dword ptr [ebp+5208h]
    L_0043dfbf:
        mov ecx,dword ptr [eax+0Ch]
    L_0043dfc2:
        mov edx,dword ptr [ecx+90h]
    L_0043dfc8:
        mov ecx,dword ptr [edx+1Ch]
    L_0043dfcb:
        xor eax,eax
    L_0043dfcd:
        test ecx,ecx
    L_0043dfcf:
        setne al
    L_0043dfd2:
        push eax
    L_0043dfd3:
        push esi
    L_0043dfd4:
        jmp asm_target_0043df39
    L_0043dfd9:
        cmp eax,4
    L_0043dfdc:
        je asm_target_0043e17a
    L_0043dfe2:
        cmp eax,7
    L_0043dfe5:
        jl asm_target_0043e20f
    L_0043dfeb:
        jmp asm_target_0043e0e5
    L_0043dff0:
        mov eax,dword ptr [ebp+5208h]
    L_0043dff6:
        test eax,eax
    L_0043dff8:
        je asm_target_0043e0e5
    L_0043dffe:
        mov eax,dword ptr [ebx+8]
    L_0043e001:
        test eax,eax
    L_0043e003:
        je asm_target_0043e204
    L_0043e009:
        cmp eax,edi
    L_0043e00b:
        jne short L_0043e033
    L_0043e00d:
        mov eax,dword ptr [ebp+618h]
    L_0043e013:
        test eax,eax
    L_0043e015:
        je asm_target_0043e0e5
    L_0043e01b:
        mov ecx,dword ptr [ebp+614h]
    L_0043e021:
        push 0
    L_0043e023:
        push 0
    L_0043e025:
        push 12h
    L_0043e027:
        push ecx
    L_0043e028:
        call dword ptr [data_00466210]
    L_0043e02e:
        jmp asm_target_0043e20f
    L_0043e033:
        cmp eax,2
    L_0043e036:
        je asm_target_0043e18d
    L_0043e03c:
        cmp eax,3
    L_0043e03f:
        je asm_target_0043e1c7
    L_0043e045:
        cmp eax,0Ah
    L_0043e048:
        jne asm_target_0043e20f
    L_0043e04e:
        jmp asm_target_0043e0e5
    L_0043e053:
        mov eax,dword ptr [ebp+5208h]
    L_0043e059:
        test eax,eax
    L_0043e05b:
        je asm_target_0043e0e5
    L_0043e061:
        mov eax,dword ptr [ebx+8]
    L_0043e064:
        test eax,eax
    L_0043e066:
        je asm_target_0043e204
    L_0043e06c:
        cmp eax,edi
    L_0043e06e:
        jne asm_target_0043e20f
    L_0043e074:
        jmp short L_0043e0e5
    L_0043e076:
        mov esi,dword ptr [data_00497798]
    L_0043e07c:
        fild dword ptr [ebx+4]
    L_0043e07f:
        test esi,esi
    L_0043e081:
        je short L_0043e0e3
    L_0043e083:
        fmul dword ptr [data_00470b1c]
    L_0043e089:
        mov dword ptr [esi+1Ch],edi
    L_0043e08c:
        call asm_FUN_00463b2c_00463b2c
    L_0043e091:
        mov dword ptr [esi+14h],eax
    L_0043e094:
        mov dword ptr [esi+18h],eax
    L_0043e097:
        jmp short L_0043e0e5
    L_0043e099:
        cmp byte ptr [data_00491d63],1
    L_0043e0a0:
        jne short L_0043e0e5
    L_0043e0a2:
        mov ecx,dword ptr [ebp+5208h]
    L_0043e0a8:
        mov eax,dword ptr [ecx+74h]
    L_0043e0ab:
        test eax,eax
    L_0043e0ad:
        jne asm_target_0043e212
    L_0043e0b3:
        test ecx,ecx
    L_0043e0b5:
        je short L_0043e0e5
    L_0043e0b7:
        call asm_Platform_InvokeInterface_0044d5b0
    L_0043e0bc:
        jmp short L_0043e0e5
    L_0043e0be:
        cmp byte ptr [data_00491d63],1
    L_0043e0c5:
        jne short L_0043e0e5
    L_0043e0c7:
        mov eax,dword ptr [ebp+5208h]
    L_0043e0cd:
        mov ecx,dword ptr [eax+74h]
    L_0043e0d0:
        test ecx,ecx
    L_0043e0d2:
        jne asm_target_0043e212
    L_0043e0d8:
        test eax,eax
    L_0043e0da:
        je short L_0043e0e5
    L_0043e0dc:
        call asm_Platform_InvokeConfigured_0044d5d0
    L_0043e0e1:
        jmp short L_0043e0e5
    L_0043e0e3:
        fstp st(0)
    L_0043e0e5:
        xor eax,eax
    L_0043e0e7:
        lea edx,[ebx+10Ch]
    L_0043e0ed:
        TH10_NOP_LEA_ECX_DISP8()
    L_0043e0f0:
        cmp dword ptr [ebx],0
    L_0043e0f3:
        je short L_0043e112
    L_0043e0f5:
        mov esi,edx
    L_0043e0f7:
        mov edi,ebx
    L_0043e0f9:
        inc eax
    L_0043e0fa:
        mov ecx,43h
    L_0043e0ff:
        add ebx,10Ch
    L_0043e105:
        add edx,10Ch
    L_0043e10b:
        cmp eax,1Fh
    L_0043e10e:
        rep movsd
    L_0043e110:
        jl short L_0043e0f0
    L_0043e112:
        mov eax,dword ptr [esp+20h]
    L_0043e116:
        test eax,eax
    L_0043e118:
        je asm_target_0043e212
    L_0043e11e:
        jmp asm_target_0043de18
    L_0043e123:
        mov esi,dword ptr [ebp+5208h]
    L_0043e129:
        mov eax,dword ptr [esi+74h]
    L_0043e12c:
        test eax,eax
    L_0043e12e:
        jne asm_target_0043e212
    L_0043e134:
        call asm_FUN_0044cf20_0044cf20
    L_0043e139:
        jmp asm_target_0043e20f
    L_0043e13e:
        mov eax,dword ptr [ebx+4]
    L_0043e141:
        test eax,eax
    L_0043e143:
        jl short L_0043e151
    L_0043e145:
        shl eax,8
    L_0043e148:
        lea ecx,[eax+ebp+4108h]
    L_0043e14f:
        jmp short L_0043e154
    L_0043e151:
        lea ecx,[ebx+0Ch]
    L_0043e154:
        push ebp
    L_0043e155:
        call asm_Path_FindBasenameSlot_0043d2a0
    L_0043e15a:
        mov ecx,eax
    L_0043e15c:
        mov eax,dword ptr [ebp+1F84h]
    L_0043e162:
        imul ecx,34h
    L_0043e165:
        add ecx,eax
    L_0043e167:
        mov eax,dword ptr [ebp+5208h]
    L_0043e16d:
        mov esi,dword ptr [eax+0Ch]
    L_0043e170:
        call asm_Platform_SelectStreamRecord_0044dca0
    L_0043e175:
        jmp asm_target_0043e20f
    L_0043e17a:
        mov eax,dword ptr [ebp+5208h]
    L_0043e180:
        push edi
    L_0043e181:
        push 0
    L_0043e183:
        call asm_SoundStream_Start_0044d440
    L_0043e188:
        jmp asm_target_0043e20f
    L_0043e18d:
        mov edx,dword ptr [ebp+618h]
    L_0043e193:
        push 100h
    L_0043e198:
        push edx
    L_0043e199:
        call dword ptr [data_0046611c]
    L_0043e19f:
        test eax,eax
    L_0043e1a1:
        je short L_0043e1bb
    L_0043e1a3:
        mov eax,dword ptr [ebp+614h]
    L_0043e1a9:
        push 0
    L_0043e1ab:
        push 0
    L_0043e1ad:
        push 12h
    L_0043e1af:
        push eax
    L_0043e1b0:
        call dword ptr [data_00466210]
    L_0043e1b6:
        dec dword ptr [ebx+8]
    L_0043e1b9:
        jmp short L_0043e20f
    L_0043e1bb:
        mov dword ptr [ebp+618h],0
    L_0043e1c5:
        jmp short L_0043e20f
    L_0043e1c7:
        mov ecx,dword ptr [ebp+618h]
    L_0043e1cd:
        mov esi,dword ptr [data_004660cc]
    L_0043e1d3:
        push ecx
    L_0043e1d4:
        call esi
    L_0043e1d6:
        mov edx,dword ptr [ebp+520Ch]
    L_0043e1dc:
        push edx
    L_0043e1dd:
        call esi
    L_0043e1df:
        mov ecx,dword ptr [ebp+5208h]
    L_0043e1e5:
        xor esi,esi
    L_0043e1e7:
        cmp ecx,esi
    L_0043e1e9:
        mov dword ptr [ebp+618h],esi
    L_0043e1ef:
        je short L_0043e1fc
    L_0043e1f1:
        mov eax,dword ptr [ecx]
    L_0043e1f3:
        push edi
    L_0043e1f4:
        call dword ptr [eax]
    L_0043e1f6:
        mov dword ptr [ebp+5208h],esi
    L_0043e1fc:
        mov dword ptr [ebp+5208h],esi
    L_0043e202:
        jmp short L_0043e20f
    L_0043e204:
        mov edi,dword ptr [ebp+5208h]
    L_0043e20a:
        call asm_Platform_AggregateInterfaces_0044d550
    L_0043e20f:
        inc dword ptr [ebx+8]
    L_0043e212:
        mov al,byte ptr [data_00491d64]
    L_0043e217:
        test al,al
    L_0043e219:
        jne short L_0043e22b
    L_0043e21b:
        mov ecx,dword ptr [esp+14h]
    L_0043e21f:
        mov eax,dword ptr [ecx]
    L_0043e221:
        pop esi
    L_0043e222:
        pop edi
    L_0043e223:
        pop ebx
    L_0043e224:
        pop ebp
    L_0043e225:
        add esp,0Ch
    L_0043e228:
        ret 4
    L_0043e22b:
        lea edx,[ebp+680h]
    L_0043e231:
        mov dword ptr [esp+10h],0
    L_0043e239:
        lea ebx,[ebp+650h]
    L_0043e23f:
        mov dword ptr [esp+20h],edx
    L_0043e243:
        mov esi,dword ptr [ebx-30h]
    L_0043e246:
        test esi,esi
    L_0043e248:
        jl asm_target_0043e36b
    L_0043e24e:
        mov edi,dword ptr [ebx]
    L_0043e250:
        test edi,edi
    L_0043e252:
        mov dword ptr [ebx-30h],0FFFFFFFFh
    L_0043e259:
        jge short L_0043e279
    L_0043e25b:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e262:
        test eax,eax
    L_0043e264:
        je short L_0043e26e
    L_0043e266:
        mov esi,eax
    L_0043e268:
        mov eax,dword ptr [esi]
    L_0043e26a:
        push esi
    L_0043e26b:
        call dword ptr [eax+48h]
    L_0043e26e:
        mov dword ptr [ebx],0
    L_0043e274:
        jmp asm_target_0043e348
    L_0043e279:
        xor eax,eax
    L_0043e27b:
        test edi,edi
    L_0043e27d:
        jle short L_0043e28d
    L_0043e27f:
        mov ecx,dword ptr [esp+20h]
    L_0043e283:
        mov edx,dword ptr [ebx]
    L_0043e285:
        add eax,dword ptr [ecx]
    L_0043e287:
        add ecx,4
    L_0043e28a:
        dec edx
    L_0043e28b:
        jne short L_0043e285
    L_0043e28d:
        cdq
    L_0043e28e:
        idiv edi
    L_0043e290:
        mov dword ptr [ebx],0
    L_0043e296:
        mov edi,eax
    L_0043e298:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e29f:
        test eax,eax
    L_0043e2a1:
        je asm_target_0043e348
    L_0043e2a7:
        mov ecx,dword ptr [eax]
    L_0043e2a9:
        push eax
    L_0043e2aa:
        call dword ptr [ecx+48h]
    L_0043e2ad:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e2b4:
        mov edx,dword ptr [eax]
    L_0043e2b6:
        push 0
    L_0043e2b8:
        push eax
    L_0043e2b9:
        call dword ptr [edx+34h]
    L_0043e2bc:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e2c3:
        mov ecx,dword ptr [eax]
    L_0043e2c5:
        push edi
    L_0043e2c6:
        push eax
    L_0043e2c7:
        call dword ptr [ecx+40h]
    L_0043e2ca:
        mov eax,dword ptr [data_00497858]
    L_0043e2cf:
        test eax,eax
    L_0043e2d1:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e2d8:
        je short L_0043e32a
    L_0043e2da:
        fild dword ptr [data_00497858]
    L_0043e2e0:
        movsx edx,word ptr [esi*8+4749CCh]
    L_0043e2e8:
        mov edi,dword ptr [eax]
    L_0043e2ea:
        add edx,1388h
    L_0043e2f0:
        fmul dword ptr [data_00470b00]
    L_0043e2f6:
        mov dword ptr [esp+18h],edx
    L_0043e2fa:
        fsubr dword ptr [data_00470afc]
    L_0043e300:
        fld st(0)
    L_0043e302:
        fmul st,st(1)
    L_0043e304:
        fmul st,st(1)
    L_0043e306:
        fsubr dword ptr [data_00470afc]
    L_0043e30c:
        fimul dword ptr [esp+18h]
    L_0043e310:
        call asm_FUN_00463b2c_00463b2c
    L_0043e315:
        fstp st(0)
    L_0043e317:
        sub eax,1388h
    L_0043e31c:
        push eax
    L_0043e31d:
        mov eax,dword ptr [ebp+esi*4+208h]
    L_0043e324:
        push eax
    L_0043e325:
        call dword ptr [edi+3Ch]
    L_0043e328:
        jmp short L_0043e335
    L_0043e32a:
        mov ecx,dword ptr [eax]
    L_0043e32c:
        push 0FFFFD8F0h
    L_0043e331:
        push eax
    L_0043e332:
        call dword ptr [ecx+3Ch]
    L_0043e335:
        mov esi,dword ptr [ebp+esi*4+208h]
    L_0043e33c:
        mov edx,dword ptr [esi]
    L_0043e33e:
        push 0
    L_0043e340:
        push 0
    L_0043e342:
        push 0
    L_0043e344:
        push esi
    L_0043e345:
        call dword ptr [edx+30h]
    L_0043e348:
        mov eax,dword ptr [esp+10h]
    L_0043e34c:
        mov edx,dword ptr [esp+20h]
    L_0043e350:
        inc eax
    L_0043e351:
        add edx,200h
    L_0043e357:
        add ebx,4
    L_0043e35a:
        cmp eax,0Ch
    L_0043e35d:
        mov dword ptr [esp+10h],eax
    L_0043e361:
        mov dword ptr [esp+20h],edx
    L_0043e365:
        jl asm_target_0043e243
    L_0043e36b:
        mov eax,dword ptr [esp+14h]
    L_0043e36f:
        mov eax,dword ptr [eax]
    L_0043e371:
        pop esi
    L_0043e372:
        pop edi
    L_0043e373:
        pop ebx
    L_0043e374:
        pop ebp
    L_0043e375:
        add esp,0Ch
    L_0043e378:
        ret 4
        _emit 0x90
        _emit 0x64
        _emit 0xde
        _emit 0x43
        _emit 0x00
        _emit 0xab
        _emit 0xde
        _emit 0x43
        _emit 0x00
        _emit 0x53
        _emit 0xe0
        _emit 0x43
        _emit 0x00
        _emit 0xf0
        _emit 0xdf
        _emit 0x43
        _emit 0x00
        _emit 0x76
        _emit 0xe0
        _emit 0x43
        _emit 0x00
        _emit 0x99
        _emit 0xe0
        _emit 0x43
        _emit 0x00
        _emit 0xbe
        _emit 0xe0
        _emit 0x43
        _emit 0x00
        _emit 0x45
        _emit 0xde
        _emit 0x43
        _emit 0x00
    }
}




