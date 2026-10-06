#ifndef TH10_OPEN_ANIMATION_HPP
#define TH10_OPEN_ANIMATION_HPP
#include <stddef.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

struct MovementRegisteredId {
    int value;
    MovementRegisteredId() {}
    MovementRegisteredId(int value) : value(value) {}
    MovementRegisteredId(const MovementRegisteredId& other) : value(other.value) {}
    MovementRegisteredId& operator=(MovementRegisteredId other) { value=other.value; return *this; }
    MovementRegisteredId& operator++() { ++value; return *this; }
    bool operator==(MovementRegisteredId other) const { return value==other.value; }
};
struct AnimationScriptId {
    int value;
    AnimationScriptId() {}
    AnimationScriptId(int value) : value(value) {}
    AnimationScriptId& operator=(MovementRegisteredId other) { value=other.value; return *this; }
    AnimationScriptId& operator=(AnimationScriptId other) { value=other.value; return *this; }
    AnimationScriptId& operator++() { ++value; return *this; }
    bool operator==(AnimationScriptId other) const { return value==other.value; }
};
struct AnimationLookupContext;
__declspec(noinline) void* __fastcall AnimationManager_Find_004491c0(
    AnimationLookupContext* context, AnimationScriptId id);
extern "C" void* data_00491c10;
extern "C" float data_00476f78;
__declspec(noinline) void __stdcall Entity_Init(Entity* entity);
Entity* __fastcall Entity_Constructor(Entity* self);
void* __cdecl operator new(unsigned int size);
extern "C" int __stdcall RunAnimationVm_0043ee30(Entity* object);

struct AnimationPool {
    char header[0x68];
    Entity objects[4096];
    unsigned char occupied[4096];
    int next_slot;
    __declspec(noinline) Entity* Allocate();
};
struct AnimationResource_00449870 {
    unsigned short id;
    unsigned char reserved_002[0x11C - 2];
    void** scripts;
    unsigned char reserved_120[4];
    int loading;
    __declspec(noinline) void InitializeObject(Entity* object, int index);

};
__declspec(noinline) void __stdcall LoadScriptPreservingState_0043e7e0(
    AnimationResource_00449870* resource, Entity* object, int index);

struct AnimationManagerNodeOpen {
    Entity* animation;
    AnimationManagerNodeOpen* next;
    AnimationManagerNodeOpen* previous;
};
struct AnimationListsOpen {
    unsigned char reserved[0x72DADC];
    AnimationManagerNodeOpen* secondary_head;
    AnimationManagerNodeOpen* secondary_tail;
    unsigned char reserved_72dae4[0x732454 - 0x72DAE4];
    int next_id;
    __declspec(noinline) AnimationScriptId RegisterSecondaryBack(Entity* object);
};
typedef char PoolObjectOffsetCheck[offsetof(AnimationPool, objects) == 0x68 ? 1 : -1];
typedef char PoolBusyOffsetCheck[offsetof(AnimationPool, occupied) == 0x3AC068 ? 1 : -1];
typedef char PoolCursorOffsetCheck[offsetof(AnimationPool, next_slot) == 0x3AD068 ? 1 : -1];
typedef char ResourceScriptsOffsetCheck[offsetof(AnimationResource_00449870, scripts) == 0x11C ? 1 : -1];
typedef char ResourceLoadingOffsetCheck[offsetof(AnimationResource_00449870, loading) == 0x124 ? 1 : -1];
typedef char SecondaryIdOffsetCheck[offsetof(AnimationListsOpen, next_id) == 0x732454 ? 1 : -1];

// The VM word at +0x35C is shared with the low-word end marker.
struct AnimationOpenFlags {
    unsigned low_flags : 30;
    unsigned render_enabled : 1;
    unsigned high_flag : 1;
};
#endif

#ifndef TH10_MOVEMENT_004250B0_HPP
#define TH10_MOVEMENT_004250B0_HPP


__declspec(noinline) void* __stdcall MovementLoadScript(int index, AnimationResource_00449870* resource, Entity* object);

