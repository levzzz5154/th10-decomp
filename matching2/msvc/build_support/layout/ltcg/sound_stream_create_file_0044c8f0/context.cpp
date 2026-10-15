// Compiler context only; never selected as recovered game code. The stop,
// cursor open, constructor and fill bodies are co-compiled so each takes its
// receiver and arguments where the real one does.
#include "../../../../src/core/zwave/sound_stream_create_file_0044c8f0.cpp"
#include "stop.cpp"
#include "../sound_interfaces_dependencies/fill.cpp"
#include "../../../../src/core/zwave/recovery_initialize_single_interface_0044d6a0.cpp"
#include "open.cpp"
#include "../sound_interfaces_dependencies/rewind.cpp"
#include "../sound_interfaces_dependencies/read.cpp"

#pragma code_seg(".text$10context")
extern "C" __declspec(noinline) int __stdcall SoundLaunchContext(WaveSoundManager** managers,
        const char** names, int count) {
    int result = 0;
    while (count--) result |= (*managers++)->LaunchMusic(*names++);
    return result;
}
#pragma code_seg()
