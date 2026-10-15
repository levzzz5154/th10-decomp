// 0x00439040..0x00439058: destroy the resource manager and release the record
// when the low bit of the flags argument is set.
extern "C" void __stdcall d3d_destroy_00438880(void* object);
extern "C" void __cdecl crt_free_startup(void* memory);

struct Object_00439040 {
    __declspec(noinline) void* Destroy(unsigned int flags);
};

#pragma code_seg(".text$01accessor")
void* Object_00439040::Destroy(unsigned int flags) {
    d3d_destroy_00438880(this);
    if (flags & 1) {
        crt_free_startup(this);
    }
    return this;
}
#pragma code_seg()
