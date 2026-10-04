// Synthetic compiler context only.
#include "../../src/render/animation_resource_initialize_object_00449870.cpp"
#include "animation_resource_initialize_object_00449870_loader.cpp"
#pragma code_seg(".text$05context")
extern "C" int __stdcall ResourceInitializeObjectContext(AnimationResource_00449870* resource,
        Entity** objects, int count) {
    for (int i=0; i<count; ++i) {
        resource->InitializeObject(objects[i], i);
        InitializePreservingLoader_0043e7e0((AnimationResource_0043e7e0*)resource,
            (AnimationObject_0043e7e0*)objects[i], i);
    }
    return 0;
}
#pragma code_seg()
