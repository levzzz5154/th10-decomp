#ifndef TH10_ITEM_COLLISION_CLOSURE_HPP
#define TH10_ITEM_COLLISION_CLOSURE_HPP
#include "th10/game/pause_result_open_004231d0/open_animation.hpp"
#include "th10/game/pause_result_open_004231d0/player/player_collision.hpp"
#include "th10/game/pause_result_open_004231d0/player/movement/movement.hpp"

// The one pointer is the genuine resource argument supplied by value.
struct ConfigureResource_00404f30 {
    AnimationResource_00449870* value;
};
struct ItemConfiguredEntity_00404f30 : Entity {
    __declspec(noinline) void Configure(int index, ConfigureResource_00404f30 resource);
};
// The registered handle is a genuine aggregate result. Native LTCG supplies
// its hidden return home; there is no explicit output input in source.
__declspec(noinline) AnimationScriptId __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, int script, const Vector3* position);

extern "C" float data_00470b4c;
extern "C" float data_00470b48;
#endif
