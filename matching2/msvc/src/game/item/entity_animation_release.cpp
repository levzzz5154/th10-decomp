#include "th10/source_views/entity_cacea2_0.hpp"
#include "th10/source_views/entity_cacea2_1.hpp"
#include "th10/source_views/entity_cacea2_2.hpp"
void __fastcall EntityAnimation_Release(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        crt_free(resource);
    entity->resource = 0;
}
