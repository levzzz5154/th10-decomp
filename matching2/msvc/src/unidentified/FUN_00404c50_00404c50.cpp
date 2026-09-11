// 0x00404C50 (7 bytes): store an integer into the field at offset 0x88.
//
// retail:  mov [ecx+88h],eax ; ret
// The object pointer arrives in ECX and the value in EAX; the stored value is
// returned in EAX.  Writing the natural setter and compiling it together with
// the synthetic caller below under /LTCG lets the link-time global register
// allocator choose the same registers, which no plain C++ spelling can name.

struct Field88Holder {
    char unknown[0x88];
    int field_88;

    __declspec(noinline) int SetField88(int value);
};

#pragma code_seg(".text$01set88")
int Field88Holder::SetField88(int value) {
    this->field_88 = value;
    return value;
}
#pragma code_seg()
