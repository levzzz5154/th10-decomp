#ifndef TH10_POSITION_SETTER_PAIR_HPP
#define TH10_POSITION_SETTER_PAIR_HPP
struct PositionVector { float x, y, z; };
struct PositionEntry {
    PositionEntry* object;
    PositionEntry* next;
    unsigned char reserved_08[0x0C];
    PositionEntry* children;
    int children_flagged;
    unsigned char reserved_1c[0x324];
    PositionVector position;
};
struct PositionLookupContext {
    unsigned char reserved[0x72DAD4];
    PositionEntry* primary_bucket;
    int reserved_2;
    PositionEntry* secondary_bucket;
};
struct PositionScriptId { int value; };
class PositionManager {
public:
    __declspec(noinline) void* __fastcall Find(PositionLookupContext* context,
                                             PositionScriptId id);
};
// The context comes first: callers evaluate the position pointer before the
// context load, which is the order retail's 0x00405750 needs.
__declspec(noinline) void __fastcall SetAnimationPosition2(
    PositionLookupContext* context, const PositionVector* position,
    PositionScriptId id);
__declspec(noinline) void __fastcall SetAnimationTranslatedPosition(
    const PositionVector* position, PositionLookupContext* context,
    PositionScriptId id);
struct AnimationPositionHandle {
    PositionScriptId value;
    __declspec(noinline) void SetPosition(const PositionVector* position);
    __declspec(noinline) void SetTranslatedPosition(const PositionVector* position);
};
extern "C" PositionLookupContext* g_sprt_ctrl;
#endif
