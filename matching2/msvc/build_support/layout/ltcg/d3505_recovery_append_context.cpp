// Compiler context only; never selected as recovered game code.
#include "../../../src/game/item/recovery_append_node_0041ab10.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryAppendCompilerContext(RecoveryNode** heads,
                                            RecoveryNode** nodes,
                                            int count) {
    while (count--) {
        (*heads++)->Append(*nodes++);
    }
    return 0;
}
#pragma code_seg()
