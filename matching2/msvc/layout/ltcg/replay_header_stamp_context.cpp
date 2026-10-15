// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/FUN_0042a810_0042a810.cpp"

#pragma code_seg(".text$03context")
int __stdcall StampUserCompilerContext(ReplayHeader_0042a810** objects, int count) {
    ReplayHeader_0042a810** cursor = objects;
    while (count--) {
        ReplayHeader_0042a810* object = *cursor++;
        object->StampUser();
        object->StampUser();
    }
    return 0;
}
#pragma code_seg()
