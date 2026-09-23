#include "th10/platform/archive_file.hpp"

// Semantic model of the 0x0043D640 retail routine. Its private entry ABI has
// the filename in EAX, then the owner and slot index on the stack. The C++
// signature below names all three inputs explicitly; it does not encode that
// register/stack split or the retail RET 8.
extern "C" __declspec(noinline) int __cdecl asm_unassigned_0043d640(
        const char* file_name, void* owner, int slot_index) {
    char* data = Archive_LoadFile(file_name, 0, 0);

    char** slot = (char**)((char*)owner + 0x5230 + slot_index * 4);
    *slot = data;
    return data ? 0 : -1;
}
