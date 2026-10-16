#ifndef TH10_GAME_LASER_SPAWN_0041C510_HPP
#define TH10_GAME_LASER_SPAWN_0041C510_HPP

#include <string.h>
#include "th10/game/entity.hpp"
#include "th10/math/timer.hpp"

// An animated sprite owned by a laser. Construction retires the registration
// bit of every animation slot, wipes the sprite and marks it as showing nothing.
struct LaserSprite2 : Entity {
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
struct LaserTrack {
    unsigned int flags;                  // +0x00
    unsigned char reserved_04[0x30];
};

struct LaserSpawnParameters;

// The virtual interface every laser answers; slot 1 sets a laser up.
struct LaserMethods {
    virtual void Virtual00() = 0;
    virtual int Initialize(const LaserSpawnParameters* parameters) = 0;
};

// Common part of every laser; its own vtable is at 0x0046DAB0.
struct LaserBase {
    void* vtable;                        // +0x000
    LaserBase* previous;        // +0x004
    LaserBase* next;            // +0x008
    int state;                           // +0x00C
    FrameTimer timer;                    // +0x010
    Vector3 position;                    // +0x024
    unsigned char reserved_030[0x54 - 0x30];
    int id;                              // +0x054
    unsigned char reserved_058[0x68 - 0x58];
    LaserTrack tracks[18];      // +0x068
    FrameTimer tail_timer;               // +0x410

    LaserMethods* Methods() {
        return reinterpret_cast<LaserMethods*>(this);
    }
};
typedef char LaserBaseSize[sizeof(LaserBase) == 0x424 ? 1 : -1];

// 0x0041C030: construct the common part. The laser arrives in EDX; the first
// argument is the unused ECX slot.
LaserBase* __fastcall LaserBase_Construct2(void* unused, LaserBase* self);

// Creation parameters of a line laser; they start cleared.
struct LineLaserParams2 {
    unsigned char reserved_000[0x1DC];

    void Construct() {
        memset(this, 0, sizeof(*this));
    }
};

// A line laser; vtable at 0x0046DA60.
struct LineLaser2 : LaserBase {
    LineLaserParams2 params;     // +0x424
    LaserSprite2 beam;           // +0x600
    LaserSprite2 flare;          // +0x9AC
};
typedef char LineLaserSize[sizeof(LineLaser2) == 0xD58 ? 1 : -1];

// Creation parameters of a beam laser; they start cleared with a width of 8.
struct BeamLaserParams2 {
    unsigned char reserved_000[0x2C];
    float width;                         // +0x2C
    unsigned char reserved_030[0x1F8 - 0x30];

    void Construct() {
        memset(this, 0, sizeof(*this));
        width = 8.0f;
    }
};

// A beam laser; vtable at 0x0046DA10.
struct BeamLaser : LaserBase {
    BeamLaserParams2 params;     // +0x424
    LaserSprite2 beam;           // +0x61C
    LaserSprite2 flare;          // +0x9C8
};
typedef char BeamLaserSize[sizeof(BeamLaser) == 0xD74 ? 1 : -1];

extern "C" unsigned char g_line_laser_vtable;  // line laser vtable
extern "C" unsigned char g_beam_laser_vtable;  // beam laser vtable

// 0x0041C5B0, 0x0041C680: construct a laser in raw storage.
__declspec(noinline) LineLaser2* __fastcall LineLaser_Construct2(LineLaser2* self);
__declspec(noinline) BeamLaser* __fastcall BeamLaser_Construct2(BeamLaser* self);

// The laser manager: a list of at most 256 lasers.
struct LaserManager2 {
    unsigned char reserved_000[0x434];
    LaserBase* tail;            // +0x434
    int count;                           // +0x438
    int next_id;                         // +0x43C

    // Give a new laser the current id and link it after the last one.
    void Append(LaserBase* laser) {
        laser->id = next_id;
        LaserBase* last = tail;
        laser->previous = last;
        last->next = laser;
        tail = laser;
        ++count;
    }
};

// Creation parameters of any laser, as the spawn sees them.
struct LaserSpawnParameters {
    // 0x0041C510: create a laser of a kind from these parameters; returns its
    // id, 0 when the manager is full.
    __declspec(noinline) int SpawnIn(LaserManager2* manager, int kind) const;
};

extern "C" LaserManager2* g_laser_manager;

#endif
