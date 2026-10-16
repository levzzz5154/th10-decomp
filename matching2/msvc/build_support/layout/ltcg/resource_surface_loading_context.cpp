#include "../../../src/unreferenced/FUN.cpp_447ec0.cpp"
#include "resource_surface_loading_clear.cpp"
#include "resource_surface_loading_archive.cpp"
#include "resource_surface_loading_log.cpp"
#pragma code_seg(".text$11context")
extern "C" int __stdcall ResourceSurfaceLoadingContext(AnimationManagerIndexed** managers,int count,const char* name) {
    for(int index=0;index<count;++index) {
        AnimationLoadMemory2(index,managers[index],name);
        AnimationLoadSurface2(managers[index],name,count-index);
    }
    return count;
}
#pragma code_seg()
