#include "th10/render/resource_surface_loading.hpp"
#include "th10/platform/archive_file.hpp"
#include "../../build_support/layout/ltcg/resource_surface_loading_log.hpp"
#pragma code_seg(".text$03memory")
extern "C" __declspec(noinline) int __stdcall AnimationLoadMemory_00447ec0(int index,AnimationManagerIndexed_00447f70* manager,const char* name) {
    char path[260];
    int size;
    if (manager->primary[index]) manager->Clear(index);
    sprintf(path,data_0046e1c8,name);
    char* memory = Archive_LoadFile(path,&size,0);
    if (!memory) {
        data_00474f70.AppendLine(data_00470150,name);
        return -1;
    }
    manager->memory[index]=memory;
    manager->memorySize[index]=size;
    return 0;
}
#pragma code_seg()
