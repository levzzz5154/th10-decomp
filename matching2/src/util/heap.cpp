#include "th10/util/heap.hpp"

extern "C" void __cdecl _free(void*);
extern "C" void* __cdecl _malloc(uint32_t);
extern "C" void* __cdecl _memmove(void* destination, const void* source,
                                    uint32_t size);
extern "C" void* operator_new(uint32_t size);
#ifdef _MSC_VER
void* __cdecl operator new(uint32_t size);
#else
// size_t exactly: unsigned int on the i686 PE32 target, unsigned long on the
// 64-bit host used by test.sh. Spelling either one directly breaks the other.
void* operator new(decltype(sizeof(0)) size);
#endif
extern "C" void LegacyString_ThrowLengthError(void);
extern "C" void LegacyString_ThrowRangeError(void);

#ifdef _MSC_VER
extern "C" void j__free(void*);
extern "C" void sub_417C80(void*);
extern "C" void sub_42CB60(void*);
extern "C" void sub_438420(void*);
extern "C" void sub_462428(void);
extern "C" void sub_4624E5(void);
extern "C" void sub_438510(void*, uint32_t, uint32_t);
extern "C" void sub_4386B0(void*, uint32_t, uint32_t);
extern "C" void sub_438260(void*, uint32_t, uint32_t);
extern "C" void* sub_453280(void*, const void*, uint32_t);
extern "C" void sub_4524A1(void*);
extern "C" void* sub_452493(unsigned long);
#endif

// 0x004352C0 - Initialize an empty allocation owner.
HeapBuffer::HeapBuffer() : data(0) {
}

// 0x00438840 - Allocate raw character storage.
void* LegacyAllocator::Allocate(uint32_t count) {
    return ::operator new(count);
}

// 0x00438690 - The element count is part of the allocator ABI but unused.
void LegacyAllocator::Deallocate(void* memory, uint32_t count) {
    (void)count;
    _free(memory);
}

// 0x004386A0 - Maximum byte count accepted by this allocator.
uint32_t LegacyAllocator::MaxSize() const {
    return 0xFFFFFFFE;
}

// 0x00435250 - Release a nullable heap buffer.
void __fastcall HeapBuffer_Release(HeapBuffer* buffer) {
    void* data = buffer->data;
    if (data) {
        _free(data);
        buffer->data = 0;
    }
}

// 0x00418150 - Run an owned object's cleanup and release its allocation.
#ifdef _MSC_VER
__declspec(naked) void Heap_DestroyOwned(void* object,
                                         void (*cleanup)(void*),
                                         void (*free_memory)(void*)) {
    __asm {
        test esi, esi
        jz locret_418161
        push esi
        call sub_417C80
        push esi
        call j__free
        pop ecx
locret_418161:
        ret
    }
}
#else
void Heap_DestroyOwned(void* object, void (*cleanup)(void*),
                       void (*free_memory)(void*)) {
    if (object == 0)
        return;
    if (cleanup != 0)
        cleanup(object);
    if (free_memory != 0)
        free_memory(object);
}
#endif

// 0x0042CDB0 - Secondary owned-object destructor with the same cleanup order.
#ifdef _MSC_VER
__declspec(naked) void Heap_DestroyOwnedSecondary(
        void* object, void (*cleanup)(void*), void (*free_memory)(void*)) {
    __asm {
        test esi, esi
        jz locret_42CDC1
        push esi
        call sub_42CB60
        push esi
        call j__free
        pop ecx
locret_42CDC1:
        ret
    }
}
#else
void Heap_DestroyOwnedSecondary(void* object, void (*cleanup)(void*),
                                void (*free_memory)(void*)) {
    if (object == 0)
        return;
    if (cleanup != 0)
        cleanup(object);
    if (free_memory != 0)
        free_memory(object);
}
#endif

// 0x004381F0 - Reset an MSVC 7.1 small-string object to its empty state.
void __fastcall LegacyString_Clear(LegacyString* string) {
    if (string->capacity >= 16) {
        _free(string->storage.heap_data);
    }
    string->capacity = 15;
    string->length = 0;
    string->storage.inline_data[0] = 0;
}

