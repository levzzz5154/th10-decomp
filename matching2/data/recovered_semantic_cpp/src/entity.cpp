#include "th10/game/entity.hpp"

extern "C" void __cdecl entry_free_00452422(void*);
extern "C" void* __cdecl operator_new(uint32_t);

void __fastcall Entity_Destructor(Entity* entity) {
    void* resource = entity->resource;
    if (resource != 0)
        entry_free_00452422(resource);
    entity->resource = 0;
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
