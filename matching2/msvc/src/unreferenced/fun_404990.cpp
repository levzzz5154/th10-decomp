// 0x00404990 (4 bytes): read the 32-bit field at offset 0x44 of the object.
//
// retail:  mov eax,[eax+44h] ; ret
// The object pointer arrives in EAX and the loaded field is handed back in EAX,
// the internal convention the whole-program link-time code generator chose for
// this leaf.  Plain C++ cannot name such a convention: writing the natural
// getter and letting the synthetic caller below be compiled in the same /LTCG
// cluster makes the global register allocator pick the same two registers.

struct Field44Holder {
    char unknown[0x44];
    int field_44;

    __declspec(noinline) int GetField44();
};

#pragma code_seg(".text$01read44")
int Field44Holder::GetField44() {
    return this->field_44;
}
#pragma code_seg()
