// 0x004130E0 - store one word into the object's second slot and return it.
// The value arrives on the stack (ECX is the object), so this is the __thiscall
// setter of that slot.
struct Object004130e0 {
    int first;   // +0x00
    int second;  // +0x04

    int SetSecond(int value);
};

int Object004130e0::SetSecond(int value) {
    second = value;
    return value;
}
