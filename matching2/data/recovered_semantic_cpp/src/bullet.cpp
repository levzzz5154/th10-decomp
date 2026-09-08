#include "th10/game/entity.hpp"

extern "C" void* __cdecl operator_new(uint32_t size);

BulletSpawnParameters* __fastcall BulletSpawnParameters_Initialize(
        void* unused, BulletSpawnParameters* parameters) {
    (void)unused;
    for (int index = 0; index < 0x7E; ++index)
        parameters->fields[index] = 0;
    parameters->fields[0x0B] = 0x41000000;
    return parameters;
}

int __fastcall Entity_AttachResourceSnapshot(
        Entity* entity, const EntityResourceSnapshot* snapshot) {
    EntityResourceSnapshot* copy =
        (EntityResourceSnapshot*)operator_new(sizeof(EntityResourceSnapshot));
    *(EntityResourceSnapshot**)((uint8_t*)entity + 0x358) = copy;
    *copy = *snapshot;
    entity->Position() = *(const Vector3*)copy;
    return 0;
}