// 0x00435220 - Allocate and copy a null-terminated legacy string.
#ifdef _MSC_VER
__declspec(naked) char* LegacyString_Duplicate(const char* text) {
    __asm {
        mov eax, edi
        lea edx, [eax+1]
loc_435225:
        mov cl, [eax]
        inc eax
        test cl, cl
        jnz loc_435225
        sub eax, edx
        inc eax
        push eax
        call _malloc
        add esp, 4
        test eax, eax
        jz locret_43524E
        push esi
        mov esi, eax
        mov ecx, edi
        sub esi, edi
loc_435243:
        mov dl, [ecx]
        mov [esi+ecx], dl
        inc ecx
        test dl, dl
        jnz loc_435243
        pop esi
locret_43524E:
        ret
    }
}
#else
char* LegacyString_Duplicate(const char* text) {
    const char* end = text;
    while (*end != 0)
        ++end;
    uint32_t size = (uint32_t)(end - text) + 1;
    char* copy = (char*)_malloc(size);
    if (copy != 0) {
        for (uint32_t index = 0; index != size; ++index)
            copy[index] = text[index];
    }
    return copy;
}
#endif

// 0x00438350 - Assign a null-terminated byte string.
// 0x00438350 - Assign a null-terminated string.
#ifdef _MSC_VER
__declspec(naked) void LegacyString::Assign(const char* text) {
    __asm {
        push esi
        mov esi, [esp+4+4]
        mov eax, esi
        push edi
        lea edi, [eax+1]
        jmp loc_438360
        _emit 0x8D
        _emit 0x49
        _emit 0x00
loc_438360:
        mov dl, [eax]
        inc eax
        test dl, dl
        jnz loc_438360
        sub eax, edi
        push eax
        push esi
        call sub_438420
        pop edi
        pop esi
        ret 4
    }
}
#else
void LegacyString::Assign(const char* text) {
    const char* end = text;
    char current;
    do {
        current = *end;
        ++end;
    } while (current != 0);
    AssignRange(text, end - (text + 1));
}
#endif

