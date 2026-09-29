// Executed with maintained name lookup/selection by the cached-launch suite.
// See reference/recovery_notes/sound_cached_stream_launch_0043d950.md for
// invalid/null handles, callback record reloads and ignored Seek failure.
extern "C" unsigned int data_004977a4;
extern "C" __declspec(dllimport) unsigned int __stdcall SetFilePointer(
        void*, int, int*, unsigned int);

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

#pragma code_seg(".text$01select")
__declspec(noinline) int PlatformStreamState_0044DCA0::Select(
        PlatformStreamRecord_0044DCA0* record) {
    if (memory_mode_07c != 0) return (int)0x80004005u;
    void* handle = handle_08c;
    if (handle == (void*)-1) return (int)0x80004005u;
    record_090 = record;
    if (handle != 0) {
        SetFilePointer(handle, (int)(data_004977a4 + record->offset_010),
                       0, 0);
        position_008 = record_090->length_01c;
    }
    cursor_02c = position_008;
    return 0;
}
#pragma code_seg()
