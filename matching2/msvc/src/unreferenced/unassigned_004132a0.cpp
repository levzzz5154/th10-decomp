// 0x004132A0: clear the thirty-five-word block, latch bit 1 and publish it as the
// current global block. The block arrives in EDX, which only a native LTCG link
// chooses, so this region is compiled as a cluster.

#include <string.h>

struct Block_004132a0 {
    unsigned int flags;                    // +0x00
    unsigned int words[0x23 - 1];          // +0x04
};

extern "C" Block_004132a0* g_fps;

__declspec(noinline) Block_004132a0* InitBlock_004132a0(Block_004132a0* block);
#pragma code_seg(".text$01accessor")
Block_004132a0* InitBlock_004132a0(Block_004132a0* block) {
    memset(block, 0, 0x8C);
    block->flags |= 2u;
    g_fps = block;
    return block;
}
#pragma code_seg()
