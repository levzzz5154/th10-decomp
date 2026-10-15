// 0x0043A4C0: open a MIDI output device, reusing the handle when it is already open on it.
extern "C" unsigned int (__stdcall* imp_midiOutClose)(void* handle);
extern "C" unsigned int (__stdcall* imp_midiOutReset)(void* handle);
extern "C" unsigned int (__stdcall* imp_midiOutOpen)(void** handle, unsigned int device, void* callback, void* instance, unsigned int flags);
extern "C" void* g_supervisor_window;
struct MidiOutput_0043a4c0 {
    void* handle;
    unsigned int device;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall OpenMidiOutput_0043a4c0(MidiOutput_0043a4c0* output, unsigned int device) {
    if (output->handle) {
        if (output->device != device) {
            imp_midiOutReset(output->handle);
            imp_midiOutClose(output->handle);
            output->handle = 0;
        } else {
            return 0;
        }
    }
    output->device = device;
    return imp_midiOutOpen(&output->handle, device, g_supervisor_window, 0, 0x10000) != 0;
}
#pragma code_seg()
