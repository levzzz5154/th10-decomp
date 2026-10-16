// Compiler context only; its bytes are not recovered game code.
#include "../../../src/core/main/destroy_entity_list.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Holder2** h, int n) {
    for (int i = 0; i < n; ++i) ReleaseAll(h[i]);
    return 0;
}
#pragma code_seg()
