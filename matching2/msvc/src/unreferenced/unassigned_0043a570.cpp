// 0x0043A570..0x0043A585: hand one short message to the MIDI device.
extern "C" __declspec(dllimport) int __stdcall midiOutShortMsg(void* device, unsigned int message);

struct Object_0043a570 {
    void* device;                    // +0x00
    __declspec(noinline) int Send(unsigned int message);
};

#pragma code_seg(".text$01accessor")
int Object_0043a570::Send(unsigned int message) {
    if (!device) {
        return 0;
    }
    return midiOutShortMsg(device, message) != 0;
}
#pragma code_seg()
