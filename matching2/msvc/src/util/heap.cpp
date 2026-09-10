#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "th10/util/heap.hpp"

// 0x00418150..0x00418161: ?Heap_DestroyOwned@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Heap_DestroyOwned_00418150() {
    __asm {
    L_00418150:
        test esi,esi
    L_00418152:
        je short L_00418161
    L_00418154:
        push esi
    L_00418155:
        call asm_FUN_00417c80_00417c80
    L_0041815a:
        push esi
    L_0041815b:
        call asm_free_004524a1
    L_00418160:
        pop ecx
    L_00418161:
        ret
    }
}

// 0x0042CDB0..0x0042CDC1: ?Heap_DestroyOwnedSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Heap_DestroyOwnedSecondary_0042cdb0() {
    __asm {
    L_0042cdb0:
        test esi,esi
    L_0042cdb2:
        je short L_0042cdc1
    L_0042cdb4:
        push esi
    L_0042cdb5:
        call asm_FUN_0042cb60_0042cb60
    L_0042cdba:
        push esi
    L_0042cdbb:
        call asm_free_004524a1
    L_0042cdc0:
        pop ecx
    L_0042cdc1:
        ret
    }
}

// 0x00435220..0x0043524E: ?LegacyString_Duplicate@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_LegacyString_Duplicate_00435220() {
    __asm {
    L_00435220:
        mov eax,edi
    L_00435222:
        lea edx,[eax+1]
    L_00435225:
        mov cl,byte ptr [eax]
    L_00435227:
        inc eax
    L_00435228:
        test cl,cl
    L_0043522a:
        jne short L_00435225
    L_0043522c:
        sub eax,edx
    L_0043522e:
        inc eax
    L_0043522f:
        push eax
    L_00435230:
        call asm_malloc_00452706
    L_00435235:
        add esp,4
    L_00435238:
        test eax,eax
    L_0043523a:
        je short L_0043524e
    L_0043523c:
        push esi
    L_0043523d:
        mov esi,eax
    L_0043523f:
        mov ecx,edi
    L_00435241:
        sub esi,edi
    L_00435243:
        mov dl,byte ptr [ecx]
    L_00435245:
        mov byte ptr [esi+ecx],dl
    L_00435248:
        inc ecx
    L_00435249:
        test dl,dl
    L_0043524b:
        jne short L_00435243
    L_0043524d:
        pop esi
    L_0043524e:
        ret
    }
}

// 0x004386B0..0x00438722: ?Grow@LegacyString@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Grow_LegacyString_004386b0() {
    __asm {
    L_004386b0:
        push ebp
    L_004386b1:
        mov ebp,esp
    L_004386b3:
        push 0FFFFFFFFh
    L_004386b5:
        push 465370h
    L_004386ba:
        mov eax,dword ptr fs:[0]
    L_004386c0:
        push eax
    L_004386c1:
        mov dword ptr fs:[0],esp
    L_004386c8:
        sub esp,0Ch
    L_004386cb:
        mov eax,dword ptr [ebp+8]
    L_004386ce:
        push ebx
    L_004386cf:
        push esi
    L_004386d0:
        mov ebx,eax
    L_004386d2:
        or ebx,0Fh
    L_004386d5:
        cmp ebx,0FFFFFFFEh
    L_004386d8:
        push edi
    L_004386d9:
        mov esi,ecx
    L_004386db:
        mov dword ptr [ebp-10h],esp
    L_004386de:
        mov dword ptr [ebp-14h],esi
    L_004386e1:
        jbe short L_004386e7
    L_004386e3:
        mov ebx,eax
    L_004386e5:
        jmp short L_00438709
    L_004386e7:
        mov edi,dword ptr [esi+18h]
    L_004386ea:
        mov eax,0AAAAAAABh
    L_004386ef:
        mul ebx
    L_004386f1:
        mov ecx,edi
    L_004386f3:
        shr ecx,1
    L_004386f5:
        shr edx,1
    L_004386f7:
        cmp edx,ecx
    L_004386f9:
        jae short L_00438709
    L_004386fb:
        mov eax,0FFFFFFFEh
    L_00438700:
        sub eax,ecx
    L_00438702:
        cmp edi,eax
    L_00438704:
        ja short L_00438709
    L_00438706:
        lea ebx,[ecx+edi]
    L_00438709:
        lea ecx,[ebx+1]
    L_0043870c:
        push ecx
    L_0043870d:
        mov dword ptr [ebp-4],0
    L_00438714:
        call asm_operator_new_00452493
    L_00438719:
        mov edx,eax
    L_0043871b:
        add esp,4
    L_0043871e:
        mov dword ptr [ebp+8],edx
    L_00438721:
        TH10_REL8(0xeb, 0x00438721, VA_asm_FUN_0043874c_0043874c)
    }
}

