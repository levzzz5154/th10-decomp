// 0x0042C920..0x0042C9EB: initialise the progress-worker state allocation.
//
// Retail takes the object in EDX, clears all 0x5ACC bytes, sets the flag word
// at +4 to 2, publishes the object through data_0047784c, and returns it in
// EAX. The fastcall's unused first argument occupies ECX; the object is its
// second argument, in EDX.
struct ProgressWorkerStorage_0042c920 {
    unsigned int reserved_0000;
    unsigned int flags_0004;
    unsigned char contents_0008[0x5AC4];
};

typedef char ProgressWorkerStorage_0042c920_size_check[
    sizeof(ProgressWorkerStorage_0042c920) == 0x5ACC ? 1 : -1];

extern "C" ProgressWorkerStorage_0042c920* data_0047784c;
extern "C" void* __cdecl asm_memset_0045bed0(
    void* destination, int value, unsigned int count);

extern "C" __declspec(noinline) ProgressWorkerStorage_0042c920* __fastcall
InitializeProgressWorkerStorageAt0042C920(
    void* unused_ecx, ProgressWorkerStorage_0042c920* state) {
    (void)unused_ecx;

    asm_memset_0045bed0(state, 0, sizeof(*state));
    state->flags_0004 = 2;
    data_0047784c = state;
    return state;
}
