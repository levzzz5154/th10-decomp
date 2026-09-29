// 0x0043A4C0: open a MIDI output device, reusing the handle when it is already open on it.
extern "C" unsigned int (__stdcall* data_004662a4)(void* handle);
extern "C" unsigned int (__stdcall* data_004662a8)(void* handle);
extern "C" unsigned int (__stdcall* data_004662ac)(void** handle, unsigned int device, void* callback, void* instance, unsigned int flags);
extern "C" void* data_00491c70;
struct MidiOutput_0043a4c0 {
    void* handle;
    unsigned int device;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall OpenMidiOutput_0043a4c0(MidiOutput_0043a4c0* output, unsigned int device) {
    if (output->handle) {
        if (output->device != device) {
            data_004662a8(output->handle);
            data_004662a4(output->handle);
            output->handle = 0;
        } else {
            return 0;
        }
    }
    output->device = device;
    return data_004662ac(&output->handle, device, data_00491c70, 0, 0x10000) != 0;
}
#pragma code_seg()
