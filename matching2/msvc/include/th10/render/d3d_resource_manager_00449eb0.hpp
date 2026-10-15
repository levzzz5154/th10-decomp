#pragma once
#include "th10/game/resource_list_destroy_abi.hpp"
#include "th10/platform/worker.hpp"

// One of the manager's two 0x24-byte resource lists.
struct FuncCtrlListView : ResourceList_DestroyABI {
    unsigned int tail[2];
};

struct FuncCtrlReleaseView {
    FuncCtrlListView primary, secondary;

    // 0x00449EB0
    __declspec(noinline) void ReleaseResources();
};

// 0x00449E50 as this caller sees it: the owner is evaluated after the list, so
// the list address is formed before the owner is pushed.
void __stdcall ReleaseResourceList(FuncCtrl* owner, ResourceList_DestroyABI* list);

// The loader worker at 0x00492254.
extern PlatformWorker g_destroy_worker;

typedef char D3DResourceManagerListSize[
    sizeof(FuncCtrlListView) == 0x24 ? 1 : -1];
