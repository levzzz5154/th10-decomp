struct ValueHelper_0044df20 {
    unsigned char reserved[0x1004];
    int value;
    __declspec(noinline) int __fastcall add(int delta) {
        int result = value;
        result += delta;
        result += (int)this;
        return result;
    }
};
extern "C" __declspec(noinline) int force_emit_0044df20(
        ValueHelper_0044df20* value, int delta) {
    return value->add(delta);
}

