// 0x004200D0: the app's draw task at priority 0x32 (registered by
// 0x00420470); flushes the pending animation
// batch and zeroes the two floats at 0x00491E64/0x00491E68.  Compiled in the
// anm_batch_flush native-LTCG cluster so Flush receives the manager in ESI.
#include "th10/render/quad_batch.hpp"

extern "C" float data_00491e64;
extern "C" float data_00491e68;

struct AppDrawFlush {
    __declspec(noinline) int Run();
};

#pragma code_seg(".text$001z3gapb")
int AppDrawFlush::Run() {
    data_00491c10->Flush();
    data_00491e64 = 0.0f;
    data_00491e68 = 0.0f;
    return 1;
}
#pragma code_seg()
