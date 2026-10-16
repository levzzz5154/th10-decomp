struct ValueHelper {
    unsigned char reserved[0x1004];
    int value;
    __declspec(noinline) int __fastcall add(int delta) {
        int result = value;
        result += delta;
        result += (int)this;
        return result;
    }
};
extern "C" __declspec(noinline) int force_emit(
        ValueHelper* value, int delta) {
    return value->add(delta);
}

