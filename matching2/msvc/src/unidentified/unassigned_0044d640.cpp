// 0x0044D640: report whether any entry of an interface list has flag bit 0 set.
struct Interface_0044d640 {
    virtual long __stdcall QueryInterface(const void* iid, void** object) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual long __stdcall Method3() = 0;
    virtual long __stdcall Method4() = 0;
    virtual long __stdcall Method5() = 0;
    virtual long __stdcall Method6() = 0;
    virtual long __stdcall Method7() = 0;
    virtual long __stdcall Method8() = 0;
    virtual long __stdcall GetFlags(int* flags) = 0;
};
struct InterfaceList_0044d640 {
    int unknown_00;
    Interface_0044d640** items;
    int unknown_08;
    int unknown_0c;
    unsigned int count;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) int __stdcall AnyFlagSet_0044d640(InterfaceList_0044d640* list) {
    int result = 0;
    if (!list->items) return 0;
    for (unsigned int i = 0; i < list->count; ++i) {
        if (list->items[i]) {
            int flags = 0;
            list->items[i]->GetFlags(&flags);
            result |= flags & 1;
        }
    }
    return result;
}
#pragma code_seg()
