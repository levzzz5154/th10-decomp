// 0x00428F30: construct the owner of eight pool blocks. The blocks are built
// by their own constructor (0x0042AC20, destructor 0x0042AC60) through the
// compiler's exception-aware vector iterator, and then the constructor body
// clears the whole owner. Native LTCG passes the owner in ESI.
#include <string.h>

struct PoolBlock_00428f30 {
    unsigned char words[0x24];

    PoolBlock_00428f30();
    ~PoolBlock_00428f30();
};

struct PoolBlockOwner_00428f30 {
    unsigned char reserved_000[0xA0];
    PoolBlock_00428f30 blocks[8];           // +0x0A0
    unsigned char reserved_1c0[0x2D4 - 0x1C0];

    __declspec(noinline) PoolBlockOwner_00428f30();
};

#pragma code_seg(".text$01fn")
PoolBlockOwner_00428f30::PoolBlockOwner_00428f30() {
    memset(this, 0, sizeof(*this));
}
#pragma code_seg()
