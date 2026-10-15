// Public destructor root preserves the genuine ECX cleanup ABI while normal
// stack destruction remains inline. The root is an entire actual lifetime body.
#pragma comment(linker, "/include:??1ResourceSizeFile@@QAE@XZ")
#include "../../../src/pack/file/resource_get_file_size_retail_004358e0.cpp"
#include "../../../src/pack/arcmngr/dat_archive_find_size_00434ef0.cpp"
#pragma code_seg(".text$11context")
extern "C" __declspec(noinline) unsigned int __stdcall ResourceSizeContext(const char** paths,
                                                                           int count) {
    unsigned int result = 0;
    for (int i = 0; i < count; ++i)
        result += ResourceGetFileSize(paths[i]);
    return result;
}
#pragma code_seg()
