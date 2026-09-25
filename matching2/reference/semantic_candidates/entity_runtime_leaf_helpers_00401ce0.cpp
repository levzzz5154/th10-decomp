#include "th10/game/entity.hpp"

// Retail entry 0x00401CE0..0x00401CFF takes Entity in EAX and two float
// values on the stack. It updates the sprite dimensions and sets flag bit 3.
extern "C" void __cdecl SetEntitySpriteSize_00401ce0(
    Entity* entity, float width, float height) {
    entity->sprite_width = width;
    entity->sprite_height = height;
    entity->flags_35C |= 8;
}

struct StridedRecord_00401d00 {
    unsigned char bytes[0x44];
};

struct StridedRecordContainer_00401d00 {
    unsigned char fields_before_records[0x118];
    StridedRecord_00401d00* records;
};

// Retail entry 0x00401D00..0x00401D0B takes the index in EAX and the
// container in ECX. Keep the 0x44-byte stride explicit until the record's
// fields are recovered.
extern "C" StridedRecord_00401d00* __cdecl GetStridedRecordAtIndex_00401d00(
    StridedRecordContainer_00401d00* container, int index) {
    return &container->records[index];
}
