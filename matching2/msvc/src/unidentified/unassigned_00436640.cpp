// 0x00436640..0x00436651: clear the three trailing words and stamp the vtable.
extern "C" unsigned int data_0046f328;
struct Object_00436640 {
    __declspec(noinline) void Construct();
};

#pragma code_seg(".text$01accessor")
void Object_00436640::Construct() {
    *(unsigned int*)((unsigned char*)this + 4) = 0;
    *(unsigned int*)((unsigned char*)this + 8) = 0;
    *(unsigned int*)((unsigned char*)this + 0xc) = 0;
    *(unsigned int*)this = (unsigned int)&data_0046f328;
}

#pragma code_seg()
