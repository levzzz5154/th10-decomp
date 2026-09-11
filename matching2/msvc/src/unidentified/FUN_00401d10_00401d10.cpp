#include "th10/game/entity.hpp"

// 0x00401D10..0x00401D16: replace the entity's sprite metadata pointer.
// The store is written at the retail byte offset; referencing the header's
// inline accessor instead leaves an empty .text COMDAT in the LTCG image.
#pragma code_seg(".text$01setmeta")
void Entity::SetSpriteMetadata(void* metadata) {
    *(void**)((uint8_t*)this + 0x394) = metadata;
}
#pragma code_seg()
