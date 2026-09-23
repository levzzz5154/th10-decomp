// 0x00417660..0x0041766F: compare the first integer stored in an unidentified
// receiver with the one stack argument and return whether they differ.
//
// The current Ghidra database does not define a Function object at this
// address. The region's retail instructions nevertheless establish a normal
// x86 thiscall member shape: ECX is read as the receiver, the argument is at
// [ESP+4], and RET 4 removes that stack argument. No caller xrefs are recorded,
// so the receiver's owner and higher-level meaning remain unknown.
struct UnidentifiedIntField_00417660 {
    int value;

    __declspec(noinline) bool IsNotEqualTo(int other) const;
};

bool UnidentifiedIntField_00417660::IsNotEqualTo(int other) const {
    return value != other;
}
