#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044B0D0..0x0044B1BC: DecryptDatBuffer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DecryptDatBuffer_0044b0d0() {
    __asm {
    L_0044b0d0:
        sub esp,8
    L_0044b0d3:
        push ebx
    L_0044b0d4:
        push ebp
    L_0044b0d5:
        push esi
    L_0044b0d6:
        mov esi,dword ptr [esp+24h]
    L_0044b0da:
        mov bl,al
    L_0044b0dc:
        push edi
    L_0044b0dd:
        mov edi,dword ptr [esp+20h]
    L_0044b0e1:
        mov eax,edi
    L_0044b0e3:
        cdq
    L_0044b0e4:
        idiv esi
    L_0044b0e6:
        mov eax,esi
    L_0044b0e8:
        mov esi,dword ptr [esp+2Ch]
    L_0044b0ec:
        mov ecx,edx
    L_0044b0ee:
        cdq
    L_0044b0ef:
        and edx,3
    L_0044b0f2:
        add eax,edx
    L_0044b0f4:
        xor edx,edx
    L_0044b0f6:
        sar eax,2
    L_0044b0f9:
        cmp ecx,eax
    L_0044b0fb:
        setge dl
    L_0044b0fe:
        dec edx
    L_0044b0ff:
        and edx,ecx
    L_0044b101:
        cmp esi,edi
    L_0044b103:
        mov dword ptr [esp+20h],edx
    L_0044b107:
        jle short L_0044b10b
    L_0044b109:
        mov esi,edi
    L_0044b10b:
        mov eax,dword ptr [esp+1Ch]
    L_0044b10f:
        push esi
    L_0044b110:
        mov dword ptr [esp+14h],eax
    L_0044b114:
        call asm_malloc_00452706
    L_0044b119:
        add esp,4
    L_0044b11c:
        test eax,eax
    L_0044b11e:
        mov dword ptr [esp+14h],eax
    L_0044b122:
        mov ebp,eax
    L_0044b124:
        je asm_target_0044b205
    L_0044b12a:
        mov edx,dword ptr [esp+20h]
    L_0044b12e:
        mov ecx,edi
    L_0044b130:
        and ecx,1
    L_0044b133:
        add ecx,edx
    L_0044b135:
        sub edi,ecx
    L_0044b137:
        mov ecx,esi
    L_0044b139:
        mov esi,dword ptr [esp+1Ch]
    L_0044b13d:
        mov edx,ecx
    L_0044b13f:
        shr ecx,2
    L_0044b142:
        mov dword ptr [esp+20h],edi
    L_0044b146:
        mov edi,eax
    L_0044b148:
        rep movsd
    L_0044b14a:
        mov ecx,edx
    L_0044b14c:
        and ecx,3
    L_0044b14f:
        rep movsb
    L_0044b151:
        mov ecx,dword ptr [esp+20h]
    L_0044b155:
        test ecx,ecx
    L_0044b157:
        jle asm_target_0044b1fc
    L_0044b15d:
        jmp short L_0044b163
    L_0044b15f:
        mov ecx,dword ptr [esp+20h]
    L_0044b163:
        mov edx,dword ptr [esp+2Ch]
    L_0044b167:
        test edx,edx
    L_0044b169:
        jle asm_target_0044b1fc
    L_0044b16f:
        mov esi,dword ptr [esp+28h]
    L_0044b173:
        cmp ecx,esi
    L_0044b175:
        jge short L_0044b17d
    L_0044b177:
        mov dword ptr [esp+28h],ecx
    L_0044b17b:
        mov esi,ecx
    L_0044b17d:
        mov eax,dword ptr [esp+10h]
    L_0044b181:
        lea edi,[eax+esi]
    L_0044b184:
        lea eax,[esi+1]
    L_0044b187:
        cdq
    L_0044b188:
        sub eax,edx
    L_0044b18a:
        sar eax,1
    L_0044b18c:
        test eax,eax
    L_0044b18e:
        mov dword ptr [esp+10h],edi
    L_0044b192:
        lea ecx,[edi-1]
    L_0044b195:
        jle short L_0044b1ab
    L_0044b197:
        mov dl,byte ptr [ebp]
    L_0044b19a:
        xor dl,bl
    L_0044b19c:
        mov byte ptr [ecx],dl
    L_0044b19e:
        mov dl,byte ptr [esp+24h]
    L_0044b1a2:
        sub ecx,2
    L_0044b1a5:
        add bl,dl
    L_0044b1a7:
        inc ebp
    L_0044b1a8:
        dec eax
    L_0044b1a9:
        jne short L_0044b197
    L_0044b1ab:
        mov eax,esi
    L_0044b1ad:
        cdq
    L_0044b1ae:
        sub eax,edx
    L_0044b1b0:
        sar eax,1
    L_0044b1b2:
        test eax,eax
    L_0044b1b4:
        lea ecx,[edi-2]
    L_0044b1b7:
        TH10_REL8(0x7e, 0x0044b1b7, VA_asm_target_0044b1d8)
    L_0044b1b9:
        mov edi,eax
    L_0044b1bb:
        TH10_REL8(0xeb, 0x0044b1bb, VA_asm_DecryptDatBuffer_part_0044b1c0)
    }
}

