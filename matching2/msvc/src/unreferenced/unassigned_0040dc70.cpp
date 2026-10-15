
extern "C" int __stdcall target_0040dc80(void* object);

struct Sub_0040dc70 { unsigned char bytes[0x100]; };

struct Outer_0040dc70 {
    unsigned char pad_000[0x103C];
    Sub_0040dc70 sub;
    __declspec(noinline) int Run();
};

#pragma code_seg(".text$01run")
int Outer_0040dc70::Run() {
    return target_0040dc80(&this->sub);
}
#pragma code_seg()
