// 0x004200D0: callback installed at 0x00420512; flushes the pending animation
// batch and zeroes the two floats at 0x00491E64/0x00491E68.  Compiled in the
// anm_batch_flush native-LTCG cluster so Flush receives the manager in ESI.
#include "th10/render/quad_batch.hpp"

extern "C" float data_00491e64;
extern "C" float data_00491e68;

struct FlushCallback_004200d0 {
    __declspec(noinline) int Run();
};

#pragma code_seg(".text$001z3gapb")
int FlushCallback_004200d0::Run() {
    data_00491c10->Flush();
    data_00491e64 = 0.0f;
    data_00491e68 = 0.0f;
    return 1;
}
#pragma code_seg()
