// 0x0043D790 - Resolve a 0x34-byte archive record and select its stream.
struct PlatformStreamRecord_0044DCA0 {
    unsigned char unknown_000[0x10];
    unsigned int offset_010;
    unsigned char unknown_014[0x08];
    unsigned int length_01c;
};

struct PlatformStreamState_0044DCA0 {
    unsigned char unknown_000[8];
    volatile unsigned int position_008;
    unsigned char unknown_00c[0x20];
    unsigned int cursor_02c;
    unsigned char unknown_030[0x4c];
    unsigned int memory_mode_07c;
    unsigned char unknown_080[0x0c];
    void* handle_08c;
    PlatformStreamRecord_0044DCA0* record_090;

    __declspec(noinline) int Select(PlatformStreamRecord_0044DCA0* record);
};

struct PlatformD790StreamOwner {
    unsigned char unknown_000[0x0c];
    PlatformStreamState_0044DCA0* stream_00c;
};

struct PlatformD790ArchiveOwner {
    unsigned char unknown_000[0x1f84];
    PlatformStreamRecord_0044DCA0* records_1f84;
    unsigned char unknown_1f88[0x3280];
    PlatformD790StreamOwner* stream_owner_5208;
};

struct PathName_0043d2a0 {
    char text[1];
    int FindBasenameSlot_0043d2a0(void* owner);
    __declspec(noinline) int SelectArchiveEntry(
        PlatformD790ArchiveOwner* owner);
};

#pragma code_seg(".text$01archive")
__declspec(noinline) int PathName_0043d2a0::SelectArchiveEntry(
        PlatformD790ArchiveOwner* owner) {
    if (owner->stream_owner_5208 == 0)
        return -1;
    int index = FindBasenameSlot_0043d2a0(owner);
    PlatformStreamRecord_0044DCA0* record =
        reinterpret_cast<PlatformStreamRecord_0044DCA0*>(
            reinterpret_cast<unsigned char*>(owner->records_1f84)
            + index * 0x34);
    owner->stream_owner_5208->stream_00c->Select(record);
    return 0;
}
#pragma code_seg()
