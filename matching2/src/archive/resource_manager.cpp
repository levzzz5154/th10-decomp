#include "th10/archive/resource_manager.hpp"
#include "th10/archive/dat.hpp"
#include "th10/platform/file.hpp"

namespace {

DatArchive g_archives[kResourceArchiveCapacity];
uint32_t g_archive_count = 0;

bool StringsEqual(const char* left, const char* right) {
    while (*left == *right) {
        if (*left == 0) return true;
        ++left;
        ++right;
    }
    return false;
}

} // namespace

#ifdef _MSC_VER
extern "C" void* sub_4356F0(void*);
extern "C" int sub_434EF0(void*, void*);
extern "C" BYTE sub_435370(void*, const char*, const char*);
extern "C" char* __cdecl _strchr(const char*, int);
extern "C" void* __imp_GetFileSize;
extern "C" void* __imp_CloseHandle;
extern "C" void* off_46F230;
extern "C" void* dword_474908;
extern "C" void* loc_465388;
#endif

// Clean reconstruction of 0x004356F0.
DatArchive* Resource_FindArchive(const char* asset_path) {
    char archive_path[260];
    Resource_ArchivePathForAsset(asset_path, archive_path);
    for (uint32_t index = 0; index < g_archive_count; ++index) {
        if (g_archives[index].filename &&
                StringsEqual(g_archives[index].filename, archive_path)) {
            return &g_archives[index];
        }
    }
    return 0;
}

// Clean reconstruction of 0x004357D0.
bool Resource_RegisterArchive(const char* archive_path) {
    if (g_archive_count >= kResourceArchiveCapacity) {
        return false;
    }
    DatArchive* archive = &g_archives[g_archive_count];
    DatArchive_Initialize(archive);
    if (!DatArchive_OpenFile(archive, archive_path)) {
        return false;
    }
    ++g_archive_count;
    return true;
}

void Resource_CloseArchives() {
    for (uint32_t index = 0; index < g_archive_count; ++index) {
        DatArchive_Close(&g_archives[index]);
    }
    g_archive_count = 0;
}

// Clean reconstruction of 0x00435800.
uint8_t* Resource_LoadFile(const char* path, uint8_t* output) {
    DatArchive* archive = Resource_FindArchive(path);
    if (archive) {
        return DatArchive_Read(
            archive, File_AfterFirstSlash(path), output);
    }

    FileHandle file;
    // Retail deliberately follows the same size/load path after a failed
    // open.  FileHandle::GetSize and ReadWhole turn the invalid handle into a
    // null result, and the stack owner performs the single cleanup path.
    file.Open(path, "r");
    return (uint8_t*)file.ReadWhole(file.GetSize());
}

// Clean reconstruction of 0x004358E0.
#ifdef _MSC_VER
__declspec(naked) uint32_t Resource_GetFileSizeRetail(const char* path) {
    __asm {
        push 0FFFFFFFFh
        mov eax, fs:[0]
        push offset loc_465388
        push eax
        mov fs:[0], esp
        sub esp, 0Ch
        push ebx
        push ebp
        push esi
        push edi
        mov esi, ecx
        call sub_4356F0
        mov ebp, eax
        xor edi, edi
        cmp ebp, edi
        jz open_file
        push 2Fh
        push esi
        call _strchr
        add esp, 8
        cmp eax, edi
        jz skip_slash
        lea esi, [eax+1]
skip_slash:
        mov ebx, esi
        mov eax, ebp
        call sub_434EF0
        pop edi
        pop esi
        pop ebp
        pop ebx
        mov ecx, [esp+0Ch]
        mov fs:[0], ecx
        add esp, 18h
        retn
open_file:
        mov ebx, offset off_46F230
        mov [esp+10h], ebx
        mov dword ptr [esp+14h], 0FFFFFFFFh
        mov [esp+18h], edi
        mov [esp+24h], edi
        mov eax, dword_474908
        push eax
        push esi
        lea ecx, [esp+18h]
        call sub_435370
        mov eax, [esp+14h]
        cmp eax, 0FFFFFFFFh
        jz size_done
        push edi
        push eax
        call dword ptr [__imp_GetFileSize]
        mov edi, eax
        mov eax, [esp+14h]
size_done:
        cmp eax, 0FFFFFFFFh
        mov [esp+10h], ebx
        jz close_done
        push eax
        call dword ptr [__imp_CloseHandle]
close_done:
        mov ecx, [esp+1Ch]
        mov eax, edi
        pop edi
        pop esi
        pop ebp
        pop ebx
        mov fs:[0], ecx
        add esp, 18h
        retn
    }
}
#else
uint32_t Resource_GetFileSize(const char* path) {
    DatArchive* archive = Resource_FindArchive(path);
    if (archive) {
        return DatArchive_FindSize(
            archive, File_AfterFirstSlash(path));
    }

    FileHandle file;
    // Keep the failed-open cleanup and return path identical to the retail
    // stack owner: GetSize returns zero for INVALID_HANDLE_VALUE.
    file.Open(path, "r");
    return file.GetSize();
}
#endif
