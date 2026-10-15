// Compiler context only; its bytes are not recovered game code.
#include "../../src/core/main/destroy_entity_list_00438a30.cpp"

#pragma code_seg(".text$03context")
int __stdcall Ctx(Holder_00438a30** h, int n) {
    for (int i = 0; i < n; ++i) ReleaseAll_00438a30(h[i]);
    return 0;
}
#pragma code_seg()
