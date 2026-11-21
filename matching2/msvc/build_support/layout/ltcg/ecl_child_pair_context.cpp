// Link the real operand resolvers and both call shapes so LTCG derives the
// retail private register conventions. Both Start and SpawnChild are selected.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"

#pragma code_seg(".text$03intvalue")
#include "../../../src/script/sptcmd/ecl_int_value.cpp"
#pragma code_seg(".text$05value")
#include "../../../src/script/sptcmd/ecl_float_value.cpp"
#pragma code_seg()

#include "../../../src/script/sptcmd/ecl_start_child.cpp"

#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) int __stdcall EclChildPairContext(EclVm** sources, int id, int index, int count) {
    int result = 0;
    while (count--) {
        EclVm* source = *sources++;
        result += source->owner->SpawnChild(id, index);
        result += source->Start(source, index);
    }
    return result;
}
#pragma code_seg()
#include "ecl_child_script_anchor.cpp"
