// Compiler context only; none of these bytes enter the image.
#include "../../src/game/player/trigger_region_004267f0.cpp"

extern "C" int __cdecl TriggerRegionEscape(void* pointer, int value);

#pragma inline_depth(0)
#pragma code_seg(".text$0040a000_context")
extern "C" int __stdcall TriggerRegionContext(Player** fields, Point3_OrientedRect** origins,
                                              float* values, int count) {
    int total = 0;
    for (int index = 0; index < count; ++index) {
        total += TriggerRegionEscape(fields[index], index);
        total += fields[index]->CheckLaserHit(origins[index], values[index], values[index + 1], values[index + 2]);
        total += TriggerRegionEscape(origins[index], total);
    }
    return total;
}
#pragma code_seg()
#pragma inline_depth()
