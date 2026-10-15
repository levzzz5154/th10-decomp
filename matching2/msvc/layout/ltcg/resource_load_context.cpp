#pragma comment(linker, "/include:?Open@BufferFile@@UAEEPBD0@Z")
#pragma comment(linker, "/include:??1FileHandleOwner@@QAE@XZ")
#include "resource_load_lifetime.cpp"
#include "../../src/pack/resfile/resource_load_00435800.cpp"
#include "resource_load_buffer_caller.cpp"
#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) BYTE __stdcall ResourceLoadContext(BufferFile* file, const char* path) { return file->BufferFile::Open(path, 0); }
#pragma code_seg()
