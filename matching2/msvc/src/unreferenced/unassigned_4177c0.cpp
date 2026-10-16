// Two adjacent animation slots share this setter shape in the retail image.
// The native-LTCG context keeps the ordinary receiver in ECX while the
// compiler reloads the second slot through EAX.
struct AnimationSlot3 {
    unsigned char reserved_000[4];
    unsigned int flags;
};

struct AnimationSlots3 {
    unsigned char reserved_000[8];
    AnimationSlot3* first;
    AnimationSlot3* second;
    __declspec(noinline) void SetFlags();
};

#pragma code_seg(".text$01setterc0")
void AnimationSlots3::SetFlags() {
    first->flags |= 2;
    second->flags |= 2;
}
#pragma code_seg()
