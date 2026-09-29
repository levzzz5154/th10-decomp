#include <string.h>
#include "asm_encoding.hpp"
#include "th10/platform/windows_types.hpp"
#include "asm_symbols.hpp"
#include "th10/platform/sound_buffer.hpp"


extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);

int Platform_GetOsVersionCode() {
    OSVERSIONINFOA version_info;
    memset(&version_info, 0, sizeof(version_info));
    version_info.dwOSVersionInfoSize = sizeof(version_info);
    GetVersionExA(&version_info);

    switch (version_info.dwPlatformId) {
    case 0:
        return 31;
    case 1:
        if (version_info.dwMajorVersion == 4)
            return version_info.dwMinorVersion != 0 ? 98 : 95;
        return version_info.dwMajorVersion * 100 + version_info.dwMinorVersion;
    case 2:
        if (version_info.dwMajorVersion == 5)
            return 2000;
        return (version_info.dwMajorVersion * 100 + version_info.dwMinorVersion) * 10;
    default:
        return -1;
    }
}



// 0x0044D5B0..0x0044D5CC: stop the first DirectSound buffer and clear the
// wrapper's playing flag. DirectSound methods use their stdcall COM ABI.
int __fastcall Platform_InvokeInterface(SoundBuffer* sound_buffer) {
    DirectSoundBuffer** const buffers = sound_buffer->buffers;
    if (buffers == 0)
        return (int)0x800401F0u;

    sound_buffer->is_playing = 0;
    DirectSoundBuffer* const buffer = buffers[0];
    return buffer->vtable->stop(buffer);
}
