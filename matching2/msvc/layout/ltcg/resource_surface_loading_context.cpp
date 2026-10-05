#include "../../src/unidentified/FUN_00447ec0_00447ec0.cpp"
#include "resource_surface_loading_clear.cpp"
#include "resource_surface_loading_archive.cpp"
#include "resource_surface_loading_log.cpp"
#pragma code_seg(".text$11context")
extern "C" int __stdcall ResourceSurfaceLoadingContext(AnimationManagerIndexed_00447f70** managers,int count,const char* name) {
    for(int index=0;index<count;++index) {
        AnimationLoadMemory_00447ec0(index,managers[index],name);
        AnimationLoadSurface_00447c80(managers[index],name,count-index);
    }
    return count;
}
#pragma code_seg()
