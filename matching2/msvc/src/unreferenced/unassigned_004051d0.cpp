
extern "C" int __stdcall target_0043ee30(void* object);

__declspec(noinline) int RetireBlock(void* object);

#pragma code_seg(".text$01retire")
__declspec(noinline) int RetireBlock(void* object) {
    return target_0043ee30(object);
}
#pragma code_seg()
