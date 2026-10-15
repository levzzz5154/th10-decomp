#include "th10/source_views/entity_cacea2_0.hpp"
#include "th10/source_views/entity_cacea2_1.hpp"
#include "th10/source_views/entity_cacea2_2.hpp"
void __fastcall EntitySecondaryResource_Release(Entity* entity) {
    void* resource = entity->secondary_resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->secondary_resource = 0;
}
