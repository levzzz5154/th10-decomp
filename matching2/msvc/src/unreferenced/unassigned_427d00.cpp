// 0x00427D00..0x00427D21: add a pair into the receiver and return its new value.
// The two fields are modeled as 32-bit words so the source expresses the
// modulo-2^32 additions performed by the x86 ADD instructions.
struct Pair4 {
    unsigned int first;
    unsigned int second;

    Pair4() {}
    Pair4(unsigned int first_value, unsigned int second_value)
        : first(first_value), second(second_value) {}
    Pair4(const Pair4& other)
        : first(other.first), second(other.second) {}

    __declspec(noinline) Pair4 __fastcall AddAndCopy(
        const Pair4& delta);
};

#pragma code_seg(".text$01addcopy")
__declspec(noinline) Pair4 __fastcall Pair4::AddAndCopy(
        const Pair4& delta) {
    first += delta.first;
    second += delta.second;
    return *this;
}
#pragma code_seg()
