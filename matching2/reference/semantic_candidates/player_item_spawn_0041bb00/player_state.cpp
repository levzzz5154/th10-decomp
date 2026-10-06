#include "effect_update.hpp"

#include "item_spawn.hpp"

// External collaborators not yet part of the complete native graph.
struct PlayerBullet {
    // The five preceding virtual slots are not used by this owner.
    virtual void Unknown0();
    virtual void Unknown1();
    virtual void Unknown2();
    virtual void Unknown3();
    virtual void Unknown4();
    virtual void Retire(int mode);
    unsigned int reserved_04;
    PlayerBullet* next;
    int state;
};
struct PlayerBulletManager {
    unsigned char reserved_00[0x18];
    PlayerBullet* first;
    __declspec(noinline) int Evaluate(const Vec3* point, float radius, int mode);
    __declspec(noinline) int Reset();
};
struct PlayerInputMode { __declspec(noinline) int Set(int mode); };
struct PlayerDeathScene { __declspec(noinline) int Open(); };
struct PlayerPracticeState { unsigned char reserved_00[0x10]; int mode; };
// The game counters at 0x00474C40.
struct PlayerScoreGauge {
    int high_score;
    int score;
    short power;
    unsigned char reserved_0a[0x30 - 0x0a];
    int lives;
    unsigned char reserved_34[0x58 - 0x34];
    int field_58;
    __declspec(noinline) void AddWithMinimum(int amount);
};
extern "C" {
extern PlayerCollisionEngine* data_004776f0;
extern PlayerBulletManager* data_0047781c;
extern PlayerItemManager* data_00477818;
extern PlayerDeathScene* data_00477830;
extern PlayerPracticeState* data_00477838;
extern PlayerInputMode data_00491c28;
extern PlayerScoreGauge data_00474c40;
extern const float data_00470d44, data_00470bc8, data_00470d40;
extern const float data_00470d3c, data_00470d38, data_00470b4c;
__declspec(noinline) int __stdcall InitializePlayer_00405860(PickupPlayer* player);
__declspec(noinline) int __stdcall RefreshFamiliars_00426f70(PlayerState* player);
__declspec(noinline) int __stdcall UpdateContact_004269d0(PlayerState* player);
__declspec(noinline) double Entity_AngleToPoint_00426610(const PlayerState* player, const Vec3* point);
int __stdcall EffectPoolUpdate(PlayerState* player);
void __stdcall asm_FUN_0043ee30_0043ee30(Entity* object);
}

