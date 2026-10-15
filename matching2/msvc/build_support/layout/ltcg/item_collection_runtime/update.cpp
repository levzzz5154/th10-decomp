// 0x0041AFD0: update every normal and special item, including collection.
// This complete C++ candidate is unselected until its full raw gate passes.
#include <math.h>
#include "types/update.hpp"
#include "th10/game/entity_script_start.hpp"

static __forceinline void IntegrateItem(ItemMotion_0041bb00* motion) {
    Vector3Value displacement(g_game_speed*motion->velocity.x,
        g_game_speed*motion->velocity.y,g_game_speed*motion->velocity.z);
    motion->position.x+=displacement.x;
    motion->position.y+=displacement.y;
    motion->position.z+=displacement.z;
}

// Express rejection tests, so unordered coordinates follow the same branch
// as retail's x87 comparisons rather than failing a positive <= chain.
static __forceinline bool OutsideItemBox(const Vector3& point,const PlayerBox& box) {
    return box.min.x>point.x || box.min.y>point.y ||
        box.max.x<point.x || box.max.y<point.y;
}

#pragma code_seg(".text$f0041afd0F")
extern "C" __declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager_0041bb00* manager) {
    int convert_items=0;
    manager->special_count=0;
    manager->live_count=0;
    SpawnItem_0041bb00* item=manager->items;
    ItemMotion_0041bb00* motion=&item->motion;
    for (int remaining=2198;remaining;--remaining,++item,motion=&item->motion) {
        if (motion->state==0) continue;
        if (motion->state==5) {
            if (--motion->variant<0) {
                motion->state=2;
                Entity_StartScript_00404f30(
                    static_cast<AnimationResource_0043e710*>(data_004776f0->item_animation),
                    &item->animation,motion->kind+374);
            }
            continue;
        }
        Player* player=g_player;
        if (motion->state==1) {
            if ((player->state!=2 && player->state!=4 && player->position.y<data_00470bf4) ||
                g_bomb->active!=0) {
                motion->magnet_speed=player->shot_type->item_seek_speed;
                motion->state=3;
                goto seek_player;
            }
            // Keep the planar products through the additions, as retail's
            // x87 path does; the Z displacement crosses a float store.
            {
                double dx=static_cast<double>(g_game_speed)*motion->velocity.x;
                double dy=static_cast<double>(g_game_speed)*motion->velocity.y;
                volatile float dz=g_game_speed*motion->velocity.z;
                motion->position.x=static_cast<float>(motion->position.x+dx);
                motion->position.y=static_cast<float>(motion->position.y+dy);
                motion->position.z+=dz;
            }
            motion->velocity.y+=g_game_speed*data_00470cdc;
            if (motion->velocity.y>=data_00470b04) motion->velocity.x=0.0f;
            if (motion->velocity.y>data_00470b08) motion->velocity.y=2.0f;
            // Retail tests the stored binary32 position, after discarding
            // the extended result of the planar addition.
            const volatile float& stored_y=motion->position.y;
            if (stored_y>data_00470be0) {
                motion->state=0;
                continue;
            }
        } else if (motion->state==2) {
            IntegrateItem(motion);
            motion->velocity.y+=g_game_speed*data_00470cdc;
            if (motion->velocity.y>=data_00470b04) {
                player=g_player;
                motion->magnet_speed=player->shot_type->item_seek_speed;
                motion->state=3;
                goto seek_player;
            }
            if (motion->position.y>data_00470be0) {
                motion->state=0;
                g_globals.AdjustPower(-4);
                continue;
            }
            player=g_player;
        } else if (motion->state==3) {
            player=g_player;
        seek_player:
            float dx=player->position.x-motion->position.x;
            float dy=player->position.y-motion->position.y;
            float angle;
            if (dy==data_00470b04 && dx==data_00470b04) angle=data_00470b94;
            else angle=static_cast<float>(atan2(static_cast<double>(dy),static_cast<double>(dx)));
            motion->velocity.SetPolar(angle,motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed<data_00470cd8) motion->magnet_speed+=data_00470c38;
            if (player->state==4) {
                motion->state=1;
                motion->velocity.x=0.0f;
                motion->velocity.y=0.0f;
            }
        } else if (motion->state==4) {
            Player* target=g_player;
            motion->velocity.SetPolar(target->AngleFromPoint(&motion->position.x),motion->magnet_speed);
            IntegrateItem(motion);
            if (motion->magnet_speed<data_00470cd8) motion->magnet_speed+=data_00470c38;
            int player_state=target->state;
            player=g_player;
            if (player_state==4) {
                motion->state=1;
                motion->velocity.x=0.0f;
                motion->velocity.y=0.0f;
            }
        } else {
            player=g_player;
        }

        if (player->state!=2) {
            Vector3 position=motion->position;
            if (!OutsideItemBox(position,player->item_collect_box)) {
                switch (motion->kind) {
                case 1: case 10: {
                    int changed=g_globals.AddPower(1);
                    int power=g_globals.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        Player_RefreshOptions(g_player);
                        g_smoll_score->Spawn(-1,&motion->position,0xFFFFFF40u);
                        g_sound_manager.QueuePan(29,motion->position.x);
                        if (g_globals.power>=100) convert_items=1;
                        g_globals.AdjustPower(12);
                    } else {
                        g_smoll_score->Spawn(g_globals.power/2,&motion->position,0xFFFF4040u);
                    }
                    g_globals.AdvanceGaugeTimer(60);
                    break;
                }
                case 2: {
                    int value, adjustment;
                    if (player->position.y<data_00470cd4) {
                        value=g_globals.gauge*10;
                        value-=value%10;
                        g_smoll_score->Spawn(value,&motion->position,0xFFFFFF00u);
                        adjustment=8;
                    } else {
                        int penalty=static_cast<int>((player->position.y-data_00470cd4)*data_00470cd0*
                            (g_globals.gauge*0.5f-data_00470ce0));
                        value=g_globals.gauge*10/2-penalty;
                        value-=value%10;
                        g_smoll_score->Spawn(value,&motion->position,0xFFFFFFFFu);
                        adjustment=1;
                    }
                    g_globals.AdjustPower(adjustment);
                    g_globals.AddScore(value);
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
                    g_smoll_score->Spawn(value,&motion->position,0xFF00FF00u);
                    g_globals.AddGauge(value);
                    g_globals.AdvanceGaugeTimer(120);
                    break;
                }
                case 4: case 11: {
                    int changed=g_globals.AddPower(20);
                    int power=g_globals.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        Player_RefreshOptions(g_player);
                        g_sound_manager.QueuePan(29,motion->position.x);
                        g_smoll_score->Spawn(-1,&motion->position,0xFFFFFF40u);
                        g_globals.AdjustPower(24);
                        if (g_globals.power>=100) convert_items=1;
                    } else {
                        g_smoll_score->Spawn(g_globals.power/2,&motion->position,0xFFFF4040u);
                    }
                    g_globals.AdvanceGaugeTimer(20);
                    break;
                }
                case 5: {
                    int value=g_globals.gauge*10;
                    g_smoll_score->Spawn(value,&motion->position,0xFFFFFF00u);
                    g_globals.AdjustPower(8);
                    g_globals.AddScore(value);
                    g_globals.AdvanceGaugeTimer(100);
                    break;
                }
                case 7:
                    g_globals.AddLives(1);
                    g_globals.AdjustPower(256);
                    break;
                case 8:
                    g_globals.AddGauge(10);
                    g_globals.AdvanceGaugeTimer(3);
                    g_globals.AddScore(10);
                    break;
                case 9:
                    g_smoll_score->Spawn(100,&motion->position,0xFF00FF00u);
                    g_globals.AddGauge(100);
                    g_globals.AdvanceGaugeTimer(60);
                    break;
                }
                motion->state=0;
                g_sound_manager.QueuePan(20,motion->position.x);
                continue;
            }
            if (motion->state!=4 && motion->state!=3) {
                unsigned int focused=g_input&4;
                bool magnet=(focused && !OutsideItemBox(position,player->focused_item_attract_box)) ||
                    (!focused && !OutsideItemBox(position,player->item_attract_box));
                if (magnet) {
                    motion->state=4;
                    motion->magnet_speed=player->shot_type->item_seek_speed*data_00470cc4;
                }
            }
        }
        asm_FUN_0043ee30_0043ee30(&item->animation);
        motion->timer.TickInline();
        ++manager->live_count;
    }
    if (convert_items) manager->ConvertItems();
    return 1;
}
#pragma code_seg()
