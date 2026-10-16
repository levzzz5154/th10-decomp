#include "../../../src/core/main/fun.cpp_4390e0.cpp"
extern "C" __declspec(noinline) int ShutdownMidi(MidiSequencer*);
extern "C" unsigned char* __stdcall ShutdownReadFile(const char*,int*,int);
struct ShutdownTextLog { char* Append(char*, ...); };
// Compiler-only reconstruction of the real 0x43A9B0 caller's operations.
// Unselected: its calling convention and bytes are not claimed as game code.
extern "C" __declspec(noinline) void CleanupMidi(MidiSequencer*);
extern "C" void __cdecl CleanupDelete_004524a1(void*);
#pragma code_seg(".text$30context")
extern "C" __declspec(noinline) int __stdcall ShutdownCallerContext(MidiSequencer* manager,int slot,const char* path) {
 if(manager->current_file_slot==slot) ShutdownMidi(manager);
 if(manager->file_buffers[slot]) {
  crt_free(manager->file_buffers[slot]);
  manager->file_buffers[slot]=0;
 }
 manager->file_buffers[slot]=0;
 manager->file_buffers[slot]=ShutdownReadFile(path,0,0);
 if(manager->file_buffers[slot]) return 0;
 reinterpret_cast<ShutdownTextLog*>(0x474F70)->Append(reinterpret_cast<char*>(0x46F908),path);
 // Real GameMain cleanup: reload global, cleanup, delete, clear global.
 MidiSequencer* owned=window_midi_manager;
 if(owned) { CleanupMidi(owned); CleanupDelete_004524a1(owned); }
 window_midi_manager=0;
 return -1;
}

// Compiler-only ABI anchor copied verbatim from maintained midi_file.cpp.
#pragma code_seg(".text$17releaseanchor")
void MidiSequencer::ReleaseTracks() {
    for (int index = 0; index < track_count; ++index) {
        if (tracks[index].data) {
            crt_free(tracks[index].data);
            tracks[index].data = 0;
        }
    }
    if (tracks) {
        crt_free(tracks);
        tracks = 0;
    }
    tracks = 0;
    track_count = 0;
}

