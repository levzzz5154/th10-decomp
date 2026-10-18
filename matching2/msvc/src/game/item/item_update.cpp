// 0x0041AFD0: update every normal and special item, including collection.
//
// Single translation unit: the genuine helper graph is included ahead of the
// update body, mirroring the production driver, so the whole-program link
// derives each helper's retail register convention from exactly the call
// sites this region has. The per-record view is anchored at position.y, the
// anchor retail keeps in EBP across the pool walk; position.x sits one float
// below it.
#include "../../../build_support/contexts/equivalent/game/item_update_0041afd0_context.cpp"

// Motion view anchored at position.y: every displacement then matches the
// retail record walk (state at +0x2c, timer at +0x18, variant at +0x3c).
struct ItemMotionY {
    float position_y;
    float position_z;
    ItemPolarVelocity2 velocity;
    int motion_counter;
    FrameTimer timer;
    int state;
    int kind;
    int display_kind;
    float magnet_speed;
    int variant;

    float& position_x() { return (&position_y)[-1]; }
    Vector3& position() { return *reinterpret_cast<Vector3*>(&position_y - 1); }
};
typedef char MotionYStateOffset[(offsetof(ItemMotionY,state)==0x2c)?1:-1];
typedef char MotionYTimerOffset[(offsetof(ItemMotionY,timer)==0x18)?1:-1];
typedef char MotionYVariantOffset[(offsetof(ItemMotionY,variant)==0x3c)?1:-1];

static __forceinline void IntegrateItem(ItemMotionY* motion) {
    Vector3Value displacement(g_game_speed*motion->velocity.x,
        g_game_speed*motion->velocity.y,g_game_speed*motion->velocity.z);
    motion->position().x+=displacement.x;
    motion->position().y+=displacement.y;
    motion->position().z+=displacement.z;
}

// Express rejection tests, so unordered coordinates follow the same branch
// as retail's x87 comparisons rather than failing a positive <= chain.
static __forceinline bool OutsideItemBox(float min_x,float min_y,float max_x,float max_y,const PlayerBox& box) {
    return box.min.x>min_x || box.min.y>min_y ||
        box.max.x<max_x || box.max.y<max_y;
}

