// 0x0041AFD0: update every normal and special item, including collection.
#include <math.h>
#include "th10/game/item_collection/update.hpp"
#include "th10/game/entity_script_start.hpp"

static __forceinline Player*& CurrentItemPlayer() { return g_player; }

// Retail keeps the address of position.y across the whole pool walk. Recover
// the real Item before accessing its fields. The final stride advances
// an integer address, not a pointer to a nonexistent record's y component.
class ItemMotionCursor {
    size_t height_address;
    enum { HeightOffset = offsetof(Item, motion) + offsetof(ItemMotionData, position)
                          + offsetof(Vector3, y) };

public:
    explicit ItemMotionCursor(Item& first)
        : height_address(reinterpret_cast<size_t>(&first.motion.position.y)) {}

    ItemMotionData* operator->() const {
        return &reinterpret_cast<Item*>(height_address - HeightOffset)->motion;
    }
    void Advance() { height_address += sizeof(Item); }
};

static __forceinline void IntegrateItem(ItemMotionCursor motion) {
    Vector3Value displacement(g_game_speed * motion->velocity.xy.x, g_game_speed * motion->velocity.xy.y,
                              g_game_speed * motion->velocity.z);
    motion->position.x += displacement.x;
    motion->position.y += displacement.y;
    motion->position.z += displacement.z;
}

static __forceinline void AdvancePursuingItem(ItemMotionCursor motion) {
    IntegrateItem(motion);
    if (motion->magnet_speed < 12.0f)
        motion->magnet_speed += 0.2f;
}

// Express rejection tests, so unordered coordinates follow the same branch
// as retail's x87 comparisons rather than failing a positive <= chain.
static __forceinline bool OutsideItemBox(float min_x, float min_y, float max_x, float max_y,
                                         const PlayerBox& box) {
    return box.min.x > min_x || box.min.y > min_y || box.max.x < max_x || box.max.y < max_y;
}

static __forceinline void TickItemTimer(FrameTimer& t) {
    t.previous = t.current;
    if (*t.speed > g_frame_timer_normal_lower && *t.speed < g_frame_timer_normal_upper) {
        ++t.current;
        t.elapsed += 1.0f;
    } else {
        t.current = int(t.elapsed += *t.speed);
    }
}

static __forceinline bool ApplyItemGravity(ItemPolarVelocity2& velocity) {
    // The sign test uses the x87 sum; the speed cap reads the stored float.
    float& vertical_speed = velocity.y;
    vertical_speed += 0.03f * g_game_speed;
    return vertical_speed >= 0.0f;
}

static __forceinline void BeginSeekingItem(ItemMotionCursor motion, const Player* player) {
    motion->magnet_speed = player->shot_type->item_seek_speed;
    motion->state = SeekingPlayer;
}

static __forceinline void CancelPursuitOnHit(ItemMotionCursor motion, float& horizontal_speed,
                                            PlayerStateId target_state) {
    if (target_state == PLAYER_HIT) {
        motion->state = Falling;
        horizontal_speed = 0.0f;
        motion->velocity.xy.y = 0.0f;
    }
}

enum PowerPickup { SmallPowerGain = 1, LargePowerGain = 20 };

enum ItemSfxId {
    SFX_ITEM_COLLECT = 20,
    SFX_POWER_UP = 29
};

enum ScorePopupColor {
    POPUP_COLOR_WHITE = 0xFFFFFFFFu,
    POPUP_COLOR_YELLOW = 0xFFFFFF00u,
    POPUP_COLOR_PALE_YELLOW = 0xFFFFFF40u,
    POPUP_COLOR_RED = 0xFFFF4040u,
    POPUP_COLOR_GREEN = 0xFF00FF00u
};

enum ItemInputMask {
    INPUT_FOCUS = 4
};

