// 0x0042AC20..0x0042AC56: PoolBlock_0042ac20::Reset
// Reinitialise a 36-byte pool block in place. Every word is cleared through a
// walking pointer, the two leading head/tail pairs are re-linked to their
// just-cleared heads so the block reads as two empty lists, and the trailing
// three-word record points back at the block itself. The block is returned so
// the caller can chain the reset.
struct PoolBlockTail {
    unsigned owner;                                  // +0x00 (block +0x18)
    unsigned field_04;                               // +0x04 (block +0x1C)
    unsigned field_08;                               // +0x08 (block +0x20)
};

struct PoolBlock_0042ac20 {
    unsigned link_00;                                // +0x00
    unsigned link_04;                                // +0x04
    unsigned link_08;                                // +0x08
    unsigned link_0C;                                // +0x0C
    unsigned field_10;                               // +0x10
    unsigned field_14;                               // +0x14
    PoolBlockTail tail;                              // +0x18

    PoolBlock_0042ac20* __fastcall Reset();
};

PoolBlock_0042ac20* __fastcall PoolBlock_0042ac20::Reset() {
    unsigned* word = (unsigned*)this;
    int remaining = 9;
    do {
        *word++ = 0;
    } while (--remaining);
    link_04 = link_00;
    link_0C = link_08;
    PoolBlockTail* self_tail = (PoolBlockTail*)((unsigned*)this + 6);
    self_tail->owner = (unsigned)this;
    self_tail->field_04 = 0;
    self_tail->field_08 = 0;
    return this;
}
