
struct StreamState {
    unsigned char reserved_000[0x7c];
    int state_07c;
    void* value_080;
    void* value_084;
    volatile int value_088;
    unsigned char reserved_08c[4];
    void* value_090;

    __declspec(noinline) int Initialize(
            void* value_090_arg, void* value_080_arg,
            int value_088_arg, int count_arg);
};

#pragma code_seg(".text$01initializer")
__declspec(noinline) int StreamState::Initialize(
        void* value_090_arg, void* value_080_arg,
        int value_088_arg, int count_arg) {
    value_090 = value_090_arg;
    value_088 = value_088_arg;
    value_080 = value_080_arg;
    value_084 = value_080_arg;
    state_07c = 1;
    int result = count_arg - 1;
    return result ? (int)0x80004001u : 0;
}
#pragma code_seg()
