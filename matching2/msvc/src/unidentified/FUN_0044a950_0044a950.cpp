// 0x0044A950..0x0044A9CE: update one keyboard binding record.
//
// Native LTCG keeps the private game ABI: the binding-set index arrives in
// ECX, the action word is retained in AX, and the action word is returned in
// AX.  The neighboring binding reader supplies the action word at the call
// site; the optimizer is intentionally allowed to choose the ESI/EDI loop
// allocation used by retail.
struct KeyboardBinding_0044a950 {
    unsigned short current;
    unsigned short previous;
    unsigned short repeat;
    unsigned short pressed;
    unsigned short released;
    unsigned short counters[16];
    unsigned char unknown_2A[0x6A - 0x2A];
};

extern "C" KeyboardBinding_0044a950 data_00474e30[];

#pragma code_seg(".text$01bindingedge")
extern "C" unsigned short __declspec(noinline) __fastcall
asm_FUN_0044a950_0044a950(unsigned int binding_set, unsigned short result) {
    KeyboardBinding_0044a950* binding = &data_00474e30[binding_set];

    binding->previous = binding->current;
    binding->current = result;

    unsigned short bit = 1;
    unsigned short bits = result;
    binding->repeat = 0;
    unsigned short* counter = binding->counters;
    int remaining = 16;
    do {
        if (bits & 1) {
            if (++*counter >= 0x1A) {
                binding->repeat |= bit;
                *counter -= 8;
            }
        } else {
            *counter = 0;
        }
        bits >>= 1;
        ++counter;
        bit <<= 1;
    } while (--remaining);

    unsigned short now = binding->current;
    unsigned short before = binding->previous;
    unsigned short changed = now ^ before;
    binding->pressed = changed & now;
    binding->released = changed & ~now;
    return result;
}
#pragma code_seg()
