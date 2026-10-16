
extern "C" int __stdcall target2(void* object);

struct Sub { unsigned char bytes[0x100]; };

struct Outer {
    unsigned char pad_000[0x103C];
    Sub sub;
    __declspec(noinline) int Run();
};

#pragma code_seg(".text$01run")
int Outer::Run() {
    return target2(&this->sub);
}
#pragma code_seg()
