#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436210..0x0043625F: ?MemoryFile_RemoveNode@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_RemoveNode_00436210() {
    __asm {
    L_00436210:
        push esi
    L_00436211:
        mov esi,ecx
    L_00436213:
        lea eax,[esi+esi*2]
    L_00436216:
        shl eax,2
    L_00436219:
        mov ecx,dword ptr [eax+477858h]
    L_0043621f:
        test ecx,ecx
    L_00436221:
        je short L_00436238
    L_00436223:
        mov edx,dword ptr [eax+477860h]
    L_00436229:
        test edx,edx
    L_0043622b:
        jne short L_0043623a
    L_0043622d:
        mov edx,dword ptr [eax+47785Ch]
    L_00436233:
        call asm_MemoryFile_RelinkChild_00436260
    L_00436238:
        pop esi
    L_00436239:
        ret
    L_0043623a:
        mov ecx,dword ptr [eax+47785Ch]
    L_00436240:
        test ecx,ecx
    L_00436242:
        je short L_00436233
    L_00436244:
        push edi
    L_00436245:
        mov eax,esi
    L_00436247:
        call asm_MemoryFile_FindPredecessor_00436330
    L_0043624c:
        mov edi,eax
    L_0043624e:
        mov ecx,edi
    L_00436250:
        call asm_MemoryFile_RemoveNode_00436210
    L_00436255:
        mov ecx,edi
    L_00436257:
        pop edi
    L_00436258:
        mov eax,esi
    L_0043625a:
        pop esi
    L_0043625b:
        jmp asm_MemoryFile_ReplaceNode_004362b0
    }
}

// 0x00436260..0x004362AE: ?MemoryFile_RelinkChild@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_RelinkChild_00436260() {
    __asm {
    L_00436260:
        push edi
    L_00436261:
        lea ecx,[esi+esi*2]
    L_00436264:
        mov edi,dword ptr [ecx*4+477858h]
    L_0043626b:
        lea eax,[edx+edx*2]
    L_0043626e:
        mov dword ptr [eax*4+477858h],edi
    L_00436275:
        mov eax,dword ptr [ecx*4+477858h]
    L_0043627c:
        lea eax,[eax+eax*2]
    L_0043627f:
        shl eax,2
    L_00436282:
        cmp dword ptr [eax+477860h],esi
    L_00436288:
        pop edi
    L_00436289:
        jne short L_0043629d
    L_0043628b:
        mov dword ptr [eax+477860h],edx
    L_00436291:
        mov dword ptr [ecx*4+477858h],0
    L_0043629c:
        ret
    L_0043629d:
        mov dword ptr [eax+47785Ch],edx
    L_004362a3:
        mov dword ptr [ecx*4+477858h],0
    L_004362ae:
        ret
    }
}

// 0x004362B0..0x00436324: ?MemoryFile_ReplaceNode@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_ReplaceNode_004362b0() {
    __asm {
    L_004362b0:
        push ebx
    L_004362b1:
        push esi
    L_004362b2:
        mov esi,eax
    L_004362b4:
        lea eax,[esi+esi*2]
    L_004362b7:
        lea edx,[eax*4+477858h]
    L_004362be:
        mov eax,dword ptr [edx]
    L_004362c0:
        lea eax,[eax+eax*2]
    L_004362c3:
        shl eax,2
    L_004362c6:
        push edi
    L_004362c7:
        cmp dword ptr [eax+47785Ch],esi
    L_004362cd:
        jne short L_004362d7
    L_004362cf:
        mov dword ptr [eax+47785Ch],ecx
    L_004362d5:
        jmp short L_004362dd
    L_004362d7:
        mov dword ptr [eax+477860h],ecx
    L_004362dd:
        lea eax,[ecx+ecx*2]
    L_004362e0:
        shl eax,2
    L_004362e3:
        lea esi,[eax+477858h]
    L_004362e9:
        mov edi,edx
    L_004362eb:
        mov ebx,dword ptr [edi]
    L_004362ed:
        mov dword ptr [esi],ebx
    L_004362ef:
        mov ebx,dword ptr [edi+4]
    L_004362f2:
        mov dword ptr [esi+4],ebx
    L_004362f5:
        mov edi,dword ptr [edi+8]
    L_004362f8:
        mov dword ptr [esi+8],edi
    L_004362fb:
        mov esi,dword ptr [eax+47785Ch]
    L_00436301:
        lea esi,[esi+esi*2]
    L_00436304:
        mov dword ptr [esi*4+477858h],ecx
    L_0043630b:
        mov eax,dword ptr [eax+477860h]
    L_00436311:
        pop edi
    L_00436312:
        lea eax,[eax+eax*2]
    L_00436315:
        pop esi
    L_00436316:
        mov dword ptr [eax*4+477858h],ecx
    L_0043631d:
        mov dword ptr [edx],0
    L_00436323:
        pop ebx
    L_00436324:
        ret
    }
}

