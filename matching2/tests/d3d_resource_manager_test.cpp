#include "th10/render/resource_manager.hpp"

#include <cassert>

uint32_t DAT_00492274;
uint8_t DAT_0049231c;

static int workerStops;
static int releasedResources;
static void* lastDeviceOwner;

extern "C" void __stdcall EnterCriticalSection(void*) {}
extern "C" void __stdcall LeaveCriticalSection(void*) {}

void __fastcall D3DResource_Release(void*, void* deviceOwner) {
    ++releasedResources;
    lastDeviceOwner = deviceOwner;
}

void D3DResourceWorker_Stop(void) {
    ++workerStops;
}

static void TestClearPending() {
    D3DResourceList list = {};
    list.pending_008 = 1;
    list.pending_00C = 2;
    list.pending_010 = 3;

    D3DResourceList_ClearPending(&list);

    assert(list.pending_008 == 0);
    assert(list.pending_00C == 0);
    assert(list.pending_010 == 0);
}

static void TestManagerLifecycle() {
    D3DResourceManager manager = {};
    manager.primary.flags = 0xFFFFFFFFu;
    manager.secondary.flags = 0xFFFFFFFFu;
    D3DResourceManager_Initialize(&manager);
    assert(manager.primary.owner == &manager.primary);
    assert(manager.secondary.owner == &manager.secondary);
    assert((manager.primary.flags & 1) == 0);
    assert((manager.secondary.flags & 1) == 0);

    int firstResource;
    int secondResource;
    D3DResourceNode second = {&secondResource, 0};
    D3DResourceNode first = {&firstResource, &second};
    manager.primary.first = &first;
    manager.primary.pending_008 = 4;
    manager.secondary.pending_00C = 5;

    D3DResourceManager_Destroy(&manager);

    assert(workerStops == 1);
    assert(releasedResources == 2);
    assert(lastDeviceOwner == &manager);
    assert(DAT_0049231c == 0);
    assert(manager.primary.pending_008 == 0);
    assert(manager.secondary.pending_00C == 0);
}

int main() {
    TestClearPending();
    TestManagerLifecycle();
    return 0;
}