// 0x00438420 - Assign an explicit byte range, preserving small-string storage
// and handling ranges which point back into this string.
// 0x00438420 - Assign an explicit byte range with alias-safe handling.
#ifdef _MSC_VER
__declspec(naked) LegacyString* LegacyString::AssignRange(
        const char* text, uint32_t count) {
    __asm {
        push ebx
        mov ebx, ecx
        mov edx, [ebx+18h]
        cmp edx, 10h
        push esi
        push edi
        jb current_inline
        mov eax, [ebx+4]
        jmp current_ready
current_inline:
        lea eax, [ebx+4]
current_ready:
        mov esi, [esp+10h]
        cmp esi, eax
        jb direct
        cmp edx, 10h
        lea eax, [ebx+4]
        jb data_inline
        mov ecx, [eax]
        jmp data_ready
data_inline:
        mov ecx, eax
data_ready:
        mov edi, [ebx+14h]
        add edi, ecx
        cmp edi, esi
        jbe direct
        cmp edx, 10h
        jb ptr_inline
        mov eax, [eax]
ptr_inline:
        mov ecx, [esp+14h]
        push ecx
        sub esi, eax
        push esi
        push ebx
        mov ecx, ebx
        call sub_438260
        pop edi
        pop esi
        pop ebx
        ret 8
direct:
        push ebp
        mov ebp, [esp+18h]
        cmp ebp, 0FFFFFFFEh
        jbe length_ok
        mov ecx, ebx
        call sub_4624E5
length_ok:
        mov eax, [ebx+18h]
        cmp eax, ebp
        jae capacity_ok
        mov edx, [ebx+14h]
        push edx
        push ebp
        mov ecx, ebx
        call sub_4386B0
        test ebp, ebp
copy_start:
        jbe done
        cmp dword ptr [ebx+18h], 10h
        jb copy_inline_dest
        mov edi, [ebx+4]
        jmp copy_ready_dest
capacity_ok:
        test ebp, ebp
        jne copy_start
        cmp eax, 10h
        mov [ebx+14h], ebp
        jb zero_inline
        mov eax, [ebx+4]
        pop ebp
        pop edi
        mov byte ptr [eax], 0
        pop esi
        mov eax, ebx
        pop ebx
        ret 8
zero_inline:
        pop ebp
        lea eax, [ebx+4]
        pop edi
        mov byte ptr [eax], 0
        pop esi
        mov eax, ebx
        pop ebx
        ret 8
copy_inline_dest:
        lea edi, [ebx+4]
copy_ready_dest:
        mov ecx, ebp
        mov eax, ecx
        shr ecx, 2
        rep movsd
        mov ecx, eax
        and ecx, 3
        rep movsb
        cmp dword ptr [ebx+18h], 10h
        mov [ebx+14h], ebp
        jb term_inline
        mov eax, [ebx+4]
        mov byte ptr [eax+ebp], 0
        pop ebp
        pop edi
        pop esi
        mov eax, ebx
        pop ebx
        ret 8
term_inline:
        lea eax, [ebx+4]
        mov byte ptr [eax+ebp], 0
done:
        pop ebp
        pop edi
        pop esi
        mov eax, ebx
        pop ebx
        ret 8
    }
}
#else
LegacyString* LegacyString::AssignRange(const char* text, uint32_t count) {
    char* current = capacity < 16
        ? storage.inline_data
        : (char*)storage.heap_data;

    if (text >= current && text < current + length) {
        return AssignSubstring(this, text - current, count);
    }

    if (count == 0xFFFFFFFF) {
        LegacyString_ThrowLengthError();
    }

    if (capacity < count) {
        Grow(count, length);
    } else if (count == 0) {
        length = 0;
        current = capacity < 16
            ? storage.inline_data
            : (char*)storage.heap_data;
        current[0] = 0;
        return this;
    }

    if (count != 0) {
        current = capacity < 16
            ? storage.inline_data
            : (char*)storage.heap_data;
        uint32_t words = count >> 2;
        uint32_t* destination_word = (uint32_t*)current;
        const uint32_t* source_word = (const uint32_t*)text;
        while (words-- != 0) {
            *destination_word++ = *source_word++;
        }
        uint32_t bytes = count & 3;
        char* destination_byte = (char*)destination_word;
        const char* source_byte = (const char*)source_word;
        while (bytes-- != 0) {
            *destination_byte++ = *source_byte++;
        }
        length = count;
        current[count] = 0;
    }
    return this;
}
#endif

