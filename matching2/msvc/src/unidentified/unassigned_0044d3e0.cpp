// 0x0044D3E0..0x0044D3F2: bounds-checked element lookup.
//
// The table keeps its element array at +0x04 and its element count at +0x10.
// The index arrives in EDX and nothing is popped, so the model is the free
// __fastcall form the project uses for register-entry helpers; the two early
// returns are separate statements because that is the layout c2 gives them.
struct UnassignedTable_0044d3e0 {
    unsigned char pad_00[4];
    void** elements;     // +0x0004
    unsigned char pad_08[8];
    unsigned int count;  // +0x0010
};

extern "C" void* __fastcall UnassignedTable_Lookup(UnassignedTable_0044d3e0* table,
                                                   unsigned int index) {
    if (table->elements == 0)
        return 0;
    if (index >= table->count)
        return 0;
    return table->elements[index];
}
