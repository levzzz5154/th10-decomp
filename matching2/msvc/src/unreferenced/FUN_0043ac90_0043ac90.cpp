// 0x0043AC90: load and parse the temporary file slot, then discard its buffer.
#include "th10/platform/temporary_track_0043ac90.hpp"
extern "C" void __cdecl crt_free(void*);
#pragma code_seg(".text$40temporary")
int __stdcall LoadTemporaryTrack(MidiSequencer* sequence, const char* name) {
    if (reinterpret_cast<SoundManager_0043a9b0*>(sequence)->LoadTrack(31, name))
        return -1;
    sequence->ParseLoadedFile(31); // Retail deliberately ignores parser failure.
    if (sequence->file_buffers[31]) {
        crt_free(sequence->file_buffers[31]);
        sequence->file_buffers[31] = 0;
    }
    sequence->file_buffers[31] = 0;
    return 0;
}
#pragma code_seg()
