// Behavioral source model for 0x004415C0.
//
// This file is retained as a semantic reference only. It is not the
// manifest-owned retail body, must not be treated as a build/cluster input, and
// does not bridge the function's private-register ABI or the helper's ABI.
#include <string.h>

namespace EntityBatchCopy_004415C0 {

enum {
    kStateRecordStride = 0x3AC,
    kStateShortSourceOffset = 0x384,
    kStateShortDestinationOffset = 0x388
};

// A semantic stand-in for the per-item work at retail address 0x00404F30.
// The ordinary C++ parameters describe values forwarded by the loop; they do
// not describe 0x00404F30's actual private register/stack calling convention.
extern "C" void __cdecl InitializeEntityAt00404F30_ModelOnly(
    unsigned char* itemByte,
    unsigned char* stateRecord,
    unsigned int fullEntryCount,
    const void* forwardedStackArgument);

// Readable behavior model only. Retail enters with count in EAX, itemByteBase
// in ECX, stateRecordBase in EDX, and forwardedStackArgument at [ESP+4].
// This normal C++ signature is intentionally not an ABI bridge for that entry.
void ApplyBatchSemanticModelOnly(
    unsigned int count,
    unsigned char* itemByteBase,
    unsigned char* stateRecordBase,
    const void* forwardedStackArgument) {
    for (unsigned int index = 0; index < count; ++index) {
        unsigned char* stateRecord =
            stateRecordBase + index * kStateRecordStride;

        InitializeEntityAt00404F30_ModelOnly(
            itemByteBase + index,
            stateRecord,
            count,
            forwardedStackArgument);

        memcpy(stateRecord + kStateShortDestinationOffset,
               stateRecord + kStateShortSourceOffset,
               sizeof(unsigned short));
    }
}

} // namespace EntityBatchCopy_004415C0
