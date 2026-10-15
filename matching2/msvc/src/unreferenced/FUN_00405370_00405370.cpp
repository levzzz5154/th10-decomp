// One entry of the input mapping table; only its first word is written here.
struct InputBinding {
    int value;
    int Set(int new_value);   // __thiscall: the table pointer arrives in ECX
};

// 0x00405370: InputBinding::Set - store the bound value and pass it back.
int InputBinding::Set(int new_value) {
    value = new_value;
    return new_value;
}
