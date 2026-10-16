// 0x00449670..0x00449693: select the sprite of the object's current resource.
// The object arrives in EAX, a convention only a native LTCG link chooses, so
// this region is compiled as a cluster.
extern "C" void* g_sprt_ctrl;

struct Resource3;

struct Node6 {
    unsigned char pad_000[0x308];
    void* field_308;                 // +0x308
};

struct Object36 {
    void* field_000;                 // +0x000
    __declspec(noinline) void SelectSpriteFromCurrentResource(Resource3* resource);
};

extern "C" Node6* __fastcall AnimationManager_Find(
    void* value, void* manager, int unused);
extern "C" void __fastcall AnimationObject_ConfigureFromResource(
    void* target, void* resource);

#pragma code_seg(".text$01accessor")
void Object36::SelectSpriteFromCurrentResource(Resource3* resource) {
    Node6* node = AnimationManager_Find(field_000, g_sprt_ctrl, (int)field_000);
    if (node != 0) {
        AnimationObject_ConfigureFromResource(node->field_308, resource);
    }
}
#pragma code_seg()
