// 0x0043A510..0x0043A532: reset and close the MIDI device, reporting success
// through the return value.
extern "C" __declspec(dllimport) int __stdcall midiOutReset(void* device);
extern "C" __declspec(dllimport) int __stdcall midiOutClose(void* device);

struct Object_0043a510 {
    void* device;                    // +0x00
    __declspec(noinline) int Close();
};

#pragma code_seg(".text$01accessor")
int Object_0043a510::Close() {
    if (!device) {
        return -1;
    }
    midiOutReset(device);
    midiOutClose(device);
    device = 0;
    return 0;
}
#pragma code_seg()
