// Compiler context only; never selected as recovered game code.
#include "../../src/game/recovery_append_node_0041ab10.cpp"

#pragma code_seg(".text$03context")
int __stdcall RecoveryAppendCompilerContext(RecoveryNode_0041ab10** heads,
                                            RecoveryNode_0041ab10** nodes,
                                            int count) {
    while (count--) {
        (*heads++)->Append(*nodes++);
    }
    return 0;
}
#pragma code_seg()
