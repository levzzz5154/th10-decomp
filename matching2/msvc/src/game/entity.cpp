#include <string.h>
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// Recovered semantic C++ definitions.
#include "th10/game/entity.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void* __cdecl operator_new(uint32_t);


// 0x00406160 / 0x004061D0 - Playfield culling tests. The retail ABI keeps the
// tested screen position in ECX and pushes the queried extents, so both are
// members of that position. Each returns 1 while a box of `width` x `height`
// centred on the position stays clear of the playfield rectangle; the
// inclusive variant tests the playfield proper (y from 0) instead of the band
// that starts 64 pixels above it.
//
// The rectangle and the half-size scale are the shared .rdata constants the
// renderer uses, so they are read through their retail addresses.
// Playfield rectangle and frame constants shared with the renderer.
extern float g_playfield_min_x;   // 0x00470B40, -192.0
extern float g_playfield_max_x;   // 0x00470B3C,  192.0
extern float g_playfield_min_y;   // 0x00470B04,    0.0
extern float g_playfield_max_y;   // 0x00470B38,  448.0

struct PlayfieldPoint {
    float x;
    float y;
    int32_t OutsidePlayfield(float width, float height) const;
    int32_t OutsidePlayfieldInclusive(float width, float height) const;
};

int32_t PlayfieldPoint::OutsidePlayfield(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= -64.0f || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

int32_t PlayfieldPoint::OutsidePlayfieldInclusive(float width, float height) const {
    float half_width = width * 0.5f;
    if (half_width + x <= g_playfield_min_x || x - half_width >= g_playfield_max_x)
        return 1;
    float half_height = height * 0.5f;
    if (half_height + y <= g_playfield_min_y || y - half_height >= g_playfield_max_y)
        return 1;
    return 0;
}

// Clears the "registered with the animation list" bit of one slot flag word.
// The retail constructor reaches every flag through a pointer, which keeps the
// store in the read-modify-write form the image uses.
static void Entity_ClearRegistrationBit(uint32_t* flags) {
    *flags &= ~1u;
}

// 0x00402050 - Entity_Constructor: retire every animation slot's registration
// bit, wipe the entity and mark its sprite index unused. Returns the entity.
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

void __fastcall EntitySecondaryResource_Release(Entity* entity) {
    void* resource = entity->secondary_resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->secondary_resource = 0;
}

void __fastcall EntityAnimation_Release(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->resource = 0;
}
