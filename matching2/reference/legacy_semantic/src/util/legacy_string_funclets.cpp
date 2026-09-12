#include "th10/util/legacy_string_funclets.hpp"

// 0x00438723 - LegacyString growth catch funclet. When the string-resize
// frame unwinds through this funclet, retail re-allocates the requested
// character count plus one terminator byte and stores the fresh buffer back
// into the frame's argument slot before resuming at 0x00438743.
void* LegacyString_GrowthCatchAllocate(unsigned int requested_length,
                                       void* (*allocate)(unsigned int size)) {
    if (allocate == 0) return 0;
    return allocate(requested_length + 1);
}

// 0x004387C2 - LegacyString assignment catch funclet. Retail releases the
// heap buffer when the capacity exceeds the 15-character inline storage,
// resets the block to an empty inline string (capacity 0xF, length 0,
// terminated first byte), and rethrows the in-flight exception via
// __CxxThrowException(0, 0).
void LegacyString_AssignCatchRelease(LegacyStringPayload* text,
                                     void (*free_memory)(void* memory),
                                     void (*rethrow)(void)) {
    if (text != 0) {
        if (text->capacity > 0xF && free_memory != 0) {
            free_memory(text->storage.heap_text);
        }
        text->capacity = 0xF;
        text->length = 0;
        text->storage.inline_text[0] = '\0';
    }
    if (rethrow != 0) rethrow();
}

// --- One-call forwarding leaves ---------------------------------------------
