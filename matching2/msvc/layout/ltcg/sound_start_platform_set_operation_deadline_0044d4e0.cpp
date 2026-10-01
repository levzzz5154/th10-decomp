// 0x0044D4E0 - Set the first DirectSound buffer's volume using the global
// volume curve, or -10000 for the zero setting. Historical names are retained.
#include "th10/platform/sound_fade_0044d4e0.hpp"

#pragma code_seg(".text$11volume")
__declspec(noinline) int
PlatformInterfaceState_0044D4E0::SetOperationDeadline(int deadline) {
    if (data_00497854 != 0) {
        float factor = 1.0f - (float)data_00497854 * 0.01f;
        int value = (int)((1.0f - factor * factor) * (deadline + 5000));
        return entries_004[0]->set_deadline(value - 5000);
    }
    return entries_004[0]->set_deadline(-10000);
}
#pragma code_seg()
