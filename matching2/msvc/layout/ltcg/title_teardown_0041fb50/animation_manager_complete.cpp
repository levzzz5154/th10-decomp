#include "title_teardown_dependencies.hpp"
#include "th10/render/anm_manager_lists.hpp"

// The complete native owner at 0x00446220. The three actual Entity
// subobjects produce their own full compiler unwind graph.
struct AnimationManagerStorage_00446220 {
    unsigned char reserved_000[0x68];
    TitleAnimation_00401FF0 pool[4096];
    unsigned char pool_in_use[4096];
    unsigned char reserved_3ad068[0x3ad130-0x3ad068];
    TitleAnimation_00401FF0 middle;
    unsigned char reserved_3ad4dc[0x72dad4-0x3ad4dc];
    AnmVmNode* primary_head;
    AnmVmNode* primary_tail;
    AnmVmNode* secondary_head;
    AnmVmNode* secondary_tail;
    TitleAnimation_00401FF0 layers[20];
    unsigned char reserved_732454[0xC];
    __declspec(noinline) ~AnimationManagerStorage_00446220();
};
typedef char PoolOffset[offsetof(AnimationManagerStorage_00446220,pool)==0x68?1:-1];
typedef char MiddleOffset[offsetof(AnimationManagerStorage_00446220,middle)==0x3ad130?1:-1];
typedef char LayerOffset[offsetof(AnimationManagerStorage_00446220,layers)==0x72dae4?1:-1];
typedef char StorageSize[sizeof(AnimationManagerStorage_00446220)==0x732460?1:-1];
#pragma code_seg(".text$06zmanager")
AnimationManagerStorage_00446220::~AnimationManagerStorage_00446220() {
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
