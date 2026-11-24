// 0x0041AFD0: update every normal and special item, including collection.
#include <math.h>
#include "th10/game/item_collection/update.hpp"
#include "th10/game/entity_script_start.hpp"

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

// Express rejection tests, so unordered coordinates follow the same branch
// as retail's x87 comparisons rather than failing a positive <= chain.
static __forceinline bool OutsideItemBox(float min_x, float min_y, float max_x, float max_y,
                                         const PlayerBox& box) {
    return box.min.x > min_x || box.min.y > min_y || box.max.x < max_x || box.max.y < max_y;
}

static __forceinline void IntegrateItem(ItemMotionCursor motion) {
    Vector3Value displacement(motion->velocity.xy.x * g_game_speed,
                              motion->velocity.xy.y * g_game_speed,
                              motion->velocity.z * g_game_speed);
    motion->position.x += displacement.x;
    motion->position.y += displacement.y;
    motion->position.z += displacement.z;
}

static __forceinline bool ApplyItemGravity(ItemPolarVelocity2& velocity) {
    float& vertical_speed = velocity.y;
    vertical_speed += g_game_speed * 0.03f;
    return vertical_speed >= 0.0f;
}

static __forceinline void TickItemTimer(FrameTimer& t) {
    t.previous = t.current;
    if (*t.speed > g_frame_timer_normal_lower && *t.speed < g_frame_timer_normal_upper) {
        ++t.current;
        t.elapsed += 1.0f;
    } else {
        t.current = static_cast<int>(t.elapsed += *t.speed);
    }
}

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

