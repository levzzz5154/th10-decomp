// 0x0041AFD0: update every normal and special item, including collection.
//
// Single translation unit: the genuine helper graph is included ahead of the
// update body, mirroring the production driver, so the whole-program link
// derives each helper's retail register convention from exactly the call
// sites this region has. The per-record view is anchored at position.y, the
// anchor retail keeps in EBP across the pool walk; position.x sits one float
// below it.
#include "item_update_0041afd0_context.cpp"

// Motion view anchored at position.y: every displacement then matches the
// retail record walk (state at +0x2c, timer at +0x18, variant at +0x3c).
struct ItemMotionY_0041afd0 {
    float position_y;
    float position_z;
    ItemPolarVelocity_0041bb00 velocity;
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
typedef char MotionYStateOffset[(offsetof(ItemMotionY_0041afd0,state)==0x2c)?1:-1];
typedef char MotionYTimerOffset[(offsetof(ItemMotionY_0041afd0,timer)==0x18)?1:-1];
typedef char MotionYVariantOffset[(offsetof(ItemMotionY_0041afd0,variant)==0x3c)?1:-1];

static __forceinline void IntegrateItem(ItemMotionY_0041afd0* motion) {
    Vector3Value displacement(data_00476f78*motion->velocity.x,
        data_00476f78*motion->velocity.y,data_00476f78*motion->velocity.z);
    motion->position().x+=displacement.x;
    motion->position().y+=displacement.y;
    motion->position().z+=displacement.z;
}

// Express rejection tests, so unordered coordinates follow the same branch
// as retail's x87 comparisons rather than failing a positive <= chain.
static __forceinline bool OutsideItemBox(float point_x,float point_y,const PlayerBox& box) {
    return box.min.x>point_x || box.min.y>point_y ||
        box.max.x<point_x || box.max.y<point_y;
}

#pragma code_seg(".text$00update")
extern "C" __declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager_0041bb00* manager) {
    const int idle=0;
    int convert_items=idle;
    manager->special_count=idle;
    manager->live_count=idle;
    SpawnItem_0041bb00* item=manager->items;
    ItemMotionY_0041afd0* motion=reinterpret_cast<ItemMotionY_0041afd0*>(&item->motion.position.y);
    const int seeking=1;
    int remaining=2198;
    for (;;) {
        if (motion->state==idle) goto step;
        if (motion->state==5) {
            if (--motion->variant<idle) {
                motion->state=2;
                Entity_StartScript_00404f30(
                    static_cast<AnimationResource_0043e710*>(data_004776f0->item_animation),
                    &item->animation,motion->kind+374);
            }
            goto step;
        }
        Player* player;
        if (motion->state==seeking) {
            player=g_player;
            if ((player->state!=2 && player->state!=4 && player->position.y<data_00470bf4) ||
                g_bomb->active!=idle) {
                motion->magnet_speed=player->shot_type->item_seek_speed;
                motion->state=3;
                goto seek_player;
            }
            // Keep the planar products through the additions, as retail's
            // x87 path does; the Z displacement crosses a float store.
            {
                double dx=static_cast<double>(data_00476f78)*motion->velocity.x;
                double dy=static_cast<double>(data_00476f78)*motion->velocity.y;
                volatile float dz=data_00476f78*motion->velocity.z;
                motion->position().x=static_cast<float>(motion->position().x+dx);
                motion->position().y=static_cast<float>(motion->position().y+dy);
                motion->position().z+=dz;
            }
            motion->velocity.y+=data_00476f78*data_00470cdc;
            if (motion->velocity.y>=data_00470b04) motion->velocity.x=0.0f;
            if (motion->velocity.y>data_00470b08) motion->velocity.y=2.0f;
            // Retail tests the stored binary32 position, after discarding
            // the extended result of the planar addition.
            const volatile float& stored_y=motion->position_y;
            if (stored_y>data_00470be0) {
                motion->state=idle;
                goto step;
            }
        } else if (motion->state==2) {
            IntegrateItem(motion);
            motion->velocity.y+=data_00476f78*data_00470cdc;
            if (motion->velocity.y>=data_00470b04) {
                player=g_player;
                motion->magnet_speed=player->shot_type->item_seek_speed;
                motion->state=3;
                goto seek_player;
            }
            const volatile float& stored_y=motion->position_y;
            if (stored_y>data_00470be0) {
                motion->state=idle;
                data_00474c40.AdjustPower(-4);
                goto step;
            }
            player=g_player;
        } else if (motion->state==3) {
            player=g_player;
        seek_player:
            float dx=player->position.x-motion->position().x;
            float dy=player->position.y-motion->position_y;
            float angle;
            if (dy==data_00470b04 && dx==data_00470b04) angle=1.5707963705062866f;
            else angle=static_cast<float>(atan2(static_cast<double>(dy),static_cast<double>(dx)));
            motion->velocity.SetPolar(angle,motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed<data_00470cd8) motion->magnet_speed+=data_00470c38;
            if (player->state==4) {
                motion->state=seeking;
                motion->velocity.x=0.0f;
                motion->velocity.y=0.0f;
            }
        } else if (motion->state==4) {
            Player* target=g_player;
            motion->velocity.SetPolar(target->AngleFromPoint(&motion->position().x),motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed<data_00470cd8) motion->magnet_speed+=data_00470c38;
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
            if (!OutsideItemBox(motion->position().x,motion->position().y,player->item_collect_box)) {
                switch (motion->kind) {
                case 1: case 10: {
                    int changed=data_00474c40.AddPower(1);
                    int power=data_00474c40.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        Player_RefreshOptions(g_player);
                        g_smoll_score->Spawn(-1,&motion->position(),0xFFFFFF40u);
                        data_00492590.QueuePan(29,motion->position().x);
                        if (data_00474c40.power>=100) convert_items=1;
                        data_00474c40.AdjustPower(12);
                    } else {
                        g_smoll_score->Spawn(data_00474c40.power/2,&motion->position(),0xFFFF4040u);
                    }
                    data_00474c40.AdvanceGaugeTimer(60);
                    break;
                }
                case 2: {
                    int value, adjustment;
                    if (player->position.y<data_00470cd4) {
                        value=data_00474c40.gauge*10;
                        value-=value%10;
                        g_smoll_score->Spawn(value,&motion->position(),0xFFFFFF00u);
                        adjustment=8;
                    } else {
                        int penalty=static_cast<int>((player->position.y-data_00470cd4)*data_00470cd0*
                            (data_00474c40.gauge*0.5f-data_00470ce0));
                        value=data_00474c40.gauge*10/2-penalty;
                        value-=value%10;
                        g_smoll_score->Spawn(value,&motion->position(),0xFFFFFFFFu);
                        adjustment=1;
                    }
                    data_00474c40.AdjustPower(adjustment);
                    data_00474c40.AddScore(value);
                    data_00474c40.AdvanceGaugeTimer(100);
                    break;
                }
                case 5: {
                    int value=data_00474c40.gauge*10;
                    g_smoll_score->Spawn(value,&motion->position(),0xFFFFFF00u);
                    data_00474c40.AdjustPower(8);
                    data_00474c40.AddScore(value);
                    data_00474c40.AdvanceGaugeTimer(100);
                    break;
                }
                case 3: {
                    int value=5000;
                    switch (data_00474c40.point_tier) {
                    case 0: case 1: value=5000; break;
                    case 2: value=8000; break;
                    case 3: case 4: value=10000; break;
                    }
                    g_smoll_score->Spawn(value,&motion->position(),0xFF00FF00u);
                    data_00474c40.AddGauge(value);
                    data_00474c40.AdvanceGaugeTimer(120);
                    break;
                }
                case 8:
                    data_00474c40.AddGauge(10);
                    data_00474c40.AdvanceGaugeTimer(3);
                    data_00474c40.AddScore(10);
                    break;
                case 9:
                    g_smoll_score->Spawn(100,&motion->position(),0xFF00FF00u);
                    data_00474c40.AddGauge(100);
                    data_00474c40.AdvanceGaugeTimer(60);
                    break;
                case 4: case 11: {
                    int changed=data_00474c40.AddPower(20);
                    int power=data_00474c40.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        Player_RefreshOptions(g_player);
                        data_00492590.QueuePan(29,motion->position().x);
                        g_smoll_score->Spawn(-1,&motion->position(),0xFFFFFF40u);
                        data_00474c40.AdjustPower(24);
                        if (data_00474c40.power>=100) convert_items=1;
                    } else {
                        g_smoll_score->Spawn(data_00474c40.power/2,&motion->position(),0xFFFF4040u);
                    }
                    data_00474c40.AdvanceGaugeTimer(20);
                    break;
                }
                case 7:
                    data_00474c40.AddLives(1);
                    data_00474c40.AdjustPower(256);
                    break;
                }
                motion->state=idle;
                data_00492590.QueuePan(20,motion->position().x);
                goto step;
            }
            if (motion->state!=4 && motion->state!=3) {
                unsigned int focused=g_input&4;
                bool magnet=(focused && !OutsideItemBox(motion->position().x,motion->position().y,player->focused_item_attract_box)) ||
                    (!focused && !OutsideItemBox(motion->position().x,motion->position().y,player->item_attract_box));
                if (magnet) {
                    motion->state=4;
                    motion->magnet_speed=player->shot_type->item_seek_speed*data_00470cc4;
                }
            }
        }
        asm_FUN_0043ee30_0043ee30(&item->animation);
        motion->timer.TickInline();
        ++manager->live_count;
step:
        ++item;
        motion=reinterpret_cast<ItemMotionY_0041afd0*>(reinterpret_cast<char*>(motion)+sizeof(SpawnItem_0041bb00));
        if (--remaining==0) break;
    }
    if (convert_items) manager->ConvertItems();
    return 1;
}
#pragma code_seg()

// Compiler entry only: the game calls this region through its plain
// __stdcall ABI, so the model pins it behind a volatile callback.
typedef int (__stdcall *ItemUpdateCallback)(ItemSpawnManager_0041bb00*);
static ItemUpdateCallback volatile ItemUpdateEntryCallback = ItemManager_UpdateItems;
extern "C" __declspec(noinline) int __stdcall ItemUpdateEntry(ItemSpawnManager_0041bb00* manager) {
    return ItemUpdateEntryCallback(manager);
}
