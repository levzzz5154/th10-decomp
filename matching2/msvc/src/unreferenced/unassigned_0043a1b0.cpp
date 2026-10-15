// 0x0043A1B0..0x0043A1B7: hand the window to the foreground.
extern "C" __declspec(dllimport) int __stdcall SetForegroundWindow(void* window);
struct Object_0043a1b0 {
    __declspec(noinline) void Activate();
};

#pragma code_seg(".text$01accessor")
void Object_0043a1b0::Activate() {
    SetForegroundWindow((void*)this);
}

#pragma code_seg()
