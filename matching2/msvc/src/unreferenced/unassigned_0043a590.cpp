// 0x0043A590: send a three-byte short MIDI message; the fourth byte is left unset.
extern "C" unsigned int (__stdcall* imp_midiOutShortMsg)(void* handle, unsigned int message);
struct MidiOutput_0043a590 {
    void* handle;
    unsigned int device;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall SendShortMessage(MidiOutput_0043a590* output, unsigned char status, unsigned char first, unsigned char second) {
    union {
        unsigned int packed;
        unsigned char bytes[4];
    } message;
    if (!output->handle) return 0;
    message.bytes[0] = status;
    message.bytes[1] = first;
    message.bytes[2] = second;
    return imp_midiOutShortMsg(output->handle, message.packed) != 0;
}
#pragma code_seg()
