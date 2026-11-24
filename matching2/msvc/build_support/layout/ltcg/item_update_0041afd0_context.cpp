// ABI context helpers for the separately compiled item update (0x0041AFD0).
// Native LTCG derives the retail register conventions from the real item,
// animation and sound call sites.
#include "item_collection_runtime/allocator.cpp"
#include "item_collection_runtime/types/line_sweeps.hpp"
#include "item_collection_runtime/entity_initialize.cpp"
#include "item_collection_runtime/dependencies.cpp"
#include "item_collection_runtime/loader.cpp"
#include "item_collection_runtime/configure.cpp"
#include "item_collection_runtime/create.cpp"
#include "../../../src/game/item/item_spawn_manager_convert_items.cpp"
#include "item_collection_runtime/resource_configure.cpp"
#include "item_collection_runtime/preserve.cpp"
#include "item_collection_runtime/initialize.cpp"
#include "item_collection_runtime/primary.cpp"
#include "item_collection_runtime/collaborators.cpp"
#include "../../../src/game/game/update_helpers.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$f0041beb0F")
__declspec(noinline) ItemPolarVelocity2* ItemPolarVelocity2::SetPolar(float angle,float speed) {
    ItemPolarVelocity2* volatile self=this;
    ItemPolarVelocity2* out=self;
    out->x=static_cast<float>(cos(angle)*speed);
    out->y=static_cast<float>(sin(angle)*speed);
    return out;
}
#pragma code_seg()