// 0x00436330..0x00436349: ?MemoryFile_FindPredecessor@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_FindPredecessor_00436330() {
    __asm {
    L_00436330:
        lea eax,[eax+eax*2]
    L_00436333:
        mov eax,dword ptr [eax*4+47785Ch]
    L_0043633a:
        lea ecx,[eax+eax*2]
    L_0043633d:
        mov ecx,dword ptr [ecx*4+477860h]
    L_00436344:
        test ecx,ecx
    L_00436346:
        TH10_REL8(0x74, 0x00436346, VA_asm_target_00436360)
    L_00436348:
        TH10_REL8(0xeb, 0x00436348, VA_asm_MemoryFile_FindPredecessor_part_00436350)
    }
}

// 0x00436350..0x00436360: ?MemoryFile_FindPredecessor@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MemoryFile_FindPredecessor_part_00436350() {
    __asm {
    L_00436350:
        mov eax,ecx
    L_00436352:
        lea edx,[eax+eax*2]
    L_00436355:
        mov ecx,dword ptr [edx*4+477860h]
    L_0043635c:
        test ecx,ecx
    L_0043635e:
        jne short L_00436350
    L_00436360:
        ret
    }
}

// 0x0043D250..0x0043D296: ?Resource_FindChunk@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Resource_FindChunk_0043d250() {
    __asm {
    L_0043d250:
        push ebx
    L_0043d251:
        push ebp
    L_0043d252:
        mov ebp,dword ptr [esp+0Ch]
    L_0043d256:
        mov ebx,eax
    L_0043d258:
        test ebx,ebx
    L_0043d25a:
        push esi
    L_0043d25b:
        mov esi,ecx
    L_0043d25d:
        jbe short L_0043d286
    L_0043d25f:
        nop
    L_0043d260:
        mov eax,dword ptr [esi+4]
    L_0043d263:
        push 4
    L_0043d265:
        push ebp
    L_0043d266:
        push esi
    L_0043d267:
        mov dword ptr [edi],eax
    L_0043d269:
        call asm_strncmp_00452f80
    L_0043d26e:
        add esp,0Ch
    L_0043d271:
        test eax,eax
    L_0043d273:
        je short L_0043d28e
    L_0043d275:
        mov eax,dword ptr [edi]
    L_0043d277:
        mov ecx,0FFFFFFF8h
    L_0043d27c:
        sub ecx,eax
    L_0043d27e:
        add ebx,ecx
    L_0043d280:
        lea esi,[esi+eax+8]
    L_0043d284:
        jne short L_0043d260
    L_0043d286:
        pop esi
    L_0043d287:
        pop ebp
    L_0043d288:
        xor eax,eax
    L_0043d28a:
        pop ebx
    L_0043d28b:
        ret 4
    L_0043d28e:
        lea eax,[esi+8]
    L_0043d291:
        pop esi
    L_0043d292:
        pop ebp
    L_0043d293:
        pop ebx
    L_0043d294:
        ret 4
    }
}

