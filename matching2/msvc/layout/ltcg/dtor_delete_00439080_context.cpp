// Compiler context and ABI anchor only; no anchor bytes enter the image.
#include "../../src/unreferenced/unassigned_00439080.cpp"
extern "C" unsigned int cleanup_vtable_0046f80c;
struct AnchorSound_00439080 { unsigned int vtable; };
// The real cleanup first restores its derived vtable through the EAX receiver.
#pragma code_seg(".text$03anchor")
extern "C" __declspec(noinline) void __cdecl asm_FUN_0043a910_0043a910(void* object) {
    ((AnchorSound_00439080*)object)->vtable = (unsigned int)&cleanup_vtable_0046f80c;
}
#pragma code_seg()
#pragma code_seg(".text$05context")
extern "C" int __stdcall DtorDeleteContext_00439080(Deletable_00439080** items, int count) {
    int freed = 0;
    while (count--) {
        freed += Deletable_00439080_Delete(*items++, 1) != 0;
    }
    return freed;
}
#pragma code_seg()
