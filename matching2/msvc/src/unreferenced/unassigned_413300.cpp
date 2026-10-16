// 0x00413300..0x00413346: remove the scheduler task of the block that
// 0x004132A0 publishes and clear the global block pointer.  Nothing calls it
// any more; the block arrives in EAX, a convention only a native LTCG link
// chooses, so the region is compiled in the scheduler's cluster.
#include "th10/game/published_block.hpp"

#pragma code_seg(".text$00d_chrelease")
__declspec(noinline) void PublishedBlock::Release() {
    Shutdown();
}
#pragma code_seg()
