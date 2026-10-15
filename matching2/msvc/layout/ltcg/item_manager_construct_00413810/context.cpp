// Compiler context only; never selected as recovered game code. The sprite
// constructor is the Entity constructor at 0x00402050, visible here so the
// lone sprite member inlines it. The caller constructs in place so that it
// needs no cleanup state of its own.
#include "th10/game/hud_construct.hpp"

static void HudSprite_ClearRegistration(uint32_t* flags) { *flags &= ~1u; }

#pragma code_seg(".text$00sprite")
HudSprite::HudSprite() {
    HudSprite_ClearRegistration(&flags_06C);
    HudSprite_ClearRegistration(&flags_0B0);
    HudSprite_ClearRegistration(&flags_0FC);
    HudSprite_ClearRegistration(&flags_128);
    HudSprite_ClearRegistration(&flags_174);
    HudSprite_ClearRegistration(&flags_1B0);
    HudSprite_ClearRegistration(&flags_1FC);
    HudSprite_ClearRegistration(&flags_228);
    HudSprite_ClearRegistration(&flags_378);
    memset(this, 0, sizeof(Entity));
    SpriteIndex() = -1;
}
#pragma code_seg()

#include "../../../src/game/front/hud_construct.cpp"

inline void* __cdecl operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$05context")
Hud* __stdcall HudConstructCompilerContext(void* block) {
    return new (block) Hud;
}
#pragma code_seg()
