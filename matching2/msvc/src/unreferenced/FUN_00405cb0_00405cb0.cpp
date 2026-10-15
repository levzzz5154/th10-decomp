// 0x00405CB0..0x00405CB7: indexed global-table lookup.
// Native LTCG gives the sole integer input its private EAX register ABI.
extern "C" int data_00474170[];

#pragma code_seg(".text$01target")
extern "C" __declspec(noinline) int __cdecl asm_FUN_00405cb0_00405cb0(int index) {
    return data_00474170[index];
}
#pragma code_seg()