// 0x0043D390..0x0043D63B: FUN_0043d390
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043d390_0043d390() {
    __asm {
    L_0043d390:
        sub esp,5Ch
    L_0043d393:
        mov eax,dword ptr [data_00473660]
    L_0043d398:
        xor eax,esp
    L_0043d39a:
        mov dword ptr [esp+58h],eax
    L_0043d39e:
        mov eax,dword ptr [esp+60h]
    L_0043d3a2:
        push ebx
    L_0043d3a3:
        mov ebx,edx
    L_0043d3a5:
        mov dword ptr [esp+8],eax
    L_0043d3a9:
        mov eax,dword ptr [ebx+610h]
    L_0043d3af:
        test eax,eax
    L_0043d3b1:
        push esi
    L_0043d3b2:
        mov esi,ecx
    L_0043d3b4:
        jne short L_0043d3cb
    L_0043d3b6:
        pop esi
    L_0043d3b7:
        xor eax,eax
    L_0043d3b9:
        pop ebx
    L_0043d3ba:
        mov ecx,dword ptr [esp+58h]
    L_0043d3be:
        xor ecx,esp
    L_0043d3c0:
        call asm_security_check_cookie_00458ea5
    L_0043d3c5:
        add esp,5Ch
    L_0043d3c8:
        ret 4
    L_0043d3cb:
        mov eax,dword ptr [ebx+esi*4+8]
    L_0043d3cf:
        test eax,eax
    L_0043d3d1:
        push edi
    L_0043d3d2:
        lea edi,[ebx+esi*4+8]
    L_0043d3d6:
        mov dword ptr [esp+24h],edi
    L_0043d3da:
        je short L_0043d3e8
    L_0043d3dc:
        mov ecx,dword ptr [eax]
    L_0043d3de:
        push eax
    L_0043d3df:
        call dword ptr [ecx+8]
    L_0043d3e2:
        mov dword ptr [edi],0
    L_0043d3e8:
        mov eax,dword ptr [ebx+esi*4+5230h]
    L_0043d3ef:
        test eax,eax
    L_0043d3f1:
        push ebp
    L_0043d3f2:
        jne short L_0043d41b
    L_0043d3f4:
        mov edi,dword ptr [data_004660ac]
    L_0043d3fa:
        mov ebp,2
    L_0043d3ff:
        nop
    L_0043d400:
        push 0Ah
    L_0043d402:
        call edi
    L_0043d404:
        cmp dword ptr [data_004977b4],ebp
    L_0043d40a:
        je asm_target_0043d625
    L_0043d410:
        mov eax,dword ptr [ebx+esi*4+5230h]
    L_0043d417:
        test eax,eax
    L_0043d419:
        je short L_0043d400
    L_0043d41b:
        mov edi,dword ptr [ebx+esi*4+5230h]
    L_0043d422:
        test edi,edi
    L_0043d424:
        mov dword ptr [esp+10h],edi
    L_0043d428:
        mov dword ptr [ebx+esi*4+5230h],0
    L_0043d433:
        je short L_0043d466
    L_0043d435:
        push 4
    L_0043d437:
        push 46FDA4h
    L_0043d43c:
        push edi
    L_0043d43d:
        call asm_strncmp_00452f80
    L_0043d442:
        add esp,0Ch
    L_0043d445:
        test eax,eax
    L_0043d447:
        je short L_0043d47e
    L_0043d449:
        mov edx,dword ptr [esp+14h]
    L_0043d44d:
        push edx
    L_0043d44e:
        push 46FD88h
    L_0043d453:
        mov ecx,474F70h
    L_0043d458:
        call asm_TextLog_Append_0044b810
    L_0043d45d:
        push edi
    L_0043d45e:
        call asm_free_00452422
    L_0043d463:
        add esp,0Ch
    L_0043d466:
        pop ebp
    L_0043d467:
        pop edi
    L_0043d468:
        pop esi
    L_0043d469:
        or eax,0FFFFFFFFh
    L_0043d46c:
        pop ebx
    L_0043d46d:
        mov ecx,dword ptr [esp+58h]
    L_0043d471:
        xor ecx,esp
    L_0043d473:
        call asm_security_check_cookie_00458ea5
    L_0043d478:
        add esp,5Ch
    L_0043d47b:
        ret 4
    L_0043d47e:
        mov ebp,dword ptr [edi+4]
    L_0043d481:
        lea esi,[edi+4]
    L_0043d484:
        push 4
    L_0043d486:
        add esi,4
    L_0043d489:
        push 46FD80h
    L_0043d48e:
        push esi
    L_0043d48f:
        call asm_strncmp_00452f80
    L_0043d494:
        add esp,0Ch
    L_0043d497:
        test eax,eax
    L_0043d499:
        je short L_0043d4a7
    L_0043d49b:
        mov eax,dword ptr [esp+14h]
    L_0043d49f:
        push eax
    L_0043d4a0:
        push 46FD64h
    L_0043d4a5:
        jmp short L_0043d453
    L_0043d4a7:
        add esi,4
    L_0043d4aa:
        add ebp,0FFFFFFF4h
    L_0043d4ad:
        push 46FD5Ch
    L_0043d4b2:
        mov eax,ebp
    L_0043d4b4:
        lea edi,[esp+30h]
    L_0043d4b8:
        mov ecx,esi
    L_0043d4ba:
        call asm_Resource_FindChunk_0043d250
    L_0043d4bf:
        test eax,eax
    L_0043d4c1:
        je short L_0043d4fb
    L_0043d4c3:
        mov ecx,dword ptr [eax]
    L_0043d4c5:
        mov dword ptr [esp+30h],ecx
    L_0043d4c9:
        mov edx,dword ptr [eax+4]
    L_0043d4cc:
        mov dword ptr [esp+34h],edx
    L_0043d4d0:
        mov ecx,dword ptr [eax+8]
    L_0043d4d3:
        mov dword ptr [esp+38h],ecx
    L_0043d4d7:
        mov edx,dword ptr [eax+0Ch]
    L_0043d4da:
        mov dword ptr [esp+3Ch],edx
    L_0043d4de:
        mov ax,word ptr [eax+10h]
    L_0043d4e2:
        mov word ptr [esp+40h],ax
    L_0043d4e7:
        push 46FD54h
    L_0043d4ec:
        mov eax,ebp
    L_0043d4ee:
        mov ecx,esi
    L_0043d4f0:
        call asm_Resource_FindChunk_0043d250
    L_0043d4f5:
        mov ebp,eax
    L_0043d4f7:
        test ebp,ebp
    L_0043d4f9:
        jne short L_0043d519
    L_0043d4fb:
        mov ecx,dword ptr [esp+14h]
    L_0043d4ff:
        push ecx
    L_0043d500:
        push 46FD64h
    L_0043d505:
        mov ecx,474F70h
    L_0043d50a:
        call asm_TextLog_Append_0044b810
    L_0043d50f:
        mov edx,dword ptr [esp+18h]
    L_0043d513:
        push edx
    L_0043d514:
        jmp asm_target_0043d45e
    L_0043d519:
        mov edi,dword ptr [esp+28h]
    L_0043d51d:
        mov ebx,dword ptr [ebx]
    L_0043d51f:
        mov esi,dword ptr [esp+2Ch]
    L_0043d523:
        xor eax,eax
    L_0043d525:
        mov dword ptr [esp+44h],eax
    L_0043d529:
        mov dword ptr [esp+48h],eax
    L_0043d52d:
        mov dword ptr [esp+4Ch],eax
    L_0043d531:
        mov dword ptr [esp+50h],eax
    L_0043d535:
        mov dword ptr [esp+54h],eax
    L_0043d539:
        mov dword ptr [esp+58h],eax
    L_0043d53d:
        mov dword ptr [esp+5Ch],eax
    L_0043d541:
        mov dword ptr [esp+60h],eax
    L_0043d545:
        push eax
    L_0043d546:
        mov dword ptr [esp+68h],eax
    L_0043d54a:
        push edi
    L_0043d54b:
        lea eax,[esp+4Ch]
    L_0043d54f:
        lea ecx,[esp+38h]
    L_0043d553:
        push eax
    L_0043d554:
        mov dword ptr [esp+50h],24h
    L_0043d55c:
        mov dword ptr [esp+54h],80C8h
    L_0043d564:
        mov dword ptr [esp+58h],esi
    L_0043d568:
        mov dword ptr [esp+60h],ecx
    L_0043d56c:
        mov edx,dword ptr [ebx]
    L_0043d56e:
        push ebx
    L_0043d56f:
        call dword ptr [edx+0Ch]
    L_0043d572:
        test eax,eax
    L_0043d574:
        jge short L_0043d588
    L_0043d576:
        mov ecx,dword ptr [esp+10h]
    L_0043d57a:
        push ecx
    L_0043d57b:
        call asm_free_00452422
    L_0043d580:
        add esp,4
    L_0043d583:
        jmp asm_target_0043d466
    L_0043d588:
        mov eax,dword ptr [edi]
    L_0043d58a:
        mov edx,dword ptr [eax]
    L_0043d58c:
        push 0
    L_0043d58e:
        lea ecx,[esp+20h]
    L_0043d592:
        push ecx
    L_0043d593:
        lea ecx,[esp+28h]
    L_0043d597:
        push ecx
    L_0043d598:
        lea ecx,[esp+24h]
    L_0043d59c:
        push ecx
    L_0043d59d:
        lea ecx,[esp+34h]
    L_0043d5a1:
        push ecx
    L_0043d5a2:
        push esi
    L_0043d5a3:
        push 0
    L_0043d5a5:
        push eax
    L_0043d5a6:
        call dword ptr [edx+2Ch]
    L_0043d5a9:
        test eax,eax
    L_0043d5ab:
        jge short L_0043d5bf
    L_0043d5ad:
        mov edx,dword ptr [esp+10h]
    L_0043d5b1:
        push edx
    L_0043d5b2:
        call asm_free_00452422
    L_0043d5b7:
        add esp,4
    L_0043d5ba:
        jmp asm_target_0043d466
    L_0043d5bf:
        mov ecx,dword ptr [esp+18h]
    L_0043d5c3:
        mov edi,dword ptr [esp+24h]
    L_0043d5c7:
        mov eax,ecx
    L_0043d5c9:
        shr ecx,2
    L_0043d5cc:
        mov esi,ebp
    L_0043d5ce:
        rep movsd
    L_0043d5d0:
        mov ecx,eax
    L_0043d5d2:
        and ecx,3
    L_0043d5d5:
        rep movsb
    L_0043d5d7:
        mov ecx,dword ptr [esp+1Ch]
    L_0043d5db:
        test ecx,ecx
    L_0043d5dd:
        je short L_0043d5fc
    L_0043d5df:
        mov edx,dword ptr [esp+18h]
    L_0043d5e3:
        mov edi,dword ptr [esp+20h]
    L_0043d5e7:
        mov eax,ecx
    L_0043d5e9:
        shr ecx,2
    L_0043d5ec:
        lea esi,[edx+ebp]
    L_0043d5ef:
        rep movsd
    L_0043d5f1:
        mov ecx,eax
    L_0043d5f3:
        and ecx,3
    L_0043d5f6:
        rep movsb
    L_0043d5f8:
        mov ecx,dword ptr [esp+1Ch]
    L_0043d5fc:
        mov edx,dword ptr [esp+28h]
    L_0043d600:
        mov eax,dword ptr [edx]
    L_0043d602:
        mov edx,dword ptr [eax]
    L_0043d604:
        push ecx
    L_0043d605:
        mov ecx,dword ptr [esp+24h]
    L_0043d609:
        push ecx
    L_0043d60a:
        mov ecx,dword ptr [esp+20h]
    L_0043d60e:
        push ecx
    L_0043d60f:
        mov ecx,dword ptr [esp+30h]
    L_0043d613:
        push ecx
    L_0043d614:
        push eax
    L_0043d615:
        call dword ptr [edx+4Ch]
    L_0043d618:
        mov edx,dword ptr [esp+10h]
    L_0043d61c:
        push edx
    L_0043d61d:
        call asm_free_00452422
    L_0043d622:
        add esp,4
    L_0043d625:
        mov ecx,dword ptr [esp+68h]
    L_0043d629:
        pop ebp
    L_0043d62a:
        pop edi
    L_0043d62b:
        pop esi
    L_0043d62c:
        pop ebx
    L_0043d62d:
        xor ecx,esp
    L_0043d62f:
        xor eax,eax
    L_0043d631:
        call asm_security_check_cookie_00458ea5
    L_0043d636:
        add esp,5Ch
    L_0043d639:
        ret 4
    }
}

