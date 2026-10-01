// Compiler context only. The dispatcher stand-in below establishes its
// EAX interpreter / stack delta / RET4 contract. Its body is synthetic and is
// never selected as recovered game code; the real 7020-byte dispatcher at
// 0x0044E1A0 remains separately owned by ecl_core_interpreter.cpp.
#include "../../src/script/ecl_vm_children.cpp"

struct EclDispatcherAbiView {
    float time;
    int status;
};

#pragma code_seg(".text$01execution")
extern "C" __declspec(noinline) int __stdcall
EclVm_RunInterpreter(EclChildState* state, float delta) {
    EclDispatcherAbiView* view = reinterpret_cast<EclDispatcherAbiView*>(state);
    view->time += delta;
    return view->status;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) int __stdcall
EclChildrenContext(EclChildOwner** items, int count, float delta) {
    int result = 0;
    while (count--) result += EclVm_TickChildren(*items++, delta);
    return result;
}
#pragma code_seg()
