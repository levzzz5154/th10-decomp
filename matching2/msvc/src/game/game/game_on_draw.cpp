// 0x004187D0: the stage's draw task.
// Clears a block of the global state unless this object's flag word says the
// block is still in use; always reports success. The owner block is huge, so
// only the touched offsets are described, in the order retail stores them.
extern "C" unsigned char g_sprt_ctrl;             // 0x00491C10  game state object

struct StateBlock {
    unsigned char unknown_00[0x4C];
    int field_4C;                                    // +0x4C
    int field_50;                                    // +0x50
    int field_54;                                    // +0x54
    int field_58;                                    // +0x58
};

int __fastcall Game_OnDraw(unsigned char* self) {
    if ((self[0x58] & 4) == 0) {
        StateBlock* block = *(StateBlock**)&g_sprt_ctrl;
        block->field_50 = 0;
        block->field_54 = 0;
        block->field_4C = 0;
        block->field_58 = 0;
    }
    return 1;
}
