#include "th10/game/frame_counter.hpp"

// 0x00427C70 - Interval test on a two-word frame counter. Retail lays
// the counter out as {previous at +0x00, current at +0x04} and returns
// 1 only when the two differ and current % interval is zero.
int32_t FrameCounter_AtInterval(const int32_t* counter, int32_t interval) {
    if (counter[1] != counter[0] && counter[1] % interval == 0) {
        return 1;
    }
    return 0;
}
