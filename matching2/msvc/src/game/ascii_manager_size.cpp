// 0x00401C90: the only slot of the ASCII manager's info vtable (0x0046CB14,
// "AsciiInf"): the manager's allocation size, 0x89AC bytes.
extern "C" int __cdecl AsciiManager_GetSize() {
    return 0x89AC;
}
