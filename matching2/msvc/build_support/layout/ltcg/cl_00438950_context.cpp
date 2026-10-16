// Compiler context only; never selected as recovered game code.
#include "../../../src/core/main/text_log_write_to_file.cpp"
#include "../../../src/core/zunlib/file_write_whole_file.cpp"
#include "../../../src/core/zunlib/text_log.cpp"

#pragma code_seg(".text$90context")
int __stdcall TextLogWriteContext_00438950(TextLog4** logs, int count) {
    while (count--)
        (*logs++)->WriteToFile();
    return 0;
}
#pragma code_seg()
