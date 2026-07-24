#pragma once

#include <cstdint>

struct AnmHandleObject;

// Two-word list node used by the animation manager's object lists
// (retail: object pointer, then next pointer).
struct AnmHandleNode {
    AnmHandleObject* object;
    AnmHandleNode* next;
};

// Animation object fragment (retail offsets in comments).
struct AnmHandleObject {
    uint32_t handle_value;    // +0x00, matched against the stored handle
    AnmHandleNode* children;  // +0x14
    int32_t solo;             // +0x18, non-zero blocks child propagation
    uint32_t flags;           // +0x35C, bit 0x4000000 requests release
};

// The two animation object lists searched for each handle (retail game
// state manager +0x72DAD4 and +0x72DADC).
struct AnmHandleLists {
    AnmHandleNode* world;
    AnmHandleNode* ui;
};

// Bullet-manager shutdown fragment (retail offsets in comments).
struct BulletManagerShutdown {
    uint32_t handles[5];       // +0x40, animation handles to release
    const void* timer_vtable;  // +0xD0, reset to the frame-timer vtable
};

// Frame-timer vtable image installed at the end (retail 0x004703E4; the
// host test provides the symbol).
extern const void* PTR_FUN_004703e4;

// 0x0040B3A0 - Release the bullet manager's five animation handles:
// stop the worker (retail 0x0044C150), and for each non-zero handle
// search the world then UI object lists for a matching object, set its
// release flag bit 0x4000000 (propagating to all children when the
// object is not solo), and clear the handle slot. Afterwards the
// embedded timer vtable at +0xD0 is restored and the worker stop path
// runs again.
void BulletManager_ReleaseAnimHandles(BulletManagerShutdown* state,
                                      const AnmHandleLists* lists,
                                      void (*stop_worker)());
