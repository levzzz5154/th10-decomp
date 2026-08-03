#include "th10/archive/dat.hpp"
#include "th10/platform/file.hpp"
#include "th10/platform/memory_file.hpp"

#ifdef _MSC_VER
extern "C" void sub_434D10(void*);
extern "C" void* sub_452493(unsigned long);
extern "C" int sub_434F70(void*, void*);
extern "C" void* sub_435220(void);
#endif

// Concrete Win32-backed form of retail 0x00434C30.
bool DatArchive_OpenFile(DatArchive* archive, const char* path) {
    FileHandle* file = new FileHandle;
    if (!file) {
        return false;
    }
    return DatArchive_Open(archive, file, path);
}

// Embedded-resource-backed form of retail 0x00434CA0.
#ifdef _MSC_VER
__declspec(naked) bool DatArchive_OpenResource(
        DatArchive* archive, const char* resource_name) {
    __asm {
        push esi
        push edi
        mov esi, ecx
        mov edi, eax
        call sub_434D10
        push 10h
        call sub_452493
        add esp, 4
        test eax, eax
        je null_file
        mov dword ptr [eax+4], 0
        mov dword ptr [eax+8], 0
        mov dword ptr [eax+0Ch], 0
        mov dword ptr [eax], 46F328h
        jmp after_alloc
null_file:
        xor eax, eax
after_alloc:
        test eax, eax
        mov [esi+0Ch], eax
        je no_close
        push edi
        call sub_434F70
        test al, al
        je fail
        call sub_435220
        test eax, eax
        mov [esi+8], eax
        je fail
        pop edi
        mov al, 1
        pop esi
        ret
fail:
        call sub_434D10
no_close:
        pop edi
        xor al, al
        pop esi
        ret
    }
}
#else
bool DatArchive_OpenResource(
        DatArchive* archive, const char* resource_name) {
    ResourceFile* file = new ResourceFile;
    if (!file) {
        return false;
    }
    return DatArchive_Open(archive, file, resource_name);
}
#endif
