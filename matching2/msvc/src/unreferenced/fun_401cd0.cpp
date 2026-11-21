#include "th10/game/entity.hpp"

// 0x00401CD0..0x00401CD6: read the entity's sprite metadata pointer.
// The load is written at the retail byte offset; referencing the header's
// inline accessor instead leaves an empty .text COMDAT in the LTCG image.
#pragma code_seg(".text$01getmeta")
void* Entity::GetSpriteMetadata() {
    return *(void**)((uint8_t*)this + 0x394);
}
#pragma code_seg()
