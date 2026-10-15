#include "../../../src/pack/file/file_handle_open_00435370.cpp"
#pragma code_seg(".text$05context")
extern "C" __declspec(noinline) BYTE __stdcall FileOpenContext(FileHandle* file, const char* path,
                                                               const char* mode) {
    return file->FileHandle::Open(path, mode);
}
#pragma code_seg()