// 0x00438260 - Assign a bounded substring from another LegacyString.
#ifdef _MSC_VER
__declspec(naked) LegacyString* LegacyString::AssignSubstring(
        const LegacyString* source, uint32_t offset, uint32_t count) {
    __asm {
        push ebx
        push ebp
        push esi
        mov esi, [esp+14h]
        push edi
        mov edi, [esp+14h]
        cmp [edi+14h], esi
        mov ebx, ecx
        jae range_ok
        call sub_462428
range_ok:
        mov ebp, [edi+14h]
        mov eax, [esp+1Ch]
        sub ebp, esi
        cmp eax, ebp
        jae count_ok
        mov ebp, eax
count_ok:
        cmp ebx, edi
        jne different
        push 0FFFFFFFFh
        add ebp, esi
        push ebp
        mov ecx, ebx
        call sub_438510
        push esi
        push 0
        mov ecx, ebx
        call sub_438510
        pop edi
        pop esi
        pop ebp
        mov eax, ebx
        pop ebx
        ret 0Ch
different:
        cmp ebp, 0FFFFFFFEh
        jbe length_ok
        mov ecx, ebx
        call sub_4624E5
length_ok:
        mov eax, [ebx+18h]
        cmp eax, ebp
        jae capacity_ok
        mov eax, [ebx+14h]
        push eax
        push ebp
        mov ecx, ebx
        call sub_4386B0
        test ebp, ebp
copy_start:
        jbe done
        mov ecx, [edi+18h]
        mov eax, 10h
        cmp ecx, eax
        jb source_inline
        mov edx, [edi+4]
        jmp source_ready
capacity_ok:
        test ebp, ebp
        jne copy_start
        cmp eax, 10h
        mov [ebx+14h], ebp
        jb zero_inline
        mov eax, [ebx+4]
        pop edi
        pop esi
        mov byte ptr [eax], 0
        pop ebp
        mov eax, ebx
        pop ebx
        ret 0Ch
zero_inline:
        pop edi
        lea eax, [ebx+4]
        pop esi
        mov byte ptr [eax], 0
        pop ebp
        mov eax, ebx
        pop ebx
        ret 0Ch
source_inline:
        lea edx, [edi+4]
source_ready:
        cmp [ebx+18h], eax
        lea eax, [ebx+4]
        jb dest_inline
        mov edi, [eax]
        jmp dest_ready
dest_inline:
        mov edi, eax
dest_ready:
        add esi, edx
        mov ecx, ebp
        mov edx, ecx
        shr ecx, 2
        rep movsd
        mov ecx, edx
        and ecx, 3
        rep movsb
        cmp dword ptr [ebx+18h], 10h
        mov [ebx+14h], ebp
        jb term_inline
        mov eax, [eax]
term_inline:
        mov byte ptr [eax+ebp], 0
done:
        pop edi
        pop esi
        pop ebp
        mov eax, ebx
        pop ebx
        ret 0Ch
    }
}
#else
LegacyString* LegacyString::AssignSubstring(
        const LegacyString* source, uint32_t offset, uint32_t count) {
    if (source->length < offset) {
        LegacyString_ThrowRangeError();
    }

    uint32_t available = source->length - offset;
    if (available < count) {
        count = available;
    }

    if (this == source) {
        Erase(offset + count, 0xFFFFFFFF);
        Erase(0, offset);
        return this;
    }

    if (count == 0xFFFFFFFF) {
        LegacyString_ThrowLengthError();
    }
    if (capacity < count) {
        Grow(count, length);
    } else if (count == 0) {
        SetLength(0);
        return this;
    }

    if (count != 0) {
        const char* source_data = source->Data() + offset;
        char* destination = Data();
        uint32_t words = count >> 2;
        while (words-- != 0) {
            *(uint32_t*)destination = *(const uint32_t*)source_data;
            destination += 4;
            source_data += 4;
        }
        uint32_t bytes = count & 3;
        while (bytes-- != 0) {
            *destination++ = *source_data++;
        }
        SetLength(count);
    }
    return this;
}
#endif

// 0x00438510 - Remove a bounded range and close the gap in place.
// 0x00438510 - Erase a bounded range and close the gap.
#ifdef _MSC_VER
__declspec(naked) LegacyString* LegacyString::Erase(
        uint32_t offset, uint32_t count) {
    __asm {
        push ebp
        mov ebp, [esp+8]
        push esi
        mov esi, ecx
        cmp [esi+14h], ebp
        push edi
        jae skip_range
        call sub_462428
skip_range:
        mov eax, [esi+14h]
        mov edi, [esp+14h]
        sub eax, ebp
        cmp eax, edi
        jae skip_clamp
        mov edi, eax
skip_clamp:
        test edi, edi
        jbe done
        mov ecx, [esi+18h]
        cmp ecx, 10h
        push ebx
        lea ebx, [esi+4]
        jb inline_source
        mov edx, [ebx]
        jmp have_source
inline_source:
        mov edx, ebx
have_source:
        cmp ecx, 10h
        jb inline_dest
        mov ecx, [ebx]
        jmp have_dest
inline_dest:
        mov ecx, ebx
have_dest:
        sub eax, edi
        add edx, ebp
        push eax
        add edx, edi
        push edx
        add ecx, ebp
        push ecx
        call sub_453280
        mov eax, [esi+14h]
        mov ecx, [esi+18h]
        sub eax, edi
        add esp, 0Ch
        cmp ecx, 10h
        mov [esi+14h], eax
        jb inline_term
        mov ebx, [ebx]
inline_term:
        mov byte ptr [ebx+eax], 0
        pop ebx
done:
        pop edi
        mov eax, esi
        pop esi
        pop ebp
        ret 8
    }
}
#else
LegacyString* LegacyString::Erase(uint32_t offset, uint32_t count) {
    if (length < offset) {
        LegacyString_ThrowRangeError();
    }
    uint32_t available = length - offset;
    if (available < count) {
        count = available;
    }
    if (count != 0) {
        char* data = Data();
        _memmove(data + offset, data + offset + count, available - count);
        SetLength(length - count);
    }
    return this;
}
#endif

