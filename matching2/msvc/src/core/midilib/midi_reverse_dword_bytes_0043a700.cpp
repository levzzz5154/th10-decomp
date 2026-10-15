// 0x0043A700: reverse the four bytes of a big-endian MIDI file dword (chunk
// lengths). The argument's bytes are read through its address, so the
// whole-program pass keeps it on the stack and gives the result its own word.
#pragma code_seg(".text$01swap")
__declspec(noinline) unsigned int __stdcall ReverseDwordBytes_0043a700(unsigned int value) {
    unsigned char bytes[4];
    bytes[0] = reinterpret_cast<unsigned char*>(&value)[3];
    bytes[1] = reinterpret_cast<unsigned char*>(&value)[2];
    bytes[2] = reinterpret_cast<unsigned char*>(&value)[1];
    bytes[3] = reinterpret_cast<unsigned char*>(&value)[0];
    return *reinterpret_cast<const unsigned int*>(bytes);
}
#pragma code_seg()
