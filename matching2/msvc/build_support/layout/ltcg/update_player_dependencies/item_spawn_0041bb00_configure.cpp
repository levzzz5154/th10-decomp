// Complete semantic model of 0x00404F30, for compiler-visible ABI context.
// This file is not selected as recovered code and has not been byte-compared.
#include "th10/game/entity.hpp"

// The resource is a genuine single pointer passed by value. Keeping its
// aggregate representation preserves the retail stack argument while LTCG
// chooses registers for the entity and script index.
#ifndef TH10_CONFIGURE_00404F30_ARGUMENT_DEFINED
#define TH10_CONFIGURE_00404F30_ARGUMENT_DEFINED
struct ConfigureResource_00404f30 {
    void* value;
};
#endif

extern "C" __declspec(noinline) void __stdcall LoadScript2(
    AnimationResourceFile* resource, AnimationObjectFile* object, int index);

// A three-float constructor expresses the temporary materialized by the
// retail compiler before each vector assignment. The retail body reuses
// a 12-byte stack temporary; the fields themselves are ordinary floats.
struct ConfigureVector_00404f30 : Vector3 {
    ConfigureVector_00404f30(float px, float py, float pz) {
        x = px;
        y = py;
        z = pz;
    }
};

#pragma code_seg(".text$020configure")
__declspec(noinline) void ItemConfiguredEntity_00404f30::Configure(
        int index,ConfigureResource_00404f30 resource) {
    Entity* entity=this;
    Entity_Init(0, entity);
    entity->position = ConfigureVector_00404f30(0.0f, 0.0f, 0.0f);
    entity->base_position = ConfigureVector_00404f30(0.0f, 0.0f, 0.0f);
    entity->render_offset = ConfigureVector_00404f30(0.0f, 0.0f, 0.0f);
    // These two rendering bytes precede the trailing runtime words. Use
    // retail offsets, as the maintained Entity accessors do for this area.
    reinterpret_cast<unsigned char*>(entity)[0x3A1] = 0x10;
    reinterpret_cast<unsigned char*>(entity)[0x3A0] = 0x10;
    entity->ScriptIndex() = static_cast<int16_t>(index);
    LoadScript2(static_cast<AnimationResourceFile*>(resource.value),
        reinterpret_cast<AnimationObjectFile*>(entity),index);
}
#pragma code_seg()
