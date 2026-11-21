// 0x00462BED..0x00462BF0: Address the payload following an eight-byte header.
extern "C" void* __fastcall crt_helper_462bed(void* object) {
    return static_cast<unsigned char*>(object) + 8;
}
