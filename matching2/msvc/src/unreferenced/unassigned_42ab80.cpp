// 0x0042AB80: scalar deleting destructor for a list node. Retail keeps the
// object in ESI, unlinks it from the pair of neighbours at +0x627C/+0x6280 and
// takes the delete flag from the first stack argument.
struct ListNode2 {
    void* field_000;
    ListNode2* field_004;
    ListNode2* field_008;
};
struct OwnedObject10 {
    unsigned char pad_000[0x627C];
    ListNode2* field_627c;
    ListNode2* field_6280;
};
extern "C" void __cdecl crt_free_startup(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor5(OwnedObject10* object, unsigned int flags);
#pragma code_seg(".text$01delete0042ab80")
void* DestroyOwned_DeletingDestructor5(OwnedObject10* object, unsigned int flags) {
    if (object->field_627c) object->field_627c->field_008 = object->field_6280;
    if (object->field_6280) object->field_6280->field_004 = object->field_627c;
    object->field_627c = 0;
    object->field_6280 = 0;
    if (flags & 1) crt_free_startup(object);
    return object;
}
#pragma code_seg()
