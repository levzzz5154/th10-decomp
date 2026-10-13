// Context only, never compared: the complete genuine item/line/animation and
// sound helper graph around UpdateItems, minus the former unselected update
// body itself. With the region's own call sites as the only remaining callers,
// the whole-program link derives each helper's retail register convention
// (the item script index in EAX, the HUD owner in ESI, the run counters in
// EAX, the converting manager in ESI, the collection angle point in EAX).
#include "../../layout/ltcg/item_collection_runtime/allocator.cpp"
#include "../../layout/ltcg/item_collection_runtime/bounded.cpp"
#include "../../layout/ltcg/item_collection_runtime/types/line_sweeps.hpp"
#include "../../layout/ltcg/item_collection_runtime/entity_initialize.cpp"
#include "../../layout/ltcg/item_collection_runtime/dependencies.cpp"
#include "../../layout/ltcg/item_collection_runtime/loader.cpp"
#include "../../layout/ltcg/item_collection_runtime/configure.cpp"
#include "../../layout/ltcg/item_collection_runtime/create.cpp"
#include "../../layout/ltcg/item_collection_runtime/convert.cpp"
#include "../../layout/ltcg/item_collection_runtime/resource_configure.cpp"
#include "../../layout/ltcg/item_collection_runtime/preserve.cpp"
#include "../../layout/ltcg/item_collection_runtime/initialize.cpp"
#include "../../layout/ltcg/item_collection_runtime/primary.cpp"
#include "../../layout/ltcg/item_collection_runtime/collaborators.cpp"
#include "../../layout/ltcg/item_collection_runtime/update_helpers.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$00context")
__declspec(noinline) ItemPolarVelocity_0041bb00* ItemPolarVelocity_0041bb00::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
__declspec(noinline) LinePolarVelocity_0041f800* LinePolarVelocity_0041f800::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
