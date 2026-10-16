extern "C" __declspec(dllimport) void* __stdcall FindWindowA(
        const char*, const char*);

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) int __cdecl asm_unassigned_0044bd00(
        const char* title) {
    return FindWindowA(title, 0) != 0;
}
#pragma code_seg()
