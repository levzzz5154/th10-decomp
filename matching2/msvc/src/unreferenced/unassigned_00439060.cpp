// 0x00439060..0x00439078: run the audio shutdown and release the record when
// the low bit of the flags argument is set.
extern "C" void __stdcall midi_manager_00446220(void* object);
extern "C" void __cdecl entry_free_004524a1(void* memory);

struct Object_00439060 {
    __declspec(noinline) void* Destroy(unsigned int flags);
};

#pragma code_seg(".text$01accessor")
void* Object_00439060::Destroy(unsigned int flags) {
    midi_manager_00446220(this);
    if (flags & 1) {
        entry_free_004524a1(this);
    }
    return this;
}
#pragma code_seg()
