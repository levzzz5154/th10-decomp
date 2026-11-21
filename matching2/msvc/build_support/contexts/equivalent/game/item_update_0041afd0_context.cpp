// Private helper definitions for the separately compiled item update.
// Native LTCG derives the register conventions from real call sites: script
// index in EAX, HUD owner in ESI, run counters in EAX, converting manager in
// ESI and the collection angle point in EAX.
// SetPolar must retain its public thiscall receiver in ECX. Giving the
// initializer a public entry also prevents the compiler from keeping the
// StartScript entity in a scratch register across initialization; the bound
// retail StartScript receives that entity in ESI. These exports exist only
// in the verifying context link, never in the installed game executable.
#define TH10_ITEM_POLAR_CONTEXT_EXPORT __declspec(dllexport)
#define TH10_ITEM_CONTEXT_PUBLIC_INIT
#include "../../../layout/ltcg/item_collection_runtime/allocator.cpp"
#include "../../../layout/ltcg/item_collection_runtime/bounded.cpp"
#include "../../../layout/ltcg/item_collection_runtime/types/line_sweeps.hpp"
#include "../../../layout/ltcg/item_collection_runtime/entity_initialize.cpp"
#include "../../../layout/ltcg/item_collection_runtime/dependencies.cpp"
#include "../../../layout/ltcg/item_collection_runtime/loader.cpp"
#include "../../../layout/ltcg/item_collection_runtime/configure.cpp"
#include "../../../layout/ltcg/item_collection_runtime/create.cpp"
#include "../../../../src/game/item/item_spawn_manager_convert_items.cpp"
#include "../../../layout/ltcg/item_collection_runtime/resource_configure.cpp"
#include "../../../layout/ltcg/item_collection_runtime/preserve.cpp"
#include "../../../layout/ltcg/item_collection_runtime/initialize.cpp"
#include "../../../layout/ltcg/item_collection_runtime/primary.cpp"
#include "../../../layout/ltcg/item_collection_runtime/collaborators.cpp"
#include "../../../../src/game/game/update_helpers.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$00context")
__declspec(dllexport) __declspec(noinline) ItemPolarVelocity2* ItemPolarVelocity2::SetPolar(float angle,float speed) {
    ItemPolarVelocity2* volatile self=this;
    ItemPolarVelocity2* out=self;
    out->x=static_cast<float>(cos(angle)*speed);
    out->y=static_cast<float>(sin(angle)*speed);
    return out;
}
__declspec(noinline) LinePolarVelocity2* LinePolarVelocity2::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