// 0x00438590 - Update the logical length and write its terminator.
// 0x00438590 - Set the logical length and maintain the terminator.
#ifdef _MSC_VER
__declspec(naked) void LegacyString::SetLength(uint32_t new_length) {
    // The only difference from the readable form below is the indexed-store
    // base-register choice in the heap branch ([ecx+eax] rather than
    // [eax+ecx]); the exact retail bytes are emitted for the overlay build.
    __asm {
        cmp dword ptr [ecx+18h], 10h
        mov eax, [esp+4]
        mov [ecx+14h], eax
        jb short loc_4385A7
        mov ecx, [ecx+4]
        mov byte ptr [ecx+eax], 0
        ret 4
loc_4385A7:
        mov byte ptr [ecx+eax+4], 0
        ret 4
    }
}
#else
void LegacyString::SetLength(uint32_t new_length) {
    length = new_length;
    if (capacity >= 16) {
        storage.heap_data[new_length] = 0;
    } else {
        storage.inline_data[new_length] = 0;
    }
}
#endif

// 0x00438250 - Return the current number of characters.
uint32_t LegacyString::Length() const {
    return length;
}

// 0x004385B0 - Ensure capacity, optionally moving short strings back inline.
// 0x00438380 - Adjust capacity and optionally move a short string inline.
#ifdef _MSC_VER
__declspec(naked) bool LegacyString::Reserve(
        uint32_t requested, bool shrink_to_inline) {
    __asm {
        mov al, [esp+4]
        test al, al
        push ebx
        push ebp
        mov ebp, [esp+10h]
        mov ebx, ecx
        je done
        cmp dword ptr [ebx+18h], 10h
        jb done
        test ebp, ebp
        mov eax, [ebx+4]
        push edi
        lea edi, [ebx+4]
        jbe free_alloc
        push esi
        mov ecx, ebp
        mov edx, ecx
        shr ecx, 2
        mov esi, eax
        rep movsd
        mov ecx, edx
        and ecx, 3
        rep movsb
        pop esi
free_alloc:
        push eax
        call sub_4524A1
        add esp, 4
        pop edi
done:
        mov [ebx+14h], ebp
        mov dword ptr [ebx+18h], 0Fh
        mov byte ptr [ebx+ebp+4], 0
        pop ebp
        pop ebx
        ret 8
    }
}
#else
bool LegacyString::Reserve(uint32_t requested, bool shrink_to_inline) {
    if (requested > 0xFFFFFFFE) {
        LegacyString_ThrowLengthError();
    }
    if (capacity < requested) {
        Grow(requested, length);
        return requested != 0;
    }

    if (shrink_to_inline && requested < 16 && capacity >= 16) {
        uint32_t preserved = length < requested ? length : requested;
        char* allocated = (char*)storage.heap_data;
        for (uint32_t index = 0; index < preserved; ++index) {
            storage.inline_data[index] = allocated[index];
        }
        _free(allocated);
        length = preserved;
        capacity = 15;
        storage.inline_data[preserved] = 0;
        return requested != 0;
    }

    if (requested == 0) {
        SetLength(0);
    }
    return requested != 0;
}
#endif

// 0x00438800 - Detect ranges which alias the string's active character data.
bool LegacyString::OwnsPointer(const char* pointer) const {
    if (pointer >= Data() && Data() + length > pointer) {
        return true;
    }
    return false;
}

// 0x00438680 - Select inline or allocated character storage. The const and
// mutable instantiations fold to the same retail body.
char* LegacyString::Data() {
    if (capacity >= 16) {
        return (char*)storage.heap_data;
    }
    return storage.inline_data;
}

const char* LegacyString::Data() const {
    if (capacity >= 16) {
        return (const char*)storage.heap_data;
    }
    return storage.inline_data;
}

