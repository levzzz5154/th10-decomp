// Compiler context only; never selected as recovered game code.
#include "../../../src/core/zunlib/text_log_append_line.cpp"

#pragma code_seg(".text$03context")
int __stdcall TextLogLineCompilerContext(TextLog5** logs, int count, int value, const char* name) {
    for (int index = 0; index < count; ++index)
        logs[index]->AppendLine("%d %s", value, name);
    return 0;
}
#pragma code_seg()
