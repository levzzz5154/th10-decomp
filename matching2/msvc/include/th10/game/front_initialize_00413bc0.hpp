// Checked front initialization and animation views for the native call graph.
#pragma once
#include <stddef.h>
#include "th10/math/timer.hpp"
#include "th10/game/entity.hpp"
#include "th10/render/animation_object_0043e5a0.hpp"
#include "th10/render/animation_handle.hpp"
#include "th10/platform/sound_queue.hpp"

struct FrontAnimationLookup;
// An animation's id. The user-declared constructors make functions return it
// through a caller-provided slot.
struct FrontAnimationId {
    unsigned int value;

    FrontAnimationId() {}
    FrontAnimationId(unsigned int id) : value(id) {}
    FrontAnimationId &operator=(FrontAnimationId other) {
        value = other.value;
        return *this;
    }
    FrontAnimationId &operator++() {
        ++value;
        return *this;
    }
    bool operator==(FrontAnimationId other) const { return value == other.value; }
};
extern "C" FrontAnimationLookup *g_sprt_ctrl;

// An animation a game object owns, named by its id.
struct FrontAnimationHandle {
    FrontAnimationId id;
};

struct FrontGameFlagWord {
    union {
        unsigned int value;
        unsigned char bytes[4];
    };
    FrontGameFlagWord &operator|=(unsigned int bits) {
        value |= bits;
        return *this;
    }
};
struct FrontAnimationPool {
    unsigned char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity *Allocate();
};
struct FrontAnimationResource {
    __declspec(noinline) void InitializeObject(Entity *object, int index);
};
struct FrontAnimationListNode {
    Entity *object;
    FrontAnimationListNode *next;
    FrontAnimationListNode *previous;
};
struct FrontAnimationLists {
    unsigned char reserved[0x72DAD4];
    FrontAnimationListNode *primary_head;
    FrontAnimationListNode *primary_tail;
    unsigned char reserved_72dadc[0x732454 - 0x72DADC];
    FrontAnimationId next_id;
    __declspec(noinline) FrontAnimationId RegisterPrimaryBack(Entity *object);
};
inline void RegisterFrontInline(FrontAnimationLists *lists, Entity *object) {
    FrontAnimationListNode *node =
        reinterpret_cast<FrontAnimationListNode *>(&object->manager_node_animation);
    node->object = object;
    node->next = 0;
    node->previous = 0;
    if (!lists->primary_head)
        lists->primary_head = node;
    else {
        FrontAnimationListNode *tail = lists->primary_tail;
        FrontAnimationListNode *next = tail->next;
        if (next) {
            node->next = next;
            tail->next->previous = node;
        }
        tail->next = node;
        node->previous = tail;
    }
    lists->primary_tail = node;
    ++lists->next_id;
    if (lists->next_id == FrontAnimationId(0))
        ++lists->next_id;
    object->animation_handle = lists->next_id.value;
}
struct FrontTreeNode {
    FrontTreeNode *object;
    FrontTreeNode *next;
    unsigned char reserved_08[0x0C];
    FrontTreeNode *children;
    int children_flagged;
    unsigned char reserved_1c[0x304 - 0x1C];
    short stop_frame;
};
struct FrontAnimationLookup {
    unsigned char reserved[0x72DAD4];
    FrontTreeNode *primary;
    void *primary_tail;
    FrontTreeNode *secondary;
    Entity *FindInline(FrontAnimationId id) {
        if (!id.value)
            return 0;
        for (FrontTreeNode *node = primary; node; node = node->next)
            if (*(unsigned int *)node->object == id.value)
                return reinterpret_cast<Entity *>(node->object);
        for (FrontTreeNode *node = secondary; node; node = node->next)
            if (*(unsigned int *)node->object == id.value)
                return reinterpret_cast<Entity *>(node->object);
        return 0;
    }
    void SetFrame3Inline(FrontAnimationId id) {
        FrontTreeNode *node = reinterpret_cast<FrontTreeNode *>(FindInline(id));
        if (node) {
            node->stop_frame = 3;
            if (!node->children_flagged)
                for (node = node->children; node; node = node->next)
                    node->object->stop_frame = 3;
        }
    }
};
struct AnimationObject_0043e710 : Entity {};
struct AnimationResource_0043e710 {
    unsigned short id;
    unsigned char reserved_02[0x11C - 2];
    void **scripts;
    unsigned char reserved_120[4];
    int loading;
};
extern "C" __declspec(noinline) void __stdcall LoadScript_0043e710(AnimationResource_0043e710 *,
                                                                   AnimationObject_0043e710 *, int);
