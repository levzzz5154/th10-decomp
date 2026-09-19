// 0x00436380..0x00436391: stamp the vtable and clear the three leading words.
extern "C" unsigned int data_0046f308;
struct Object_00436380 {
    __declspec(noinline) void Init();
};

#pragma code_seg(".text$01accessor")
void Object_00436380::Init() {
    *(unsigned int*)this = (unsigned int)&data_0046f308;
    *(unsigned int*)((unsigned char*)this + 4) = 0;
    *(unsigned int*)((unsigned char*)this + 8) = 0;
    *(unsigned int*)((unsigned char*)this + 0xc) = 0;
}

#pragma code_seg()
