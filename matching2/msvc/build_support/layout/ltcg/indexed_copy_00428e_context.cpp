// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428ea0.cpp"

struct IndexedCopySource2 {
    unsigned int first;
    unsigned int second;
    __declspec(noinline) void Copy(void* base, int index);
};
struct IndexedCopySource3 {
    unsigned int first;
    unsigned int second;
    __declspec(noinline) void Copy(void* base, int index);
};
struct IndexedCopySource4 {
    unsigned int first;
    unsigned int second;
    __declspec(noinline) void Copy(void* base, int index);
};
#pragma code_seg(".text$09context")
int __stdcall IndexedCopyCompilerContext(
        IndexedCopySource** ea0,
        IndexedCopySource2** ec0,
        IndexedCopySource3** ee0,
        IndexedCopySource4** f00,
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
