// 0x0042AB80: scalar deleting destructor for a list node. Retail keeps the
// object in ESI, unlinks it from the pair of neighbours at +0x627C/+0x6280 and
// takes the delete flag from the first stack argument.
struct ListNode_0042ab80 {
    void* field_000;
    ListNode_0042ab80* field_004;
    ListNode_0042ab80* field_008;
};
struct OwnedObject_0042ab80 {
    unsigned char pad_000[0x627C];
    ListNode_0042ab80* field_627c;
    ListNode_0042ab80* field_6280;
};
extern "C" void __cdecl entry_free_004524a1(void* memory);
__declspec(noinline) void* DestroyOwned_DeletingDestructor_0042ab80(OwnedObject_0042ab80* object, unsigned int flags);
#pragma code_seg(".text$01delete0042ab80")
void* DestroyOwned_DeletingDestructor_0042ab80(OwnedObject_0042ab80* object, unsigned int flags) {
    if (object->field_627c) object->field_627c->field_008 = object->field_6280;
    if (object->field_6280) object->field_6280->field_004 = object->field_627c;
    object->field_627c = 0;
    object->field_6280 = 0;
    if (flags & 1) entry_free_004524a1(object);
    return object;
}
#pragma code_seg()
