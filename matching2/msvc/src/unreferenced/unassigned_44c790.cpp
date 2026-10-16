

extern "C" void __cdecl asm_Ordinal_11_00452170();
struct JoystickInterface2;
struct PropertyOwner {
    void Apply(JoystickInterface2** slot);
};

struct JoystickInterface2 {
    struct Vtable {
        void* query_interface;
        void* add_reference;
        void (__stdcall *release)(JoystickInterface2*);
        void* reserved_0c;
        void* reserved_10;
        void* reserved_14;
        int (__stdcall *configure)(JoystickInterface2*, int, int);
    };
    Vtable* vtable;
};

struct JoystickSlot2 {
    JoystickInterface2* interface_pointer;

    __declspec(noinline) int Configure(int device, int flags, int property_owner);
};

#pragma code_seg(".text$03setup")
int JoystickSlot2::Configure(int device, int flags, int property_owner) {
    JoystickInterface2* interface_pointer = this->interface_pointer;
    if (interface_pointer != 0) {
        interface_pointer->vtable->release(interface_pointer);
        this->interface_pointer = 0;
    }

    typedef int (__stdcall *Probe)(int, void*, int);
    int result = reinterpret_cast<Probe>(asm_Ordinal_11_00452170)(0, this, 0);
    if (result >= 0) {
        interface_pointer = this->interface_pointer;
        result = interface_pointer->vtable->configure(interface_pointer, device, flags);
        if (result >= 0) {
            reinterpret_cast<PropertyOwner*>(property_owner)->Apply(
                &this->interface_pointer);
            result = 0;
        }
    }
    return result;
}
#pragma code_seg()
