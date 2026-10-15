// 0041BB00: allocate and initialize one dropped item. Native retail arguments
// are manager in EAX, position in ECX, then kind/id/angle/speed on the stack.
#include "types/item_spawn.hpp"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct ItemAnimationResources_0041bb00 {
    unsigned char reserved_000[0x3e0b50];
    void* item_animation;
};
extern "C" {
extern short g_globals_power;
extern float g_game_speed;
extern ItemAnimationResources_0041bb00* g_bullet_manager;
}
struct ItemBankSnapshot {
    ItemAnimationResources_0041bb00* value;
    ItemBankSnapshot(ItemAnimationResources_0041bb00* p):value(p) {}
    ItemBankSnapshot(const ItemBankSnapshot& other):value(other.value) {}
};
#include "th10/render/animation_public_callers.hpp"
__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** output, int script, const Vector3* position);
static __forceinline void ResetSpawnTimer_0041bb00(SpawnItem_0041bb00* item) {
    item->motion_state=0;
    _ReadWriteBarrier();
    unsigned int flags=item->timer.flags;
    if (!(flags&1u)) {
        flags|=1u;
        item->timer.current=0;
        item->timer.previous=-999999;
        item->timer.elapsed=0.0f;
        item->timer.speed=&g_game_speed;
        item->timer.flags=flags;
    }
    item->timer.current=0;
    item->timer.elapsed=0.0f;
    item->timer.previous=-1;
    item->motion_counter=0;
    _ReadWriteBarrier();
}
#pragma code_seg(".text$30spawn")
__declspec(noinline) int ItemSpawnManager_0041bb00::Spawn(
        const Vector3* position,int kind,int identifier,float angle,float speed) {
    // Ordinary drops scan the first 150 entries. A full pool silently drops
    // the request, and every exit returns zero.
    if (kind != 8) {
        SpawnItem_0041bb00* item=normal;
        int slot=0;
        do {
            if (item->state==0) goto found;
            ++slot;
            ++item;
        } while (slot<150);
        return 0;
    found:
        item->state=1;
        Vector3* location=&item->position;
        *location=*position;
        if (location->x<=-192.0f) location->x=-192.0f;
        else if (location->x>=192.0f) location->x=192.0f;
        item->velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
        if (g_globals_power>=100) {
            switch(kind) {
            case 10: case 11: kind=5; break;
            case 1: case 4: kind=9; break;
            }
        }
        if (item->kind==3) {
            void* retired_handle;
            ItemAnimation_CreateOffset_00448db0(g_bullet_manager->item_animation,
                &retired_handle,393,location);
        }
        item->kind=kind;
        item->display_kind=kind;
        if (kind==10) {
            item->display_kind=1;
            Entity_StartScript_00404f30(static_cast<AnimationResource_0043e710*>(g_bullet_manager->item_animation), &item->animation,375);
            item->animation.primary_color=identifier;
            return 0;
        }
        ItemBankSnapshot bank=g_bullet_manager;
        int script;
        if (kind==11) { item->display_kind=4; script=378; }
        else script=kind+374;
        Entity_StartScript_00404f30(static_cast<AnimationResource_0043e710*>(bank.value->item_animation), &item->animation,script);
        item->animation.primary_color=identifier;
        return 0;
    }
    // Kind 8 uses a 2048-entry ring; its count rises even when this ring slot
    // is occupied. Signed remainders preserve retail's cursor arithmetic.
    int cursor=special_cursor;
    SpawnItem_0041bb00* item=&special[cursor];
    int count=++special_count;
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
        item->position=*position;
        item->velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
    }
    special_cursor=(special_cursor+1)%2048;
    return 0;
}
#pragma code_seg()