// These are inline expansions of the real embedded timer operations.
static inline void ResetPlayerTimer(FrameTimer& timer, int frame) {
    if (!(timer.flags & 1)) {
        timer.current = 0;
        timer.previous = -999999;
        timer.elapsed = 0.0f;
        timer.speed = &g_score_default_speed;
        timer.flags |= 1;
    }
    timer.current = frame;
    timer.elapsed = float(frame);
    timer.previous = frame - 1;
}
template <class Timer>
static __forceinline void DecrementPlayerTimer(Timer* timer, int count) {
    timer->previous = timer->current;
    if (*timer->speed > g_frame_timer_normal_lower && *timer->speed < g_frame_timer_normal_upper)
        timer->elapsed -= float(count);
    else
        timer->elapsed -= *timer->speed * float(count);
    timer->current = int(timer->elapsed);
}
static __forceinline Vec3 operator-(const Vec3& a, const Vec3& b) {
    Vec3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r;
}
struct ScaledVec3 : Vec3 {
    ScaledVec3(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
static __forceinline ScaledVec3 operator*(const Vec3& a, float f) {
    return ScaledVec3(a.x * f, a.y * f, a.z * f);
}
static __forceinline void ShowFamiliar(ScheduledFamiliar* familiar) { familiar->active = 1; }
static inline void ActivatePlayerCollisions(bool idle_only) {
    PlayerCollisionRecord* record = data_004776f0->records;
    for (int remaining = 2000; remaining; --remaining, ++record)
        if (record->state != 0 && record->state != 3 &&
                (!idle_only || record->countdown == 0))
            record->Activate();
}
#pragma code_seg(".text$c00playerstate")
extern "C" __declspec(noinline) int __stdcall PlayerState_Update_00425730(PlayerState* player) {
    switch (player->phase) {
    case 0: {
        player->fixed_y = 48000 - player->state_timer.current * 8000 / 60;
        player->spawn_origin.y = float(player->fixed_y) * 0.01f;
        ShowFamiliar(&player->familiars[0]);
        ShowFamiliar(&player->familiars[1]);
        ShowFamiliar(&player->familiars[2]);
        ShowFamiliar(&player->familiars[3]);
        int history_index;
        for (history_index = 32; player->familiar_level * 8 < history_index; --history_index)
            player->history[history_index] = player->history[player->familiar_level * 8];
        for (; history_index > 0; --history_index)
            player->history[history_index] = player->history[history_index - 1];
        PlayerState::HistoryPoint* head = player->history;
        head->x = player->fixed_x;
        head->y = player->fixed_y;
        if (player->state_timer.current >= 30) {
            ActivatePlayerCollisions(true);
            for (PlayerBullet* bullet = data_0047781c->first; bullet;) {
                PlayerBullet* next = bullet->next;
                if (bullet->state != 1) bullet->Retire(0);
                bullet = next;
            }
        } else {
            float radius = float(player->state_timer.current) * data_00470d44 + data_00470bc8;
            data_004776f0->Check(&player->previous_position, radius, 0, 1);
            data_004776f0->Check(&player->previous_position, data_00470d40 * radius, 0, 0);
            data_0047781c->Evaluate(&player->previous_position, radius, 0);
        }
        if (player->state_timer.current < 60) break;
        player->phase = 1;
        ResetPlayerTimer(player->state_timer, 0);
        // The actual entry transition continues directly into the live state.
    }
    case 1:
        if (data_0047770c && !data_0047770c->script && data_004776ec &&
                !data_004776ec->active && static_cast<short>(data_00474c40.power / 20) != 0 &&
                data_00474e5c.revive) {
            reinterpret_cast<PlayerSchedulerRecord*>(&player->invulnerability_timer)->SetSchedulerValue(270);
            InitializePlayer_00405860(data_004776ec);
            data_00474c40.power -= 20;
            RefreshFamiliars_00426f70(player);
            {
                int power = data_00474c40.power;
                data_0047770c->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
            }
            data_00474c40.AddWithMinimum(3000);
        }
        if (player->state_timer.current < 30) {
            ActivatePlayerCollisions(true);
            for (PlayerBullet* bullet = data_0047781c->first; bullet;) {
                PlayerBullet* next = bullet->next;
                if (bullet->state != 1) bullet->Retire(0);
                bullet = next;
            }
        }
        player->Move();
        break;
    case 4:
        if (player->state_timer.current >= 8) {
            UpdateContact_004269d0(player);
            // Once contact has been updated, state 4 shares the full death path.
        } else {
            if (data_004776ec && !data_004776ec->active &&
                    static_cast<short>(data_00474c40.power / 20) != 0 && data_00474e5c.revive) {
                reinterpret_cast<PlayerSchedulerRecord*>(&player->state_timer)->SetSchedulerValue(60);
                reinterpret_cast<PlayerSchedulerRecord*>(&player->invulnerability_timer)->SetSchedulerValue(200);
                InitializePlayer_00405860(data_004776ec);
                data_00474c40.power -= 20;
                RefreshFamiliars_00426f70(player);
                {
                int power = data_00474c40.power;
                data_0047770c->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
            }
                player->phase = 1;
            }
            break;
        }
    case 2:
        if (player->state_timer.current == 3) {
            data_00474c40.power -= 64;
            if (data_00474c40.power < 0) data_00474c40.power = 0;
            {
                int power = data_00474c40.power;
                data_0047770c->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
            }
            Vec3 target = {0.0f, player->spawn_origin.y - data_00470b4c, 0.0f};
            float angle = float(Entity_AngleToPoint_00426610(player, &target));
            for (int fan_index = 0; fan_index < 7; ++fan_index) {
                float direction = (float(fan_index) * data_00470d3c + angle) - data_00470d38;
                int kind = fan_index == 1 || fan_index == 3 || fan_index == 5 ? 4 : 1;
                data_00477818->Spawn(reinterpret_cast<const Vector3*>(&player->spawn_origin), kind, 0xffffff, direction, 3.0f);
            }
            RefreshFamiliars_00426f70(player);
        }
        if (player->state_timer.current >= 30) {
            if (data_00474c40.lives < 0) {
                if (data_00477838->mode == 1) data_00491c28.Set(4);
                else data_00477830->Open();
            } else {
                player->phase = 0;
                g_score_default_speed = 1.0f;
                Pickup_AllocateIndicator(0, player, &player->spawn_origin, 0x42000000, 0x41800000, 30, 150);
                player->previous_position = player->spawn_origin;
                player->fixed_x = 0;
                player->fixed_y = 48000;
                player->spawn_origin.x = 0.0f;
                player->spawn_origin.y = 480.0f;
                reinterpret_cast<PlayerSchedulerRecord*>(&player->invulnerability_timer)->SetSchedulerValue(280);
                reinterpret_cast<PlayerSchedulerRecord*>(&player->state_timer)->SetSchedulerValue(0);
            }
        }
        break;
    case 3:
        if (player->state_timer.current != 4 && player->state_timer.current == 15) {
            ActivatePlayerCollisions(false);
            data_0047781c->Reset();
        }
        break;
    }

    PickupRegion* circle = player->regions;
    PickupRegion* table = circle;
    for (int region_index = 0; region_index < 32; ++circle, ++region_index) {
        PickupRegion& region = table[region_index];
        if (region.flags & 1) {
            region.motion.Update();
            region.motion.Advance();
            circle->radius += region.speed;
            region.angle += region.angle_step;
            DecrementPlayerTimer(&region.timer, 1);
            if (region.timer.current <= 0) region.flags &= ~1u;
        }
    }
    FrameTimer& invulnerability = player->invulnerability_timer;
    if (invulnerability.current > 0) {
        DecrementPlayerTimer(&invulnerability, 1);
        if (player->state_timer.current != player->state_timer.previous && player->state_timer.current % 3 == 0) {
            player->animation.secondary_color = 0xff0000ff;
            player->animation.flags_35C |= 0x8000;
        } else player->animation.flags_35C &= ~0x8000u;
    } else player->animation.flags_35C &= ~0x8000u;
    asm_FUN_0043ee30_0043ee30(&player->animation);

    player->primary_min = player->spawn_origin - player->primary_half;
    player->primary_max = player->spawn_origin + player->primary_half;
    player->secondary_half_min = player->spawn_origin - player->full_size * 0.5f;
    player->secondary_half_max = player->full_size * 0.5f + player->spawn_origin;
    player->secondary_min = player->spawn_origin - player->outer_half;
    player->secondary_max = player->spawn_origin + player->outer_half;
    player->size_min = player->spawn_origin - player->full_size;
    player->size_max = player->spawn_origin + player->full_size;
    player->state_timer.TickInline();
    player->auxiliary_timer.TickInline();

    if (!data_0047770c->script && data_00477704 && data_00477704->enabled &&
            player->state_timer.current % 60 == 0) {
        ++data_00474c40.field_58;
        if (data_00474c40.field_58 > 1024) data_00474c40.field_58 = 1024;
        else if (data_00474c40.field_58 < -1024) data_00474c40.field_58 = -1024;
    }
    if (!data_0047770c->script && data_00477704 && data_00477704->enabled)
        player->UpdateSequence();
    else {
        ResetPlayerTimer(player->stage_timer, -1);
        player->pending_3504 = 0;
        player->pending_name_3508 = 0;
    }
    EffectPoolUpdate(player);
    return 1;
}
#pragma code_seg()
