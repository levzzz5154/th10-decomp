// 0x00404C90 (7 bytes): store an integer into the field at offset 0x84.
//
// retail:  mov [eax+84h],ecx ; ret
// This one takes the object pointer in EAX and the value in ECX: a declared
// result would put EAX on the result instead, so the recovered function is
// declared void and the synthetic caller below, compiled in the same /LTCG
// cluster, makes the global register allocator pick retail's registers.

struct Field84Setter {
    char unknown[0x84];
    int field_84;

    __declspec(noinline) void SetField84(int value);
};

#pragma code_seg(".text$01set84")
void Field84Setter::SetField84(int value) {
    this->field_84 = value;
}
#pragma code_seg()
