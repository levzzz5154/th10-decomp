// 0x0042C7E0..0x0042C7F9: test whether an indexed animation slot resolves.
// Native LTCG places the table in EAX and the slot index in ECX, then keeps
// SprtCtrl::Find's private EDX/context plus stack-id call setup.
struct AnimationTable_0042c7e0 {
    unsigned char reserved_000[0x2C4];
    void* slots[1];
};

struct AnimationLookupContext;
struct AnimationScriptId {
    int value;
};

class SprtCtrl {
public:
    void* __fastcall Find(AnimationLookupContext* context,
                           AnimationScriptId id);
};
extern "C" AnimationLookupContext* g_sprt_ctrl;
#pragma code_seg(".text$05has")
// Reverse the source-only formal order to make MSVC encode the commutative
// table-plus-index address with table in EAX and index in ECX, as retail.
extern "C" __declspec(noinline) int AnimationTable_HasSlot_0042c7e0(
        int index, AnimationTable_0042c7e0* table) {
    return reinterpret_cast<SprtCtrl*>(g_sprt_ctrl)
               ->Find(g_sprt_ctrl,
                      *reinterpret_cast<AnimationScriptId*>(
                          (unsigned char*)table + 0x2C4 + index * 4)) != 0;
}
#pragma code_seg()
