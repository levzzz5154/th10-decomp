// 0x00405160: store a value in the runtime record field at +0x44.
// Retail receives the record in EAX and the value in ECX and ends in a plain RET.

struct RuntimeRecord {
    char unknown_00[0x44];
    int value_44;                       // +0x44

    __declspec(noinline) void SetValue44(int value);
};

#pragma code_seg(".text$01f405160")
void RuntimeRecord::SetValue44(int value) {
    this->value_44 = value;
}
#pragma code_seg()
