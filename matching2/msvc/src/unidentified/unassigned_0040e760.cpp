
struct Inner_0040e760 {
    unsigned char bytes[0x100];
    __declspec(noinline) void Run();
};

struct Outer_0040e760 {
    unsigned char pad_000[0x103C];
    Inner_0040e760 inner;
    __declspec(noinline) void Run();
};

#pragma code_seg(".text$01run")
void Outer_0040e760::Run() {
    inner.Run();
}
#pragma code_seg()
