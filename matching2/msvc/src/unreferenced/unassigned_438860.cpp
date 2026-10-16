// 0x00438860..0x00438869: allocate the incoming size through the image's
// operator new.
extern "C" void* __cdecl operator_new2(unsigned int size);

#pragma code_seg(".text$01accessor")
__declspec(noinline) void* __cdecl Allocate2(unsigned int size) {
    return operator_new2(size);
}
#pragma code_seg()
