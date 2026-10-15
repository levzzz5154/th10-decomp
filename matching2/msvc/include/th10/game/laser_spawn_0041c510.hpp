#ifndef TH10_GAME_LASER_SPAWN_0041C510_HPP
#define TH10_GAME_LASER_SPAWN_0041C510_HPP

#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

// An animated sprite owned by a laser. Construction retires the registration
// bit of every animation slot, wipes the sprite and marks it as showing nothing.
struct LaserSprite_0041c510 : Entity {
    __forceinline void Construct() {
        ClearRegistrationBit(&flags_06C);
        ClearRegistrationBit(&flags_0B0);
        ClearRegistrationBit(&flags_0FC);
        ClearRegistrationBit(&flags_128);
        ClearRegistrationBit(&flags_174);
        ClearRegistrationBit(&flags_1B0);
        ClearRegistrationBit(&flags_1FC);
        ClearRegistrationBit(&flags_228);
        ClearRegistrationBit(&flags_378);
        memset(this, 0, sizeof(Entity));
        SpriteIndex() = -1;
    }

    static void ClearRegistrationBit(uint32_t* flags) {
        *flags &= ~1u;
    }
};

// One interpolated value of a laser.
struct LaserTrack_0041c030 {
    unsigned int flags;                  // +0x00
    unsigned char reserved_04[0x30];
};

struct LaserSpawnParameters_0041c510;

// The virtual interface every laser answers; slot 1 sets a laser up.
struct LaserMethods_0041c510 {
    virtual void Virtual00() = 0;
    virtual int Initialize(const LaserSpawnParameters_0041c510* parameters) = 0;
};

// Common part of every laser; its own vtable is at 0x0046DAB0.
struct LaserBase_0041c030 {
    void* vtable;                        // +0x000
    LaserBase_0041c030* previous;        // +0x004
    LaserBase_0041c030* next;            // +0x008
    int state;                           // +0x00C
    FrameTimer timer;                    // +0x010
    Vector3 position;                    // +0x024
    unsigned char reserved_030[0x54 - 0x30];
    int id;                              // +0x054
    unsigned char reserved_058[0x68 - 0x58];
    LaserTrack_0041c030 tracks[18];      // +0x068
    FrameTimer tail_timer;               // +0x410

    LaserMethods_0041c510* Methods() {
        return reinterpret_cast<LaserMethods_0041c510*>(this);
    }
};
typedef char LaserBaseSize_0041c030[sizeof(LaserBase_0041c030) == 0x424 ? 1 : -1];

// 0x0041C030: construct the common part. The laser arrives in EDX; the first
// argument is the unused ECX slot.
LaserBase_0041c030* __fastcall LaserBase_Construct_0041c030(void* unused, LaserBase_0041c030* self);

// Creation parameters of a line laser; they start cleared.
struct LineLaserParams_0041c5b0 {
    unsigned char reserved_000[0x1DC];

    void Construct() {
        memset(this, 0, sizeof(*this));
    }
};

// A line laser; vtable at 0x0046DA60.
struct LineLaser_0041c5b0 : LaserBase_0041c030 {
    LineLaserParams_0041c5b0 params;     // +0x424
    LaserSprite_0041c510 beam;           // +0x600
    LaserSprite_0041c510 flare;          // +0x9AC
};
typedef char LineLaserSize_0041c5b0[sizeof(LineLaser_0041c5b0) == 0xD58 ? 1 : -1];

// Creation parameters of a beam laser; they start cleared with a width of 8.
struct BeamLaserParams_0041c680 {
    unsigned char reserved_000[0x2C];
    float width;                         // +0x2C
    unsigned char reserved_030[0x1F8 - 0x30];

    void Construct() {
        memset(this, 0, sizeof(*this));
        width = 8.0f;
    }
};

// A beam laser; vtable at 0x0046DA10.
struct BeamLaser_0041c680 : LaserBase_0041c030 {
    BeamLaserParams_0041c680 params;     // +0x424
    LaserSprite_0041c510 beam;           // +0x61C
    LaserSprite_0041c510 flare;          // +0x9C8
};
typedef char BeamLaserSize_0041c680[sizeof(BeamLaser_0041c680) == 0xD74 ? 1 : -1];

extern "C" unsigned char g_line_laser_vtable;  // line laser vtable
extern "C" unsigned char g_beam_laser_vtable;  // beam laser vtable

// 0x0041C5B0, 0x0041C680: construct a laser in raw storage.
__declspec(noinline) LineLaser_0041c5b0* __fastcall LineLaser_Construct_0041c5b0(LineLaser_0041c5b0* self);
__declspec(noinline) BeamLaser_0041c680* __fastcall BeamLaser_Construct_0041c680(BeamLaser_0041c680* self);

// The laser manager: a list of at most 256 lasers.
struct LaserManager_0041c510 {
    unsigned char reserved_000[0x434];
    LaserBase_0041c030* tail;            // +0x434
    int count;                           // +0x438
    int next_id;                         // +0x43C

    // Give a new laser the current id and link it after the last one.
    void Append(LaserBase_0041c030* laser) {
        laser->id = next_id;
        LaserBase_0041c030* last = tail;
        laser->previous = last;
        last->next = laser;
        tail = laser;
        ++count;
    }
};

// Creation parameters of any laser, as the spawn sees them.
struct LaserSpawnParameters_0041c510 {
    // 0x0041C510: create a laser of a kind from these parameters; returns its
    // id, 0 when the manager is full.
    __declspec(noinline) int SpawnIn(LaserManager_0041c510* manager, int kind) const;
};

extern "C" LaserManager_0041c510* g_laser_manager;

#endif
