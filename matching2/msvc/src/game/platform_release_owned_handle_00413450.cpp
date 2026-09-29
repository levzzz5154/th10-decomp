// 0x00413450..0x004134A3: tear down and free the published block, if any.
// Its caller at 0x00420270 passes the block in EBX, a convention only a native
// LTCG link chooses, so the region is compiled in the scheduler's cluster.
#include "th10/game/published_block.hpp"

#pragma code_seg(".text$00d_chtdelete")
__declspec(noinline) void DeletePublishedBlock(PublishedBlock* block) {
    if (block) {
        block->Shutdown();
        operator delete(block);
    }
}
#pragma code_seg()
