// 0x0043A540..0x0043A56D: prepare and send the long message the record points
// at, reporting whether the send succeeded.
extern "C" __declspec(dllimport) int __stdcall midiOutPrepareHeader(void* device, void* header, unsigned int size);
extern "C" __declspec(dllimport) int __stdcall midiOutLongMsg(void* device, void* header, unsigned int size);

struct Object26 {
    void* device;                    // +0x00
    __declspec(noinline) int SendLong(void* header);
};

#pragma code_seg(".text$01accessor")
int Object26::SendLong(void* header) {
    if (!device) {
        return 0;
    }
    if (midiOutPrepareHeader(device, header, 0x40) != 0) {
        return 1;
    }
    return midiOutLongMsg(device, header, 0x40) != 0;
}
#pragma code_seg()
