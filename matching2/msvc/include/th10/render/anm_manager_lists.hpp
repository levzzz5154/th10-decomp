#pragma once

// Views of the animation manager's VM pool and its two update lists, as used
// by the update passes at 0x00448860/0x00448900 and VM removal at 0x00448BB0.

struct AnmManagerVm;

// Intrusive list node embedded in every VM.
struct AnmVmNode {
    AnmManagerVm* vm;
    AnmVmNode* next;
    AnmVmNode* previous;

    __forceinline void Unlink() {
        if (next) next->previous = previous;
        if (previous) previous->next = next;
        next = 0;
        previous = 0;
    }
};

enum { kAnmVmMarkedForRemoval = 0x04000000 };

// One animation VM (the Entity layout, 0x3AC bytes).
struct AnmManagerVm {
    int id;                                         // +0x000
    AnmVmNode manager_node;                         // +0x004
    AnmVmNode child_node;                           // +0x010
    AnmManagerVm* next_in_layer;                    // +0x01C
    int layer;                                      // +0x020
    unsigned char reserved_024[0x358 - 0x024];
    void* heap_data;                                // +0x358
    unsigned int flags;                             // +0x35C
    unsigned char reserved_360[0x398 - 0x360];
    int (__fastcall* on_tick)(AnmManagerVm* vm);    // +0x398
    unsigned char reserved_39c[0x3AC - 0x39C];
};
typedef char AnmManagerVm_size_must_be_0x3ac[sizeof(AnmManagerVm) == 0x3AC ? 1 : -1];

enum { kAnmVmPoolSize = 0x1000, kAnmLayerCount = 19 };

struct AnmManager {
    unsigned char reserved_000[0x64];
    int updated_count;                              // +0x000064
    AnmManagerVm pool[kAnmVmPoolSize];              // +0x000068
    unsigned char pool_in_use[kAnmVmPoolSize];      // +0x3AC068
    unsigned char reserved_3ad068[0x72DAD4 - 0x3AD068];
    AnmVmNode* primary_head;                        // +0x72DAD4
    AnmVmNode* primary_tail;                        // +0x72DAD8
    AnmVmNode* secondary_head;                      // +0x72DADC
    AnmVmNode* secondary_tail;                      // +0x72DAE0
    AnmManagerVm primary_layers[kAnmLayerCount];    // +0x72DAE4, draw-order list heads
    AnmManagerVm secondary_layer;                   // +0x7320A8, draw-order list head

    __declspec(noinline) int UpdatePrimary();
    __declspec(noinline) int UpdateSecondary();
    __declspec(noinline) int RemoveVm(AnmManagerVm* vm);
};
