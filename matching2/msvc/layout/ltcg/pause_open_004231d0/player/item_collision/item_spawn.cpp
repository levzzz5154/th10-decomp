#include "th10/game/pause_result_open_004231d0/player/item_collision/item_collision.hpp"
extern "C" short data_00474c48;

static __forceinline void ResetSpawnTimer_0041bb00(SpawnItem_0041bb00* item) {
    item->motion_state=0;
    unsigned int flags=item->timer_flags;
    if (!(flags&1u)) {
        flags|=1u;
        item->timer_current=0;
        item->timer_previous=-999999;
        item->timer_elapsed=0.0f;
        item->timer_speed=&data_00476f78;
        item->timer_flags=flags;
    }
    item->timer_current=0;
    item->timer_elapsed=0.0f;
    item->timer_previous=-1;
    item->motion_counter=0;
}
#pragma code_seg(".text$0041bb00_fn")
__declspec(noinline) int ItemSpawnManager_0041bb00::Spawn(
        const float* position,int kind,int identifier,float angle,float speed) {
    ItemSpawnManager_0041bb00* manager=this;
    // Ordinary drops scan the first 150 entries. A full pool silently drops
    // the request, and every exit returns zero.
    if (kind != 8) {
        SpawnItem_0041bb00* item=manager->normal;
        int slot=0;
        while (item->state!=0) {
            ++slot;
            ++item;
            if (slot>=150) return 0;
        }
        item->state=1;
        float* location=item->position;
        location[0]=position[0];
        location[1]=position[1];
        location[2]=position[2];
        if (location[0]<=-192.0f) location[0]=-192.0f;
        else if (location[0]>=192.0f) location[0]=192.0f;
        item->velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
        int mapped_kind=kind;
        if (data_00474c48>=100) {
            switch(mapped_kind) {
            case 1: case 4: mapped_kind=9; break;
            case 10: case 11: mapped_kind=5; break;
            }
        }
        if (item->kind==3) {
            ItemAnimation_CreateOffset_00448db0(data_004776f0->item_animation,
                393,
                reinterpret_cast<const Vector3*>(location));
        }
        item->kind=mapped_kind;
        item->display_kind=mapped_kind;
        if (mapped_kind==10) {
            item->display_kind=1;
            ConfigureResource_00404f30 resource={static_cast<AnimationResource_00449870*>(data_004776f0->item_animation)};
            reinterpret_cast<ItemConfiguredEntity_00404f30*>(item)->Configure(375,resource);
            item->identifier=identifier;
            return 0;
        }
        int script;
        if (mapped_kind==11) { item->display_kind=4; script=378; }
        else script=mapped_kind+374;
        ConfigureResource_00404f30 resource={static_cast<AnimationResource_00449870*>(data_004776f0->item_animation)};
        reinterpret_cast<ItemConfiguredEntity_00404f30*>(item)->Configure(script,resource);
        item->identifier=identifier;
        return 0;
    }
    // Kind 8 uses a 2048-entry ring; its count rises even when this ring slot
    // is occupied. Signed remainders preserve retail's cursor arithmetic.
    int cursor=manager->special_cursor;
    SpawnItem_0041bb00* item=&manager->special[cursor];
    int count=++manager->special_count;
    if (item->state==0) {
        int variant;
        if (count>=1024) variant=cursor%32+16;
        else if (count>=512) variant=cursor%16+8;
        else if (count>=256) variant=cursor%8+4;
        else variant=cursor%4;
        item->variant=variant;
        item->kind=8;
        item->display_kind=8;
        item->state=5;
        item->position[0]=position[0];
        item->position[1]=position[1];
        item->position[2]=position[2];
        item->velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
    }
    manager->special_cursor=(manager->special_cursor+1)%2048;
    return 0;
}
#pragma code_seg()