// Recovered semantic C++ definitions.
#include "th10/platform/memory_file.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
#ifdef _MSC_VER
extern "C" void* __cdecl memcpy(void* destination, const void* source,
                                DWORD size);
#pragma intrinsic(memcpy)
#endif

#define TH10_BUFFER_DESTRUCTOR_ATTRIBUTES __declspec(noinline)
#include "th10/platform/buffer_file_lifetime.inl"

// This definition makes the virtual lifetime entries available to the compiler.
// The retail constructor uses EAX for this and is still an assembly region;
// this ordinary-thiscall constructor is not selected into the fixed image.
BufferFile::BufferFile() : size_(0), position_(0), data_(0) {}

DWORD BufferFile::Read(void* destination, DWORD requested) {
    DWORD remaining = (DWORD)((data_ + size_) - position_);
    if (remaining >= requested) {
        memcpy(destination, position_, requested);
        position_ += requested;
        return requested;
    }
    if (remaining != 0) {
        memcpy(destination, position_, remaining);
        position_ += remaining;
        return remaining;
    }
    return 0;
}

BYTE BufferFile::Write(const void*, DWORD) {
    return 0;
}

DWORD BufferFile::Tell() const {
    return (DWORD)(position_ - data_);
}

DWORD BufferFile::GetSize() const {
    return size_;
}
