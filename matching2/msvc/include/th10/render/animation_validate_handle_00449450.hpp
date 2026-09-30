#pragma once

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
    __declspec(noinline) void* __fastcall Find(
        AnimationLookupContext* context, AnimationScriptId_00449450 id);
    // Retail passes handle in ESI and returns its looked-up object in EAX.
    __declspec(noinline) void* __cdecl ValidateHandle(AnimationHandle_00449450* handle);
};
