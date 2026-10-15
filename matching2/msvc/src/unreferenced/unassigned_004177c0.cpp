// Two adjacent animation slots share this setter shape in the retail image.
// The native-LTCG context keeps the ordinary receiver in ECX while the
// compiler reloads the second slot through EAX.
struct AnimationSlot_004177c0 {
    unsigned char reserved_000[4];
    unsigned int flags;
};

struct AnimationSlots_004177c0 {
    unsigned char reserved_000[8];
    AnimationSlot_004177c0* first;
    AnimationSlot_004177c0* second;
    __declspec(noinline) void SetFlags();
};

#pragma code_seg(".text$01setterc0")
void AnimationSlots_004177c0::SetFlags() {
    first->flags |= 2;
    second->flags |= 2;
}
#pragma code_seg()
