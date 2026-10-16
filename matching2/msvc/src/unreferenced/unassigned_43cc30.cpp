// 0x0043CC30..0x0043CC3C: mark the record ready.
struct Object33 {
    __declspec(noinline) int Reset();
};

#pragma code_seg(".text$01accessor")
int Object33::Reset() {
    *(unsigned int*)((unsigned char*)this + 0x5224) = 2;
    return 0;
}

#pragma code_seg()
