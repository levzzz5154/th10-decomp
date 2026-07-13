#include "th10/archive/dat.hpp"
#include "th10/platform/file.hpp"

// Concrete Win32-backed form of retail 0x00434C30.
bool DatArchive_OpenFile(DatArchive* archive, const char* path) {
    FileHandle* file = new FileHandle;
    if (!file) {
        return false;
    }
    return DatArchive_Open(archive, file, path);
}
