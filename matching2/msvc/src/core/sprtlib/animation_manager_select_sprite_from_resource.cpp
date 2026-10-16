// 0x004496A0..0x004496C1: configure the animation object a handle names from
// a resource.  Compiled with the lookup (0x004491C0) and the configure body
// (0x0043E5A0) so both calls keep their native-LTCG entries.  The cluster
// driver includes this file after the two sources that define these types.
extern "C" AnimationLookupContext* g_sprt_ctrl;

struct AnimationHandle14 {
    AnimationScriptId id;

    void ConfigureFromResource(Resource2* resource, int index);
};

#pragma code_seg(".text$50findzz")
__declspec(noinline) void AnimationHandle14::ConfigureFromResource(Resource2* resource, int index) {
    AnimationObject3* object = reinterpret_cast<AnimationObject3*>(
        reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)->Find(g_sprt_ctrl, id));
    if (object != 0)
        resource->ConfigureObject(object, index);
}
#pragma code_seg()
