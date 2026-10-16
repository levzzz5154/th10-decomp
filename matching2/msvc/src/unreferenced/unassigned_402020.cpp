extern "C" void __cdecl crt_free(void* block);

struct Holder {
    unsigned char pad_000[0x358];
    void* field_358;
    __declspec(noinline) void ReleaseOwned();
};

#pragma code_seg(".text$01release")
void Holder::ReleaseOwned() {
    if (field_358) crt_free(field_358);
    field_358 = 0;
}
#pragma code_seg()
