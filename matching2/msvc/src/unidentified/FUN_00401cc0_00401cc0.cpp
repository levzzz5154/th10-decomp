#include "th10/game/entity.hpp"

// 0x00401CC0..0x00401CC6: replace the entity's primary ARGB color.
#pragma code_seg(".text$01color")
void Entity::SetPrimaryColor(uint32_t color) {
    this->primary_color = color;
}
#pragma code_seg()
