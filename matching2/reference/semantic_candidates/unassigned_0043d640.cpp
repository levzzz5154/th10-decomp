#include "th10/platform/archive_file.hpp"
#include "sound_wave_types.hpp"

// 0x0043D640: filename in EAX, owner/index on the stack, RET 8. This explicit
// stdcall interface is a behavioral candidate, not the recovered private ABI.
extern "C" int __stdcall Sound_LoadPendingSlot_0043d640(
        const char* file_name, WaveSoundManager* owner, int slot_index) {
    unsigned char* data = reinterpret_cast<unsigned char*>(Archive_LoadFile(file_name, 0, 0));

    // Retail does not range-check the index. Preserve its wrapping address
    // calculation without signed multiplication or bounded-array arithmetic.
    unsigned int address = reinterpret_cast<unsigned int>(owner) + 0x5230 +
        static_cast<unsigned int>(slot_index) * 4;
    unsigned char* volatile* slot = reinterpret_cast<unsigned char* volatile*>(address);
    *slot = data;
    return data ? 0 : -1;
}
