#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// Recovered semantic C++ definitions.
#include "th10/game/frame_counter.hpp"
// 0x00427C70: the later historical semantic match, in addition to the original 33.
int FrameCounterPair::AtInterval(int interval) {
    if (current != previous && current % interval == 0) {
        return 1;
    }
    return 0;
}