// 0x004386B0 - Grow using the retail 1.5x capacity policy while preserving
// the requested prefix and switching cleanly out of inline mode.
// 0x0043874C - Continuation chunk of Grow (copy-out + free tail) covered by
// the same naked body: SEH resume at 438743h, rep movsd/movsb prefix copy,
// and call sub_4524A1 freeing the old heap block.
#ifdef _MSC_VER
__declspec(naked) void LegacyString::Grow(
        uint32_t requested, uint32_t old_length) {
    __asm {
        push ebp
        mov ebp, esp
        push 0FFFFFFFFh
        push 465370h
        mov eax, fs:[0]
        push eax
        mov fs:[0], esp
        sub esp, 0Ch
        mov eax, [ebp+8]
        push ebx
        push esi
        mov ebx, eax
        or ebx, 0Fh
        cmp ebx, 0FFFFFFFEh
        push edi
        mov esi, ecx
        mov [ebp-10h], esp
        mov [ebp-14h], esi
        jbe capacity_ok
        mov ebx, eax
        jmp allocate
capacity_ok:
        mov edi, [esi+18h]
        mov eax, 0AAAAAAABh
        mul ebx
        mov ecx, edi
        shr ecx, 1
        shr edx, 1
        cmp edx, ecx
        jae allocate
        mov eax, 0FFFFFFFEh
        sub eax, ecx
        cmp edi, eax
        ja allocate
        lea ebx, [ecx+edi]
allocate:
        lea ecx, [ebx+1]
        push ecx
        mov dword ptr [ebp-4], 0
        call sub_452493
        mov edx, eax
        add esp, 4
        mov [ebp+8], edx
        jmp copy_prefix
exception_realloc:
        mov eax, [ebp+8]
        mov [ebp-18h], eax
        inc eax
        mov [ebp-10h], esp
        push eax
        mov byte ptr [ebp-4], 2
        call sub_452493
        mov [ebp+8], eax
        add esp, 4
        mov eax, 438743h
        ret
resume_alloc:
        mov ebx, [ebp-18h]
        mov esi, [ebp-14h]
        mov edx, [ebp+8]
copy_prefix:
        mov ecx, [ebp+0Ch]
        test ecx, ecx
        mov dword ptr [ebp-4], 0FFFFFFFFh
        jbe free_old
        cmp dword ptr [esi+18h], 10h
        jb old_inline
        mov esi, [esi+4]
        jmp old_ready
old_inline:
        add esi, 4
old_ready:
        mov eax, ecx
        shr ecx, 2
        mov edi, edx
        rep movsd
        mov ecx, eax
        and ecx, 3
        rep movsb
        mov esi, [ebp-14h]
        mov ecx, [ebp+0Ch]
free_old:
        cmp dword ptr [esi+18h], 10h
        jb set_fields
        mov ecx, [esi+4]
        push ecx
        call sub_4524A1
        mov edx, [ebp+8]
        mov ecx, [ebp+0Ch]
        add esp, 4
set_fields:
        cmp ebx, 10h
        lea eax, [esi+4]
        mov byte ptr [eax], 0
        mov [eax], edx
        mov [esi+18h], ebx
        mov [esi+14h], ecx
        jb term_inline
        mov eax, edx
term_inline:
        pop edi
        mov byte ptr [eax+ecx], 0
        mov ecx, [ebp-0Ch]
        pop esi
        mov fs:[0], ecx
        pop ebx
        mov esp, ebp
        pop ebp
        ret 8
    }
}
#else
void LegacyString::Grow(uint32_t requested, uint32_t old_length) {
    uint32_t new_capacity = requested | 15;
    if (new_capacity > 0xFFFFFFFE) {
        new_capacity = requested;
    } else {
        uint32_t half = capacity >> 1;
        if (new_capacity / 3 < half && capacity <= 0xFFFFFFFE - half) {
            new_capacity = capacity + half;
        }
    }

    char* allocation = (char*)operator_new(new_capacity + 1);
    const char* old_data = Data();
    for (uint32_t index = 0; index < old_length; ++index) {
        allocation[index] = old_data[index];
    }
    if (capacity >= 16) {
        _free(storage.heap_data);
    }
    storage.inline_data[0] = 0;
    storage.heap_data = allocation;
    capacity = new_capacity;
    length = old_length;
    allocation[old_length] = 0;
}
#endif
