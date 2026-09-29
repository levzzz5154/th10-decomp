// 0x004133F0..0x0041344A: tear the published block down like 0x00413300 and
// free it when bit 0 of the flags is set.  Nothing calls it any more; the
// block arrives in EBX, a convention only a native LTCG link chooses, so the
// region is compiled in the scheduler's cluster.
#include "th10/game/published_block.hpp"

#pragma code_seg(".text$00d_chsdestroy")
__declspec(noinline) PublishedBlock* PublishedBlock::Destroy(unsigned int flags) {
    Shutdown();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma code_seg()
