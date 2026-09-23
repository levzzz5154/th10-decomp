// 0x004357D0..0x004357F3: append one successfully opened DAT archive to the
// global archive table. The retail region has a private internal convention:
// the path is live in EAX, while this function computes the archive receiver
// in ECX for DatArchive::Open. The native-LTCG context models that call edge.

struct DatArchiveRecord_004357D0 {
    void* entries;          // +0x00
    int entry_count;        // +0x04
    char* filename;         // +0x08
    void* file;             // +0x0C

    // The context supplies a compiler-only ABI anchor for the retail open
    // method at 0x00434C30. That anchor is never exported as game code.
    __declspec(noinline) bool Open(const char* archive_path);
};

typedef char DatArchiveRecord_004357D0_must_be_16_bytes[
    sizeof(DatArchiveRecord_004357D0) == 0x10 ? 1 : -1];

extern "C" unsigned char data_00477850;
extern "C" unsigned char data_004923b0;

#pragma code_seg(".text$01register")
__declspec(noinline) bool __cdecl Resource_RegisterArchive(
        const char* archive_path) {
    int* archive_count = reinterpret_cast<int*>(&data_00477850);
    DatArchiveRecord_004357D0* archives =
        reinterpret_cast<DatArchiveRecord_004357D0*>(&data_004923b0);
    DatArchiveRecord_004357D0* archive = archives + *archive_count;

    if (!archive->Open(archive_path))
        return false;

    ++*archive_count;
    return true;
}
#pragma code_seg()
