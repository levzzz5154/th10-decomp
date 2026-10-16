// 0x0040CD80: fastcall indexed store with a twelve-element base offset.
// The source parameter order is intentional; native LTCG selects ECX/EDX/EAX.
#pragma code_seg(".text$01f")
extern "C" __declspec(noinline) void __fastcall H3701CD80_Fast2(
    int index, int* object, int value) {
    object[index + 12] = value;
}
#pragma code_seg()
