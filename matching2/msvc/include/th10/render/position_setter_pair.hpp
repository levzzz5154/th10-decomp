#ifndef TH10_POSITION_SETTER_PAIR_HPP
#define TH10_POSITION_SETTER_PAIR_HPP
struct PositionVector_004492f0 { float x, y, z; };
struct PositionEntry_004492f0 {
    PositionEntry_004492f0* object;
    PositionEntry_004492f0* next;
    unsigned char reserved_08[0x0C];
    PositionEntry_004492f0* children;
    int children_flagged;
    unsigned char reserved_1c[0x324];
    PositionVector_004492f0 position;
};
struct PositionLookupContext_004492f0 {
    unsigned char reserved[0x72DAD4];
    PositionEntry_004492f0* primary_bucket;
    int reserved_2;
    PositionEntry_004492f0* secondary_bucket;
};
struct PositionScriptId_004492f0 { int value; };
class PositionManager_004492f0 {
public:
    __declspec(noinline) void* __fastcall Find(PositionLookupContext_004492f0* context,
                                             PositionScriptId_004492f0 id);
};
// The context comes first: callers evaluate the position pointer before the
// context load, which is the order retail's 0x00405750 needs.
__declspec(noinline) void __fastcall SetAnimationPosition_004492f0(
    PositionLookupContext_004492f0* context, const PositionVector_004492f0* position,
    PositionScriptId_004492f0 id);
__declspec(noinline) void __fastcall SetAnimationTranslatedPosition_00449350(
    const PositionVector_004492f0* position, PositionLookupContext_004492f0* context,
    PositionScriptId_004492f0 id);
struct AnimationPositionHandle {
    PositionScriptId_004492f0 value;
    __declspec(noinline) void SetPosition(const PositionVector_004492f0* position);
    __declspec(noinline) void SetTranslatedPosition(const PositionVector_004492f0* position);
};
extern "C" PositionLookupContext_004492f0* data_00491c10;
#endif
