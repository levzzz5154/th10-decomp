#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00461184..0x00461360: FUN_00461184
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00461184_00461184() {
    __asm {
    L_00461184:
        push ebp
    L_00461185:
        mov ebp,esp
    L_00461187:
        sub esp,0Ch
    L_0046118a:
        and dword ptr [ebp-8],0
    L_0046118e:
        cmp dword ptr [ebp+10h],0
    L_00461192:
        push ebx
    L_00461193:
        mov ebx,dword ptr [ebp+0Ch]
    L_00461196:
        push esi
    L_00461197:
        push edi
    L_00461198:
        mov edx,ebx
    L_0046119a:
        je asm_target_0046135a
    L_004611a0:
        mov eax,dword ptr [ebp+8]
    L_004611a3:
        mov ecx,eax
    L_004611a5:
        and eax,1Fh
    L_004611a8:
        sar ecx,5
    L_004611ab:
        lea esi,[eax+eax*8]
    L_004611ae:
        lea edi,[ecx*4+499200h]
    L_004611b5:
        mov eax,dword ptr [edi]
    L_004611b7:
        shl esi,2
    L_004611ba:
        add eax,esi
    L_004611bc:
        mov cl,byte ptr [eax+4]
    L_004611bf:
        test cl,2
    L_004611c2:
        jne asm_target_0046135a
    L_004611c8:
        test cl,48h
    L_004611cb:
        je short L_004611ef
    L_004611cd:
        cmp byte ptr [eax+5],0Ah
    L_004611d1:
        je short L_004611ef
    L_004611d3:
        mov eax,dword ptr [edi]
    L_004611d5:
        mov al,byte ptr [eax+esi+5]
    L_004611d9:
        dec dword ptr [ebp+10h]
    L_004611dc:
        mov byte ptr [ebx],al
    L_004611de:
        mov eax,dword ptr [edi]
    L_004611e0:
        lea edx,[ebx+1]
    L_004611e3:
        mov dword ptr [ebp-8],1
    L_004611ea:
        mov byte ptr [eax+esi+5],0Ah
    L_004611ef:
        push 0
    L_004611f1:
        lea eax,[ebp-0Ch]
    L_004611f4:
        push eax
    L_004611f5:
        push dword ptr [ebp+10h]
    L_004611f8:
        mov eax,dword ptr [edi]
    L_004611fa:
        push edx
    L_004611fb:
        push dword ptr [eax+esi]
    L_004611fe:
        call dword ptr [data_004660d0]
    L_00461204:
        test eax,eax
    L_00461206:
        jne short L_00461241
    L_00461208:
        call dword ptr [data_0046610c]
    L_0046120e:
        push 5
    L_00461210:
        pop esi
    L_00461211:
        cmp eax,esi
    L_00461213:
        jne short L_00461229
    L_00461215:
        call asm_FUN_00456af2_00456af2
    L_0046121a:
        mov dword ptr [eax],9
    L_00461220:
        call asm_FUN_00456afb_00456afb
    L_00461225:
        mov dword ptr [eax],esi
    L_00461227:
        jmp short L_00461239
    L_00461229:
        cmp eax,6Dh
    L_0046122c:
        je asm_target_0046135a
    L_00461232:
        push eax
    L_00461233:
        call asm_dosmaperr_00456b04
    L_00461238:
        pop ecx
    L_00461239:
        or eax,0FFFFFFFFh
    L_0046123c:
        jmp asm_target_0046135c
    L_00461241:
        mov eax,dword ptr [ebp-0Ch]
    L_00461244:
        mov ecx,dword ptr [edi]
    L_00461246:
        add dword ptr [ebp-8],eax
    L_00461249:
        test byte ptr [ecx+esi+4],80h
    L_0046124e:
        je asm_target_00461355
    L_00461254:
        test eax,eax
    L_00461256:
        je short L_00461268
    L_00461258:
        cmp byte ptr [ebx],0Ah
    L_0046125b:
        jne short L_00461268
    L_0046125d:
        mov eax,ecx
    L_0046125f:
        lea eax,[eax+esi+4]
    L_00461263:
        or byte ptr [eax],4
    L_00461266:
        jmp short L_00461271
    L_00461268:
        mov eax,dword ptr [edi]
    L_0046126a:
        lea eax,[eax+esi+4]
    L_0046126e:
        and byte ptr [eax],0FBh
    L_00461271:
        mov eax,dword ptr [ebp+0Ch]
    L_00461274:
        mov ecx,dword ptr [ebp-8]
    L_00461277:
        add ecx,eax
    L_00461279:
        cmp eax,ecx
    L_0046127b:
        mov dword ptr [ebp+10h],eax
    L_0046127e:
        mov dword ptr [ebp-8],ecx
    L_00461281:
        jae asm_target_0046134f
    L_00461287:
        mov eax,dword ptr [ebp+10h]
    L_0046128a:
        mov al,byte ptr [eax]
    L_0046128c:
        cmp al,1Ah
    L_0046128e:
        je asm_target_0046133f
    L_00461294:
        cmp al,0Dh
    L_00461296:
        je short L_004612a3
    L_00461298:
        mov byte ptr [ebx],al
    L_0046129a:
        inc ebx
    L_0046129b:
        inc dword ptr [ebp+10h]
    L_0046129e:
        jmp asm_target_00461331
    L_004612a3:
        dec ecx
    L_004612a4:
        cmp dword ptr [ebp+10h],ecx
    L_004612a7:
        jae short L_004612bd
    L_004612a9:
        mov eax,dword ptr [ebp+10h]
    L_004612ac:
        inc eax
    L_004612ad:
        cmp byte ptr [eax],0Ah
    L_004612b0:
        jne short L_004612b8
    L_004612b2:
        add dword ptr [ebp+10h],2
    L_004612b6:
        jmp short L_00461311
    L_004612b8:
        mov dword ptr [ebp+10h],eax
    L_004612bb:
        jmp short L_0046132d
    L_004612bd:
        inc dword ptr [ebp+10h]
    L_004612c0:
        push 0
    L_004612c2:
        lea eax,[ebp-0Ch]
    L_004612c5:
        push eax
    L_004612c6:
        push 1
    L_004612c8:
        lea eax,[ebp-1]
    L_004612cb:
        push eax
    L_004612cc:
        mov eax,dword ptr [edi]
    L_004612ce:
        push dword ptr [eax+esi]
    L_004612d1:
        call dword ptr [data_004660d0]
    L_004612d7:
        test eax,eax
    L_004612d9:
        jne short L_004612e5
    L_004612db:
        call dword ptr [data_0046610c]
    L_004612e1:
        test eax,eax
    L_004612e3:
        jne short L_0046132d
    L_004612e5:
        cmp dword ptr [ebp-0Ch],0
    L_004612e9:
        je short L_0046132d
    L_004612eb:
        mov eax,dword ptr [edi]
    L_004612ed:
        test byte ptr [eax+esi+4],48h
    L_004612f2:
        je short L_00461306
    L_004612f4:
        mov al,byte ptr [ebp-1]
    L_004612f7:
        cmp al,0Ah
    L_004612f9:
        je short L_00461311
    L_004612fb:
        mov byte ptr [ebx],0Dh
    L_004612fe:
        mov ecx,dword ptr [edi]
    L_00461300:
        mov byte ptr [ecx+esi+5],al
    L_00461304:
        jmp short L_00461330
    L_00461306:
        cmp ebx,dword ptr [ebp+0Ch]
    L_00461309:
        jne short L_00461316
    L_0046130b:
        cmp byte ptr [ebp-1],0Ah
    L_0046130f:
        jne short L_00461316
    L_00461311:
        mov byte ptr [ebx],0Ah
    L_00461314:
        jmp short L_00461330
    L_00461316:
        push 1
    L_00461318:
        push 0FFFFFFFFh
    L_0046131a:
        push 0FFFFFFFFh
    L_0046131c:
        push dword ptr [ebp+8]
    L_0046131f:
        call asm_lseeki64_lk_0045fa1a
    L_00461324:
        add esp,10h
    L_00461327:
        cmp byte ptr [ebp-1],0Ah
    L_0046132b:
        je short L_00461331
    L_0046132d:
        mov byte ptr [ebx],0Dh
    L_00461330:
        inc ebx
    L_00461331:
        mov ecx,dword ptr [ebp-8]
    L_00461334:
        cmp dword ptr [ebp+10h],ecx
    L_00461337:
        jb asm_target_00461287
    L_0046133d:
        jmp short L_0046134f
    L_0046133f:
        mov eax,dword ptr [edi]
    L_00461341:
        test byte ptr [eax+esi+4],40h
    L_00461346:
        jne short L_0046134f
    L_00461348:
        lea esi,[eax+esi+4]
    L_0046134c:
        or byte ptr [esi],2
    L_0046134f:
        sub ebx,dword ptr [ebp+0Ch]
    L_00461352:
        mov dword ptr [ebp-8],ebx
    L_00461355:
        mov eax,dword ptr [ebp-8]
    L_00461358:
        jmp short L_0046135c
    L_0046135a:
        xor eax,eax
    L_0046135c:
        pop edi
    L_0046135d:
        pop esi
    L_0046135e:
        pop ebx
    L_0046135f:
        leave
    L_00461360:
        ret
    }
}
