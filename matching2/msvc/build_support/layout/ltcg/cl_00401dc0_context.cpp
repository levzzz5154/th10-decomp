// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_401dc0.cpp"

#pragma code_seg(".text$00h_init")
#include "../../contexts/legacy/game/entity_initialize.cpp"
#pragma code_seg()

#include "../../../src/core/sprtanim/animation_object_configure_from_resource.cpp"

#pragma code_seg(".text$03context")
int __stdcall EntityInitFromResourceContext_00401dc0(Entity** entities,
                                                     Resource2** resources,
                                                     int count) {
    int result = 0;
    for (int i = 0; i < count; ++i)
        result += Entity_InitFromResource(entities[i], resources[i], i);
    return result;
}
#pragma code_seg()
