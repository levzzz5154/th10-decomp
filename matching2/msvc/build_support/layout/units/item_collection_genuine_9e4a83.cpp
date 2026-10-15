// Complete allocator/animation graph reached by the two actual line callers.
// These ordinary polar bodies retain their public member ABI. Their FCOS/FSIN
// output is unselected; production has separate exact FSINCOS recoveries.
#include "../ltcg/item_collection_runtime/allocator.cpp"
#include "../ltcg/item_collection_runtime/bounded.cpp"
#include "../ltcg/item_collection_runtime/types/line_sweeps.hpp"
#include "../ltcg/item_collection_runtime/entity_initialize.cpp"
#include "../ltcg/item_collection_runtime/dependencies.cpp"
#include "../ltcg/item_collection_runtime/loader.cpp"
#include "../ltcg/item_collection_runtime/configure.cpp"
#include "../ltcg/item_collection_runtime/create.cpp"
#include "../../../src/game/item/item_spawn_manager_convert_items.cpp"
#include "../ltcg/item_collection_runtime/resource_configure.cpp"
#include "../ltcg/item_collection_runtime/preserve.cpp"
#include "../ltcg/item_collection_runtime/initialize.cpp"
#include "../ltcg/item_collection_runtime/primary.cpp"
#include "../ltcg/item_collection_runtime/collaborators.cpp"
#include "../../../src/game/game/update_helpers.cpp"
#include "../ltcg/item_collection_runtime/update.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$f0041beb0F")
__declspec(noinline) ItemPolarVelocity_0041bb00* ItemPolarVelocity_0041bb00::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
#pragma code_seg(".text$f0041f800F")
__declspec(noinline) LinePolarVelocity_0041f800* LinePolarVelocity_0041f800::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()

