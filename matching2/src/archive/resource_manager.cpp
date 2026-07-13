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
    if (!file.Open(path, "r")) {
        return 0;
    }
    return (uint8_t*)file.ReadWhole(file.GetSize());
}

// Clean reconstruction of 0x004358E0.
uint32_t Resource_GetFileSize(const char* path) {
    DatArchive* archive = Resource_FindArchive(path);
    if (archive) {
        return DatArchive_FindSize(
            archive, File_AfterFirstSlash(path));
    }

    FileHandle file;
    if (!file.Open(path, "r")) {
        return 0;
    }
    return file.GetSize();
}
