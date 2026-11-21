// This unselected child calls the same floating resolver as the interpreter.
#include "th10/runtime/script/sptcmd/ecl_core_interpreter.hpp"

__forceinline float EclVm::FloatValue(int selector, EclVm* vm, float value) {
    return vm->FloatOperands().ResolveFloatValue(selector, value);
}

#include "../../../../src/script/sptcmd/ecl_start_child.cpp"
