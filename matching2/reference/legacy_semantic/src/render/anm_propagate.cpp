#include "th10/render/anm_propagate.hpp"

namespace {

// Shared body: store the sprite word and propagate to children unless
// the object is solo.
void StoreSpriteWord(AnmObject* object, uint16_t value) {
    object->sprite_word = value;
    if (object->solo != 0) {
        return;
    }
    for (AnmChildNode* node = object->children; node != 0; node = node->next) {
        node->object->sprite_word = value;
    }
}

}  // namespace

// 0x00409E50 - Mark a handle's object (sprite word 1) and its children.
// Retail resolves through FUN_004491C0 with the global game state
// manager; a failed resolve is a no-op.
void Anm_MarkHandleAndChildren(const uint32_t* handle_slot,
                               AnmResolveFn resolve) {
    AnmObject* object = resolve != 0 ? resolve(*handle_slot) : 0;
    if (object != 0) {
        StoreSpriteWord(object, 1);
    }
}

// 0x0042C770 - Store a sprite word through a handle-table slot. Same
// resolve-and-propagate shape as 0x00409E50 with a caller-chosen value
// and the handle taken from the owner's table at +0x2C4.
void Anm_SetSpriteWordForSlot(const uint32_t* handle_table, int32_t index,
                              uint16_t value, AnmResolveFn resolve) {
    AnmObject* object = resolve != 0 ? resolve(handle_table[index]) : 0;
    if (object != 0) {
        StoreSpriteWord(object, value);
    }
}
