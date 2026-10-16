// 0x00405150: store a value in the runtime record field at +0x48.
// Retail receives the record in ECX and the value in EAX and ends in a plain RET.

struct RuntimeRecord {
    char unknown_00[0x48];
    int value_48;                       // +0x48
};

__declspec(noinline) void StoreValue48(RuntimeRecord* record, int value);

#pragma code_seg(".text$01f405150")
void StoreValue48(RuntimeRecord* record, int value) {
    record->value_48 = value;
}
#pragma code_seg()
