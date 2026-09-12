#pragma once

#include "th10/game/entity.hpp"

struct D3DResourceNode {
    void* resource;
    D3DResourceNode* next;
};

struct D3DResourceList {
    uint32_t reserved_header;
    uint32_t flags;
    uint32_t pending_008;
    uint32_t pending_00C;
    uint32_t pending_010;
    D3DResourceList* owner;
    D3DResourceNode* first;
    D3DResourceNode* last;
    uint32_t reserved_tail;
};
// sizeof(D3DResourceList) == 0x24

struct D3DResourceManager {
    D3DResourceList primary;
    D3DResourceList secondary;
};
// sizeof(D3DResourceManager) == 0x48

void D3DResourceList_Initialize(D3DResourceList* list);
void D3DResourceList_ClearPending(D3DResourceList* list);
void D3DResourceList_ReleaseResources(
    D3DResourceList* list, void* device_owner);
void D3DResourceManager_Initialize(D3DResourceManager* manager);
void D3DResourceManager_Destroy(D3DResourceManager* manager);
