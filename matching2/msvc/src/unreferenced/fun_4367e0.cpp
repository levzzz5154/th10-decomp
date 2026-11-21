// 0x4367e0: initialise the resource slot pair and return the object in EAX.
// The object arrives in EAX and the value in ECX, which only a native LTCG
// link chooses together, so this region is compiled as a cluster
// (resource_slot_init.json).

struct ResourceSlotInit {
    int field_00000; // +0x00
    int field_00004; // +0x04
    int field_00008; // +0x08
    __declspec(noinline) void Init(int value);
};
typedef char ResourceSlotInit_004367e0_size_must_fit[sizeof(ResourceSlotInit) == 0x0C ? 1 : -1];

#pragma code_seg(".text$01init004367e0")
void ResourceSlotInit::Init(int value) {
    field_00004 = 0;
    field_00008 = value;
}
#pragma code_seg()
