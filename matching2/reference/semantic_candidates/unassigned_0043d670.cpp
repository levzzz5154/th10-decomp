#include "th10/platform/archive_file.hpp"

// Semantic model of the 0x0043D670 retail routine. Its private entry ABI has
// the filename in EAX and the owner as one stack argument. This ordinary C++
// signature names both inputs explicitly; it does not encode that register /
// stack split or the retail RET 4.
extern "C" __declspec(noinline) int __cdecl asm_unassigned_0043d670(
        const char* file_name, void* owner) {
    char* data = Archive_LoadFile(file_name, 0, 0);

    *(char**)((char*)owner + 0x1F84) = data;
    return data ? 0 : -1;
}
