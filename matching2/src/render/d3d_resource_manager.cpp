#include "th10/render/resource_manager.hpp"

extern "C" void __stdcall EnterCriticalSection(void* critical_section);
extern "C" void __stdcall LeaveCriticalSection(void* critical_section);

extern uint32_t DAT_00492274;
extern uint8_t DAT_0049231c;

void __fastcall D3DResource_Release(void* resource, void* device_owner);
void D3DResourceWorker_Stop(void);

void D3DResourceList_Initialize(D3DResourceList* list) {
    list->field_000 = 0;
    list->flags &= 0xFFFFFFFE;
    list->pending_008 = 0;
    list->pending_00C = 0;
    list->pending_010 = 0;
    list->owner = list;
    list->first = 0;
    list->last = 0;
}

// 0x00449E50 - Release each D3D object tracked by one resource list.
void D3DResourceList_ReleaseResources(
        D3DResourceList* list, void* device_owner) {
    D3DResourceNode* node = list->first;
    while (node != 0) {
        void* resource = node->resource;
        node = node->next;
        if (resource != 0) {
            EnterCriticalSection(&DAT_00492274);
            ++DAT_0049231c;
            D3DResource_Release(resource, device_owner);
            LeaveCriticalSection(&DAT_00492274);
            --DAT_0049231c;
        }
    }
}

// 0x00449AA0 - Initialize both embedded resource lists.
void D3DResourceManager_Initialize(D3DResourceManager* manager) {
    D3DResourceList_Initialize(&manager->primary);
    D3DResourceList_Initialize(&manager->secondary);
}

// 0x00438880 - Stop the worker and release both classes of D3D resources.
void D3DResourceManager_Destroy(D3DResourceManager* manager) {
    D3DResourceWorker_Stop();
    D3DResourceList_ReleaseResources(&manager->primary, manager);
    D3DResourceList_ReleaseResources(&manager->secondary, manager);
    manager->primary.pending_008 = 0;
    manager->primary.pending_00C = 0;
    manager->primary.pending_010 = 0;
    manager->secondary.pending_008 = 0;
    manager->secondary.pending_00C = 0;
    manager->secondary.pending_010 = 0;
}