template <PowerPickup gain>
static __forceinline void CollectPowerItem(ItemMotionCursor motion, const Vector3* point, int& convert_items) {
    ItemRunState& run = g_globals;
    int changed = g_globals.AddPower(gain);
    int power = g_globals.power;
    g_front->SetPowerDigits(power / 20, (power % 20) * 100 / 20);
    if (changed) {
        Player_RefreshOptions(CurrentItemPlayer());
        // Sound, score text and the full-power check occur in different orders.
        if (gain == LargePowerGain) {
            g_sound_manager.QueuePan(SFX_POWER_UP, motion->position.x);
            g_smoll_score->Spawn(-1, point, POPUP_COLOR_PALE_YELLOW);
            g_globals.AdjustPower(24);
            if (g_globals.power >= 100)
                convert_items = 1;
        } else {
            g_smoll_score->Spawn(-1, point, POPUP_COLOR_PALE_YELLOW);
            g_sound_manager.QueuePan(SFX_POWER_UP, motion->position.x);
            if (g_globals.power >= 100)
                convert_items = 1;
            g_globals.AdjustPower(12);
        }
    } else {
        g_smoll_score->Spawn(g_globals.power / 2, point, POPUP_COLOR_RED);
    }
    run.AdvanceGaugeTimer(gain == SmallPowerGain ? 60 : 20);
}

static __forceinline void CollectPointItem(const Player* player, const Vector3* point) {
    ItemRunState& run = g_globals;
    int value, adjustment;
    if (player->position.y < 144.0f) {
        int scaled = g_globals.gauge * 10;
        value = scaled - scaled % 10;
        g_smoll_score->Spawn(value, point, POPUP_COLOR_YELLOW);
        adjustment = 8;
    } else {
        float scaled = (player->position.y - 144.0f) * 0.0032894737f;
        int penalty = static_cast<int>(scaled * (g_globals.gauge * 0.5f - 5000.0f));
        value = g_globals.gauge * 10 / 2 - penalty;
        value -= value % 10;
        g_smoll_score->Spawn(value, point, POPUP_COLOR_WHITE);
        adjustment = 1;
    }
    g_globals.AdjustPower(adjustment);
    run.AddScore(value);
    g_globals.AdvanceGaugeTimer(100);
}

static __forceinline int TieredGaugeValue(int tier) {
    int value = 5000;
    switch (tier) {
    case 0:
    case 1:
        value = 5000;
        break;
    case 2:
        value = 8000;
        break;
    case 3:
    case 4:
        value = 10000;
        break;
    }
    return value;
}

static __forceinline void CollectItem(ItemMotionCursor motion, const Player* player, int& convert_items) {
    ItemRunState& run = g_globals;
    const Vector3* point = &motion->position;
    switch (motion->kind) {
    case ITEM_POWER_SMALL:
    case ITEM_POWER_SMALL_BOSS:
        CollectPowerItem<SmallPowerGain>(motion, point, convert_items);
        break;
    case ITEM_POINT:
        CollectPointItem(player, point);
        break;
    case ITEM_POINT_FULL_POWER: {
        int value = g_globals.gauge * 10;
        g_smoll_score->Spawn(value, point, POPUP_COLOR_YELLOW);
        g_globals.AdjustPower(8);
        run.AddScore(value);
        g_globals.AdvanceGaugeTimer(100);
        break;
    }
    case ITEM_FAITH_LARGE: {
        int value = TieredGaugeValue(g_globals.point_tier);
        g_smoll_score->Spawn(value, point, POPUP_COLOR_GREEN);
        g_globals.AddGauge(value);
        run.AdvanceGaugeTimer(120);
        break;
    }
    case ITEM_FAITH_CANCEL:
        g_globals.AddGauge(10);
        run.AdvanceGaugeTimer(3);
        run.AddScore(10);
        break;
    case ITEM_FAITH_CONVERTED:
        g_smoll_score->Spawn(100, point, POPUP_COLOR_GREEN);
        g_globals.AddGauge(100);
        run.AdvanceGaugeTimer(60);
        break;
    case ITEM_POWER_LARGE:
    case ITEM_POWER_LARGE_BOSS:
        CollectPowerItem<LargePowerGain>(motion, point, convert_items);
        break;
    case ITEM_1UP:
        g_globals.AddLives(1);
        g_globals.AdjustPower(256);
        break;
    }
    motion->state = Inactive;
    g_sound_manager.QueuePan(SFX_ITEM_COLLECT, motion->position.x);
}

