// 0x00427D70..0x00427D75: store the two private register arguments.
// Native LTCG selects the object pointer in EAX and the values in ECX/EDX.
struct Pair_00427d70 {
    int first_000;
    int second_004;

    __declspec(noinline) void Set(int first, int second);
};

typedef char Pair_00427d70_size_must_fit[
    sizeof(Pair_00427d70) == 0x8 ? 1 : -1];

#pragma code_seg(".text$01set")
void Pair_00427d70::Set(int first, int second) {
    first_000 = first;
    second_004 = second;
}
#pragma code_seg()
