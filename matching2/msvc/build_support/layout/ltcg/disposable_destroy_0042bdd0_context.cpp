// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_42bdd0.cpp"

#pragma code_seg(".text$03context")
extern "C" int __stdcall DisposableDestroyContext_0042bdd0(Disposable** items, int count) {
    while (count--) {
        Disposable_0042bdd0_Destroy(*items++, 1);
    }
    return 0;
}
#pragma code_seg()