// A collected item has already been retired and must not tick its animation or timer.
static __forceinline bool UpdateItemContact(ItemMotionCursor motion, const Player* player,
                                           int& convert_items) {
    if (player->state != PLAYER_DYING) {
        Vector3 min_point;
        Vector3 max_point;
        max_point.x = motion->position.x;
        max_point.y = motion->position.y;
        min_point.x = motion->position.x;
        min_point.y = motion->position.y;
        if (!OutsideItemBox(min_point.x, min_point.y, max_point.x, max_point.y,
                            player->item_collect_box)) {
            CollectItem(motion, player, convert_items);
            return true;
        }
        if (motion->state != Attracted && motion->state != SeekingPlayer) {
            unsigned int focused = g_input & INPUT_FOCUS;
            short focused2 = focused;
            bool magnet =
                (focused && !OutsideItemBox(min_point.x, min_point.y, max_point.x, max_point.y,
                                            player->focused_item_attract_box)) ||
                (!focused2 && !OutsideItemBox(min_point.x, min_point.y, max_point.x, max_point.y,
                                              player->item_attract_box));
            if (magnet) {
                motion->magnet_speed = player->shot_type->item_seek_speed * 0.33333334f;
                motion->state = Attracted;
            }
        }
    }
    return false;
}

#pragma code_seg(".text$f0041afd0F")
extern "C" __declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager* manager) {
    Item* item = manager->items;
    int convert_items = 0;
    manager->special_count = 0;
    manager->live_count = 0;
    ItemMotionCursor motion(*item);
    int remaining = sizeof(manager->items) / sizeof(manager->items[0]);
    for (;;) {
        if (motion->state == Inactive)
            goto step;
        if (motion->state == WaitingForScript) {
            if (--motion->variant < 0) {
                motion->state = Launching;
                Entity_StartScript(
                    static_cast<AnimationResourceFile*>(g_bullet_manager->item_animation),
                    item, motion->kind + 374);
            }
            goto step;
        }
        Player* player;
        ItemPolarVelocity2* velocity;
        if (motion->state == Falling) {
            player = CurrentItemPlayer();
            if ((player->state != PLAYER_DYING && player->state != PLAYER_HIT &&
                 player->position.y < 128.0f) ||
                g_bomb->active != 0) {
                BeginSeekingItem(motion, player);
                goto seek_player;
            }
            IntegrateItem(motion);
            if (ApplyItemGravity(motion->velocity.xy))
                motion->velocity.xy.x = 0.0f;
            if (motion->velocity.xy.y > flt_2)
                motion->velocity.xy.y = 2.0f;
            // Retail tests the stored binary32 position, after discarding
            // the extended result of the planar addition.
            const volatile float& stored_y = motion->position.y;
            if (stored_y > flt_472) {
                motion->state = Inactive;
                goto step;
            }
        } else if (motion->state == Launching) {
            IntegrateItem(motion);
            if (ApplyItemGravity(motion->velocity.xy)) {
                BeginSeekingItem(motion, CurrentItemPlayer());
                player = CurrentItemPlayer();
                goto seek_player;
            }
            const volatile float& stored_y = motion->position.y;
            if (stored_y > flt_472) {
                motion->state = Inactive;
                g_globals.AdjustPower(-4);
                goto step;
            }
            player = CurrentItemPlayer();
        } else if (motion->state == SeekingPlayer) {
            player = CurrentItemPlayer();
        seek_player:
            float dx = player->position.x - motion->position.x;
            float dy = player->position.y - motion->position.y;
            float angle;
            if (dy == 0.0f && dx == 0.0f) {
                velocity = &motion->velocity.xy;
                angle = 1.5707963705062866f;
            } else {
                velocity = &motion->velocity.xy;
                angle = static_cast<float>(atan2(static_cast<double>(dy), static_cast<double>(dx)));
            }
            velocity->SetPolar(angle, motion->magnet_speed);
            AdvancePursuingItem(motion);
            CancelPursuitOnHit(motion, velocity->x, player->state);
        } else if (motion->state == Attracted) {
            Player* target = CurrentItemPlayer();
            velocity = &motion->velocity.xy;
            velocity->SetPolar(target->AngleFromPoint(&motion->position.x), motion->magnet_speed);
            AdvancePursuingItem(motion);
            PlayerStateId player_state = target->state;
            player = CurrentItemPlayer();
            CancelPursuitOnHit(motion, velocity->x, player_state);
        } else {
            player = CurrentItemPlayer();
        }

        if (UpdateItemContact(motion, player, convert_items))
            goto step;
        RunAnimationVm(item);
        TickItemTimer(motion->timer);
        ++manager->live_count;
    step:
        ++item;
        motion.Advance();
        if (--remaining == 0)
            break;
    }
    if (convert_items)
        manager->ConvertItems();
    return 1;
}
#pragma code_seg()