// 0x0044B1C0..0x0044B212: DecryptDatBuffer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DecryptDatBuffer_part_0044b1c0() {
    __asm {
    L_0044b1c0:
        mov al,byte ptr [ebp]
    L_0044b1c3:
        xor al,bl
    L_0044b1c5:
        mov byte ptr [ecx],al
    L_0044b1c7:
        mov al,byte ptr [esp+24h]
    L_0044b1cb:
        sub ecx,2
    L_0044b1ce:
        add bl,al
    L_0044b1d0:
        inc ebp
    L_0044b1d1:
        dec edi
    L_0044b1d2:
        jne short L_0044b1c0
    L_0044b1d4:
        mov edi,dword ptr [esp+10h]
    L_0044b1d8:
        mov eax,dword ptr [esp+20h]
    L_0044b1dc:
        mov edx,dword ptr [esp+2Ch]
    L_0044b1e0:
        sub eax,esi
    L_0044b1e2:
        sub edx,esi
    L_0044b1e4:
        mov dword ptr [esp+20h],eax
    L_0044b1e8:
        test eax,eax
    L_0044b1ea:
        mov eax,dword ptr [esp+14h]
    L_0044b1ee:
        mov dword ptr [esp+10h],edi
    L_0044b1f2:
        mov dword ptr [esp+2Ch],edx
    L_0044b1f6:
        jg asm_target_0044b15f
    L_0044b1fc:
        push eax
    L_0044b1fd:
        call asm_free_00452422
    L_0044b202:
        add esp,4
    L_0044b205:
        mov eax,dword ptr [esp+1Ch]
    L_0044b209:
        pop edi
    L_0044b20a:
        pop esi
    L_0044b20b:
        pop ebp
    L_0044b20c:
        pop ebx
    L_0044b20d:
        add esp,8
    L_0044b210:
        ret 14h
    }
}

