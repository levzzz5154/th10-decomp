// 0x00404CE0 (7 bytes): read the 32-bit field at offset 0x84 of the object.
//
// retail:  mov eax,[eax+84h] ; ret
// The object pointer arrives in EAX and the value is handed back in EAX, the
// internal convention the link-time code generator chose.  Writing the natural
// getter and compiling it together with the synthetic caller below under /LTCG
// lets the global register allocator pick the same registers.

struct Field84Holder {
    char unknown[0x84];
    int field_84;

    __declspec(noinline) int GetField84();
};

#pragma code_seg(".text$01get84")
int Field84Holder::GetField84() {
    return this->field_84;
}
#pragma code_seg()
