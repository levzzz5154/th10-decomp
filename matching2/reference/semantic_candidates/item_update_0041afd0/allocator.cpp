// 0041BB00: allocate and initialize one dropped item. Native retail arguments
// are manager in EAX, position in ECX, then kind/id/angle/speed on the stack.
#include "th10/game/item_spawn_0041bb00.hpp"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
struct ItemAnimationResources_0041bb00 {
    unsigned char reserved_000[0x3e0b50];
    void* item_animation;
};
extern "C" {
extern short data_00474c48;
extern float data_00476f78;
extern ItemAnimationResources_0041bb00* data_004776f0;
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
    item->motion.velocity.z=0.0f;
    _ReadWriteBarrier();
    unsigned int flags=item->motion.timer.flags;
    if (!(flags&1u)) {
        flags|=1u;
        item->motion.timer.current=0;
        item->motion.timer.previous=-999999;
        item->motion.timer.elapsed=0.0f;
        item->motion.timer.speed=&data_00476f78;
        item->motion.timer.flags=flags;
    }
    item->motion.timer.current=0;
    item->motion.timer.elapsed=0.0f;
    item->motion.timer.previous=-1;
    item->motion.motion_counter=0;
    _ReadWriteBarrier();
}
#pragma code_seg(".text$30spawn")
__declspec(noinline) int ItemSpawnManager_0041bb00::Spawn(
        const Vector3* position,int kind,int identifier,float angle,float speed) {
    // Ordinary drops scan the first 150 entries. A full pool silently drops
    // the request, and every exit returns zero.
    if (kind != 8) {
        SpawnItem_0041bb00* item=items;
        int slot=0;
        do {
            if (item->motion.state==0) goto found;
            ++slot;
            ++item;
        } while (slot<150);
        return 0;
    found:
        item->motion.state=1;
        Vector3* location=&item->motion.position;
        *location=*position;
        if (location->x<=-192.0f) location->x=-192.0f;
        else if (location->x>=192.0f) location->x=192.0f;
        item->motion.velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
        if (data_00474c48>=100) {
            switch(kind) {
            case 10: case 11: kind=5; break;
            case 1: case 4: kind=9; break;
            }
        }
        if (item->motion.kind==3) {
            void* retired_handle;
            ItemAnimation_CreateOffset_00448db0(data_004776f0->item_animation,
                &retired_handle,393,location);
        }
        item->motion.kind=kind;
        item->motion.display_kind=kind;
        if (kind==10) {
            item->motion.display_kind=1;
            Entity_StartScript_00404f30(static_cast<AnimationResource_0043e710*>(data_004776f0->item_animation), &item->animation,375);
            item->animation.primary_color=identifier;
            return 0;
        }
        ItemBankSnapshot bank=data_004776f0;
        int script;
        if (kind==11) { item->motion.display_kind=4; script=378; }
        else script=kind+374;
        Entity_StartScript_00404f30(static_cast<AnimationResource_0043e710*>(bank.value->item_animation), &item->animation,script);
        item->animation.primary_color=identifier;
        return 0;
    }
    // Kind 8 uses a 2048-entry ring; its count rises even when this ring slot
    // is occupied. Signed remainders preserve retail's cursor arithmetic.
    int cursor=special_cursor;
    SpawnItem_0041bb00* item=&items[150+cursor];
    int count=++special_count;
    if (item->motion.state==0) {
        int variant;
        if (count>=1024) variant=cursor%32+16;
        else if (count>=512) variant=cursor%16+8;
        else if (count>=256) variant=cursor%8+4;
        else variant=cursor%4;
        item->motion.variant=variant;
        item->motion.kind=8;
        item->motion.display_kind=8;
        item->motion.state=5;
        item->motion.position=*position;
        item->motion.velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
    }
    special_cursor=(special_cursor+1)%2048;
    return 0;
}
#pragma code_seg()
