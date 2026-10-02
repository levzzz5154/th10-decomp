#include <string.h>
#include "th10/game/entity.hpp"
#pragma code_seg(".text$02constructor")
static void Entity_ClearRegistrationBit(uint32_t* flags) {
    *flags &= ~1u;
}

// 0x00402050 - Entity_Constructor: retire every animation slot's registration
// bit, wipe the entity and mark its sprite index unused. Returns the entity.
__declspec(noinline) Entity* __fastcall Entity_Constructor(Entity* entity) {
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
    return entity;
}


#pragma code_seg()
