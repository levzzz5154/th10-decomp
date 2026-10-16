// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_42a810.cpp"

#pragma code_seg(".text$03context")
int __stdcall StampUserCompilerContext(ReplayHeader3** objects, int count) {
    ReplayHeader3** cursor = objects;
    while (count--) {
        ReplayHeader3* object = *cursor++;
        object->StampUser();
        object->StampUser();
    }
    return 0;
}
#pragma code_seg()
