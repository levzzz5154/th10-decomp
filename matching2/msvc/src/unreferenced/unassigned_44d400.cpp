// 0x0044D400: query one entry of an interface list for the interface 0x0046747C names.
extern "C" const unsigned char g_iid_unk_indirect[16];
struct Interface2 {
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
struct InterfaceList {
    int unknown_00;
    Interface2** items;
    int unknown_08;
    int unknown_0c;
    unsigned int count;
};

#pragma code_seg(".text$01accessor")
__declspec(noinline) long __stdcall QueryItem(InterfaceList* list, unsigned int index, void** object) {
    if (!list->items) return 0x800401F0;
    if (index >= list->count) return 0x80070057;
    *object = 0;
    return list->items[index]->QueryInterface(g_iid_unk_indirect, object);
}
#pragma code_seg()
