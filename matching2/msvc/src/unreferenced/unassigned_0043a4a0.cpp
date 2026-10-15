// 0x0043A4A0..0x0043A4BC: reset and close the MIDI device the record owns.
extern "C" __declspec(dllimport) int __stdcall midiOutReset(void* device);
extern "C" __declspec(dllimport) int __stdcall midiOutClose(void* device);

struct Object_0043a4a0 {
    void* device;                    // +0x00
    __declspec(noinline) void Close();
};

#pragma code_seg(".text$01accessor")
void Object_0043a4a0::Close() {
    if (device) {
        midiOutReset(device);
        midiOutClose(device);
        device = 0;
    }
}
#pragma code_seg()
