// 0x0043A5C0..0x0043A5FE: copy the product name of a MIDI output device into
// the caller's buffer.  The midiOutGetDevCapsA result is ignored.  Nothing
// calls this any more; the device id arrives in ECX and the buffer in ESI, a
// convention only a native LTCG link chooses, so the region is compiled in its
// own cluster.
#include <string.h>

struct MidiOutCaps {
    unsigned short wMid;
    unsigned short wPid;
    unsigned int vDriverVersion;
    char szPname[32];
    unsigned short wTechnology;
    unsigned short wVoices;
    unsigned short wNotes;
    unsigned short wChannelMask;
    unsigned int dwSupport;
};

typedef unsigned int (__stdcall *MidiOutGetDevCapsFn)(
        unsigned int device, MidiOutCaps* caps, unsigned int size);

extern "C" MidiOutGetDevCapsFn imp_midiOutGetDevCapsA;

#pragma code_seg(".text$01midi")
__declspec(noinline) void MidiOut_GetDeviceName(unsigned int device, char* name) {
    MidiOutCaps caps;
    imp_midiOutGetDevCapsA(device, &caps, sizeof(caps));
    strcpy(name, caps.szPname);
}
#pragma code_seg()
