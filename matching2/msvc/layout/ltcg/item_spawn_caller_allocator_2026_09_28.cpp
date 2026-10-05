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
#include "th10/render/animation_public_callers.hpp"
struct ConfigureResource_00404f30 { void* value; };
#define TH10_CONFIGURE_00404F30_ARGUMENT_DEFINED
struct ItemConfiguredEntity_00404f30 : Entity {
    __declspec(noinline) void Configure(int index,ConfigureResource_00404f30 resource);
};
__declspec(noinline) void** __stdcall ItemAnimation_CreateOffset_00448db0(
    void* resource, void** output, int script, const Vector3* position);
static __forceinline void ResetSpawnTimer_0041bb00(SpawnItem_0041bb00* item) {
    item->motion_state=0;
    _ReadWriteBarrier();
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
    _ReadWriteBarrier();
}
#pragma code_seg(".text$30spawn")
struct ItemVector_0041bb00 {
    float x,y,z;
};
__declspec(noinline) int ItemSpawnManager_0041bb00::Spawn(
        const float* position,int kind,int identifier,float angle,float speed) {
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
        ItemVector_0041bb00* location=reinterpret_cast<ItemVector_0041bb00*>(item->position);
        *location=*reinterpret_cast<const ItemVector_0041bb00*>(position);
        if (location->x<=-192.0f) location->x=-192.0f;
        else if (location->x>=192.0f) location->x=192.0f;
        item->velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
        if (data_00474c48>=100) {
            switch(kind) {
            case 10: case 11: kind=5; break;
            case 1: case 4: kind=9; break;
            }
        }
        if (item->kind==3)
            ItemAnimation_CreateOffset_00448db0(data_004776f0->item_animation,
                reinterpret_cast<void**>(&speed),393,
                reinterpret_cast<const Vector3*>(location));
        item->kind=kind;
        item->display_kind=kind;
        if (kind==10) {
            item->display_kind=1;
            ConfigureResource_00404f30 resource={data_004776f0->item_animation};
            reinterpret_cast<ItemConfiguredEntity_00404f30*>(item)->Configure(375,resource);
            item->identifier=identifier;
            return 0;
        }
        int script;
        if (kind==11) { item->display_kind=4; script=378; }
        else script=kind+374;
        reinterpret_cast<ItemConfiguredEntity_00404f30*>(item)->Configure(script,
            *reinterpret_cast<ConfigureResource_00404f30*>(&data_004776f0->item_animation));
        item->identifier=identifier;
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
        *reinterpret_cast<ItemVector_0041bb00*>(item->position)=*reinterpret_cast<const ItemVector_0041bb00*>(position);
        item->velocity.SetPolar(angle,speed);
        ResetSpawnTimer_0041bb00(item);
    }
    special_cursor=(special_cursor+1)%2048;
    return 0;
}
#pragma code_seg()
