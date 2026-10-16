// 0x0043D790 - Resolve a 0x34-byte archive record and select its stream.
// Executed in the cached-launch differential suite; it reloads table/stream
// after name lookup and ignores cursor selection errors. See
// reference/recovery_notes/sound_cached_stream_launch.md.
struct PlatformStreamRecord {
    unsigned char unknown_000[0x10];
    unsigned int offset_010;
    unsigned char unknown_014[0x08];
    unsigned int length_01c;
};

struct PlatformStreamState {
    unsigned char unknown_000[8];
    volatile unsigned int position_008;
    unsigned char unknown_00c[0x20];
    unsigned int cursor_02c;
    unsigned char unknown_030[0x4c];
    unsigned int memory_mode_07c;
    unsigned char unknown_080[0x0c];
    void* handle_08c;
    PlatformStreamRecord* record_090;

    __declspec(noinline) int Select(PlatformStreamRecord* record);
};

struct PlatformD790StreamOwner {
    unsigned char unknown_000[0x0c];
    PlatformStreamState* stream_00c;
};

struct PlatformD790ArchiveOwner {
    unsigned char unknown_000[0x1f84];
    PlatformStreamRecord* records_1f84;
    unsigned char unknown_1f88[0x3280];
    PlatformD790StreamOwner* stream_owner_5208;
};

struct PathName {
    char text[1];
    int FindBasenameSlot(void* owner);
    __declspec(noinline) int SelectArchiveEntry(
        PlatformD790ArchiveOwner* owner);
};

#pragma code_seg(".text$01archive")
__declspec(noinline) int PathName::SelectArchiveEntry(
        PlatformD790ArchiveOwner* owner) {
    if (owner->stream_owner_5208 == 0)
        return -1;
    int index = FindBasenameSlot(owner);
    PlatformStreamRecord* record =
        reinterpret_cast<PlatformStreamRecord*>(
            reinterpret_cast<unsigned char*>(owner->records_1f84)
            + index * 0x34);
    owner->stream_owner_5208->stream_00c->Select(record);
    return 0;
}
#pragma code_seg()
