// Full ordinary polar helper bodies are compiler-only context. They emit
// FCOS/FSIN and are not claimed to recover the retail FSINCOS leaf functions.
#include "item_spawn_caller_allocator_2026_09_28.cpp"
#include "../../../src/game/laser/fun_0041f400_0041f400.cpp"
#include "th10/game/line_effect_sweeps_0041e260_0041f400.hpp"
#include "item_spawn_0041bb00_dependencies.cpp"
#include "item_spawn_0041bb00_loader.cpp"
#include "item_spawn_0041bb00_configure.cpp"
#include "item_spawn_0041bb00_create.cpp"
#include <math.h>
#pragma intrinsic(cos,sin)
#pragma code_seg(".text$35itempolar")
__declspec(noinline) ItemPolarVelocity_0041bb00* ItemPolarVelocity_0041bb00::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()
#pragma code_seg(".text$55linepolar")
__declspec(noinline) LinePolarVelocity_0041f800* LinePolarVelocity_0041f800::SetPolar(float angle,float speed) {
    x=static_cast<float>(cos(angle)*speed);
    y=static_cast<float>(sin(angle)*speed);
    return this;
}
#pragma code_seg()

// Publish the complete line polar public member-function address.
// This compiler-only entry exposes its complete ordinary body to consumers
// whose indirect calls use the declared thiscall ABI. The runtime request
// also exposes the allocator general argument contract. It is not game code.
typedef LinePolarVelocity_0041f800* (LinePolarVelocity_0041f800::*LinePolarSetter_0041f800)(float,float);
typedef int (LineEffectSweep_0041e260::*AllSegmentsCompilerMethod_2026_09_28)(int);
#pragma code_seg(".text$99context")
extern "C" int __stdcall PublishPolarCompilerContext_2026_09_28(
        LinePolarSetter_0041f800* line,AllSegmentsCompilerMethod_2026_09_28* all,
        ItemSpawnManager_0041bb00* manager,const float* position,
        int kind,int identifier,float angle,float speed) {
    *line=&LinePolarVelocity_0041f800::SetPolar;
    line[1]=reinterpret_cast<LinePolarSetter_0041f800>(&ItemPolarVelocity_0041bb00::SetPolar);
    *all=&LineEffectSweep_0041e260::CreateAllSegments;
    return manager->Spawn(position,kind,identifier,angle,speed);
}
#pragma code_seg()
