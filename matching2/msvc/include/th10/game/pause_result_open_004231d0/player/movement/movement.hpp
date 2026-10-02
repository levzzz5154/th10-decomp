#ifndef TH10_MOVEMENT_004250B0_HPP
#define TH10_MOVEMENT_004250B0_HPP
#include "th10/game/pause_result_open_004231d0/open_animation.hpp"

struct MovementPoint { int x, y; };
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
struct MovementState {
    unsigned char reserved_000[0x10];
    AnimationResource_00449870* resource;               // +010
    Entity animation;                                  // +014..3BF
    Vector3 position;                                  // +3C0
    MovementPoint integer_position;                    // +3CC
    int normal_speed;                                  // +3D4
    int slow_speed;                                    // +3D8
    int normal_diagonal_speed;                         // +3DC
    int slow_diagonal_speed;                           // +3E0
    unsigned char reserved_3e4[0x3F0 - 0x3E4];
    MovementPoint velocity;                            // +3F0
    unsigned char reserved_3f8[0x44C - 0x3F8];
    MovementPoint previous_movement;                   // +44C
    int direction;                                     // +454
    unsigned char reserved_458[0x48C - 0x458];
    int playable_state;                                // +48C
    unsigned char reserved_490[0x329C - 0x490];
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
    int playable;
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
    int next_id;
    __declspec(noinline) AnimationScriptId RegisterPrimaryBack(Entity* object);
};

extern unsigned int g_movement_input;                    // 0x474E5C
extern int g_movement_character;                         // 0x474C68
extern int g_movement_shot_type;                         // 0x474C6C
extern MovementGate* g_movement_gate;                    // 0x477704
extern MovementResources* g_movement_resources;          // 0x4776F0
extern float g_movement_position_scale;                  // 0x470B00
extern float g_movement_render_x;                        // 0x470B4C
extern float g_movement_render_y;                        // 0x470B48

__declspec(noinline) void __stdcall MovementLoadScript_0043e710(
    AnimationResource_00449870* resource, Entity* object, int index);
__declspec(noinline) void __fastcall MovementStopFrame_00449210(
    unsigned short frame, AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __fastcall MovementSetPosition_004492f0(
    const Vector3* position, AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) void __fastcall MovementSetTranslatedPosition_00449350(
    const Vector3* position, AnimationLookupContext* context, AnimationScriptId id);
__declspec(noinline) int PlayerMovement_004250b0(MovementState* player);

typedef char MovementOrbitSize[sizeof(MovementOrbit) == 0x98 ? 1 : -1];
typedef char MovementOrbitCurrent[offsetof(MovementOrbit, current) == 0x3C ? 1 : -1];
typedef char MovementOrbitCallbackOffset[offsetof(MovementOrbit, update) == 0x90 ? 1 : -1];
typedef char MovementAnimationOffset[offsetof(MovementState, animation) == 0x14 ? 1 : -1];
typedef char MovementPositionOffset[offsetof(MovementState, position) == 0x3C0 ? 1 : -1];
typedef char MovementSpeedOffset[offsetof(MovementState, normal_speed) == 0x3D4 ? 1 : -1];
typedef char MovementPreviousOffset[offsetof(MovementState, previous_movement) == 0x44C ? 1 : -1];
typedef char MovementStateOffset[offsetof(MovementState, playable_state) == 0x48C ? 1 : -1];
typedef char MovementHandleOffset[offsetof(MovementState, slow_animation) == 0x329C ? 1 : -1];
typedef char MovementOrbitsOffset[offsetof(MovementState, orbits) == 0x32A0 ? 1 : -1];
typedef char MovementTrailSectionsOffset[offsetof(MovementState, trail_sections) == 0x3500 ? 1 : -1];
typedef char MovementAgeOffset[offsetof(MovementState, slow_transition_age) == 0x4308 ? 1 : -1];
typedef char MovementTrailOffset[offsetof(MovementState, trail) == 0x436C ? 1 : -1];
typedef char MovementSlowOffset[offsetof(MovementState, slow) == 0x4474 ? 1 : -1];
#endif
