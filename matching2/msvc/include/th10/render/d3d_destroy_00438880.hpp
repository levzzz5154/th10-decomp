#pragma once
#include <stddef.h>
#include "th10/game/resource_list_destroy_abi.hpp"
// Two retail 0x24-byte resource lists. Their pending words are cleared by
// member destruction, including when resource release throws.
#pragma code_seg(".text$05listclear")
struct FuncCtrlDestroyList : ResourceList_DestroyABI {
    unsigned int tail[2];
    ~FuncCtrlDestroyList() {
        pending[0] = 0;
        pending[1] = 0;
        pending[2] = 0;
    }
};
#pragma code_seg()
struct FuncCtrlDestroyView {
    FuncCtrlDestroyList primary, secondary;
    __declspec(noinline) ~FuncCtrlDestroyView();
};
struct Object_00439040 : FuncCtrlDestroyView {
    __declspec(noinline) void* Destroy(unsigned int flags);
};
typedef char ListExtentCheck[sizeof(FuncCtrlDestroyList) == 0x24 ? 1 : -1];
typedef char PendingOffsetCheck[offsetof(ResourceList_DestroyABI, pending) == 8 ? 1 : -1];
typedef char FirstOffsetCheck[offsetof(ResourceList_DestroyABI, first) == 0x18 ? 1 : -1];
typedef char ManagerExtentCheck[sizeof(FuncCtrlDestroyView) == 0x48 ? 1 : -1];
