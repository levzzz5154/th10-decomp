#include "th10/platform/file.hpp"
#include "th10/archive/resource_manager.hpp"

// Clean conventional-ABI form of 0x004356D0.
const char* File_AfterFirstSlash(const char* path) {
    const char* cursor = path;
    while (*cursor != 0) {
        if (*cursor == '/') {
            return cursor + 1;
        }
        ++cursor;
    }
    return path;
}

// Path normalization performed by retail 0x004356F0: an asset such as
// "th10/stage01.ecl" belongs to the archive named "th10.dat".
void Resource_ArchivePathForAsset(
        const char* asset_path, char archive_path[260]) {
    uint32_t index = 0;
    int32_t slash = -1;
    while (asset_path[index] != 0 && index < 259) {
        archive_path[index] = asset_path[index];
        if (slash < 0 && asset_path[index] == '/') {
            slash = (int32_t)index;
        }
        ++index;
    }
    archive_path[index] = 0;
    if (slash >= 0) {
        archive_path[slash + 0] = '.';
        archive_path[slash + 1] = 'd';
        archive_path[slash + 2] = 'a';
        archive_path[slash + 3] = 't';
        archive_path[slash + 4] = 0;
    }
}
