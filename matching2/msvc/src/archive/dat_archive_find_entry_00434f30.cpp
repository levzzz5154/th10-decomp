#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
#include "../../layout/ltcg/archive_find_entry_followup_types.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434F30..0x00434F64: ?DatArchive_FindEntry@@
// Naked body preserves the retail register/stack ABI.
#if 0
extern "C" __declspec(naked) void __cdecl asm_DatArchive_FindEntry_00434f30() {
    __asm {
    L_00434f30:
        push edi
    L_00434f31:
        mov edi,dword ptr [eax]
    L_00434f33:
        test edi,edi
    L_00434f35:
        jne short L_00434f3b
    L_00434f37:
        xor eax,eax
    L_00434f39:
        pop edi
    L_00434f3a:
        ret
    L_00434f3b:
        push esi
    L_00434f3c:
        mov esi,dword ptr [eax+4]
    L_00434f3f:
        test esi,esi
    L_00434f41:
        jle short L_00434f5b
    L_00434f43:
        mov eax,dword ptr [edi]
    L_00434f45:
        push eax
    L_00434f46:
        push ebx
    L_00434f47:
        call asm_stricmp_0046054e
    L_00434f4c:
        add esp,8
    L_00434f4f:
        test eax,eax
    L_00434f51:
        je short L_00434f60
    L_00434f53:
        dec esi
    L_00434f54:
        add edi,10h
    L_00434f57:
        test esi,esi
    L_00434f59:
        jg short L_00434f43
    L_00434f5b:
        pop esi
    L_00434f5c:
        xor eax,eax
    L_00434f5e:
        pop edi
    L_00434f5f:
        ret
    L_00434f60:
        pop esi
    L_00434f61:
        mov eax,edi
    L_00434f63:
        pop edi
    L_00434f64:
        ret
    }
}
#endif

#pragma code_seg(".text$01find")
__declspec(noinline) ArchiveFindEntryRecord* DatArchive_FindEntry(
        ArchiveFindEntryIndex* archive, const char* name) {
    if (archive->entries == 0)
        return 0;
    ArchiveFindEntryRecord* entry = archive->entries;
    int remaining = archive->entry_count;
    while (remaining > 0) {
        if (archive_find_stricmp(name, entry->name) == 0)
            return entry;
        --remaining;
        ++entry;
    }
    return 0;
}
#pragma code_seg()
