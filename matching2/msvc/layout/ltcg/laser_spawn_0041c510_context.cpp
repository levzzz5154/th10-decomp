// Compiler context only; never selected as recovered game code.
#include "th10/game/laser_spawn_0041c510.hpp"
#include "laser_spawn_0041c510_anchors.cpp"
#include "../../src/game/laser/laser_spawn_0041c510.cpp"

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall LaserSpawnContext(const int* kinds, const float* angles, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        struct { float values[16]; } parameters;
        parameters.values[0] = angles[index];
        total += reinterpret_cast<LaserSpawnParameters_0041c510*>(&parameters)->SpawnIn(g_laser_manager, kinds[index]);
        total += reinterpret_cast<LaserSpawnParameters_0041c510*>(&parameters)->SpawnIn(g_laser_manager, 1);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
