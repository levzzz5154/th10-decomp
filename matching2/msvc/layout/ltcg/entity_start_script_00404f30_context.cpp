// Compiler context and ABI anchors only; none of these bytes enter the image.
#include "../../src/render/animation_object_load_script_0043e710.cpp"

// 0x00401DE0 takes the entity in EDX and nothing else, and no retail caller
// relies on EDX surviving it. The recovered body (src/game/
// entity_initialize_00401de0.cpp) would tell this link that EDX is preserved,
// so this stand-in keeps the entry register and hides the register kill set
// behind an external call. It only fixes the call's shape.
extern "C" void __cdecl EntityInitTail_00404f30(Entity* entity);

#pragma code_seg(".text$00h_init")
__declspec(noinline) void __fastcall Entity_Init(void* unused, Entity* entity) {
    (void)unused;
    memset(entity, 0, sizeof(Entity));
    EntityInitTail_00404f30(entity);
}
#pragma code_seg()

#include "../../src/game/entity_start_script_00404f30.cpp"

struct EntityPairOwner_00404f30 {
    unsigned char reserved_00[0x10];
    Entity first;
    Entity second;
};

#pragma code_seg(".text$03context")
extern "C" int __stdcall EntityStartScriptContext_00404f30(EntityPairOwner_00404f30** owners,
                                                AnimationResource_0043e710** resources,
                                                AnimationObject_0043e710** objects,
                                                int count) {
    for (int i = 0; i < count; ++i) {
        EntityPairOwner_00404f30* owner = owners[i];
        Entity_StartScript_00404f30(resources[i], &owner->first, 12);
        Entity_StartScript_00404f30(resources[i], &owner->second, 11);
    }
    for (int slot = 0; slot < count; ++slot)
        LoadScript_0043e710(resources[0], objects[slot], slot);
    return count;
}
#pragma code_seg()
