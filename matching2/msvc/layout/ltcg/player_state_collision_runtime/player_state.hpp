#pragma once
// Collaborators of the player-state update at 0x00425730.
#include "effect_update.hpp"
#include "item_spawn.hpp"
#include "movement_input.hpp"
#include "th10/game/power_display_004054b0.hpp"

struct PlayerBullet {
    // The five preceding virtual slots are not used by this owner.
    virtual void Unknown0();
    virtual void Unknown1();
    virtual void Unknown2();
    virtual void Unknown3();
    virtual void Unknown4();
    virtual void Retire(int mode);
    virtual void Unknown6();
    virtual int Evaluate(const Vec3* point, float radius, int mode);
    unsigned int reserved_04;
    PlayerBullet* next;
    int state;
};
struct PlayerBulletManager {
    unsigned char reserved_00[0x18];
    PlayerBullet* first;
    __declspec(noinline) int Evaluate(const Vec3* point, float radius, int mode);
    unsigned char reserved_01c[0x440-0x1c];
    Vec3 evaluation_point;
    __declspec(noinline) int Reset(int mode);
};
struct PlayerInputMode {
    unsigned char reserved_000[0x390];
    int mode;
    unsigned char reserved_394[0x3cc - 0x394];
    unsigned int flags;
    __declspec(noinline) void Set(int mode);
};
struct PlayerDeathScene {
    int reserved_00;
    int phase;
    int cursor;
    int background;
    FrameTimer timer;
    int current_resource;
    int result_flag;
    __declspec(noinline) int Open();
};
// The timer seen through the setter at 0x00405410.
struct PlayerSchedulerRecord {
    int field_00;    // 0x00 value, stored one below the raw value
    int field_04;    // 0x04 value
    float field_08;  // 0x08 value converted to float
    int field_0C;    // 0x0C default marker
    int flags_10;    // 0x10 initialised flag

    __declspec(noinline) void SetSchedulerValue(int value);
};
struct PlayerPracticeState { unsigned char reserved_00[0x10]; int mode; };
extern "C" {
extern PlayerCollisionEngine* data_004776f0;
extern PlayerBulletManager* data_0047781c;
extern PlayerItemManager* data_00477818;
extern PlayerDeathScene* data_00477830;
extern PlayerPracticeState* data_00477838;
extern PlayerInputMode data_00491c28;
__declspec(noinline) int __stdcall InitializePlayer_00405860(PickupPlayer* player);
__declspec(noinline) int __stdcall RefreshFamiliars_00426f70(PlayerState* player);
__declspec(noinline) int __stdcall UpdateContact_004269d0(PlayerState* player);
__declspec(noinline) double __stdcall Entity_AngleToPoint_00426610(const PlayerState* player, const Vec3* point);
int __stdcall EffectPoolUpdate(PlayerState* player);
void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
}

// Inline expansion of the region motion step.
inline void Motion::Update() {
    if (!(flags & 1)) {
        velocity.SetPolar(angle, speed);
        velocity.z = 0.0f;
    } else {
        radius += radius_step;
        angle = NormalizeAngle(speed + angle);
    }
}
