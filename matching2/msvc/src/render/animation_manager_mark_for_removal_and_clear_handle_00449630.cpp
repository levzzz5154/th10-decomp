// 0x00449630: mark the animation a handle names for deferred removal, then
// clear the handle. Native LTCG passes the handle in ESI; the manager rides
// through ECX untouched to SetFlag.
struct AnimationLookupContext;
class AnimationManager {
public:
    void* __fastcall SetFlag(AnimationLookupContext* context, int id);
};

extern "C" AnimationLookupContext* data_00491c10;

struct AnimationHandle_00449630 {
    int id;

    __declspec(noinline) void __fastcall MarkForRemovalAndClear(AnimationManager* manager);
};

#pragma code_seg(".text$01fn")
void __fastcall AnimationHandle_00449630::MarkForRemovalAndClear(AnimationManager* manager) {
    manager->SetFlag(data_00491c10, id);
    id = 0;
}
#pragma code_seg()