struct MovementPoint {
 long x, y;
 MovementPoint() {}
 MovementPoint(int x, int y):x(x),y(y) {}
 MovementPoint& operator=(const MovementPoint& other) { x=other.x; y=other.y; return *this; }
 MovementPoint operator+(const MovementPoint& other) const { return MovementPoint(x+other.x,y+other.y); }
 MovementPoint operator-(const MovementPoint& other) const { return MovementPoint(x-other.x,y-other.y); }
 MovementPoint operator*(int scale) const { return MovementPoint(x*scale,y*scale); }
 MovementPoint operator/(int divisor) const { return MovementPoint(x/divisor,y/divisor); }
 bool operator!=(const MovementPoint& other) const { return x!=other.x || y!=other.y; }
 MovementPoint& operator+=(const MovementPoint& other) { x+=other.x; y+=other.y; return *this; }
};
struct MovementOrbit;
typedef int (__fastcall *MovementOrbitCallback)(MovementOrbit* orbit);
struct MovementOrbit {
    int active;                                        // +00
    unsigned char reserved_004[0x34 - 4];
    MovementPoint desired;                             // +34
    MovementPoint current;                             // +3C
    MovementPoint normal_offset;                       // +44
    MovementPoint slow_offset;                         // +4C
    unsigned char reserved_054[0x68 - 0x54];
    AnimationScriptId first_animation;                 // +68
    AnimationScriptId second_animation;                // +6C
    unsigned char reserved_070[0x8C - 0x70];
    int reset_position;                                // +8C
    MovementOrbitCallback update;                      // +90
    int reserved_094;
};
enum MovementDirection {
    MovementNone=0, MovementUp=1, MovementDown=2, MovementLeft=3,
    MovementRight=4, MovementUpLeft=5, MovementUpRight=6,
    MovementDownLeft=7, MovementDownRight=8
};
struct MovementState {
    unsigned char reserved_000[0x10];
    AnimationResource_00449870* resource;               // +010
    Entity animation;                                  // +014..3BF
    volatile Vector3 position;                                  // +3C0
    MovementPoint integer_position;                    // +3CC
    int normal_speed;                                  // +3D4
    int slow_speed;                                    // +3D8
    int normal_diagonal_speed;                         // +3DC
    int slow_diagonal_speed;                           // +3E0
    unsigned char reserved_3e4[0x3F0 - 0x3E4];
    MovementPoint velocity;                            // +3F0
    unsigned char reserved_3f8[0x44C - 0x3F8];
    MovementPoint previous_movement;                   // +44C
    MovementDirection direction;                       // +454
    unsigned char reserved_458[0x488 - 0x458];
    FrameTimer auxiliary_timer;                        // +488, current +48C
    unsigned char reserved_49c[0x329C - 0x49C];
    AnimationScriptId slow_animation;                  // +329C
    MovementOrbit orbits[4];                           // +32A0
    int trail_sections;                                // +3500
    unsigned char reserved_3504[0x4308 - 0x3504];
    int slow_transition_age;                           // +4308
    unsigned char reserved_430c[0x436C - 0x430C];
    MovementPoint trail[33];                           // +436C..4473
    int slow;                                          // +4474
};
struct MovementGate {
    unsigned char reserved[0x60];
    int active;
};
struct MovementResources {
    unsigned char reserved[0x3E0B50];
    AnimationResource_00449870* player_resource;
};
struct MovementPrimaryLists {
    unsigned char reserved[0x72DAD4];
    AnimationManagerNodeOpen* head;
    AnimationManagerNodeOpen* tail;
    unsigned char reserved_72dadc[0x732454 - 0x72DADC];
    MovementRegisteredId next_id;
    __declspec(noinline) MovementRegisteredId RegisterPrimaryBack(Entity* object);
};

struct MovementInput { union { unsigned int word; unsigned char bytes[4]; }; };
extern volatile MovementInput g_movement_input;                    // 0x474E5C
extern int g_movement_character;                         // 0x474C68
extern int g_movement_shot_type;                         // 0x474C6C
extern MovementGate* g_movement_gate;                    // 0x477704
extern MovementResources* g_movement_resources;          // 0x4776F0
extern const float g_movement_position_scale;                  // 0x470B00
extern const float g_movement_render_x;                        // 0x470B4C
extern const float g_movement_render_y;                        // 0x470B48


__declspec(noinline) void __fastcall MovementStopFrame_00449210(
    unsigned short frame, AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __fastcall MovementSetPosition_004492f0(
    const Vector3* position, AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __fastcall MovementSetTranslatedPosition_00449350(
    const Vector3* position, AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) int PlayerMovement_004250b0(MovementState* player);

typedef char MovementDirectionSize[sizeof(MovementDirection) == 4 ? 1 : -1];
typedef char MovementOrbitSize[sizeof(MovementOrbit) == 0x98 ? 1 : -1];
typedef char MovementOrbitCurrent[offsetof(MovementOrbit, current) == 0x3C ? 1 : -1];
typedef char MovementOrbitCallbackOffset[offsetof(MovementOrbit, update) == 0x90 ? 1 : -1];
typedef char MovementAnimationOffset[offsetof(MovementState, animation) == 0x14 ? 1 : -1];
typedef char MovementPositionOffset[offsetof(MovementState, position) == 0x3C0 ? 1 : -1];
typedef char MovementSpeedOffset[offsetof(MovementState, normal_speed) == 0x3D4 ? 1 : -1];
typedef char MovementPreviousOffset[offsetof(MovementState, previous_movement) == 0x44C ? 1 : -1];
typedef char MovementAuxiliaryTimerOffset[offsetof(MovementState, auxiliary_timer) == 0x488 ? 1 : -1];
typedef char MovementAuxiliaryFrameOffset[offsetof(MovementState, auxiliary_timer) + offsetof(FrameTimer, current) == 0x48C ? 1 : -1];
typedef char MovementHandleOffset[offsetof(MovementState, slow_animation) == 0x329C ? 1 : -1];
typedef char MovementOrbitsOffset[offsetof(MovementState, orbits) == 0x32A0 ? 1 : -1];
typedef char MovementTrailSectionsOffset[offsetof(MovementState, trail_sections) == 0x3500 ? 1 : -1];
typedef char MovementAgeOffset[offsetof(MovementState, slow_transition_age) == 0x4308 ? 1 : -1];
typedef char MovementTrailOffset[offsetof(MovementState, trail) == 0x436C ? 1 : -1];
typedef char MovementSlowOffset[offsetof(MovementState, slow) == 0x4474 ? 1 : -1];
#endif