#pragma code_seg(".text$f0041afd0F")
extern "C" __declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager* manager) {
    Item* item = manager->items;
    int convert_items = 0;
    int pickup_score;
    int rank_delta;
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

        if (motion->state == Falling) {
            if ((g_player->state != PLAYER_DYING && g_player->state != PLAYER_HIT &&
                 g_player->position.y < 128.0f) ||
                g_bomb->active != 0) {
                motion->magnet_speed = g_player->shot_type->item_seek_speed;
                motion->state = SeekingPlayer;
                goto seek_player;
            }
            IntegrateItem(motion);
            if (ApplyItemGravity(motion->velocity.xy))
                motion->velocity.xy.x = 0.0f;
            if (motion->velocity.xy.y > flt_2)
                motion->velocity.xy.y = 2.0f;
            const volatile float& stored_y = motion->position.y;
            if (stored_y > flt_472) {
                motion->state = Inactive;
                goto step;
            }
        } else if (motion->state == Launching) {
            IntegrateItem(motion);
            if (ApplyItemGravity(motion->velocity.xy)) {
                motion->magnet_speed = g_player->shot_type->item_seek_speed;
                motion->state = SeekingPlayer;
                goto seek_player;
            }
            const volatile float& stored_y = motion->position.y;
            if (stored_y > flt_472) {
                motion->state = Inactive;
                g_globals.AdjustRank(-4);
                goto step;
            }
        } else if (motion->state == SeekingPlayer) {
        seek_player:
            float dx = g_player->position.x - motion->position.x;
            float dy = g_player->position.y - motion->position.y;
            float angle;
            if (dy == 0.0f && dx == 0.0f)
                angle = 1.5707963705062866f;
            else
                angle = static_cast<float>(atan2(static_cast<double>(dy), static_cast<double>(dx)));
            motion->velocity.xy.SetPolar(angle, motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed < 12.0f)
                motion->magnet_speed += 0.2f;
            if (g_player->state == PLAYER_HIT) {
                motion->state = Falling;
                motion->velocity.xy.x = 0.0f;
                motion->velocity.xy.y = 0.0f;
            }
        } else if (motion->state == Attracted) {
            float speed = motion->magnet_speed;
            float angle = g_player->AngleFromPoint(&motion->position.x);
            motion->velocity.xy.SetPolar(angle, speed);
            IntegrateItem(motion);
            if (motion->magnet_speed < 12.0f)
                motion->magnet_speed += 0.2f;
            if (g_player->state == PLAYER_HIT) {
                motion->state = Falling;
                motion->velocity.xy.x = 0.0f;
                motion->velocity.xy.y = 0.0f;
            }
        }

        Vector3 min_point, max_point;
        Player* player = g_player;
        if (player->state == PLAYER_DYING)
            goto animate;

        max_point.x = motion->position.x;
        max_point.y = motion->position.y;
        min_point.x = motion->position.x;
        min_point.y = motion->position.y;
        if (!OutsideItemBox(min_point.x, min_point.y, max_point.x, max_point.y,
                            player->item_collect_box)) {
            ItemRunState& run = g_globals;
            const Vector3* point = &motion->position;
            switch (motion->kind) {
            case ITEM_POWER_SMALL:
            case ITEM_POWER_SMALL_BOSS: {
                int changed = g_globals.AddPower(1);
                int power = g_globals.power;
                g_front->SetPowerDigits(power / 20, ((power % 20) * 100) / 20);
                if (changed != 0) {
                    Player_RefreshOptions(g_player);
                    g_smoll_score->Spawn(-1, point, POPUP_COLOR_PALE_YELLOW);
                    g_sound_manager.QueuePan(SFX_POWER_UP, motion->position.x);
                    if (g_globals.power >= 100)
                        convert_items = 1;
                    g_globals.AdjustRank(12);
                    run.AdvanceGaugeTimer(60);
                } else {
                    g_smoll_score->Spawn(g_globals.power / 2, point, POPUP_COLOR_RED);
                    run.AdvanceGaugeTimer(60);
                }
                break;
            }
            case ITEM_POINT:
                if (player->position.y < 144.0f) {
                    int scaled = g_globals.gauge * 10;
                    pickup_score = scaled - scaled % 10;
                    g_smoll_score->Spawn(pickup_score, point, POPUP_COLOR_YELLOW);
                    rank_delta = 8;
                    goto add_score;
                } else {
                    float distance_scale = (player->position.y - 144.0f) / (448.0f - 144.0f);
                    int penalty = static_cast<int>(
                        distance_scale * (g_globals.gauge * 0.5f - 5000.0f));
                    pickup_score = g_globals.gauge * 10 / 2 - penalty;
                    pickup_score -= pickup_score % 10;
                    g_smoll_score->Spawn(pickup_score, point, POPUP_COLOR_WHITE);
                    rank_delta = 1;
                    goto add_score;
                }
            case ITEM_POINT_FULL_POWER:
                pickup_score = g_globals.gauge;
                pickup_score *= 10;
                g_smoll_score->Spawn(pickup_score, point, POPUP_COLOR_YELLOW);
                rank_delta = 8;
            add_score:
                g_globals.AdjustRank(rank_delta);
                run.AddScore(pickup_score);
                g_globals.AdvanceGaugeTimer(100);
                break;
            case ITEM_FAITH_LARGE: {
                int amount = 5000;
                switch (g_globals.point_tier) {
                case 0:
                case 1:
                    amount = 5000;
                    break;
                case 2:
                    amount = 8000;
                    break;
                case 3:
                case 4:
                    amount = 10000;
                    break;
                }
                g_smoll_score->Spawn(amount, point, POPUP_COLOR_GREEN);
                g_globals.AddGauge(amount);
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
            case ITEM_POWER_LARGE_BOSS: {
                int changed = g_globals.AddPower(20);
                int power = g_globals.power;
                g_front->SetPowerDigits(power / 20, ((power % 20) * 100) / 20);
                if (changed != 0) {
                    Player_RefreshOptions(g_player);
                    g_sound_manager.QueuePan(SFX_POWER_UP, motion->position.x);
                    g_smoll_score->Spawn(-1, point, POPUP_COLOR_PALE_YELLOW);
                    g_globals.AdjustRank(24);
                    if (g_globals.power < 100)
                        goto large_power_timer;
                    convert_items = 1;
                    run.AdvanceGaugeTimer(20);
                    break;
                } else {
                    g_smoll_score->Spawn(g_globals.power / 2, point, POPUP_COLOR_RED);
                }
            large_power_timer:
                run.AdvanceGaugeTimer(20);
                break;
            }
            case ITEM_1UP:
                g_globals.AddLives(1);
                g_globals.AdjustRank(256);
                break;
            }
            motion->state = Inactive;
            g_sound_manager.QueuePan(SFX_ITEM_COLLECT, motion->position.x);
            goto step;
        }

        if (motion->state != Attracted && motion->state != SeekingPlayer) {
            unsigned int focused = g_input & INPUT_FOCUS;
            if ((focused != 0 &&
                 !OutsideItemBox(min_point.x, min_point.y, max_point.x, max_point.y,
                                 player->focused_item_attract_box)) ||
                (static_cast<short>(focused) == 0 &&
                 !OutsideItemBox(min_point.x, min_point.y, max_point.x, max_point.y,
                                 player->item_attract_box))) {
                float speed = player->shot_type->item_seek_speed;
                motion->state = Attracted;
                motion->magnet_speed = speed * 0.3333333432674408f;
            }
        }

    animate:
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
