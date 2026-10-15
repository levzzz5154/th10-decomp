// The enemy's ECL variable lookups (vtable 0x0046D0C0 slots 0x08 and 0x10):
// the address of one of its four float or four integer script variables,
// selected by the variable's id, or null for any other id.
struct Enemy {
    unsigned char unknown_0000[0x1138];
    float float_vars[4];                     // +0x1138, ids -9985..-9982
    int int_vars[4];                         // +0x1148, ids -9981..-9978
    float* GetFloatVarAddress(int id);
    int* GetIntVarAddress(int id);
};

// 0x00412300
float* Enemy::GetFloatVarAddress(int id) {
    switch (id) {
    case -9985:
        return &float_vars[0];
    case -9984:
        return &float_vars[1];
    case -9983:
        return &float_vars[2];
    case -9982:
        return &float_vars[3];
    }
    return 0;
}

// 0x004126D0
int* Enemy::GetIntVarAddress(int id) {
    switch (id) {
    case -9981: return &int_vars[0];
    case -9980: return &int_vars[1];
    case -9979: return &int_vars[2];
    case -9978: return &int_vars[3];
    default: return 0;
    }
}