// 0x0043874C..0x004387C1: FUN_0043874c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043874c_0043874c() {
    __asm {
    L_0043874c:
        mov ecx,dword ptr [ebp+0Ch]
    L_0043874f:
        test ecx,ecx
    L_00438751:
        mov dword ptr [ebp-4],0FFFFFFFFh
    L_00438758:
        jbe short L_0043877e
    L_0043875a:
        cmp dword ptr [esi+18h],10h
    L_0043875e:
        jb short L_00438765
    L_00438760:
        mov esi,dword ptr [esi+4]
    L_00438763:
        jmp short L_00438768
    L_00438765:
        add esi,4
    L_00438768:
        mov eax,ecx
    L_0043876a:
        shr ecx,2
    L_0043876d:
        mov edi,edx
    L_0043876f:
        rep movsd
    L_00438771:
        mov ecx,eax
    L_00438773:
        and ecx,3
    L_00438776:
        rep movsb
    L_00438778:
        mov esi,dword ptr [ebp-14h]
    L_0043877b:
        mov ecx,dword ptr [ebp+0Ch]
    L_0043877e:
        cmp dword ptr [esi+18h],10h
    L_00438782:
        jb short L_00438796
    L_00438784:
        mov ecx,dword ptr [esi+4]
    L_00438787:
        push ecx
    L_00438788:
        call asm_free_004524a1
    L_0043878d:
        mov edx,dword ptr [ebp+8]
    L_00438790:
        mov ecx,dword ptr [ebp+0Ch]
    L_00438793:
        add esp,4
    L_00438796:
        cmp ebx,10h
    L_00438799:
        lea eax,[esi+4]
    L_0043879c:
        mov byte ptr [eax],0
    L_0043879f:
        mov dword ptr [eax],edx
    L_004387a1:
        mov dword ptr [esi+18h],ebx
    L_004387a4:
        mov dword ptr [esi+14h],ecx
    L_004387a7:
        jb short L_004387ab
    L_004387a9:
        mov eax,edx
    L_004387ab:
        pop edi
    L_004387ac:
        mov byte ptr [eax+ecx],0
    L_004387b0:
        mov ecx,dword ptr [ebp-0Ch]
    L_004387b3:
        pop esi
    L_004387b4:
        mov dword ptr fs:[0],ecx
    L_004387bb:
        pop ebx
    L_004387bc:
        mov esp,ebp
    L_004387be:
        pop ebp
    L_004387bf:
        ret 8
    }
}

// Recovered semantic C++ definitions.

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void __cdecl entry_free_004524a1(void*);
#ifdef _MSC_VER
void* __cdecl operator new(uint32_t size);
#else
void* operator new(decltype(sizeof(0)) size);
#endif

HeapBuffer::HeapBuffer() : data(0) {
}

void* LegacyAllocator::Allocate(uint32_t count) {
    return ::operator new(count);
}

void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    entry_free_004524a1(memory);
}

uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
}

void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data != 0) {
        entry_free_00452422(data);
        buffer->data = 0;
    }
}
