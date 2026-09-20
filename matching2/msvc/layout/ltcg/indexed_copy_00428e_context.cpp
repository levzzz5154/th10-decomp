// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_00428ea0.cpp"

struct IndexedCopySource_00428ec0 {
    unsigned int first;
    unsigned int second;
    __declspec(noinline) void Copy(void* base, int index);
};
struct IndexedCopySource_00428ee0 {
    unsigned int first;
    unsigned int second;
    __declspec(noinline) void Copy(void* base, int index);
};
struct IndexedCopySource_00428f00 {
    unsigned int first;
    unsigned int second;
    __declspec(noinline) void Copy(void* base, int index);
};
#pragma code_seg(".text$09context")
int __stdcall IndexedCopyCompilerContext(
        IndexedCopySource_00428ea0** ea0,
        IndexedCopySource_00428ec0** ec0,
        IndexedCopySource_00428ee0** ee0,
        IndexedCopySource_00428f00** f00,
        void** bases,
        int* indexes,
        int count) {
    int result = 0;
    while (count--) {
        (*ea0)->Copy(*bases, *indexes);
        (*ec0)->Copy(*bases, *indexes);
        (*ee0)->Copy(*bases, *indexes);
        (*f00)->Copy(*bases, *indexes);
        ++ea0;
        ++ec0;
        ++ee0;
        ++f00;
        ++bases;
        ++indexes;
        ++result;
    }
    return result;
}
#pragma code_seg()
