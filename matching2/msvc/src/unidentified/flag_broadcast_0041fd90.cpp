// 0x0041FD90: if a record is flagged, raise the running bit of three
// sub-records, clear a global bit, publish a global mode and clear the flag.
// Both the early exit and the tail return 1, so MSVC merges them into one.
struct Sub_0041fd90 { unsigned char pad_000[4]; unsigned int flags_004; };
struct Owner_0041fd90 {
    unsigned char pad_000[0x0C];
    Sub_0041fd90* a_00c;                 // +0x00C
    Sub_0041fd90* b_010;                 // +0x010
    unsigned char pad_014[0x89a8 - 0x14];
    Sub_0041fd90* c_89a8;                // +0x89A8
};
struct Flagged_0041fd90 { unsigned int flags_000; };
extern "C" Owner_0041fd90* data_004776e0;
extern "C" unsigned int data_00491ff4;
extern "C" unsigned int data_00491fb8;
extern "C" __declspec(noinline) int __fastcall Update_0041fd90(void* unused, Flagged_0041fd90* record);
#pragma code_seg(".text$01flag")
int __fastcall Update_0041fd90(void* unused, Flagged_0041fd90* record) {
    (void)unused;
    if (!(record->flags_000 & 2u))
        return 1;
    Owner_0041fd90* owner = data_004776e0;
    owner->a_00c->flags_004 |= 2u;
    owner->b_010->flags_004 |= 2u;
    owner->c_89a8->flags_004 |= 2u;
        unsigned int* global = &data_00491ff4;
        *global &= 0xFFFFEFFFu;
        unsigned int* mode = &data_00491fb8;
        *mode = 4u;
        unsigned int* flags = &record->flags_000;
        *flags &= ~2u;
    return 1;
}
#pragma code_seg()
