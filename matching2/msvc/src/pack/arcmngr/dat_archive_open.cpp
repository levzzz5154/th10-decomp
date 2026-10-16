// DAT archive openers: 0x00434C30 opens an archive file on disk and
// 0x00434CA0 opens one embedded as an RCDATA resource.
//
// Both drop whatever the archive held, attach a fresh file backend, read the
// index through LoadIndex and keep a private copy of the path.  Any failure
// after the backend is attached closes the archive again.  The disk opener
// then reopens its backend by the owned filename so later reads can seek in
// it; that second Open's result is ignored.
//
// Retail passes the archive in ECX and the path in EAX, and the callees take
// the archive in ESI and the path copy's source in EDI.  Native LTCG picks
// those registers, so both bodies are compiled in the cluster
// build_support/layout/ltcg/dat_archive_open.json.
#include "th10/archive/dat_archive_types.hpp"
#include "th10/platform/memory_file.hpp"

extern "C" void* __cdecl asm_operator_new_00452493(unsigned int size);
char* LegacyString_Duplicate(const char* text);
extern "C" const char* g_dat_archive_read_mode;

inline void* __cdecl operator new(size_t, void* storage) { return storage; }

#pragma code_seg(".text$01open")
__declspec(noinline) bool DatArchive::Open(const char* path) {
    Close();
    void* storage = asm_operator_new_00452493(sizeof(FileHandle));
    file = storage ? new (storage) FileHandle : 0;
    if (!file)
        return false;
    if (LoadIndex(path)) {
        filename = LegacyString_Duplicate(path);
        if (filename) {
            file->Open(filename, g_dat_archive_read_mode);
            return true;
        }
    }
    Close();
    return false;
}
#pragma code_seg()

#pragma code_seg(".text$01openresource")
__declspec(noinline) bool DatArchive::OpenResource(const char* resource_name) {
    Close();
    void* storage = asm_operator_new_00452493(sizeof(ResourceFile));
    file = storage ? new (storage) ResourceFile : 0;
    if (!file)
        return false;
    if (LoadIndex(resource_name)) {
        filename = LegacyString_Duplicate(resource_name);
        if (filename)
            return true;
    }
    Close();
    return false;
}
#pragma code_seg()
