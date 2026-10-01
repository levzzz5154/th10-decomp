#pragma once
#include <stddef.h>
#include "th10/game/resource_list_destroy_abi.hpp"
// Two retail 0x24-byte resource lists. Their pending words are cleared by
// member destruction, including when resource release throws.
#pragma code_seg(".text$05listclear")
struct D3DResourceList_Destroy_00438880 : ResourceList_DestroyABI_00449e50 {
    unsigned int tail[2];
    ~D3DResourceList_Destroy_00438880() {
        pending[0] = 0;
        pending[1] = 0;
        pending[2] = 0;
    }
};
#pragma code_seg()
struct D3DResourceManager_Destroy_00438880 {
    D3DResourceList_Destroy_00438880 primary, secondary;
    __declspec(noinline) ~D3DResourceManager_Destroy_00438880();
};
struct Object_00439040 : D3DResourceManager_Destroy_00438880 {
    __declspec(noinline) void* Destroy(unsigned int flags);
};
typedef char ListExtentCheck[sizeof(D3DResourceList_Destroy_00438880) == 0x24 ? 1 : -1];
typedef char PendingOffsetCheck[offsetof(ResourceList_DestroyABI_00449e50, pending) == 8 ? 1 : -1];
typedef char FirstOffsetCheck[offsetof(ResourceList_DestroyABI_00449e50, first) == 0x18 ? 1 : -1];
typedef char ManagerExtentCheck[sizeof(D3DResourceManager_Destroy_00438880) == 0x48 ? 1 : -1];
