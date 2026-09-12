#include "th10/game/bullet_anim_release.hpp"

namespace {

// Search one object list for a node whose object carries the handle.
AnmHandleNode* FindHandle(AnmHandleNode* head, uint32_t handle) {
    for (AnmHandleNode* node = head; node != 0; node = node->next) {
        if (node->object->handle_value == handle) {
            return node;
        }
    }
    return 0;
}

}  // namespace

// 0x0040B3A0 - Release the bullet manager's five animation handles.
// Retail keeps the manager in EAX, reads the two object lists from the
// global game state manager (+0x72DAD4 world, +0x72DADC UI), and
// brackets the sweep with the worker stop path at 0x0044C150. Every
// handle slot is cleared whether or not a matching object was found.
void BulletManager_ReleaseAnimHandles(BulletManagerShutdown* state,
                                      const AnmHandleLists* lists,
                                      void (*stop_worker)()) {
    if (stop_worker != 0) {
        stop_worker();
    }
    for (int slot = 0; slot < 5; ++slot) {
        const uint32_t handle = state->handles[slot];
        if (handle != 0) {
            AnmHandleNode* node = FindHandle(lists->world, handle);
            if (node == 0) {
                node = FindHandle(lists->ui, handle);
            }
            if (node != 0 && node->object != 0) {
                AnmHandleObject* object = node->object;
                object->flags |= 0x4000000u;
                if (object->solo == 0) {
                    for (AnmHandleNode* child = object->children; child != 0;
                         child = child->next) {
                        child->object->flags |= 0x4000000u;
                    }
                }
            }
        }
        state->handles[slot] = 0;
    }
    state->timer_vtable = &PTR_FUN_004703e4;
    if (stop_worker != 0) {
        stop_worker();
    }
}