#pragma code_seg(".text$00update")
extern "C" __declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager* manager) {
    ItemRunState& run=g_globals;
    const int idle=0;
    int convert_items=idle;
    manager->special_count=idle;
    manager->live_count=idle;
    SpawnItem* item=manager->items;
    ItemMotionY* motion=reinterpret_cast<ItemMotionY*>(&item->motion.position.y);
    const int seeking=1;
    int remaining=2198;
    for (;;) {
        if (motion->state==idle) goto step;
        if (motion->state==5) {
            if (--motion->variant<idle) {
                motion->state=2;
                Entity_StartScript(
                    static_cast<AnimationResourceFile*>(g_bullet_manager->item_animation),
                    &item->animation,motion->kind+374);
            }
            goto step;
        }
        Player* player;
        if (motion->state==seeking) {
            player=g_player;
            if ((player->state!=2 && player->state!=4 && player->position.y<flt_128) ||
                g_bomb->active!=idle) {
                motion->magnet_speed=player->shot_type->item_seek_speed;
                motion->state=3;
                goto seek_player;
            }
            IntegrateItem(motion);
            motion->velocity.y+=flt_0_03*g_game_speed;
            if (motion->velocity.y>=flt_0) motion->velocity.x=0.0f;
            if (motion->velocity.y>flt_2) motion->velocity.y=2.0f;
            // Retail tests the stored binary32 position, after discarding
            // the extended result of the planar addition.
            const volatile float& stored_y=motion->position_y;
            if (stored_y>flt_472) {
                motion->state=idle;
                goto step;
            }
        } else if (motion->state==2) {
            IntegrateItem(motion);
            motion->velocity.y+=flt_0_03*g_game_speed;
            if (motion->velocity.y>=flt_0) {
                player=g_player;
                motion->magnet_speed=player->shot_type->item_seek_speed;
                motion->state=3;
                goto seek_player;
            }
            const volatile float& stored_y=motion->position_y;
            if (stored_y>flt_472) {
                motion->state=idle;
                g_globals.AdjustPower(-4);
                goto step;
            }
            player=g_player;
        } else if (motion->state==3) {
        seek_player:
            player=g_player;
            float dx=player->position.x-motion->position().x;
            float dy=player->position.y-motion->position_y;
            float angle;
            if (dy==flt_0 && dx==flt_0) angle=1.5707963705062866f;
            else angle=static_cast<float>(atan2(static_cast<double>(dy),static_cast<double>(dx)));
            motion->velocity.SetPolar(angle,motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed<flt_12) {
                float speed=motion->magnet_speed;
                motion->magnet_speed=speed+flt_0_2;
            }
            if (player->state==4) {
                motion->state=seeking;
                motion->velocity.x=0.0f;
                motion->velocity.y=0.0f;
            }
        } else if (motion->state==4) {
            Player* target=g_player;
            motion->velocity.SetPolar(target->AngleFromPoint(&motion->position().x),motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed<flt_12) {
                float speed=motion->magnet_speed;
                motion->magnet_speed=speed+flt_0_2;
            }
            int player_state=target->state;
            player=g_player;
            if (player_state==4) {
                motion->state=seeking;
                motion->velocity.x=0.0f;
                motion->velocity.y=0.0f;
            }
        } else {
            player=g_player;
        }

        if (player->state!=2) {
            Vector3 min_point;
            Vector3 max_point;
            min_point.x=motion->position_x();
            min_point.y=motion->position_y;
            max_point.x=motion->position_x();
            max_point.y=motion->position_y;
            Vector3* point=&motion->position();
            if (!OutsideItemBox(min_point.x,min_point.y,max_point.x,max_point.y,player->item_collect_box)) {
                switch (motion->kind) {
                case 1: case 10: {
                    int changed=g_globals.AddPower(1);
                    int power=g_globals.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        Player_RefreshOptions(g_player);
                        g_smoll_score->Spawn(-1,point,0xFFFFFF40u);
                        g_sound_manager.QueuePan(29,point->x);
                        if (g_globals.power>=100) convert_items=1;
                        g_globals.AdjustPower(12);
                    } else {
                        g_smoll_score->Spawn(g_globals.power/2,point,0xFFFF4040u);
                    }
                    run.AdvanceGaugeTimer(60);
                    break;
                }
                case 2: {
                    int gauge=g_globals.gauge;
                    int value, adjustment;
                    if (player->position.y<flt_144) {
                        value=gauge*10;
                        value-=value%10;
                        g_smoll_score->Spawn(value,point,0xFFFFFF00u);
                        adjustment=8;
                    } else {
                        float scaled=(player->position.y-flt_144)*flt_0_003289474;
                        int penalty=static_cast<int>(scaled*(g_globals.gauge*0.5f-flt_5000));
                        value=gauge*10/2-penalty;
                        value-=value%10;
                        g_smoll_score->Spawn(value,point,0xFFFFFFFFu);
                        adjustment=1;
                    }
                    g_globals.AdjustPower(adjustment);
                    run.AddScore(value);
                    g_globals.AdvanceGaugeTimer(100);
                    break;
                }
                case 5: {
                    int value=g_globals.gauge*10;
                    g_smoll_score->Spawn(value,point,0xFFFFFF00u);
                    g_globals.AdjustPower(8);
                    run.AddScore(value);
                    g_globals.AdvanceGaugeTimer(100);
                    break;
                }
                case 3: {
                    int value=5000;
                    switch (g_globals.point_tier) {
                    case 0: case 1: value=5000; break;
                    case 2: value=8000; break;
                    case 3: case 4: value=10000; break;
                    }
                    g_smoll_score->Spawn(value,point,0xFF00FF00u);
                    g_globals.AddGauge(value);
                    run.AdvanceGaugeTimer(120);
                    break;
                }
                case 8:
                    g_globals.AddGauge(10);
                    run.AdvanceGaugeTimer(3);
                    run.AddScore(10);
                    break;
                case 9:
                    g_smoll_score->Spawn(100,point,0xFF00FF00u);
                    g_globals.AddGauge(100);
                    run.AdvanceGaugeTimer(60);
                    break;
                case 4: case 11: {
                    int changed=g_globals.AddPower(20);
                    int power=g_globals.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        Player_RefreshOptions(g_player);
                        g_sound_manager.QueuePan(29,point->x);
                        g_smoll_score->Spawn(-1,point,0xFFFFFF40u);
                        g_globals.AdjustPower(24);
                        if (g_globals.power>=100) convert_items=1;
                    } else {
                        g_smoll_score->Spawn(g_globals.power/2,point,0xFFFF4040u);
                    }
                    run.AdvanceGaugeTimer(20);
                    break;
                }
                case 7:
                    g_globals.AddLives(1);
                    g_globals.AdjustPower(256);
                    break;
                }
                motion->state=idle;
                g_sound_manager.QueuePan(20,motion->position().x);
                goto step;
            }
            if (motion->state!=4 && motion->state!=3) {
                unsigned int focused=g_input&4;
                short focused2=focused;
                bool magnet=(focused && !OutsideItemBox(min_point.x,min_point.y,max_point.x,max_point.y,player->focused_item_attract_box)) ||
                    (!focused2 && !OutsideItemBox(min_point.x,min_point.y,max_point.x,max_point.y,player->item_attract_box));
                if (magnet) {
                    motion->state=4;
                    motion->magnet_speed=player->shot_type->item_seek_speed*flt_0_33333334;
                }
            }
        }
        asm_FUN_0043ee30_0043ee30(&item->animation);
        motion->timer.TickInline();
        ++manager->live_count;
step:
        ++item;
        motion=reinterpret_cast<ItemMotionY*>(reinterpret_cast<char*>(motion)+sizeof(SpawnItem));
        if (--remaining==0) break;
    }
    if (convert_items) manager->ConvertItems();
    return 1;
}
#pragma code_seg()

// Compiler entry only: the game calls this region through its plain
// __stdcall ABI, so the model pins it behind a volatile callback.
typedef int (__stdcall *ItemUpdateCallback)(ItemSpawnManager*);
static ItemUpdateCallback volatile ItemUpdateEntryCallback = ItemManager_UpdateItems;
extern "C" __declspec(noinline) int __stdcall ItemUpdateEntry(ItemSpawnManager* manager) {
    return ItemUpdateEntryCallback(manager);
}
