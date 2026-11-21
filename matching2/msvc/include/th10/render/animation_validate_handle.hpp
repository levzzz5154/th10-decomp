#pragma once

struct AnimationLookupContext;
struct AnimationScriptId2 {
    int value;
};
struct ValidatedAnmHandle {
    unsigned int value;
};
extern "C" AnimationLookupContext* g_sprt_ctrl;

class ResultAnmManagerView {
public:
    __declspec(noinline) void* __fastcall Find(
        AnimationLookupContext* context, AnimationScriptId2 id);
    // Retail passes handle in ESI and returns its looked-up object in EAX.
    __declspec(noinline) void* __cdecl ValidateHandle(ValidatedAnmHandle* handle);
};
