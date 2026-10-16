// 0x00449630: mark the animation a handle names for deferred removal, then
// clear the handle. Native LTCG passes the handle in ESI; the manager rides
// through ECX untouched to SetFlag.
struct AnimationLookupContext;
class SprtCtrl {
public:
    void* __fastcall SetFlag(AnimationLookupContext* context, int id);
};

extern "C" AnimationLookupContext* g_sprt_ctrl;

struct AnimationHandle13 {
    int id;

    __declspec(noinline) void __fastcall MarkForRemovalAndClear(SprtCtrl* manager);
};

#pragma code_seg(".text$01fn")
void __fastcall AnimationHandle13::MarkForRemovalAndClear(SprtCtrl* manager) {
    manager->SetFlag(g_sprt_ctrl, id);
    id = 0;
}
#pragma code_seg()
