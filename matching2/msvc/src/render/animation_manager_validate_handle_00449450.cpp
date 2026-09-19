// 0x00449450..0x00449464: clear a stale animation handle.
struct AnimationLookupContext;
struct AnimationScriptId_00449450 {
    int value;
};
struct AnimationHandle_00449450 {
    unsigned int value;
};
extern "C" AnimationLookupContext* data_00491c10;

class AnimationManager_00449450 {
public:
    void* __fastcall Find(AnimationLookupContext* context, AnimationScriptId_00449450 id);
    __declspec(noinline) void ValidateHandle(AnimationHandle_00449450* handle);
};

#pragma code_seg(".text$01validate")
void AnimationManager_00449450::ValidateHandle(AnimationHandle_00449450* handle) {
    AnimationScriptId_00449450 id = { (int)handle->value };
    if (Find(data_00491c10, id) == 0)
        handle->value = 0;
}
#pragma code_seg()