// Complete cluster body. LoadScript uses the public fastcall overload from
// entity.hpp; both native bindings consume the object in EDX, with ECX unused.
__declspec(noinline) void __stdcall Entity_Init(Entity *entity);
Entity *__fastcall Entity_Constructor(Entity *entity);
void *__cdecl operator new(unsigned int size);

struct FrontGameCounters {
    int high_score;    // 0x00474C40
    int score;         // 0x00474C44
    short power_units; // 0x00474C48
    int gauge;         // 0x00474C4C
    int gauge_decay;
    FrameTimer gauge_timer; // 0x00474C54
    int character;          // 0x00474C68
    int shot_type;          // 0x00474C6C
    int lives;              // 0x00474C70
    int difficulty;         // 0x00474C74
    int field_38;
    int stage;       // 0x00474C7C
    int stage_shown; // 0x00474C80
    int reserved_44[3];
    int continues;            // 0x00474C90
    int high_score_continues; // 0x00474C94
    int field_58;             // 0x00474C98
    int next_extend;          // 0x00474C9C
    FrontGameFlagWord flags;  // 0x00474CA0
    int reserved_64[2];
    int initial_lives; // 0x00474CAC
};
typedef char FrontGameNextExtendOffset[offsetof(FrontGameCounters, next_extend) == 0x5C ? 1 : -1];

struct FrontTask {
    int priority;
    unsigned int flags;
};
struct FrontInitializeView {
    int reserved_00[2];
    FrontTask *update_task;
    FrontTask *draw_task;
    Entity animations[43];
    FrontAnimationId digits[8];
    FrontAnimationHandle caption;
    FrontAnimationHandle secondary;
    unsigned char reserved_9e1c[0x9E50 - 0x9E1C];
    FrontAnimationId difficulty_caption;
    FrontAnimationId difficulty_label;
    FrontAnimationId persistent_a;
    FrontAnimationId persistent_b;
    unsigned char reserved_9e60[0x9E80 - 0x9E60];
    void *alternate_resource;
    unsigned char reserved_9e84[0x9E90 - 0x9E84];
    int field_9e90;
    unsigned char reserved_9e94[0x9EC8 - 0x9E94];
    void *captions;
    void SetLifeIcons(int count) {
        int index = 0;
        for (; index < count; ++index)
            animations[20 + index].flags_35C |= 2;
        if (index >= 9)
            return;
        for (; index < 9; ++index)
            animations[20 + index].flags_35C &= ~2u;
    }
    __declspec(noinline) void Initialize();
};
typedef char FrontAnimations[offsetof(FrontInitializeView, animations) == 0x10 ? 1 : -1];
typedef char
    FrontAlternate[offsetof(FrontInitializeView, alternate_resource) == 0x9E80 ? 1 : -1];
typedef char FrontResource[offsetof(FrontInitializeView, captions) == 0x9EC8 ? 1 : -1];
struct FrontStageThread {
    unsigned char reserved_00[0x8994];
    void *title_resource;
};
struct FrontGameState {
    unsigned char reserved_00[0x5C];
    int stage_one_gate;
};
extern "C" FrontStageThread *g_ascii_manager;
extern "C" FrontGameState *g_game;
extern "C" int data_00491fb8;
extern "C" int data_00491fc4;
extern "C" FrontGameCounters g_globals;
extern "C" FrontInitializeView *g_front;
