#pragma once

struct AnimationLookupContext;
struct AnimationScriptId2 {
    int value;
};
struct AnimationHandle10 {
    unsigned int value;
};
extern "C" AnimationLookupContext* g_sprt_ctrl;

class AnimationManager15 {
public:
    __declspec(noinline) void* __fastcall Find(
        AnimationLookupContext* context, AnimationScriptId2 id);
    // Retail passes handle in ESI and returns its looked-up object in EAX.
    __declspec(noinline) void* __cdecl ValidateHandle(AnimationHandle10* handle);
};
