// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/FUN.cpp_4051b0.cpp"

#pragma code_seg(".text$03context")
int __stdcall f4051b0CompilerContext(GameRuntimeState** states, int count, char value) {
    for (int index = 0; index < count; ++index)
        states[index]->SetEnabled(value);
    return 0;
}
#pragma code_seg()
