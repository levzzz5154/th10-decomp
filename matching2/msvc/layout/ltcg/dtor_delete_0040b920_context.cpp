// Compiler context only; none of these bytes enter the image.
#include "../../src/unreferenced/unassigned_0040b920.cpp"
#include "../../src/platform/platform_stop_worker_0044c150.cpp"

#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_0040b920(BulletAnimOwner** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_0040b920_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
