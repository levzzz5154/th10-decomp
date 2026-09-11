#include "th10/game/entity.hpp"

// 0x00401CB0..0x00401CB6: store the ARGB alpha byte of the entity's primary
// colour. primary_color is a little-endian uint32 at +0x2FC, so its alpha
// channel is the byte at +0x2FF.
#pragma code_seg(".text$01alpha")
void Entity::SetPrimaryColorAlpha(char alpha) {
    *(uint8_t*)((uint8_t*)this + 0x2FF) = alpha;
}
#pragma code_seg()
