// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../../src/game/mother/data_version_load_00420100.cpp"

// The real archive opener closure, as in dat_archive_open_00434c30: it is what
// gives the opener its archive in ECX and its path in EAX.
#include "../../../src/pack/arcmngr/dat_archive_open_00434c30.cpp"
#include "../../../src/pack/arcmngr/dat_archive_close_00434d10.cpp"
#include "../../../src/pack/arcmngr/legacy_string_duplicate_00435220.cpp"

// The file constructors stay external here, so no vtable is emitted.

extern "C" int __stdcall DatIndexDecode_0044b0d0(void* data, int size, int key);

// LoadIndex (0x00434F70) modelled only for its argument shape.
#pragma code_seg(".text$05loadindex")
__declspec(noinline) bool DatArchive::LoadIndex(const char* path) {
    if (!file)
        return false;
    unsigned int header[4];
    if (file->Open(path, g_dat_archive_read_mode) && file->Read(header, sizeof(header))) {
        entry_count = DatIndexDecode_0044b0d0(header, 16, 0x1B);
        if (entry_count > 0)
            return true;
    }
    delete file;
    file = 0;
    return false;
}
#pragma code_seg()

#pragma code_seg(".text$00a1context")
extern "C" int __stdcall DataVersionLoadContext(DatArchive* archives, const char** paths, int count) {
    int result = 0;
    for (int index = 0; index < count; ++index) {
        if (archives[index].Open(paths[index]))
            ++result;
        if (archives[index].OpenResource(paths[index] + 4))
            ++result;
        result += DataVersion_Load_00420100();
    }
    return result;
}
#pragma code_seg()

// Complete real archive read closure and log, supplying their register contracts.
#define ARCHIVE_READ_SECTION ".text$02e_read"
#define ARCHIVE_FIND_SECTION ".text$04find"
#define ARCHIVE_DECRYPT_SECTION ".text$08adecrypt"
#define ARCHIVE_LOAD_SECTION ".text$08cload"
#include "native_archive_read/read.cpp"
#include "../../../src/pack/arcmngr/archive_find.cpp"
#include "native_archive_read/decrypt.cpp"
#include "../../../src/core/zunlib/archive_load_file.cpp"
#include "resource_surface_loading_log.cpp"
