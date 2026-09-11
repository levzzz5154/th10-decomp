#include <string.h>
#include "th10/game/entity.hpp"

// 0x0041ACF0..0x0041AD57: pool-element constructor of the effect array built by
// 0x0041AED0 (2198 elements of 0x3F0 bytes). The shared Entity head is retired
// exactly like Entity_Constructor (0x00402050); the extra flag word at +0x3D8 is
// effect-only state that lives past the zeroed head.
struct EffectEntity : Entity {
    uint32_t& Flags_3D8() {
        return *(uint32_t*)((uint8_t*)this + 0x3D8);
    }
};

// Clears the "registered with the animation list" bit of one slot flag word.
// The retail constructor reaches every flag through a pointer, which keeps the
// store in the read-modify-write form the image uses.
static void Entity_ClearRegistrationBit(uint32_t* flags) {
    *flags &= ~1u;
}

EffectEntity* __fastcall EffectEntity_Constructor(EffectEntity* entity) {
    Entity_ClearRegistrationBit(&entity->flags_06C);
    Entity_ClearRegistrationBit(&entity->flags_0B0);
    Entity_ClearRegistrationBit(&entity->flags_0FC);
    Entity_ClearRegistrationBit(&entity->flags_128);
    Entity_ClearRegistrationBit(&entity->flags_174);
    Entity_ClearRegistrationBit(&entity->flags_1B0);
    Entity_ClearRegistrationBit(&entity->flags_1FC);
    Entity_ClearRegistrationBit(&entity->flags_228);
    Entity_ClearRegistrationBit(&entity->flags_378);
    memset(entity, 0, sizeof(Entity));
    entity->SpriteIndex() = -1;
    Entity_ClearRegistrationBit(&entity->Flags_3D8());
    return entity;
}
