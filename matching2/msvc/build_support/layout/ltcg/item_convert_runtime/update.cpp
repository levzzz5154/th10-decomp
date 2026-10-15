// 0x0041AFD0: update every normal and special item, including collection.
// This complete C++ candidate is unselected until its full raw gate passes.
#include <math.h>
#include "types/update.hpp"
#include "th10/game/entity_script_start.hpp"

static __forceinline void IntegrateItem(SpawnItem* item) {
    Vector3Value displacement(g_game_speed*item->velocity.x,
        g_game_speed*item->velocity.y,g_game_speed*item->velocity.z);
    item->position.x+=displacement.x;
    item->position.y+=displacement.y;
    item->position.z+=displacement.z;
}

// Express rejection tests, so unordered coordinates follow the same branch
// as retail's x87 comparisons rather than failing a positive <= chain.
static __forceinline bool OutsideItemBox(const Vector3& point,const ItemCollectionBox& box) {
    return point.x<box.minimum.x || point.y<box.minimum.y ||
        box.maximum.x<point.x || box.maximum.y<point.y;
}

#pragma code_seg(".text$f0041afd0F")
extern "C" __declspec(noinline) int __stdcall ItemManager_UpdateItems(ItemSpawnManager* manager) {
    bool convert_items=false;
    manager->special_count=0;
    manager->live_count=0;
    SpawnItem* item=manager->items;
    for (int remaining=2198;remaining;--remaining,++item) {
        if (item->state==0) continue;
        if (item->state==5) {
            if (--item->variant<0) {
                item->state=2;
                Entity_StartScript(
                    static_cast<AnimationResourceFile*>(g_bullet_manager->item_animation),
                    &item->animation,item->kind+374);
            }
            continue;
        }
        ItemCollector* player=g_player;
        if (item->state==1) {
            if ((player->state!=2 && player->state!=4 && player->position.y<flt_128) ||
                g_bomb->active!=0) {
                item->magnet_speed=player->movement->seek_speed;
                item->state=3;
                goto seek_player;
            }
            // Keep the planar products through the additions, as retail's
            // x87 path does; the Z displacement crosses a float store.
            {
                double dx=static_cast<double>(g_game_speed)*item->velocity.x;
                double dy=static_cast<double>(g_game_speed)*item->velocity.y;
                volatile float dz=g_game_speed*item->velocity.z;
                item->position.x=static_cast<float>(item->position.x+dx);
                item->position.y=static_cast<float>(item->position.y+dy);
                item->position.z+=dz;
            }
            item->velocity.y+=g_game_speed*flt_0_03;
            if (item->velocity.y>=flt_0) item->velocity.x=0.0f;
            if (item->velocity.y>flt_2) item->velocity.y=2.0f;
            // Retail tests the stored binary32 position, after discarding
            // the extended result of the planar addition.
            const volatile float& stored_y=item->position.y;
            if (stored_y>flt_472) {
                item->state=0;
                continue;
            }
        } else if (item->state==2) {
            IntegrateItem(item);
            item->velocity.y+=g_game_speed*flt_0_03;
            if (item->velocity.y>=flt_0) {
                player=g_player;
                item->magnet_speed=player->movement->seek_speed;
                item->state=3;
                goto seek_player;
            }
            if (item->position.y>flt_472) {
                item->state=0;
                g_globals.AdjustPower(-4);
                continue;
            }
            player=g_player;
        } else if (item->state==3) {
            player=g_player;
        seek_player:
            float dx=player->position.x-item->position.x;
            float dy=player->position.y-item->position.y;
            float angle;
            if (dy==flt_0 && dx==flt_0) angle=flt_pi_2;
            else angle=static_cast<float>(atan2(static_cast<double>(dy),static_cast<double>(dx)));
            item->velocity.SetPolar(angle,item->magnet_speed);
            IntegrateItem(item);
            if (item->magnet_speed<flt_12) item->magnet_speed+=flt_0_2;
            if (player->state==4) {
                item->state=1;
                item->velocity.x=0.0f;
                item->velocity.y=0.0f;
            }
        } else if (item->state==4) {
            ItemCollector* target=g_player;
            item->velocity.SetPolar(target->AngleFromPoint(&item->position),item->magnet_speed);
            IntegrateItem(item);
            if (item->magnet_speed<flt_12) item->magnet_speed+=flt_0_2;
            int player_state=target->state;
            player=g_player;
            if (player_state==4) {
                item->state=1;
                item->velocity.x=0.0f;
                item->velocity.y=0.0f;
            }
        } else {
            player=g_player;
        }

        if (player->state!=2) {
            Vector3 position=item->position;
            if (!OutsideItemBox(position,player->collection)) {
                switch (item->kind) {
                case 1: case 10: {
                    int changed=g_globals.AddPower(1);
                    int power=g_globals.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        ItemCollector_PowerChanged(g_player);
                        g_smoll_score->Spawn(-1,&item->position,0xFFFFFF40u);
                        g_sound_manager.QueuePan(29,item->position.x);
                        if (g_globals.power>=100) convert_items=true;
                        g_globals.AdjustPower(12);
                    } else {
                        g_smoll_score->Spawn(g_globals.power/2,&item->position,0xFFFF4040u);
                    }
                    g_globals.AdvanceGaugeTimer(60);
                    break;
                }
                case 2: {
                    int value, adjustment;
                    if (player->position.y<flt_144) {
                        value=g_globals.gauge*10;
                        value-=value%10;
                        g_smoll_score->Spawn(value,&item->position,0xFFFFFF00u);
                        adjustment=8;
                    } else {
                        int penalty=static_cast<int>((player->position.y-flt_144)*flt_0_003289474*
                            (g_globals.gauge*0.5f-flt_5000));
                        value=g_globals.gauge*10/2-penalty;
                        value-=value%10;
                        g_smoll_score->Spawn(value,&item->position,0xFFFFFFFFu);
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
                    g_smoll_score->Spawn(value,&item->position,0xFF00FF00u);
                    g_globals.AddGauge(value);
                    g_globals.AdvanceGaugeTimer(120);
                    break;
                }
                case 4: case 11: {
                    int changed=g_globals.AddPower(20);
                    int power=g_globals.power;
                    g_front->SetPowerDigits(power/20,(power%20)*100/20);
                    if (changed) {
                        ItemCollector_PowerChanged(g_player);
                        g_sound_manager.QueuePan(29,item->position.x);
                        g_smoll_score->Spawn(-1,&item->position,0xFFFFFF40u);
                        g_globals.AdjustPower(24);
                        if (g_globals.power>=100) convert_items=true;
                    } else {
                        g_smoll_score->Spawn(g_globals.power/2,&item->position,0xFFFF4040u);
                    }
                    g_globals.AdvanceGaugeTimer(20);
                    break;
                }
                case 5: {
                    int value=g_globals.gauge*10;
                    g_smoll_score->Spawn(value,&item->position,0xFFFFFF00u);
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
                    g_smoll_score->Spawn(100,&item->position,0xFF00FF00u);
                    g_globals.AddGauge(100);
                    g_globals.AdvanceGaugeTimer(60);
                    break;
                }
                item->state=0;
                g_sound_manager.QueuePan(20,item->position.x);
                continue;
            }
            if (item->state!=4 && item->state!=3) {
                unsigned int focused=g_input&4;
                bool magnet=(focused && !OutsideItemBox(position,player->focused_magnet)) ||
                    (!focused && !OutsideItemBox(position,player->unfocused_magnet));
                if (magnet) {
                    item->state=4;
                    item->magnet_speed=player->movement->seek_speed*flt_0_33333334;
                }
            }
        }
        asm_FUN_0043ee30_0043ee30(&item->animation);
        item->timer.TickInline();
        ++manager->live_count;
    }
    if (convert_items) manager->ConvertItems();
    return 1;
}
#pragma code_seg()
