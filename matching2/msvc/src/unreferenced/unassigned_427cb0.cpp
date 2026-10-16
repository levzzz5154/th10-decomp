// 0x00427CB0..0x00427CB5 (6 bytes): subtract 20 from the signed countdown at
// +0x08.
//
// Retail is `add word ptr [eax+8],0FFECh` / `ret`.  The object arrives in EAX
// and nothing is returned, so the store is the whole body.  The sibling leaves
// 0x00427C90 (`sub word ptr [eax+8],cx` with a floor at zero) and 0x00427CC0
// (this field divided by 20) read the same 16-bit field.

struct Countdown2 {
    unsigned char unknown_00[0x08];
    short value;                   // +0x08

    __declspec(noinline) void SubtractTick();
};

#pragma code_seg(".text$01sub")
void Countdown2::SubtractTick() {
    value -= 20;
}
#pragma code_seg()
