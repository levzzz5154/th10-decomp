// Compiler context only; never selected as recovered game code. The sprite
// constructor is the Entity constructor at 0x00402050, visible here so the
// lone sprite member inlines it. The caller constructs in place so that it
// needs no cleanup state of its own.
#include "th10/game/item_manager_construct_00413810.hpp"

static void ItemManagerSprite_ClearRegistration(uint32_t* flags) { *flags &= ~1u; }

#pragma code_seg(".text$00sprite")
ItemManagerSprite_00413810::ItemManagerSprite_00413810() {
    ItemManagerSprite_ClearRegistration(&flags_06C);
    ItemManagerSprite_ClearRegistration(&flags_0B0);
    ItemManagerSprite_ClearRegistration(&flags_0FC);
    ItemManagerSprite_ClearRegistration(&flags_128);
    ItemManagerSprite_ClearRegistration(&flags_174);
    ItemManagerSprite_ClearRegistration(&flags_1B0);
    ItemManagerSprite_ClearRegistration(&flags_1FC);
    ItemManagerSprite_ClearRegistration(&flags_228);
    ItemManagerSprite_ClearRegistration(&flags_378);
    memset(this, 0, sizeof(Entity));
    SpriteIndex() = -1;
}
#pragma code_seg()

#include "../../../src/game/item_manager_construct_00413810.cpp"

inline void* __cdecl operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$05context")
ItemManager_00413810* __stdcall ItemManagerConstructCompilerContext(void* block) {
    return new (block) ItemManager_00413810;
}
#pragma code_seg()
