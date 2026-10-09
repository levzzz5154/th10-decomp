#pragma once
#include "runtime.hpp"
#include "collision.hpp"
// Movement uses the same 0x4478-byte player object as the complete owner.
// This checked view exposes the overlapping familiar and scheduler fields:
// slow_animation overlays familiars[0] at 0x329C, orbit current positions
// overlay ScheduledFamiliar::position, and transition age overlays ordinal 5.
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
    AnimationRef first_animation;                 // +68
    AnimationRef second_animation;                // +6C
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
    AnimationResource_0043e710* resource;               // +010
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
    MovementDirection direction;                       // +454
    unsigned char reserved_458[0x488 - 0x458];
    FrameTimer auxiliary_timer;                        // +488, current +48C
    unsigned char reserved_49c[0x329C - 0x49C];
    AnimationRef slow_animation;                  // +329C
    MovementOrbit orbits[4];                           // +32A0
    int trail_sections;                                // +3500
    unsigned char reserved_3504[0x4308 - 0x3504];
    int slow_transition_age;                           // +4308
    unsigned char reserved_430c[0x436C - 0x430C];
    MovementPoint trail[33];                           // +436C..4473
    int slow;                                          // +4474
};

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

typedef char MovementPlayerSize[sizeof(MovementState)==sizeof(PlayerState)?1:-1];
typedef char MovementSharedFamiliarPosition[
 offsetof(MovementState,orbits)+offsetof(MovementOrbit,current)==
 offsetof(PlayerState,familiars)+offsetof(ScheduledFamiliar,position)?1:-1];
typedef char MovementSharedTransitionAge[
 offsetof(MovementState,slow_transition_age)==offsetof(PlayerState,active_by_ordinal)+5*4?1:-1];
extern "C" int data_00474c6c;
#include "movement_input.hpp"
extern "C" const float data_00470b00;
extern "C" const float data_00470b4c, data_00470b48;
// Actual complete animation operations, called only by the real movement body.
__declspec(noinline) void __fastcall MovementStopFrame_00449210(
 unsigned short frame, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall MovementSetPosition_004492f0(
 const Vector3* position, PickupAnimationLists* context, AnimationRef id);
__declspec(noinline) void __fastcall MovementSetTranslatedPosition_00449350(
 PickupAnimationLists* context, const Vector3* position, AnimationRef id);
