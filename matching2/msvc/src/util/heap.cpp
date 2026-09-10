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
