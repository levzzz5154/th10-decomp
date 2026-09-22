// 0x00435300..0x00435314: initialize the FileHandle state.
// Native LTCG exposes the incoming object pointer in EAX for this free
// initializer, preserving the retail result-register convention without
// inline assembly.
struct FileHandle_00435300 {
    void* vtable;
    int handle;
    int state;
};

#pragma code_seg(".text$01file_handle_init")
extern "C" __declspec(noinline) void FileHandle_Initialize_00435300(
    FileHandle_00435300* self) {
    self->vtable = (void*)0x0046F230;
    self->handle = -1;
    self->state = 0;
}
#pragma code_seg()
