// BLOCKED (D3402): closest_byte_count=0/450; first_diff=unmeasured
// residual_class=abi/cluster; the readable state-machine candidate compiled to
// 501 bytes because retail enters with the replay object in ESI, the filename
// in the stack slot, and private helper calls carrying EAX/EDI/EBP roles.
// variants_tested=archived ReplayArchive_Load semantic body with raw-offset
// state model and direct helper declarations; standalone MSVC 13.10 probe.
// next_lever=build a real-caller LTCG cluster with replay bootstrap callers
// and preserve the ESI entry plus private helper register conventions.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A200..0x0042A32C: FUN_0042a200
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a200_0042a200() {
    __asm {
    L_0042a200:
        sub esp,108h
    L_0042a206:
        mov eax,dword ptr [data_00473660]
    L_0042a20b:
        xor eax,esp
    L_0042a20d:
        mov dword ptr [esp+104h],eax
    L_0042a214:
        mov eax,dword ptr [esp+10Ch]
    L_0042a21b:
        mov edx,esi
    L_0042a21d:
        push ebp
    L_0042a21e:
        sub edx,eax
    L_0042a220:
        push edi
    L_0042a221:
        mov ecx,eax
    L_0042a223:
        lea edi,[edx+1D4h]
    L_0042a229:
        lea esp,[esp+force_disp32_zero]
    L_0042a230:
        mov dl,byte ptr [ecx]
    L_0042a232:
        mov byte ptr [edi+ecx],dl
    L_0042a235:
        inc ecx
    L_0042a236:
        test dl,dl
    L_0042a238:
        jne short L_0042a230
    L_0042a23a:
        test byte ptr [data_00474ca0],20h
    L_0042a241:
        jne short L_0042a2ac
    L_0042a243:
        push eax
    L_0042a244:
        lea eax,[esp+10h]
    L_0042a248:
        push 46E644h
    L_0042a24d:
        push eax
    L_0042a24e:
        call asm_sprintf_00452ae8
    L_0042a253:
        add esp,0Ch
    L_0042a256:
        lea ecx,[esp+0Ch]
    L_0042a25a:
        push ecx
    L_0042a25b:
        call asm_File_ProbeExists_0044b4d0
    L_0042a260:
        test eax,eax
    L_0042a262:
        je short L_0042a293
    L_0042a264:
        lea edx,[esp+0Ch]
    L_0042a268:
        push edx
    L_0042a269:
        call asm_File_OpenSharedRead_0044b6b0
    L_0042a26e:
        test eax,eax
    L_0042a270:
        jne short L_0042a293
    L_0042a272:
        mov edi,24h
    L_0042a277:
        call asm_File_ReadShared_0044b790
    L_0042a27c:
        mov dword ptr [esi+14h],eax
    L_0042a27f:
        cmp dword ptr [eax],72303174h
    L_0042a285:
        jne short L_0042a28e
    L_0042a287:
        cmp word ptr [eax+4],5
    L_0042a28c:
        je short L_0042a29b
    L_0042a28e:
        call asm_File_CloseProbeHandle_0044b7e0
    L_0042a293:
        or eax,0FFFFFFFFh
    L_0042a296:
        jmp asm_target_0042a3a9
    L_0042a29b:
        mov edi,dword ptr [eax+1Ch]
    L_0042a29e:
        call asm_File_ReadShared_0044b790
    L_0042a2a3:
        mov ebp,eax
    L_0042a2a5:
        call asm_File_CloseProbeHandle_0044b7e0
    L_0042a2aa:
        jmp short L_0042a2be
    L_0042a2ac:
        push 0
    L_0042a2ae:
        lea ecx,[esp+0Ch]
    L_0042a2b2:
        push ecx
    L_0042a2b3:
        call asm_FUN_0044b360_0044b360
    L_0042a2b8:
        mov dword ptr [esi+14h],eax
    L_0042a2bb:
        lea ebp,[eax+24h]
    L_0042a2be:
        mov edx,dword ptr [esi+14h]
    L_0042a2c1:
        mov eax,dword ptr [edx+20h]
    L_0042a2c4:
        push eax
    L_0042a2c5:
        call asm_malloc_00452706
    L_0042a2ca:
        mov dword ptr [esi+1C0h],eax
    L_0042a2d0:
        mov eax,dword ptr [esi+14h]
    L_0042a2d3:
        mov eax,dword ptr [eax+1Ch]
    L_0042a2d6:
        add esp,4
    L_0042a2d9:
        push eax
    L_0042a2da:
        push 400h
    L_0042a2df:
        push 0E1h
    L_0042a2e4:
        push eax
    L_0042a2e5:
        push ebp
    L_0042a2e6:
        mov al,0AAh
    L_0042a2e8:
        call asm_DecryptDatBuffer_0044b0d0
    L_0042a2ed:
        mov ecx,dword ptr [esi+14h]
    L_0042a2f0:
        mov eax,dword ptr [ecx+1Ch]
    L_0042a2f3:
        push eax
    L_0042a2f4:
        push 80h
    L_0042a2f9:
        push 7Ah
    L_0042a2fb:
        push eax
    L_0042a2fc:
        push ebp
    L_0042a2fd:
        mov al,3Dh
    L_0042a2ff:
        call asm_DecryptDatBuffer_0044b0d0
    L_0042a304:
        mov eax,dword ptr [esi+14h]
    L_0042a307:
        mov edx,dword ptr [eax+20h]
    L_0042a30a:
        mov ecx,dword ptr [esi+1C0h]
    L_0042a310:
        push edx
    L_0042a311:
        mov edx,dword ptr [eax+1Ch]
    L_0042a314:
        push ecx
    L_0042a315:
        push edx
    L_0042a316:
        push ebp
    L_0042a317:
        call asm_DecompressDatLzss_00435dc0
    L_0042a31c:
        mov eax,dword ptr [esi+1C0h]
    L_0042a322:
        mov dword ptr [esi+18h],eax
    L_0042a325:
        add eax,64h
    L_0042a328:
        xor edi,edi
    L_0042a32a:
        push ebx
    L_0042a32b:
        TH10_REL8(0xeb, 0x0042a32b, VA_asm_FUN_0042a200_part_0042a330)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0042a330:
        mov ecx,dword ptr [esi+18h]
    L_0042a333:
        mov ecx,dword ptr [ecx+4Ch]
    L_0042a336:
        cmp ecx,8
    L_0042a339:
        jl short L_0042a340
    L_0042a33b:
        mov ecx,6
    L_0042a340:
        cmp edi,ecx
    L_0042a342:
        jge short L_0042a390
    L_0042a344:
        movsx ecx,word ptr [eax]
    L_0042a347:
        lea edx,[ecx+ecx*8]
    L_0042a34a:
        mov dword ptr [esi+edx*4+0B0h],eax
    L_0042a351:
        movsx ecx,word ptr [eax]
    L_0042a354:
        lea ecx,[ecx+ecx*8]
    L_0042a357:
        lea edx,[eax+1C4h]
    L_0042a35d:
        mov dword ptr [esi+ecx*4+0A0h],edx
    L_0042a364:
        movsx ecx,word ptr [eax]
    L_0042a367:
        lea edx,[ecx+ecx*8]
    L_0042a36a:
        mov ebx,dword ptr [esi+edx*4+0A0h]
    L_0042a371:
        lea ecx,[esi+edx*4]
    L_0042a374:
        mov edx,dword ptr [eax+4]
    L_0042a377:
        lea edx,[edx+edx*2]
    L_0042a37a:
        lea edx,[ebx+edx*2]
    L_0042a37d:
        mov dword ptr [ecx+0A8h],edx
    L_0042a383:
        mov ecx,dword ptr [eax+8]
    L_0042a386:
        lea eax,[eax+ecx+1C4h]
    L_0042a38d:
        inc edi
    L_0042a38e:
        jmp short L_0042a330
    L_0042a390:
        test byte ptr [data_00474ca0],20h
    L_0042a397:
        pop ebx
    L_0042a398:
        jne short L_0042a3a7
    L_0042a39a:
        test ebp,ebp
    L_0042a39c:
        je short L_0042a3a7
    L_0042a39e:
        push ebp
    L_0042a39f:
        call asm_free_00452422
    L_0042a3a4:
        add esp,4
    L_0042a3a7:
        xor eax,eax
    L_0042a3a9:
        mov ecx,dword ptr [esp+10Ch]
    L_0042a3b0:
        pop edi
    L_0042a3b1:
        pop ebp
    L_0042a3b2:
        xor ecx,esp
    L_0042a3b4:
        call asm_security_check_cookie_00458ea5
    L_0042a3b9:
        add esp,108h
    L_0042a3bf:
        ret 4
    }
}
