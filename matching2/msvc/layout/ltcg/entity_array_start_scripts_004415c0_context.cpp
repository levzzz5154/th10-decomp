// Compiler context and ABI anchors only; none of these bytes enter the image.
// The script starter, its loader and their own context come from the
// 0x00404F30 cluster driver so the starter keeps its ESI/EAX entry here.
#include "entity_start_script_00404f30_context.cpp"
#include "../../src/core/sprtanim/entity_array_start_scripts_004415c0.cpp"

#pragma code_seg(".text$04context")
extern "C" int __stdcall EntityArrayStartScriptsContext_004415c0(
        Entity** arrays, AnimationResource_0043e710** resources, int count) {
    for (int i = 0; i < count; ++i)
        EntityArray_StartScripts_004415c0(arrays[i], i + 3, count, resources[i]);
    return count;
}
#pragma code_seg()
