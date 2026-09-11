// Compiler context only; never selected as recovered game code.
#include "../../src/platform/file_write_whole_file_0044b540.cpp"

#pragma code_seg(".text$03context")
int __stdcall FileWriteWholeFileCompilerContext(const char* path, const void* buffer,
                                                const unsigned long* sizes, int count) {
    int last = 0;
    for (int index = 0; index < count; ++index)
        last = File_WriteWholeFile(path, buffer, sizes[index]);
    return last;
}
#pragma code_seg()
