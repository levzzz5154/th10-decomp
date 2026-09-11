// 0x0043BB30: submits a six-word description through the interface pointer at
// 0x00491C3C (slot 0x18 of its vtable). Returns 0 only when that call fails;
// a description whose first word is already aligned reports success at once.
struct BlitRequest {
    int field_00;
    int field_04;
    int field_08;
    int field_0C;
    int field_10;
    int field_14;
};

struct Device {
    void** vtable;                   // +0x00
};

extern "C" unsigned char data_00491c3c;

int __stdcall FUN_0043bb30_0043bb30(int a1, int a2) {
    int result = 1;
    if ((*(int*)(a1 + 24) & 3) != 0) {
        BlitRequest request;
        request.field_00 = 24;
        request.field_04 = 16;
        request.field_08 = *(int*)(a1 + 24);
        request.field_0C = 2;
        request.field_10 = -1000;
        request.field_14 = 1000;
        Device* device = *(Device**)&data_00491c3c;
        if (((int (__stdcall*)(Device*, int, BlitRequest*))device->vtable[6])(
                device, 4, &request) < 0)
            return 0;
    }
    return result;
}
