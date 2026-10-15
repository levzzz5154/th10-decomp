#include "th10/source_views/bullet_99a1d5_0.hpp"
#include "th10/source_views/bullet_99a1d5_1.hpp"
#include "th10/source_views/bullet_99a1d5_2.hpp"
int __fastcall Entity_AttachResourceSnapshot(
        Entity* entity, const EntityResourceSnapshot* snapshot) {
    EntityResourceSnapshot* copy =
        (EntityResourceSnapshot*)operator_new(sizeof(EntityResourceSnapshot));
    *(EntityResourceSnapshot**)((uint8_t*)entity + 0x358) = copy;
    *copy = *snapshot;
    entity->Position() = *(const Vector3*)copy;
    return 0;
}
