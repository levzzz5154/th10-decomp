
extern "C" int __stdcall target3(void* object);

__declspec(noinline) int RetireBlock(void* object);

#pragma code_seg(".text$01retire")
__declspec(noinline) int RetireBlock(void* object) {
    return target3(object);
}
#pragma code_seg()
