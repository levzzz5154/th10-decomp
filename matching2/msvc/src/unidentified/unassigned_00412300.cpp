// 0x00412300..0x0041234F: the address of one of the four float variables at
// +0x1138, selected by its script id (-9985..-9982), or null for another id.
struct FloatVars_00412300 {
    unsigned char reserved_0000[0x1138];
    float values[4];                        // +0x1138
    float* Find(int id);
};

float* FloatVars_00412300::Find(int id) {
    switch (id) {
    case -9985:
        return &values[0];
    case -9984:
        return &values[1];
    case -9983:
        return &values[2];
    case -9982:
        return &values[3];
    }
    return 0;
}
