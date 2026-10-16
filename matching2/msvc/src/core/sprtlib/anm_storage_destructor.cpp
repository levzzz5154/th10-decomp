#include "th10/game/game_thread.hpp"
#include "th10/render/anm_manager_lists.hpp"

// 0x00446220: drain both animation lists, then destroy the layer sprites,
// middle sprite and pooled sprites. Native LTCG preserves the stack receiver
// and the EDI-manager/ESI-VM RemoveVm call convention.
typedef GameThreadSlot AnmOwnedSprite;
struct AnimationManagerStorage {
    unsigned char reserved_000[0x68];
    AnmOwnedSprite pool[4096];
    unsigned char pool_in_use[4096];
    unsigned char reserved_3ad068[0x3ad130-0x3ad068];
    AnmOwnedSprite middle;
    unsigned char reserved_3ad4dc[0x72dad4-0x3ad4dc];
    AnmVmNode* primary_head;
    AnmVmNode* primary_tail;
    AnmVmNode* secondary_head;
    AnmVmNode* secondary_tail;
    AnmOwnedSprite layers[20];
    unsigned char reserved_732454[0xC];
    __declspec(noinline) ~AnimationManagerStorage();
};
typedef char PoolOffset[offsetof(AnimationManagerStorage,pool)==0x68?1:-1];
typedef char MiddleOffset[offsetof(AnimationManagerStorage,middle)==0x3ad130?1:-1];
typedef char LayerOffset[offsetof(AnimationManagerStorage,layers)==0x72dae4?1:-1];
typedef char StorageSize[sizeof(AnimationManagerStorage)==0x732460?1:-1];
#pragma code_seg(".text$01dtor")
AnimationManagerStorage::~AnimationManagerStorage() {
    AnmManager* manager = reinterpret_cast<AnmManager*>(this);
    for (AnmVmNode* node=primary_head; node;) {
        AnmVmNode* next=node->next;
        manager->RemoveVm(node->vm);
        node=next;
    }
    for (AnmVmNode* node=secondary_head; node;) {
        AnmVmNode* next=node->next;
        manager->RemoveVm(node->vm);
        node=next;
    }
}
#pragma code_seg()
