// Compiler context only; never selected as recovered game code.
#include "../../src/platform/text_log_write_to_file_00438950.cpp"
#include "../../src/platform/file_write_whole_file_0044b540.cpp"
#include "../../src/platform/text_log.cpp"

#pragma code_seg(".text$90context")
int __stdcall TextLogWriteContext_00438950(TextLog_0044b810** logs, int count) {
    while (count--)
        (*logs++)->WriteToFile();
    return 0;
}
#pragma code_seg()
