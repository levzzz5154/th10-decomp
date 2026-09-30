
#include "../../src/render/animation_manager_register_resource_0043e460.cpp"

int __stdcall Music_Load(int slot, const char* file_name);
int __stdcall Music_Stop();
int __stdcall Music_FadeOut(float frames);

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __stdcall RegistrarContext_0043e460(
        AnimationManager_0043e460** managers, int count, const char* name, int resource, int parameter) {
    int total = 0;
    // The music requests are reached only through their addresses here.
    *(int (__stdcall**)(int, const char*))managers[count] = Music_Load;
    *(int (__stdcall**)())managers[count + 1] = Music_Stop;
    *(int (__stdcall**)(float))managers[count + 2] = Music_FadeOut;
    while (count--)
        total += (int)(*managers++)->RegisterResource(name, resource, parameter);
    return total;
}
#pragma code_seg()
