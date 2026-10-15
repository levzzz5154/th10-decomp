#include "th10/source_views/entity_cacea2_0.hpp"
#include "th10/source_views/entity_cacea2_1.hpp"
#include "th10/source_views/entity_cacea2_2.hpp"
Entity* __fastcall Entity_Constructor(Entity* entity) {
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
