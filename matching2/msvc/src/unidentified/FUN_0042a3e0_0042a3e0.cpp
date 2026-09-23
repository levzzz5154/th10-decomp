// Ghidra's body at 0x0042A3E0 reads this global as a pointer-sized value.
// The original symbol headers type it as a byte because they describe the
// storage address, so read the stored pointer through its address explicitly.
extern "C" unsigned char data_00477810;
extern "C" unsigned int data_00474e30;

struct SceneState_0042a3e0 {
    unsigned char pad_00[0x58];
    unsigned char flags_58;
};

struct Object_0042a3e0 {
    unsigned char pad_00[0x10];
    int field_10;
    unsigned char pad_14[0x1B4];
    int field_1C8;

    __declspec(noinline) int __thiscall Check();
};

// Observed callback ABI: ECX supplies this, EAX returns 1 or 6, and the
// function uses a plain RET.  Names describe offsets only; their semantics
// are not established by the available evidence.
int __thiscall Object_0042a3e0::Check() {
    SceneState_0042a3e0* scene =
        *reinterpret_cast<SceneState_0042a3e0**>(&data_00477810);
    if (scene) {
        int result = 1;
        if ((scene->flags_58 & 4u) != 0) {
            return result;
        }
        if (field_10 != 1) {
            return result;
        }
        if ((data_00474e30 & 0x100u) == 0) {
            return result;
        }

        result = 1;
        if (field_1C8 % 4 != 0) {
            result = 6;
        }
        return result;
    }

    return 1;
}