// 0x0044B220..0x0044B352: EncryptDatBuffer
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_EncryptDatBuffer_0044b220() {
    __asm {
    L_0044b220:
        sub esp,8
    L_0044b223:
        push ebx
    L_0044b224:
        push ebp
    L_0044b225:
        push esi
    L_0044b226:
        mov esi,dword ptr [esp+24h]
    L_0044b22a:
        mov bl,al
    L_0044b22c:
        push edi
    L_0044b22d:
        mov edi,dword ptr [esp+20h]
    L_0044b231:
        mov eax,edi
    L_0044b233:
        cdq
    L_0044b234:
        idiv esi
    L_0044b236:
        mov eax,esi
    L_0044b238:
        mov esi,dword ptr [esp+2Ch]
    L_0044b23c:
        mov ecx,edx
    L_0044b23e:
        cdq
    L_0044b23f:
        and edx,3
    L_0044b242:
        add eax,edx
    L_0044b244:
        xor edx,edx
    L_0044b246:
        sar eax,2
    L_0044b249:
        cmp ecx,eax
    L_0044b24b:
        setge dl
    L_0044b24e:
        dec edx
    L_0044b24f:
        and edx,ecx
    L_0044b251:
        cmp esi,edi
    L_0044b253:
        mov dword ptr [esp+20h],edx
    L_0044b257:
        jle short L_0044b25b
    L_0044b259:
        mov esi,edi
    L_0044b25b:
        mov ebp,dword ptr [esp+1Ch]
    L_0044b25f:
        push esi
    L_0044b260:
        call asm_malloc_00452706
    L_0044b265:
        add esp,4
    L_0044b268:
        test eax,eax
    L_0044b26a:
        mov dword ptr [esp+10h],eax
    L_0044b26e:
        mov dword ptr [esp+14h],eax
    L_0044b272:
        je asm_target_0044b345
    L_0044b278:
        mov edx,dword ptr [esp+20h]
    L_0044b27c:
        mov ecx,edi
    L_0044b27e:
        and ecx,1
    L_0044b281:
        add ecx,edx
    L_0044b283:
        sub edi,ecx
    L_0044b285:
        mov ecx,esi
    L_0044b287:
        mov edx,ecx
    L_0044b289:
        shr ecx,2
    L_0044b28c:
        mov dword ptr [esp+20h],edi
    L_0044b290:
        mov esi,ebp
    L_0044b292:
        mov edi,eax
    L_0044b294:
        rep movsd
    L_0044b296:
        mov ecx,edx
    L_0044b298:
        and ecx,3
    L_0044b29b:
        rep movsb
    L_0044b29d:
        mov ecx,dword ptr [esp+20h]
    L_0044b2a1:
        test ecx,ecx
    L_0044b2a3:
        jle asm_target_0044b33c
    L_0044b2a9:
        mov edi,eax
    L_0044b2ab:
        jmp short L_0044b2b1
    L_0044b2ad:
        mov ecx,dword ptr [esp+20h]
    L_0044b2b1:
        mov edx,dword ptr [esp+2Ch]
    L_0044b2b5:
        test edx,edx
    L_0044b2b7:
        jle asm_target_0044b33c
    L_0044b2bd:
        mov esi,dword ptr [esp+28h]
    L_0044b2c1:
        cmp ecx,esi
    L_0044b2c3:
        jge short L_0044b2cb
    L_0044b2c5:
        mov dword ptr [esp+28h],ecx
    L_0044b2c9:
        mov esi,ecx
    L_0044b2cb:
        lea eax,[esi+1]
    L_0044b2ce:
        cdq
    L_0044b2cf:
        sub eax,edx
    L_0044b2d1:
        add edi,esi
    L_0044b2d3:
        sar eax,1
    L_0044b2d5:
        test eax,eax
    L_0044b2d7:
        mov dword ptr [esp+14h],edi
    L_0044b2db:
        lea ecx,[edi-1]
    L_0044b2de:
        jle short L_0044b2f4
    L_0044b2e0:
        mov dl,byte ptr [ecx]
    L_0044b2e2:
        xor dl,bl
    L_0044b2e4:
        mov byte ptr [ebp],dl
    L_0044b2e7:
        mov dl,byte ptr [esp+24h]
    L_0044b2eb:
        sub ecx,2
    L_0044b2ee:
        add bl,dl
    L_0044b2f0:
        inc ebp
    L_0044b2f1:
        dec eax
    L_0044b2f2:
        jne short L_0044b2e0
    L_0044b2f4:
        mov eax,esi
    L_0044b2f6:
        cdq
    L_0044b2f7:
        sub eax,edx
    L_0044b2f9:
        sar eax,1
    L_0044b2fb:
        test eax,eax
    L_0044b2fd:
        lea ecx,[edi-2]
    L_0044b300:
        jle short L_0044b31c
    L_0044b302:
        mov edi,eax
    L_0044b304:
        mov al,byte ptr [ecx]
    L_0044b306:
        xor al,bl
    L_0044b308:
        mov byte ptr [ebp],al
    L_0044b30b:
        mov al,byte ptr [esp+24h]
    L_0044b30f:
        sub ecx,2
    L_0044b312:
        add bl,al
    L_0044b314:
        inc ebp
    L_0044b315:
        dec edi
    L_0044b316:
        jne short L_0044b304
    L_0044b318:
        mov edi,dword ptr [esp+14h]
    L_0044b31c:
        mov eax,dword ptr [esp+20h]
    L_0044b320:
        mov edx,dword ptr [esp+2Ch]
    L_0044b324:
        sub eax,esi
    L_0044b326:
        sub edx,esi
    L_0044b328:
        mov dword ptr [esp+20h],eax
    L_0044b32c:
        test eax,eax
    L_0044b32e:
        mov eax,dword ptr [esp+10h]
    L_0044b332:
        mov dword ptr [esp+2Ch],edx
    L_0044b336:
        jg asm_target_0044b2ad
    L_0044b33c:
        push eax
    L_0044b33d:
        call asm_free_00452422
    L_0044b342:
        add esp,4
    L_0044b345:
        mov eax,dword ptr [esp+1Ch]
    L_0044b349:
        pop edi
    L_0044b34a:
        pop esi
    L_0044b34b:
        pop ebp
    L_0044b34c:
        pop ebx
    L_0044b34d:
        add esp,8
    L_0044b350:
        ret 14h
    }
}
